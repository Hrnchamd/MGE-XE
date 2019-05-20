using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MGEgui.DistantLand {

    public partial class RunSetupForm : Form {

        private Dictionary<string, bool> flags;

        public RunSetupForm(Dictionary<string, bool> flags) {
            InitializeComponent();
            Statics.Localizations.Apply(this);

            this.HelpButtonClicked += new CancelEventHandler(RunSetupForm_HelpButtonClicked);
            this.flags = flags;
            cbTex.Enabled = flags["EnaLandTex"];
            cbMesh.Enabled = flags["EnaLandMesh"];
            cbMeshAuto.Enabled = flags["EnaLandAuto"];
            cbStat.Enabled = flags["EnaStatics"];
            cbTex.Checked = flags["ChkLandTex"];
            cbMesh.Checked = flags["ChkLandMesh"];
            cbMeshAuto.Checked = flags["ChkLandAuto"];
            cbStat.Checked = flags["ChkStatics"];
            flags["RunSetup"] = false;
            flags["AutoRun"] = false;
        }

        private void cbMesh_CheckedChanged(object sender, EventArgs e) {
            if (cbMesh.Checked == false) {
                cbMeshAuto.Enabled = false;
            } else {
                cbMeshAuto.Enabled = flags["EnaLandAuto"];
            }
        }

        private void setChecked() {
            flags["ChkLandTex"] = cbTex.Checked;
            flags["ChkLandMesh"] = cbMesh.Checked;
            flags["ChkLandAuto"] = cbMeshAuto.Checked;
            flags["ChkStatics"] = cbStat.Checked;
            flags["Debug"] = cbDebug.Checked;
        }

        private void bAutoSetup_click(object sender, EventArgs e) {
            flags["ChkLandTex"] = true;
            flags["ChkLandMesh"] = true;
            flags["ChkLandAuto"] = true;
            flags["ChkStatics"] = true;
            flags["Debug"] = cbDebug.Checked;

            flags["RunSetup"] = true;
            flags["AutoRun"] = true;
            Close();
        }

        private void bRun_Click(object sender, EventArgs e) {
            setChecked();
            flags["RunSetup"] = true;
            flags["AutoRun"] = true;
            Close();
        }

        private void bSetup_Click(object sender, EventArgs e) {
            setChecked();
            flags["RunSetup"] = true;
            Close();
        }

        private void RunSetupForm_HelpButtonClicked(object sender, CancelEventArgs e) {
            cbDebug.Visible = !cbDebug.Visible;
            e.Cancel = true;
        }

    }

}
