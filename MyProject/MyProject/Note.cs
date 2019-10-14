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
    public partial class Note : Form {
        public Note() {
            InitializeComponent();
        }
        public void setImage() {
            Bitmap image = new Bitmap(MyProject.Properties.Resources.Left);
            this.pictureBox1.Image = image;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Width = image.Width;
            this.pictureBox1.Height = image.Height;
        }
        public void setVscroll(int val) {
            this.AutoScrollPosition = new Point(Form1.hscroll.getScrollVal(), val);
        }
    }
}
