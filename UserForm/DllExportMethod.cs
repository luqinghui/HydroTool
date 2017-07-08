﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace UserForm
{
    public static class DllExportMethod
    {
        const string DebugDllPath = @"..\..\..\x64\Debug\Toolbox.dll";
        const string ReleaseDllPath = @"..\..\..\x64\Release\Toolbox.dll";

        [DllImport(ReleaseDllPath, EntryPoint = "fill_depression_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int FillDepressionAlg(string filename, bool indentify);

        [DllImport(ReleaseDllPath, EntryPoint = "identify_depression_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int IdentifyDepressionAlg(string filename);

        [DllImport(ReleaseDllPath, EntryPoint = "flow_dir_original_d8_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int FlowDirectionD8(string filename, bool forceout);

        [DllImport(ReleaseDllPath, EntryPoint = "flow_dir_pf_d8_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int FlowDirectionPF(string filename, bool forceout);
    }
}
