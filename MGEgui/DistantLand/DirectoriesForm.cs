using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Globalization;

namespace MGEgui.DistantLand {

    public partial class DirectoriesForm : Form {

        private List<string> dirs;
        private string datafiles;

        public DirectoriesForm(string datafiles, List<string> dirs) {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            Statics.Localizations.ApplyDialogs(this, new string[] { "folderAdd" });

            this.folderAdd.SelectedPath = Statics.runDir + @"\Data Files";
            this.datafiles = datafiles;
            this.dirs = dirs;
            while (dirs.IndexOf(datafiles) != -1) {
                dirs.Remove(datafiles);
            }
            lbDirectories.Items.AddRange(dirs.ToArray());
        }

        private void bClear_Click(object sender, EventArgs e) {
            lbDirectories.Items.Clear();
        }

        private void bAdd_Click(object sender, EventArgs e) {
            if (folderAdd.ShowDialog() != DialogResult.OK) {
                return;
            }
            string s = folderAdd.SelectedPath;
            if (string.Equals(s, datafiles, StringComparison.OrdinalIgnoreCase)) {
                return;
            }
            foreach (string d in lbDirectories.Items) {
                if (string.Equals(s, d, StringComparison.OrdinalIgnoreCase)) {
                    return;
                }
            }
            lbDirectories.Items.Add(folderAdd.SelectedPath);
        }

        private void bRemove_Click(object sender, EventArgs e) {
            int index = lbDirectories.SelectedIndex;
            if (index != -1) {
                lbDirectories.Items.RemoveAt(index);
            }
        }

        private void bSave_Click(object sender, EventArgs e) {
            dirs.Clear();
            foreach (string s in lbDirectories.Items) {
                dirs.Add(s);
            }
            Close();
        }

    }

}
