using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyProject {
    public partial class Wave : Form {
        public int number,maxnum;
        struct WavHeader
        {
            public byte[] riffID;
            public uint size;
            public byte[] wavID;
            public byte[] fmtID;
            public uint fmtSize;
            public ushort format;
            public ushort channels;
            public uint sampleRate;
            public uint bytePerSec; 
            public ushort blockSize;
            public ushort bit;
            public byte[] dataID;
            public uint dataSize;
        }
        WavHeader Header = new WavHeader();
        public byte trash;
        List<short> DataList = new List<short>();
        public int w,ww;
        public Wave()
        {
            InitializeComponent();
            number = 1;
            w = DataList.Count * 52 / 44100;
            maxnum = Convert.ToInt32(Math.Ceiling(Convert.ToDouble(DataList.Count) / (44100 * 15)));
        }
        public void setscroll(int val) {
            this.AutoScrollPosition = new Point(val, val);
        }
        public void setchart() {
            chart1.Location = new Point(0, 20);
            chart1.Width = (int)(DataList.Count * (long)1024 / 661500);
            chart1.Height = this.Height - 20;
        }
        public void setscale() {
            for (int i = 0; (i+1)*44100 <= DataList.Count; i++) {
                TextBox textbox = new TextBox();
                textbox.Location = new System.Drawing.Point((int)(68.266* (this.Controls.Count-1)), 0);
                textbox.Size = new System.Drawing.Size(35, 20);
                textbox.Name = "textbox_" + this.Controls.Count + 1;
                textbox.Text = (i / 60).ToString("D2") + ":" + (i % 60).ToString("D2");
                this.Controls.Add(textbox);
            }
        }
        public int ReadWave(string wavname){
            //int[] a = new int[100000];
            chart1.Series["Series1"].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastLine;
            FileStream fs = new FileStream(wavname, FileMode.Open, FileAccess.Read);
            BinaryReader br = new BinaryReader(fs);
            Header.riffID = br.ReadBytes(4);
            Header.size = br.ReadUInt32();
            Header.wavID = br.ReadBytes(4);
            Header.fmtID = br.ReadBytes(4);
            Header.fmtSize = br.ReadUInt32();
            Header.format = br.ReadUInt16();
            Header.channels = br.ReadUInt16();
            Header.sampleRate = br.ReadUInt32();
            Header.bytePerSec = br.ReadUInt32();
            Header.blockSize = br.ReadUInt16();
            Header.bit = br.ReadUInt16();
            for (int i = 0; i < Header.fmtSize - 16; i++) {
                trash = br.ReadByte();
            }
            while (true)
            {
                Header.dataID = br.ReadBytes(4);
                Header.dataSize = br.ReadUInt32();
                if (System.Text.Encoding.UTF8.GetString(Header.dataID) == "data") break;
                for (int i = 0; i < Header.dataSize; i++) {
                    trash = br.ReadByte();
                }
            }
            for (int i = 0; i < Header.dataSize / 2; i++)
            {
                DataList.Add((short)br.ReadUInt16());
                for (int j = 0; j < Header.channels - 1; j++,i++) {
                    short trash = (short)br.ReadUInt16();
                }
            }
            long sm = 0;
            for (int i = 0; i < DataList.Count ; i++)
            {
                
                chart1.Series["Series1"].Points.AddXY(i, DataList[i]);
            }
            //chart1.ChartAreas[0].AxisY.Maximum = 5000;
            return (int)(DataList.Count * (long)1024 / 661500);
        }

        private void Wave_Load(object sender, EventArgs e) {

        }
    }
}
