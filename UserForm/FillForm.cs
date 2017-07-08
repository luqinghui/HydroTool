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
    public partial class FillForm : Form
    {
        public FillForm()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            bool identify = false;
            if (checkBox1.Checked)
                identify = true;
            DllExportMethod.FillDepressionAlg(FileNameTextBox.Text, identify);
            MessageBox.Show("Fill Done!");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_dlg = new OpenFileDialog();
            if (open_dlg.ShowDialog() == DialogResult.OK)
            {
                FileNameTextBox.Text = open_dlg.FileName;
            }
        }
    }
}
