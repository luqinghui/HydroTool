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
    public partial class IdentifyNestedDepressionsForm : Form
    {
        public IdentifyNestedDepressionsForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_dlg = new OpenFileDialog();
            if (open_dlg.ShowDialog() == DialogResult.OK)
            {
                FileNameTextBox.Text = open_dlg.FileName;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DllExportMethod.IdentifyNestedDepressions(FileNameTextBox.Text);
            MessageBox.Show("Flow Direction Done!");
        }
    }
}
