using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;
using System.Linq;
using MGEgui.INI;

namespace MGEgui {
    public class ShaderActive : Form {
        private Button bMoveUp;
        private ListBox lbSelected;
        private ListBox lbAvailable;
        private Button bMoveDown;
        private Button bSave;
        private Button bClear;
        private Button bCancel;

        private bool setup = false;
            
        private static List<string> effectHDR = new List<string> { "Eye Adaptation (HDR)" };
        private static List<string> effectSSAO = new List<string> { "SSAO Fast", "SSAO HQ" };
        private static List<string> effectBloom = new List<string> { "Bloom Fine", "Bloom Soft" };
        private static List<string> effectSunshafts = new List<string> { "Sunshafts" };
        private static List<string> effectDoF = new List<string> { "Depth of Field" };
        private static List<string> effectWaterSunshafts = new List<string> { "Underwater Effects" };
        private static List<string> effectInteriorCaustics = new List<string> { "Underwater Interior Effects" };
        
        private static string[] presetLowest = new [] { effectBloom[0] };
        private static string[] presetLow = new [] { effectSunshafts[0], effectBloom[0], effectHDR[0] };
        private static string[] presetMed = new [] { effectSSAO[0], effectSunshafts[0], effectBloom[0], effectHDR[0] };
        private static string[] presetHigh = new [] { effectSSAO[0], effectInteriorCaustics[0], effectWaterSunshafts[0], effectSunshafts[0], effectBloom[1], effectHDR[0] };
        private static string[] presetUltra = new [] { effectSSAO[1], effectInteriorCaustics[0], effectWaterSunshafts[0], effectSunshafts[0], effectBloom[1], effectHDR[0] };
        
        public static string iniShaderChain = "Shader Chain";
        public static INIFile.INIVariableDef iniHDRTime = new INIFile.INIVariableDef("HDRTime", "Misc", "HDR Reaction Time", INIFile.INIVariableType.Single, "2", 0.01, 30, 2);
        public static INIFile.INIVariableDef[] iniShaderDefault = {
            INIFile.iniDefEmpty, iniHDRTime
        };
        
        #region tooltip_messages
        public Dictionary<string, string[]> tooltip_messages = new Dictionary<string, string[]> {
            { "HDR", new string [] { "cmbHDR", "lHDR" } },
            { "HDRTime", new string [] { "udHDRTime", "lHDRTime" } },
            { "SSAO", new string [] { "cmbSSAO", "lSSAO" } },
            { "Bloom", new string [] { "cmbBloom", "lBloom" } },
            { "Sunshafts", new string [] { "cmbSunshafts", "lSunshafts" } },
            { "DoF", new string [] { "cmbDoF", "lDoF" } },
            { "WaterSunshafts", new string [] { "cmbWaterSunshafts", "lWaterSunshafts" } },
            { "InteriorCaustics", new string [] { "cmbInteriorCaustics", "lInteriorCaustics" } },
        };
        #endregion

        #region FormDesignerGunk
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components=null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if(disposing&&(components!=null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            this.bMoveUp = new System.Windows.Forms.Button();
            this.lbSelected = new System.Windows.Forms.ListBox();
            this.lbAvailable = new System.Windows.Forms.ListBox();
            this.bMoveDown = new System.Windows.Forms.Button();
            this.bSave = new System.Windows.Forms.Button();
            this.bClear = new System.Windows.Forms.Button();
            this.bCancel = new System.Windows.Forms.Button();
            this.lAvailableList = new System.Windows.Forms.Label();
            this.lActiveList = new System.Windows.Forms.Label();
            this.bEditor = new System.Windows.Forms.Button();
            this.lShaderUsage = new System.Windows.Forms.Label();
            this.tableLayoutPanelAdv = new System.Windows.Forms.TableLayoutPanel();
            this.panelActions = new System.Windows.Forms.Panel();
            this.panelActiveListActions = new System.Windows.Forms.Panel();
            this.cmbPresets = new System.Windows.Forms.ComboBox();
            this.lShaderOptions = new System.Windows.Forms.Label();
            this.lPresets = new System.Windows.Forms.Label();
            this.cmbHDR = new System.Windows.Forms.ComboBox();
            this.cmbSSAO = new System.Windows.Forms.ComboBox();
            this.cmbBloom = new System.Windows.Forms.ComboBox();
            this.cmbSunshafts = new System.Windows.Forms.ComboBox();
            this.cmbDoF = new System.Windows.Forms.ComboBox();
            this.cmbWaterSunshafts = new System.Windows.Forms.ComboBox();
            this.lSSAO = new System.Windows.Forms.Label();
            this.lBloom = new System.Windows.Forms.Label();
            this.lDoF = new System.Windows.Forms.Label();
            this.lWaterSunshafts = new System.Windows.Forms.Label();
            this.lSunshafts = new System.Windows.Forms.Label();
            this.lHDR = new System.Windows.Forms.Label();
            this.cmbInteriorCaustics = new System.Windows.Forms.ComboBox();
            this.lInteriorCaustics = new System.Windows.Forms.Label();
            this.bAdvancedMode = new System.Windows.Forms.Button();
            this.udHDRTime = new System.Windows.Forms.NumericUpDown();
            this.lHDRTime = new System.Windows.Forms.Label();
            this.lHDRTime2 = new System.Windows.Forms.Label();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.tableRightAlign1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableRightAlign2 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanelAdv.SuspendLayout();
            this.panelActions.SuspendLayout();
            this.panelActiveListActions.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udHDRTime)).BeginInit();
            this.tableRightAlign1.SuspendLayout();
            this.tableRightAlign2.SuspendLayout();
            this.SuspendLayout();
            // 
            // bMoveUp
            // 
            this.bMoveUp.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.bMoveUp.Location = new System.Drawing.Point(0, 9);
            this.bMoveUp.Name = "bMoveUp";
            this.bMoveUp.Size = new System.Drawing.Size(79, 23);
            this.bMoveUp.TabIndex = 0;
            this.bMoveUp.Text = "Move up";
            this.bMoveUp.Click += new System.EventHandler(this.bMoveUp_Click);
            // 
            // lbSelected
            // 
            this.lbSelected.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lbSelected.ItemHeight = 15;
            this.lbSelected.Location = new System.Drawing.Point(9, 244);
            this.lbSelected.Name = "lbSelected";
            this.lbSelected.Size = new System.Drawing.Size(237, 124);
            this.lbSelected.TabIndex = 3;
            this.lbSelected.DoubleClick += new System.EventHandler(this.lbSelected_DoubleClick);
            // 
            // lbAvailable
            // 
            this.lbAvailable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lbAvailable.ItemHeight = 15;
            this.lbAvailable.Location = new System.Drawing.Point(9, 26);
            this.lbAvailable.Name = "lbAvailable";
            this.lbAvailable.Size = new System.Drawing.Size(237, 189);
            this.lbAvailable.TabIndex = 1;
            this.lbAvailable.DoubleClick += new System.EventHandler(this.lbAvailable_DoubleClick);
            // 
            // bMoveDown
            // 
            this.bMoveDown.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.bMoveDown.Location = new System.Drawing.Point(0, 38);
            this.bMoveDown.Name = "bMoveDown";
            this.bMoveDown.Size = new System.Drawing.Size(79, 23);
            this.bMoveDown.TabIndex = 1;
            this.bMoveDown.Text = "Move down";
            this.bMoveDown.Click += new System.EventHandler(this.bMoveDown_Click);
            // 
            // bSave
            // 
            this.bSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bSave.Location = new System.Drawing.Point(92, 376);
            this.bSave.Name = "bSave";
            this.bSave.Size = new System.Drawing.Size(90, 23);
            this.bSave.TabIndex = 21;
            this.bSave.Text = "Save";
            this.bSave.Click += new System.EventHandler(this.bSave_Click);
            // 
            // bClear
            // 
            this.bClear.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.bClear.Location = new System.Drawing.Point(0, 85);
            this.bClear.Name = "bClear";
            this.bClear.Size = new System.Drawing.Size(79, 23);
            this.bClear.TabIndex = 2;
            this.bClear.Text = "Clear";
            this.bClear.Click += new System.EventHandler(this.bClear_Click);
            // 
            // bCancel
            // 
            this.bCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.bCancel.Location = new System.Drawing.Point(188, 376);
            this.bCancel.Name = "bCancel";
            this.bCancel.Size = new System.Drawing.Size(90, 23);
            this.bCancel.TabIndex = 22;
            this.bCancel.Text = "Cancel";
            this.bCancel.Click += new System.EventHandler(this.bCancel_Click);
            // 
            // lAvailableList
            // 
            this.lAvailableList.AutoSize = true;
            this.lAvailableList.Location = new System.Drawing.Point(9, 8);
            this.lAvailableList.Name = "lAvailableList";
            this.lAvailableList.Size = new System.Drawing.Size(98, 15);
            this.lAvailableList.TabIndex = 0;
            this.lAvailableList.Text = "Available shaders";
            // 
            // lActiveList
            // 
            this.lActiveList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.lActiveList.AutoSize = true;
            this.lActiveList.Location = new System.Drawing.Point(9, 218);
            this.lActiveList.Name = "lActiveList";
            this.lActiveList.Padding = new System.Windows.Forms.Padding(0, 8, 0, 0);
            this.lActiveList.Size = new System.Drawing.Size(237, 23);
            this.lActiveList.TabIndex = 2;
            this.lActiveList.Text = "Active Shaders";
            // 
            // bEditor
            // 
            this.bEditor.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.bEditor.Location = new System.Drawing.Point(0, 8);
            this.bEditor.Name = "bEditor";
            this.bEditor.Size = new System.Drawing.Size(79, 23);
            this.bEditor.TabIndex = 0;
            this.bEditor.Text = "Editor";
            this.bEditor.UseVisualStyleBackColor = true;
            this.bEditor.Click += new System.EventHandler(this.bEditor_Click);
            // 
            // lShaderUsage
            // 
            this.lShaderUsage.AutoSize = true;
            this.tableLayoutPanelAdv.SetColumnSpan(this.lShaderUsage, 2);
            this.lShaderUsage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lShaderUsage.Location = new System.Drawing.Point(9, 371);
            this.lShaderUsage.Name = "lShaderUsage";
            this.lShaderUsage.Padding = new System.Windows.Forms.Padding(0, 8, 0, 8);
            this.lShaderUsage.Size = new System.Drawing.Size(322, 31);
            this.lShaderUsage.TabIndex = 10;
            this.lShaderUsage.Text = "Double-click to add or remove shaders from the active list.\r\n";
            // 
            // tableLayoutPanelAdv
            // 
            this.tableLayoutPanelAdv.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                                    | System.Windows.Forms.AnchorStyles.Left)));
            this.tableLayoutPanelAdv.ColumnCount = 2;
            this.tableLayoutPanelAdv.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanelAdv.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 85F));
            this.tableLayoutPanelAdv.Controls.Add(this.lAvailableList, 0, 0);
            this.tableLayoutPanelAdv.Controls.Add(this.lShaderUsage, 0, 4);
            this.tableLayoutPanelAdv.Controls.Add(this.lbAvailable, 0, 1);
            this.tableLayoutPanelAdv.Controls.Add(this.lActiveList, 0, 2);
            this.tableLayoutPanelAdv.Controls.Add(this.lbSelected, 0, 3);
            this.tableLayoutPanelAdv.Controls.Add(this.panelActions, 1, 1);
            this.tableLayoutPanelAdv.Controls.Add(this.panelActiveListActions, 1, 3);
            this.tableLayoutPanelAdv.Location = new System.Drawing.Point(304, 0);
            this.tableLayoutPanelAdv.Name = "tableLayoutPanelAdv";
            this.tableLayoutPanelAdv.Padding = new System.Windows.Forms.Padding(6, 8, 6, 8);
            this.tableLayoutPanelAdv.RowCount = 5;
            this.tableLayoutPanelAdv.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanelAdv.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 60F));
            this.tableLayoutPanelAdv.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanelAdv.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutPanelAdv.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanelAdv.Size = new System.Drawing.Size(340, 410);
            this.tableLayoutPanelAdv.TabIndex = 23;
            // 
            // panelActions
            // 
            this.panelActions.AutoSize = true;
            this.panelActions.Controls.Add(this.bEditor);
            this.panelActions.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelActions.Location = new System.Drawing.Point(252, 26);
            this.panelActions.Name = "panelActions";
            this.panelActions.Size = new System.Drawing.Size(79, 189);
            this.panelActions.TabIndex = 11;
            // 
            // panelActiveListActions
            // 
            this.panelActiveListActions.AutoSize = true;
            this.panelActiveListActions.Controls.Add(this.bMoveUp);
            this.panelActiveListActions.Controls.Add(this.bMoveDown);
            this.panelActiveListActions.Controls.Add(this.bClear);
            this.panelActiveListActions.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelActiveListActions.Location = new System.Drawing.Point(252, 244);
            this.panelActiveListActions.Name = "panelActiveListActions";
            this.panelActiveListActions.Size = new System.Drawing.Size(79, 124);
            this.panelActiveListActions.TabIndex = 12;
            // 
            // cmbPresets
            // 
            this.cmbPresets.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPresets.FormattingEnabled = true;
            this.cmbPresets.Items.AddRange(new object[] {
                                    "Lowest",
                                    "Low",
                                    "Medium",
                                    "High",
                                    "Very High",
                                    "Custom"});
            this.cmbPresets.Location = new System.Drawing.Point(118, 39);
            this.cmbPresets.Name = "cmbPresets";
            this.cmbPresets.Size = new System.Drawing.Size(125, 23);
            this.cmbPresets.TabIndex = 2;
            this.cmbPresets.SelectedIndexChanged += new System.EventHandler(this.cmbPresets_Changed);
            // 
            // lShaderOptions
            // 
            this.lShaderOptions.AutoSize = true;
            this.lShaderOptions.Location = new System.Drawing.Point(12, 8);
            this.lShaderOptions.Name = "lShaderOptions";
            this.lShaderOptions.Size = new System.Drawing.Size(86, 15);
            this.lShaderOptions.TabIndex = 0;
            this.lShaderOptions.Text = "Shader options";
            // 
            // lPresets
            // 
            this.lPresets.AutoSize = true;
            this.lPresets.Dock = System.Windows.Forms.DockStyle.Right;
            this.lPresets.Location = new System.Drawing.Point(20, 0);
            this.lPresets.Margin = new System.Windows.Forms.Padding(0);
            this.lPresets.Name = "lPresets";
            this.lPresets.Size = new System.Drawing.Size(80, 23);
            this.lPresets.TabIndex = 1;
            this.lPresets.Text = "Quality preset";
            this.lPresets.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // cmbHDR
            // 
            this.cmbHDR.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbHDR.FormattingEnabled = true;
            this.cmbHDR.Items.AddRange(new object[] {
                                    "Off",
                                    "On"});
            this.cmbHDR.Location = new System.Drawing.Point(168, 99);
            this.cmbHDR.Name = "cmbHDR";
            this.cmbHDR.Size = new System.Drawing.Size(110, 23);
            this.cmbHDR.TabIndex = 4;
            this.cmbHDR.SelectedIndexChanged += new System.EventHandler(this.onOptionUpdate);
            // 
            // cmbSSAO
            // 
            this.cmbSSAO.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbSSAO.FormattingEnabled = true;
            this.cmbSSAO.Items.AddRange(new object[] {
                                    "Off",
                                    "Medium quality",
                                    "High quality"});
            this.cmbSSAO.Location = new System.Drawing.Point(168, 152);
            this.cmbSSAO.Name = "cmbSSAO";
            this.cmbSSAO.Size = new System.Drawing.Size(110, 23);
            this.cmbSSAO.TabIndex = 9;
            this.cmbSSAO.SelectedIndexChanged += new System.EventHandler(this.onOptionUpdate);
            // 
            // cmbBloom
            // 
            this.cmbBloom.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbBloom.FormattingEnabled = true;
            this.cmbBloom.Items.AddRange(new object[] {
                                    "Off",
                                    "Fine",
                                    "Soft"});
            this.cmbBloom.Location = new System.Drawing.Point(168, 179);
            this.cmbBloom.Name = "cmbBloom";
            this.cmbBloom.Size = new System.Drawing.Size(110, 23);
            this.cmbBloom.TabIndex = 11;
            this.cmbBloom.SelectedIndexChanged += new System.EventHandler(this.onOptionUpdate);
            // 
            // cmbSunshafts
            // 
            this.cmbSunshafts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbSunshafts.FormattingEnabled = true;
            this.cmbSunshafts.Items.AddRange(new object[] {
                                    "Off",
                                    "On"});
            this.cmbSunshafts.Location = new System.Drawing.Point(168, 206);
            this.cmbSunshafts.Name = "cmbSunshafts";
            this.cmbSunshafts.Size = new System.Drawing.Size(110, 23);
            this.cmbSunshafts.TabIndex = 13;
            this.cmbSunshafts.SelectedIndexChanged += new System.EventHandler(this.onOptionUpdate);
            // 
            // cmbDoF
            // 
            this.cmbDoF.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbDoF.FormattingEnabled = true;
            this.cmbDoF.Items.AddRange(new object[] {
                                    "Off",
                                    "On"});
            this.cmbDoF.Location = new System.Drawing.Point(168, 233);
            this.cmbDoF.Name = "cmbDoF";
            this.cmbDoF.Size = new System.Drawing.Size(110, 23);
            this.cmbDoF.TabIndex = 15;
            this.cmbDoF.SelectedIndexChanged += new System.EventHandler(this.onOptionUpdate);
            // 
            // cmbWaterSunshafts
            // 
            this.cmbWaterSunshafts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbWaterSunshafts.FormattingEnabled = true;
            this.cmbWaterSunshafts.Items.AddRange(new object[] {
                                    "Off",
                                    "On"});
            this.cmbWaterSunshafts.Location = new System.Drawing.Point(168, 260);
            this.cmbWaterSunshafts.Name = "cmbWaterSunshafts";
            this.cmbWaterSunshafts.Size = new System.Drawing.Size(110, 23);
            this.cmbWaterSunshafts.TabIndex = 17;
            this.cmbWaterSunshafts.SelectedIndexChanged += new System.EventHandler(this.onOptionUpdate);
            // 
            // lSSAO
            // 
            this.lSSAO.AutoSize = true;
            this.lSSAO.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSSAO.Location = new System.Drawing.Point(114, 54);
            this.lSSAO.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lSSAO.Name = "lSSAO";
            this.lSSAO.Size = new System.Drawing.Size(36, 23);
            this.lSSAO.TabIndex = 8;
            this.lSSAO.Text = "SSAO";
            this.lSSAO.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lBloom
            // 
            this.lBloom.AutoSize = true;
            this.lBloom.Dock = System.Windows.Forms.DockStyle.Right;
            this.lBloom.Location = new System.Drawing.Point(108, 81);
            this.lBloom.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lBloom.Name = "lBloom";
            this.lBloom.Size = new System.Drawing.Size(42, 23);
            this.lBloom.TabIndex = 10;
            this.lBloom.Text = "Bloom";
            this.lBloom.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lDoF
            // 
            this.lDoF.AutoSize = true;
            this.lDoF.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDoF.Location = new System.Drawing.Point(69, 135);
            this.lDoF.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lDoF.Name = "lDoF";
            this.lDoF.Size = new System.Drawing.Size(81, 23);
            this.lDoF.TabIndex = 14;
            this.lDoF.Text = "Depth of Field";
            this.lDoF.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lWaterSunshafts
            // 
            this.lWaterSunshafts.AutoSize = true;
            this.lWaterSunshafts.Dock = System.Windows.Forms.DockStyle.Right;
            this.lWaterSunshafts.Location = new System.Drawing.Point(28, 162);
            this.lWaterSunshafts.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lWaterSunshafts.Name = "lWaterSunshafts";
            this.lWaterSunshafts.Size = new System.Drawing.Size(122, 23);
            this.lWaterSunshafts.TabIndex = 16;
            this.lWaterSunshafts.Text = "Underwater Sunshafts";
            this.lWaterSunshafts.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lSunshafts
            // 
            this.lSunshafts.AutoSize = true;
            this.lSunshafts.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSunshafts.Location = new System.Drawing.Point(92, 108);
            this.lSunshafts.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lSunshafts.Name = "lSunshafts";
            this.lSunshafts.Size = new System.Drawing.Size(58, 23);
            this.lSunshafts.TabIndex = 12;
            this.lSunshafts.Text = "Sunshafts";
            this.lSunshafts.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lHDR
            // 
            this.lHDR.AutoSize = true;
            this.lHDR.Dock = System.Windows.Forms.DockStyle.Right;
            this.lHDR.Location = new System.Drawing.Point(119, 0);
            this.lHDR.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lHDR.Name = "lHDR";
            this.lHDR.Size = new System.Drawing.Size(31, 23);
            this.lHDR.TabIndex = 3;
            this.lHDR.Text = "HDR";
            this.lHDR.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // cmbInteriorCaustics
            // 
            this.cmbInteriorCaustics.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbInteriorCaustics.FormattingEnabled = true;
            this.cmbInteriorCaustics.Items.AddRange(new object[] {
                                    "Off",
                                    "On"});
            this.cmbInteriorCaustics.Location = new System.Drawing.Point(168, 287);
            this.cmbInteriorCaustics.Name = "cmbInteriorCaustics";
            this.cmbInteriorCaustics.Size = new System.Drawing.Size(110, 23);
            this.cmbInteriorCaustics.TabIndex = 19;
            this.cmbInteriorCaustics.SelectedIndexChanged += new System.EventHandler(this.onOptionUpdate);
            // 
            // lInteriorCaustics
            // 
            this.lInteriorCaustics.AutoSize = true;
            this.lInteriorCaustics.Dock = System.Windows.Forms.DockStyle.Right;
            this.lInteriorCaustics.Location = new System.Drawing.Point(24, 189);
            this.lInteriorCaustics.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lInteriorCaustics.Name = "lInteriorCaustics";
            this.lInteriorCaustics.Size = new System.Drawing.Size(126, 23);
            this.lInteriorCaustics.TabIndex = 18;
            this.lInteriorCaustics.Text = "Interior Water Caustics";
            this.lInteriorCaustics.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // bAdvancedMode
            // 
            this.bAdvancedMode.Location = new System.Drawing.Point(183, 330);
            this.bAdvancedMode.Name = "bAdvancedMode";
            this.bAdvancedMode.Size = new System.Drawing.Size(95, 23);
            this.bAdvancedMode.TabIndex = 20;
            this.bAdvancedMode.Text = "Modding >>>";
            this.bAdvancedMode.UseVisualStyleBackColor = true;
            this.bAdvancedMode.Click += new System.EventHandler(this.bAdvancedMode_Click);
            // 
            // udHDRTime
            // 
            this.udHDRTime.DecimalPlaces = 2;
            this.udHDRTime.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udHDRTime.Location = new System.Drawing.Point(168, 126);
            this.udHDRTime.Maximum = new decimal(new int[] {
                                    30,
                                    0,
                                    0,
                                    0});
            this.udHDRTime.Minimum = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    131072});
            this.udHDRTime.Name = "udHDRTime";
            this.udHDRTime.Size = new System.Drawing.Size(70, 23);
            this.udHDRTime.TabIndex = 6;
            this.udHDRTime.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udHDRTime.Value = new decimal(new int[] {
                                    20,
                                    0,
                                    0,
                                    65536});
            // 
            // lHDRTime
            // 
            this.lHDRTime.AutoSize = true;
            this.lHDRTime.Dock = System.Windows.Forms.DockStyle.Right;
            this.lHDRTime.Location = new System.Drawing.Point(23, 27);
            this.lHDRTime.Margin = new System.Windows.Forms.Padding(0, 0, 0, 4);
            this.lHDRTime.Name = "lHDRTime";
            this.lHDRTime.Size = new System.Drawing.Size(127, 23);
            this.lHDRTime.TabIndex = 5;
            this.lHDRTime.Text = "Exposure reaction time";
            this.lHDRTime.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lHDRTime2
            // 
            this.lHDRTime2.AutoSize = true;
            this.lHDRTime2.Location = new System.Drawing.Point(244, 128);
            this.lHDRTime2.Name = "lHDRTime2";
            this.lHDRTime2.Size = new System.Drawing.Size(24, 15);
            this.lHDRTime2.TabIndex = 7;
            this.lHDRTime2.Text = "sec";
            // 
            // tableRightAlign1
            // 
            this.tableRightAlign1.ColumnCount = 1;
            this.tableRightAlign1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableRightAlign1.Controls.Add(this.lPresets, 0, 0);
            this.tableRightAlign1.Location = new System.Drawing.Point(12, 39);
            this.tableRightAlign1.Name = "tableRightAlign1";
            this.tableRightAlign1.RowCount = 1;
            this.tableRightAlign1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableRightAlign1.Size = new System.Drawing.Size(100, 23);
            this.tableRightAlign1.TabIndex = 24;
            // 
            // tableRightAlign2
            // 
            this.tableRightAlign2.ColumnCount = 1;
            this.tableRightAlign2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableRightAlign2.Controls.Add(this.lInteriorCaustics, 0, 7);
            this.tableRightAlign2.Controls.Add(this.lWaterSunshafts, 0, 6);
            this.tableRightAlign2.Controls.Add(this.lDoF, 0, 5);
            this.tableRightAlign2.Controls.Add(this.lHDRTime, 0, 1);
            this.tableRightAlign2.Controls.Add(this.lSunshafts, 0, 4);
            this.tableRightAlign2.Controls.Add(this.lBloom, 0, 3);
            this.tableRightAlign2.Controls.Add(this.lSSAO, 0, 2);
            this.tableRightAlign2.Controls.Add(this.lHDR, 0, 0);
            this.tableRightAlign2.Location = new System.Drawing.Point(12, 99);
            this.tableRightAlign2.Name = "tableRightAlign2";
            this.tableRightAlign2.RowCount = 8;
            this.tableRightAlign2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableRightAlign2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableRightAlign2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableRightAlign2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableRightAlign2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableRightAlign2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableRightAlign2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableRightAlign2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableRightAlign2.Size = new System.Drawing.Size(150, 211);
            this.tableRightAlign2.TabIndex = 25;
            // 
            // ShaderActive
            // 
            this.AcceptButton = this.bSave;
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.CancelButton = this.bCancel;
            this.ClientSize = new System.Drawing.Size(644, 411);
            this.Controls.Add(this.tableRightAlign2);
            this.Controls.Add(this.tableRightAlign1);
            this.Controls.Add(this.lHDRTime2);
            this.Controls.Add(this.udHDRTime);
            this.Controls.Add(this.bAdvancedMode);
            this.Controls.Add(this.bSave);
            this.Controls.Add(this.bCancel);
            this.Controls.Add(this.cmbInteriorCaustics);
            this.Controls.Add(this.cmbWaterSunshafts);
            this.Controls.Add(this.cmbDoF);
            this.Controls.Add(this.cmbSunshafts);
            this.Controls.Add(this.cmbBloom);
            this.Controls.Add(this.cmbSSAO);
            this.Controls.Add(this.cmbHDR);
            this.Controls.Add(this.cmbPresets);
            this.Controls.Add(this.lShaderOptions);
            this.Controls.Add(this.tableLayoutPanelAdv);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(650, 440);
            this.MinimumSize = new System.Drawing.Size(305, 440);
            this.Name = "ShaderActive";
            this.Text = "Set active shaders";
            this.tableLayoutPanelAdv.ResumeLayout(false);
            this.tableLayoutPanelAdv.PerformLayout();
            this.panelActions.ResumeLayout(false);
            this.panelActiveListActions.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.udHDRTime)).EndInit();
            this.tableRightAlign1.ResumeLayout(false);
            this.tableRightAlign1.PerformLayout();
            this.tableRightAlign2.ResumeLayout(false);
            this.tableRightAlign2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();
        }
        private System.Windows.Forms.TableLayoutPanel tableRightAlign2;
        private System.Windows.Forms.TableLayoutPanel tableRightAlign1;
        public System.Windows.Forms.ToolTip toolTip;
        private System.Windows.Forms.Label lHDRTime2;
        private System.Windows.Forms.Label lHDRTime;
        private System.Windows.Forms.NumericUpDown udHDRTime;
        private System.Windows.Forms.Button bAdvancedMode;
        private System.Windows.Forms.Label lInteriorCaustics;
        private System.Windows.Forms.ComboBox cmbInteriorCaustics;
        private System.Windows.Forms.Label lHDR;
        private System.Windows.Forms.Label lSunshafts;
        private System.Windows.Forms.Label lWaterSunshafts;
        private System.Windows.Forms.Label lDoF;
        private System.Windows.Forms.Label lBloom;
        private System.Windows.Forms.Label lSSAO;
        private System.Windows.Forms.ComboBox cmbWaterSunshafts;
        private System.Windows.Forms.ComboBox cmbDoF;
        private System.Windows.Forms.ComboBox cmbSunshafts;
        private System.Windows.Forms.ComboBox cmbBloom;
        private System.Windows.Forms.ComboBox cmbSSAO;
        private System.Windows.Forms.ComboBox cmbHDR;
        private System.Windows.Forms.Label lPresets;
        private System.Windows.Forms.Label lShaderOptions;
        private System.Windows.Forms.ComboBox cmbPresets;
        private System.Windows.Forms.Panel panelActiveListActions;
        private System.Windows.Forms.Panel panelActions;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanelAdv;
        private System.Windows.Forms.Label lShaderUsage;
        private System.Windows.Forms.Button bEditor;
        private System.Windows.Forms.Label lActiveList;
        private System.Windows.Forms.Label lAvailableList;

        #endregion
        #endregion
        
        public ShaderActive() {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            this.Size = new System.Drawing.Size(this.MinimumSize.Width, this.Size.Height);

            loadSettings();
            onShaderListUpdate();
        }
        
        private void loadSettings() {
            foreach (String s in Directory.GetFiles(Statics.runDir + "\\" + Statics.pathShaders)) {
                if(s.EndsWith(".fx")) lbAvailable.Items.Add(Path.GetFileNameWithoutExtension(s));
            }
            
            INIFile iniFile = new INIFile(Statics.iniFileName, iniShaderDefault, true);
            udHDRTime.Value = (decimal)iniFile.getKeyValue("HDRTime");
                
            List<string> shaderList = new List<string>(iniFile.getSectList(iniShaderChain));
            foreach (string s in shaderList) {
				if (File.Exists(Statics.runDir + "\\" + Statics.pathShaders + "\\" + s + ".fx")) {
	                lbSelected.Items.Add(s);
            	}
            }
        }

        private void cmbPresets_Changed(object sender, EventArgs e) {
            if(setup) return;
            if(cmbPresets.SelectedIndex == cmbPresets.Items.Count - 1) return;
            
            string[][] presets = new string[][] { presetLowest, presetLow, presetMed, presetHigh, presetUltra };
            lbSelected.Items.Clear();
            lbSelected.Items.AddRange(presets[cmbPresets.SelectedIndex]);
            onShaderListUpdate();
        }
        
        private void bAdvancedMode_Click(object sender, EventArgs e) {
            int newWidth = (this.Size.Width == this.MinimumSize.Width) ? this.MaximumSize.Width : this.MinimumSize.Width;
            this.Size = new System.Drawing.Size(newWidth, this.Size.Height);
        }
        
        private void onOptionUpdate(object sender, EventArgs e) {
            if(setup) return;
            
            lbSelected.Items.Clear();
            addShaderOption(effectSSAO, cmbSSAO.SelectedIndex);
            addShaderOption(effectInteriorCaustics, cmbInteriorCaustics.SelectedIndex);
            addShaderOption(effectWaterSunshafts, cmbWaterSunshafts.SelectedIndex);
            addShaderOption(effectDoF, cmbDoF.SelectedIndex);
            addShaderOption(effectSunshafts, cmbSunshafts.SelectedIndex);
            addShaderOption(effectBloom, cmbBloom.SelectedIndex);
            addShaderOption(effectHDR, cmbHDR.SelectedIndex);
            
            setup = true;
            cmbPresets.SelectedIndex = cmbPresets.Items.Count - 1;
            setup = false;
        }
        
        private void onShaderListUpdate() {
            setup = true;

            cmbHDR.SelectedIndex = findShaderOption(effectHDR);
            cmbSSAO.SelectedIndex = findShaderOption(effectSSAO);
            cmbBloom.SelectedIndex = findShaderOption(effectBloom);
            cmbSunshafts.SelectedIndex = findShaderOption(effectSunshafts);
            cmbDoF.SelectedIndex = findShaderOption(effectDoF);
            cmbWaterSunshafts.SelectedIndex = findShaderOption(effectWaterSunshafts);
            cmbInteriorCaustics.SelectedIndex = findShaderOption(effectInteriorCaustics);

            string[][] presets = new string[][] { presetLowest, presetLow, presetMed, presetHigh, presetUltra };
            IEnumerable<string> sel = lbSelected.Items.OfType<string>();

            cmbPresets.SelectedIndex = 5;
            for(int n = 0; n != presets.Count(); n++) {
                if(presets[n].SequenceEqual(sel)) {
                    cmbPresets.SelectedIndex = n;
                    break;
                }
            }

            setup = false;
        }
        
        private void addShaderOption(List<string> effect, int n) {
            if(n > 0)
                lbSelected.Items.Add(effect[n - 1]);
        }
        
        private int findShaderOption(List<string> effect) {
            foreach(string item in lbSelected.Items) {
                if(effect.Contains(item))
                    return 1 + effect.IndexOf(item);
            }
            return 0;
        }
        
        private void lbAvailable_DoubleClick(object sender,EventArgs e) {
            if(lbSelected.Items.Count>=32) return;
            if(lbAvailable.SelectedIndex==-1) return;

            DirectX.DXMain.CreateDevice(this);
            if (DirectX.Shaders.CompileShader(false, null, null, Statics.runDir + "\\" + Statics.pathShaders + "\\" + (string)lbAvailable.SelectedItem + ".fx") != null) {
                MessageBox.Show("That shader does not currently compile.");
            } else {
                lbSelected.Items.Add(string.Copy((string)lbAvailable.SelectedItem));
                onShaderListUpdate();
            }
            DirectX.DXMain.CloseDevice();
        }

        private void lbSelected_DoubleClick(object sender,EventArgs e) {
            if(lbSelected.SelectedIndex!=-1) {
                lbSelected.Items.RemoveAt(lbSelected.SelectedIndex);
                onShaderListUpdate();
            }
        }

        private void bCancel_Click(object sender,EventArgs e) {
            Close();
        }

        private void bSave_Click(object sender,EventArgs e) {
            INIFile iniFile = new INIFile(Statics.iniFileName, iniShaderDefault, true);
            
            iniFile.setKey("HDRTime", (double)udHDRTime.Value);
            iniFile.setSectOrderedList(iniShaderChain, lbSelected.Items.OfType<string>().ToArray());
            
            iniFile.save();
            Close();
        }

        private void bMoveUp_Click(object sender,EventArgs e) {
            if(lbSelected.SelectedIndex>0) {
                string s=(string)lbSelected.Items[lbSelected.SelectedIndex];
                lbSelected.Items[lbSelected.SelectedIndex]=lbSelected.Items[lbSelected.SelectedIndex-1];
                lbSelected.Items[lbSelected.SelectedIndex-1]=s;
                lbSelected.SelectedIndex--;
            }
        }

        private void bMoveDown_Click(object sender,EventArgs e) {
            if(lbSelected.SelectedIndex!=-1&&lbSelected.SelectedIndex!=lbSelected.Items.Count-1) {
                string s=(string)lbSelected.Items[lbSelected.SelectedIndex];
                lbSelected.Items[lbSelected.SelectedIndex]=lbSelected.Items[lbSelected.SelectedIndex+1];
                lbSelected.Items[lbSelected.SelectedIndex+1]=s;
                lbSelected.SelectedIndex++;
            }
        }

        private void bClear_Click(object sender,EventArgs e) {
            lbSelected.Items.Clear();
        }

        private void bEditor_Click(object sender, EventArgs e)
        {
        	string shader = null;
            if(lbAvailable.SelectedIndex != -1)
				shader = Statics.runDir + "\\" + Statics.pathShaders + "\\" + (string)lbAvailable.SelectedItem + ".fx";

            ShaderEditorForm ed = new ShaderEditorForm(shader);
            ed.ShowDialog();
        }
    }
}
