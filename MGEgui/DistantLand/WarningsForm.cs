using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MGEgui.DistantLand
{
    public partial class WarningsForm : Form
    {
        public WarningsForm(List<string> list) {
            InitializeComponent();
            lTotal.Text += list.Count;
            dgvWarnings.Columns[0].HeaderCell.Style.Alignment = DataGridViewContentAlignment.MiddleRight;
            dgvWarnings.Columns[0].DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleRight;
            int i = 0;
            foreach (string item in list) dgvWarnings.Rows.Add(new object[] {++i, item});
        }
    }
}
