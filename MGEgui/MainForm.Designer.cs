using System.Windows.Forms;
using System;
using System.ComponentModel;

namespace MGEgui {
    partial class MainForm {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components=null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.DudMenu = new System.Windows.Forms.ContextMenu();
            this.OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.SaveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.toolTip = new System.Windows.Forms.ToolTip(this.components);
            this.tpInput = new System.Windows.Forms.TabPage();
            this.gbMWLighting = new System.Windows.Forms.GroupBox();
            this.bMWLightingReset = new System.Windows.Forms.Button();
            this.lLightingConst = new System.Windows.Forms.Label();
            this.lLightingLin = new System.Windows.Forms.Label();
            this.lLightingQuad = new System.Windows.Forms.Label();
            this.udLightingConst = new System.Windows.Forms.NumericUpDown();
            this.udLightingLinear = new System.Windows.Forms.NumericUpDown();
            this.udLightingQuad = new System.Windows.Forms.NumericUpDown();
            this.gbMWGeneral = new System.Windows.Forms.GroupBox();
            this.lScreenshotStatus = new System.Windows.Forms.Label();
            this.cbScreenshots = new System.Windows.Forms.CheckBox();
            this.cbHitFader = new System.Windows.Forms.CheckBox();
            this.cbAudio = new System.Windows.Forms.CheckBox();
            this.cbHQShadows = new System.Windows.Forms.CheckBox();
            this.cbShowFPS = new System.Windows.Forms.CheckBox();
            this.cbThreadLoad = new System.Windows.Forms.CheckBox();
            this.cbYesToAll = new System.Windows.Forms.CheckBox();
            this.cbSubtitles = new System.Windows.Forms.CheckBox();
            this.gbMsgs = new System.Windows.Forms.GroupBox();
            this.cbDisplayMessages = new System.Windows.Forms.CheckBox();
            this.udMsgsTime = new System.Windows.Forms.NumericUpDown();
            this.cmbMsgsLocale = new System.Windows.Forms.ComboBox();
            this.lMsgsTime = new System.Windows.Forms.Label();
            this.lMsgsLanguage = new System.Windows.Forms.Label();
            this.lMsgsTimeUnit = new System.Windows.Forms.Label();
            this.pCam3rdPrsn = new System.Windows.Forms.Panel();
            this.cbCam3rdPrsn = new System.Windows.Forms.CheckBox();
            this.gbCam3rdPrsn = new System.Windows.Forms.GroupBox();
            this.udCam3rdZ = new System.Windows.Forms.NumericUpDown();
            this.udCam3rdY = new System.Windows.Forms.NumericUpDown();
            this.udCam3rdX = new System.Windows.Forms.NumericUpDown();
            this.lCam3rdX = new System.Windows.Forms.Label();
            this.lCam3rdY = new System.Windows.Forms.Label();
            this.lCam3rdZ = new System.Windows.Forms.Label();
            this.gbInputTools = new System.Windows.Forms.GroupBox();
            this.bMacroEd = new System.Windows.Forms.Button();
            this.bRemapper = new System.Windows.Forms.Button();
            this.gbInputOpts = new System.Windows.Forms.GroupBox();
            this.cbD3D8To9Only = new System.Windows.Forms.CheckBox();
            this.cbMenuCaching = new System.Windows.Forms.CheckBox();
            this.cbAutoCrosshair = new System.Windows.Forms.CheckBox();
            this.cbDisableMGE = new System.Windows.Forms.CheckBox();
            this.cbDisableMWSE = new System.Windows.Forms.CheckBox();
            this.cbSkipMovie = new System.Windows.Forms.CheckBox();
            this.cbAltCombat = new System.Windows.Forms.CheckBox();
            this.lSShotFormat = new System.Windows.Forms.Label();
            this.cmbSShotFormat = new System.Windows.Forms.ComboBox();
            this.tpGlobal = new System.Windows.Forms.TabPage();
            this.gbSShot = new System.Windows.Forms.GroupBox();
            this.tableLayoutScreenshots = new System.Windows.Forms.TableLayoutPanel();
            this.tableAlignSSFormat = new System.Windows.Forms.TableLayoutPanel();
            this.lSShotName = new System.Windows.Forms.Label();
            this.tbSShotName = new System.Windows.Forms.TextBox();
            this.lSShotDir = new System.Windows.Forms.Label();
            this.tbSShotDir = new System.Windows.Forms.TextBox();
            this.lSShotSuffix = new System.Windows.Forms.Label();
            this.cmbSShotSuffix = new System.Windows.Forms.ComboBox();
            this.lScreenshotHelp = new System.Windows.Forms.Label();
            this.panelSShotDirButtons = new System.Windows.Forms.Panel();
            this.bSShotDirBrowse = new System.Windows.Forms.Button();
            this.bSShotDirClear = new System.Windows.Forms.Button();
            this.gbScene = new System.Windows.Forms.GroupBox();
            this.cbReduceTextureMemUse = new System.Windows.Forms.CheckBox();
            this.cbAutoFOV = new System.Windows.Forms.CheckBox();
            this.udUIScale = new System.Windows.Forms.NumericUpDown();
            this.lUIScale = new System.Windows.Forms.Label();
            this.lFPSLimit = new System.Windows.Forms.Label();
            this.udFPSLimit = new System.Windows.Forms.NumericUpDown();
            this.bShaderEd = new System.Windows.Forms.Button();
            this.cmbFogMode = new System.Windows.Forms.ComboBox();
            this.lFogMode = new System.Windows.Forms.Label();
            this.cbHWShader = new System.Windows.Forms.CheckBox();
            this.cbFPSCounter = new System.Windows.Forms.CheckBox();
            this.udFOV = new System.Windows.Forms.NumericUpDown();
            this.lFOV = new System.Windows.Forms.Label();
            this.gbDisplay = new System.Windows.Forms.GroupBox();
            this.tableLayoutWindowAlign = new System.Windows.Forms.TableLayoutPanel();
            this.panelWindowAlign = new System.Windows.Forms.Panel();
            this.rbWindowAlignBottomRight = new System.Windows.Forms.RadioButton();
            this.rbWindowAlignCenterRight = new System.Windows.Forms.RadioButton();
            this.rbWindowAlignTopRight = new System.Windows.Forms.RadioButton();
            this.rbWindowAlignBottomCenter = new System.Windows.Forms.RadioButton();
            this.rbWindowAlignBottomLeft = new System.Windows.Forms.RadioButton();
            this.rbWindowAlignCenter = new System.Windows.Forms.RadioButton();
            this.rbWindowAlignCenterLeft = new System.Windows.Forms.RadioButton();
            this.rbWindowAlignCenterTop = new System.Windows.Forms.RadioButton();
            this.rbWindowAlignTopLeft = new System.Windows.Forms.RadioButton();
            this.lWindowAlign = new System.Windows.Forms.Label();
            this.tableAlignResolution = new System.Windows.Forms.TableLayoutPanel();
            this.lResolution = new System.Windows.Forms.Label();
            this.cbBorderless = new System.Windows.Forms.CheckBox();
            this.tbRefreshRate = new System.Windows.Forms.TextBox();
            this.tableLayoutDisplay = new System.Windows.Forms.TableLayoutPanel();
            this.cmbAntiAlias = new System.Windows.Forms.ComboBox();
            this.lAntiAlias = new System.Windows.Forms.Label();
            this.cmbVWait = new System.Windows.Forms.ComboBox();
            this.cmbAnisoLevel = new System.Windows.Forms.ComboBox();
            this.lAnisoLevel = new System.Windows.Forms.Label();
            this.lVWait = new System.Windows.Forms.Label();
            this.tbAspect = new System.Windows.Forms.TextBox();
            this.bSelectResolution = new System.Windows.Forms.Button();
            this.cbWindowed = new System.Windows.Forms.CheckBox();
            this.tbResolution = new System.Windows.Forms.TextBox();
            this.lAspect = new System.Windows.Forms.Label();
            this.lRefreshRate = new System.Windows.Forms.Label();
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tpDL = new System.Windows.Forms.TabPage();
            this.bDistantLandWizard = new System.Windows.Forms.Button();
            this.cbDLDistantLand = new System.Windows.Forms.CheckBox();
            this.gbDistantLand = new System.Windows.Forms.GroupBox();
            this.tableLayoutDL = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutDLLeft = new System.Windows.Forms.TableLayoutPanel();
            this.gbXEFeatures = new System.Windows.Forms.GroupBox();
            this.cbDLSunShadows = new System.Windows.Forms.CheckBox();
            this.cmbDLShadowDetail = new System.Windows.Forms.ComboBox();
            this.cmbPerPixelLightFlags = new System.Windows.Forms.ComboBox();
            this.cbPerPixelLighting = new System.Windows.Forms.CheckBox();
            this.bMWLightSettings = new System.Windows.Forms.Button();
            this.gbDLDrawDist = new System.Windows.Forms.GroupBox();
            this.lDLDrawDist = new System.Windows.Forms.Label();
            this.udDLDrawDist = new System.Windows.Forms.NumericUpDown();
            this.gbDLWater = new System.Windows.Forms.GroupBox();
            this.cbDLDynRipples = new System.Windows.Forms.CheckBox();
            this.gbDLWtrCaust = new System.Windows.Forms.GroupBox();
            this.lDLWtrCaust = new System.Windows.Forms.Label();
            this.udDLWtrCaust = new System.Windows.Forms.NumericUpDown();
            this.gbDLWtrWave = new System.Windows.Forms.GroupBox();
            this.lDLWtrWave = new System.Windows.Forms.Label();
            this.udDLWtrWave = new System.Windows.Forms.NumericUpDown();
            this.gbDLWtrRefl = new System.Windows.Forms.GroupBox();
            this.cbDLSkyRefl = new System.Windows.Forms.CheckBox();
            this.cbDLReflLand = new System.Windows.Forms.CheckBox();
            this.cbDLReflBlur = new System.Windows.Forms.CheckBox();
            this.cbDLReflNStatics = new System.Windows.Forms.CheckBox();
            this.cbDLReflInterior = new System.Windows.Forms.CheckBox();
            this.tableLayoutDLRight = new System.Windows.Forms.TableLayoutPanel();
            this.pDLAutoDist = new System.Windows.Forms.Panel();
            this.cbDLAutoDist = new System.Windows.Forms.CheckBox();
            this.gbDLAutoDist = new System.Windows.Forms.GroupBox();
            this.rbDLAutoByAFogEnd = new System.Windows.Forms.RadioButton();
            this.rbDLAutoByDrawDist = new System.Windows.Forms.RadioButton();
            this.pDLStatics = new System.Windows.Forms.Panel();
            this.cbDLDistantStatics = new System.Windows.Forms.CheckBox();
            this.gbDLStatics = new System.Windows.Forms.GroupBox();
            this.tableAlignDLStatics = new System.Windows.Forms.TableLayoutPanel();
            this.lDLNear = new System.Windows.Forms.Label();
            this.udDLDistNear = new System.Windows.Forms.NumericUpDown();
            this.udDLDistVeryFar = new System.Windows.Forms.NumericUpDown();
            this.tbDLNearSize = new System.Windows.Forms.TextBox();
            this.lDLFar = new System.Windows.Forms.Label();
            this.lDLVeryFar = new System.Windows.Forms.Label();
            this.udDLSizeVeryFar = new System.Windows.Forms.NumericUpDown();
            this.udDLSizeFar = new System.Windows.Forms.NumericUpDown();
            this.udDLDistFar = new System.Windows.Forms.NumericUpDown();
            this.lDLMinSize = new System.Windows.Forms.Label();
            this.lDLEndDist = new System.Windows.Forms.Label();
            this.bDLWthr = new System.Windows.Forms.Button();
            this.gbDLFog = new System.Windows.Forms.GroupBox();
            this.tableAlignDLFog = new System.Windows.Forms.TableLayoutPanel();
            this.udDLFogAStart = new System.Windows.Forms.NumericUpDown();
            this.udDLFogAEnd = new System.Windows.Forms.NumericUpDown();
            this.udDLFogExpMul = new System.Windows.Forms.NumericUpDown();
            this.lDLFogExpMul = new System.Windows.Forms.Label();
            this.udDLFogBStart = new System.Windows.Forms.NumericUpDown();
            this.udDLFogBEnd = new System.Windows.Forms.NumericUpDown();
            this.lDLFogI = new System.Windows.Forms.Label();
            this.udDLFogIStart = new System.Windows.Forms.NumericUpDown();
            this.udDLFogIEnd = new System.Windows.Forms.NumericUpDown();
            this.lDLFogB = new System.Windows.Forms.Label();
            this.lDLFogA = new System.Windows.Forms.Label();
            this.cbDLScattering = new System.Windows.Forms.CheckBox();
            this.cbDLFogExp = new System.Windows.Forms.CheckBox();
            this.lDLFogStart = new System.Windows.Forms.Label();
            this.lDLFogEnd = new System.Windows.Forms.Label();
            this.tpConfig = new System.Windows.Forms.TabPage();
            this.gbErrorReporting = new System.Windows.Forms.GroupBox();
            this.bReportingShowDLWizardLog = new System.Windows.Forms.Button();
            this.bReportingShowLog = new System.Windows.Forms.Button();
            this.gbMainUI = new System.Windows.Forms.GroupBox();
            this.pLanguage = new System.Windows.Forms.Panel();
            this.cmbUILanguage = new System.Windows.Forms.ComboBox();
            this.cbUILangAuto = new System.Windows.Forms.CheckBox();
            this.lUILanguage = new System.Windows.Forms.Label();
            this.cmbTipReadSpd = new System.Windows.Forms.ComboBox();
            this.lTipReadSpd = new System.Windows.Forms.Label();
            this.lTipRSpdUnit = new System.Windows.Forms.Label();
            this.gbMainInfo = new System.Windows.Forms.GroupBox();
            this.bViewCaps = new System.Windows.Forms.Button();
            this.bHelp = new System.Windows.Forms.Button();
            this.bAbout = new System.Windows.Forms.Button();
            this.gbMainSettings = new System.Windows.Forms.GroupBox();
            this.bResetSettings = new System.Windows.Forms.Button();
            this.bImport = new System.Windows.Forms.Button();
            this.bExport = new System.Windows.Forms.Button();
            this.cbClearINI = new System.Windows.Forms.CheckBox();
            this.tpInstructions = new System.Windows.Forms.TabPage();
            this.lInstructions = new System.Windows.Forms.Label();
            this.SShotFolderDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.tpInput.SuspendLayout();
            this.gbMWLighting.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udLightingConst)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udLightingLinear)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udLightingQuad)).BeginInit();
            this.gbMWGeneral.SuspendLayout();
            this.gbMsgs.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udMsgsTime)).BeginInit();
            this.pCam3rdPrsn.SuspendLayout();
            this.gbCam3rdPrsn.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udCam3rdZ)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udCam3rdY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udCam3rdX)).BeginInit();
            this.gbInputTools.SuspendLayout();
            this.gbInputOpts.SuspendLayout();
            this.tpGlobal.SuspendLayout();
            this.gbSShot.SuspendLayout();
            this.tableLayoutScreenshots.SuspendLayout();
            this.tableAlignSSFormat.SuspendLayout();
            this.panelSShotDirButtons.SuspendLayout();
            this.gbScene.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udUIScale)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udFPSLimit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udFOV)).BeginInit();
            this.gbDisplay.SuspendLayout();
            this.tableLayoutWindowAlign.SuspendLayout();
            this.panelWindowAlign.SuspendLayout();
            this.tableAlignResolution.SuspendLayout();
            this.tableLayoutDisplay.SuspendLayout();
            this.tabControl.SuspendLayout();
            this.tpDL.SuspendLayout();
            this.gbDistantLand.SuspendLayout();
            this.tableLayoutDL.SuspendLayout();
            this.tableLayoutDLLeft.SuspendLayout();
            this.gbXEFeatures.SuspendLayout();
            this.gbDLDrawDist.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLDrawDist)).BeginInit();
            this.gbDLWater.SuspendLayout();
            this.gbDLWtrCaust.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLWtrCaust)).BeginInit();
            this.gbDLWtrWave.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLWtrWave)).BeginInit();
            this.gbDLWtrRefl.SuspendLayout();
            this.tableLayoutDLRight.SuspendLayout();
            this.pDLAutoDist.SuspendLayout();
            this.gbDLAutoDist.SuspendLayout();
            this.pDLStatics.SuspendLayout();
            this.gbDLStatics.SuspendLayout();
            this.tableAlignDLStatics.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLDistNear)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLDistVeryFar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLSizeVeryFar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLSizeFar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLDistFar)).BeginInit();
            this.gbDLFog.SuspendLayout();
            this.tableAlignDLFog.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogAStart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogAEnd)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogExpMul)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogBStart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogBEnd)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogIStart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogIEnd)).BeginInit();
            this.tpConfig.SuspendLayout();
            this.gbErrorReporting.SuspendLayout();
            this.gbMainUI.SuspendLayout();
            this.pLanguage.SuspendLayout();
            this.gbMainInfo.SuspendLayout();
            this.gbMainSettings.SuspendLayout();
            this.tpInstructions.SuspendLayout();
            this.SuspendLayout();
            // 
            // OpenFileDialog
            // 
            this.OpenFileDialog.DefaultExt = "mge";
            this.OpenFileDialog.Filter = "MGE exported settings (*.MGE)|*.MGE";
            this.OpenFileDialog.RestoreDirectory = true;
            this.OpenFileDialog.Title = "Select settings file to import";
            // 
            // SaveFileDialog
            // 
            this.SaveFileDialog.DefaultExt = "mge";
            this.SaveFileDialog.Filter = "MGE exported settings (*.MGE)|*.MGE";
            this.SaveFileDialog.RestoreDirectory = true;
            this.SaveFileDialog.Title = "Export settings";
            // 
            // toolTip
            // 
            this.toolTip.AutomaticDelay = 3000;
            this.toolTip.AutoPopDelay = 30000;
            this.toolTip.InitialDelay = 500;
            this.toolTip.ReshowDelay = 100;
            // 
            // tpInput
            // 
            this.tpInput.Controls.Add(this.gbMWLighting);
            this.tpInput.Controls.Add(this.gbMWGeneral);
            this.tpInput.Controls.Add(this.gbMsgs);
            this.tpInput.Controls.Add(this.pCam3rdPrsn);
            this.tpInput.Controls.Add(this.gbInputTools);
            this.tpInput.Controls.Add(this.gbInputOpts);
            this.tpInput.Location = new System.Drawing.Point(4, 24);
            this.tpInput.Name = "tpInput";
            this.tpInput.Size = new System.Drawing.Size(716, 473);
            this.tpInput.TabIndex = 3;
            this.tpInput.Text = "In-Game";
            this.tpInput.ToolTipText = "Options affecting Morrowind during gameplay, including a macro editor and key rem" +
            "apper.";
            this.tpInput.UseVisualStyleBackColor = true;
            // 
            // gbMWLighting
            // 
            this.gbMWLighting.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.gbMWLighting.Controls.Add(this.bMWLightingReset);
            this.gbMWLighting.Controls.Add(this.lLightingConst);
            this.gbMWLighting.Controls.Add(this.lLightingLin);
            this.gbMWLighting.Controls.Add(this.lLightingQuad);
            this.gbMWLighting.Controls.Add(this.udLightingConst);
            this.gbMWLighting.Controls.Add(this.udLightingLinear);
            this.gbMWLighting.Controls.Add(this.udLightingQuad);
            this.gbMWLighting.Location = new System.Drawing.Point(390, 129);
            this.gbMWLighting.Name = "gbMWLighting";
            this.gbMWLighting.Size = new System.Drawing.Size(318, 72);
            this.gbMWLighting.TabIndex = 10;
            this.gbMWLighting.TabStop = false;
            this.gbMWLighting.Text = "Dynamic lighting coefficients";
            // 
            // bMWLightingReset
            // 
            this.bMWLightingReset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bMWLightingReset.Location = new System.Drawing.Point(256, 0);
            this.bMWLightingReset.Name = "bMWLightingReset";
            this.bMWLightingReset.Size = new System.Drawing.Size(56, 22);
            this.bMWLightingReset.TabIndex = 6;
            this.bMWLightingReset.Text = "Reset";
            this.bMWLightingReset.UseVisualStyleBackColor = true;
            this.bMWLightingReset.Click += new System.EventHandler(this.bMWLightingReset_Click);
            // 
            // lLightingConst
            // 
            this.lLightingConst.AutoSize = true;
            this.lLightingConst.Location = new System.Drawing.Point(182, 21);
            this.lLightingConst.Name = "lLightingConst";
            this.lLightingConst.Size = new System.Drawing.Size(55, 15);
            this.lLightingConst.TabIndex = 5;
            this.lLightingConst.Text = "Constant";
            // 
            // lLightingLin
            // 
            this.lLightingLin.AutoSize = true;
            this.lLightingLin.Location = new System.Drawing.Point(97, 21);
            this.lLightingLin.Name = "lLightingLin";
            this.lLightingLin.Size = new System.Drawing.Size(39, 15);
            this.lLightingLin.TabIndex = 4;
            this.lLightingLin.Text = "Linear";
            // 
            // lLightingQuad
            // 
            this.lLightingQuad.AutoSize = true;
            this.lLightingQuad.Location = new System.Drawing.Point(12, 21);
            this.lLightingQuad.Name = "lLightingQuad";
            this.lLightingQuad.Size = new System.Drawing.Size(59, 15);
            this.lLightingQuad.TabIndex = 3;
            this.lLightingQuad.Text = "Quadratic";
            // 
            // udLightingConst
            // 
            this.udLightingConst.DecimalPlaces = 3;
            this.udLightingConst.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udLightingConst.Location = new System.Drawing.Point(184, 39);
            this.udLightingConst.Maximum = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    0});
            this.udLightingConst.Name = "udLightingConst";
            this.udLightingConst.Size = new System.Drawing.Size(64, 23);
            this.udLightingConst.TabIndex = 2;
            // 
            // udLightingLinear
            // 
            this.udLightingLinear.DecimalPlaces = 3;
            this.udLightingLinear.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udLightingLinear.Location = new System.Drawing.Point(99, 39);
            this.udLightingLinear.Maximum = new decimal(new int[] {
                                    30,
                                    0,
                                    0,
                                    0});
            this.udLightingLinear.Name = "udLightingLinear";
            this.udLightingLinear.Size = new System.Drawing.Size(64, 23);
            this.udLightingLinear.TabIndex = 1;
            this.udLightingLinear.Value = new decimal(new int[] {
                                    3,
                                    0,
                                    0,
                                    0});
            // 
            // udLightingQuad
            // 
            this.udLightingQuad.DecimalPlaces = 3;
            this.udLightingQuad.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udLightingQuad.Location = new System.Drawing.Point(14, 39);
            this.udLightingQuad.Maximum = new decimal(new int[] {
                                    30,
                                    0,
                                    0,
                                    0});
            this.udLightingQuad.Name = "udLightingQuad";
            this.udLightingQuad.Size = new System.Drawing.Size(64, 23);
            this.udLightingQuad.TabIndex = 0;
            // 
            // gbMWGeneral
            // 
            this.gbMWGeneral.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbMWGeneral.Controls.Add(this.lScreenshotStatus);
            this.gbMWGeneral.Controls.Add(this.cbScreenshots);
            this.gbMWGeneral.Controls.Add(this.cbHitFader);
            this.gbMWGeneral.Controls.Add(this.cbAudio);
            this.gbMWGeneral.Controls.Add(this.cbHQShadows);
            this.gbMWGeneral.Controls.Add(this.cbShowFPS);
            this.gbMWGeneral.Controls.Add(this.cbThreadLoad);
            this.gbMWGeneral.Controls.Add(this.cbYesToAll);
            this.gbMWGeneral.Controls.Add(this.cbSubtitles);
            this.gbMWGeneral.Location = new System.Drawing.Point(8, 207);
            this.gbMWGeneral.Name = "gbMWGeneral";
            this.gbMWGeneral.Size = new System.Drawing.Size(700, 185);
            this.gbMWGeneral.TabIndex = 9;
            this.gbMWGeneral.TabStop = false;
            this.gbMWGeneral.Text = "Morrowind.ini settings";
            // 
            // lScreenshotStatus
            // 
            this.lScreenshotStatus.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.lScreenshotStatus.Location = new System.Drawing.Point(13, 121);
            this.lScreenshotStatus.Name = "lScreenshotStatus";
            this.lScreenshotStatus.Size = new System.Drawing.Size(670, 54);
            this.lScreenshotStatus.TabIndex = 9;
            this.lScreenshotStatus.Text = "Screenshots can be taken with the PrintScreen key. MGE will compress and save the" +
            "m for you.";
            // 
            // cbScreenshots
            // 
            this.cbScreenshots.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbScreenshots.AutoSize = true;
            this.cbScreenshots.Location = new System.Drawing.Point(350, 21);
            this.cbScreenshots.Name = "cbScreenshots";
            this.cbScreenshots.Size = new System.Drawing.Size(121, 19);
            this.cbScreenshots.TabIndex = 0;
            this.cbScreenshots.Text = "Allow screenshots";
            // 
            // cbHitFader
            // 
            this.cbHitFader.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbHitFader.AutoSize = true;
            this.cbHitFader.Checked = true;
            this.cbHitFader.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbHitFader.Location = new System.Drawing.Point(350, 90);
            this.cbHitFader.Name = "cbHitFader";
            this.cbHitFader.Size = new System.Drawing.Size(72, 19);
            this.cbHitFader.TabIndex = 8;
            this.cbHitFader.Text = "Hit fader";
            // 
            // cbAudio
            // 
            this.cbAudio.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbAudio.AutoSize = true;
            this.cbAudio.Location = new System.Drawing.Point(350, 67);
            this.cbAudio.Name = "cbAudio";
            this.cbAudio.Size = new System.Drawing.Size(97, 19);
            this.cbAudio.TabIndex = 7;
            this.cbAudio.Text = "Disable audio";
            // 
            // cbHQShadows
            // 
            this.cbHQShadows.AutoSize = true;
            this.cbHQShadows.Location = new System.Drawing.Point(13, 44);
            this.cbHQShadows.Name = "cbHQShadows";
            this.cbHQShadows.Size = new System.Drawing.Size(208, 19);
            this.cbHQShadows.TabIndex = 1;
            this.cbHQShadows.Text = "High detail actor shadows [buggy]";
            // 
            // cbShowFPS
            // 
            this.cbShowFPS.AutoSize = true;
            this.cbShowFPS.Location = new System.Drawing.Point(13, 90);
            this.cbShowFPS.Name = "cbShowFPS";
            this.cbShowFPS.Size = new System.Drawing.Size(77, 19);
            this.cbShowFPS.TabIndex = 2;
            this.cbShowFPS.Text = "Show FPS";
            // 
            // cbThreadLoad
            // 
            this.cbThreadLoad.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbThreadLoad.AutoSize = true;
            this.cbThreadLoad.Checked = true;
            this.cbThreadLoad.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbThreadLoad.Location = new System.Drawing.Point(350, 44);
            this.cbThreadLoad.Name = "cbThreadLoad";
            this.cbThreadLoad.Size = new System.Drawing.Size(106, 19);
            this.cbThreadLoad.TabIndex = 6;
            this.cbThreadLoad.Text = "Thread loading";
            // 
            // cbYesToAll
            // 
            this.cbYesToAll.AutoSize = true;
            this.cbYesToAll.Location = new System.Drawing.Point(13, 21);
            this.cbYesToAll.Name = "cbYesToAll";
            this.cbYesToAll.Size = new System.Drawing.Size(164, 19);
            this.cbYesToAll.TabIndex = 5;
            this.cbYesToAll.Text = "Allow yes to all load errors";
            // 
            // cbSubtitles
            // 
            this.cbSubtitles.AutoSize = true;
            this.cbSubtitles.Location = new System.Drawing.Point(13, 67);
            this.cbSubtitles.Name = "cbSubtitles";
            this.cbSubtitles.Size = new System.Drawing.Size(102, 19);
            this.cbSubtitles.TabIndex = 3;
            this.cbSubtitles.Text = "Show subtitles";
            // 
            // gbMsgs
            // 
            this.gbMsgs.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbMsgs.Controls.Add(this.cbDisplayMessages);
            this.gbMsgs.Controls.Add(this.udMsgsTime);
            this.gbMsgs.Controls.Add(this.cmbMsgsLocale);
            this.gbMsgs.Controls.Add(this.lMsgsTime);
            this.gbMsgs.Controls.Add(this.lMsgsLanguage);
            this.gbMsgs.Controls.Add(this.lMsgsTimeUnit);
            this.gbMsgs.Location = new System.Drawing.Point(8, 395);
            this.gbMsgs.Name = "gbMsgs";
            this.gbMsgs.Size = new System.Drawing.Size(700, 66);
            this.gbMsgs.TabIndex = 8;
            this.gbMsgs.TabStop = false;
            this.gbMsgs.Text = "MGE status messages";
            // 
            // cbDisplayMessages
            // 
            this.cbDisplayMessages.AutoSize = true;
            this.cbDisplayMessages.Location = new System.Drawing.Point(13, 30);
            this.cbDisplayMessages.Name = "cbDisplayMessages";
            this.cbDisplayMessages.Size = new System.Drawing.Size(118, 19);
            this.cbDisplayMessages.TabIndex = 11;
            this.cbDisplayMessages.Text = "Display messages";
            // 
            // udMsgsTime
            // 
            this.udMsgsTime.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.udMsgsTime.Increment = new decimal(new int[] {
                                    500,
                                    0,
                                    0,
                                    0});
            this.udMsgsTime.Location = new System.Drawing.Point(503, 34);
            this.udMsgsTime.Maximum = new decimal(new int[] {
                                    50000,
                                    0,
                                    0,
                                    0});
            this.udMsgsTime.Minimum = new decimal(new int[] {
                                    500,
                                    0,
                                    0,
                                    0});
            this.udMsgsTime.Name = "udMsgsTime";
            this.udMsgsTime.Size = new System.Drawing.Size(56, 23);
            this.udMsgsTime.TabIndex = 1;
            this.udMsgsTime.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udMsgsTime.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            this.udMsgsTime.Value = new decimal(new int[] {
                                    5000,
                                    0,
                                    0,
                                    0});
            // 
            // cmbMsgsLocale
            // 
            this.cmbMsgsLocale.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cmbMsgsLocale.Enabled = false;
            this.cmbMsgsLocale.FormattingEnabled = true;
            this.cmbMsgsLocale.Items.AddRange(new object[] {
                                    "English (default)"});
            this.cmbMsgsLocale.Location = new System.Drawing.Point(250, 34);
            this.cmbMsgsLocale.Name = "cmbMsgsLocale";
            this.cmbMsgsLocale.Size = new System.Drawing.Size(128, 23);
            this.cmbMsgsLocale.Sorted = true;
            this.cmbMsgsLocale.TabIndex = 0;
            this.cmbMsgsLocale.Text = "English (default)";
            // 
            // lMsgsTime
            // 
            this.lMsgsTime.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lMsgsTime.AutoSize = true;
            this.lMsgsTime.Location = new System.Drawing.Point(503, 16);
            this.lMsgsTime.Name = "lMsgsTime";
            this.lMsgsTime.Size = new System.Drawing.Size(52, 15);
            this.lMsgsTime.TabIndex = 0;
            this.lMsgsTime.Text = "Timeout";
            // 
            // lMsgsLanguage
            // 
            this.lMsgsLanguage.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.lMsgsLanguage.AutoSize = true;
            this.lMsgsLanguage.Enabled = false;
            this.lMsgsLanguage.Location = new System.Drawing.Point(250, 16);
            this.lMsgsLanguage.Name = "lMsgsLanguage";
            this.lMsgsLanguage.Size = new System.Drawing.Size(122, 15);
            this.lMsgsLanguage.TabIndex = 0;
            this.lMsgsLanguage.Text = "Language localization";
            // 
            // lMsgsTimeUnit
            // 
            this.lMsgsTimeUnit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lMsgsTimeUnit.AutoSize = true;
            this.lMsgsTimeUnit.Location = new System.Drawing.Point(564, 36);
            this.lMsgsTimeUnit.Name = "lMsgsTimeUnit";
            this.lMsgsTimeUnit.Size = new System.Drawing.Size(23, 15);
            this.lMsgsTimeUnit.TabIndex = 0;
            this.lMsgsTimeUnit.Text = "ms";
            // 
            // pCam3rdPrsn
            // 
            this.pCam3rdPrsn.Controls.Add(this.cbCam3rdPrsn);
            this.pCam3rdPrsn.Controls.Add(this.gbCam3rdPrsn);
            this.pCam3rdPrsn.Location = new System.Drawing.Point(8, 129);
            this.pCam3rdPrsn.Name = "pCam3rdPrsn";
            this.pCam3rdPrsn.Size = new System.Drawing.Size(276, 72);
            this.pCam3rdPrsn.TabIndex = 7;
            this.pCam3rdPrsn.TabStop = true;
            // 
            // cbCam3rdPrsn
            // 
            this.cbCam3rdPrsn.AutoSize = true;
            this.cbCam3rdPrsn.Location = new System.Drawing.Point(8, -1);
            this.cbCam3rdPrsn.Name = "cbCam3rdPrsn";
            this.cbCam3rdPrsn.Size = new System.Drawing.Size(183, 19);
            this.cbCam3rdPrsn.TabIndex = 0;
            this.cbCam3rdPrsn.Text = "Customize 3rd person camera";
            this.cbCam3rdPrsn.UseVisualStyleBackColor = false;
            this.cbCam3rdPrsn.CheckedChanged += new System.EventHandler(this.cbCam3rdPrsn_CheckedChanged);
            // 
            // gbCam3rdPrsn
            // 
            this.gbCam3rdPrsn.Controls.Add(this.udCam3rdZ);
            this.gbCam3rdPrsn.Controls.Add(this.udCam3rdY);
            this.gbCam3rdPrsn.Controls.Add(this.udCam3rdX);
            this.gbCam3rdPrsn.Controls.Add(this.lCam3rdX);
            this.gbCam3rdPrsn.Controls.Add(this.lCam3rdY);
            this.gbCam3rdPrsn.Controls.Add(this.lCam3rdZ);
            this.gbCam3rdPrsn.Dock = System.Windows.Forms.DockStyle.Top;
            this.gbCam3rdPrsn.Enabled = false;
            this.gbCam3rdPrsn.Location = new System.Drawing.Point(0, 0);
            this.gbCam3rdPrsn.Name = "gbCam3rdPrsn";
            this.gbCam3rdPrsn.Size = new System.Drawing.Size(276, 72);
            this.gbCam3rdPrsn.TabIndex = 1;
            this.gbCam3rdPrsn.TabStop = false;
            // 
            // udCam3rdZ
            // 
            this.udCam3rdZ.DecimalPlaces = 1;
            this.udCam3rdZ.Location = new System.Drawing.Point(169, 39);
            this.udCam3rdZ.Maximum = new decimal(new int[] {
                                    125,
                                    0,
                                    0,
                                    0});
            this.udCam3rdZ.Minimum = new decimal(new int[] {
                                    125,
                                    0,
                                    0,
                                    -2147483648});
            this.udCam3rdZ.Name = "udCam3rdZ";
            this.udCam3rdZ.Size = new System.Drawing.Size(60, 23);
            this.udCam3rdZ.TabIndex = 2;
            this.udCam3rdZ.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udCam3rdZ.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            // 
            // udCam3rdY
            // 
            this.udCam3rdY.DecimalPlaces = 1;
            this.udCam3rdY.Increment = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    0});
            this.udCam3rdY.Location = new System.Drawing.Point(91, 39);
            this.udCam3rdY.Maximum = new decimal(new int[] {
                                    25,
                                    0,
                                    0,
                                    -2147483648});
            this.udCam3rdY.Minimum = new decimal(new int[] {
                                    2500,
                                    0,
                                    0,
                                    -2147483648});
            this.udCam3rdY.Name = "udCam3rdY";
            this.udCam3rdY.Size = new System.Drawing.Size(60, 23);
            this.udCam3rdY.TabIndex = 1;
            this.udCam3rdY.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udCam3rdY.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            this.udCam3rdY.Value = new decimal(new int[] {
                                    160,
                                    0,
                                    0,
                                    -2147483648});
            // 
            // udCam3rdX
            // 
            this.udCam3rdX.DecimalPlaces = 1;
            this.udCam3rdX.Location = new System.Drawing.Point(13, 39);
            this.udCam3rdX.Maximum = new decimal(new int[] {
                                    125,
                                    0,
                                    0,
                                    0});
            this.udCam3rdX.Minimum = new decimal(new int[] {
                                    125,
                                    0,
                                    0,
                                    -2147483648});
            this.udCam3rdX.Name = "udCam3rdX";
            this.udCam3rdX.Size = new System.Drawing.Size(60, 23);
            this.udCam3rdX.TabIndex = 0;
            this.udCam3rdX.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udCam3rdX.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            // 
            // lCam3rdX
            // 
            this.lCam3rdX.AutoSize = true;
            this.lCam3rdX.Location = new System.Drawing.Point(11, 21);
            this.lCam3rdX.Name = "lCam3rdX";
            this.lCam3rdX.Size = new System.Drawing.Size(47, 15);
            this.lCam3rdX.TabIndex = 3;
            this.lCam3rdX.Text = "X offset";
            // 
            // lCam3rdY
            // 
            this.lCam3rdY.AutoSize = true;
            this.lCam3rdY.Location = new System.Drawing.Point(89, 21);
            this.lCam3rdY.Name = "lCam3rdY";
            this.lCam3rdY.Size = new System.Drawing.Size(47, 15);
            this.lCam3rdY.TabIndex = 4;
            this.lCam3rdY.Text = "Y offset";
            // 
            // lCam3rdZ
            // 
            this.lCam3rdZ.AutoSize = true;
            this.lCam3rdZ.Location = new System.Drawing.Point(167, 21);
            this.lCam3rdZ.Name = "lCam3rdZ";
            this.lCam3rdZ.Size = new System.Drawing.Size(47, 15);
            this.lCam3rdZ.TabIndex = 5;
            this.lCam3rdZ.Text = "Z offset";
            // 
            // gbInputTools
            // 
            this.gbInputTools.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.gbInputTools.Controls.Add(this.bMacroEd);
            this.gbInputTools.Controls.Add(this.bRemapper);
            this.gbInputTools.Location = new System.Drawing.Point(524, 3);
            this.gbInputTools.Name = "gbInputTools";
            this.gbInputTools.Size = new System.Drawing.Size(184, 119);
            this.gbInputTools.TabIndex = 1;
            this.gbInputTools.TabStop = false;
            this.gbInputTools.Text = "Input tools";
            // 
            // bMacroEd
            // 
            this.bMacroEd.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.bMacroEd.AutoSize = true;
            this.bMacroEd.Location = new System.Drawing.Point(6, 19);
            this.bMacroEd.Name = "bMacroEd";
            this.bMacroEd.Size = new System.Drawing.Size(172, 33);
            this.bMacroEd.TabIndex = 0;
            this.bMacroEd.Text = "Macro editor";
            this.bMacroEd.Click += new System.EventHandler(this.bMacroEd_Click);
            // 
            // bRemapper
            // 
            this.bRemapper.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.bRemapper.AutoSize = true;
            this.bRemapper.Location = new System.Drawing.Point(6, 60);
            this.bRemapper.Name = "bRemapper";
            this.bRemapper.Size = new System.Drawing.Size(172, 33);
            this.bRemapper.TabIndex = 1;
            this.bRemapper.Text = "Key remapper";
            this.bRemapper.Click += new System.EventHandler(this.bRemapper_Click);
            // 
            // gbInputOpts
            // 
            this.gbInputOpts.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbInputOpts.Controls.Add(this.cbD3D8To9Only);
            this.gbInputOpts.Controls.Add(this.cbMenuCaching);
            this.gbInputOpts.Controls.Add(this.cbAutoCrosshair);
            this.gbInputOpts.Controls.Add(this.cbDisableMGE);
            this.gbInputOpts.Controls.Add(this.cbDisableMWSE);
            this.gbInputOpts.Controls.Add(this.cbSkipMovie);
            this.gbInputOpts.Controls.Add(this.cbAltCombat);
            this.gbInputOpts.Location = new System.Drawing.Point(8, 3);
            this.gbInputOpts.Name = "gbInputOpts";
            this.gbInputOpts.Size = new System.Drawing.Size(510, 119);
            this.gbInputOpts.TabIndex = 0;
            this.gbInputOpts.TabStop = false;
            this.gbInputOpts.Text = "Options";
            // 
            // cbD3D8To9Only
            // 
            this.cbD3D8To9Only.AutoSize = true;
            this.cbD3D8To9Only.Location = new System.Drawing.Point(11, 77);
            this.cbD3D8To9Only.Name = "cbD3D8To9Only";
            this.cbD3D8To9Only.Size = new System.Drawing.Size(154, 19);
            this.cbD3D8To9Only.TabIndex = 12;
            this.cbD3D8To9Only.Text = "Use D3D8To9 proxy only";
            this.cbD3D8To9Only.UseVisualStyleBackColor = true;
            // 
            // cbMenuCaching
            // 
            this.cbMenuCaching.AutoSize = true;
            this.cbMenuCaching.Checked = true;
            this.cbMenuCaching.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbMenuCaching.Location = new System.Drawing.Point(182, 88);
            this.cbMenuCaching.Name = "cbMenuCaching";
            this.cbMenuCaching.Size = new System.Drawing.Size(164, 19);
            this.cbMenuCaching.TabIndex = 11;
            this.cbMenuCaching.Text = "Responsive menu caching";
            this.cbMenuCaching.UseVisualStyleBackColor = true;
            // 
            // cbAutoCrosshair
            // 
            this.cbAutoCrosshair.AutoSize = true;
            this.cbAutoCrosshair.Location = new System.Drawing.Point(182, 65);
            this.cbAutoCrosshair.Name = "cbAutoCrosshair";
            this.cbAutoCrosshair.Size = new System.Drawing.Size(125, 19);
            this.cbAutoCrosshair.TabIndex = 10;
            this.cbAutoCrosshair.Text = "Crosshair autohide";
            this.cbAutoCrosshair.UseVisualStyleBackColor = true;
            // 
            // cbDisableMGE
            // 
            this.cbDisableMGE.AutoSize = true;
            this.cbDisableMGE.Location = new System.Drawing.Point(11, 19);
            this.cbDisableMGE.Name = "cbDisableMGE";
            this.cbDisableMGE.Size = new System.Drawing.Size(138, 19);
            this.cbDisableMGE.TabIndex = 9;
            this.cbDisableMGE.Text = "Disable MGE in game";
            this.cbDisableMGE.UseVisualStyleBackColor = true;
            this.cbDisableMGE.CheckedChanged += new System.EventHandler(this.cbDisableMGE_CheckedChanged);
            // 
            // cbDisableMWSE
            // 
            this.cbDisableMWSE.AutoSize = true;
            this.cbDisableMWSE.Location = new System.Drawing.Point(11, 42);
            this.cbDisableMWSE.Name = "cbDisableMWSE";
            this.cbDisableMWSE.Size = new System.Drawing.Size(144, 19);
            this.cbDisableMWSE.TabIndex = 8;
            this.cbDisableMWSE.Text = "Disable internal MWSE";
            // 
            // cbSkipMovie
            // 
            this.cbSkipMovie.AutoSize = true;
            this.cbSkipMovie.Checked = true;
            this.cbSkipMovie.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbSkipMovie.Location = new System.Drawing.Point(182, 19);
            this.cbSkipMovie.Name = "cbSkipMovie";
            this.cbSkipMovie.Size = new System.Drawing.Size(131, 19);
            this.cbSkipMovie.TabIndex = 0;
            this.cbSkipMovie.Text = "Skip opening movie";
            // 
            // cbAltCombat
            // 
            this.cbAltCombat.AutoSize = true;
            this.cbAltCombat.Location = new System.Drawing.Point(182, 42);
            this.cbAltCombat.Name = "cbAltCombat";
            this.cbAltCombat.Size = new System.Drawing.Size(173, 19);
            this.cbAltCombat.TabIndex = 2;
            this.cbAltCombat.Text = "Alternative combat controls";
            // 
            // lSShotFormat
            // 
            this.lSShotFormat.AutoSize = true;
            this.lSShotFormat.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSShotFormat.Location = new System.Drawing.Point(30, 0);
            this.lSShotFormat.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.lSShotFormat.Name = "lSShotFormat";
            this.lSShotFormat.Size = new System.Drawing.Size(45, 27);
            this.lSShotFormat.TabIndex = 0;
            this.lSShotFormat.Text = "Format";
            this.lSShotFormat.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // cmbSShotFormat
            // 
            this.cmbSShotFormat.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cmbSShotFormat.Items.AddRange(new object[] {
                                    "BMP",
                                    "JPEG",
                                    "DDS",
                                    "PNG",
                                    "TGA"});
            this.cmbSShotFormat.Location = new System.Drawing.Point(81, 3);
            this.cmbSShotFormat.Name = "cmbSShotFormat";
            this.cmbSShotFormat.Size = new System.Drawing.Size(56, 23);
            this.cmbSShotFormat.TabIndex = 1;
            this.cmbSShotFormat.Text = "PNG";
            // 
            // tpGlobal
            // 
            this.tpGlobal.Controls.Add(this.gbSShot);
            this.tpGlobal.Controls.Add(this.gbScene);
            this.tpGlobal.Controls.Add(this.gbDisplay);
            this.tpGlobal.Location = new System.Drawing.Point(4, 24);
            this.tpGlobal.Name = "tpGlobal";
            this.tpGlobal.Size = new System.Drawing.Size(716, 473);
            this.tpGlobal.TabIndex = 1;
            this.tpGlobal.Text = "Graphics";
            this.tpGlobal.ToolTipText = "Contains graphics settings like screen size, \nrefresh rate, anti-aliasing, and sh" +
            "aders.";
            this.tpGlobal.UseVisualStyleBackColor = true;
            // 
            // gbSShot
            // 
            this.gbSShot.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbSShot.Controls.Add(this.tableLayoutScreenshots);
            this.gbSShot.Location = new System.Drawing.Point(8, 290);
            this.gbSShot.Name = "gbSShot";
            this.gbSShot.Size = new System.Drawing.Size(700, 177);
            this.gbSShot.TabIndex = 2;
            this.gbSShot.TabStop = false;
            this.gbSShot.Text = "Screenshots";
            // 
            // tableLayoutScreenshots
            // 
            this.tableLayoutScreenshots.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutScreenshots.AutoSize = true;
            this.tableLayoutScreenshots.ColumnCount = 3;
            this.tableLayoutScreenshots.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 105F));
            this.tableLayoutScreenshots.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutScreenshots.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutScreenshots.Controls.Add(this.tableAlignSSFormat, 2, 0);
            this.tableLayoutScreenshots.Controls.Add(this.lSShotName, 0, 0);
            this.tableLayoutScreenshots.Controls.Add(this.tbSShotName, 1, 0);
            this.tableLayoutScreenshots.Controls.Add(this.lSShotDir, 0, 4);
            this.tableLayoutScreenshots.Controls.Add(this.tbSShotDir, 1, 4);
            this.tableLayoutScreenshots.Controls.Add(this.lSShotSuffix, 0, 2);
            this.tableLayoutScreenshots.Controls.Add(this.cmbSShotSuffix, 1, 2);
            this.tableLayoutScreenshots.Controls.Add(this.lScreenshotHelp, 0, 5);
            this.tableLayoutScreenshots.Controls.Add(this.panelSShotDirButtons, 2, 4);
            this.tableLayoutScreenshots.Location = new System.Drawing.Point(6, 22);
            this.tableLayoutScreenshots.Name = "tableLayoutScreenshots";
            this.tableLayoutScreenshots.RowCount = 6;
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 4F));
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 4F));
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutScreenshots.Size = new System.Drawing.Size(688, 153);
            this.tableLayoutScreenshots.TabIndex = 6;
            // 
            // tableAlignSSFormat
            // 
            this.tableAlignSSFormat.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.tableAlignSSFormat.AutoSize = true;
            this.tableAlignSSFormat.ColumnCount = 2;
            this.tableAlignSSFormat.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableAlignSSFormat.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableAlignSSFormat.Controls.Add(this.cmbSShotFormat, 1, 0);
            this.tableAlignSSFormat.Controls.Add(this.lSShotFormat, 0, 0);
            this.tableAlignSSFormat.Location = new System.Drawing.Point(548, 0);
            this.tableAlignSSFormat.Margin = new System.Windows.Forms.Padding(0);
            this.tableAlignSSFormat.MinimumSize = new System.Drawing.Size(140, 29);
            this.tableAlignSSFormat.Name = "tableAlignSSFormat";
            this.tableAlignSSFormat.RowCount = 1;
            this.tableAlignSSFormat.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableAlignSSFormat.Size = new System.Drawing.Size(140, 29);
            this.tableAlignSSFormat.TabIndex = 7;
            // 
            // lSShotName
            // 
            this.lSShotName.AutoSize = true;
            this.lSShotName.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSShotName.Location = new System.Drawing.Point(12, 0);
            this.lSShotName.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.lSShotName.Name = "lSShotName";
            this.lSShotName.Size = new System.Drawing.Size(90, 27);
            this.lSShotName.TabIndex = 0;
            this.lSShotName.Text = "File name prefix";
            this.lSShotName.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // tbSShotName
            // 
            this.tbSShotName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.tbSShotName.Location = new System.Drawing.Point(108, 3);
            this.tbSShotName.Name = "tbSShotName";
            this.tbSShotName.Size = new System.Drawing.Size(424, 23);
            this.tbSShotName.TabIndex = 0;
            this.tbSShotName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.fileNameFilter_KeyPress);
            // 
            // lSShotDir
            // 
            this.lSShotDir.AutoSize = true;
            this.lSShotDir.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSShotDir.Location = new System.Drawing.Point(7, 66);
            this.lSShotDir.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.lSShotDir.Name = "lSShotDir";
            this.lSShotDir.Size = new System.Drawing.Size(95, 27);
            this.lSShotDir.TabIndex = 0;
            this.lSShotDir.Text = "Output directory";
            this.lSShotDir.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // tbSShotDir
            // 
            this.tbSShotDir.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.tbSShotDir.Location = new System.Drawing.Point(108, 69);
            this.tbSShotDir.Name = "tbSShotDir";
            this.tbSShotDir.ReadOnly = true;
            this.tbSShotDir.Size = new System.Drawing.Size(424, 23);
            this.tbSShotDir.TabIndex = 3;
            this.tbSShotDir.Text = "- Morrowind folder -";
            this.tbSShotDir.TextAlignChanged += new System.EventHandler(this.tbSSDir_TextAlignChanged);
            // 
            // lSShotSuffix
            // 
            this.lSShotSuffix.AutoSize = true;
            this.lSShotSuffix.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSShotSuffix.Location = new System.Drawing.Point(13, 33);
            this.lSShotSuffix.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.lSShotSuffix.Name = "lSShotSuffix";
            this.lSShotSuffix.Size = new System.Drawing.Size(89, 27);
            this.lSShotSuffix.TabIndex = 4;
            this.lSShotSuffix.Text = "File name suffix";
            this.lSShotSuffix.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // cmbSShotSuffix
            // 
            this.cmbSShotSuffix.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbSShotSuffix.FormattingEnabled = true;
            this.cmbSShotSuffix.Items.AddRange(new object[] {
                                    "Timestamp",
                                    "Ordinal",
                                    "Character and Ordinal",
                                    "Character, Game time, Ordinal"});
            this.cmbSShotSuffix.Location = new System.Drawing.Point(108, 36);
            this.cmbSShotSuffix.Name = "cmbSShotSuffix";
            this.cmbSShotSuffix.Size = new System.Drawing.Size(424, 23);
            this.cmbSShotSuffix.TabIndex = 5;
            this.cmbSShotSuffix.Text = "Timestamp";
            // 
            // lScreenshotHelp
            // 
            this.lScreenshotHelp.AutoSize = true;
            this.tableLayoutScreenshots.SetColumnSpan(this.lScreenshotHelp, 3);
            this.lScreenshotHelp.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lScreenshotHelp.Location = new System.Drawing.Point(8, 95);
            this.lScreenshotHelp.Margin = new System.Windows.Forms.Padding(8, 0, 22, 0);
            this.lScreenshotHelp.Name = "lScreenshotHelp";
            this.lScreenshotHelp.Size = new System.Drawing.Size(658, 58);
            this.lScreenshotHelp.TabIndex = 6;
            this.lScreenshotHelp.Text = "Screenshots can be taken in-game with the PrintScreen key.";
            this.lScreenshotHelp.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // panelSShotDirButtons
            // 
            this.panelSShotDirButtons.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.panelSShotDirButtons.AutoSize = true;
            this.panelSShotDirButtons.Controls.Add(this.bSShotDirBrowse);
            this.panelSShotDirButtons.Controls.Add(this.bSShotDirClear);
            this.panelSShotDirButtons.Location = new System.Drawing.Point(535, 66);
            this.panelSShotDirButtons.Margin = new System.Windows.Forms.Padding(0);
            this.panelSShotDirButtons.Name = "panelSShotDirButtons";
            this.panelSShotDirButtons.Size = new System.Drawing.Size(153, 29);
            this.panelSShotDirButtons.TabIndex = 8;
            // 
            // bSShotDirBrowse
            // 
            this.bSShotDirBrowse.Location = new System.Drawing.Point(4, 3);
            this.bSShotDirBrowse.Name = "bSShotDirBrowse";
            this.bSShotDirBrowse.Size = new System.Drawing.Size(70, 23);
            this.bSShotDirBrowse.TabIndex = 4;
            this.bSShotDirBrowse.Text = "Browse";
            this.bSShotDirBrowse.UseVisualStyleBackColor = true;
            this.bSShotDirBrowse.Click += new System.EventHandler(this.bSShotDirBrowse_Click);
            // 
            // bSShotDirClear
            // 
            this.bSShotDirClear.Location = new System.Drawing.Point(80, 3);
            this.bSShotDirClear.Name = "bSShotDirClear";
            this.bSShotDirClear.Size = new System.Drawing.Size(70, 23);
            this.bSShotDirClear.TabIndex = 5;
            this.bSShotDirClear.Text = "Clear";
            this.bSShotDirClear.UseVisualStyleBackColor = true;
            this.bSShotDirClear.Click += new System.EventHandler(this.bSSDirClear_Click);
            // 
            // gbScene
            // 
            this.gbScene.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbScene.Controls.Add(this.cbReduceTextureMemUse);
            this.gbScene.Controls.Add(this.cbAutoFOV);
            this.gbScene.Controls.Add(this.udUIScale);
            this.gbScene.Controls.Add(this.lUIScale);
            this.gbScene.Controls.Add(this.lFPSLimit);
            this.gbScene.Controls.Add(this.udFPSLimit);
            this.gbScene.Controls.Add(this.bShaderEd);
            this.gbScene.Controls.Add(this.cmbFogMode);
            this.gbScene.Controls.Add(this.lFogMode);
            this.gbScene.Controls.Add(this.cbHWShader);
            this.gbScene.Controls.Add(this.cbFPSCounter);
            this.gbScene.Controls.Add(this.udFOV);
            this.gbScene.Controls.Add(this.lFOV);
            this.gbScene.Location = new System.Drawing.Point(8, 142);
            this.gbScene.Name = "gbScene";
            this.gbScene.Size = new System.Drawing.Size(700, 142);
            this.gbScene.TabIndex = 1;
            this.gbScene.TabStop = false;
            this.gbScene.Text = "Renderer";
            // 
            // cbReduceTextureMemUse
            // 
            this.cbReduceTextureMemUse.AutoSize = true;
            this.cbReduceTextureMemUse.Location = new System.Drawing.Point(12, 86);
            this.cbReduceTextureMemUse.Name = "cbReduceTextureMemUse";
            this.cbReduceTextureMemUse.Size = new System.Drawing.Size(173, 19);
            this.cbReduceTextureMemUse.TabIndex = 24;
            this.cbReduceTextureMemUse.Text = "Reduce texture memory use";
            this.cbReduceTextureMemUse.UseVisualStyleBackColor = true;
            // 
            // cbAutoFOV
            // 
            this.cbAutoFOV.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbAutoFOV.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbAutoFOV.Location = new System.Drawing.Point(325, 24);
            this.cbAutoFOV.Name = "cbAutoFOV";
            this.cbAutoFOV.Size = new System.Drawing.Size(120, 24);
            this.cbAutoFOV.TabIndex = 20;
            this.cbAutoFOV.Text = "Auto FOV";
            this.cbAutoFOV.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbAutoFOV.UseVisualStyleBackColor = true;
            this.cbAutoFOV.CheckedChanged += new System.EventHandler(this.cbAutoFOV_CheckedChanged);
            // 
            // udUIScale
            // 
            this.udUIScale.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.udUIScale.DecimalPlaces = 2;
            this.udUIScale.Increment = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    131072});
            this.udUIScale.Location = new System.Drawing.Point(456, 103);
            this.udUIScale.Maximum = new decimal(new int[] {
                                    4,
                                    0,
                                    0,
                                    0});
            this.udUIScale.Minimum = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    65536});
            this.udUIScale.Name = "udUIScale";
            this.udUIScale.Size = new System.Drawing.Size(65, 23);
            this.udUIScale.TabIndex = 23;
            this.udUIScale.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udUIScale.Value = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    0});
            // 
            // lUIScale
            // 
            this.lUIScale.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.lUIScale.AutoSize = true;
            this.lUIScale.Location = new System.Drawing.Point(527, 105);
            this.lUIScale.Name = "lUIScale";
            this.lUIScale.Size = new System.Drawing.Size(92, 15);
            this.lUIScale.TabIndex = 22;
            this.lUIScale.Text = "Menu UI scaling";
            // 
            // lFPSLimit
            // 
            this.lFPSLimit.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.lFPSLimit.AutoSize = true;
            this.lFPSLimit.Location = new System.Drawing.Point(527, 52);
            this.lFPSLimit.Name = "lFPSLimit";
            this.lFPSLimit.Size = new System.Drawing.Size(63, 15);
            this.lFPSLimit.TabIndex = 19;
            this.lFPSLimit.Text = "FPS limiter";
            // 
            // udFPSLimit
            // 
            this.udFPSLimit.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.udFPSLimit.Location = new System.Drawing.Point(457, 50);
            this.udFPSLimit.Maximum = new decimal(new int[] {
                                    240,
                                    0,
                                    0,
                                    0});
            this.udFPSLimit.Minimum = new decimal(new int[] {
                                    15,
                                    0,
                                    0,
                                    0});
            this.udFPSLimit.Name = "udFPSLimit";
            this.udFPSLimit.Size = new System.Drawing.Size(64, 23);
            this.udFPSLimit.TabIndex = 18;
            this.udFPSLimit.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udFPSLimit.Value = new decimal(new int[] {
                                    144,
                                    0,
                                    0,
                                    0});
            // 
            // bShaderEd
            // 
            this.bShaderEd.AutoSize = true;
            this.bShaderEd.Location = new System.Drawing.Point(152, 22);
            this.bShaderEd.MinimumSize = new System.Drawing.Size(124, 25);
            this.bShaderEd.Name = "bShaderEd";
            this.bShaderEd.Size = new System.Drawing.Size(124, 25);
            this.bShaderEd.TabIndex = 17;
            this.bShaderEd.Text = "Shader setup...";
            this.bShaderEd.Click += new System.EventHandler(this.bShaderEd_Click);
            // 
            // cmbFogMode
            // 
            this.cmbFogMode.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cmbFogMode.Items.AddRange(new object[] {
                                    "Depth pixel (Fast)",
                                    "Depth vertex",
                                    "Range vertex (Best)"});
            this.cmbFogMode.Location = new System.Drawing.Point(355, 76);
            this.cmbFogMode.Name = "cmbFogMode";
            this.cmbFogMode.Size = new System.Drawing.Size(166, 23);
            this.cmbFogMode.TabIndex = 13;
            this.cmbFogMode.Text = "Depth pixel (Fast)";
            this.cmbFogMode.SelectedIndexChanged += new System.EventHandler(this.cmbFogMode_SelectedIndexChanged);
            // 
            // lFogMode
            // 
            this.lFogMode.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.lFogMode.AutoSize = true;
            this.lFogMode.Location = new System.Drawing.Point(527, 79);
            this.lFogMode.Name = "lFogMode";
            this.lFogMode.Size = new System.Drawing.Size(61, 15);
            this.lFogMode.TabIndex = 12;
            this.lFogMode.Text = "Fog mode";
            // 
            // cbHWShader
            // 
            this.cbHWShader.AutoSize = true;
            this.cbHWShader.Location = new System.Drawing.Point(12, 27);
            this.cbHWShader.Name = "cbHWShader";
            this.cbHWShader.Size = new System.Drawing.Size(104, 19);
            this.cbHWShader.TabIndex = 14;
            this.cbHWShader.Text = "Enable shaders";
            // 
            // cbFPSCounter
            // 
            this.cbFPSCounter.AutoSize = true;
            this.cbFPSCounter.Location = new System.Drawing.Point(12, 61);
            this.cbFPSCounter.Name = "cbFPSCounter";
            this.cbFPSCounter.Size = new System.Drawing.Size(86, 19);
            this.cbFPSCounter.TabIndex = 5;
            this.cbFPSCounter.Text = "Display FPS";
            // 
            // udFOV
            // 
            this.udFOV.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.udFOV.DecimalPlaces = 1;
            this.udFOV.Location = new System.Drawing.Point(457, 24);
            this.udFOV.Maximum = new decimal(new int[] {
                                    170,
                                    0,
                                    0,
                                    0});
            this.udFOV.Minimum = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    0});
            this.udFOV.Name = "udFOV";
            this.udFOV.Size = new System.Drawing.Size(64, 23);
            this.udFOV.TabIndex = 4;
            this.udFOV.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udFOV.Value = new decimal(new int[] {
                                    75,
                                    0,
                                    0,
                                    0});
            // 
            // lFOV
            // 
            this.lFOV.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.lFOV.AutoSize = true;
            this.lFOV.Location = new System.Drawing.Point(527, 26);
            this.lFOV.Name = "lFOV";
            this.lFOV.Size = new System.Drawing.Size(60, 15);
            this.lFOV.TabIndex = 3;
            this.lFOV.Text = "Horz. FOV";
            // 
            // gbDisplay
            // 
            this.gbDisplay.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbDisplay.Controls.Add(this.tableLayoutWindowAlign);
            this.gbDisplay.Controls.Add(this.tableAlignResolution);
            this.gbDisplay.Controls.Add(this.cbBorderless);
            this.gbDisplay.Controls.Add(this.tbRefreshRate);
            this.gbDisplay.Controls.Add(this.tableLayoutDisplay);
            this.gbDisplay.Controls.Add(this.tbAspect);
            this.gbDisplay.Controls.Add(this.bSelectResolution);
            this.gbDisplay.Controls.Add(this.cbWindowed);
            this.gbDisplay.Controls.Add(this.tbResolution);
            this.gbDisplay.Controls.Add(this.lAspect);
            this.gbDisplay.Controls.Add(this.lRefreshRate);
            this.gbDisplay.Location = new System.Drawing.Point(8, 3);
            this.gbDisplay.Name = "gbDisplay";
            this.gbDisplay.Size = new System.Drawing.Size(700, 133);
            this.gbDisplay.TabIndex = 0;
            this.gbDisplay.TabStop = false;
            this.gbDisplay.Text = "Display";
            // 
            // tableLayoutWindowAlign
            // 
            this.tableLayoutWindowAlign.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutWindowAlign.AutoSize = true;
            this.tableLayoutWindowAlign.ColumnCount = 1;
            this.tableLayoutWindowAlign.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutWindowAlign.Controls.Add(this.panelWindowAlign, 0, 1);
            this.tableLayoutWindowAlign.Controls.Add(this.lWindowAlign, 0, 0);
            this.tableLayoutWindowAlign.Location = new System.Drawing.Point(588, 12);
            this.tableLayoutWindowAlign.Name = "tableLayoutWindowAlign";
            this.tableLayoutWindowAlign.RowCount = 2;
            this.tableLayoutWindowAlign.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutWindowAlign.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutWindowAlign.Size = new System.Drawing.Size(103, 77);
            this.tableLayoutWindowAlign.TabIndex = 11;
            // 
            // panelWindowAlign
            // 
            this.panelWindowAlign.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.panelWindowAlign.AutoSize = true;
            this.panelWindowAlign.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignBottomRight);
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignCenterRight);
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignTopRight);
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignBottomCenter);
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignBottomLeft);
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignCenter);
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignCenterLeft);
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignCenterTop);
            this.panelWindowAlign.Controls.Add(this.rbWindowAlignTopLeft);
            this.panelWindowAlign.Location = new System.Drawing.Point(23, 18);
            this.panelWindowAlign.Name = "panelWindowAlign";
            this.panelWindowAlign.Size = new System.Drawing.Size(56, 56);
            this.panelWindowAlign.TabIndex = 10;
            // 
            // rbWindowAlignBottomRight
            // 
            this.rbWindowAlignBottomRight.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignBottomRight.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignBottomRight.Location = new System.Drawing.Point(36, 36);
            this.rbWindowAlignBottomRight.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignBottomRight.Name = "rbWindowAlignBottomRight";
            this.rbWindowAlignBottomRight.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignBottomRight.TabIndex = 8;
            this.rbWindowAlignBottomRight.Tag = "2,2";
            this.rbWindowAlignBottomRight.Text = "↘";
            this.rbWindowAlignBottomRight.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignBottomRight.UseVisualStyleBackColor = true;
            // 
            // rbWindowAlignCenterRight
            // 
            this.rbWindowAlignCenterRight.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignCenterRight.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignCenterRight.Location = new System.Drawing.Point(36, 18);
            this.rbWindowAlignCenterRight.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignCenterRight.Name = "rbWindowAlignCenterRight";
            this.rbWindowAlignCenterRight.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignCenterRight.TabIndex = 5;
            this.rbWindowAlignCenterRight.Tag = "1,2";
            this.rbWindowAlignCenterRight.Text = "→";
            this.rbWindowAlignCenterRight.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignCenterRight.UseVisualStyleBackColor = true;
            // 
            // rbWindowAlignTopRight
            // 
            this.rbWindowAlignTopRight.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignTopRight.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignTopRight.Location = new System.Drawing.Point(36, 0);
            this.rbWindowAlignTopRight.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignTopRight.Name = "rbWindowAlignTopRight";
            this.rbWindowAlignTopRight.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignTopRight.TabIndex = 2;
            this.rbWindowAlignTopRight.Tag = "2,0";
            this.rbWindowAlignTopRight.Text = "↗";
            this.rbWindowAlignTopRight.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignTopRight.UseVisualStyleBackColor = true;
            // 
            // rbWindowAlignBottomCenter
            // 
            this.rbWindowAlignBottomCenter.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignBottomCenter.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignBottomCenter.Location = new System.Drawing.Point(18, 36);
            this.rbWindowAlignBottomCenter.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignBottomCenter.Name = "rbWindowAlignBottomCenter";
            this.rbWindowAlignBottomCenter.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignBottomCenter.TabIndex = 7;
            this.rbWindowAlignBottomCenter.Tag = "1,2";
            this.rbWindowAlignBottomCenter.Text = "↓";
            this.rbWindowAlignBottomCenter.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignBottomCenter.UseVisualStyleBackColor = true;
            // 
            // rbWindowAlignBottomLeft
            // 
            this.rbWindowAlignBottomLeft.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignBottomLeft.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignBottomLeft.Location = new System.Drawing.Point(0, 36);
            this.rbWindowAlignBottomLeft.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignBottomLeft.Name = "rbWindowAlignBottomLeft";
            this.rbWindowAlignBottomLeft.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignBottomLeft.TabIndex = 6;
            this.rbWindowAlignBottomLeft.Tag = "0,2";
            this.rbWindowAlignBottomLeft.Text = "↙";
            this.rbWindowAlignBottomLeft.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignBottomLeft.UseVisualStyleBackColor = true;
            // 
            // rbWindowAlignCenter
            // 
            this.rbWindowAlignCenter.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignCenter.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignCenter.Location = new System.Drawing.Point(18, 18);
            this.rbWindowAlignCenter.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignCenter.Name = "rbWindowAlignCenter";
            this.rbWindowAlignCenter.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignCenter.TabIndex = 4;
            this.rbWindowAlignCenter.Tag = "1,1";
            this.rbWindowAlignCenter.Text = "▪";
            this.rbWindowAlignCenter.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignCenter.UseVisualStyleBackColor = true;
            // 
            // rbWindowAlignCenterLeft
            // 
            this.rbWindowAlignCenterLeft.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignCenterLeft.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignCenterLeft.Location = new System.Drawing.Point(0, 18);
            this.rbWindowAlignCenterLeft.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignCenterLeft.Name = "rbWindowAlignCenterLeft";
            this.rbWindowAlignCenterLeft.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignCenterLeft.TabIndex = 3;
            this.rbWindowAlignCenterLeft.Tag = "0,1";
            this.rbWindowAlignCenterLeft.Text = "←";
            this.rbWindowAlignCenterLeft.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignCenterLeft.UseVisualStyleBackColor = true;
            // 
            // rbWindowAlignCenterTop
            // 
            this.rbWindowAlignCenterTop.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignCenterTop.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignCenterTop.Location = new System.Drawing.Point(18, 0);
            this.rbWindowAlignCenterTop.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignCenterTop.Name = "rbWindowAlignCenterTop";
            this.rbWindowAlignCenterTop.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignCenterTop.TabIndex = 1;
            this.rbWindowAlignCenterTop.Tag = "1,0";
            this.rbWindowAlignCenterTop.Text = "↑";
            this.rbWindowAlignCenterTop.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignCenterTop.UseVisualStyleBackColor = true;
            // 
            // rbWindowAlignTopLeft
            // 
            this.rbWindowAlignTopLeft.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignTopLeft.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignTopLeft.Location = new System.Drawing.Point(0, 0);
            this.rbWindowAlignTopLeft.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignTopLeft.Name = "rbWindowAlignTopLeft";
            this.rbWindowAlignTopLeft.Size = new System.Drawing.Size(20, 20);
            this.rbWindowAlignTopLeft.TabIndex = 0;
            this.rbWindowAlignTopLeft.Tag = "0,0";
            this.rbWindowAlignTopLeft.Text = "↖";
            this.rbWindowAlignTopLeft.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.rbWindowAlignTopLeft.UseVisualStyleBackColor = true;
            // 
            // lWindowAlign
            // 
            this.lWindowAlign.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.lWindowAlign.AutoSize = true;
            this.lWindowAlign.Location = new System.Drawing.Point(3, 0);
            this.lWindowAlign.Name = "lWindowAlign";
            this.lWindowAlign.Size = new System.Drawing.Size(97, 15);
            this.lWindowAlign.TabIndex = 9;
            this.lWindowAlign.Text = "Window location";
            this.lWindowAlign.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // tableAlignResolution
            // 
            this.tableAlignResolution.ColumnCount = 1;
            this.tableAlignResolution.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableAlignResolution.Controls.Add(this.lResolution, 0, 0);
            this.tableAlignResolution.Location = new System.Drawing.Point(4, 22);
            this.tableAlignResolution.Name = "tableAlignResolution";
            this.tableAlignResolution.RowCount = 1;
            this.tableAlignResolution.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableAlignResolution.Size = new System.Drawing.Size(96, 23);
            this.tableAlignResolution.TabIndex = 8;
            // 
            // lResolution
            // 
            this.lResolution.AutoSize = true;
            this.lResolution.Dock = System.Windows.Forms.DockStyle.Right;
            this.lResolution.Location = new System.Drawing.Point(33, 0);
            this.lResolution.Margin = new System.Windows.Forms.Padding(0);
            this.lResolution.Name = "lResolution";
            this.lResolution.Size = new System.Drawing.Size(63, 23);
            this.lResolution.TabIndex = 0;
            this.lResolution.Text = "Resolution";
            this.lResolution.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // cbBorderless
            // 
            this.cbBorderless.AutoSize = true;
            this.cbBorderless.Enabled = false;
            this.cbBorderless.Location = new System.Drawing.Point(408, 53);
            this.cbBorderless.Name = "cbBorderless";
            this.cbBorderless.Size = new System.Drawing.Size(125, 19);
            this.cbBorderless.TabIndex = 7;
            this.cbBorderless.Text = "Borderless window";
            this.cbBorderless.UseVisualStyleBackColor = true;
            // 
            // tbRefreshRate
            // 
            this.tbRefreshRate.Location = new System.Drawing.Point(192, 51);
            this.tbRefreshRate.Name = "tbRefreshRate";
            this.tbRefreshRate.ReadOnly = true;
            this.tbRefreshRate.Size = new System.Drawing.Size(52, 23);
            this.tbRefreshRate.TabIndex = 6;
            this.tbRefreshRate.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tableLayoutDisplay
            // 
            this.tableLayoutDisplay.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutDisplay.AutoSize = true;
            this.tableLayoutDisplay.ColumnCount = 6;
            this.tableLayoutDisplay.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutDisplay.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutDisplay.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutDisplay.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutDisplay.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutDisplay.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutDisplay.Controls.Add(this.cmbAntiAlias, 0, 0);
            this.tableLayoutDisplay.Controls.Add(this.lAntiAlias, 1, 0);
            this.tableLayoutDisplay.Controls.Add(this.cmbVWait, 4, 0);
            this.tableLayoutDisplay.Controls.Add(this.cmbAnisoLevel, 2, 0);
            this.tableLayoutDisplay.Controls.Add(this.lAnisoLevel, 3, 0);
            this.tableLayoutDisplay.Controls.Add(this.lVWait, 5, 0);
            this.tableLayoutDisplay.Location = new System.Drawing.Point(10, 85);
            this.tableLayoutDisplay.Name = "tableLayoutDisplay";
            this.tableLayoutDisplay.RowCount = 1;
            this.tableLayoutDisplay.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 42F));
            this.tableLayoutDisplay.Size = new System.Drawing.Size(681, 42);
            this.tableLayoutDisplay.TabIndex = 0;
            // 
            // cmbAntiAlias
            // 
            this.cmbAntiAlias.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.cmbAntiAlias.ContextMenu = this.DudMenu;
            this.cmbAntiAlias.Items.AddRange(new object[] {
                                    "Off",
                                    "2x",
                                    "4x",
                                    "8x",
                                    "16x"});
            this.cmbAntiAlias.Location = new System.Drawing.Point(3, 9);
            this.cmbAntiAlias.Name = "cmbAntiAlias";
            this.cmbAntiAlias.Size = new System.Drawing.Size(64, 23);
            this.cmbAntiAlias.TabIndex = 0;
            this.cmbAntiAlias.Text = "Off";
            this.cmbAntiAlias.SelectedIndexChanged += new System.EventHandler(this.cmbAlias_SelectedIndexChanged);
            this.cmbAntiAlias.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
            // 
            // lAntiAlias
            // 
            this.lAntiAlias.AutoSize = true;
            this.lAntiAlias.Dock = System.Windows.Forms.DockStyle.Left;
            this.lAntiAlias.Location = new System.Drawing.Point(73, 0);
            this.lAntiAlias.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.lAntiAlias.Name = "lAntiAlias";
            this.lAntiAlias.Size = new System.Drawing.Size(69, 40);
            this.lAntiAlias.TabIndex = 0;
            this.lAntiAlias.Text = "Antialiasing";
            this.lAntiAlias.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // cmbVWait
            // 
            this.cmbVWait.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.cmbVWait.Items.AddRange(new object[] {
                                    "Off",
                                    "On",
                                    "x2",
                                    "x3",
                                    "x4"});
            this.cmbVWait.Location = new System.Drawing.Point(461, 9);
            this.cmbVWait.Name = "cmbVWait";
            this.cmbVWait.Size = new System.Drawing.Size(80, 23);
            this.cmbVWait.TabIndex = 2;
            this.cmbVWait.Text = "Off";
            this.cmbVWait.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
            // 
            // cmbAnisoLevel
            // 
            this.cmbAnisoLevel.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.cmbAnisoLevel.Items.AddRange(new object[] {
                                    "Off",
                                    "2x",
                                    "4x",
                                    "8x",
                                    "16x"});
            this.cmbAnisoLevel.Location = new System.Drawing.Point(209, 9);
            this.cmbAnisoLevel.Name = "cmbAnisoLevel";
            this.cmbAnisoLevel.Size = new System.Drawing.Size(64, 23);
            this.cmbAnisoLevel.TabIndex = 10;
            this.cmbAnisoLevel.Text = "Off";
            this.cmbAnisoLevel.SelectedIndexChanged += new System.EventHandler(this.cmbAnsiLevel_SelectedIndexChanged);
            // 
            // lAnisoLevel
            // 
            this.lAnisoLevel.AutoSize = true;
            this.lAnisoLevel.Dock = System.Windows.Forms.DockStyle.Left;
            this.lAnisoLevel.Location = new System.Drawing.Point(279, 0);
            this.lAnisoLevel.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.lAnisoLevel.Name = "lAnisoLevel";
            this.lAnisoLevel.Size = new System.Drawing.Size(112, 40);
            this.lAnisoLevel.TabIndex = 8;
            this.lAnisoLevel.Text = "Anisotropic filtering";
            this.lAnisoLevel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lVWait
            // 
            this.lVWait.AutoSize = true;
            this.lVWait.Dock = System.Windows.Forms.DockStyle.Left;
            this.lVWait.Location = new System.Drawing.Point(547, 0);
            this.lVWait.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
            this.lVWait.Name = "lVWait";
            this.lVWait.Size = new System.Drawing.Size(39, 40);
            this.lVWait.TabIndex = 0;
            this.lVWait.Text = "VSync";
            this.lVWait.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tbAspect
            // 
            this.tbAspect.Location = new System.Drawing.Point(192, 22);
            this.tbAspect.Name = "tbAspect";
            this.tbAspect.ReadOnly = true;
            this.tbAspect.Size = new System.Drawing.Size(52, 23);
            this.tbAspect.TabIndex = 2;
            this.tbAspect.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // bSelectResolution
            // 
            this.bSelectResolution.Location = new System.Drawing.Point(9, 50);
            this.bSelectResolution.Name = "bSelectResolution";
            this.bSelectResolution.Size = new System.Drawing.Size(178, 25);
            this.bSelectResolution.TabIndex = 1;
            this.bSelectResolution.Text = "Select screen resolution";
            this.bSelectResolution.Click += new System.EventHandler(this.bSelectResolution_Click);
            // 
            // cbWindowed
            // 
            this.cbWindowed.AutoSize = true;
            this.cbWindowed.Location = new System.Drawing.Point(408, 25);
            this.cbWindowed.Name = "cbWindowed";
            this.cbWindowed.Size = new System.Drawing.Size(117, 19);
            this.cbWindowed.TabIndex = 3;
            this.cbWindowed.Text = "Windowed mode";
            this.cbWindowed.CheckedChanged += new System.EventHandler(this.cbWindowed_CheckedChanged);
            // 
            // tbResolution
            // 
            this.tbResolution.Location = new System.Drawing.Point(106, 22);
            this.tbResolution.Name = "tbResolution";
            this.tbResolution.ReadOnly = true;
            this.tbResolution.Size = new System.Drawing.Size(80, 23);
            this.tbResolution.TabIndex = 0;
            this.tbResolution.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lAspect
            // 
            this.lAspect.AutoSize = true;
            this.lAspect.Location = new System.Drawing.Point(250, 25);
            this.lAspect.Name = "lAspect";
            this.lAspect.Size = new System.Drawing.Size(70, 15);
            this.lAspect.TabIndex = 0;
            this.lAspect.Text = "Aspect ratio";
            this.lAspect.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lRefreshRate
            // 
            this.lRefreshRate.AutoSize = true;
            this.lRefreshRate.Location = new System.Drawing.Point(250, 54);
            this.lRefreshRate.Name = "lRefreshRate";
            this.lRefreshRate.Size = new System.Drawing.Size(69, 15);
            this.lRefreshRate.TabIndex = 0;
            this.lRefreshRate.Text = "Refresh rate";
            this.lRefreshRate.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.tpGlobal);
            this.tabControl.Controls.Add(this.tpDL);
            this.tabControl.Controls.Add(this.tpInput);
            this.tabControl.Controls.Add(this.tpConfig);
            this.tabControl.Controls.Add(this.tpInstructions);
            this.tabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl.Location = new System.Drawing.Point(0, 0);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.ShowToolTips = true;
            this.tabControl.Size = new System.Drawing.Size(724, 501);
            this.tabControl.TabIndex = 0;
            // 
            // tpDL
            // 
            this.tpDL.Controls.Add(this.bDistantLandWizard);
            this.tpDL.Controls.Add(this.cbDLDistantLand);
            this.tpDL.Controls.Add(this.gbDistantLand);
            this.tpDL.Location = new System.Drawing.Point(4, 24);
            this.tpDL.Name = "tpDL";
            this.tpDL.Size = new System.Drawing.Size(716, 473);
            this.tpDL.TabIndex = 7;
            this.tpDL.Text = "Distant Land";
            this.tpDL.ToolTipText = "This tab controls whether and how distant land,\ndistant statics, animated grass, " +
            "reflective water\nare rendered, and also contains weather settings\nfor distant la" +
            "nd wind speed and fog range.";
            this.tpDL.UseVisualStyleBackColor = true;
            // 
            // bDistantLandWizard
            // 
            this.bDistantLandWizard.Location = new System.Drawing.Point(136, 42);
            this.bDistantLandWizard.Name = "bDistantLandWizard";
            this.bDistantLandWizard.Size = new System.Drawing.Size(134, 42);
            this.bDistantLandWizard.TabIndex = 10;
            this.bDistantLandWizard.Text = "Distant land generator wizard";
            this.bDistantLandWizard.Click += new System.EventHandler(this.bDistantLandWizard_Click);
            // 
            // cbDLDistantLand
            // 
            this.cbDLDistantLand.AutoSize = true;
            this.cbDLDistantLand.Location = new System.Drawing.Point(16, 3);
            this.cbDLDistantLand.Name = "cbDLDistantLand";
            this.cbDLDistantLand.Size = new System.Drawing.Size(114, 19);
            this.cbDLDistantLand.TabIndex = 0;
            this.cbDLDistantLand.Text = "Use Distant &Land";
            this.cbDLDistantLand.UseVisualStyleBackColor = true;
            this.cbDLDistantLand.CheckedChanged += new System.EventHandler(this.cbDistantLand_CheckedChanged);
            // 
            // gbDistantLand
            // 
            this.gbDistantLand.Controls.Add(this.tableLayoutDL);
            this.gbDistantLand.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbDistantLand.Enabled = false;
            this.gbDistantLand.Location = new System.Drawing.Point(0, 0);
            this.gbDistantLand.Name = "gbDistantLand";
            this.gbDistantLand.Padding = new System.Windows.Forms.Padding(3, 9, 3, 3);
            this.gbDistantLand.Size = new System.Drawing.Size(716, 473);
            this.gbDistantLand.TabIndex = 1;
            this.gbDistantLand.TabStop = false;
            // 
            // tableLayoutDL
            // 
            this.tableLayoutDL.ColumnCount = 2;
            this.tableLayoutDL.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 49F));
            this.tableLayoutDL.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 51F));
            this.tableLayoutDL.Controls.Add(this.tableLayoutDLLeft, 0, 0);
            this.tableLayoutDL.Controls.Add(this.tableLayoutDLRight, 1, 0);
            this.tableLayoutDL.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutDL.Location = new System.Drawing.Point(3, 25);
            this.tableLayoutDL.Name = "tableLayoutDL";
            this.tableLayoutDL.RowCount = 1;
            this.tableLayoutDL.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutDL.Size = new System.Drawing.Size(710, 445);
            this.tableLayoutDL.TabIndex = 12;
            // 
            // tableLayoutDLLeft
            // 
            this.tableLayoutDLLeft.ColumnCount = 1;
            this.tableLayoutDLLeft.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutDLLeft.Controls.Add(this.gbXEFeatures, 0, 2);
            this.tableLayoutDLLeft.Controls.Add(this.gbDLDrawDist, 0, 0);
            this.tableLayoutDLLeft.Controls.Add(this.gbDLWater, 0, 1);
            this.tableLayoutDLLeft.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutDLLeft.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutDLLeft.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutDLLeft.Name = "tableLayoutDLLeft";
            this.tableLayoutDLLeft.RowCount = 3;
            this.tableLayoutDLLeft.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutDLLeft.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutDLLeft.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutDLLeft.Size = new System.Drawing.Size(347, 445);
            this.tableLayoutDLLeft.TabIndex = 0;
            // 
            // gbXEFeatures
            // 
            this.gbXEFeatures.Controls.Add(this.cbDLSunShadows);
            this.gbXEFeatures.Controls.Add(this.cmbDLShadowDetail);
            this.gbXEFeatures.Controls.Add(this.cmbPerPixelLightFlags);
            this.gbXEFeatures.Controls.Add(this.cbPerPixelLighting);
            this.gbXEFeatures.Controls.Add(this.bMWLightSettings);
            this.gbXEFeatures.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbXEFeatures.Location = new System.Drawing.Point(3, 309);
            this.gbXEFeatures.Name = "gbXEFeatures";
            this.gbXEFeatures.Size = new System.Drawing.Size(341, 133);
            this.gbXEFeatures.TabIndex = 11;
            this.gbXEFeatures.TabStop = false;
            this.gbXEFeatures.Text = "XE";
            // 
            // cbDLSunShadows
            // 
            this.cbDLSunShadows.AutoSize = true;
            this.cbDLSunShadows.Location = new System.Drawing.Point(18, 25);
            this.cbDLSunShadows.Name = "cbDLSunShadows";
            this.cbDLSunShadows.Size = new System.Drawing.Size(150, 19);
            this.cbDLSunShadows.TabIndex = 0;
            this.cbDLSunShadows.Text = "Dynamic solar shadows";
            this.cbDLSunShadows.UseVisualStyleBackColor = true;
            // 
            // cmbDLShadowDetail
            // 
            this.cmbDLShadowDetail.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbDLShadowDetail.FormattingEnabled = true;
            this.cmbDLShadowDetail.Items.AddRange(new object[] {
                                    "medium",
                                    "high"});
            this.cmbDLShadowDetail.Location = new System.Drawing.Point(219, 24);
            this.cmbDLShadowDetail.Name = "cmbDLShadowDetail";
            this.cmbDLShadowDetail.Size = new System.Drawing.Size(116, 23);
            this.cmbDLShadowDetail.TabIndex = 12;
            this.cmbDLShadowDetail.Text = "medium";
            // 
            // cmbPerPixelLightFlags
            // 
            this.cmbPerPixelLightFlags.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbPerPixelLightFlags.Enabled = false;
            this.cmbPerPixelLightFlags.FormattingEnabled = true;
            this.cmbPerPixelLightFlags.Items.AddRange(new object[] {
                                    "always on",
                                    "interiors only"});
            this.cmbPerPixelLightFlags.Location = new System.Drawing.Point(200, 59);
            this.cmbPerPixelLightFlags.Name = "cmbPerPixelLightFlags";
            this.cmbPerPixelLightFlags.Size = new System.Drawing.Size(135, 23);
            this.cmbPerPixelLightFlags.TabIndex = 11;
            this.cmbPerPixelLightFlags.Text = "always on";
            // 
            // cbPerPixelLighting
            // 
            this.cbPerPixelLighting.Location = new System.Drawing.Point(18, 52);
            this.cbPerPixelLighting.Name = "cbPerPixelLighting";
            this.cbPerPixelLighting.Size = new System.Drawing.Size(165, 36);
            this.cbPerPixelLighting.TabIndex = 1;
            this.cbPerPixelLighting.Text = "Per-pixel lighting shader";
            this.cbPerPixelLighting.UseVisualStyleBackColor = true;
            this.cbPerPixelLighting.CheckedChanged += new System.EventHandler(this.cbPerPixelLighting_CheckedChanged);
            // 
            // bMWLightSettings
            // 
            this.bMWLightSettings.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.bMWLightSettings.Location = new System.Drawing.Point(89, 102);
            this.bMWLightSettings.Name = "bMWLightSettings";
            this.bMWLightSettings.Size = new System.Drawing.Size(160, 25);
            this.bMWLightSettings.TabIndex = 10;
            this.bMWLightSettings.Text = "Light Settings...";
            this.bMWLightSettings.UseVisualStyleBackColor = true;
            this.bMWLightSettings.Click += new System.EventHandler(this.bMWLightSettings_Click);
            // 
            // gbDLDrawDist
            // 
            this.gbDLDrawDist.Controls.Add(this.lDLDrawDist);
            this.gbDLDrawDist.Controls.Add(this.udDLDrawDist);
            this.gbDLDrawDist.Dock = System.Windows.Forms.DockStyle.Top;
            this.gbDLDrawDist.Location = new System.Drawing.Point(3, 3);
            this.gbDLDrawDist.Name = "gbDLDrawDist";
            this.gbDLDrawDist.Size = new System.Drawing.Size(341, 62);
            this.gbDLDrawDist.TabIndex = 0;
            this.gbDLDrawDist.TabStop = false;
            this.gbDLDrawDist.Text = "&Draw Distance";
            // 
            // lDLDrawDist
            // 
            this.lDLDrawDist.AutoSize = true;
            this.lDLDrawDist.Location = new System.Drawing.Point(62, 24);
            this.lDLDrawDist.Name = "lDLDrawDist";
            this.lDLDrawDist.Size = new System.Drawing.Size(30, 15);
            this.lDLDrawDist.TabIndex = 0;
            this.lDLDrawDist.Text = "cells";
            this.lDLDrawDist.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // udDLDrawDist
            // 
            this.udDLDrawDist.DecimalPlaces = 1;
            this.udDLDrawDist.Location = new System.Drawing.Point(6, 22);
            this.udDLDrawDist.Maximum = new decimal(new int[] {
                                    300,
                                    0,
                                    0,
                                    0});
            this.udDLDrawDist.Minimum = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    0});
            this.udDLDrawDist.Name = "udDLDrawDist";
            this.udDLDrawDist.Size = new System.Drawing.Size(50, 23);
            this.udDLDrawDist.TabIndex = 0;
            this.udDLDrawDist.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLDrawDist.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            this.udDLDrawDist.Value = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    0});
            this.udDLDrawDist.ValueChanged += new System.EventHandler(this.udDLDrawDist_ValueChanged);
            // 
            // gbDLWater
            // 
            this.gbDLWater.AutoSize = true;
            this.gbDLWater.Controls.Add(this.cbDLDynRipples);
            this.gbDLWater.Controls.Add(this.gbDLWtrCaust);
            this.gbDLWater.Controls.Add(this.gbDLWtrWave);
            this.gbDLWater.Controls.Add(this.gbDLWtrRefl);
            this.gbDLWater.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbDLWater.Location = new System.Drawing.Point(3, 71);
            this.gbDLWater.Name = "gbDLWater";
            this.gbDLWater.Size = new System.Drawing.Size(341, 232);
            this.gbDLWater.TabIndex = 9;
            this.gbDLWater.TabStop = false;
            this.gbDLWater.Text = "&Water";
            // 
            // cbDLDynRipples
            // 
            this.cbDLDynRipples.AutoSize = true;
            this.cbDLDynRipples.Location = new System.Drawing.Point(16, 113);
            this.cbDLDynRipples.Name = "cbDLDynRipples";
            this.cbDLDynRipples.Size = new System.Drawing.Size(111, 19);
            this.cbDLDynRipples.TabIndex = 1;
            this.cbDLDynRipples.Text = "D&ynamic ripples";
            this.cbDLDynRipples.UseVisualStyleBackColor = true;
            this.cbDLDynRipples.CheckedChanged += new System.EventHandler(this.cbDLDynRipples_CheckedChanged);
            // 
            // gbDLWtrCaust
            // 
            this.gbDLWtrCaust.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbDLWtrCaust.Controls.Add(this.lDLWtrCaust);
            this.gbDLWtrCaust.Controls.Add(this.udDLWtrCaust);
            this.gbDLWtrCaust.Location = new System.Drawing.Point(6, 172);
            this.gbDLWtrCaust.Name = "gbDLWtrCaust";
            this.gbDLWtrCaust.Size = new System.Drawing.Size(329, 54);
            this.gbDLWtrCaust.TabIndex = 4;
            this.gbDLWtrCaust.TabStop = false;
            this.gbDLWtrCaust.Text = "&Caustics [underwater refracted lighting]";
            // 
            // lDLWtrCaust
            // 
            this.lDLWtrCaust.AutoSize = true;
            this.lDLWtrCaust.Location = new System.Drawing.Point(59, 24);
            this.lDLWtrCaust.Name = "lDLWtrCaust";
            this.lDLWtrCaust.Size = new System.Drawing.Size(75, 15);
            this.lDLWtrCaust.TabIndex = 0;
            this.lDLWtrCaust.Text = "% brightness";
            this.lDLWtrCaust.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // udDLWtrCaust
            // 
            this.udDLWtrCaust.Increment = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    0});
            this.udDLWtrCaust.Location = new System.Drawing.Point(11, 22);
            this.udDLWtrCaust.Name = "udDLWtrCaust";
            this.udDLWtrCaust.Size = new System.Drawing.Size(42, 23);
            this.udDLWtrCaust.TabIndex = 0;
            this.udDLWtrCaust.Tag = "";
            this.udDLWtrCaust.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLWtrCaust.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            this.udDLWtrCaust.Value = new decimal(new int[] {
                                    50,
                                    0,
                                    0,
                                    0});
            // 
            // gbDLWtrWave
            // 
            this.gbDLWtrWave.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbDLWtrWave.Controls.Add(this.lDLWtrWave);
            this.gbDLWtrWave.Controls.Add(this.udDLWtrWave);
            this.gbDLWtrWave.Enabled = false;
            this.gbDLWtrWave.Location = new System.Drawing.Point(6, 112);
            this.gbDLWtrWave.Name = "gbDLWtrWave";
            this.gbDLWtrWave.Size = new System.Drawing.Size(329, 56);
            this.gbDLWtrWave.TabIndex = 3;
            this.gbDLWtrWave.TabStop = false;
            // 
            // lDLWtrWave
            // 
            this.lDLWtrWave.AutoSize = true;
            this.lDLWtrWave.Location = new System.Drawing.Point(59, 26);
            this.lDLWtrWave.Name = "lDLWtrWave";
            this.lDLWtrWave.Size = new System.Drawing.Size(92, 15);
            this.lDLWtrWave.TabIndex = 1;
            this.lDLWtrWave.Text = "Height of wa&ves";
            this.lDLWtrWave.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // udDLWtrWave
            // 
            this.udDLWtrWave.Location = new System.Drawing.Point(11, 24);
            this.udDLWtrWave.Maximum = new decimal(new int[] {
                                    250,
                                    0,
                                    0,
                                    0});
            this.udDLWtrWave.Name = "udDLWtrWave";
            this.udDLWtrWave.Size = new System.Drawing.Size(42, 23);
            this.udDLWtrWave.TabIndex = 0;
            this.udDLWtrWave.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLWtrWave.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            // 
            // gbDLWtrRefl
            // 
            this.gbDLWtrRefl.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbDLWtrRefl.Controls.Add(this.cbDLSkyRefl);
            this.gbDLWtrRefl.Controls.Add(this.cbDLReflLand);
            this.gbDLWtrRefl.Controls.Add(this.cbDLReflBlur);
            this.gbDLWtrRefl.Controls.Add(this.cbDLReflNStatics);
            this.gbDLWtrRefl.Controls.Add(this.cbDLReflInterior);
            this.gbDLWtrRefl.Location = new System.Drawing.Point(6, 17);
            this.gbDLWtrRefl.Name = "gbDLWtrRefl";
            this.gbDLWtrRefl.Size = new System.Drawing.Size(329, 92);
            this.gbDLWtrRefl.TabIndex = 0;
            this.gbDLWtrRefl.TabStop = false;
            this.gbDLWtrRefl.Text = "Reflections";
            // 
            // cbDLSkyRefl
            // 
            this.cbDLSkyRefl.AutoSize = true;
            this.cbDLSkyRefl.Location = new System.Drawing.Point(11, 19);
            this.cbDLSkyRefl.Name = "cbDLSkyRefl";
            this.cbDLSkyRefl.Size = new System.Drawing.Size(44, 19);
            this.cbDLSkyRefl.TabIndex = 0;
            this.cbDLSkyRefl.Text = "S&ky";
            this.cbDLSkyRefl.UseVisualStyleBackColor = true;
            // 
            // cbDLReflLand
            // 
            this.cbDLReflLand.AutoSize = true;
            this.cbDLReflLand.Location = new System.Drawing.Point(11, 42);
            this.cbDLReflLand.Name = "cbDLReflLand";
            this.cbDLReflLand.Size = new System.Drawing.Size(82, 19);
            this.cbDLReflLand.TabIndex = 2;
            this.cbDLReflLand.Text = "Landsca&pe";
            this.cbDLReflLand.UseVisualStyleBackColor = true;
            this.cbDLReflLand.CheckedChanged += new System.EventHandler(this.cbDLReflectiveWater_CheckedChanged);
            // 
            // cbDLReflBlur
            // 
            this.cbDLReflBlur.AutoSize = true;
            this.cbDLReflBlur.Location = new System.Drawing.Point(11, 65);
            this.cbDLReflBlur.Name = "cbDLReflBlur";
            this.cbDLReflBlur.Size = new System.Drawing.Size(105, 19);
            this.cbDLReflBlur.TabIndex = 4;
            this.cbDLReflBlur.Text = "&Blur reflections";
            this.cbDLReflBlur.UseVisualStyleBackColor = true;
            // 
            // cbDLReflNStatics
            // 
            this.cbDLReflNStatics.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbDLReflNStatics.AutoSize = true;
            this.cbDLReflNStatics.Location = new System.Drawing.Point(168, 19);
            this.cbDLReflNStatics.Name = "cbDLReflNStatics";
            this.cbDLReflNStatics.Size = new System.Drawing.Size(101, 19);
            this.cbDLReflNStatics.TabIndex = 1;
            this.cbDLReflNStatics.Text = "&Nearby Statics";
            this.cbDLReflNStatics.UseVisualStyleBackColor = true;
            // 
            // cbDLReflInterior
            // 
            this.cbDLReflInterior.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbDLReflInterior.AutoSize = true;
            this.cbDLReflInterior.Enabled = false;
            this.cbDLReflInterior.Location = new System.Drawing.Point(168, 42);
            this.cbDLReflInterior.Name = "cbDLReflInterior";
            this.cbDLReflInterior.Size = new System.Drawing.Size(69, 19);
            this.cbDLReflInterior.TabIndex = 3;
            this.cbDLReflInterior.Text = "&Interiors";
            this.cbDLReflInterior.UseVisualStyleBackColor = true;
            // 
            // tableLayoutDLRight
            // 
            this.tableLayoutDLRight.ColumnCount = 1;
            this.tableLayoutDLRight.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutDLRight.Controls.Add(this.pDLAutoDist, 0, 0);
            this.tableLayoutDLRight.Controls.Add(this.pDLStatics, 0, 1);
            this.tableLayoutDLRight.Controls.Add(this.bDLWthr, 0, 3);
            this.tableLayoutDLRight.Controls.Add(this.gbDLFog, 0, 2);
            this.tableLayoutDLRight.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutDLRight.Location = new System.Drawing.Point(347, 0);
            this.tableLayoutDLRight.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutDLRight.Name = "tableLayoutDLRight";
            this.tableLayoutDLRight.RowCount = 4;
            this.tableLayoutDLRight.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutDLRight.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutDLRight.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutDLRight.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutDLRight.Size = new System.Drawing.Size(363, 445);
            this.tableLayoutDLRight.TabIndex = 1;
            // 
            // pDLAutoDist
            // 
            this.pDLAutoDist.Controls.Add(this.cbDLAutoDist);
            this.pDLAutoDist.Controls.Add(this.gbDLAutoDist);
            this.pDLAutoDist.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pDLAutoDist.Location = new System.Drawing.Point(3, 3);
            this.pDLAutoDist.Name = "pDLAutoDist";
            this.pDLAutoDist.Size = new System.Drawing.Size(357, 76);
            this.pDLAutoDist.TabIndex = 13;
            // 
            // cbDLAutoDist
            // 
            this.cbDLAutoDist.AutoSize = true;
            this.cbDLAutoDist.Location = new System.Drawing.Point(8, 0);
            this.cbDLAutoDist.Name = "cbDLAutoDist";
            this.cbDLAutoDist.Size = new System.Drawing.Size(153, 19);
            this.cbDLAutoDist.TabIndex = 2;
            this.cbDLAutoDist.Text = "&Auto set other distances";
            this.cbDLAutoDist.UseVisualStyleBackColor = false;
            this.cbDLAutoDist.CheckedChanged += new System.EventHandler(this.cbAutoSetDistances_CheckedChanged);
            // 
            // gbDLAutoDist
            // 
            this.gbDLAutoDist.Controls.Add(this.rbDLAutoByAFogEnd);
            this.gbDLAutoDist.Controls.Add(this.rbDLAutoByDrawDist);
            this.gbDLAutoDist.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbDLAutoDist.Location = new System.Drawing.Point(0, 0);
            this.gbDLAutoDist.Name = "gbDLAutoDist";
            this.gbDLAutoDist.Size = new System.Drawing.Size(357, 76);
            this.gbDLAutoDist.TabIndex = 13;
            this.gbDLAutoDist.TabStop = false;
            // 
            // rbDLAutoByAFogEnd
            // 
            this.rbDLAutoByAFogEnd.AutoSize = true;
            this.rbDLAutoByAFogEnd.Location = new System.Drawing.Point(18, 48);
            this.rbDLAutoByAFogEnd.Name = "rbDLAutoByAFogEnd";
            this.rbDLAutoByAFogEnd.Size = new System.Drawing.Size(155, 19);
            this.rbDLAutoByAFogEnd.TabIndex = 1;
            this.rbDLAutoByAFogEnd.TabStop = true;
            this.rbDLAutoByAFogEnd.Text = "By Above Water Fo&g End";
            this.rbDLAutoByAFogEnd.UseVisualStyleBackColor = true;
            this.rbDLAutoByAFogEnd.CheckedChanged += new System.EventHandler(this.rbDLAutoDist_CheckedChanged);
            // 
            // rbDLAutoByDrawDist
            // 
            this.rbDLAutoByDrawDist.AutoSize = true;
            this.rbDLAutoByDrawDist.Checked = true;
            this.rbDLAutoByDrawDist.Location = new System.Drawing.Point(18, 24);
            this.rbDLAutoByDrawDist.Name = "rbDLAutoByDrawDist";
            this.rbDLAutoByDrawDist.Size = new System.Drawing.Size(116, 19);
            this.rbDLAutoByDrawDist.TabIndex = 0;
            this.rbDLAutoByDrawDist.TabStop = true;
            this.rbDLAutoByDrawDist.Text = "By D&raw Distance";
            this.rbDLAutoByDrawDist.UseVisualStyleBackColor = true;
            this.rbDLAutoByDrawDist.CheckedChanged += new System.EventHandler(this.rbDLAutoDist_CheckedChanged);
            // 
            // pDLStatics
            // 
            this.pDLStatics.Controls.Add(this.cbDLDistantStatics);
            this.pDLStatics.Controls.Add(this.gbDLStatics);
            this.pDLStatics.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pDLStatics.Location = new System.Drawing.Point(3, 85);
            this.pDLStatics.Name = "pDLStatics";
            this.pDLStatics.Size = new System.Drawing.Size(357, 118);
            this.pDLStatics.TabIndex = 5;
            this.pDLStatics.TabStop = true;
            // 
            // cbDLDistantStatics
            // 
            this.cbDLDistantStatics.AutoSize = true;
            this.cbDLDistantStatics.Location = new System.Drawing.Point(8, 0);
            this.cbDLDistantStatics.Name = "cbDLDistantStatics";
            this.cbDLDistantStatics.Size = new System.Drawing.Size(122, 19);
            this.cbDLDistantStatics.TabIndex = 0;
            this.cbDLDistantStatics.Text = "Use Distant &Statics";
            this.cbDLDistantStatics.UseVisualStyleBackColor = false;
            this.cbDLDistantStatics.CheckedChanged += new System.EventHandler(this.cbDistantStatics_CheckedChanged);
            // 
            // gbDLStatics
            // 
            this.gbDLStatics.Controls.Add(this.tableAlignDLStatics);
            this.gbDLStatics.Controls.Add(this.lDLMinSize);
            this.gbDLStatics.Controls.Add(this.lDLEndDist);
            this.gbDLStatics.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbDLStatics.Enabled = false;
            this.gbDLStatics.Location = new System.Drawing.Point(0, 0);
            this.gbDLStatics.Name = "gbDLStatics";
            this.gbDLStatics.Size = new System.Drawing.Size(357, 118);
            this.gbDLStatics.TabIndex = 1;
            this.gbDLStatics.TabStop = false;
            // 
            // tableAlignDLStatics
            // 
            this.tableAlignDLStatics.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.tableAlignDLStatics.ColumnCount = 4;
            this.tableAlignDLStatics.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableAlignDLStatics.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableAlignDLStatics.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 10F));
            this.tableAlignDLStatics.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableAlignDLStatics.Controls.Add(this.lDLNear, 0, 0);
            this.tableAlignDLStatics.Controls.Add(this.udDLDistNear, 3, 0);
            this.tableAlignDLStatics.Controls.Add(this.udDLDistVeryFar, 3, 4);
            this.tableAlignDLStatics.Controls.Add(this.tbDLNearSize, 1, 0);
            this.tableAlignDLStatics.Controls.Add(this.lDLFar, 0, 2);
            this.tableAlignDLStatics.Controls.Add(this.lDLVeryFar, 0, 4);
            this.tableAlignDLStatics.Controls.Add(this.udDLSizeVeryFar, 1, 4);
            this.tableAlignDLStatics.Controls.Add(this.udDLSizeFar, 1, 2);
            this.tableAlignDLStatics.Controls.Add(this.udDLDistFar, 3, 2);
            this.tableAlignDLStatics.Location = new System.Drawing.Point(8, 35);
            this.tableAlignDLStatics.Name = "tableAlignDLStatics";
            this.tableAlignDLStatics.RowCount = 5;
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 23F));
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 2F));
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 23F));
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 2F));
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 23F));
            this.tableAlignDLStatics.Size = new System.Drawing.Size(335, 73);
            this.tableAlignDLStatics.TabIndex = 6;
            // 
            // lDLNear
            // 
            this.lDLNear.AutoSize = true;
            this.lDLNear.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLNear.Location = new System.Drawing.Point(190, 0);
            this.lDLNear.Name = "lDLNear";
            this.lDLNear.Size = new System.Drawing.Size(32, 23);
            this.lDLNear.TabIndex = 0;
            this.lDLNear.Text = "Near";
            this.lDLNear.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // udDLDistNear
            // 
            this.udDLDistNear.DecimalPlaces = 1;
            this.udDLDistNear.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLDistNear.Location = new System.Drawing.Point(285, 0);
            this.udDLDistNear.Margin = new System.Windows.Forms.Padding(0);
            this.udDLDistNear.Maximum = new decimal(new int[] {
                                    2998,
                                    0,
                                    0,
                                    65536});
            this.udDLDistNear.Name = "udDLDistNear";
            this.udDLDistNear.Size = new System.Drawing.Size(50, 23);
            this.udDLDistNear.TabIndex = 1;
            this.udDLDistNear.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLDistNear.Value = new decimal(new int[] {
                                    2,
                                    0,
                                    0,
                                    0});
            this.udDLDistNear.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
            // 
            // udDLDistVeryFar
            // 
            this.udDLDistVeryFar.DecimalPlaces = 1;
            this.udDLDistVeryFar.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLDistVeryFar.Location = new System.Drawing.Point(285, 50);
            this.udDLDistVeryFar.Margin = new System.Windows.Forms.Padding(0);
            this.udDLDistVeryFar.Maximum = new decimal(new int[] {
                                    300,
                                    0,
                                    0,
                                    0});
            this.udDLDistVeryFar.Name = "udDLDistVeryFar";
            this.udDLDistVeryFar.Size = new System.Drawing.Size(50, 23);
            this.udDLDistVeryFar.TabIndex = 5;
            this.udDLDistVeryFar.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLDistVeryFar.Value = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    0});
            this.udDLDistVeryFar.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
            // 
            // tbDLNearSize
            // 
            this.tbDLNearSize.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbDLNearSize.Location = new System.Drawing.Point(225, 0);
            this.tbDLNearSize.Margin = new System.Windows.Forms.Padding(0);
            this.tbDLNearSize.MaxLength = 3;
            this.tbDLNearSize.Name = "tbDLNearSize";
            this.tbDLNearSize.ReadOnly = true;
            this.tbDLNearSize.Size = new System.Drawing.Size(50, 23);
            this.tbDLNearSize.TabIndex = 0;
            this.tbDLNearSize.Text = "400";
            this.tbDLNearSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // lDLFar
            // 
            this.lDLFar.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLFar.Location = new System.Drawing.Point(67, 25);
            this.lDLFar.Name = "lDLFar";
            this.lDLFar.Size = new System.Drawing.Size(155, 23);
            this.lDLFar.TabIndex = 0;
            this.lDLFar.Text = "Far";
            this.lDLFar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lDLVeryFar
            // 
            this.lDLVeryFar.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLVeryFar.Location = new System.Drawing.Point(67, 50);
            this.lDLVeryFar.Name = "lDLVeryFar";
            this.lDLVeryFar.Size = new System.Drawing.Size(155, 23);
            this.lDLVeryFar.TabIndex = 0;
            this.lDLVeryFar.Text = "Very Far";
            this.lDLVeryFar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // udDLSizeVeryFar
            // 
            this.udDLSizeVeryFar.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLSizeVeryFar.Increment = new decimal(new int[] {
                                    10,
                                    0,
                                    0,
                                    0});
            this.udDLSizeVeryFar.Location = new System.Drawing.Point(225, 50);
            this.udDLSizeVeryFar.Margin = new System.Windows.Forms.Padding(0);
            this.udDLSizeVeryFar.Maximum = new decimal(new int[] {
                                    9999,
                                    0,
                                    0,
                                    0});
            this.udDLSizeVeryFar.Name = "udDLSizeVeryFar";
            this.udDLSizeVeryFar.Size = new System.Drawing.Size(50, 23);
            this.udDLSizeVeryFar.TabIndex = 4;
            this.udDLSizeVeryFar.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLSizeVeryFar.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            this.udDLSizeVeryFar.Value = new decimal(new int[] {
                                    800,
                                    0,
                                    0,
                                    0});
            this.udDLSizeVeryFar.ValueChanged += new System.EventHandler(this.ValidateDistances);
            // 
            // udDLSizeFar
            // 
            this.udDLSizeFar.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLSizeFar.Increment = new decimal(new int[] {
                                    10,
                                    0,
                                    0,
                                    0});
            this.udDLSizeFar.Location = new System.Drawing.Point(225, 25);
            this.udDLSizeFar.Margin = new System.Windows.Forms.Padding(0);
            this.udDLSizeFar.Maximum = new decimal(new int[] {
                                    9999,
                                    0,
                                    0,
                                    0});
            this.udDLSizeFar.Name = "udDLSizeFar";
            this.udDLSizeFar.Size = new System.Drawing.Size(50, 23);
            this.udDLSizeFar.TabIndex = 2;
            this.udDLSizeFar.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLSizeFar.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            this.udDLSizeFar.Value = new decimal(new int[] {
                                    600,
                                    0,
                                    0,
                                    0});
            this.udDLSizeFar.ValueChanged += new System.EventHandler(this.ValidateDistances);
            // 
            // udDLDistFar
            // 
            this.udDLDistFar.DecimalPlaces = 1;
            this.udDLDistFar.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLDistFar.Location = new System.Drawing.Point(285, 25);
            this.udDLDistFar.Margin = new System.Windows.Forms.Padding(0);
            this.udDLDistFar.Maximum = new decimal(new int[] {
                                    2999,
                                    0,
                                    0,
                                    65536});
            this.udDLDistFar.Name = "udDLDistFar";
            this.udDLDistFar.Size = new System.Drawing.Size(50, 23);
            this.udDLDistFar.TabIndex = 3;
            this.udDLDistFar.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLDistFar.Value = new decimal(new int[] {
                                    4,
                                    0,
                                    0,
                                    0});
            this.udDLDistFar.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
            // 
            // lDLMinSize
            // 
            this.lDLMinSize.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lDLMinSize.AutoSize = true;
            this.lDLMinSize.Location = new System.Drawing.Point(230, 18);
            this.lDLMinSize.Name = "lDLMinSize";
            this.lDLMinSize.Size = new System.Drawing.Size(51, 15);
            this.lDLMinSize.TabIndex = 0;
            this.lDLMinSize.Text = "Min Size";
            // 
            // lDLEndDist
            // 
            this.lDLEndDist.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lDLEndDist.AutoSize = true;
            this.lDLEndDist.Location = new System.Drawing.Point(290, 18);
            this.lDLEndDist.Name = "lDLEndDist";
            this.lDLEndDist.Size = new System.Drawing.Size(50, 15);
            this.lDLEndDist.TabIndex = 0;
            this.lDLEndDist.Text = "End Dist";
            // 
            // bDLWthr
            // 
            this.bDLWthr.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.bDLWthr.Location = new System.Drawing.Point(101, 417);
            this.bDLWthr.Name = "bDLWthr";
            this.bDLWthr.Size = new System.Drawing.Size(160, 25);
            this.bDLWthr.TabIndex = 8;
            this.bDLWthr.Text = "Weat&her Settings...";
            this.bDLWthr.UseVisualStyleBackColor = true;
            this.bDLWthr.Click += new System.EventHandler(this.bDLWthr_Click);
            // 
            // gbDLFog
            // 
            this.gbDLFog.Controls.Add(this.tableAlignDLFog);
            this.gbDLFog.Controls.Add(this.cbDLScattering);
            this.gbDLFog.Controls.Add(this.cbDLFogExp);
            this.gbDLFog.Controls.Add(this.lDLFogStart);
            this.gbDLFog.Controls.Add(this.lDLFogEnd);
            this.gbDLFog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gbDLFog.Location = new System.Drawing.Point(3, 209);
            this.gbDLFog.Name = "gbDLFog";
            this.gbDLFog.Size = new System.Drawing.Size(357, 202);
            this.gbDLFog.TabIndex = 6;
            this.gbDLFog.TabStop = false;
            this.gbDLFog.Text = "&Fog";
            // 
            // tableAlignDLFog
            // 
            this.tableAlignDLFog.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.tableAlignDLFog.ColumnCount = 4;
            this.tableAlignDLFog.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableAlignDLFog.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableAlignDLFog.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 10F));
            this.tableAlignDLFog.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableAlignDLFog.Controls.Add(this.udDLFogAStart, 1, 0);
            this.tableAlignDLFog.Controls.Add(this.udDLFogAEnd, 3, 0);
            this.tableAlignDLFog.Controls.Add(this.udDLFogExpMul, 3, 6);
            this.tableAlignDLFog.Controls.Add(this.lDLFogExpMul, 0, 6);
            this.tableAlignDLFog.Controls.Add(this.udDLFogBStart, 1, 2);
            this.tableAlignDLFog.Controls.Add(this.udDLFogBEnd, 3, 2);
            this.tableAlignDLFog.Controls.Add(this.lDLFogI, 0, 4);
            this.tableAlignDLFog.Controls.Add(this.udDLFogIStart, 1, 4);
            this.tableAlignDLFog.Controls.Add(this.udDLFogIEnd, 3, 4);
            this.tableAlignDLFog.Controls.Add(this.lDLFogB, 0, 2);
            this.tableAlignDLFog.Controls.Add(this.lDLFogA, 0, 0);
            this.tableAlignDLFog.Location = new System.Drawing.Point(8, 30);
            this.tableAlignDLFog.Name = "tableAlignDLFog";
            this.tableAlignDLFog.RowCount = 7;
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 23F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 2F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 23F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 2F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 23F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 4F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 23F));
            this.tableAlignDLFog.Size = new System.Drawing.Size(335, 76);
            this.tableAlignDLFog.TabIndex = 10;
            // 
            // udDLFogAStart
            // 
            this.udDLFogAStart.DecimalPlaces = 1;
            this.udDLFogAStart.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLFogAStart.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogAStart.Location = new System.Drawing.Point(225, 0);
            this.udDLFogAStart.Margin = new System.Windows.Forms.Padding(0);
            this.udDLFogAStart.Maximum = new decimal(new int[] {
                                    2999,
                                    0,
                                    0,
                                    65536});
            this.udDLFogAStart.Name = "udDLFogAStart";
            this.udDLFogAStart.Size = new System.Drawing.Size(50, 23);
            this.udDLFogAStart.TabIndex = 0;
            this.udDLFogAStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLFogAStart.Value = new decimal(new int[] {
                                    2,
                                    0,
                                    0,
                                    0});
            this.udDLFogAStart.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
            // 
            // udDLFogAEnd
            // 
            this.udDLFogAEnd.DecimalPlaces = 1;
            this.udDLFogAEnd.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLFogAEnd.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogAEnd.Location = new System.Drawing.Point(285, 0);
            this.udDLFogAEnd.Margin = new System.Windows.Forms.Padding(0);
            this.udDLFogAEnd.Maximum = new decimal(new int[] {
                                    300,
                                    0,
                                    0,
                                    0});
            this.udDLFogAEnd.Minimum = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogAEnd.Name = "udDLFogAEnd";
            this.udDLFogAEnd.Size = new System.Drawing.Size(50, 23);
            this.udDLFogAEnd.TabIndex = 1;
            this.udDLFogAEnd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLFogAEnd.Value = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    0});
            this.udDLFogAEnd.ValueChanged += new System.EventHandler(this.udDLFogAEnd_ValueChanged);
            // 
            // udDLFogExpMul
            // 
            this.udDLFogExpMul.DecimalPlaces = 1;
            this.udDLFogExpMul.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLFogExpMul.Enabled = false;
            this.udDLFogExpMul.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogExpMul.Location = new System.Drawing.Point(285, 77);
            this.udDLFogExpMul.Margin = new System.Windows.Forms.Padding(0);
            this.udDLFogExpMul.Maximum = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    0});
            this.udDLFogExpMul.Minimum = new decimal(new int[] {
                                    25,
                                    0,
                                    0,
                                    65536});
            this.udDLFogExpMul.Name = "udDLFogExpMul";
            this.udDLFogExpMul.Size = new System.Drawing.Size(50, 23);
            this.udDLFogExpMul.TabIndex = 7;
            this.udDLFogExpMul.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLFogExpMul.Value = new decimal(new int[] {
                                    4,
                                    0,
                                    0,
                                    0});
            this.udDLFogExpMul.Visible = false;
            this.udDLFogExpMul.ValueChanged += new System.EventHandler(this.udDLFogExpMul_ValueChanged);
            // 
            // lDLFogExpMul
            // 
            this.lDLFogExpMul.AutoSize = true;
            this.tableAlignDLFog.SetColumnSpan(this.lDLFogExpMul, 3);
            this.lDLFogExpMul.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLFogExpMul.Enabled = false;
            this.lDLFogExpMul.Location = new System.Drawing.Point(113, 77);
            this.lDLFogExpMul.Name = "lDLFogExpMul";
            this.lDLFogExpMul.Size = new System.Drawing.Size(169, 23);
            this.lDLFogExpMul.TabIndex = 8;
            this.lDLFogExpMul.Text = "Exponential distance multiplier";
            this.lDLFogExpMul.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.lDLFogExpMul.Visible = false;
            // 
            // udDLFogBStart
            // 
            this.udDLFogBStart.DecimalPlaces = 1;
            this.udDLFogBStart.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLFogBStart.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogBStart.Location = new System.Drawing.Point(225, 25);
            this.udDLFogBStart.Margin = new System.Windows.Forms.Padding(0);
            this.udDLFogBStart.Maximum = new decimal(new int[] {
                                    2999,
                                    0,
                                    0,
                                    65536});
            this.udDLFogBStart.Minimum = new decimal(new int[] {
                                    999,
                                    0,
                                    0,
                                    -2147418112});
            this.udDLFogBStart.Name = "udDLFogBStart";
            this.udDLFogBStart.Size = new System.Drawing.Size(50, 23);
            this.udDLFogBStart.TabIndex = 2;
            this.udDLFogBStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLFogBStart.Value = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    -2147418112});
            this.udDLFogBStart.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
            // 
            // udDLFogBEnd
            // 
            this.udDLFogBEnd.DecimalPlaces = 1;
            this.udDLFogBEnd.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLFogBEnd.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogBEnd.Location = new System.Drawing.Point(285, 25);
            this.udDLFogBEnd.Margin = new System.Windows.Forms.Padding(0);
            this.udDLFogBEnd.Maximum = new decimal(new int[] {
                                    300,
                                    0,
                                    0,
                                    0});
            this.udDLFogBEnd.Minimum = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogBEnd.Name = "udDLFogBEnd";
            this.udDLFogBEnd.Size = new System.Drawing.Size(50, 23);
            this.udDLFogBEnd.TabIndex = 3;
            this.udDLFogBEnd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLFogBEnd.Value = new decimal(new int[] {
                                    3,
                                    0,
                                    0,
                                    65536});
            this.udDLFogBEnd.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
            // 
            // lDLFogI
            // 
            this.lDLFogI.AutoSize = true;
            this.lDLFogI.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLFogI.Enabled = false;
            this.lDLFogI.Location = new System.Drawing.Point(109, 50);
            this.lDLFogI.Name = "lDLFogI";
            this.lDLFogI.Size = new System.Drawing.Size(113, 23);
            this.lDLFogI.TabIndex = 0;
            this.lDLFogI.Text = "Distant Interiors Fog";
            this.lDLFogI.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // udDLFogIStart
            // 
            this.udDLFogIStart.DecimalPlaces = 2;
            this.udDLFogIStart.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLFogIStart.Enabled = false;
            this.udDLFogIStart.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogIStart.Location = new System.Drawing.Point(225, 50);
            this.udDLFogIStart.Margin = new System.Windows.Forms.Padding(0);
            this.udDLFogIStart.Maximum = new decimal(new int[] {
                                    2999,
                                    0,
                                    0,
                                    65536});
            this.udDLFogIStart.Minimum = new decimal(new int[] {
                                    90,
                                    0,
                                    0,
                                    -2147352576});
            this.udDLFogIStart.Name = "udDLFogIStart";
            this.udDLFogIStart.Size = new System.Drawing.Size(50, 23);
            this.udDLFogIStart.TabIndex = 4;
            this.udDLFogIStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLFogIStart.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
            // 
            // udDLFogIEnd
            // 
            this.udDLFogIEnd.DecimalPlaces = 2;
            this.udDLFogIEnd.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLFogIEnd.Enabled = false;
            this.udDLFogIEnd.Increment = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    65536});
            this.udDLFogIEnd.Location = new System.Drawing.Point(285, 50);
            this.udDLFogIEnd.Margin = new System.Windows.Forms.Padding(0);
            this.udDLFogIEnd.Maximum = new decimal(new int[] {
                                    300,
                                    0,
                                    0,
                                    0});
            this.udDLFogIEnd.Minimum = new decimal(new int[] {
                                    10,
                                    0,
                                    0,
                                    131072});
            this.udDLFogIEnd.Name = "udDLFogIEnd";
            this.udDLFogIEnd.Size = new System.Drawing.Size(50, 23);
            this.udDLFogIEnd.TabIndex = 5;
            this.udDLFogIEnd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udDLFogIEnd.Value = new decimal(new int[] {
                                    20,
                                    0,
                                    0,
                                    65536});
            this.udDLFogIEnd.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
            // 
            // lDLFogB
            // 
            this.lDLFogB.AutoSize = true;
            this.lDLFogB.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLFogB.Location = new System.Drawing.Point(126, 25);
            this.lDLFogB.Name = "lDLFogB";
            this.lDLFogB.Size = new System.Drawing.Size(96, 23);
            this.lDLFogB.TabIndex = 0;
            this.lDLFogB.Text = "Below Water Fog";
            this.lDLFogB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lDLFogA
            // 
            this.lDLFogA.AutoSize = true;
            this.lDLFogA.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLFogA.Location = new System.Drawing.Point(124, 0);
            this.lDLFogA.Name = "lDLFogA";
            this.lDLFogA.Size = new System.Drawing.Size(98, 23);
            this.lDLFogA.TabIndex = 0;
            this.lDLFogA.Text = "Above Water Fog";
            this.lDLFogA.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // cbDLScattering
            // 
            this.cbDLScattering.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cbDLScattering.AutoSize = true;
            this.cbDLScattering.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbDLScattering.Enabled = false;
            this.cbDLScattering.Location = new System.Drawing.Point(72, 143);
            this.cbDLScattering.Name = "cbDLScattering";
            this.cbDLScattering.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.cbDLScattering.Size = new System.Drawing.Size(271, 19);
            this.cbDLScattering.TabIndex = 9;
            this.cbDLScattering.Text = "High quality atmosphere && distance &colouring";
            this.cbDLScattering.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbDLScattering.UseVisualStyleBackColor = true;
            // 
            // cbDLFogExp
            // 
            this.cbDLFogExp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cbDLFogExp.AutoSize = true;
            this.cbDLFogExp.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbDLFogExp.Location = new System.Drawing.Point(139, 118);
            this.cbDLFogExp.Name = "cbDLFogExp";
            this.cbDLFogExp.Size = new System.Drawing.Size(204, 19);
            this.cbDLFogExp.TabIndex = 6;
            this.cbDLFogExp.Text = "Use high quality (e&xponential) fog";
            this.cbDLFogExp.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbDLFogExp.UseVisualStyleBackColor = true;
            this.cbDLFogExp.CheckedChanged += new System.EventHandler(this.cbDLFogExp_CheckedChanged);
            // 
            // lDLFogStart
            // 
            this.lDLFogStart.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lDLFogStart.AutoSize = true;
            this.lDLFogStart.Location = new System.Drawing.Point(230, 13);
            this.lDLFogStart.Name = "lDLFogStart";
            this.lDLFogStart.Size = new System.Drawing.Size(31, 15);
            this.lDLFogStart.TabIndex = 0;
            this.lDLFogStart.Text = "Start";
            // 
            // lDLFogEnd
            // 
            this.lDLFogEnd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lDLFogEnd.AutoSize = true;
            this.lDLFogEnd.Location = new System.Drawing.Point(290, 13);
            this.lDLFogEnd.Margin = new System.Windows.Forms.Padding(0);
            this.lDLFogEnd.Name = "lDLFogEnd";
            this.lDLFogEnd.Size = new System.Drawing.Size(27, 15);
            this.lDLFogEnd.TabIndex = 0;
            this.lDLFogEnd.Text = "End";
            // 
            // tpConfig
            // 
            this.tpConfig.Controls.Add(this.gbErrorReporting);
            this.tpConfig.Controls.Add(this.gbMainUI);
            this.tpConfig.Controls.Add(this.gbMainInfo);
            this.tpConfig.Controls.Add(this.gbMainSettings);
            this.tpConfig.Location = new System.Drawing.Point(4, 24);
            this.tpConfig.Name = "tpConfig";
            this.tpConfig.Size = new System.Drawing.Size(716, 473);
            this.tpConfig.TabIndex = 0;
            this.tpConfig.Text = "Config";
            this.tpConfig.ToolTipText = "Load/save all MGE settings.";
            this.tpConfig.UseVisualStyleBackColor = true;
            // 
            // gbErrorReporting
            // 
            this.gbErrorReporting.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbErrorReporting.Controls.Add(this.bReportingShowDLWizardLog);
            this.gbErrorReporting.Controls.Add(this.bReportingShowLog);
            this.gbErrorReporting.Location = new System.Drawing.Point(8, 323);
            this.gbErrorReporting.Name = "gbErrorReporting";
            this.gbErrorReporting.Size = new System.Drawing.Size(700, 60);
            this.gbErrorReporting.TabIndex = 3;
            this.gbErrorReporting.TabStop = false;
            this.gbErrorReporting.Text = "Error reporting";
            // 
            // bReportingShowDLWizardLog
            // 
            this.bReportingShowDLWizardLog.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.bReportingShowDLWizardLog.Location = new System.Drawing.Point(270, 22);
            this.bReportingShowDLWizardLog.Name = "bReportingShowDLWizardLog";
            this.bReportingShowDLWizardLog.Size = new System.Drawing.Size(160, 25);
            this.bReportingShowDLWizardLog.TabIndex = 1;
            this.bReportingShowDLWizardLog.Text = "Open DL generator log";
            this.bReportingShowDLWizardLog.UseVisualStyleBackColor = true;
            this.bReportingShowDLWizardLog.Click += new System.EventHandler(this.bReportingShowDLWizardLog_Click);
            // 
            // bReportingShowLog
            // 
            this.bReportingShowLog.Location = new System.Drawing.Point(6, 22);
            this.bReportingShowLog.Name = "bReportingShowLog";
            this.bReportingShowLog.Size = new System.Drawing.Size(156, 25);
            this.bReportingShowLog.TabIndex = 0;
            this.bReportingShowLog.Text = "Open last mgeXE.log";
            this.bReportingShowLog.UseVisualStyleBackColor = true;
            this.bReportingShowLog.Click += new System.EventHandler(this.bReportingShowLog_Click);
            // 
            // gbMainUI
            // 
            this.gbMainUI.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbMainUI.Controls.Add(this.pLanguage);
            this.gbMainUI.Controls.Add(this.cmbTipReadSpd);
            this.gbMainUI.Controls.Add(this.lTipReadSpd);
            this.gbMainUI.Controls.Add(this.lTipRSpdUnit);
            this.gbMainUI.Location = new System.Drawing.Point(8, 69);
            this.gbMainUI.Name = "gbMainUI";
            this.gbMainUI.Size = new System.Drawing.Size(700, 80);
            this.gbMainUI.TabIndex = 2;
            this.gbMainUI.TabStop = false;
            this.gbMainUI.Text = "User Interface";
            // 
            // pLanguage
            // 
            this.pLanguage.AutoSize = true;
            this.pLanguage.Controls.Add(this.cmbUILanguage);
            this.pLanguage.Controls.Add(this.cbUILangAuto);
            this.pLanguage.Controls.Add(this.lUILanguage);
            this.pLanguage.Location = new System.Drawing.Point(8, 25);
            this.pLanguage.Name = "pLanguage";
            this.pLanguage.Size = new System.Drawing.Size(210, 42);
            this.pLanguage.TabIndex = 0;
            // 
            // cmbUILanguage
            // 
            this.cmbUILanguage.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.cmbUILanguage.FormattingEnabled = true;
            this.cmbUILanguage.Location = new System.Drawing.Point(0, 19);
            this.cmbUILanguage.Name = "cmbUILanguage";
            this.cmbUILanguage.Size = new System.Drawing.Size(210, 23);
            this.cmbUILanguage.TabIndex = 1;
            this.cmbUILanguage.SelectedIndexChanged += new System.EventHandler(this.cmbUILanguage_SelectedIndexChanged);
            this.cmbUILanguage.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
            // 
            // cbUILangAuto
            // 
            this.cbUILangAuto.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cbUILangAuto.AutoSize = true;
            this.cbUILangAuto.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbUILangAuto.Location = new System.Drawing.Point(125, -1);
            this.cbUILangAuto.Name = "cbUILangAuto";
            this.cbUILangAuto.Size = new System.Drawing.Size(85, 19);
            this.cbUILangAuto.TabIndex = 0;
            this.cbUILangAuto.Text = "Autodetect";
            this.cbUILangAuto.UseVisualStyleBackColor = true;
            this.cbUILangAuto.CheckedChanged += new System.EventHandler(this.cbUILangAuto_CheckedChanged);
            // 
            // lUILanguage
            // 
            this.lUILanguage.AutoSize = true;
            this.lUILanguage.Location = new System.Drawing.Point(-2, 0);
            this.lUILanguage.Name = "lUILanguage";
            this.lUILanguage.Size = new System.Drawing.Size(59, 15);
            this.lUILanguage.TabIndex = 0;
            this.lUILanguage.Text = "Language";
            // 
            // cmbTipReadSpd
            // 
            this.cmbTipReadSpd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbTipReadSpd.FormattingEnabled = true;
            this.cmbTipReadSpd.Items.AddRange(new object[] {
                                    "5",
                                    "6.25",
                                    "7.5",
                                    "8.75",
                                    "10",
                                    "12.5",
                                    "15",
                                    "17.5",
                                    "20",
                                    "25",
                                    "30",
                                    "35",
                                    "40",
                                    "50",
                                    "60",
                                    "70"});
            this.cmbTipReadSpd.Location = new System.Drawing.Point(408, 44);
            this.cmbTipReadSpd.Name = "cmbTipReadSpd";
            this.cmbTipReadSpd.Size = new System.Drawing.Size(48, 23);
            this.cmbTipReadSpd.TabIndex = 2;
            this.cmbTipReadSpd.Text = "15";
            this.cmbTipReadSpd.SelectedIndexChanged += new System.EventHandler(this.cmbMainTipReadSpd_SelectedIndexChanged);
            this.cmbTipReadSpd.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
            // 
            // lTipReadSpd
            // 
            this.lTipReadSpd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lTipReadSpd.AutoSize = true;
            this.lTipReadSpd.Location = new System.Drawing.Point(408, 26);
            this.lTipReadSpd.Name = "lTipReadSpd";
            this.lTipReadSpd.Size = new System.Drawing.Size(122, 15);
            this.lTipReadSpd.TabIndex = 0;
            this.lTipReadSpd.Text = "Tooltip reading speed";
            // 
            // lTipRSpdUnit
            // 
            this.lTipRSpdUnit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lTipRSpdUnit.AutoSize = true;
            this.lTipRSpdUnit.Location = new System.Drawing.Point(462, 47);
            this.lTipRSpdUnit.Name = "lTipRSpdUnit";
            this.lTipRSpdUnit.Size = new System.Drawing.Size(60, 15);
            this.lTipRSpdUnit.TabIndex = 0;
            this.lTipRSpdUnit.Text = "chars/sec.";
            // 
            // gbMainInfo
            // 
            this.gbMainInfo.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbMainInfo.Controls.Add(this.bViewCaps);
            this.gbMainInfo.Controls.Add(this.bHelp);
            this.gbMainInfo.Controls.Add(this.bAbout);
            this.gbMainInfo.Location = new System.Drawing.Point(8, 3);
            this.gbMainInfo.Name = "gbMainInfo";
            this.gbMainInfo.Size = new System.Drawing.Size(700, 60);
            this.gbMainInfo.TabIndex = 0;
            this.gbMainInfo.TabStop = false;
            this.gbMainInfo.Text = "Information";
            // 
            // bViewCaps
            // 
            this.bViewCaps.Location = new System.Drawing.Point(6, 22);
            this.bViewCaps.Name = "bViewCaps";
            this.bViewCaps.Size = new System.Drawing.Size(160, 25);
            this.bViewCaps.TabIndex = 0;
            this.bViewCaps.Text = "Report max AA and AF";
            this.bViewCaps.Click += new System.EventHandler(this.bViewCaps_Click);
            // 
            // bHelp
            // 
            this.bHelp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bHelp.Location = new System.Drawing.Point(534, 22);
            this.bHelp.Name = "bHelp";
            this.bHelp.Size = new System.Drawing.Size(160, 25);
            this.bHelp.TabIndex = 1;
            this.bHelp.Text = "Help";
            this.bHelp.Click += new System.EventHandler(this.bHelp_Click);
            // 
            // bAbout
            // 
            this.bAbout.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.bAbout.Location = new System.Drawing.Point(270, 22);
            this.bAbout.Name = "bAbout";
            this.bAbout.Size = new System.Drawing.Size(160, 25);
            this.bAbout.TabIndex = 2;
            this.bAbout.Text = "About";
            this.bAbout.Click += new System.EventHandler(this.bAbout_Click);
            // 
            // gbMainSettings
            // 
            this.gbMainSettings.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.gbMainSettings.Controls.Add(this.bResetSettings);
            this.gbMainSettings.Controls.Add(this.bImport);
            this.gbMainSettings.Controls.Add(this.bExport);
            this.gbMainSettings.Controls.Add(this.cbClearINI);
            this.gbMainSettings.Location = new System.Drawing.Point(8, 389);
            this.gbMainSettings.Name = "gbMainSettings";
            this.gbMainSettings.Size = new System.Drawing.Size(700, 76);
            this.gbMainSettings.TabIndex = 1;
            this.gbMainSettings.TabStop = false;
            this.gbMainSettings.Text = "Settings";
            // 
            // bResetSettings
            // 
            this.bResetSettings.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bResetSettings.Location = new System.Drawing.Point(6, 40);
            this.bResetSettings.Name = "bResetSettings";
            this.bResetSettings.Size = new System.Drawing.Size(160, 25);
            this.bResetSettings.TabIndex = 1;
            this.bResetSettings.Text = "Reset settings";
            this.bResetSettings.Click += new System.EventHandler(this.bResetSettings_Click);
            // 
            // bImport
            // 
            this.bImport.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.bImport.Location = new System.Drawing.Point(270, 40);
            this.bImport.Name = "bImport";
            this.bImport.Size = new System.Drawing.Size(160, 25);
            this.bImport.TabIndex = 3;
            this.bImport.Text = "Import settings";
            this.bImport.Click += new System.EventHandler(this.bImport_Click);
            // 
            // bExport
            // 
            this.bExport.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bExport.Location = new System.Drawing.Point(534, 40);
            this.bExport.Name = "bExport";
            this.bExport.Size = new System.Drawing.Size(160, 25);
            this.bExport.TabIndex = 4;
            this.bExport.Text = "Export settings";
            this.bExport.Click += new System.EventHandler(this.bExport_Click);
            // 
            // cbClearINI
            // 
            this.cbClearINI.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cbClearINI.AutoSize = true;
            this.cbClearINI.Location = new System.Drawing.Point(8, 18);
            this.cbClearINI.Name = "cbClearINI";
            this.cbClearINI.Size = new System.Drawing.Size(130, 19);
            this.cbClearINI.TabIndex = 0;
            this.cbClearINI.Text = "Clear saved settings";
            this.cbClearINI.UseVisualStyleBackColor = true;
            // 
            // tpInstructions
            // 
            this.tpInstructions.Controls.Add(this.lInstructions);
            this.tpInstructions.Location = new System.Drawing.Point(4, 24);
            this.tpInstructions.Name = "tpInstructions";
            this.tpInstructions.Size = new System.Drawing.Size(716, 473);
            this.tpInstructions.TabIndex = 8;
            this.tpInstructions.Text = "Instructions";
            this.tpInstructions.ToolTipText = "A guide to setting up MGE XE.";
            this.tpInstructions.UseVisualStyleBackColor = true;
            // 
            // lInstructions
            // 
            this.lInstructions.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lInstructions.Location = new System.Drawing.Point(0, 0);
            this.lInstructions.Name = "lInstructions";
            this.lInstructions.Padding = new System.Windows.Forms.Padding(12);
            this.lInstructions.Size = new System.Drawing.Size(716, 473);
            this.lInstructions.TabIndex = 0;
            this.lInstructions.Text = resources.GetString("lInstructions.Text");
            // 
            // SShotFolderDialog
            // 
            this.SShotFolderDialog.Description = "Select output folder for screenshots taken in game:";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(724, 501);
            this.Controls.Add(this.tabControl);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(740, 540);
            this.Name = "MainForm";
            this.Text = "     ";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.MainForm_FormClosing);
            this.tpInput.ResumeLayout(false);
            this.gbMWLighting.ResumeLayout(false);
            this.gbMWLighting.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udLightingConst)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udLightingLinear)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udLightingQuad)).EndInit();
            this.gbMWGeneral.ResumeLayout(false);
            this.gbMWGeneral.PerformLayout();
            this.gbMsgs.ResumeLayout(false);
            this.gbMsgs.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udMsgsTime)).EndInit();
            this.pCam3rdPrsn.ResumeLayout(false);
            this.pCam3rdPrsn.PerformLayout();
            this.gbCam3rdPrsn.ResumeLayout(false);
            this.gbCam3rdPrsn.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udCam3rdZ)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udCam3rdY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udCam3rdX)).EndInit();
            this.gbInputTools.ResumeLayout(false);
            this.gbInputTools.PerformLayout();
            this.gbInputOpts.ResumeLayout(false);
            this.gbInputOpts.PerformLayout();
            this.tpGlobal.ResumeLayout(false);
            this.gbSShot.ResumeLayout(false);
            this.gbSShot.PerformLayout();
            this.tableLayoutScreenshots.ResumeLayout(false);
            this.tableLayoutScreenshots.PerformLayout();
            this.tableAlignSSFormat.ResumeLayout(false);
            this.tableAlignSSFormat.PerformLayout();
            this.panelSShotDirButtons.ResumeLayout(false);
            this.gbScene.ResumeLayout(false);
            this.gbScene.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udUIScale)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udFPSLimit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udFOV)).EndInit();
            this.gbDisplay.ResumeLayout(false);
            this.gbDisplay.PerformLayout();
            this.tableLayoutWindowAlign.ResumeLayout(false);
            this.tableLayoutWindowAlign.PerformLayout();
            this.panelWindowAlign.ResumeLayout(false);
            this.tableAlignResolution.ResumeLayout(false);
            this.tableAlignResolution.PerformLayout();
            this.tableLayoutDisplay.ResumeLayout(false);
            this.tableLayoutDisplay.PerformLayout();
            this.tabControl.ResumeLayout(false);
            this.tpDL.ResumeLayout(false);
            this.tpDL.PerformLayout();
            this.gbDistantLand.ResumeLayout(false);
            this.tableLayoutDL.ResumeLayout(false);
            this.tableLayoutDLLeft.ResumeLayout(false);
            this.tableLayoutDLLeft.PerformLayout();
            this.gbXEFeatures.ResumeLayout(false);
            this.gbXEFeatures.PerformLayout();
            this.gbDLDrawDist.ResumeLayout(false);
            this.gbDLDrawDist.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLDrawDist)).EndInit();
            this.gbDLWater.ResumeLayout(false);
            this.gbDLWater.PerformLayout();
            this.gbDLWtrCaust.ResumeLayout(false);
            this.gbDLWtrCaust.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLWtrCaust)).EndInit();
            this.gbDLWtrWave.ResumeLayout(false);
            this.gbDLWtrWave.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLWtrWave)).EndInit();
            this.gbDLWtrRefl.ResumeLayout(false);
            this.gbDLWtrRefl.PerformLayout();
            this.tableLayoutDLRight.ResumeLayout(false);
            this.pDLAutoDist.ResumeLayout(false);
            this.pDLAutoDist.PerformLayout();
            this.gbDLAutoDist.ResumeLayout(false);
            this.gbDLAutoDist.PerformLayout();
            this.pDLStatics.ResumeLayout(false);
            this.pDLStatics.PerformLayout();
            this.gbDLStatics.ResumeLayout(false);
            this.gbDLStatics.PerformLayout();
            this.tableAlignDLStatics.ResumeLayout(false);
            this.tableAlignDLStatics.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLDistNear)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLDistVeryFar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLSizeVeryFar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLSizeFar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLDistFar)).EndInit();
            this.gbDLFog.ResumeLayout(false);
            this.gbDLFog.PerformLayout();
            this.tableAlignDLFog.ResumeLayout(false);
            this.tableAlignDLFog.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogAStart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogAEnd)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogExpMul)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogBStart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogBEnd)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogIStart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.udDLFogIEnd)).EndInit();
            this.tpConfig.ResumeLayout(false);
            this.gbErrorReporting.ResumeLayout(false);
            this.gbMainUI.ResumeLayout(false);
            this.gbMainUI.PerformLayout();
            this.pLanguage.ResumeLayout(false);
            this.pLanguage.PerformLayout();
            this.gbMainInfo.ResumeLayout(false);
            this.gbMainSettings.ResumeLayout(false);
            this.gbMainSettings.PerformLayout();
            this.tpInstructions.ResumeLayout(false);
            this.ResumeLayout(false);
        }
        private System.Windows.Forms.TableLayoutPanel tableLayoutWindowAlign;
        private System.Windows.Forms.Label lWindowAlign;
        private System.Windows.Forms.RadioButton rbWindowAlignTopLeft;
        private System.Windows.Forms.RadioButton rbWindowAlignCenterTop;
        private System.Windows.Forms.RadioButton rbWindowAlignCenterLeft;
        private System.Windows.Forms.RadioButton rbWindowAlignCenter;
        private System.Windows.Forms.RadioButton rbWindowAlignBottomLeft;
        private System.Windows.Forms.RadioButton rbWindowAlignBottomCenter;
        private System.Windows.Forms.RadioButton rbWindowAlignTopRight;
        private System.Windows.Forms.RadioButton rbWindowAlignCenterRight;
        private System.Windows.Forms.RadioButton rbWindowAlignBottomRight;
        private System.Windows.Forms.Panel panelWindowAlign;
        private System.Windows.Forms.CheckBox cbD3D8To9Only;
        private System.Windows.Forms.ComboBox cmbDLShadowDetail;
        private System.Windows.Forms.CheckBox cbReduceTextureMemUse;
        private System.Windows.Forms.Panel panelSShotDirButtons;
        private System.Windows.Forms.Label lScreenshotHelp;
        private System.Windows.Forms.CheckBox cbAutoFOV;
        private System.Windows.Forms.ComboBox cmbPerPixelLightFlags;
        public System.Windows.Forms.ComboBox cmbSShotSuffix;
        public System.Windows.Forms.Label lSShotSuffix;
        private System.Windows.Forms.Panel pDLAutoDist;
        private System.Windows.Forms.TableLayoutPanel tableAlignSSFormat;
        private System.Windows.Forms.TableLayoutPanel tableAlignDLFog;
        private System.Windows.Forms.TableLayoutPanel tableAlignDLStatics;
        private System.Windows.Forms.TableLayoutPanel tableAlignResolution;
        public System.Windows.Forms.GroupBox gbDLAutoDist;
        private System.Windows.Forms.TableLayoutPanel tableLayoutDLRight;
        private System.Windows.Forms.TableLayoutPanel tableLayoutDLLeft;
        private System.Windows.Forms.TableLayoutPanel tableLayoutDL;
        private System.Windows.Forms.Label lUIScale;
        private System.Windows.Forms.NumericUpDown udUIScale;
        private System.Windows.Forms.CheckBox cbBorderless;
        private System.Windows.Forms.TextBox tbRefreshRate;
        private System.Windows.Forms.Button bReportingShowLog;
        private System.Windows.Forms.Button bReportingShowDLWizardLog;
        private System.Windows.Forms.GroupBox gbErrorReporting;
        private System.Windows.Forms.CheckBox cbPerPixelLighting;
        private System.Windows.Forms.CheckBox cbDLSunShadows;
        private System.Windows.Forms.GroupBox gbXEFeatures;
        private System.Windows.Forms.Button bMWLightSettings;
        public System.Windows.Forms.CheckBox cbDLReflInterior;
        private System.Windows.Forms.TableLayoutPanel tableLayoutDisplay;
        private System.Windows.Forms.TableLayoutPanel tableLayoutScreenshots;
        private System.Windows.Forms.Button bMWLightingReset;
        private System.Windows.Forms.Label lInstructions;
        private System.Windows.Forms.TabPage tpInstructions;
        private System.Windows.Forms.CheckBox cbMenuCaching;
        private System.Windows.Forms.CheckBox cbAutoCrosshair;
        private System.Windows.Forms.CheckBox cbDLScattering;
        private System.Windows.Forms.NumericUpDown udFPSLimit;
        private System.Windows.Forms.Label lFPSLimit;
        private System.Windows.Forms.Panel pLanguage;
        public System.Windows.Forms.TabPage tpConfig;
        private System.Windows.Forms.NumericUpDown udLightingConst;
        private System.Windows.Forms.NumericUpDown udLightingLinear;
        private System.Windows.Forms.NumericUpDown udLightingQuad;
        private System.Windows.Forms.Label lLightingQuad;
        private System.Windows.Forms.Label lLightingLin;
        private System.Windows.Forms.Label lLightingConst;
        private System.Windows.Forms.GroupBox gbMWLighting;

        #endregion

        public Label lDLVeryFar;
        public Label lDLFar;
        public Label lDLNear;
        public Label lDLMinSize;
        public Label lDLEndDist;
        public CheckBox cbDLDistantStatics;
        public CheckBox cbDLDistantLand;
        public TextBox tbDLNearSize;
        public TabControl tabControl;
        public ContextMenu DudMenu;
        public OpenFileDialog OpenFileDialog;
        public SaveFileDialog SaveFileDialog;
        public ToolTip toolTip;
        public Button bShaderEd;
        public CheckBox cbHitFader;
        public CheckBox cbSubtitles;
        public CheckBox cbAudio;
        public CheckBox cbShowFPS;
        public Label lScreenshotStatus;
        public CheckBox cbScreenshots;
        public CheckBox cbHQShadows;
        public CheckBox cbYesToAll;
        public CheckBox cbThreadLoad;
        public TabPage tpInput;
        public Button bRemapper;
        public CheckBox cbAltCombat;
        public CheckBox cbSkipMovie;
        public Button bMacroEd;
        public Label lSShotFormat;
        public CheckBox cbHWShader;
        public ComboBox cmbSShotFormat;
        public ComboBox cmbAnisoLevel;
        public Label lAnisoLevel;
        public ComboBox cmbFogMode;
        public Label lFogMode;
        public CheckBox cbFPSCounter;
        public CheckBox cbDisplayMessages;
        public TabPage tpGlobal;
        public TextBox tbResolution;
        public Button bSelectResolution;
        public Label lResolution;
        public CheckBox cbWindowed;
        public Label lRefreshRate;
        public ComboBox cmbAntiAlias;
        public Label lAntiAlias;
        public ComboBox cmbVWait;
        public Label lVWait;
        public CheckBox cbDisableMWSE;
        public TabPage tpDL;
        public CheckBox cbDLReflNStatics;
        public CheckBox cbDLReflLand;
        public GroupBox gbDistantLand;
        public GroupBox gbDLWtrRefl;
        public GroupBox gbDLStatics;
        public CheckBox cbDLAutoDist;
        public GroupBox gbDLFog;
        public Label lDLFogB;
        public Label lDLFogA;
        public Label lDLFogStart;
        public Label lDLFogEnd;
        public NumericUpDown udDLDrawDist;
        public NumericUpDown udDLSizeVeryFar;
        public NumericUpDown udDLSizeFar;
        public NumericUpDown udDLDistVeryFar;
        public NumericUpDown udDLDistFar;
        public NumericUpDown udDLDistNear;
        public NumericUpDown udDLFogAStart;
        public NumericUpDown udDLFogAEnd;
        public NumericUpDown udDLFogBEnd;
        public NumericUpDown udDLFogBStart;
        public Button bDLWthr;
        public NumericUpDown udFOV;
        public Label lFOV;
        public Button bResetSettings;
        public Button bAbout;
        public Button bViewCaps;
        public Button bExport;
        public Button bImport;
        public Button bHelp;
        public GroupBox gbMainInfo;
        public GroupBox gbMainSettings;
        public Button bDistantLandWizard;
        public GroupBox gbDLDrawDist;
        public Label lDLDrawDist;
        public CheckBox cbClearINI;
        public GroupBox gbMWGeneral;
        public GroupBox gbDisplay;
        public GroupBox gbScene;
        public TextBox tbAspect;
        public Label lAspect;
        public GroupBox gbSShot;
        public Label lSShotDir;
        public TextBox tbSShotDir;
        public Button bSShotDirClear;
        public Button bSShotDirBrowse;
        public TextBox tbSShotName;
        public Label lSShotName;
        public FolderBrowserDialog SShotFolderDialog;
        public NumericUpDown udDLFogIEnd;
        public NumericUpDown udDLFogIStart;
        public Label lDLFogI;
		public CheckBox cbDLSkyRefl;
        public CheckBox cbDLDynRipples;
        private CheckBox cbDisableMGE;
        private GroupBox gbInputOpts;
        private GroupBox gbInputTools;
        public System.Windows.Forms.GroupBox gbDLWater;
        private CheckBox cbDLReflBlur;
        private GroupBox gbDLWtrCaust;
        public NumericUpDown udDLWtrCaust;
        private GroupBox gbDLWtrWave;
        public NumericUpDown udDLWtrWave;
        public Label lDLWtrCaust;
        public Label lDLWtrWave;
        public NumericUpDown udDLFogExpMul;
        public Label lDLFogExpMul;
        public CheckBox cbDLFogExp;
        private RadioButton rbDLAutoByAFogEnd;
        private RadioButton rbDLAutoByDrawDist;
        private GroupBox gbMainUI;
        private ComboBox cmbUILanguage;
        private Label lUILanguage;
        private Label lTipReadSpd;
        private Label lTipRSpdUnit;
        public ComboBox cmbTipReadSpd;
        private GroupBox gbMsgs;
        private ComboBox cmbMsgsLocale;
        private Label lMsgsLanguage;
        public NumericUpDown udMsgsTime;
        private Label lMsgsTimeUnit;
        private Label lMsgsTime;
        private Panel pDLStatics;
        private CheckBox cbUILangAuto;
        private Panel pCam3rdPrsn;
        private CheckBox cbCam3rdPrsn;
        private GroupBox gbCam3rdPrsn;
        public NumericUpDown udCam3rdZ;
        public NumericUpDown udCam3rdY;
        public NumericUpDown udCam3rdX;
        private Label lCam3rdX;
        private Label lCam3rdY;
        private Label lCam3rdZ;
    }
}