using System;
using System.IO;
using System.Windows.Forms;

namespace MGEgui.DistantLand {
    partial class OverrideListForm : Form {
        private ListBox lbParentStatOverrideList;
        private Label lParentStatOverrideList;

        public OverrideListForm(ListBox lbList, Label lList) {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            Statics.Localizations.ApplyDialogs(this, new string[] { "openStaticListDialog" });

            this.openStaticListDialog.InitialDirectory = Path.Combine(Statics.runDir, Statics.fn_dlOverridesPath);
            lParentStatOverrideList = lList;
            lbParentStatOverrideList = lbList;
            if (lbList != null) {
                lbOverrideList.Items.AddRange(lbList.Items);
            }
        }

        private void bClear_Click(object sender, EventArgs e) {
            lbOverrideList.Items.Clear();
        }

        private void bRemove_Click(object sender, EventArgs e) {
            int index = lbOverrideList.SelectedIndex;
            if (index != -1) {
                lbOverrideList.Items.RemoveAt(index);
            }
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
            if (lbParentStatOverrideList != null) {
                lbParentStatOverrideList.Items.Clear();
                lbParentStatOverrideList.Items.AddRange(lbOverrideList.Items);
                if (lParentStatOverrideList != null) {
                    lParentStatOverrideList.Visible = (lbOverrideList.Items.Count == 0);
                }
            }
            Close();
        }

        private void bAdd_Click(object sender, EventArgs e) {
            if (openStaticListDialog.ShowDialog() != DialogResult.OK) {
                return;
            }
            foreach (string overrideFile in openStaticListDialog.FileNames) {
                lbOverrideList.Items.Add(new DistantLandForm.OverrideListItem(overrideFile));
            }
        }

    }
}
