using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MyProject {
    class WavToMidi {
        [DllImport("MyDllProject.dll", CallingConvention = CallingConvention.Cdecl)]
        public extern static bool wavToMidi(String strin, String strout);
    }
}
