using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Media;

namespace MyProject {
    public partial class Form1 : Form {
        OpenFileDialog OpenFileDialog1 = new OpenFileDialog();
        SaveFileDialog sfd1 = new SaveFileDialog();
        public static Wave wave = new Wave();
        public static Midi midi = new Midi();
        public static Hscroll hscroll = new Hscroll();
        public static Vscroll vscroll = new Vscroll();
        public static Note note = new Note();
        String filename, filename2;
        static string fn3;
        public static int width;
        public Form1() {
            InitializeComponent();
            this.AutoScroll = false;
        }
        private void formToolStripMenuItem_Click(object sender, EventArgs e) {
            OpenFileDialog1.DefaultExt = "*.wav";
            OpenFileDialog1.AddExtension = true;
            OpenFileDialog1.Filter = "Wave File (.wav) | *.wav";
            OpenFileDialog1.ShowDialog();
            sfd1.DefaultExt = "*.wav";
            sfd1.AddExtension = true;
            sfd1.Filter = "MIDI File (.mid) | *.mid";
            sfd1.ShowDialog();
            filename2 = sfd1.FileName.Replace("\\", "\\\\");
            filename = OpenFileDialog1.FileName.Replace("\\", "\\\\");
            WavToMidi.wavToMidi(filename, filename2);

            width = wave.ReadWave(OpenFileDialog1.FileName);
            setform();
            note.Show();
            wave.Show();
            midi.Show();
            hscroll.Show();
            vscroll.Show();
            this.playOutputToolStripMenuItem.Enabled = true;
        }
        private void setform() {
            int width1 = this.Width - 175;
            int line1 = 126;
            /*Wave*/
            wave.MdiParent = this;
            wave.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            wave.StartPosition = FormStartPosition.Manual;
            wave.AutoScroll = true;
            wave.AutoScrollMinSize = new Size(0, 0);
            wave.Location = new Point(line1, 0);
            wave.Width = width1 - 20;
            wave.Height = this.Height * 20 / 100;
            wave.setchart();
            wave.setscale();

            /*Midi*/
            midi.MdiParent = this;
            midi.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            midi.StartPosition = FormStartPosition.Manual;
            midi.AutoScroll = true;
            midi.Location = new Point(line1, this.Height * 23 / 100);
            midi.Width = width1;
            midi.Height = this.Height * 60 / 100;
            midi.setImage();
            midi.start();

            /*Note*/
            note.MdiParent = this;
            note.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            note.StartPosition = FormStartPosition.Manual;
            note.AutoScroll = true;
            note.Location = new Point(0, this.Height * 23 / 100);
            note.Width = line1 + 20;
            note.Height = this.Height * 60 / 100;
            note.setImage();

            /*Hscroll*/
            hscroll.MdiParent = this;
            hscroll.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            hscroll.StartPosition = FormStartPosition.Manual;
            hscroll.TopMost = true;
            hscroll.AutoScroll = false;
            hscroll.Location = new Point(line1, this.Height * 83 / 100);
            hscroll.Width = width1;
            hscroll.Height = 20;
            hscroll.setscroll(width - width1 + 25);

            /*Vscroll*/
            vscroll.MdiParent = this;
            vscroll.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            vscroll.StartPosition = FormStartPosition.Manual;
            vscroll.AutoScroll = false;
            vscroll.TopMost = true;
            vscroll.Location = new Point(line1 + width1 - 20, this.Height * 23 / 100);
            vscroll.Width = 20;
            vscroll.Height = this.Height * 60 / 100;
            vscroll.setscroll(midi.getHeight() - vscroll.Height);
        }

        private void playToolStripMenuItem_Click(object sender, EventArgs e) {
            PlayMidi.PlayMidiFile(sfd1.FileName);
        }

        
    }
}

