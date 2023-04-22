﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using MGEgui.INI;

namespace MGEgui {

    public partial class DLWeatherForm : Form {

        private Dictionary<string, float> defaults;

        #region tooltip_messages
        public Dictionary<string, string[]> tooltip_messages = new Dictionary<string, string[]> {
            { "Save", new string [] { "bSave" } },
            { "Cancel", new string [] { "bCancel" } },
            { "Reset", new string [] { "bReset" } },
            { "Wind", new string [] { "gbWind" } },
            { "FogDay", new string [] { "gbFogDay" } },
            { "FogOffs", new string [] { "gbFogOffsDay" } },
        };
        #endregion

        public DLWeatherForm() {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            LocalizeDefaultButtons(Statics.strings["Default"]);
            defaults = new Dictionary<string, float>();
            LoadSettings();
        }

        private void LocalizeDefaultButtons(string s) {
            foreach (Control c in gbWind.Controls) {
                if (c is Button) {
                    c.Text = s;
                }
            }
            foreach (Control c in gbFogDay.Controls) {
                if (c is Button) {
                    c.Text = s;
                }
            }
            foreach (Control c in gbFogOffsDay.Controls) {
                if (c is Button) {
                    c.Text = s;
                }
            }
        }

        private const string iniDLWeather = "Distant Land Weather";
        // wind
        private static INIFile.INIVariableDef iniClearWind = new INIFile.INIVariableDef("ClearWind", iniDLWeather, "Clear Wind Ratio", INIFile.INIVariableType.Single, "0.1", 0, 1);
        private static INIFile.INIVariableDef iniCloudyWind = new INIFile.INIVariableDef("CloudyWind", iniDLWeather, "Cloudy Wind Ratio", INIFile.INIVariableType.Single, "0.2", 0, 1);
        private static INIFile.INIVariableDef iniFoggyWind = new INIFile.INIVariableDef("FoggyWind", iniDLWeather, "Foggy Wind Ratio", INIFile.INIVariableType.Single, "0", 0, 1);
        private static INIFile.INIVariableDef iniOvercastWind = new INIFile.INIVariableDef("OvercastWind", iniDLWeather, "Overcast Wind Ratio", INIFile.INIVariableType.Single, "0.2", 0, 1);
        private static INIFile.INIVariableDef iniRainWind = new INIFile.INIVariableDef("RainWind", iniDLWeather, "Rain Wind Ratio", INIFile.INIVariableType.Single, "0.3", 0, 1);
        private static INIFile.INIVariableDef iniThunderWind = new INIFile.INIVariableDef("ThunderWind", iniDLWeather, "Thunderstorm Wind Ratio", INIFile.INIVariableType.Single, "0.5", 0, 1);
        private static INIFile.INIVariableDef iniAshWind = new INIFile.INIVariableDef("AshWind", iniDLWeather, "Ashstorm Wind Ratio", INIFile.INIVariableType.Single, "0.8", 0, 1);
        private static INIFile.INIVariableDef iniBlightWind = new INIFile.INIVariableDef("BlightWind", iniDLWeather, "Blight Wind Ratio", INIFile.INIVariableType.Single, "0.9", 0, 1);
        private static INIFile.INIVariableDef iniSnowWind = new INIFile.INIVariableDef("SnowWind", iniDLWeather, "Snow Wind Ratio", INIFile.INIVariableType.Single, "0", 0, 1);
        private static INIFile.INIVariableDef iniBlizzardWind = new INIFile.INIVariableDef("BlizzardWind", iniDLWeather, "Blizzard Wind Ratio", INIFile.INIVariableType.Single, "0.9", 0, 1);
        // day fog
        private static INIFile.INIVariableDef iniClearFogDay = new INIFile.INIVariableDef("ClearFogDay", iniDLWeather, "Clear Fog Ratio", INIFile.INIVariableType.Single, "1", 0.001, 2);
        private static INIFile.INIVariableDef iniCloudyFogDay = new INIFile.INIVariableDef("CloudyFogDay", iniDLWeather, "Cloudy Fog Ratio", INIFile.INIVariableType.Single, "0.9", 0.001, 2);
        private static INIFile.INIVariableDef iniFoggyFogDay = new INIFile.INIVariableDef("FoggyFogDay", iniDLWeather, "Foggy Fog Ratio", INIFile.INIVariableType.Single, "0.2", 0.001, 2);
        private static INIFile.INIVariableDef iniOvercastFogDay = new INIFile.INIVariableDef("OvercastFogDay", iniDLWeather, "Overcast Fog Ratio", INIFile.INIVariableType.Single, "0.7", 0.001, 2);
        private static INIFile.INIVariableDef iniRainFogDay = new INIFile.INIVariableDef("RainFogDay", iniDLWeather, "Rain Fog Ratio", INIFile.INIVariableType.Single, "0.5", 0.001, 2);
        private static INIFile.INIVariableDef iniThunderFogDay = new INIFile.INIVariableDef("ThunderFogDay", iniDLWeather, "Thunderstorm Fog Ratio", INIFile.INIVariableType.Single, "0.5", 0.001, 2);
        private static INIFile.INIVariableDef iniAshFogDay = new INIFile.INIVariableDef("AshFogDay", iniDLWeather, "Ashstorm Fog Ratio", INIFile.INIVariableType.Single, "0.25", 0.001, 2);
        private static INIFile.INIVariableDef iniBlightFogDay = new INIFile.INIVariableDef("BlightFogDay", iniDLWeather, "Blight Fog Ratio", INIFile.INIVariableType.Single, "0.25", 0.001, 2);
        private static INIFile.INIVariableDef iniSnowFogDay = new INIFile.INIVariableDef("SnowFogDay", iniDLWeather, "Snow Fog Ratio", INIFile.INIVariableType.Single, "0.5", 0.001, 2);
        private static INIFile.INIVariableDef iniBlizzardFogDay = new INIFile.INIVariableDef("BlizzardFogDay", iniDLWeather, "Blizzard Fog Ratio", INIFile.INIVariableType.Single, "0.16", 0.001, 2);
        // day fog offset
        private static INIFile.INIVariableDef iniClearFogOffsDay = new INIFile.INIVariableDef("ClearFogOffsDay", iniDLWeather, "Clear Fog Offset", INIFile.INIVariableType.Single, "0", 0, 200);
        private static INIFile.INIVariableDef iniCloudyFogOffsDay = new INIFile.INIVariableDef("CloudyFogOffsDay", iniDLWeather, "Cloudy Fog Offset", INIFile.INIVariableType.Single, "0", 0, 200);
        private static INIFile.INIVariableDef iniFoggyFogOffsDay = new INIFile.INIVariableDef("FoggyFogOffsDay", iniDLWeather, "Foggy Fog Offset", INIFile.INIVariableType.Single, "30", 0, 200);
        private static INIFile.INIVariableDef iniOvercastFogOffsDay = new INIFile.INIVariableDef("OvercastFogOffsDay", iniDLWeather, "Overcast Fog Offset", INIFile.INIVariableType.Single, "0", 0, 200);
        private static INIFile.INIVariableDef iniRainFogOffsDay = new INIFile.INIVariableDef("RainFogOffsDay", iniDLWeather, "Rain Fog Offset", INIFile.INIVariableType.Single, "10", 0, 200);
        private static INIFile.INIVariableDef iniThunderFogOffsDay = new INIFile.INIVariableDef("ThunderFogOffsDay", iniDLWeather, "Thunderstorm Fog Offset", INIFile.INIVariableType.Single, "20", 0, 200);
        private static INIFile.INIVariableDef iniAshFogOffsDay = new INIFile.INIVariableDef("AshFogOffsDay", iniDLWeather, "Ashstorm Fog Offset", INIFile.INIVariableType.Single, "45", 0, 200);
        private static INIFile.INIVariableDef iniBlightFogOffsDay = new INIFile.INIVariableDef("BlightFogOffsDay", iniDLWeather, "Blight Fog Offset", INIFile.INIVariableType.Single, "50", 0, 200);
        private static INIFile.INIVariableDef iniSnowFogOffsDay = new INIFile.INIVariableDef("SnowFogOffsDay", iniDLWeather, "Snow Fog Offset", INIFile.INIVariableType.Single, "40", 0, 90);
        private static INIFile.INIVariableDef iniBlizzardFogOffsDay = new INIFile.INIVariableDef("BlizzardFogOffsDay", iniDLWeather, "Blizzard Fog Offset", INIFile.INIVariableType.Single, "100", 0, 200);

        public static INIFile.INIVariableDef[] iniWeatherSettings = {
            INIFile.iniDefEmpty,
            iniClearWind, iniClearFogDay, iniClearFogOffsDay,
            iniCloudyWind, iniCloudyFogDay, iniCloudyFogOffsDay,
            iniFoggyWind, iniFoggyFogDay, iniFoggyFogOffsDay,
            iniOvercastWind, iniOvercastFogDay, iniOvercastFogOffsDay,
            iniRainWind, iniRainFogDay, iniRainFogOffsDay,
            iniThunderWind, iniThunderFogDay, iniThunderFogOffsDay,
            iniAshWind, iniAshFogDay, iniAshFogOffsDay,
            iniBlightWind, iniBlightFogDay, iniBlightFogOffsDay,
            iniSnowWind, iniSnowFogDay, iniSnowFogOffsDay,
            iniBlizzardWind, iniBlizzardFogDay, iniBlizzardFogOffsDay
        };

        private void LoadSettings() {
            INIFile iniFile = new INIFile(Statics.fn_inifile, iniWeatherSettings);

            // Load settings into controls
            foreach (Control ctl in this.Controls["gbWind"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                ud.Value = (decimal)iniFile.getKeyValue(ud.Name.Substring(2));
            }
            foreach (Control ctl in this.Controls["gbFogDay"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                ud.Value = (decimal)iniFile.getKeyValue(ud.Name.Substring(2));
            }
            foreach (Control ctl in this.Controls["gbFogOffsDay"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                ud.Value = (decimal)iniFile.getKeyValue(ud.Name.Substring(2));
            }
            
            // Load settings for default buttons
            iniFile = new INIFile(Statics.fn_nul, iniWeatherSettings);
            foreach (Control ctl in this.Controls["gbWind"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                string s = ud.Name.Substring(2);
                defaults.Add(s, (float)iniFile.getKeyValue(s));
            }
            foreach (Control ctl in this.Controls["gbFogDay"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                string s = ud.Name.Substring(2);
                defaults.Add(s, (float)iniFile.getKeyValue(s));
            }
            foreach (Control ctl in this.Controls["gbFogOffsDay"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                string s = ud.Name.Substring(2);
                defaults.Add(s, (float)iniFile.getKeyValue(s));
            }
        }

        private decimal udValue(NumericUpDown target, float value) {
            return ((decimal)value < target.Minimum ? target.Minimum : ((decimal)value > target.Maximum ? target.Maximum : (decimal)value));
        }

        private void bReset_Click(object sender, EventArgs e) {
            foreach (Control ctl in this.Controls["gbWind"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                string s = ud.Name.Substring(2);
                if (defaults.ContainsKey(s)) {
                    ud.Value = udValue(ud, defaults[s]);
                }
            }
            foreach (Control ctl in this.Controls["gbFogDay"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                string s = ud.Name.Substring(2);
                if (defaults.ContainsKey(s)) {
                    ud.Value = udValue(ud, defaults[s]);
                }
            }
            foreach (Control ctl in this.Controls["gbFogOffsDay"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                string s = ud.Name.Substring(2);
                if (defaults.ContainsKey(s)) {
                    ud.Value = udValue(ud, defaults[s]);
                }
            }
        }

        private void bDefault_Click(object sender, EventArgs e) {
            Control ctl = (Control)sender;
            string s = ctl.Name.Substring(1);
            if (defaults.ContainsKey(s)) {
                NumericUpDown ud = (NumericUpDown)ctl.Parent.Controls["ud" + s];
                if (defaults.ContainsKey(s)) {
                    ud.Value = udValue(ud, defaults[s]);
                }
            }
        }

        private void bSave_Click(object sender, EventArgs e) {
            INIFile iniFile = new INIFile(Statics.fn_inifile, iniWeatherSettings, true);
            iniFile.initialize();
            
            foreach (Control ctl in this.Controls["gbWind"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                iniFile.setKey(ud.Name.Substring(2), (double)ud.Value);
            }
            foreach (Control ctl in this.Controls["gbFogDay"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                iniFile.setKey(ud.Name.Substring(2), (double)ud.Value);
            }
            foreach (Control ctl in this.Controls["gbFogOffsDay"].Controls) {
                if (ctl.Name.Substring(0, 2) != "ud") {
                    continue;
                }
                NumericUpDown ud = (NumericUpDown)ctl;
                iniFile.setKey(ud.Name.Substring(2), (double)ud.Value);
            }
            
            iniFile.save();
            Close();
        }

    }

}
