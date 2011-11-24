using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MGEgui {
    
    public partial class DLOptionsForm : Form {

        private Dictionary<string, bool> options;

        private const string tipResetSettings = "Resets MGE settings back to defaults.";
        private static Dictionary<string, string> tips = new Dictionary<string, string>() {
            {"DLNotInt", "Disables Distant Land feature in interiors and interiors behaving like exterior.\nChecking this will cause interior water to use non pixel shaded texture,\nand disable extended view distance for interiors with generated Distant Statics."},
            {"DLInitOff", "Disables Distant Land at game startup.\nDistant Land can be reenabled in game by binding 'Toggle distant land' macro and using it in game,\nor by a script that enables Distant Land at certain point of game."},
            {"DLMWBlendOff", "Disables Morrowind/MGE Distant Land and Statics blending at game startup.\nBlending can be reenabled in game by binding 'Toggle MW/MGE blending' macro and using it in game."},
        };
        
        public DLOptionsForm(Dictionary<string, bool> options) {
            InitializeComponent();
            this.options = options;
            foreach (Control ctl in Controls) {
                if (ctl.Name.Substring(0, 2) != "cb") continue;
                string s = ctl.Name.Substring(2);
                if (tips.ContainsKey(s)) toolTip.SetToolTip(ctl, tips[s]);
                if (options != null && options.ContainsKey(s)) ((CheckBox)ctl).Checked = options[s];
            }
        }

        private void cb_CheckedChanged(object sender, EventArgs e) {
            CheckBox cb = (CheckBox)sender;
            string s = cb.Name.Substring(2);
            if (options != null && options.ContainsKey(s)) options[s] = cb.Checked;
        }

        private void DLOptionsForm_FormClosed (object sender, FormClosedEventArgs e) {
            bool status = !options ["DLNotInt"] && !Statics.mf.cbDLAutoDist.Checked && Statics.mf.cbDLDistantLand.Checked;
            Statics.mf.lDLFogI.Enabled = status;
            Statics.mf.udDLFogIStart.Enabled = status;
            Statics.mf.udDLFogIEnd.Enabled = status;
        }

    }

}
