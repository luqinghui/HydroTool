using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace UserForm
{
    public static class DllExportMethod
    {
        const string DllPath = @"Toolbox.dll";

        [DllImport(DllPath, EntryPoint = "fill_depression_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int FillDepressions(string filename);

        [DllImport(DllPath, EntryPoint = "identify_depression_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int IdentifyDepressions(string filename);

        [DllImport(DllPath, EntryPoint = "flow_dir_original_d8_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int FlowDirectionD8(string filename, bool forceout);

        [DllImport(DllPath, EntryPoint = "flow_dir_pf_d8_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int FlowDirectionPF(string filename, bool forceout);

        [DllImport(DllPath, EntryPoint = "flow_accu_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int FlowAccumulation(string filename);

        [DllImport(DllPath, EntryPoint = "identify_nested_depressions_alg", CallingConvention = CallingConvention.StdCall)]
        public static extern int IdentifyNestedDepressions(string filename);
    }
}
