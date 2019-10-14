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
    public partial class Vscroll : Form {
        public Vscroll() {
            InitializeComponent();
            vScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(vScrollBar1_Scroll);
        }
        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e) {
            //Form1.wave.setscroll(hScrollBar1.Value);
            Form1.midi.setVscroll(vScrollBar1.Value);
            Form1.note.setVscroll(vScrollBar1.Value);
            Form1.midi.updatepict();
        }
        public int getScrollVal() {
            return vScrollBar1.Value;
        }
        public void setscroll(int height) {
            vScrollBar1.Location = new Point(0, 0);
            vScrollBar1.Width = this.Width;
            vScrollBar1.Height = this.Height;
            vScrollBar1.Minimum = 0;
            vScrollBar1.Maximum = height;
        }

        private void vScrollBar1_Scroll_1(object sender, ScrollEventArgs e) {

        }
    }
}
