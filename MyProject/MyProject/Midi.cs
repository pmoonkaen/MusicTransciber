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
    public partial class Midi : Form {
        int[,] arr = new int [1000000,5];
        int num = 0;
        public static int height;
        public Midi()
        {
            InitializeComponent();
        }
        public int getHeight() {
            return height;
        }
        public void setscroll(int val) {
            this.AutoScrollPosition = new Point(val, Form1.vscroll.getScrollVal());
        }
        public void setVscroll(int val) {
            this.AutoScrollPosition = new Point(Form1.hscroll.getScrollVal(), val);
        }
        public void setImage() {
            Bitmap image = new Bitmap(MyProject.Properties.Resources.Right);
            Image thumb = image.GetThumbnailImage(Form1.width, image.Height, () => false, IntPtr.Zero);
            height = image.Height;
            this.pictureBox1.Image = thumb;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = thumb.Size;
        }
        public void start()
        {
            string fileContent = File.ReadAllText("mididata.txt");

            string[] integerStrings = fileContent.Split(new char[] { ' ', '\t', '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            int[] integers = new int[integerStrings.Length];

            for (int n = 0; n < integerStrings.Length; n++)
            {
                integers[n] = int.Parse(integerStrings[n]);
            }
            int cnt = 0;
            while (cnt < integerStrings.Length - 1)
            {
                int ssam = integers[cnt++];
                int nsam = integers[cnt++];
                int qqq = integers[cnt++];
                for (int i = 0; i < qqq; i++)
                {
                    int note = integers[cnt++];
                    arr[num, 0] = (int)(1024 * (long)ssam / (15 * 44100 - 1));
                    arr[num, 1] = ((88 - note) * 16) + 1;
                    arr[num, 2] = (int)(1024 * (long)(nsam - ssam) / (15 * 44100 - 1));
                    arr[num, 3] = 15;
                    arr[num, 4] = (int)(1024 * (long)nsam / (15 * 44100 - 1));
                    num++;
                }
            }
        }
        public void updatepict() {
            this.pictureBox1.Update();
        }
        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            int cnt2 = 0;
            while (cnt2 < num && arr[cnt2, 0] + arr[cnt2, 2] < this.pictureBox1.Width)
            {
                System.Drawing.SolidBrush myBrush = new System.Drawing.SolidBrush(System.Drawing.Color.Black);
                System.Drawing.Graphics formGraphics = this.pictureBox1.CreateGraphics();
                formGraphics.FillRectangle(myBrush, new Rectangle(arr[cnt2,0] , arr[cnt2, 1], arr[cnt2,2], arr[cnt2, 3]));
                myBrush.Dispose();
                formGraphics.Dispose();
                cnt2++;
            }
            while (cnt2 < num && arr[cnt2, 0] < this.pictureBox1.Width) {
                System.Drawing.SolidBrush myBrush = new System.Drawing.SolidBrush(System.Drawing.Color.Black);
                System.Drawing.Graphics formGraphics = this.pictureBox1.CreateGraphics();
                formGraphics.FillRectangle(myBrush, new Rectangle(arr[cnt2, 0], arr[cnt2, 1], this.pictureBox1.Width - arr[cnt2, 0], arr[cnt2, 3]));
                myBrush.Dispose();
                formGraphics.Dispose();
                cnt2++;
            }
        }
    }
}
