using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using MGEgui.INI;

namespace MGEgui {

    public partial class LightingForm : Form {

        #region tooltip_messages
        public Dictionary<string, string[]> tooltip_messages = new Dictionary<string, string[]> {
            { "Save", new string [] { "bSave" } },
            { "Cancel", new string [] { "bCancel" } },
            { "Reset", new string [] { "bReset" } },
            { "Sun", new string [] { "gbSun" } },
            { "Ambient", new string [] { "gbAmbient" } },
        };
        #endregion

        public LightingForm() {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            LoadSettings();
        }
        
        private const string iniPPLighting = "Per Pixel Lighting";
        // Sun multiplier
        private static INIFile.INIVariableDef iniClearSun = new INIFile.INIVariableDef("ClearSun", iniPPLighting, "Clear Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniCloudySun = new INIFile.INIVariableDef("CloudySun", iniPPLighting, "Cloudy Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniFoggySun = new INIFile.INIVariableDef("FoggySun", iniPPLighting, "Foggy Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniOvercastSun = new INIFile.INIVariableDef("OvercastSun", iniPPLighting, "Overcast Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniRainSun = new INIFile.INIVariableDef("RainSun", iniPPLighting, "Rain Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniThunderSun = new INIFile.INIVariableDef("ThunderSun", iniPPLighting, "Thunderstorm Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniAshSun = new INIFile.INIVariableDef("AshSun", iniPPLighting, "Ashstorm Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniBlightSun = new INIFile.INIVariableDef("BlightSun", iniPPLighting, "Blight Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniSnowSun = new INIFile.INIVariableDef("SnowSun", iniPPLighting, "Snow Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniBlizzardSun = new INIFile.INIVariableDef("BlizzardSun", iniPPLighting, "Blizzard Sun Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        // Ambient multiplier
        private static INIFile.INIVariableDef iniClearAmb = new INIFile.INIVariableDef("ClearAmb", iniPPLighting, "Clear Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniCloudyAmb = new INIFile.INIVariableDef("CloudyAmb", iniPPLighting, "Cloudy Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniFoggyAmb = new INIFile.INIVariableDef("FoggyAmb", iniPPLighting, "Foggy Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniOvercastAmb = new INIFile.INIVariableDef("OvercastAmb", iniPPLighting, "Overcast Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniRainAmb = new INIFile.INIVariableDef("RainAmb", iniPPLighting, "Rain Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniThunderAmb = new INIFile.INIVariableDef("ThunderAmb", iniPPLighting, "Thunderstorm Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniAshAmb = new INIFile.INIVariableDef("AshAmb", iniPPLighting, "Ashstorm Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniBlightAmb = new INIFile.INIVariableDef("BlightAmb", iniPPLighting, "Blight Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniSnowAmb = new INIFile.INIVariableDef("SnowAmb", iniPPLighting, "Snow Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);
        private static INIFile.INIVariableDef iniBlizzardAmb = new INIFile.INIVariableDef("BlizzardAmb", iniPPLighting, "Blizzard Ambient Brightness", INIFile.INIVariableType.Single, "1", 0, 10);

        public static INIFile.INIVariableDef[] iniWeatherSettings = {
            INIFile.iniDefEmpty,
            iniClearSun, iniClearAmb,
            iniCloudySun, iniCloudyAmb,
            iniFoggySun, iniFoggyAmb,
            iniOvercastSun, iniOvercastAmb,
            iniRainSun, iniRainAmb,
            iniThunderSun, iniThunderAmb,
            iniAshSun, iniAshAmb,
            iniBlightSun, iniBlightAmb,
            iniSnowSun, iniSnowAmb,
            iniBlizzardSun, iniBlizzardAmb
        };

        private void LoadSettings() {
            INIFile iniFile = new INIFile(Statics.fn_inifile, iniWeatherSettings);
            foreach (Control ctl in this.Controls["gbSun"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") continue;
                NumericUpDown ud = (NumericUpDown)ctl;
                ud.Value = (decimal)iniFile.getKeyValue(ud.Name.Substring(2));
            }
            foreach (Control ctl in this.Controls["gbAmbient"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") continue;
                NumericUpDown ud = (NumericUpDown)ctl;
                ud.Value = (decimal)iniFile.getKeyValue(ud.Name.Substring(2));
            }
        }

        private decimal udValue(NumericUpDown target, float value) {
            return ((decimal)value < target.Minimum ? target.Minimum : ((decimal)value > target.Maximum ? target.Maximum : (decimal)value));
        }

        private void bReset_Click(object sender, EventArgs e) {
            foreach (Control ctl in this.Controls["gbSun"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") continue;
                NumericUpDown ud = (NumericUpDown)ctl;
                ud.Value = 1.0M;
            }
            foreach (Control ctl in this.Controls["gbAmbient"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") continue;
                NumericUpDown ud = (NumericUpDown)ctl;
                ud.Value = 1.0M;
            }
        }
    
        private void bSave_Click(object sender, EventArgs e) {
            INIFile iniFile = new INIFile(Statics.fn_inifile, iniWeatherSettings, true);
            iniFile.initialize();
            
            foreach (Control ctl in this.Controls["gbSun"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") continue;
                NumericUpDown ud = (NumericUpDown)ctl;
                iniFile.setKey(ud.Name.Substring(2), (double)ud.Value);
            }
            foreach (Control ctl in this.Controls["gbAmbient"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") continue;
                NumericUpDown ud = (NumericUpDown)ctl;
                iniFile.setKey(ud.Name.Substring(2), (double)ud.Value);
            }

            iniFile.save();
            Close();
        }

    }

}
