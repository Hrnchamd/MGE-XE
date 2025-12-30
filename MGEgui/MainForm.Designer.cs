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
            this.cbUseSharedMemory = new System.Windows.Forms.CheckBox();
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
            this.tpInput.Location = new System.Drawing.Point(4, 34);
            this.tpInput.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tpInput.Name = "tpInput";
            this.tpInput.Size = new System.Drawing.Size(1078, 714);
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
            this.gbMWLighting.Location = new System.Drawing.Point(585, 194);
            this.gbMWLighting.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMWLighting.Name = "gbMWLighting";
            this.gbMWLighting.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMWLighting.Size = new System.Drawing.Size(477, 108);
            this.gbMWLighting.TabIndex = 10;
            this.gbMWLighting.TabStop = false;
            this.gbMWLighting.Text = "Dynamic lighting coefficients";
            // 
            // bMWLightingReset
            // 
            this.bMWLightingReset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bMWLightingReset.Location = new System.Drawing.Point(384, 0);
            this.bMWLightingReset.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bMWLightingReset.Name = "bMWLightingReset";
            this.bMWLightingReset.Size = new System.Drawing.Size(84, 33);
            this.bMWLightingReset.TabIndex = 6;
            this.bMWLightingReset.Text = "Reset";
            this.bMWLightingReset.UseVisualStyleBackColor = true;
            this.bMWLightingReset.Click += new System.EventHandler(this.bMWLightingReset_Click);
            // 
            // lLightingConst
            // 
            this.lLightingConst.AutoSize = true;
            this.lLightingConst.Location = new System.Drawing.Point(273, 32);
            this.lLightingConst.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lLightingConst.Name = "lLightingConst";
            this.lLightingConst.Size = new System.Drawing.Size(83, 25);
            this.lLightingConst.TabIndex = 5;
            this.lLightingConst.Text = "Constant";
            // 
            // lLightingLin
            // 
            this.lLightingLin.AutoSize = true;
            this.lLightingLin.Location = new System.Drawing.Point(146, 32);
            this.lLightingLin.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lLightingLin.Name = "lLightingLin";
            this.lLightingLin.Size = new System.Drawing.Size(58, 25);
            this.lLightingLin.TabIndex = 4;
            this.lLightingLin.Text = "Linear";
            // 
            // lLightingQuad
            // 
            this.lLightingQuad.AutoSize = true;
            this.lLightingQuad.Location = new System.Drawing.Point(18, 32);
            this.lLightingQuad.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lLightingQuad.Name = "lLightingQuad";
            this.lLightingQuad.Size = new System.Drawing.Size(89, 25);
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
            this.udLightingConst.Location = new System.Drawing.Point(276, 58);
            this.udLightingConst.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.udLightingConst.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.udLightingConst.Name = "udLightingConst";
            this.udLightingConst.Size = new System.Drawing.Size(96, 31);
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
            this.udLightingLinear.Location = new System.Drawing.Point(148, 58);
            this.udLightingLinear.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.udLightingLinear.Maximum = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.udLightingLinear.Name = "udLightingLinear";
            this.udLightingLinear.Size = new System.Drawing.Size(96, 31);
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
            this.udLightingQuad.Location = new System.Drawing.Point(21, 58);
            this.udLightingQuad.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.udLightingQuad.Maximum = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.udLightingQuad.Name = "udLightingQuad";
            this.udLightingQuad.Size = new System.Drawing.Size(96, 31);
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
            this.gbMWGeneral.Location = new System.Drawing.Point(12, 310);
            this.gbMWGeneral.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMWGeneral.Name = "gbMWGeneral";
            this.gbMWGeneral.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMWGeneral.Size = new System.Drawing.Size(1050, 278);
            this.gbMWGeneral.TabIndex = 9;
            this.gbMWGeneral.TabStop = false;
            this.gbMWGeneral.Text = "Morrowind.ini settings";
            // 
            // lScreenshotStatus
            // 
            this.lScreenshotStatus.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lScreenshotStatus.Location = new System.Drawing.Point(20, 182);
            this.lScreenshotStatus.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lScreenshotStatus.Name = "lScreenshotStatus";
            this.lScreenshotStatus.Size = new System.Drawing.Size(1005, 81);
            this.lScreenshotStatus.TabIndex = 9;
            this.lScreenshotStatus.Text = "Screenshots can be taken with the PrintScreen key. MGE will compress and save the" +
    "m for you.";
            // 
            // cbScreenshots
            // 
            this.cbScreenshots.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbScreenshots.AutoSize = true;
            this.cbScreenshots.Location = new System.Drawing.Point(525, 32);
            this.cbScreenshots.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbScreenshots.Name = "cbScreenshots";
            this.cbScreenshots.Size = new System.Drawing.Size(180, 29);
            this.cbScreenshots.TabIndex = 0;
            this.cbScreenshots.Text = "Allow screenshots";
            // 
            // cbHitFader
            // 
            this.cbHitFader.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbHitFader.AutoSize = true;
            this.cbHitFader.Checked = true;
            this.cbHitFader.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbHitFader.Location = new System.Drawing.Point(525, 135);
            this.cbHitFader.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbHitFader.Name = "cbHitFader";
            this.cbHitFader.Size = new System.Drawing.Size(107, 29);
            this.cbHitFader.TabIndex = 8;
            this.cbHitFader.Text = "Hit fader";
            // 
            // cbAudio
            // 
            this.cbAudio.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbAudio.AutoSize = true;
            this.cbAudio.Location = new System.Drawing.Point(525, 100);
            this.cbAudio.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbAudio.Name = "cbAudio";
            this.cbAudio.Size = new System.Drawing.Size(146, 29);
            this.cbAudio.TabIndex = 7;
            this.cbAudio.Text = "Disable audio";
            // 
            // cbHQShadows
            // 
            this.cbHQShadows.AutoSize = true;
            this.cbHQShadows.Location = new System.Drawing.Point(20, 66);
            this.cbHQShadows.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbHQShadows.Name = "cbHQShadows";
            this.cbHQShadows.Size = new System.Drawing.Size(311, 29);
            this.cbHQShadows.TabIndex = 1;
            this.cbHQShadows.Text = "High detail actor shadows [buggy]";
            // 
            // cbShowFPS
            // 
            this.cbShowFPS.AutoSize = true;
            this.cbShowFPS.Location = new System.Drawing.Point(20, 135);
            this.cbShowFPS.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbShowFPS.Name = "cbShowFPS";
            this.cbShowFPS.Size = new System.Drawing.Size(116, 29);
            this.cbShowFPS.TabIndex = 2;
            this.cbShowFPS.Text = "Show FPS";
            // 
            // cbThreadLoad
            // 
            this.cbThreadLoad.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbThreadLoad.AutoSize = true;
            this.cbThreadLoad.Checked = true;
            this.cbThreadLoad.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbThreadLoad.Location = new System.Drawing.Point(525, 66);
            this.cbThreadLoad.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbThreadLoad.Name = "cbThreadLoad";
            this.cbThreadLoad.Size = new System.Drawing.Size(157, 29);
            this.cbThreadLoad.TabIndex = 6;
            this.cbThreadLoad.Text = "Thread loading";
            // 
            // cbYesToAll
            // 
            this.cbYesToAll.AutoSize = true;
            this.cbYesToAll.Location = new System.Drawing.Point(20, 32);
            this.cbYesToAll.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbYesToAll.Name = "cbYesToAll";
            this.cbYesToAll.Size = new System.Drawing.Size(248, 29);
            this.cbYesToAll.TabIndex = 5;
            this.cbYesToAll.Text = "Allow yes to all load errors";
            // 
            // cbSubtitles
            // 
            this.cbSubtitles.AutoSize = true;
            this.cbSubtitles.Location = new System.Drawing.Point(20, 100);
            this.cbSubtitles.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbSubtitles.Name = "cbSubtitles";
            this.cbSubtitles.Size = new System.Drawing.Size(153, 29);
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
            this.gbMsgs.Location = new System.Drawing.Point(12, 592);
            this.gbMsgs.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMsgs.Name = "gbMsgs";
            this.gbMsgs.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMsgs.Size = new System.Drawing.Size(1050, 99);
            this.gbMsgs.TabIndex = 8;
            this.gbMsgs.TabStop = false;
            this.gbMsgs.Text = "MGE status messages";
            // 
            // cbDisplayMessages
            // 
            this.cbDisplayMessages.AutoSize = true;
            this.cbDisplayMessages.Location = new System.Drawing.Point(20, 45);
            this.cbDisplayMessages.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDisplayMessages.Name = "cbDisplayMessages";
            this.cbDisplayMessages.Size = new System.Drawing.Size(179, 29);
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
            this.udMsgsTime.Location = new System.Drawing.Point(754, 51);
            this.udMsgsTime.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.udMsgsTime.Size = new System.Drawing.Size(84, 31);
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
            this.cmbMsgsLocale.Location = new System.Drawing.Point(375, 51);
            this.cmbMsgsLocale.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbMsgsLocale.Name = "cmbMsgsLocale";
            this.cmbMsgsLocale.Size = new System.Drawing.Size(190, 33);
            this.cmbMsgsLocale.Sorted = true;
            this.cmbMsgsLocale.TabIndex = 0;
            this.cmbMsgsLocale.Text = "English (default)";
            // 
            // lMsgsTime
            // 
            this.lMsgsTime.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lMsgsTime.AutoSize = true;
            this.lMsgsTime.Location = new System.Drawing.Point(754, 24);
            this.lMsgsTime.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lMsgsTime.Name = "lMsgsTime";
            this.lMsgsTime.Size = new System.Drawing.Size(77, 25);
            this.lMsgsTime.TabIndex = 0;
            this.lMsgsTime.Text = "Timeout";
            // 
            // lMsgsLanguage
            // 
            this.lMsgsLanguage.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.lMsgsLanguage.AutoSize = true;
            this.lMsgsLanguage.Enabled = false;
            this.lMsgsLanguage.Location = new System.Drawing.Point(375, 24);
            this.lMsgsLanguage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lMsgsLanguage.Name = "lMsgsLanguage";
            this.lMsgsLanguage.Size = new System.Drawing.Size(182, 25);
            this.lMsgsLanguage.TabIndex = 0;
            this.lMsgsLanguage.Text = "Language localization";
            // 
            // lMsgsTimeUnit
            // 
            this.lMsgsTimeUnit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lMsgsTimeUnit.AutoSize = true;
            this.lMsgsTimeUnit.Location = new System.Drawing.Point(846, 54);
            this.lMsgsTimeUnit.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lMsgsTimeUnit.Name = "lMsgsTimeUnit";
            this.lMsgsTimeUnit.Size = new System.Drawing.Size(36, 25);
            this.lMsgsTimeUnit.TabIndex = 0;
            this.lMsgsTimeUnit.Text = "ms";
            // 
            // pCam3rdPrsn
            // 
            this.pCam3rdPrsn.Controls.Add(this.cbCam3rdPrsn);
            this.pCam3rdPrsn.Controls.Add(this.gbCam3rdPrsn);
            this.pCam3rdPrsn.Location = new System.Drawing.Point(12, 194);
            this.pCam3rdPrsn.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pCam3rdPrsn.Name = "pCam3rdPrsn";
            this.pCam3rdPrsn.Size = new System.Drawing.Size(414, 108);
            this.pCam3rdPrsn.TabIndex = 7;
            this.pCam3rdPrsn.TabStop = true;
            // 
            // cbCam3rdPrsn
            // 
            this.cbCam3rdPrsn.AutoSize = true;
            this.cbCam3rdPrsn.Location = new System.Drawing.Point(12, -2);
            this.cbCam3rdPrsn.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbCam3rdPrsn.Name = "cbCam3rdPrsn";
            this.cbCam3rdPrsn.Size = new System.Drawing.Size(275, 29);
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
            this.gbCam3rdPrsn.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbCam3rdPrsn.Name = "gbCam3rdPrsn";
            this.gbCam3rdPrsn.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbCam3rdPrsn.Size = new System.Drawing.Size(414, 108);
            this.gbCam3rdPrsn.TabIndex = 1;
            this.gbCam3rdPrsn.TabStop = false;
            // 
            // udCam3rdZ
            // 
            this.udCam3rdZ.DecimalPlaces = 1;
            this.udCam3rdZ.Location = new System.Drawing.Point(254, 58);
            this.udCam3rdZ.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.udCam3rdZ.Size = new System.Drawing.Size(90, 31);
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
            this.udCam3rdY.Location = new System.Drawing.Point(136, 58);
            this.udCam3rdY.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.udCam3rdY.Size = new System.Drawing.Size(90, 31);
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
            this.udCam3rdX.Location = new System.Drawing.Point(20, 58);
            this.udCam3rdX.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.udCam3rdX.Size = new System.Drawing.Size(90, 31);
            this.udCam3rdX.TabIndex = 0;
            this.udCam3rdX.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.udCam3rdX.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
            // 
            // lCam3rdX
            // 
            this.lCam3rdX.AutoSize = true;
            this.lCam3rdX.Location = new System.Drawing.Point(16, 32);
            this.lCam3rdX.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lCam3rdX.Name = "lCam3rdX";
            this.lCam3rdX.Size = new System.Drawing.Size(74, 25);
            this.lCam3rdX.TabIndex = 3;
            this.lCam3rdX.Text = "X offset";
            // 
            // lCam3rdY
            // 
            this.lCam3rdY.AutoSize = true;
            this.lCam3rdY.Location = new System.Drawing.Point(134, 32);
            this.lCam3rdY.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lCam3rdY.Name = "lCam3rdY";
            this.lCam3rdY.Size = new System.Drawing.Size(73, 25);
            this.lCam3rdY.TabIndex = 4;
            this.lCam3rdY.Text = "Y offset";
            // 
            // lCam3rdZ
            // 
            this.lCam3rdZ.AutoSize = true;
            this.lCam3rdZ.Location = new System.Drawing.Point(250, 32);
            this.lCam3rdZ.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lCam3rdZ.Name = "lCam3rdZ";
            this.lCam3rdZ.Size = new System.Drawing.Size(73, 25);
            this.lCam3rdZ.TabIndex = 5;
            this.lCam3rdZ.Text = "Z offset";
            // 
            // gbInputTools
            // 
            this.gbInputTools.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.gbInputTools.Controls.Add(this.bMacroEd);
            this.gbInputTools.Controls.Add(this.bRemapper);
            this.gbInputTools.Location = new System.Drawing.Point(786, 4);
            this.gbInputTools.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbInputTools.Name = "gbInputTools";
            this.gbInputTools.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbInputTools.Size = new System.Drawing.Size(276, 178);
            this.gbInputTools.TabIndex = 1;
            this.gbInputTools.TabStop = false;
            this.gbInputTools.Text = "Input tools";
            // 
            // bMacroEd
            // 
            this.bMacroEd.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bMacroEd.AutoSize = true;
            this.bMacroEd.Location = new System.Drawing.Point(9, 28);
            this.bMacroEd.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bMacroEd.Name = "bMacroEd";
            this.bMacroEd.Size = new System.Drawing.Size(258, 50);
            this.bMacroEd.TabIndex = 0;
            this.bMacroEd.Text = "Macro editor";
            this.bMacroEd.Click += new System.EventHandler(this.bMacroEd_Click);
            // 
            // bRemapper
            // 
            this.bRemapper.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bRemapper.AutoSize = true;
            this.bRemapper.Location = new System.Drawing.Point(9, 90);
            this.bRemapper.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bRemapper.Name = "bRemapper";
            this.bRemapper.Size = new System.Drawing.Size(258, 50);
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
            this.gbInputOpts.Location = new System.Drawing.Point(12, 4);
            this.gbInputOpts.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbInputOpts.Name = "gbInputOpts";
            this.gbInputOpts.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbInputOpts.Size = new System.Drawing.Size(765, 178);
            this.gbInputOpts.TabIndex = 0;
            this.gbInputOpts.TabStop = false;
            this.gbInputOpts.Text = "Options";
            // 
            // cbD3D8To9Only
            // 
            this.cbD3D8To9Only.AutoSize = true;
            this.cbD3D8To9Only.Location = new System.Drawing.Point(16, 116);
            this.cbD3D8To9Only.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbD3D8To9Only.Name = "cbD3D8To9Only";
            this.cbD3D8To9Only.Size = new System.Drawing.Size(235, 29);
            this.cbD3D8To9Only.TabIndex = 12;
            this.cbD3D8To9Only.Text = "Use D3D8To9 proxy only";
            this.cbD3D8To9Only.UseVisualStyleBackColor = true;
            // 
            // cbMenuCaching
            // 
            this.cbMenuCaching.AutoSize = true;
            this.cbMenuCaching.Checked = true;
            this.cbMenuCaching.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbMenuCaching.Location = new System.Drawing.Point(273, 132);
            this.cbMenuCaching.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbMenuCaching.Name = "cbMenuCaching";
            this.cbMenuCaching.Size = new System.Drawing.Size(242, 29);
            this.cbMenuCaching.TabIndex = 11;
            this.cbMenuCaching.Text = "Responsive menu caching";
            this.cbMenuCaching.UseVisualStyleBackColor = true;
            // 
            // cbAutoCrosshair
            // 
            this.cbAutoCrosshair.AutoSize = true;
            this.cbAutoCrosshair.Location = new System.Drawing.Point(273, 98);
            this.cbAutoCrosshair.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbAutoCrosshair.Name = "cbAutoCrosshair";
            this.cbAutoCrosshair.Size = new System.Drawing.Size(186, 29);
            this.cbAutoCrosshair.TabIndex = 10;
            this.cbAutoCrosshair.Text = "Crosshair autohide";
            this.cbAutoCrosshair.UseVisualStyleBackColor = true;
            // 
            // cbDisableMGE
            // 
            this.cbDisableMGE.AutoSize = true;
            this.cbDisableMGE.Location = new System.Drawing.Point(16, 28);
            this.cbDisableMGE.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDisableMGE.Name = "cbDisableMGE";
            this.cbDisableMGE.Size = new System.Drawing.Size(207, 29);
            this.cbDisableMGE.TabIndex = 9;
            this.cbDisableMGE.Text = "Disable MGE in game";
            this.cbDisableMGE.UseVisualStyleBackColor = true;
            this.cbDisableMGE.CheckedChanged += new System.EventHandler(this.cbDisableMGE_CheckedChanged);
            // 
            // cbDisableMWSE
            // 
            this.cbDisableMWSE.AutoSize = true;
            this.cbDisableMWSE.Location = new System.Drawing.Point(16, 63);
            this.cbDisableMWSE.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDisableMWSE.Name = "cbDisableMWSE";
            this.cbDisableMWSE.Size = new System.Drawing.Size(216, 29);
            this.cbDisableMWSE.TabIndex = 8;
            this.cbDisableMWSE.Text = "Disable internal MWSE";
            // 
            // cbSkipMovie
            // 
            this.cbSkipMovie.AutoSize = true;
            this.cbSkipMovie.Checked = true;
            this.cbSkipMovie.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbSkipMovie.Location = new System.Drawing.Point(273, 28);
            this.cbSkipMovie.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbSkipMovie.Name = "cbSkipMovie";
            this.cbSkipMovie.Size = new System.Drawing.Size(197, 29);
            this.cbSkipMovie.TabIndex = 0;
            this.cbSkipMovie.Text = "Skip opening movie";
            // 
            // cbAltCombat
            // 
            this.cbAltCombat.AutoSize = true;
            this.cbAltCombat.Location = new System.Drawing.Point(273, 63);
            this.cbAltCombat.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbAltCombat.Name = "cbAltCombat";
            this.cbAltCombat.Size = new System.Drawing.Size(257, 29);
            this.cbAltCombat.TabIndex = 2;
            this.cbAltCombat.Text = "Alternative combat controls";
            // 
            // lSShotFormat
            // 
            this.lSShotFormat.AutoSize = true;
            this.lSShotFormat.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSShotFormat.Location = new System.Drawing.Point(47, 0);
            this.lSShotFormat.Margin = new System.Windows.Forms.Padding(4, 0, 4, 3);
            this.lSShotFormat.Name = "lSShotFormat";
            this.lSShotFormat.Size = new System.Drawing.Size(69, 41);
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
            this.cmbSShotFormat.Location = new System.Drawing.Point(124, 4);
            this.cmbSShotFormat.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbSShotFormat.Name = "cmbSShotFormat";
            this.cmbSShotFormat.Size = new System.Drawing.Size(82, 33);
            this.cmbSShotFormat.TabIndex = 1;
            this.cmbSShotFormat.Text = "PNG";
            // 
            // tpGlobal
            // 
            this.tpGlobal.Controls.Add(this.gbSShot);
            this.tpGlobal.Controls.Add(this.gbScene);
            this.tpGlobal.Controls.Add(this.gbDisplay);
            this.tpGlobal.Location = new System.Drawing.Point(4, 34);
            this.tpGlobal.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tpGlobal.Name = "tpGlobal";
            this.tpGlobal.Size = new System.Drawing.Size(1078, 714);
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
            this.gbSShot.Location = new System.Drawing.Point(12, 435);
            this.gbSShot.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbSShot.Name = "gbSShot";
            this.gbSShot.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbSShot.Size = new System.Drawing.Size(1050, 266);
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
            this.tableLayoutScreenshots.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 158F));
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
            this.tableLayoutScreenshots.Location = new System.Drawing.Point(9, 33);
            this.tableLayoutScreenshots.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tableLayoutScreenshots.Name = "tableLayoutScreenshots";
            this.tableLayoutScreenshots.RowCount = 6;
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 6F));
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 6F));
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutScreenshots.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutScreenshots.Size = new System.Drawing.Size(1032, 231);
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
            this.tableAlignSSFormat.Location = new System.Drawing.Point(822, 0);
            this.tableAlignSSFormat.Margin = new System.Windows.Forms.Padding(0);
            this.tableAlignSSFormat.MinimumSize = new System.Drawing.Size(210, 44);
            this.tableAlignSSFormat.Name = "tableAlignSSFormat";
            this.tableAlignSSFormat.RowCount = 1;
            this.tableAlignSSFormat.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableAlignSSFormat.Size = new System.Drawing.Size(210, 44);
            this.tableAlignSSFormat.TabIndex = 7;
            // 
            // lSShotName
            // 
            this.lSShotName.AutoSize = true;
            this.lSShotName.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSShotName.Location = new System.Drawing.Point(18, 0);
            this.lSShotName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 3);
            this.lSShotName.Name = "lSShotName";
            this.lSShotName.Size = new System.Drawing.Size(136, 41);
            this.lSShotName.TabIndex = 0;
            this.lSShotName.Text = "File name prefix";
            this.lSShotName.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // tbSShotName
            // 
            this.tbSShotName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.tbSShotName.Location = new System.Drawing.Point(162, 6);
            this.tbSShotName.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbSShotName.Name = "tbSShotName";
            this.tbSShotName.Size = new System.Drawing.Size(637, 31);
            this.tbSShotName.TabIndex = 0;
            this.tbSShotName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.fileNameFilter_KeyPress);
            // 
            // lSShotDir
            // 
            this.lSShotDir.AutoSize = true;
            this.lSShotDir.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSShotDir.Location = new System.Drawing.Point(10, 97);
            this.lSShotDir.Margin = new System.Windows.Forms.Padding(4, 0, 4, 3);
            this.lSShotDir.Name = "lSShotDir";
            this.lSShotDir.Size = new System.Drawing.Size(144, 39);
            this.lSShotDir.TabIndex = 0;
            this.lSShotDir.Text = "Output directory";
            this.lSShotDir.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // tbSShotDir
            // 
            this.tbSShotDir.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.tbSShotDir.Location = new System.Drawing.Point(162, 102);
            this.tbSShotDir.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbSShotDir.Name = "tbSShotDir";
            this.tbSShotDir.ReadOnly = true;
            this.tbSShotDir.Size = new System.Drawing.Size(637, 31);
            this.tbSShotDir.TabIndex = 3;
            this.tbSShotDir.Text = "- Morrowind folder -";
            this.tbSShotDir.TextAlignChanged += new System.EventHandler(this.tbSSDir_TextAlignChanged);
            // 
            // lSShotSuffix
            // 
            this.lSShotSuffix.AutoSize = true;
            this.lSShotSuffix.Dock = System.Windows.Forms.DockStyle.Right;
            this.lSShotSuffix.Location = new System.Drawing.Point(20, 50);
            this.lSShotSuffix.Margin = new System.Windows.Forms.Padding(4, 0, 4, 3);
            this.lSShotSuffix.Name = "lSShotSuffix";
            this.lSShotSuffix.Size = new System.Drawing.Size(134, 38);
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
            this.cmbSShotSuffix.Location = new System.Drawing.Point(162, 54);
            this.cmbSShotSuffix.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbSShotSuffix.Name = "cmbSShotSuffix";
            this.cmbSShotSuffix.Size = new System.Drawing.Size(637, 33);
            this.cmbSShotSuffix.TabIndex = 5;
            this.cmbSShotSuffix.Text = "Timestamp";
            // 
            // lScreenshotHelp
            // 
            this.lScreenshotHelp.AutoSize = true;
            this.tableLayoutScreenshots.SetColumnSpan(this.lScreenshotHelp, 3);
            this.lScreenshotHelp.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lScreenshotHelp.Location = new System.Drawing.Point(12, 139);
            this.lScreenshotHelp.Margin = new System.Windows.Forms.Padding(12, 0, 33, 0);
            this.lScreenshotHelp.Name = "lScreenshotHelp";
            this.lScreenshotHelp.Size = new System.Drawing.Size(987, 92);
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
            this.panelSShotDirButtons.Location = new System.Drawing.Point(803, 97);
            this.panelSShotDirButtons.Margin = new System.Windows.Forms.Padding(0);
            this.panelSShotDirButtons.Name = "panelSShotDirButtons";
            this.panelSShotDirButtons.Size = new System.Drawing.Size(229, 42);
            this.panelSShotDirButtons.TabIndex = 8;
            // 
            // bSShotDirBrowse
            // 
            this.bSShotDirBrowse.Location = new System.Drawing.Point(6, 4);
            this.bSShotDirBrowse.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bSShotDirBrowse.Name = "bSShotDirBrowse";
            this.bSShotDirBrowse.Size = new System.Drawing.Size(105, 34);
            this.bSShotDirBrowse.TabIndex = 4;
            this.bSShotDirBrowse.Text = "Browse";
            this.bSShotDirBrowse.UseVisualStyleBackColor = true;
            this.bSShotDirBrowse.Click += new System.EventHandler(this.bSShotDirBrowse_Click);
            // 
            // bSShotDirClear
            // 
            this.bSShotDirClear.Location = new System.Drawing.Point(120, 4);
            this.bSShotDirClear.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bSShotDirClear.Name = "bSShotDirClear";
            this.bSShotDirClear.Size = new System.Drawing.Size(105, 34);
            this.bSShotDirClear.TabIndex = 5;
            this.bSShotDirClear.Text = "Clear";
            this.bSShotDirClear.UseVisualStyleBackColor = true;
            this.bSShotDirClear.Click += new System.EventHandler(this.bSSDirClear_Click);
            // 
            // gbScene
            // 
            this.gbScene.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gbScene.Controls.Add(this.cbUseSharedMemory);
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
            this.gbScene.Location = new System.Drawing.Point(12, 213);
            this.gbScene.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbScene.Name = "gbScene";
            this.gbScene.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbScene.Size = new System.Drawing.Size(1050, 213);
            this.gbScene.TabIndex = 1;
            this.gbScene.TabStop = false;
            this.gbScene.Text = "Renderer";
            // 
            // cbReduceTextureMemUse
            // 
            this.cbReduceTextureMemUse.AutoSize = true;
            this.cbReduceTextureMemUse.Location = new System.Drawing.Point(18, 129);
            this.cbReduceTextureMemUse.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbReduceTextureMemUse.Name = "cbReduceTextureMemUse";
            this.cbReduceTextureMemUse.Size = new System.Drawing.Size(258, 29);
            this.cbReduceTextureMemUse.TabIndex = 24;
            this.cbReduceTextureMemUse.Text = "Reduce texture memory use";
            this.cbReduceTextureMemUse.UseVisualStyleBackColor = true;
            // 
            // cbAutoFOV
            // 
            this.cbAutoFOV.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbAutoFOV.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbAutoFOV.Location = new System.Drawing.Point(488, 36);
            this.cbAutoFOV.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbAutoFOV.Name = "cbAutoFOV";
            this.cbAutoFOV.Size = new System.Drawing.Size(180, 36);
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
            this.udUIScale.Location = new System.Drawing.Point(684, 154);
            this.udUIScale.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.udUIScale.Size = new System.Drawing.Size(98, 31);
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
            this.lUIScale.Location = new System.Drawing.Point(790, 158);
            this.lUIScale.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lUIScale.Name = "lUIScale";
            this.lUIScale.Size = new System.Drawing.Size(138, 25);
            this.lUIScale.TabIndex = 22;
            this.lUIScale.Text = "Menu UI scaling";
            // 
            // lFPSLimit
            // 
            this.lFPSLimit.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.lFPSLimit.AutoSize = true;
            this.lFPSLimit.Location = new System.Drawing.Point(790, 78);
            this.lFPSLimit.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lFPSLimit.Name = "lFPSLimit";
            this.lFPSLimit.Size = new System.Drawing.Size(95, 25);
            this.lFPSLimit.TabIndex = 19;
            this.lFPSLimit.Text = "FPS limiter";
            // 
            // udFPSLimit
            // 
            this.udFPSLimit.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.udFPSLimit.Location = new System.Drawing.Point(686, 75);
            this.udFPSLimit.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.udFPSLimit.Size = new System.Drawing.Size(96, 31);
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
            this.bShaderEd.Location = new System.Drawing.Point(228, 33);
            this.bShaderEd.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bShaderEd.MinimumSize = new System.Drawing.Size(186, 38);
            this.bShaderEd.Name = "bShaderEd";
            this.bShaderEd.Size = new System.Drawing.Size(190, 45);
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
            this.cmbFogMode.Location = new System.Drawing.Point(532, 114);
            this.cmbFogMode.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbFogMode.Name = "cmbFogMode";
            this.cmbFogMode.Size = new System.Drawing.Size(247, 33);
            this.cmbFogMode.TabIndex = 13;
            this.cmbFogMode.Text = "Depth pixel (Fast)";
            this.cmbFogMode.SelectedIndexChanged += new System.EventHandler(this.cmbFogMode_SelectedIndexChanged);
            // 
            // lFogMode
            // 
            this.lFogMode.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.lFogMode.AutoSize = true;
            this.lFogMode.Location = new System.Drawing.Point(790, 118);
            this.lFogMode.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lFogMode.Name = "lFogMode";
            this.lFogMode.Size = new System.Drawing.Size(95, 25);
            this.lFogMode.TabIndex = 12;
            this.lFogMode.Text = "Fog mode";
            // 
            // cbHWShader
            // 
            this.cbHWShader.AutoSize = true;
            this.cbHWShader.Location = new System.Drawing.Point(18, 40);
            this.cbHWShader.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbHWShader.Name = "cbHWShader";
            this.cbHWShader.Size = new System.Drawing.Size(156, 29);
            this.cbHWShader.TabIndex = 14;
            this.cbHWShader.Text = "Enable shaders";
            // 
            // cbFPSCounter
            // 
            this.cbFPSCounter.AutoSize = true;
            this.cbFPSCounter.Location = new System.Drawing.Point(18, 92);
            this.cbFPSCounter.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbFPSCounter.Name = "cbFPSCounter";
            this.cbFPSCounter.Size = new System.Drawing.Size(130, 29);
            this.cbFPSCounter.TabIndex = 5;
            this.cbFPSCounter.Text = "Display FPS";
            // 
            // udFOV
            // 
            this.udFOV.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.udFOV.DecimalPlaces = 1;
            this.udFOV.Location = new System.Drawing.Point(686, 36);
            this.udFOV.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.udFOV.Size = new System.Drawing.Size(96, 31);
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
            this.lFOV.Location = new System.Drawing.Point(790, 39);
            this.lFOV.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lFOV.Name = "lFOV";
            this.lFOV.Size = new System.Drawing.Size(93, 25);
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
            this.gbDisplay.Location = new System.Drawing.Point(12, 4);
            this.gbDisplay.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDisplay.Name = "gbDisplay";
            this.gbDisplay.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDisplay.Size = new System.Drawing.Size(1050, 200);
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
            this.tableLayoutWindowAlign.Location = new System.Drawing.Point(842, 18);
            this.tableLayoutWindowAlign.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tableLayoutWindowAlign.Name = "tableLayoutWindowAlign";
            this.tableLayoutWindowAlign.RowCount = 2;
            this.tableLayoutWindowAlign.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutWindowAlign.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutWindowAlign.Size = new System.Drawing.Size(195, 123);
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
            this.panelWindowAlign.Location = new System.Drawing.Point(55, 29);
            this.panelWindowAlign.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.panelWindowAlign.Name = "panelWindowAlign";
            this.panelWindowAlign.Size = new System.Drawing.Size(84, 84);
            this.panelWindowAlign.TabIndex = 10;
            // 
            // rbWindowAlignBottomRight
            // 
            this.rbWindowAlignBottomRight.Appearance = System.Windows.Forms.Appearance.Button;
            this.rbWindowAlignBottomRight.Font = new System.Drawing.Font("Segoe UI", 8F);
            this.rbWindowAlignBottomRight.Location = new System.Drawing.Point(54, 54);
            this.rbWindowAlignBottomRight.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignBottomRight.Name = "rbWindowAlignBottomRight";
            this.rbWindowAlignBottomRight.Size = new System.Drawing.Size(30, 30);
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
            this.rbWindowAlignCenterRight.Location = new System.Drawing.Point(54, 27);
            this.rbWindowAlignCenterRight.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignCenterRight.Name = "rbWindowAlignCenterRight";
            this.rbWindowAlignCenterRight.Size = new System.Drawing.Size(30, 30);
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
            this.rbWindowAlignTopRight.Location = new System.Drawing.Point(54, 0);
            this.rbWindowAlignTopRight.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignTopRight.Name = "rbWindowAlignTopRight";
            this.rbWindowAlignTopRight.Size = new System.Drawing.Size(30, 30);
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
            this.rbWindowAlignBottomCenter.Location = new System.Drawing.Point(27, 54);
            this.rbWindowAlignBottomCenter.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignBottomCenter.Name = "rbWindowAlignBottomCenter";
            this.rbWindowAlignBottomCenter.Size = new System.Drawing.Size(30, 30);
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
            this.rbWindowAlignBottomLeft.Location = new System.Drawing.Point(0, 54);
            this.rbWindowAlignBottomLeft.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignBottomLeft.Name = "rbWindowAlignBottomLeft";
            this.rbWindowAlignBottomLeft.Size = new System.Drawing.Size(30, 30);
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
            this.rbWindowAlignCenter.Location = new System.Drawing.Point(27, 27);
            this.rbWindowAlignCenter.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignCenter.Name = "rbWindowAlignCenter";
            this.rbWindowAlignCenter.Size = new System.Drawing.Size(30, 30);
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
            this.rbWindowAlignCenterLeft.Location = new System.Drawing.Point(0, 27);
            this.rbWindowAlignCenterLeft.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignCenterLeft.Name = "rbWindowAlignCenterLeft";
            this.rbWindowAlignCenterLeft.Size = new System.Drawing.Size(30, 30);
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
            this.rbWindowAlignCenterTop.Location = new System.Drawing.Point(27, 0);
            this.rbWindowAlignCenterTop.Margin = new System.Windows.Forms.Padding(0);
            this.rbWindowAlignCenterTop.Name = "rbWindowAlignCenterTop";
            this.rbWindowAlignCenterTop.Size = new System.Drawing.Size(30, 30);
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
            this.rbWindowAlignTopLeft.Size = new System.Drawing.Size(30, 30);
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
            this.lWindowAlign.Location = new System.Drawing.Point(4, 0);
            this.lWindowAlign.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lWindowAlign.Name = "lWindowAlign";
            this.lWindowAlign.Size = new System.Drawing.Size(187, 25);
            this.lWindowAlign.TabIndex = 9;
            this.lWindowAlign.Text = "Window location";
            this.lWindowAlign.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // tableAlignResolution
            // 
            this.tableAlignResolution.ColumnCount = 1;
            this.tableAlignResolution.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableAlignResolution.Controls.Add(this.lResolution, 0, 0);
            this.tableAlignResolution.Location = new System.Drawing.Point(6, 33);
            this.tableAlignResolution.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tableAlignResolution.Name = "tableAlignResolution";
            this.tableAlignResolution.RowCount = 1;
            this.tableAlignResolution.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableAlignResolution.Size = new System.Drawing.Size(144, 34);
            this.tableAlignResolution.TabIndex = 8;
            // 
            // lResolution
            // 
            this.lResolution.AutoSize = true;
            this.lResolution.Dock = System.Windows.Forms.DockStyle.Right;
            this.lResolution.Location = new System.Drawing.Point(49, 0);
            this.lResolution.Margin = new System.Windows.Forms.Padding(0);
            this.lResolution.Name = "lResolution";
            this.lResolution.Size = new System.Drawing.Size(95, 34);
            this.lResolution.TabIndex = 0;
            this.lResolution.Text = "Resolution";
            this.lResolution.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // cbBorderless
            // 
            this.cbBorderless.AutoSize = true;
            this.cbBorderless.Enabled = false;
            this.cbBorderless.Location = new System.Drawing.Point(612, 80);
            this.cbBorderless.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbBorderless.Name = "cbBorderless";
            this.cbBorderless.Size = new System.Drawing.Size(187, 29);
            this.cbBorderless.TabIndex = 7;
            this.cbBorderless.Text = "Borderless window";
            this.cbBorderless.UseVisualStyleBackColor = true;
            // 
            // tbRefreshRate
            // 
            this.tbRefreshRate.Location = new System.Drawing.Point(288, 76);
            this.tbRefreshRate.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbRefreshRate.Name = "tbRefreshRate";
            this.tbRefreshRate.ReadOnly = true;
            this.tbRefreshRate.Size = new System.Drawing.Size(76, 31);
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
            this.tableLayoutDisplay.Location = new System.Drawing.Point(15, 128);
            this.tableLayoutDisplay.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tableLayoutDisplay.Name = "tableLayoutDisplay";
            this.tableLayoutDisplay.RowCount = 1;
            this.tableLayoutDisplay.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 63F));
            this.tableLayoutDisplay.Size = new System.Drawing.Size(1022, 63);
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
            this.cmbAntiAlias.Location = new System.Drawing.Point(4, 15);
            this.cmbAntiAlias.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbAntiAlias.Name = "cmbAntiAlias";
            this.cmbAntiAlias.Size = new System.Drawing.Size(94, 33);
            this.cmbAntiAlias.TabIndex = 0;
            this.cmbAntiAlias.Text = "Off";
            this.cmbAntiAlias.SelectedIndexChanged += new System.EventHandler(this.cmbAlias_SelectedIndexChanged);
            this.cmbAntiAlias.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
            // 
            // lAntiAlias
            // 
            this.lAntiAlias.AutoSize = true;
            this.lAntiAlias.Dock = System.Windows.Forms.DockStyle.Left;
            this.lAntiAlias.Location = new System.Drawing.Point(106, 0);
            this.lAntiAlias.Margin = new System.Windows.Forms.Padding(4, 0, 4, 3);
            this.lAntiAlias.Name = "lAntiAlias";
            this.lAntiAlias.Size = new System.Drawing.Size(103, 60);
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
            this.cmbVWait.Location = new System.Drawing.Point(691, 15);
            this.cmbVWait.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbVWait.Name = "cmbVWait";
            this.cmbVWait.Size = new System.Drawing.Size(118, 33);
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
            this.cmbAnisoLevel.Location = new System.Drawing.Point(313, 15);
            this.cmbAnisoLevel.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbAnisoLevel.Name = "cmbAnisoLevel";
            this.cmbAnisoLevel.Size = new System.Drawing.Size(94, 33);
            this.cmbAnisoLevel.TabIndex = 10;
            this.cmbAnisoLevel.Text = "Off";
            this.cmbAnisoLevel.SelectedIndexChanged += new System.EventHandler(this.cmbAnsiLevel_SelectedIndexChanged);
            // 
            // lAnisoLevel
            // 
            this.lAnisoLevel.AutoSize = true;
            this.lAnisoLevel.Dock = System.Windows.Forms.DockStyle.Left;
            this.lAnisoLevel.Location = new System.Drawing.Point(415, 0);
            this.lAnisoLevel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 3);
            this.lAnisoLevel.Name = "lAnisoLevel";
            this.lAnisoLevel.Size = new System.Drawing.Size(168, 60);
            this.lAnisoLevel.TabIndex = 8;
            this.lAnisoLevel.Text = "Anisotropic filtering";
            this.lAnisoLevel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lVWait
            // 
            this.lVWait.AutoSize = true;
            this.lVWait.Dock = System.Windows.Forms.DockStyle.Left;
            this.lVWait.Location = new System.Drawing.Point(817, 0);
            this.lVWait.Margin = new System.Windows.Forms.Padding(4, 0, 4, 3);
            this.lVWait.Name = "lVWait";
            this.lVWait.Size = new System.Drawing.Size(59, 60);
            this.lVWait.TabIndex = 0;
            this.lVWait.Text = "VSync";
            this.lVWait.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tbAspect
            // 
            this.tbAspect.Location = new System.Drawing.Point(288, 33);
            this.tbAspect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbAspect.Name = "tbAspect";
            this.tbAspect.ReadOnly = true;
            this.tbAspect.Size = new System.Drawing.Size(76, 31);
            this.tbAspect.TabIndex = 2;
            this.tbAspect.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // bSelectResolution
            // 
            this.bSelectResolution.Location = new System.Drawing.Point(14, 75);
            this.bSelectResolution.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bSelectResolution.Name = "bSelectResolution";
            this.bSelectResolution.Size = new System.Drawing.Size(267, 38);
            this.bSelectResolution.TabIndex = 1;
            this.bSelectResolution.Text = "Select screen resolution";
            this.bSelectResolution.Click += new System.EventHandler(this.bSelectResolution_Click);
            // 
            // cbWindowed
            // 
            this.cbWindowed.AutoSize = true;
            this.cbWindowed.Location = new System.Drawing.Point(612, 38);
            this.cbWindowed.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbWindowed.Name = "cbWindowed";
            this.cbWindowed.Size = new System.Drawing.Size(176, 29);
            this.cbWindowed.TabIndex = 3;
            this.cbWindowed.Text = "Windowed mode";
            this.cbWindowed.CheckedChanged += new System.EventHandler(this.cbWindowed_CheckedChanged);
            // 
            // tbResolution
            // 
            this.tbResolution.Location = new System.Drawing.Point(159, 33);
            this.tbResolution.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbResolution.Name = "tbResolution";
            this.tbResolution.ReadOnly = true;
            this.tbResolution.Size = new System.Drawing.Size(118, 31);
            this.tbResolution.TabIndex = 0;
            this.tbResolution.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lAspect
            // 
            this.lAspect.AutoSize = true;
            this.lAspect.Location = new System.Drawing.Point(375, 38);
            this.lAspect.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lAspect.Name = "lAspect";
            this.lAspect.Size = new System.Drawing.Size(107, 25);
            this.lAspect.TabIndex = 0;
            this.lAspect.Text = "Aspect ratio";
            this.lAspect.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // lRefreshRate
            // 
            this.lRefreshRate.AutoSize = true;
            this.lRefreshRate.Location = new System.Drawing.Point(375, 81);
            this.lRefreshRate.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lRefreshRate.Name = "lRefreshRate";
            this.lRefreshRate.Size = new System.Drawing.Size(105, 25);
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
            this.tabControl.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.ShowToolTips = true;
            this.tabControl.Size = new System.Drawing.Size(1086, 752);
            this.tabControl.TabIndex = 0;
            // 
            // tpDL
            // 
            this.tpDL.Controls.Add(this.bDistantLandWizard);
            this.tpDL.Controls.Add(this.cbDLDistantLand);
            this.tpDL.Controls.Add(this.gbDistantLand);
            this.tpDL.Location = new System.Drawing.Point(4, 34);
            this.tpDL.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tpDL.Name = "tpDL";
            this.tpDL.Size = new System.Drawing.Size(1078, 714);
            this.tpDL.TabIndex = 7;
            this.tpDL.Text = "Distant Land";
            this.tpDL.ToolTipText = "This tab controls whether and how distant land,\ndistant statics, animated grass, " +
    "reflective water\nare rendered, and also contains weather settings\nfor distant la" +
    "nd wind speed and fog range.";
            this.tpDL.UseVisualStyleBackColor = true;
            // 
            // bDistantLandWizard
            // 
            this.bDistantLandWizard.Location = new System.Drawing.Point(204, 63);
            this.bDistantLandWizard.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bDistantLandWizard.Name = "bDistantLandWizard";
            this.bDistantLandWizard.Size = new System.Drawing.Size(201, 63);
            this.bDistantLandWizard.TabIndex = 10;
            this.bDistantLandWizard.Text = "Distant land generator wizard";
            this.bDistantLandWizard.Click += new System.EventHandler(this.bDistantLandWizard_Click);
            // 
            // cbDLDistantLand
            // 
            this.cbDLDistantLand.AutoSize = true;
            this.cbDLDistantLand.Location = new System.Drawing.Point(24, 4);
            this.cbDLDistantLand.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLDistantLand.Name = "cbDLDistantLand";
            this.cbDLDistantLand.Size = new System.Drawing.Size(171, 29);
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
            this.gbDistantLand.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDistantLand.Name = "gbDistantLand";
            this.gbDistantLand.Padding = new System.Windows.Forms.Padding(4, 14, 4, 4);
            this.gbDistantLand.Size = new System.Drawing.Size(1078, 714);
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
            this.tableLayoutDL.Location = new System.Drawing.Point(4, 38);
            this.tableLayoutDL.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tableLayoutDL.Name = "tableLayoutDL";
            this.tableLayoutDL.RowCount = 1;
            this.tableLayoutDL.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutDL.Size = new System.Drawing.Size(1070, 672);
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
            this.tableLayoutDLLeft.Size = new System.Drawing.Size(524, 672);
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
            this.gbXEFeatures.Location = new System.Drawing.Point(4, 468);
            this.gbXEFeatures.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbXEFeatures.Name = "gbXEFeatures";
            this.gbXEFeatures.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbXEFeatures.Size = new System.Drawing.Size(516, 200);
            this.gbXEFeatures.TabIndex = 11;
            this.gbXEFeatures.TabStop = false;
            this.gbXEFeatures.Text = "XE";
            // 
            // cbDLSunShadows
            // 
            this.cbDLSunShadows.AutoSize = true;
            this.cbDLSunShadows.Location = new System.Drawing.Point(27, 38);
            this.cbDLSunShadows.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLSunShadows.Name = "cbDLSunShadows";
            this.cbDLSunShadows.Size = new System.Drawing.Size(225, 29);
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
            this.cmbDLShadowDetail.Location = new System.Drawing.Point(332, 36);
            this.cmbDLShadowDetail.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbDLShadowDetail.Name = "cmbDLShadowDetail";
            this.cmbDLShadowDetail.Size = new System.Drawing.Size(172, 33);
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
            this.cmbPerPixelLightFlags.Location = new System.Drawing.Point(304, 88);
            this.cmbPerPixelLightFlags.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbPerPixelLightFlags.Name = "cmbPerPixelLightFlags";
            this.cmbPerPixelLightFlags.Size = new System.Drawing.Size(200, 33);
            this.cmbPerPixelLightFlags.TabIndex = 11;
            this.cmbPerPixelLightFlags.Text = "always on";
            // 
            // cbPerPixelLighting
            // 
            this.cbPerPixelLighting.Location = new System.Drawing.Point(27, 78);
            this.cbPerPixelLighting.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbPerPixelLighting.Name = "cbPerPixelLighting";
            this.cbPerPixelLighting.Size = new System.Drawing.Size(248, 54);
            this.cbPerPixelLighting.TabIndex = 1;
            this.cbPerPixelLighting.Text = "Per-pixel lighting shader";
            this.cbPerPixelLighting.UseVisualStyleBackColor = true;
            this.cbPerPixelLighting.CheckedChanged += new System.EventHandler(this.cbPerPixelLighting_CheckedChanged);
            // 
            // bMWLightSettings
            // 
            this.bMWLightSettings.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.bMWLightSettings.Location = new System.Drawing.Point(136, 153);
            this.bMWLightSettings.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bMWLightSettings.Name = "bMWLightSettings";
            this.bMWLightSettings.Size = new System.Drawing.Size(240, 38);
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
            this.gbDLDrawDist.Location = new System.Drawing.Point(4, 4);
            this.gbDLDrawDist.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLDrawDist.Name = "gbDLDrawDist";
            this.gbDLDrawDist.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLDrawDist.Size = new System.Drawing.Size(516, 93);
            this.gbDLDrawDist.TabIndex = 0;
            this.gbDLDrawDist.TabStop = false;
            this.gbDLDrawDist.Text = "&Draw Distance";
            // 
            // lDLDrawDist
            // 
            this.lDLDrawDist.AutoSize = true;
            this.lDLDrawDist.Location = new System.Drawing.Point(93, 36);
            this.lDLDrawDist.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLDrawDist.Name = "lDLDrawDist";
            this.lDLDrawDist.Size = new System.Drawing.Size(45, 25);
            this.lDLDrawDist.TabIndex = 0;
            this.lDLDrawDist.Text = "cells";
            this.lDLDrawDist.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // udDLDrawDist
            // 
            this.udDLDrawDist.DecimalPlaces = 1;
            this.udDLDrawDist.Location = new System.Drawing.Point(9, 33);
            this.udDLDrawDist.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
            this.udDLDrawDist.Size = new System.Drawing.Size(75, 31);
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
            this.gbDLWater.Location = new System.Drawing.Point(4, 105);
            this.gbDLWater.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLWater.Name = "gbDLWater";
            this.gbDLWater.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLWater.Size = new System.Drawing.Size(516, 355);
            this.gbDLWater.TabIndex = 9;
            this.gbDLWater.TabStop = false;
            this.gbDLWater.Text = "&Water";
            // 
            // cbDLDynRipples
            // 
            this.cbDLDynRipples.AutoSize = true;
            this.cbDLDynRipples.Location = new System.Drawing.Point(24, 170);
            this.cbDLDynRipples.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLDynRipples.Name = "cbDLDynRipples";
            this.cbDLDynRipples.Size = new System.Drawing.Size(165, 29);
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
            this.gbDLWtrCaust.Location = new System.Drawing.Point(9, 258);
            this.gbDLWtrCaust.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLWtrCaust.Name = "gbDLWtrCaust";
            this.gbDLWtrCaust.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLWtrCaust.Size = new System.Drawing.Size(498, 81);
            this.gbDLWtrCaust.TabIndex = 4;
            this.gbDLWtrCaust.TabStop = false;
            this.gbDLWtrCaust.Text = "&Caustics [underwater refracted lighting]";
            // 
            // lDLWtrCaust
            // 
            this.lDLWtrCaust.AutoSize = true;
            this.lDLWtrCaust.Location = new System.Drawing.Point(88, 36);
            this.lDLWtrCaust.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLWtrCaust.Name = "lDLWtrCaust";
            this.lDLWtrCaust.Size = new System.Drawing.Size(115, 25);
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
            this.udDLWtrCaust.Location = new System.Drawing.Point(16, 33);
            this.udDLWtrCaust.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.udDLWtrCaust.Name = "udDLWtrCaust";
            this.udDLWtrCaust.Size = new System.Drawing.Size(63, 31);
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
            this.gbDLWtrWave.Location = new System.Drawing.Point(9, 168);
            this.gbDLWtrWave.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLWtrWave.Name = "gbDLWtrWave";
            this.gbDLWtrWave.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLWtrWave.Size = new System.Drawing.Size(498, 84);
            this.gbDLWtrWave.TabIndex = 3;
            this.gbDLWtrWave.TabStop = false;
            // 
            // lDLWtrWave
            // 
            this.lDLWtrWave.AutoSize = true;
            this.lDLWtrWave.Location = new System.Drawing.Point(88, 39);
            this.lDLWtrWave.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLWtrWave.Name = "lDLWtrWave";
            this.lDLWtrWave.Size = new System.Drawing.Size(140, 25);
            this.lDLWtrWave.TabIndex = 1;
            this.lDLWtrWave.Text = "Height of wa&ves";
            this.lDLWtrWave.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // udDLWtrWave
            // 
            this.udDLWtrWave.Location = new System.Drawing.Point(16, 36);
            this.udDLWtrWave.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.udDLWtrWave.Maximum = new decimal(new int[] {
            250,
            0,
            0,
            0});
            this.udDLWtrWave.Name = "udDLWtrWave";
            this.udDLWtrWave.Size = new System.Drawing.Size(63, 31);
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
            this.gbDLWtrRefl.Location = new System.Drawing.Point(9, 26);
            this.gbDLWtrRefl.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLWtrRefl.Name = "gbDLWtrRefl";
            this.gbDLWtrRefl.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLWtrRefl.Size = new System.Drawing.Size(498, 138);
            this.gbDLWtrRefl.TabIndex = 0;
            this.gbDLWtrRefl.TabStop = false;
            this.gbDLWtrRefl.Text = "Reflections";
            // 
            // cbDLSkyRefl
            // 
            this.cbDLSkyRefl.AutoSize = true;
            this.cbDLSkyRefl.Location = new System.Drawing.Point(16, 28);
            this.cbDLSkyRefl.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLSkyRefl.Name = "cbDLSkyRefl";
            this.cbDLSkyRefl.Size = new System.Drawing.Size(66, 29);
            this.cbDLSkyRefl.TabIndex = 0;
            this.cbDLSkyRefl.Text = "S&ky";
            this.cbDLSkyRefl.UseVisualStyleBackColor = true;
            // 
            // cbDLReflLand
            // 
            this.cbDLReflLand.AutoSize = true;
            this.cbDLReflLand.Location = new System.Drawing.Point(16, 63);
            this.cbDLReflLand.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLReflLand.Name = "cbDLReflLand";
            this.cbDLReflLand.Size = new System.Drawing.Size(121, 29);
            this.cbDLReflLand.TabIndex = 2;
            this.cbDLReflLand.Text = "Landsca&pe";
            this.cbDLReflLand.UseVisualStyleBackColor = true;
            this.cbDLReflLand.CheckedChanged += new System.EventHandler(this.cbDLReflectiveWater_CheckedChanged);
            // 
            // cbDLReflBlur
            // 
            this.cbDLReflBlur.AutoSize = true;
            this.cbDLReflBlur.Location = new System.Drawing.Point(16, 98);
            this.cbDLReflBlur.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLReflBlur.Name = "cbDLReflBlur";
            this.cbDLReflBlur.Size = new System.Drawing.Size(154, 29);
            this.cbDLReflBlur.TabIndex = 4;
            this.cbDLReflBlur.Text = "&Blur reflections";
            this.cbDLReflBlur.UseVisualStyleBackColor = true;
            // 
            // cbDLReflNStatics
            // 
            this.cbDLReflNStatics.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbDLReflNStatics.AutoSize = true;
            this.cbDLReflNStatics.Location = new System.Drawing.Point(254, 28);
            this.cbDLReflNStatics.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLReflNStatics.Name = "cbDLReflNStatics";
            this.cbDLReflNStatics.Size = new System.Drawing.Size(150, 29);
            this.cbDLReflNStatics.TabIndex = 1;
            this.cbDLReflNStatics.Text = "&Nearby Statics";
            this.cbDLReflNStatics.UseVisualStyleBackColor = true;
            // 
            // cbDLReflInterior
            // 
            this.cbDLReflInterior.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.cbDLReflInterior.AutoSize = true;
            this.cbDLReflInterior.Enabled = false;
            this.cbDLReflInterior.Location = new System.Drawing.Point(254, 63);
            this.cbDLReflInterior.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLReflInterior.Name = "cbDLReflInterior";
            this.cbDLReflInterior.Size = new System.Drawing.Size(103, 29);
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
            this.tableLayoutDLRight.Location = new System.Drawing.Point(524, 0);
            this.tableLayoutDLRight.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutDLRight.Name = "tableLayoutDLRight";
            this.tableLayoutDLRight.RowCount = 4;
            this.tableLayoutDLRight.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutDLRight.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutDLRight.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutDLRight.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutDLRight.Size = new System.Drawing.Size(546, 672);
            this.tableLayoutDLRight.TabIndex = 1;
            // 
            // pDLAutoDist
            // 
            this.pDLAutoDist.Controls.Add(this.cbDLAutoDist);
            this.pDLAutoDist.Controls.Add(this.gbDLAutoDist);
            this.pDLAutoDist.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pDLAutoDist.Location = new System.Drawing.Point(4, 4);
            this.pDLAutoDist.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pDLAutoDist.Name = "pDLAutoDist";
            this.pDLAutoDist.Size = new System.Drawing.Size(538, 114);
            this.pDLAutoDist.TabIndex = 13;
            // 
            // cbDLAutoDist
            // 
            this.cbDLAutoDist.AutoSize = true;
            this.cbDLAutoDist.Location = new System.Drawing.Point(12, 0);
            this.cbDLAutoDist.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLAutoDist.Name = "cbDLAutoDist";
            this.cbDLAutoDist.Size = new System.Drawing.Size(230, 29);
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
            this.gbDLAutoDist.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLAutoDist.Name = "gbDLAutoDist";
            this.gbDLAutoDist.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLAutoDist.Size = new System.Drawing.Size(538, 114);
            this.gbDLAutoDist.TabIndex = 13;
            this.gbDLAutoDist.TabStop = false;
            // 
            // rbDLAutoByAFogEnd
            // 
            this.rbDLAutoByAFogEnd.AutoSize = true;
            this.rbDLAutoByAFogEnd.Location = new System.Drawing.Point(27, 72);
            this.rbDLAutoByAFogEnd.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbDLAutoByAFogEnd.Name = "rbDLAutoByAFogEnd";
            this.rbDLAutoByAFogEnd.Size = new System.Drawing.Size(235, 29);
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
            this.rbDLAutoByDrawDist.Location = new System.Drawing.Point(27, 36);
            this.rbDLAutoByDrawDist.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbDLAutoByDrawDist.Name = "rbDLAutoByDrawDist";
            this.rbDLAutoByDrawDist.Size = new System.Drawing.Size(174, 29);
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
            this.pDLStatics.Location = new System.Drawing.Point(4, 126);
            this.pDLStatics.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pDLStatics.Name = "pDLStatics";
            this.pDLStatics.Size = new System.Drawing.Size(538, 177);
            this.pDLStatics.TabIndex = 5;
            this.pDLStatics.TabStop = true;
            // 
            // cbDLDistantStatics
            // 
            this.cbDLDistantStatics.AutoSize = true;
            this.cbDLDistantStatics.Location = new System.Drawing.Point(12, 0);
            this.cbDLDistantStatics.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLDistantStatics.Name = "cbDLDistantStatics";
            this.cbDLDistantStatics.Size = new System.Drawing.Size(183, 29);
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
            this.gbDLStatics.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLStatics.Name = "gbDLStatics";
            this.gbDLStatics.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLStatics.Size = new System.Drawing.Size(538, 177);
            this.gbDLStatics.TabIndex = 1;
            this.gbDLStatics.TabStop = false;
            // 
            // tableAlignDLStatics
            // 
            this.tableAlignDLStatics.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableAlignDLStatics.ColumnCount = 4;
            this.tableAlignDLStatics.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableAlignDLStatics.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 75F));
            this.tableAlignDLStatics.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 15F));
            this.tableAlignDLStatics.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 75F));
            this.tableAlignDLStatics.Controls.Add(this.lDLNear, 0, 0);
            this.tableAlignDLStatics.Controls.Add(this.udDLDistNear, 3, 0);
            this.tableAlignDLStatics.Controls.Add(this.udDLDistVeryFar, 3, 4);
            this.tableAlignDLStatics.Controls.Add(this.tbDLNearSize, 1, 0);
            this.tableAlignDLStatics.Controls.Add(this.lDLFar, 0, 2);
            this.tableAlignDLStatics.Controls.Add(this.lDLVeryFar, 0, 4);
            this.tableAlignDLStatics.Controls.Add(this.udDLSizeVeryFar, 1, 4);
            this.tableAlignDLStatics.Controls.Add(this.udDLSizeFar, 1, 2);
            this.tableAlignDLStatics.Controls.Add(this.udDLDistFar, 3, 2);
            this.tableAlignDLStatics.Location = new System.Drawing.Point(12, 52);
            this.tableAlignDLStatics.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tableAlignDLStatics.Name = "tableAlignDLStatics";
            this.tableAlignDLStatics.RowCount = 5;
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 3F));
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 3F));
            this.tableAlignDLStatics.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.tableAlignDLStatics.Size = new System.Drawing.Size(504, 110);
            this.tableAlignDLStatics.TabIndex = 6;
            // 
            // lDLNear
            // 
            this.lDLNear.AutoSize = true;
            this.lDLNear.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLNear.Location = new System.Drawing.Point(286, 0);
            this.lDLNear.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLNear.Name = "lDLNear";
            this.lDLNear.Size = new System.Drawing.Size(49, 34);
            this.lDLNear.TabIndex = 0;
            this.lDLNear.Text = "Near";
            this.lDLNear.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // udDLDistNear
            // 
            this.udDLDistNear.DecimalPlaces = 1;
            this.udDLDistNear.Dock = System.Windows.Forms.DockStyle.Fill;
            this.udDLDistNear.Location = new System.Drawing.Point(429, 0);
            this.udDLDistNear.Margin = new System.Windows.Forms.Padding(0);
            this.udDLDistNear.Maximum = new decimal(new int[] {
            2998,
            0,
            0,
            65536});
            this.udDLDistNear.Name = "udDLDistNear";
            this.udDLDistNear.Size = new System.Drawing.Size(75, 31);
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
            this.udDLDistVeryFar.Location = new System.Drawing.Point(429, 74);
            this.udDLDistVeryFar.Margin = new System.Windows.Forms.Padding(0);
            this.udDLDistVeryFar.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.udDLDistVeryFar.Name = "udDLDistVeryFar";
            this.udDLDistVeryFar.Size = new System.Drawing.Size(75, 31);
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
            this.tbDLNearSize.Location = new System.Drawing.Point(339, 0);
            this.tbDLNearSize.Margin = new System.Windows.Forms.Padding(0);
            this.tbDLNearSize.MaxLength = 3;
            this.tbDLNearSize.Name = "tbDLNearSize";
            this.tbDLNearSize.ReadOnly = true;
            this.tbDLNearSize.Size = new System.Drawing.Size(75, 31);
            this.tbDLNearSize.TabIndex = 0;
            this.tbDLNearSize.Text = "400";
            this.tbDLNearSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // lDLFar
            // 
            this.lDLFar.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLFar.Location = new System.Drawing.Point(103, 37);
            this.lDLFar.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLFar.Name = "lDLFar";
            this.lDLFar.Size = new System.Drawing.Size(232, 34);
            this.lDLFar.TabIndex = 0;
            this.lDLFar.Text = "Far";
            this.lDLFar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lDLVeryFar
            // 
            this.lDLVeryFar.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLVeryFar.Location = new System.Drawing.Point(103, 74);
            this.lDLVeryFar.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLVeryFar.Name = "lDLVeryFar";
            this.lDLVeryFar.Size = new System.Drawing.Size(232, 36);
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
            this.udDLSizeVeryFar.Location = new System.Drawing.Point(339, 74);
            this.udDLSizeVeryFar.Margin = new System.Windows.Forms.Padding(0);
            this.udDLSizeVeryFar.Maximum = new decimal(new int[] {
            9999,
            0,
            0,
            0});
            this.udDLSizeVeryFar.Name = "udDLSizeVeryFar";
            this.udDLSizeVeryFar.Size = new System.Drawing.Size(75, 31);
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
            this.udDLSizeFar.Location = new System.Drawing.Point(339, 37);
            this.udDLSizeFar.Margin = new System.Windows.Forms.Padding(0);
            this.udDLSizeFar.Maximum = new decimal(new int[] {
            9999,
            0,
            0,
            0});
            this.udDLSizeFar.Name = "udDLSizeFar";
            this.udDLSizeFar.Size = new System.Drawing.Size(75, 31);
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
            this.udDLDistFar.Location = new System.Drawing.Point(429, 37);
            this.udDLDistFar.Margin = new System.Windows.Forms.Padding(0);
            this.udDLDistFar.Maximum = new decimal(new int[] {
            2999,
            0,
            0,
            65536});
            this.udDLDistFar.Name = "udDLDistFar";
            this.udDLDistFar.Size = new System.Drawing.Size(75, 31);
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
            this.lDLMinSize.Location = new System.Drawing.Point(347, 27);
            this.lDLMinSize.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLMinSize.Name = "lDLMinSize";
            this.lDLMinSize.Size = new System.Drawing.Size(78, 25);
            this.lDLMinSize.TabIndex = 0;
            this.lDLMinSize.Text = "Min Size";
            // 
            // lDLEndDist
            // 
            this.lDLEndDist.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lDLEndDist.AutoSize = true;
            this.lDLEndDist.Location = new System.Drawing.Point(437, 27);
            this.lDLEndDist.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLEndDist.Name = "lDLEndDist";
            this.lDLEndDist.Size = new System.Drawing.Size(78, 25);
            this.lDLEndDist.TabIndex = 0;
            this.lDLEndDist.Text = "End Dist";
            // 
            // bDLWthr
            // 
            this.bDLWthr.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.bDLWthr.Location = new System.Drawing.Point(153, 630);
            this.bDLWthr.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bDLWthr.Name = "bDLWthr";
            this.bDLWthr.Size = new System.Drawing.Size(240, 38);
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
            this.gbDLFog.Location = new System.Drawing.Point(4, 311);
            this.gbDLFog.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLFog.Name = "gbDLFog";
            this.gbDLFog.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbDLFog.Size = new System.Drawing.Size(538, 311);
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
            this.tableAlignDLFog.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 75F));
            this.tableAlignDLFog.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 15F));
            this.tableAlignDLFog.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 75F));
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
            this.tableAlignDLFog.Location = new System.Drawing.Point(12, 45);
            this.tableAlignDLFog.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tableAlignDLFog.Name = "tableAlignDLFog";
            this.tableAlignDLFog.RowCount = 7;
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 3F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 3F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 6F));
            this.tableAlignDLFog.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.tableAlignDLFog.Size = new System.Drawing.Size(504, 114);
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
            this.udDLFogAStart.Location = new System.Drawing.Point(339, 0);
            this.udDLFogAStart.Margin = new System.Windows.Forms.Padding(0);
            this.udDLFogAStart.Maximum = new decimal(new int[] {
            2999,
            0,
            0,
            65536});
            this.udDLFogAStart.Name = "udDLFogAStart";
            this.udDLFogAStart.Size = new System.Drawing.Size(75, 31);
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
            this.udDLFogAEnd.Location = new System.Drawing.Point(429, 0);
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
            this.udDLFogAEnd.Size = new System.Drawing.Size(75, 31);
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
            this.udDLFogExpMul.Location = new System.Drawing.Point(429, 114);
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
            this.udDLFogExpMul.Size = new System.Drawing.Size(75, 31);
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
            this.lDLFogExpMul.Location = new System.Drawing.Point(173, 114);
            this.lDLFogExpMul.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLFogExpMul.Name = "lDLFogExpMul";
            this.lDLFogExpMul.Size = new System.Drawing.Size(252, 34);
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
            this.udDLFogBStart.Location = new System.Drawing.Point(339, 37);
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
            this.udDLFogBStart.Size = new System.Drawing.Size(75, 31);
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
            this.udDLFogBEnd.Location = new System.Drawing.Point(429, 37);
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
            this.udDLFogBEnd.Size = new System.Drawing.Size(75, 31);
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
            this.lDLFogI.Location = new System.Drawing.Point(161, 74);
            this.lDLFogI.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLFogI.Name = "lDLFogI";
            this.lDLFogI.Size = new System.Drawing.Size(174, 34);
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
            this.udDLFogIStart.Location = new System.Drawing.Point(339, 74);
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
            this.udDLFogIStart.Size = new System.Drawing.Size(75, 31);
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
            this.udDLFogIEnd.Location = new System.Drawing.Point(429, 74);
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
            this.udDLFogIEnd.Size = new System.Drawing.Size(75, 31);
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
            this.lDLFogB.Location = new System.Drawing.Point(189, 37);
            this.lDLFogB.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLFogB.Name = "lDLFogB";
            this.lDLFogB.Size = new System.Drawing.Size(146, 34);
            this.lDLFogB.TabIndex = 0;
            this.lDLFogB.Text = "Below Water Fog";
            this.lDLFogB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lDLFogA
            // 
            this.lDLFogA.AutoSize = true;
            this.lDLFogA.Dock = System.Windows.Forms.DockStyle.Right;
            this.lDLFogA.Location = new System.Drawing.Point(184, 0);
            this.lDLFogA.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLFogA.Name = "lDLFogA";
            this.lDLFogA.Size = new System.Drawing.Size(151, 34);
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
            this.cbDLScattering.Location = new System.Drawing.Point(114, 214);
            this.cbDLScattering.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLScattering.Name = "cbDLScattering";
            this.cbDLScattering.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.cbDLScattering.Size = new System.Drawing.Size(403, 29);
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
            this.cbDLFogExp.Location = new System.Drawing.Point(213, 177);
            this.cbDLFogExp.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbDLFogExp.Name = "cbDLFogExp";
            this.cbDLFogExp.Size = new System.Drawing.Size(304, 29);
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
            this.lDLFogStart.Location = new System.Drawing.Point(347, 20);
            this.lDLFogStart.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lDLFogStart.Name = "lDLFogStart";
            this.lDLFogStart.Size = new System.Drawing.Size(48, 25);
            this.lDLFogStart.TabIndex = 0;
            this.lDLFogStart.Text = "Start";
            // 
            // lDLFogEnd
            // 
            this.lDLFogEnd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lDLFogEnd.AutoSize = true;
            this.lDLFogEnd.Location = new System.Drawing.Point(437, 20);
            this.lDLFogEnd.Margin = new System.Windows.Forms.Padding(0);
            this.lDLFogEnd.Name = "lDLFogEnd";
            this.lDLFogEnd.Size = new System.Drawing.Size(42, 25);
            this.lDLFogEnd.TabIndex = 0;
            this.lDLFogEnd.Text = "End";
            // 
            // tpConfig
            // 
            this.tpConfig.Controls.Add(this.gbErrorReporting);
            this.tpConfig.Controls.Add(this.gbMainUI);
            this.tpConfig.Controls.Add(this.gbMainInfo);
            this.tpConfig.Controls.Add(this.gbMainSettings);
            this.tpConfig.Location = new System.Drawing.Point(4, 34);
            this.tpConfig.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tpConfig.Name = "tpConfig";
            this.tpConfig.Size = new System.Drawing.Size(1078, 714);
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
            this.gbErrorReporting.Location = new System.Drawing.Point(12, 484);
            this.gbErrorReporting.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbErrorReporting.Name = "gbErrorReporting";
            this.gbErrorReporting.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbErrorReporting.Size = new System.Drawing.Size(1050, 90);
            this.gbErrorReporting.TabIndex = 3;
            this.gbErrorReporting.TabStop = false;
            this.gbErrorReporting.Text = "Error reporting";
            // 
            // bReportingShowDLWizardLog
            // 
            this.bReportingShowDLWizardLog.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.bReportingShowDLWizardLog.Location = new System.Drawing.Point(405, 33);
            this.bReportingShowDLWizardLog.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bReportingShowDLWizardLog.Name = "bReportingShowDLWizardLog";
            this.bReportingShowDLWizardLog.Size = new System.Drawing.Size(240, 38);
            this.bReportingShowDLWizardLog.TabIndex = 1;
            this.bReportingShowDLWizardLog.Text = "Open DL generator log";
            this.bReportingShowDLWizardLog.UseVisualStyleBackColor = true;
            this.bReportingShowDLWizardLog.Click += new System.EventHandler(this.bReportingShowDLWizardLog_Click);
            // 
            // bReportingShowLog
            // 
            this.bReportingShowLog.Location = new System.Drawing.Point(9, 33);
            this.bReportingShowLog.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bReportingShowLog.Name = "bReportingShowLog";
            this.bReportingShowLog.Size = new System.Drawing.Size(234, 38);
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
            this.gbMainUI.Location = new System.Drawing.Point(12, 104);
            this.gbMainUI.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMainUI.Name = "gbMainUI";
            this.gbMainUI.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMainUI.Size = new System.Drawing.Size(1050, 120);
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
            this.pLanguage.Location = new System.Drawing.Point(12, 38);
            this.pLanguage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pLanguage.Name = "pLanguage";
            this.pLanguage.Size = new System.Drawing.Size(360, 63);
            this.pLanguage.TabIndex = 0;
            // 
            // cmbUILanguage
            // 
            this.cmbUILanguage.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.cmbUILanguage.FormattingEnabled = true;
            this.cmbUILanguage.Location = new System.Drawing.Point(0, 30);
            this.cmbUILanguage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbUILanguage.Name = "cmbUILanguage";
            this.cmbUILanguage.Size = new System.Drawing.Size(360, 33);
            this.cmbUILanguage.TabIndex = 1;
            this.cmbUILanguage.SelectedIndexChanged += new System.EventHandler(this.cmbUILanguage_SelectedIndexChanged);
            this.cmbUILanguage.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
            // 
            // cbUILangAuto
            // 
            this.cbUILangAuto.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cbUILangAuto.AutoSize = true;
            this.cbUILangAuto.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cbUILangAuto.Location = new System.Drawing.Point(234, -2);
            this.cbUILangAuto.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbUILangAuto.Name = "cbUILangAuto";
            this.cbUILangAuto.Size = new System.Drawing.Size(126, 29);
            this.cbUILangAuto.TabIndex = 0;
            this.cbUILangAuto.Text = "Autodetect";
            this.cbUILangAuto.UseVisualStyleBackColor = true;
            this.cbUILangAuto.CheckedChanged += new System.EventHandler(this.cbUILangAuto_CheckedChanged);
            // 
            // lUILanguage
            // 
            this.lUILanguage.AutoSize = true;
            this.lUILanguage.Location = new System.Drawing.Point(-3, 0);
            this.lUILanguage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lUILanguage.Name = "lUILanguage";
            this.lUILanguage.Size = new System.Drawing.Size(89, 25);
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
            this.cmbTipReadSpd.Location = new System.Drawing.Point(612, 66);
            this.cmbTipReadSpd.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cmbTipReadSpd.Name = "cmbTipReadSpd";
            this.cmbTipReadSpd.Size = new System.Drawing.Size(70, 33);
            this.cmbTipReadSpd.TabIndex = 2;
            this.cmbTipReadSpd.Text = "15";
            this.cmbTipReadSpd.SelectedIndexChanged += new System.EventHandler(this.cmbMainTipReadSpd_SelectedIndexChanged);
            this.cmbTipReadSpd.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
            // 
            // lTipReadSpd
            // 
            this.lTipReadSpd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lTipReadSpd.AutoSize = true;
            this.lTipReadSpd.Location = new System.Drawing.Point(612, 39);
            this.lTipReadSpd.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lTipReadSpd.Name = "lTipReadSpd";
            this.lTipReadSpd.Size = new System.Drawing.Size(184, 25);
            this.lTipReadSpd.TabIndex = 0;
            this.lTipReadSpd.Text = "Tooltip reading speed";
            // 
            // lTipRSpdUnit
            // 
            this.lTipRSpdUnit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lTipRSpdUnit.AutoSize = true;
            this.lTipRSpdUnit.Location = new System.Drawing.Point(693, 70);
            this.lTipRSpdUnit.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lTipRSpdUnit.Name = "lTipRSpdUnit";
            this.lTipRSpdUnit.Size = new System.Drawing.Size(89, 25);
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
            this.gbMainInfo.Location = new System.Drawing.Point(12, 4);
            this.gbMainInfo.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMainInfo.Name = "gbMainInfo";
            this.gbMainInfo.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMainInfo.Size = new System.Drawing.Size(1050, 90);
            this.gbMainInfo.TabIndex = 0;
            this.gbMainInfo.TabStop = false;
            this.gbMainInfo.Text = "Information";
            // 
            // bViewCaps
            // 
            this.bViewCaps.Location = new System.Drawing.Point(9, 33);
            this.bViewCaps.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bViewCaps.Name = "bViewCaps";
            this.bViewCaps.Size = new System.Drawing.Size(240, 38);
            this.bViewCaps.TabIndex = 0;
            this.bViewCaps.Text = "Report max AA and AF";
            this.bViewCaps.Click += new System.EventHandler(this.bViewCaps_Click);
            // 
            // bHelp
            // 
            this.bHelp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bHelp.Location = new System.Drawing.Point(801, 33);
            this.bHelp.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bHelp.Name = "bHelp";
            this.bHelp.Size = new System.Drawing.Size(240, 38);
            this.bHelp.TabIndex = 1;
            this.bHelp.Text = "Help";
            this.bHelp.Click += new System.EventHandler(this.bHelp_Click);
            // 
            // bAbout
            // 
            this.bAbout.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.bAbout.Location = new System.Drawing.Point(405, 33);
            this.bAbout.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bAbout.Name = "bAbout";
            this.bAbout.Size = new System.Drawing.Size(240, 38);
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
            this.gbMainSettings.Location = new System.Drawing.Point(12, 584);
            this.gbMainSettings.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMainSettings.Name = "gbMainSettings";
            this.gbMainSettings.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.gbMainSettings.Size = new System.Drawing.Size(1050, 114);
            this.gbMainSettings.TabIndex = 1;
            this.gbMainSettings.TabStop = false;
            this.gbMainSettings.Text = "Settings";
            // 
            // bResetSettings
            // 
            this.bResetSettings.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bResetSettings.Location = new System.Drawing.Point(9, 60);
            this.bResetSettings.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bResetSettings.Name = "bResetSettings";
            this.bResetSettings.Size = new System.Drawing.Size(240, 38);
            this.bResetSettings.TabIndex = 1;
            this.bResetSettings.Text = "Reset settings";
            this.bResetSettings.Click += new System.EventHandler(this.bResetSettings_Click);
            // 
            // bImport
            // 
            this.bImport.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.bImport.Location = new System.Drawing.Point(405, 60);
            this.bImport.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bImport.Name = "bImport";
            this.bImport.Size = new System.Drawing.Size(240, 38);
            this.bImport.TabIndex = 3;
            this.bImport.Text = "Import settings";
            this.bImport.Click += new System.EventHandler(this.bImport_Click);
            // 
            // bExport
            // 
            this.bExport.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bExport.Location = new System.Drawing.Point(801, 60);
            this.bExport.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.bExport.Name = "bExport";
            this.bExport.Size = new System.Drawing.Size(240, 38);
            this.bExport.TabIndex = 4;
            this.bExport.Text = "Export settings";
            this.bExport.Click += new System.EventHandler(this.bExport_Click);
            // 
            // cbClearINI
            // 
            this.cbClearINI.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cbClearINI.AutoSize = true;
            this.cbClearINI.Location = new System.Drawing.Point(12, 27);
            this.cbClearINI.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cbClearINI.Name = "cbClearINI";
            this.cbClearINI.Size = new System.Drawing.Size(195, 29);
            this.cbClearINI.TabIndex = 0;
            this.cbClearINI.Text = "Clear saved settings";
            this.cbClearINI.UseVisualStyleBackColor = true;
            // 
            // tpInstructions
            // 
            this.tpInstructions.Controls.Add(this.lInstructions);
            this.tpInstructions.Location = new System.Drawing.Point(4, 34);
            this.tpInstructions.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tpInstructions.Name = "tpInstructions";
            this.tpInstructions.Size = new System.Drawing.Size(1078, 714);
            this.tpInstructions.TabIndex = 8;
            this.tpInstructions.Text = "Instructions";
            this.tpInstructions.ToolTipText = "A guide to setting up MGE XE.";
            this.tpInstructions.UseVisualStyleBackColor = true;
            // 
            // lInstructions
            // 
            this.lInstructions.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lInstructions.Location = new System.Drawing.Point(0, 0);
            this.lInstructions.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lInstructions.Name = "lInstructions";
            this.lInstructions.Padding = new System.Windows.Forms.Padding(18, 18, 18, 18);
            this.lInstructions.Size = new System.Drawing.Size(1078, 714);
            this.lInstructions.TabIndex = 0;
            this.lInstructions.Text = resources.GetString("lInstructions.Text");
            // 
            // SShotFolderDialog
            // 
            this.SShotFolderDialog.Description = "Select output folder for screenshots taken in game:";
            // 
            // cbUseSharedMemory
            // 
            this.cbUseSharedMemory.AutoSize = true;
            this.cbUseSharedMemory.Location = new System.Drawing.Point(19, 166);
            this.cbUseSharedMemory.Name = "cbUseSharedMemory";
            this.cbUseSharedMemory.Size = new System.Drawing.Size(197, 29);
            this.cbUseSharedMemory.TabIndex = 25;
            this.cbUseSharedMemory.Text = "Use shared memory";
            this.cbUseSharedMemory.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(144F, 144F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(1086, 752);
            this.Controls.Add(this.tabControl);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(1099, 782);
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
        private CheckBox cbUseSharedMemory;
    }
}