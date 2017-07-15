using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UserForm
{    
    public partial class MainForm : Form
    {
        

        public MainForm()
        {
            InitializeComponent();
        }

        private void fillDepressionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FillForm fill = new FillForm();
            fill.ShowDialog();
        }

        private void identifyDepressionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_dlg = new OpenFileDialog();
            if(open_dlg.ShowDialog() == DialogResult.OK)
            {
                DllExportMethod.IdentifyDepressionAlg(open_dlg.FileName);
                MessageBox.Show("Identify Done!");
            }
        }

        private void d8ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FlowDirD8From d8 = new FlowDirD8From();
            d8.ShowDialog();
        }

        private void pFToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FlowDirPFFrom pf = new FlowDirPFFrom();
            pf.ShowDialog();
        }

        private void originalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FlowAccuForm accu = new FlowAccuForm();
            accu.ShowDialog();
        }
    }
}
