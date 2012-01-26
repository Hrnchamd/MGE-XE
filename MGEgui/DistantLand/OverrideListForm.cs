using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;

namespace MGEgui.DistantLand
{
    partial class OverrideListForm : Form
    {
        private ListBox lbStaticOverrideList;
        private Label lStaticOverrideList;

        public OverrideListForm(ListBox lbList, Label lList) {
            InitializeComponent();
            Statics.Localizations.Apply(this);

            this.openStaticListDialog.InitialDirectory = Statics.runDir + "\\MGE3";
            lStaticOverrideList = lList;
            lbStaticOverrideList = lbList;
            if (lbList != null) lbOverrideList.Items.AddRange(lbList.Items);
        }

        private void bClear_Click(object sender, EventArgs e) {
            lbOverrideList.Items.Clear();
        }

        private void bRemove_Click(object sender, EventArgs e) {
            int index = lbOverrideList.SelectedIndex;
            if (index != -1) lbOverrideList.Items.RemoveAt(index);
        }

        private void bUp_Click(object sender, EventArgs e) {
            int index = lbOverrideList.SelectedIndex;
            if (index > 0) {
                string s = (string)lbOverrideList.Items[index];
                lbOverrideList.Items[index--] = lbOverrideList.Items[index];
                lbOverrideList.Items[index] = s;
                lbOverrideList.SelectedIndex--;
            }
        }

        private void bDown_Click(object sender, EventArgs e) {
            int index = lbOverrideList.SelectedIndex;
            if (index != -1 && index != lbOverrideList.Items.Count - 1) {
                string s = (string)lbOverrideList.Items[index];
                lbOverrideList.Items[index++] = lbOverrideList.Items[index];
                lbOverrideList.Items[index] = s;
                lbOverrideList.SelectedIndex++;
            }
        }

        private void bSave_Click(object sender, EventArgs e) {
            if (lbStaticOverrideList != null) {
                lbStaticOverrideList.Items.Clear();
                lbStaticOverrideList.Items.AddRange(lbOverrideList.Items);
                if (lStaticOverrideList != null) lStaticOverrideList.Visible = (lbStaticOverrideList.Items.Count == 0);
            }
            Close();
        }

        private void bAdd_Click(object sender, EventArgs e) {
            if (openStaticListDialog.ShowDialog() != DialogResult.OK) return;
            lbOverrideList.Items.AddRange(openStaticListDialog.FileNames);
        }

    }
}
