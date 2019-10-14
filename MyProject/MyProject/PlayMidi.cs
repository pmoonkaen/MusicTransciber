using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;

namespace MyProject {
    public static class PlayMidi {
        [DllImport("winmm.dll", EntryPoint = "mciSendStringA")]
        private static extern int mciSendString(string lpstrCommand, string lpstrReturnString, int uReturnLength, int hwndCallback);

        public static bool PlayMidiFile(string midiFile) {

            if (File.Exists(midiFile)) {
                mciSendString("Open \"" + midiFile + "\" type mpegvideo alias midi", null, 0, 0);
                int rtn = mciSendString("play midi", null, 0, 0);
                return (rtn == 0);
            }
            else
                return false;
        } 
    }
}
