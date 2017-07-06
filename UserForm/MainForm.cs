using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace UserForm
{    
    public partial class MainForm : Form
    {
        const string DebugDllPath = @"..\..\..\x64\Debug\Toolbox.dll";
        const string ReleaseDllPath = @"..\..\..\x64\Release\Toolbox.dll";

        [DllImport(ReleaseDllPath, EntryPoint = "fill_depression_alg", CallingConvention = CallingConvention.StdCall)]
        static extern int FillDepressionAlg(string filename, bool indentify);

        public MainForm()
        {
            InitializeComponent();
        }

        private void fillDepressionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_dlg = new OpenFileDialog();
            if (open_dlg.ShowDialog() == DialogResult.OK)
            {
                FillDepressionAlg(open_dlg.FileName, false);
                MessageBox.Show("Fill Done!");
            }
        }

        private void identifyDepressionToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
