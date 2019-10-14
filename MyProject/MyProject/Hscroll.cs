using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyProject {
    public partial class Hscroll : Form {
        public Hscroll() {
            InitializeComponent();
            hScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(hScrollBar1_Scroll);
        }
        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e) {
            Form1.wave.setscroll(hScrollBar1.Value);
            Form1.midi.setscroll(hScrollBar1.Value);
            Form1.midi.updatepict();
        }
        public int getScrollVal() {
            return hScrollBar1.Value;
        }
        public void setscroll(int width) {
            hScrollBar1.Location = new Point(0, 0);
            hScrollBar1.Width = this.Width-10;
            hScrollBar1.Height = this.Height;
            hScrollBar1.Minimum = 0;
            hScrollBar1.Maximum = width;
        }
    }
}
