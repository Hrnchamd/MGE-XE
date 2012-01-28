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
        	System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
        	this.DudMenu = new System.Windows.Forms.ContextMenu();
        	this.OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
        	this.SaveFileDialog = new System.Windows.Forms.SaveFileDialog();
        	this.toolTip = new System.Windows.Forms.ToolTip(this.components);
        	this.cbDLSkyRefl = new System.Windows.Forms.CheckBox();
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
        	this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
        	this.lSShotDir = new System.Windows.Forms.Label();
        	this.lSShotName = new System.Windows.Forms.Label();
        	this.tbSShotName = new System.Windows.Forms.TextBox();
        	this.tbSShotDir = new System.Windows.Forms.TextBox();
        	this.udSShotNum = new System.Windows.Forms.NumericUpDown();
        	this.bSShotDirClear = new System.Windows.Forms.Button();
        	this.bSShotDirBrowse = new System.Windows.Forms.Button();
        	this.lSShotNum = new System.Windows.Forms.Label();
        	this.gbScene = new System.Windows.Forms.GroupBox();
        	this.lHDR2 = new System.Windows.Forms.Label();
        	this.bAutoFOV = new System.Windows.Forms.Button();
        	this.lFPSLimit = new System.Windows.Forms.Label();
        	this.udFPSLimit = new System.Windows.Forms.NumericUpDown();
        	this.udHDR = new System.Windows.Forms.NumericUpDown();
        	this.bShaderEd = new System.Windows.Forms.Button();
        	this.lHDR = new System.Windows.Forms.Label();
        	this.cmbFogMode = new System.Windows.Forms.ComboBox();
        	this.lFogMode = new System.Windows.Forms.Label();
        	this.lLOD = new System.Windows.Forms.Label();
        	this.udLOD = new System.Windows.Forms.NumericUpDown();
        	this.cbHWShader = new System.Windows.Forms.CheckBox();
        	this.cbFPSCounter = new System.Windows.Forms.CheckBox();
        	this.udFOV = new System.Windows.Forms.NumericUpDown();
        	this.lFOV = new System.Windows.Forms.Label();
        	this.gbDisplay = new System.Windows.Forms.GroupBox();
        	this.tableLayoutDisplay = new System.Windows.Forms.TableLayoutPanel();
        	this.cmbAntiAlias = new System.Windows.Forms.ComboBox();
        	this.lAntiAlias = new System.Windows.Forms.Label();
        	this.cmbVWait = new System.Windows.Forms.ComboBox();
        	this.cmbAnisoLevel = new System.Windows.Forms.ComboBox();
        	this.lAnisoLevel = new System.Windows.Forms.Label();
        	this.lVWait = new System.Windows.Forms.Label();
        	this.tbAspect = new System.Windows.Forms.TextBox();
        	this.bCalcResolution = new System.Windows.Forms.Button();
        	this.cbWindowed = new System.Windows.Forms.CheckBox();
        	this.cmbRefreshRate = new System.Windows.Forms.ComboBox();
        	this.bCalcRefresh = new System.Windows.Forms.Button();
        	this.tbResolution = new System.Windows.Forms.TextBox();
        	this.lResolution = new System.Windows.Forms.Label();
        	this.lAspect = new System.Windows.Forms.Label();
        	this.lRefreshRate = new System.Windows.Forms.Label();
        	this.tabControl = new System.Windows.Forms.TabControl();
        	this.tpDL = new System.Windows.Forms.TabPage();
        	this.bDistantLandWizard = new System.Windows.Forms.Button();
        	this.cbDLDistantLand = new System.Windows.Forms.CheckBox();
        	this.gbDistantLand = new System.Windows.Forms.GroupBox();
        	this.bMWLightSettings = new System.Windows.Forms.Button();
        	this.pDLStatics = new System.Windows.Forms.Panel();
        	this.cbDLDistantStatics = new System.Windows.Forms.CheckBox();
        	this.gbDLStatics = new System.Windows.Forms.GroupBox();
        	this.udDLDistVeryFar = new System.Windows.Forms.NumericUpDown();
        	this.udDLDistFar = new System.Windows.Forms.NumericUpDown();
        	this.udDLDistNear = new System.Windows.Forms.NumericUpDown();
        	this.udDLSizeVeryFar = new System.Windows.Forms.NumericUpDown();
        	this.udDLSizeFar = new System.Windows.Forms.NumericUpDown();
        	this.tbDLNearSize = new System.Windows.Forms.TextBox();
        	this.lDLVeryFar = new System.Windows.Forms.Label();
        	this.lDLFar = new System.Windows.Forms.Label();
        	this.lDLNear = new System.Windows.Forms.Label();
        	this.lDLMinSize = new System.Windows.Forms.Label();
        	this.lDLEndDist = new System.Windows.Forms.Label();
        	this.cbDLAutoDist = new System.Windows.Forms.CheckBox();
        	this.gbDLAutoDist = new System.Windows.Forms.GroupBox();
        	this.rbDLAutoByAFogEnd = new System.Windows.Forms.RadioButton();
        	this.rbDLAutoByDrawDist = new System.Windows.Forms.RadioButton();
        	this.gbDLWater = new System.Windows.Forms.GroupBox();
        	this.cbDLDynRipples = new System.Windows.Forms.CheckBox();
        	this.gbDLWtrCaust = new System.Windows.Forms.GroupBox();
        	this.lDLWtrCaust = new System.Windows.Forms.Label();
        	this.udDLWtrCaust = new System.Windows.Forms.NumericUpDown();
        	this.gbDLWtrWave = new System.Windows.Forms.GroupBox();
        	this.lDLWtrWave = new System.Windows.Forms.Label();
        	this.udDLWtrWave = new System.Windows.Forms.NumericUpDown();
        	this.gbDLWtrRefl = new System.Windows.Forms.GroupBox();
        	this.cbDLReflLand = new System.Windows.Forms.CheckBox();
        	this.cbDLReflBlur = new System.Windows.Forms.CheckBox();
        	this.cbDLReflNStatics = new System.Windows.Forms.CheckBox();
        	this.cbDLReflInterior = new System.Windows.Forms.CheckBox();
        	this.bDLWthr = new System.Windows.Forms.Button();
        	this.gbDLDrawDist = new System.Windows.Forms.GroupBox();
        	this.lDLDrawDist = new System.Windows.Forms.Label();
        	this.udDLDrawDist = new System.Windows.Forms.NumericUpDown();
        	this.gbDLFog = new System.Windows.Forms.GroupBox();
        	this.cbDLScattering = new System.Windows.Forms.CheckBox();
        	this.lDLFogExpMul = new System.Windows.Forms.Label();
        	this.udDLFogExpMul = new System.Windows.Forms.NumericUpDown();
        	this.lDLFogI = new System.Windows.Forms.Label();
        	this.udDLFogIEnd = new System.Windows.Forms.NumericUpDown();
        	this.udDLFogIStart = new System.Windows.Forms.NumericUpDown();
        	this.udDLFogBEnd = new System.Windows.Forms.NumericUpDown();
        	this.cbDLFogExp = new System.Windows.Forms.CheckBox();
        	this.udDLFogBStart = new System.Windows.Forms.NumericUpDown();
        	this.udDLFogAEnd = new System.Windows.Forms.NumericUpDown();
        	this.udDLFogAStart = new System.Windows.Forms.NumericUpDown();
        	this.lDLFogB = new System.Windows.Forms.Label();
        	this.lDLFogA = new System.Windows.Forms.Label();
        	this.lDLFogStart = new System.Windows.Forms.Label();
        	this.lDLFogEnd = new System.Windows.Forms.Label();
        	this.tpConfig = new System.Windows.Forms.TabPage();
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
        	this.tableLayoutPanel1.SuspendLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udSShotNum)).BeginInit();
        	this.gbScene.SuspendLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udFPSLimit)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udHDR)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udLOD)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udFOV)).BeginInit();
        	this.gbDisplay.SuspendLayout();
        	this.tableLayoutDisplay.SuspendLayout();
        	this.tabControl.SuspendLayout();
        	this.tpDL.SuspendLayout();
        	this.gbDistantLand.SuspendLayout();
        	this.pDLStatics.SuspendLayout();
        	this.gbDLStatics.SuspendLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udDLDistVeryFar)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLDistFar)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLDistNear)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLSizeVeryFar)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLSizeFar)).BeginInit();
        	this.gbDLAutoDist.SuspendLayout();
        	this.gbDLWater.SuspendLayout();
        	this.gbDLWtrCaust.SuspendLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udDLWtrCaust)).BeginInit();
        	this.gbDLWtrWave.SuspendLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udDLWtrWave)).BeginInit();
        	this.gbDLWtrRefl.SuspendLayout();
        	this.gbDLDrawDist.SuspendLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udDLDrawDist)).BeginInit();
        	this.gbDLFog.SuspendLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogExpMul)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogIEnd)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogIStart)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogBEnd)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogBStart)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogAEnd)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogAStart)).BeginInit();
        	this.tpConfig.SuspendLayout();
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
        	// cbDLSkyRefl
        	// 
        	this.cbDLSkyRefl.AutoSize = true;
        	this.cbDLSkyRefl.Location = new System.Drawing.Point(11, 19);
        	this.cbDLSkyRefl.Name = "cbDLSkyRefl";
        	this.cbDLSkyRefl.Size = new System.Drawing.Size(44, 17);
        	this.cbDLSkyRefl.TabIndex = 0;
        	this.cbDLSkyRefl.Text = "S&ky";
        	this.cbDLSkyRefl.UseVisualStyleBackColor = true;
        	// 
        	// tpInput
        	// 
        	this.tpInput.Controls.Add(this.gbMWLighting);
        	this.tpInput.Controls.Add(this.gbMWGeneral);
        	this.tpInput.Controls.Add(this.gbMsgs);
        	this.tpInput.Controls.Add(this.pCam3rdPrsn);
        	this.tpInput.Controls.Add(this.gbInputTools);
        	this.tpInput.Controls.Add(this.gbInputOpts);
        	this.tpInput.Location = new System.Drawing.Point(4, 21);
        	this.tpInput.Name = "tpInput";
        	this.tpInput.Size = new System.Drawing.Size(578, 420);
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
        	this.gbMWLighting.Location = new System.Drawing.Point(304, 129);
        	this.gbMWLighting.Name = "gbMWLighting";
        	this.gbMWLighting.Size = new System.Drawing.Size(266, 72);
        	this.gbMWLighting.TabIndex = 10;
        	this.gbMWLighting.TabStop = false;
        	this.gbMWLighting.Text = "Dynamic lighting coefficients";
        	// 
        	// bMWLightingReset
        	// 
        	this.bMWLightingReset.Location = new System.Drawing.Point(203, 0);
        	this.bMWLightingReset.Name = "bMWLightingReset";
        	this.bMWLightingReset.Size = new System.Drawing.Size(56, 20);
        	this.bMWLightingReset.TabIndex = 6;
        	this.bMWLightingReset.Text = "Reset";
        	this.bMWLightingReset.UseVisualStyleBackColor = true;
        	this.bMWLightingReset.Click += new System.EventHandler(this.bMWLightingReset_click);
        	// 
        	// lLightingConst
        	// 
        	this.lLightingConst.AutoSize = true;
        	this.lLightingConst.Location = new System.Drawing.Point(182, 21);
        	this.lLightingConst.Name = "lLightingConst";
        	this.lLightingConst.Size = new System.Drawing.Size(49, 13);
        	this.lLightingConst.TabIndex = 5;
        	this.lLightingConst.Text = "Constant";
        	// 
        	// lLightingLin
        	// 
        	this.lLightingLin.AutoSize = true;
        	this.lLightingLin.Location = new System.Drawing.Point(97, 21);
        	this.lLightingLin.Name = "lLightingLin";
        	this.lLightingLin.Size = new System.Drawing.Size(36, 13);
        	this.lLightingLin.TabIndex = 4;
        	this.lLightingLin.Text = "Linear";
        	// 
        	// lLightingQuad
        	// 
        	this.lLightingQuad.AutoSize = true;
        	this.lLightingQuad.Location = new System.Drawing.Point(12, 21);
        	this.lLightingQuad.Name = "lLightingQuad";
        	this.lLightingQuad.Size = new System.Drawing.Size(53, 13);
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
        	this.udLightingConst.Name = "udLightingConst";
        	this.udLightingConst.Size = new System.Drawing.Size(64, 20);
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
        	this.udLightingLinear.Name = "udLightingLinear";
        	this.udLightingLinear.Size = new System.Drawing.Size(64, 20);
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
        	this.udLightingQuad.Name = "udLightingQuad";
        	this.udLightingQuad.Size = new System.Drawing.Size(64, 20);
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
        	this.gbMWGeneral.Size = new System.Drawing.Size(562, 139);
        	this.gbMWGeneral.TabIndex = 9;
        	this.gbMWGeneral.TabStop = false;
        	this.gbMWGeneral.Text = "Morrowind.ini settings";
        	// 
        	// lScreenshotStatus
        	// 
        	this.lScreenshotStatus.AutoSize = true;
        	this.lScreenshotStatus.Location = new System.Drawing.Point(13, 115);
        	this.lScreenshotStatus.Name = "lScreenshotStatus";
        	this.lScreenshotStatus.Size = new System.Drawing.Size(456, 13);
        	this.lScreenshotStatus.TabIndex = 9;
        	this.lScreenshotStatus.Text = "Screenshots can be taken with the PrintScreen key. MGE will compress and save the" +
        	"m for you.";
        	// 
        	// cbScreenshots
        	// 
        	this.cbScreenshots.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cbScreenshots.AutoSize = true;
        	this.cbScreenshots.Location = new System.Drawing.Point(281, 21);
        	this.cbScreenshots.Name = "cbScreenshots";
        	this.cbScreenshots.Size = new System.Drawing.Size(111, 17);
        	this.cbScreenshots.TabIndex = 0;
        	this.cbScreenshots.Text = "Allow screenshots";
        	// 
        	// cbHitFader
        	// 
        	this.cbHitFader.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cbHitFader.AutoSize = true;
        	this.cbHitFader.Checked = true;
        	this.cbHitFader.CheckState = System.Windows.Forms.CheckState.Checked;
        	this.cbHitFader.Location = new System.Drawing.Point(281, 90);
        	this.cbHitFader.Name = "cbHitFader";
        	this.cbHitFader.Size = new System.Drawing.Size(66, 17);
        	this.cbHitFader.TabIndex = 8;
        	this.cbHitFader.Text = "Hit fader";
        	// 
        	// cbAudio
        	// 
        	this.cbAudio.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cbAudio.AutoSize = true;
        	this.cbAudio.Location = new System.Drawing.Point(281, 67);
        	this.cbAudio.Name = "cbAudio";
        	this.cbAudio.Size = new System.Drawing.Size(90, 17);
        	this.cbAudio.TabIndex = 7;
        	this.cbAudio.Text = "Disable audio";
        	// 
        	// cbHQShadows
        	// 
        	this.cbHQShadows.AutoSize = true;
        	this.cbHQShadows.Location = new System.Drawing.Point(13, 44);
        	this.cbHQShadows.Name = "cbHQShadows";
        	this.cbHQShadows.Size = new System.Drawing.Size(186, 17);
        	this.cbHQShadows.TabIndex = 1;
        	this.cbHQShadows.Text = "High detail actor shadows [buggy]";
        	// 
        	// cbShowFPS
        	// 
        	this.cbShowFPS.AutoSize = true;
        	this.cbShowFPS.Location = new System.Drawing.Point(13, 90);
        	this.cbShowFPS.Name = "cbShowFPS";
        	this.cbShowFPS.Size = new System.Drawing.Size(76, 17);
        	this.cbShowFPS.TabIndex = 2;
        	this.cbShowFPS.Text = "Show FPS";
        	// 
        	// cbThreadLoad
        	// 
        	this.cbThreadLoad.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cbThreadLoad.AutoSize = true;
        	this.cbThreadLoad.Checked = true;
        	this.cbThreadLoad.CheckState = System.Windows.Forms.CheckState.Checked;
        	this.cbThreadLoad.Location = new System.Drawing.Point(281, 44);
        	this.cbThreadLoad.Name = "cbThreadLoad";
        	this.cbThreadLoad.Size = new System.Drawing.Size(97, 17);
        	this.cbThreadLoad.TabIndex = 6;
        	this.cbThreadLoad.Text = "Thread loading";
        	// 
        	// cbYesToAll
        	// 
        	this.cbYesToAll.AutoSize = true;
        	this.cbYesToAll.Location = new System.Drawing.Point(13, 21);
        	this.cbYesToAll.Name = "cbYesToAll";
        	this.cbYesToAll.Size = new System.Drawing.Size(147, 17);
        	this.cbYesToAll.TabIndex = 5;
        	this.cbYesToAll.Text = "Allow yes to all load errors";
        	// 
        	// cbSubtitles
        	// 
        	this.cbSubtitles.AutoSize = true;
        	this.cbSubtitles.Location = new System.Drawing.Point(13, 67);
        	this.cbSubtitles.Name = "cbSubtitles";
        	this.cbSubtitles.Size = new System.Drawing.Size(94, 17);
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
        	this.gbMsgs.Location = new System.Drawing.Point(8, 352);
        	this.gbMsgs.Name = "gbMsgs";
        	this.gbMsgs.Size = new System.Drawing.Size(562, 60);
        	this.gbMsgs.TabIndex = 8;
        	this.gbMsgs.TabStop = false;
        	this.gbMsgs.Text = "MGE status messages";
        	// 
        	// cbDisplayMessages
        	// 
        	this.cbDisplayMessages.AutoSize = true;
        	this.cbDisplayMessages.Location = new System.Drawing.Point(18, 27);
        	this.cbDisplayMessages.Name = "cbDisplayMessages";
        	this.cbDisplayMessages.Size = new System.Drawing.Size(110, 17);
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
        	this.udMsgsTime.Location = new System.Drawing.Point(452, 32);
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
        	this.udMsgsTime.Size = new System.Drawing.Size(56, 20);
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
        	this.cmbMsgsLocale.Location = new System.Drawing.Point(281, 31);
        	this.cmbMsgsLocale.Name = "cmbMsgsLocale";
        	this.cmbMsgsLocale.Size = new System.Drawing.Size(128, 21);
        	this.cmbMsgsLocale.Sorted = true;
        	this.cmbMsgsLocale.TabIndex = 0;
        	this.cmbMsgsLocale.Text = "English (default)";
        	// 
        	// lMsgsTime
        	// 
        	this.lMsgsTime.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.lMsgsTime.AutoSize = true;
        	this.lMsgsTime.Location = new System.Drawing.Point(449, 16);
        	this.lMsgsTime.Name = "lMsgsTime";
        	this.lMsgsTime.Size = new System.Drawing.Size(45, 13);
        	this.lMsgsTime.TabIndex = 0;
        	this.lMsgsTime.Text = "Timeout";
        	// 
        	// lMsgsLanguage
        	// 
        	this.lMsgsLanguage.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.lMsgsLanguage.AutoSize = true;
        	this.lMsgsLanguage.Enabled = false;
        	this.lMsgsLanguage.Location = new System.Drawing.Point(279, 15);
        	this.lMsgsLanguage.Name = "lMsgsLanguage";
        	this.lMsgsLanguage.Size = new System.Drawing.Size(110, 13);
        	this.lMsgsLanguage.TabIndex = 0;
        	this.lMsgsLanguage.Text = "Language localization";
        	// 
        	// lMsgsTimeUnit
        	// 
        	this.lMsgsTimeUnit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.lMsgsTimeUnit.AutoSize = true;
        	this.lMsgsTimeUnit.Location = new System.Drawing.Point(509, 34);
        	this.lMsgsTimeUnit.Name = "lMsgsTimeUnit";
        	this.lMsgsTimeUnit.Size = new System.Drawing.Size(20, 13);
        	this.lMsgsTimeUnit.TabIndex = 0;
        	this.lMsgsTimeUnit.Text = "ms";
        	// 
        	// pCam3rdPrsn
        	// 
        	this.pCam3rdPrsn.Controls.Add(this.cbCam3rdPrsn);
        	this.pCam3rdPrsn.Controls.Add(this.gbCam3rdPrsn);
        	this.pCam3rdPrsn.Location = new System.Drawing.Point(8, 129);
        	this.pCam3rdPrsn.Name = "pCam3rdPrsn";
        	this.pCam3rdPrsn.Size = new System.Drawing.Size(250, 72);
        	this.pCam3rdPrsn.TabIndex = 7;
        	this.pCam3rdPrsn.TabStop = true;
        	// 
        	// cbCam3rdPrsn
        	// 
        	this.cbCam3rdPrsn.AutoSize = true;
        	this.cbCam3rdPrsn.Location = new System.Drawing.Point(8, -1);
        	this.cbCam3rdPrsn.Name = "cbCam3rdPrsn";
        	this.cbCam3rdPrsn.Size = new System.Drawing.Size(165, 17);
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
        	this.gbCam3rdPrsn.Size = new System.Drawing.Size(250, 72);
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
        	this.udCam3rdZ.Size = new System.Drawing.Size(60, 20);
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
        	this.udCam3rdY.Size = new System.Drawing.Size(60, 20);
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
        	this.udCam3rdX.Size = new System.Drawing.Size(60, 20);
        	this.udCam3rdX.TabIndex = 0;
        	this.udCam3rdX.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udCam3rdX.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
        	// 
        	// lCam3rdX
        	// 
        	this.lCam3rdX.AutoSize = true;
        	this.lCam3rdX.Location = new System.Drawing.Point(11, 21);
        	this.lCam3rdX.Name = "lCam3rdX";
        	this.lCam3rdX.Size = new System.Drawing.Size(43, 13);
        	this.lCam3rdX.TabIndex = 3;
        	this.lCam3rdX.Text = "X offset";
        	// 
        	// lCam3rdY
        	// 
        	this.lCam3rdY.AutoSize = true;
        	this.lCam3rdY.Location = new System.Drawing.Point(89, 21);
        	this.lCam3rdY.Name = "lCam3rdY";
        	this.lCam3rdY.Size = new System.Drawing.Size(43, 13);
        	this.lCam3rdY.TabIndex = 4;
        	this.lCam3rdY.Text = "Y offset";
        	// 
        	// lCam3rdZ
        	// 
        	this.lCam3rdZ.AutoSize = true;
        	this.lCam3rdZ.Location = new System.Drawing.Point(167, 21);
        	this.lCam3rdZ.Name = "lCam3rdZ";
        	this.lCam3rdZ.Size = new System.Drawing.Size(43, 13);
        	this.lCam3rdZ.TabIndex = 5;
        	this.lCam3rdZ.Text = "Z offset";
        	// 
        	// gbInputTools
        	// 
        	this.gbInputTools.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.gbInputTools.Controls.Add(this.bMacroEd);
        	this.gbInputTools.Controls.Add(this.bRemapper);
        	this.gbInputTools.Location = new System.Drawing.Point(403, 3);
        	this.gbInputTools.Name = "gbInputTools";
        	this.gbInputTools.Size = new System.Drawing.Size(167, 119);
        	this.gbInputTools.TabIndex = 1;
        	this.gbInputTools.TabStop = false;
        	this.gbInputTools.Text = "Input tools";
        	// 
        	// bMacroEd
        	// 
        	this.bMacroEd.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.bMacroEd.Location = new System.Drawing.Point(6, 19);
        	this.bMacroEd.Name = "bMacroEd";
        	this.bMacroEd.Size = new System.Drawing.Size(155, 25);
        	this.bMacroEd.TabIndex = 0;
        	this.bMacroEd.Text = "Macro editor";
        	this.bMacroEd.Click += new System.EventHandler(this.bMacroEd_Click);
        	// 
        	// bRemapper
        	// 
        	this.bRemapper.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.bRemapper.Location = new System.Drawing.Point(6, 50);
        	this.bRemapper.Name = "bRemapper";
        	this.bRemapper.Size = new System.Drawing.Size(155, 25);
        	this.bRemapper.TabIndex = 1;
        	this.bRemapper.Text = "Key remapper";
        	this.bRemapper.Click += new System.EventHandler(this.bRemapper_Click);
        	// 
        	// gbInputOpts
        	// 
        	this.gbInputOpts.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.gbInputOpts.Controls.Add(this.cbMenuCaching);
        	this.gbInputOpts.Controls.Add(this.cbAutoCrosshair);
        	this.gbInputOpts.Controls.Add(this.cbDisableMGE);
        	this.gbInputOpts.Controls.Add(this.cbDisableMWSE);
        	this.gbInputOpts.Controls.Add(this.cbSkipMovie);
        	this.gbInputOpts.Controls.Add(this.cbAltCombat);
        	this.gbInputOpts.Location = new System.Drawing.Point(8, 3);
        	this.gbInputOpts.Name = "gbInputOpts";
        	this.gbInputOpts.Size = new System.Drawing.Size(389, 119);
        	this.gbInputOpts.TabIndex = 0;
        	this.gbInputOpts.TabStop = false;
        	this.gbInputOpts.Text = "Options";
        	// 
        	// cbMenuCaching
        	// 
        	this.cbMenuCaching.AutoSize = true;
        	this.cbMenuCaching.Checked = true;
        	this.cbMenuCaching.CheckState = System.Windows.Forms.CheckState.Checked;
        	this.cbMenuCaching.Location = new System.Drawing.Point(178, 88);
        	this.cbMenuCaching.Name = "cbMenuCaching";
        	this.cbMenuCaching.Size = new System.Drawing.Size(152, 17);
        	this.cbMenuCaching.TabIndex = 11;
        	this.cbMenuCaching.Text = "Responsive menu caching";
        	this.cbMenuCaching.UseVisualStyleBackColor = true;
        	// 
        	// cbAutoCrosshair
        	// 
        	this.cbAutoCrosshair.AutoSize = true;
        	this.cbAutoCrosshair.Location = new System.Drawing.Point(178, 65);
        	this.cbAutoCrosshair.Name = "cbAutoCrosshair";
        	this.cbAutoCrosshair.Size = new System.Drawing.Size(113, 17);
        	this.cbAutoCrosshair.TabIndex = 10;
        	this.cbAutoCrosshair.Text = "Crosshair autohide";
        	this.cbAutoCrosshair.UseVisualStyleBackColor = true;
        	// 
        	// cbDisableMGE
        	// 
        	this.cbDisableMGE.AutoSize = true;
        	this.cbDisableMGE.Location = new System.Drawing.Point(11, 19);
        	this.cbDisableMGE.Name = "cbDisableMGE";
        	this.cbDisableMGE.Size = new System.Drawing.Size(128, 17);
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
        	this.cbDisableMWSE.Size = new System.Drawing.Size(135, 17);
        	this.cbDisableMWSE.TabIndex = 8;
        	this.cbDisableMWSE.Text = "Disable internal MWSE";
        	// 
        	// cbSkipMovie
        	// 
        	this.cbSkipMovie.AutoSize = true;
        	this.cbSkipMovie.Checked = true;
        	this.cbSkipMovie.CheckState = System.Windows.Forms.CheckState.Checked;
        	this.cbSkipMovie.Location = new System.Drawing.Point(178, 19);
        	this.cbSkipMovie.Name = "cbSkipMovie";
        	this.cbSkipMovie.Size = new System.Drawing.Size(119, 17);
        	this.cbSkipMovie.TabIndex = 0;
        	this.cbSkipMovie.Text = "Skip opening movie";
        	// 
        	// cbAltCombat
        	// 
        	this.cbAltCombat.AutoSize = true;
        	this.cbAltCombat.Location = new System.Drawing.Point(178, 42);
        	this.cbAltCombat.Name = "cbAltCombat";
        	this.cbAltCombat.Size = new System.Drawing.Size(154, 17);
        	this.cbAltCombat.TabIndex = 2;
        	this.cbAltCombat.Text = "Alternative combat controls";
        	// 
        	// lSShotFormat
        	// 
        	this.lSShotFormat.AutoSize = true;
        	this.lSShotFormat.Dock = System.Windows.Forms.DockStyle.Right;
        	this.lSShotFormat.Location = new System.Drawing.Point(297, 0);
        	this.lSShotFormat.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
        	this.lSShotFormat.Name = "lSShotFormat";
        	this.lSShotFormat.Size = new System.Drawing.Size(39, 25);
        	this.lSShotFormat.TabIndex = 0;
        	this.lSShotFormat.Text = "Format";
        	this.lSShotFormat.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// cmbSShotFormat
        	// 
        	this.cmbSShotFormat.Dock = System.Windows.Forms.DockStyle.Right;
        	this.cmbSShotFormat.Items.AddRange(new object[] {
        	        	        	"BMP",
        	        	        	"JPEG",
        	        	        	"DDS",
        	        	        	"PNG",
        	        	        	"TGA"});
        	this.cmbSShotFormat.Location = new System.Drawing.Point(342, 3);
        	this.cmbSShotFormat.Name = "cmbSShotFormat";
        	this.cmbSShotFormat.Size = new System.Drawing.Size(45, 21);
        	this.cmbSShotFormat.TabIndex = 1;
        	this.cmbSShotFormat.Text = "PNG";
        	// 
        	// tpGlobal
        	// 
        	this.tpGlobal.Controls.Add(this.gbSShot);
        	this.tpGlobal.Controls.Add(this.gbScene);
        	this.tpGlobal.Controls.Add(this.gbDisplay);
        	this.tpGlobal.Location = new System.Drawing.Point(4, 21);
        	this.tpGlobal.Name = "tpGlobal";
        	this.tpGlobal.Size = new System.Drawing.Size(578, 420);
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
        	this.gbSShot.Controls.Add(this.tableLayoutPanel1);
        	this.gbSShot.Controls.Add(this.udSShotNum);
        	this.gbSShot.Controls.Add(this.bSShotDirClear);
        	this.gbSShot.Controls.Add(this.bSShotDirBrowse);
        	this.gbSShot.Controls.Add(this.lSShotNum);
        	this.gbSShot.Location = new System.Drawing.Point(8, 295);
        	this.gbSShot.Name = "gbSShot";
        	this.gbSShot.Size = new System.Drawing.Size(562, 89);
        	this.gbSShot.TabIndex = 2;
        	this.gbSShot.TabStop = false;
        	this.gbSShot.Text = "Screenshots";
        	// 
        	// tableLayoutPanel1
        	// 
        	this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.tableLayoutPanel1.AutoSize = true;
        	this.tableLayoutPanel1.ColumnCount = 4;
        	this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
        	this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
        	this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
        	this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
        	this.tableLayoutPanel1.Controls.Add(this.lSShotDir, 0, 2);
        	this.tableLayoutPanel1.Controls.Add(this.lSShotName, 0, 0);
        	this.tableLayoutPanel1.Controls.Add(this.tbSShotName, 1, 0);
        	this.tableLayoutPanel1.Controls.Add(this.tbSShotDir, 1, 2);
        	this.tableLayoutPanel1.Controls.Add(this.cmbSShotFormat, 3, 0);
        	this.tableLayoutPanel1.Controls.Add(this.lSShotFormat, 2, 0);
        	this.tableLayoutPanel1.Location = new System.Drawing.Point(6, 18);
        	this.tableLayoutPanel1.Name = "tableLayoutPanel1";
        	this.tableLayoutPanel1.RowCount = 3;
        	this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
        	this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 4F));
        	this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
        	this.tableLayoutPanel1.Size = new System.Drawing.Size(390, 58);
        	this.tableLayoutPanel1.TabIndex = 6;
        	// 
        	// lSShotDir
        	// 
        	this.lSShotDir.Anchor = System.Windows.Forms.AnchorStyles.Right;
        	this.lSShotDir.AutoSize = true;
        	this.lSShotDir.Location = new System.Drawing.Point(3, 37);
        	this.lSShotDir.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
        	this.lSShotDir.Name = "lSShotDir";
        	this.lSShotDir.Size = new System.Drawing.Size(82, 13);
        	this.lSShotDir.TabIndex = 0;
        	this.lSShotDir.Text = "Output directory";
        	this.lSShotDir.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// lSShotName
        	// 
        	this.lSShotName.AutoSize = true;
        	this.lSShotName.Dock = System.Windows.Forms.DockStyle.Right;
        	this.lSShotName.Location = new System.Drawing.Point(5, 0);
        	this.lSShotName.Margin = new System.Windows.Forms.Padding(3, 0, 3, 2);
        	this.lSShotName.Name = "lSShotName";
        	this.lSShotName.Size = new System.Drawing.Size(80, 25);
        	this.lSShotName.TabIndex = 0;
        	this.lSShotName.Text = "File name prefix";
        	this.lSShotName.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// tbSShotName
        	// 
        	this.tbSShotName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.tbSShotName.Location = new System.Drawing.Point(91, 3);
        	this.tbSShotName.Name = "tbSShotName";
        	this.tbSShotName.Size = new System.Drawing.Size(200, 20);
        	this.tbSShotName.TabIndex = 0;
        	this.tbSShotName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.fileNameFilter_KeyPress);
        	// 
        	// tbSShotDir
        	// 
        	this.tbSShotDir.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.tableLayoutPanel1.SetColumnSpan(this.tbSShotDir, 3);
        	this.tbSShotDir.Location = new System.Drawing.Point(91, 34);
        	this.tbSShotDir.Name = "tbSShotDir";
        	this.tbSShotDir.ReadOnly = true;
        	this.tbSShotDir.Size = new System.Drawing.Size(296, 20);
        	this.tbSShotDir.TabIndex = 3;
        	this.tbSShotDir.Text = "- Morrowind folder -";
        	this.tbSShotDir.TextAlignChanged += new System.EventHandler(this.tbSSDir_TextAlignChanged);
        	// 
        	// udSShotNum
        	// 
        	this.udSShotNum.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.udSShotNum.Location = new System.Drawing.Point(521, 22);
        	this.udSShotNum.Maximum = new decimal(new int[] {
        	        	        	5,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udSShotNum.Minimum = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udSShotNum.Name = "udSShotNum";
        	this.udSShotNum.Size = new System.Drawing.Size(32, 20);
        	this.udSShotNum.TabIndex = 2;
        	this.udSShotNum.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udSShotNum.Value = new decimal(new int[] {
        	        	        	3,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	// 
        	// bSShotDirClear
        	// 
        	this.bSShotDirClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bSShotDirClear.Location = new System.Drawing.Point(483, 51);
        	this.bSShotDirClear.Name = "bSShotDirClear";
        	this.bSShotDirClear.Size = new System.Drawing.Size(70, 22);
        	this.bSShotDirClear.TabIndex = 5;
        	this.bSShotDirClear.Text = "Clear";
        	this.bSShotDirClear.UseVisualStyleBackColor = true;
        	this.bSShotDirClear.Click += new System.EventHandler(this.bSSDirClear_Click);
        	// 
        	// bSShotDirBrowse
        	// 
        	this.bSShotDirBrowse.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bSShotDirBrowse.Location = new System.Drawing.Point(405, 51);
        	this.bSShotDirBrowse.Name = "bSShotDirBrowse";
        	this.bSShotDirBrowse.Size = new System.Drawing.Size(70, 22);
        	this.bSShotDirBrowse.TabIndex = 4;
        	this.bSShotDirBrowse.Text = "Browse";
        	this.bSShotDirBrowse.UseVisualStyleBackColor = true;
        	this.bSShotDirBrowse.Click += new System.EventHandler(this.bSShotDirBrowse_Click);
        	// 
        	// lSShotNum
        	// 
        	this.lSShotNum.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.lSShotNum.Location = new System.Drawing.Point(378, 20);
        	this.lSShotNum.Name = "lSShotNum";
        	this.lSShotNum.Size = new System.Drawing.Size(137, 21);
        	this.lSShotNum.TabIndex = 0;
        	this.lSShotNum.Text = "Num. chars minimum";
        	this.lSShotNum.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// gbScene
        	// 
        	this.gbScene.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.gbScene.Controls.Add(this.lHDR2);
        	this.gbScene.Controls.Add(this.bAutoFOV);
        	this.gbScene.Controls.Add(this.lFPSLimit);
        	this.gbScene.Controls.Add(this.udFPSLimit);
        	this.gbScene.Controls.Add(this.udHDR);
        	this.gbScene.Controls.Add(this.bShaderEd);
        	this.gbScene.Controls.Add(this.lHDR);
        	this.gbScene.Controls.Add(this.cmbFogMode);
        	this.gbScene.Controls.Add(this.lFogMode);
        	this.gbScene.Controls.Add(this.lLOD);
        	this.gbScene.Controls.Add(this.udLOD);
        	this.gbScene.Controls.Add(this.cbHWShader);
        	this.gbScene.Controls.Add(this.cbFPSCounter);
        	this.gbScene.Controls.Add(this.udFOV);
        	this.gbScene.Controls.Add(this.lFOV);
        	this.gbScene.Location = new System.Drawing.Point(8, 142);
        	this.gbScene.Name = "gbScene";
        	this.gbScene.Size = new System.Drawing.Size(562, 147);
        	this.gbScene.TabIndex = 1;
        	this.gbScene.TabStop = false;
        	this.gbScene.Text = "Renderer";
        	// 
        	// lHDR2
        	// 
        	this.lHDR2.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.lHDR2.AutoSize = true;
        	this.lHDR2.Location = new System.Drawing.Point(217, 57);
        	this.lHDR2.Name = "lHDR2";
        	this.lHDR2.Size = new System.Drawing.Size(24, 13);
        	this.lHDR2.TabIndex = 21;
        	this.lHDR2.Text = "sec";
        	// 
        	// bAutoFOV
        	// 
        	this.bAutoFOV.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.bAutoFOV.Location = new System.Drawing.Point(296, 23);
        	this.bAutoFOV.Name = "bAutoFOV";
        	this.bAutoFOV.Size = new System.Drawing.Size(65, 20);
        	this.bAutoFOV.TabIndex = 20;
        	this.bAutoFOV.Text = "Auto FOV";
        	this.bAutoFOV.UseVisualStyleBackColor = true;
        	this.bAutoFOV.Click += new System.EventHandler(this.bAutoFOV_Click);
        	// 
        	// lFPSLimit
        	// 
        	this.lFPSLimit.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.lFPSLimit.AutoSize = true;
        	this.lFPSLimit.Location = new System.Drawing.Point(436, 78);
        	this.lFPSLimit.Name = "lFPSLimit";
        	this.lFPSLimit.Size = new System.Drawing.Size(56, 13);
        	this.lFPSLimit.TabIndex = 19;
        	this.lFPSLimit.Text = "FPS limiter";
        	// 
        	// udFPSLimit
        	// 
        	this.udFPSLimit.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.udFPSLimit.Location = new System.Drawing.Point(367, 76);
        	this.udFPSLimit.Maximum = new decimal(new int[] {
        	        	        	120,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udFPSLimit.Name = "udFPSLimit";
        	this.udFPSLimit.Size = new System.Drawing.Size(63, 20);
        	this.udFPSLimit.TabIndex = 18;
        	this.udFPSLimit.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	// 
        	// udHDR
        	// 
        	this.udHDR.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.udHDR.DecimalPlaces = 2;
        	this.udHDR.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udHDR.Location = new System.Drawing.Point(155, 55);
        	this.udHDR.Maximum = new decimal(new int[] {
        	        	        	30,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udHDR.Name = "udHDR";
        	this.udHDR.Size = new System.Drawing.Size(56, 20);
        	this.udHDR.TabIndex = 0;
        	this.udHDR.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udHDR.UpDownAlign = System.Windows.Forms.LeftRightAlignment.Left;
        	this.udHDR.Value = new decimal(new int[] {
        	        	        	2,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	// 
        	// bShaderEd
        	// 
        	this.bShaderEd.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.bShaderEd.Location = new System.Drawing.Point(145, 19);
        	this.bShaderEd.Name = "bShaderEd";
        	this.bShaderEd.Size = new System.Drawing.Size(112, 25);
        	this.bShaderEd.TabIndex = 17;
        	this.bShaderEd.Text = "Shader setup";
        	this.bShaderEd.Click += new System.EventHandler(this.bShaderEd_Click);
        	// 
        	// lHDR
        	// 
        	this.lHDR.AutoSize = true;
        	this.lHDR.Location = new System.Drawing.Point(26, 57);
        	this.lHDR.Name = "lHDR";
        	this.lHDR.Size = new System.Drawing.Size(94, 13);
        	this.lHDR.TabIndex = 0;
        	this.lHDR.Text = "HDR reaction time";
        	// 
        	// cmbFogMode
        	// 
        	this.cmbFogMode.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cmbFogMode.Items.AddRange(new object[] {
        	        	        	"Depth pixel (Fast)",
        	        	        	"Depth vertex",
        	        	        	"Range vertex (Best)"});
        	this.cmbFogMode.Location = new System.Drawing.Point(315, 49);
        	this.cmbFogMode.Name = "cmbFogMode";
        	this.cmbFogMode.Size = new System.Drawing.Size(116, 21);
        	this.cmbFogMode.TabIndex = 13;
        	this.cmbFogMode.Text = "Depth pixel (Fast)";
        	this.cmbFogMode.SelectedIndexChanged += new System.EventHandler(this.cmbFogMode_SelectedIndexChanged);
        	// 
        	// lFogMode
        	// 
        	this.lFogMode.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.lFogMode.AutoSize = true;
        	this.lFogMode.Location = new System.Drawing.Point(437, 52);
        	this.lFogMode.Name = "lFogMode";
        	this.lFogMode.Size = new System.Drawing.Size(54, 13);
        	this.lFogMode.TabIndex = 12;
        	this.lFogMode.Text = "Fog mode";
        	// 
        	// lLOD
        	// 
        	this.lLOD.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.lLOD.AutoSize = true;
        	this.lLOD.Location = new System.Drawing.Point(436, 104);
        	this.lLOD.Name = "lLOD";
        	this.lLOD.Size = new System.Drawing.Size(91, 13);
        	this.lLOD.TabIndex = 9;
        	this.lLOD.Text = "Mipmap LOD bias";
        	// 
        	// udLOD
        	// 
        	this.udLOD.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.udLOD.DecimalPlaces = 2;
        	this.udLOD.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udLOD.Location = new System.Drawing.Point(366, 102);
        	this.udLOD.Maximum = new decimal(new int[] {
        	        	        	2,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udLOD.Minimum = new decimal(new int[] {
        	        	        	2,
        	        	        	0,
        	        	        	0,
        	        	        	-2147483648});
        	this.udLOD.Name = "udLOD";
        	this.udLOD.Size = new System.Drawing.Size(64, 20);
        	this.udLOD.TabIndex = 11;
        	this.udLOD.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	// 
        	// cbHWShader
        	// 
        	this.cbHWShader.AutoSize = true;
        	this.cbHWShader.Location = new System.Drawing.Point(10, 24);
        	this.cbHWShader.Name = "cbHWShader";
        	this.cbHWShader.Size = new System.Drawing.Size(99, 17);
        	this.cbHWShader.TabIndex = 14;
        	this.cbHWShader.Text = "Enable shaders";
        	// 
        	// cbFPSCounter
        	// 
        	this.cbFPSCounter.AutoSize = true;
        	this.cbFPSCounter.Location = new System.Drawing.Point(10, 100);
        	this.cbFPSCounter.Name = "cbFPSCounter";
        	this.cbFPSCounter.Size = new System.Drawing.Size(83, 17);
        	this.cbFPSCounter.TabIndex = 5;
        	this.cbFPSCounter.Text = "Display FPS";
        	// 
        	// udFOV
        	// 
        	this.udFOV.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.udFOV.DecimalPlaces = 2;
        	this.udFOV.Increment = new decimal(new int[] {
        	        	        	2,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udFOV.Location = new System.Drawing.Point(367, 23);
        	this.udFOV.Maximum = new decimal(new int[] {
        	        	        	150,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udFOV.Minimum = new decimal(new int[] {
        	        	        	5,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udFOV.Name = "udFOV";
        	this.udFOV.Size = new System.Drawing.Size(64, 20);
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
        	this.lFOV.Location = new System.Drawing.Point(437, 25);
        	this.lFOV.Name = "lFOV";
        	this.lFOV.Size = new System.Drawing.Size(56, 13);
        	this.lFOV.TabIndex = 3;
        	this.lFOV.Text = "Horz. FOV";
        	// 
        	// gbDisplay
        	// 
        	this.gbDisplay.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.gbDisplay.Controls.Add(this.tableLayoutDisplay);
        	this.gbDisplay.Controls.Add(this.tbAspect);
        	this.gbDisplay.Controls.Add(this.bCalcResolution);
        	this.gbDisplay.Controls.Add(this.cbWindowed);
        	this.gbDisplay.Controls.Add(this.cmbRefreshRate);
        	this.gbDisplay.Controls.Add(this.bCalcRefresh);
        	this.gbDisplay.Controls.Add(this.tbResolution);
        	this.gbDisplay.Controls.Add(this.lResolution);
        	this.gbDisplay.Controls.Add(this.lAspect);
        	this.gbDisplay.Controls.Add(this.lRefreshRate);
        	this.gbDisplay.Location = new System.Drawing.Point(8, 3);
        	this.gbDisplay.Name = "gbDisplay";
        	this.gbDisplay.Size = new System.Drawing.Size(562, 133);
        	this.gbDisplay.TabIndex = 0;
        	this.gbDisplay.TabStop = false;
        	this.gbDisplay.Text = "Display";
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
        	this.tableLayoutDisplay.Location = new System.Drawing.Point(10, 91);
        	this.tableLayoutDisplay.Name = "tableLayoutDisplay";
        	this.tableLayoutDisplay.RowCount = 1;
        	this.tableLayoutDisplay.RowStyles.Add(new System.Windows.Forms.RowStyle());
        	this.tableLayoutDisplay.Size = new System.Drawing.Size(543, 27);
        	this.tableLayoutDisplay.TabIndex = 0;
        	// 
        	// cmbAntiAlias
        	// 
        	this.cmbAntiAlias.ContextMenu = this.DudMenu;
        	this.cmbAntiAlias.Items.AddRange(new object[] {
        	        	        	"None",
        	        	        	"2x",
        	        	        	"3x",
        	        	        	"4x",
        	        	        	"5x",
        	        	        	"6x",
        	        	        	"7x",
        	        	        	"8x",
        	        	        	"9x",
        	        	        	"10x",
        	        	        	"11x",
        	        	        	"12x",
        	        	        	"13x",
        	        	        	"14x",
        	        	        	"15x",
        	        	        	"16x"});
        	this.cmbAntiAlias.Location = new System.Drawing.Point(3, 3);
        	this.cmbAntiAlias.Name = "cmbAntiAlias";
        	this.cmbAntiAlias.Size = new System.Drawing.Size(64, 21);
        	this.cmbAntiAlias.TabIndex = 0;
        	this.cmbAntiAlias.Text = "None";
        	this.cmbAntiAlias.SelectedIndexChanged += new System.EventHandler(this.cmbAlias_SelectedIndexChanged);
        	this.cmbAntiAlias.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
        	// 
        	// lAntiAlias
        	// 
        	this.lAntiAlias.Anchor = System.Windows.Forms.AnchorStyles.Left;
        	this.lAntiAlias.AutoSize = true;
        	this.lAntiAlias.Location = new System.Drawing.Point(73, 6);
        	this.lAntiAlias.Margin = new System.Windows.Forms.Padding(3, 0, 3, 1);
        	this.lAntiAlias.Name = "lAntiAlias";
        	this.lAntiAlias.Size = new System.Drawing.Size(60, 13);
        	this.lAntiAlias.TabIndex = 0;
        	this.lAntiAlias.Text = "Antialiasing";
        	// 
        	// cmbVWait
        	// 
        	this.cmbVWait.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cmbVWait.Items.AddRange(new object[] {
        	        	        	"Off",
        	        	        	"On",
        	        	        	"x2",
        	        	        	"x3",
        	        	        	"x4"});
        	this.cmbVWait.Location = new System.Drawing.Point(364, 3);
        	this.cmbVWait.Name = "cmbVWait";
        	this.cmbVWait.Size = new System.Drawing.Size(80, 21);
        	this.cmbVWait.TabIndex = 2;
        	this.cmbVWait.Text = "Off";
        	this.cmbVWait.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
        	// 
        	// cmbAnisoLevel
        	// 
        	this.cmbAnisoLevel.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cmbAnisoLevel.Items.AddRange(new object[] {
        	        	        	"Off",
        	        	        	"2x",
        	        	        	"4x",
        	        	        	"8x",
        	        	        	"16x"});
        	this.cmbAnisoLevel.Location = new System.Drawing.Point(168, 3);
        	this.cmbAnisoLevel.Name = "cmbAnisoLevel";
        	this.cmbAnisoLevel.Size = new System.Drawing.Size(64, 21);
        	this.cmbAnisoLevel.TabIndex = 10;
        	this.cmbAnisoLevel.Text = "Off";
        	this.cmbAnisoLevel.SelectedIndexChanged += new System.EventHandler(this.cmbAnsiLevel_SelectedIndexChanged);
        	// 
        	// lAnisoLevel
        	// 
        	this.lAnisoLevel.Anchor = System.Windows.Forms.AnchorStyles.Left;
        	this.lAnisoLevel.AutoSize = true;
        	this.lAnisoLevel.Location = new System.Drawing.Point(238, 6);
        	this.lAnisoLevel.Margin = new System.Windows.Forms.Padding(3, 0, 3, 1);
        	this.lAnisoLevel.Name = "lAnisoLevel";
        	this.lAnisoLevel.Size = new System.Drawing.Size(95, 13);
        	this.lAnisoLevel.TabIndex = 8;
        	this.lAnisoLevel.Text = "Anisotropic filtering";
        	// 
        	// lVWait
        	// 
        	this.lVWait.Anchor = System.Windows.Forms.AnchorStyles.Left;
        	this.lVWait.AutoSize = true;
        	this.lVWait.Location = new System.Drawing.Point(450, 6);
        	this.lVWait.Margin = new System.Windows.Forms.Padding(3, 0, 3, 1);
        	this.lVWait.Name = "lVWait";
        	this.lVWait.Size = new System.Drawing.Size(38, 13);
        	this.lVWait.TabIndex = 0;
        	this.lVWait.Text = "VSync";
        	// 
        	// tbAspect
        	// 
        	this.tbAspect.Location = new System.Drawing.Point(182, 22);
        	this.tbAspect.Name = "tbAspect";
        	this.tbAspect.ReadOnly = true;
        	this.tbAspect.Size = new System.Drawing.Size(36, 20);
        	this.tbAspect.TabIndex = 2;
        	this.tbAspect.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
        	// 
        	// bCalcResolution
        	// 
        	this.bCalcResolution.Location = new System.Drawing.Point(10, 48);
        	this.bCalcResolution.Name = "bCalcResolution";
        	this.bCalcResolution.Size = new System.Drawing.Size(166, 25);
        	this.bCalcResolution.TabIndex = 1;
        	this.bCalcResolution.Text = "Select screen resolution";
        	this.bCalcResolution.Click += new System.EventHandler(this.bCalcResolution_Click);
        	// 
        	// cbWindowed
        	// 
        	this.cbWindowed.AutoSize = true;
        	this.cbWindowed.Location = new System.Drawing.Point(182, 54);
        	this.cbWindowed.Name = "cbWindowed";
        	this.cbWindowed.Size = new System.Drawing.Size(106, 17);
        	this.cbWindowed.TabIndex = 3;
        	this.cbWindowed.Text = "Windowed mode";
        	this.cbWindowed.CheckedChanged += new System.EventHandler(this.cbWindowed_CheckedChanged);
        	// 
        	// cmbRefreshRate
        	// 
        	this.cmbRefreshRate.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.cmbRefreshRate.ItemHeight = 13;
        	this.cmbRefreshRate.Items.AddRange(new object[] {
        	        	        	"Default"});
        	this.cmbRefreshRate.Location = new System.Drawing.Point(475, 22);
        	this.cmbRefreshRate.Name = "cmbRefreshRate";
        	this.cmbRefreshRate.Size = new System.Drawing.Size(72, 21);
        	this.cmbRefreshRate.TabIndex = 3;
        	this.cmbRefreshRate.Text = "Default";
        	// 
        	// bCalcRefresh
        	// 
        	this.bCalcRefresh.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bCalcRefresh.Location = new System.Drawing.Point(364, 49);
        	this.bCalcRefresh.Name = "bCalcRefresh";
        	this.bCalcRefresh.Size = new System.Drawing.Size(185, 25);
        	this.bCalcRefresh.TabIndex = 5;
        	this.bCalcRefresh.Text = "Find valid refresh rates";
        	this.bCalcRefresh.Click += new System.EventHandler(this.bCalcRefresh_Click);
        	// 
        	// tbResolution
        	// 
        	this.tbResolution.Location = new System.Drawing.Point(96, 22);
        	this.tbResolution.Name = "tbResolution";
        	this.tbResolution.ReadOnly = true;
        	this.tbResolution.Size = new System.Drawing.Size(80, 20);
        	this.tbResolution.TabIndex = 0;
        	// 
        	// lResolution
        	// 
        	this.lResolution.Location = new System.Drawing.Point(10, 21);
        	this.lResolution.Name = "lResolution";
        	this.lResolution.Size = new System.Drawing.Size(83, 21);
        	this.lResolution.TabIndex = 0;
        	this.lResolution.Text = "Resolution";
        	this.lResolution.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// lAspect
        	// 
        	this.lAspect.AutoSize = true;
        	this.lAspect.Location = new System.Drawing.Point(224, 25);
        	this.lAspect.Name = "lAspect";
        	this.lAspect.Size = new System.Drawing.Size(63, 13);
        	this.lAspect.TabIndex = 0;
        	this.lAspect.Text = "Aspect ratio";
        	this.lAspect.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
        	// 
        	// lRefreshRate
        	// 
        	this.lRefreshRate.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.lRefreshRate.Location = new System.Drawing.Point(292, 21);
        	this.lRefreshRate.Name = "lRefreshRate";
        	this.lRefreshRate.Size = new System.Drawing.Size(177, 21);
        	this.lRefreshRate.TabIndex = 0;
        	this.lRefreshRate.Text = "Refresh rate";
        	this.lRefreshRate.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
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
        	this.tabControl.Size = new System.Drawing.Size(586, 445);
        	this.tabControl.TabIndex = 0;
        	// 
        	// tpDL
        	// 
        	this.tpDL.Controls.Add(this.bDistantLandWizard);
        	this.tpDL.Controls.Add(this.cbDLDistantLand);
        	this.tpDL.Controls.Add(this.gbDistantLand);
        	this.tpDL.Location = new System.Drawing.Point(4, 21);
        	this.tpDL.Name = "tpDL";
        	this.tpDL.Size = new System.Drawing.Size(578, 420);
        	this.tpDL.TabIndex = 7;
        	this.tpDL.Text = "Distant Land";
        	this.tpDL.ToolTipText = "This tab controls whether and how distant land,\ndistant statics, animated grass, " +
        	"reflective water\nare rendered, and also contains weather settings\nfor distant la" +
        	"nd wind speed and fog range.";
        	this.tpDL.UseVisualStyleBackColor = true;
        	// 
        	// bDistantLandWizard
        	// 
        	this.bDistantLandWizard.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.bDistantLandWizard.Location = new System.Drawing.Point(158, 26);
        	this.bDistantLandWizard.Name = "bDistantLandWizard";
        	this.bDistantLandWizard.Size = new System.Drawing.Size(129, 42);
        	this.bDistantLandWizard.TabIndex = 10;
        	this.bDistantLandWizard.Text = "Distant land generator wizard";
        	this.bDistantLandWizard.Click += new System.EventHandler(this.bDistantLandWizard_Click);
        	// 
        	// cbDLDistantLand
        	// 
        	this.cbDLDistantLand.AutoSize = true;
        	this.cbDLDistantLand.Location = new System.Drawing.Point(16, 3);
        	this.cbDLDistantLand.Name = "cbDLDistantLand";
        	this.cbDLDistantLand.Size = new System.Drawing.Size(108, 17);
        	this.cbDLDistantLand.TabIndex = 0;
        	this.cbDLDistantLand.Text = "Use Distant &Land";
        	this.cbDLDistantLand.UseVisualStyleBackColor = true;
        	this.cbDLDistantLand.CheckedChanged += new System.EventHandler(this.cbDistantLand_CheckedChanged);
        	// 
        	// gbDistantLand
        	// 
        	this.gbDistantLand.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
        	        	        	| System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.gbDistantLand.Controls.Add(this.bMWLightSettings);
        	this.gbDistantLand.Controls.Add(this.pDLStatics);
        	this.gbDistantLand.Controls.Add(this.cbDLAutoDist);
        	this.gbDistantLand.Controls.Add(this.gbDLAutoDist);
        	this.gbDistantLand.Controls.Add(this.gbDLWater);
        	this.gbDistantLand.Controls.Add(this.bDLWthr);
        	this.gbDistantLand.Controls.Add(this.gbDLDrawDist);
        	this.gbDistantLand.Controls.Add(this.gbDLFog);
        	this.gbDistantLand.Enabled = false;
        	this.gbDistantLand.Location = new System.Drawing.Point(8, 3);
        	this.gbDistantLand.Name = "gbDistantLand";
        	this.gbDistantLand.Size = new System.Drawing.Size(562, 409);
        	this.gbDistantLand.TabIndex = 1;
        	this.gbDistantLand.TabStop = false;
        	// 
        	// bMWLightSettings
        	// 
        	this.bMWLightSettings.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.bMWLightSettings.Enabled = false;
        	this.bMWLightSettings.Location = new System.Drawing.Point(15, 378);
        	this.bMWLightSettings.Name = "bMWLightSettings";
        	this.bMWLightSettings.Size = new System.Drawing.Size(128, 25);
        	this.bMWLightSettings.TabIndex = 10;
        	this.bMWLightSettings.Text = "Light Settings...";
        	this.bMWLightSettings.UseVisualStyleBackColor = true;
        	// 
        	// pDLStatics
        	// 
        	this.pDLStatics.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.pDLStatics.Controls.Add(this.cbDLDistantStatics);
        	this.pDLStatics.Controls.Add(this.gbDLStatics);
        	this.pDLStatics.Location = new System.Drawing.Point(15, 69);
        	this.pDLStatics.Name = "pDLStatics";
        	this.pDLStatics.Size = new System.Drawing.Size(262, 114);
        	this.pDLStatics.TabIndex = 5;
        	this.pDLStatics.TabStop = true;
        	// 
        	// cbDLDistantStatics
        	// 
        	this.cbDLDistantStatics.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cbDLDistantStatics.AutoSize = true;
        	this.cbDLDistantStatics.Location = new System.Drawing.Point(8, 0);
        	this.cbDLDistantStatics.Name = "cbDLDistantStatics";
        	this.cbDLDistantStatics.Size = new System.Drawing.Size(116, 17);
        	this.cbDLDistantStatics.TabIndex = 0;
        	this.cbDLDistantStatics.Text = "Use Distant &Statics";
        	this.cbDLDistantStatics.UseVisualStyleBackColor = true;
        	this.cbDLDistantStatics.CheckedChanged += new System.EventHandler(this.cbDistantStatics_CheckedChanged);
        	// 
        	// gbDLStatics
        	// 
        	this.gbDLStatics.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.gbDLStatics.Controls.Add(this.udDLDistVeryFar);
        	this.gbDLStatics.Controls.Add(this.udDLDistFar);
        	this.gbDLStatics.Controls.Add(this.udDLDistNear);
        	this.gbDLStatics.Controls.Add(this.udDLSizeVeryFar);
        	this.gbDLStatics.Controls.Add(this.udDLSizeFar);
        	this.gbDLStatics.Controls.Add(this.tbDLNearSize);
        	this.gbDLStatics.Controls.Add(this.lDLVeryFar);
        	this.gbDLStatics.Controls.Add(this.lDLFar);
        	this.gbDLStatics.Controls.Add(this.lDLNear);
        	this.gbDLStatics.Controls.Add(this.lDLMinSize);
        	this.gbDLStatics.Controls.Add(this.lDLEndDist);
        	this.gbDLStatics.Enabled = false;
        	this.gbDLStatics.Location = new System.Drawing.Point(0, 0);
        	this.gbDLStatics.Name = "gbDLStatics";
        	this.gbDLStatics.Size = new System.Drawing.Size(262, 114);
        	this.gbDLStatics.TabIndex = 1;
        	this.gbDLStatics.TabStop = false;
        	// 
        	// udDLDistVeryFar
        	// 
        	this.udDLDistVeryFar.DecimalPlaces = 1;
        	this.udDLDistVeryFar.Location = new System.Drawing.Point(196, 78);
        	this.udDLDistVeryFar.Maximum = new decimal(new int[] {
        	        	        	300,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLDistVeryFar.Name = "udDLDistVeryFar";
        	this.udDLDistVeryFar.Size = new System.Drawing.Size(50, 20);
        	this.udDLDistVeryFar.TabIndex = 5;
        	this.udDLDistVeryFar.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLDistVeryFar.Value = new decimal(new int[] {
        	        	        	5,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLDistVeryFar.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
        	// 
        	// udDLDistFar
        	// 
        	this.udDLDistFar.DecimalPlaces = 1;
        	this.udDLDistFar.Location = new System.Drawing.Point(196, 54);
        	this.udDLDistFar.Maximum = new decimal(new int[] {
        	        	        	2999,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLDistFar.Name = "udDLDistFar";
        	this.udDLDistFar.Size = new System.Drawing.Size(50, 20);
        	this.udDLDistFar.TabIndex = 3;
        	this.udDLDistFar.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLDistFar.Value = new decimal(new int[] {
        	        	        	4,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLDistFar.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
        	// 
        	// udDLDistNear
        	// 
        	this.udDLDistNear.DecimalPlaces = 1;
        	this.udDLDistNear.Location = new System.Drawing.Point(196, 30);
        	this.udDLDistNear.Maximum = new decimal(new int[] {
        	        	        	2998,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLDistNear.Name = "udDLDistNear";
        	this.udDLDistNear.Size = new System.Drawing.Size(50, 20);
        	this.udDLDistNear.TabIndex = 1;
        	this.udDLDistNear.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLDistNear.Value = new decimal(new int[] {
        	        	        	2,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLDistNear.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
        	// 
        	// udDLSizeVeryFar
        	// 
        	this.udDLSizeVeryFar.Increment = new decimal(new int[] {
        	        	        	10,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLSizeVeryFar.Location = new System.Drawing.Point(138, 78);
        	this.udDLSizeVeryFar.Maximum = new decimal(new int[] {
        	        	        	9999,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLSizeVeryFar.Name = "udDLSizeVeryFar";
        	this.udDLSizeVeryFar.Size = new System.Drawing.Size(50, 20);
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
        	this.udDLSizeFar.Increment = new decimal(new int[] {
        	        	        	10,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLSizeFar.Location = new System.Drawing.Point(138, 54);
        	this.udDLSizeFar.Maximum = new decimal(new int[] {
        	        	        	9999,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLSizeFar.Name = "udDLSizeFar";
        	this.udDLSizeFar.Size = new System.Drawing.Size(50, 20);
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
        	// tbDLNearSize
        	// 
        	this.tbDLNearSize.Location = new System.Drawing.Point(138, 30);
        	this.tbDLNearSize.MaxLength = 3;
        	this.tbDLNearSize.Name = "tbDLNearSize";
        	this.tbDLNearSize.ReadOnly = true;
        	this.tbDLNearSize.Size = new System.Drawing.Size(50, 20);
        	this.tbDLNearSize.TabIndex = 0;
        	this.tbDLNearSize.Text = "400";
        	this.tbDLNearSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	// 
        	// lDLVeryFar
        	// 
        	this.lDLVeryFar.Location = new System.Drawing.Point(34, 78);
        	this.lDLVeryFar.Name = "lDLVeryFar";
        	this.lDLVeryFar.Size = new System.Drawing.Size(102, 19);
        	this.lDLVeryFar.TabIndex = 0;
        	this.lDLVeryFar.Text = "Very Far";
        	this.lDLVeryFar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// lDLFar
        	// 
        	this.lDLFar.Location = new System.Drawing.Point(34, 54);
        	this.lDLFar.Name = "lDLFar";
        	this.lDLFar.Size = new System.Drawing.Size(102, 19);
        	this.lDLFar.TabIndex = 0;
        	this.lDLFar.Text = "Far";
        	this.lDLFar.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// lDLNear
        	// 
        	this.lDLNear.Location = new System.Drawing.Point(34, 30);
        	this.lDLNear.Name = "lDLNear";
        	this.lDLNear.Size = new System.Drawing.Size(102, 19);
        	this.lDLNear.TabIndex = 0;
        	this.lDLNear.Text = "Near";
        	this.lDLNear.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// lDLMinSize
        	// 
        	this.lDLMinSize.AutoSize = true;
        	this.lDLMinSize.Location = new System.Drawing.Point(135, 16);
        	this.lDLMinSize.Name = "lDLMinSize";
        	this.lDLMinSize.Size = new System.Drawing.Size(47, 13);
        	this.lDLMinSize.TabIndex = 0;
        	this.lDLMinSize.Text = "Min Size";
        	// 
        	// lDLEndDist
        	// 
        	this.lDLEndDist.AutoSize = true;
        	this.lDLEndDist.Location = new System.Drawing.Point(193, 16);
        	this.lDLEndDist.Name = "lDLEndDist";
        	this.lDLEndDist.Size = new System.Drawing.Size(47, 13);
        	this.lDLEndDist.TabIndex = 0;
        	this.lDLEndDist.Text = "End Dist";
        	// 
        	// cbDLAutoDist
        	// 
        	this.cbDLAutoDist.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cbDLAutoDist.AutoSize = true;
        	this.cbDLAutoDist.Location = new System.Drawing.Point(306, 19);
        	this.cbDLAutoDist.Name = "cbDLAutoDist";
        	this.cbDLAutoDist.Size = new System.Drawing.Size(140, 17);
        	this.cbDLAutoDist.TabIndex = 2;
        	this.cbDLAutoDist.Text = "&Auto set other distances";
        	this.cbDLAutoDist.CheckedChanged += new System.EventHandler(this.cbAutoSetDistances_CheckedChanged);
        	// 
        	// gbDLAutoDist
        	// 
        	this.gbDLAutoDist.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.gbDLAutoDist.Controls.Add(this.rbDLAutoByAFogEnd);
        	this.gbDLAutoDist.Controls.Add(this.rbDLAutoByDrawDist);
        	this.gbDLAutoDist.Enabled = false;
        	this.gbDLAutoDist.Location = new System.Drawing.Point(288, 19);
        	this.gbDLAutoDist.Name = "gbDLAutoDist";
        	this.gbDLAutoDist.Size = new System.Drawing.Size(262, 71);
        	this.gbDLAutoDist.TabIndex = 3;
        	this.gbDLAutoDist.TabStop = false;
        	// 
        	// rbDLAutoByAFogEnd
        	// 
        	this.rbDLAutoByAFogEnd.AutoSize = true;
        	this.rbDLAutoByAFogEnd.Location = new System.Drawing.Point(18, 45);
        	this.rbDLAutoByAFogEnd.Name = "rbDLAutoByAFogEnd";
        	this.rbDLAutoByAFogEnd.Size = new System.Drawing.Size(146, 17);
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
        	this.rbDLAutoByDrawDist.Location = new System.Drawing.Point(18, 22);
        	this.rbDLAutoByDrawDist.Name = "rbDLAutoByDrawDist";
        	this.rbDLAutoByDrawDist.Size = new System.Drawing.Size(110, 17);
        	this.rbDLAutoByDrawDist.TabIndex = 0;
        	this.rbDLAutoByDrawDist.TabStop = true;
        	this.rbDLAutoByDrawDist.Text = "By D&raw Distance";
        	this.rbDLAutoByDrawDist.UseVisualStyleBackColor = true;
        	this.rbDLAutoByDrawDist.CheckedChanged += new System.EventHandler(this.rbDLAutoDist_CheckedChanged);
        	// 
        	// gbDLWater
        	// 
        	this.gbDLWater.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.gbDLWater.Controls.Add(this.cbDLDynRipples);
        	this.gbDLWater.Controls.Add(this.gbDLWtrCaust);
        	this.gbDLWater.Controls.Add(this.gbDLWtrWave);
        	this.gbDLWater.Controls.Add(this.gbDLWtrRefl);
        	this.gbDLWater.Location = new System.Drawing.Point(288, 96);
        	this.gbDLWater.Name = "gbDLWater";
        	this.gbDLWater.Size = new System.Drawing.Size(262, 276);
        	this.gbDLWater.TabIndex = 9;
        	this.gbDLWater.TabStop = false;
        	this.gbDLWater.Text = "&Water";
        	// 
        	// cbDLDynRipples
        	// 
        	this.cbDLDynRipples.AutoSize = true;
        	this.cbDLDynRipples.Location = new System.Drawing.Point(13, 113);
        	this.cbDLDynRipples.Name = "cbDLDynRipples";
        	this.cbDLDynRipples.Size = new System.Drawing.Size(100, 17);
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
        	this.gbDLWtrCaust.Size = new System.Drawing.Size(250, 52);
        	this.gbDLWtrCaust.TabIndex = 4;
        	this.gbDLWtrCaust.TabStop = false;
        	this.gbDLWtrCaust.Text = "&Caustics [underwater refracted lighting]";
        	// 
        	// lDLWtrCaust
        	// 
        	this.lDLWtrCaust.AutoSize = true;
        	this.lDLWtrCaust.Location = new System.Drawing.Point(59, 24);
        	this.lDLWtrCaust.Name = "lDLWtrCaust";
        	this.lDLWtrCaust.Size = new System.Drawing.Size(66, 13);
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
        	this.udDLWtrCaust.Size = new System.Drawing.Size(42, 20);
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
        	this.gbDLWtrWave.Location = new System.Drawing.Point(6, 114);
        	this.gbDLWtrWave.Name = "gbDLWtrWave";
        	this.gbDLWtrWave.Size = new System.Drawing.Size(250, 52);
        	this.gbDLWtrWave.TabIndex = 3;
        	this.gbDLWtrWave.TabStop = false;
        	// 
        	// lDLWtrWave
        	// 
        	this.lDLWtrWave.AutoSize = true;
        	this.lDLWtrWave.Location = new System.Drawing.Point(59, 24);
        	this.lDLWtrWave.Name = "lDLWtrWave";
        	this.lDLWtrWave.Size = new System.Drawing.Size(84, 13);
        	this.lDLWtrWave.TabIndex = 1;
        	this.lDLWtrWave.Text = "Height of wa&ves";
        	this.lDLWtrWave.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
        	// 
        	// udDLWtrWave
        	// 
        	this.udDLWtrWave.Location = new System.Drawing.Point(11, 22);
        	this.udDLWtrWave.Maximum = new decimal(new int[] {
        	        	        	250,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLWtrWave.Name = "udDLWtrWave";
        	this.udDLWtrWave.Size = new System.Drawing.Size(42, 20);
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
        	this.gbDLWtrRefl.Location = new System.Drawing.Point(6, 19);
        	this.gbDLWtrRefl.Name = "gbDLWtrRefl";
        	this.gbDLWtrRefl.Size = new System.Drawing.Size(250, 89);
        	this.gbDLWtrRefl.TabIndex = 0;
        	this.gbDLWtrRefl.TabStop = false;
        	this.gbDLWtrRefl.Text = "Reflections";
        	// 
        	// cbDLReflLand
        	// 
        	this.cbDLReflLand.AutoSize = true;
        	this.cbDLReflLand.Location = new System.Drawing.Point(11, 42);
        	this.cbDLReflLand.Name = "cbDLReflLand";
        	this.cbDLReflLand.Size = new System.Drawing.Size(79, 17);
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
        	this.cbDLReflBlur.Size = new System.Drawing.Size(95, 17);
        	this.cbDLReflBlur.TabIndex = 4;
        	this.cbDLReflBlur.Text = "&Blur reflections";
        	this.cbDLReflBlur.UseVisualStyleBackColor = true;
        	// 
        	// cbDLReflNStatics
        	// 
        	this.cbDLReflNStatics.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cbDLReflNStatics.AutoSize = true;
        	this.cbDLReflNStatics.Location = new System.Drawing.Point(128, 19);
        	this.cbDLReflNStatics.Name = "cbDLReflNStatics";
        	this.cbDLReflNStatics.Size = new System.Drawing.Size(95, 17);
        	this.cbDLReflNStatics.TabIndex = 1;
        	this.cbDLReflNStatics.Text = "&Nearby Statics";
        	this.cbDLReflNStatics.UseVisualStyleBackColor = true;
        	// 
        	// cbDLReflInterior
        	// 
        	this.cbDLReflInterior.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.cbDLReflInterior.AutoSize = true;
        	this.cbDLReflInterior.Enabled = false;
        	this.cbDLReflInterior.Location = new System.Drawing.Point(128, 42);
        	this.cbDLReflInterior.Name = "cbDLReflInterior";
        	this.cbDLReflInterior.Size = new System.Drawing.Size(63, 17);
        	this.cbDLReflInterior.TabIndex = 3;
        	this.cbDLReflInterior.Text = "&Interiors";
        	this.cbDLReflInterior.UseVisualStyleBackColor = true;
        	// 
        	// bDLWthr
        	// 
        	this.bDLWthr.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.bDLWthr.Location = new System.Drawing.Point(150, 378);
        	this.bDLWthr.Name = "bDLWthr";
        	this.bDLWthr.Size = new System.Drawing.Size(128, 25);
        	this.bDLWthr.TabIndex = 8;
        	this.bDLWthr.Text = "Weat&her Settings...";
        	this.bDLWthr.UseVisualStyleBackColor = true;
        	this.bDLWthr.Click += new System.EventHandler(this.bDLWthr_Click);
        	// 
        	// gbDLDrawDist
        	// 
        	this.gbDLDrawDist.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.gbDLDrawDist.Controls.Add(this.lDLDrawDist);
        	this.gbDLDrawDist.Controls.Add(this.udDLDrawDist);
        	this.gbDLDrawDist.Location = new System.Drawing.Point(15, 19);
        	this.gbDLDrawDist.Name = "gbDLDrawDist";
        	this.gbDLDrawDist.Size = new System.Drawing.Size(130, 44);
        	this.gbDLDrawDist.TabIndex = 0;
        	this.gbDLDrawDist.TabStop = false;
        	this.gbDLDrawDist.Text = "&Draw Distance";
        	// 
        	// lDLDrawDist
        	// 
        	this.lDLDrawDist.Location = new System.Drawing.Point(58, 15);
        	this.lDLDrawDist.Name = "lDLDrawDist";
        	this.lDLDrawDist.Size = new System.Drawing.Size(61, 19);
        	this.lDLDrawDist.TabIndex = 0;
        	this.lDLDrawDist.Text = "cells";
        	this.lDLDrawDist.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
        	// 
        	// udDLDrawDist
        	// 
        	this.udDLDrawDist.DecimalPlaces = 1;
        	this.udDLDrawDist.Location = new System.Drawing.Point(6, 15);
        	this.udDLDrawDist.Maximum = new decimal(new int[] {
        	        	        	250,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLDrawDist.Minimum = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLDrawDist.Name = "udDLDrawDist";
        	this.udDLDrawDist.Size = new System.Drawing.Size(50, 20);
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
        	// gbDLFog
        	// 
        	this.gbDLFog.Anchor = System.Windows.Forms.AnchorStyles.Top;
        	this.gbDLFog.Controls.Add(this.cbDLScattering);
        	this.gbDLFog.Controls.Add(this.lDLFogExpMul);
        	this.gbDLFog.Controls.Add(this.udDLFogExpMul);
        	this.gbDLFog.Controls.Add(this.lDLFogI);
        	this.gbDLFog.Controls.Add(this.udDLFogIEnd);
        	this.gbDLFog.Controls.Add(this.udDLFogIStart);
        	this.gbDLFog.Controls.Add(this.udDLFogBEnd);
        	this.gbDLFog.Controls.Add(this.cbDLFogExp);
        	this.gbDLFog.Controls.Add(this.udDLFogBStart);
        	this.gbDLFog.Controls.Add(this.udDLFogAEnd);
        	this.gbDLFog.Controls.Add(this.udDLFogAStart);
        	this.gbDLFog.Controls.Add(this.lDLFogB);
        	this.gbDLFog.Controls.Add(this.lDLFogA);
        	this.gbDLFog.Controls.Add(this.lDLFogStart);
        	this.gbDLFog.Controls.Add(this.lDLFogEnd);
        	this.gbDLFog.Location = new System.Drawing.Point(15, 189);
        	this.gbDLFog.Name = "gbDLFog";
        	this.gbDLFog.Size = new System.Drawing.Size(262, 183);
        	this.gbDLFog.TabIndex = 6;
        	this.gbDLFog.TabStop = false;
        	this.gbDLFog.Text = "&Fog";
        	// 
        	// cbDLScattering
        	// 
        	this.cbDLScattering.AutoSize = true;
        	this.cbDLScattering.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
        	this.cbDLScattering.Enabled = false;
        	this.cbDLScattering.Location = new System.Drawing.Point(11, 153);
        	this.cbDLScattering.Name = "cbDLScattering";
        	this.cbDLScattering.RightToLeft = System.Windows.Forms.RightToLeft.No;
        	this.cbDLScattering.Size = new System.Drawing.Size(237, 17);
        	this.cbDLScattering.TabIndex = 9;
        	this.cbDLScattering.Text = "High quality atmosphere && distance &colouring";
        	this.cbDLScattering.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	this.cbDLScattering.UseVisualStyleBackColor = true;
        	// 
        	// lDLFogExpMul
        	// 
        	this.lDLFogExpMul.Enabled = false;
        	this.lDLFogExpMul.Location = new System.Drawing.Point(19, 126);
        	this.lDLFogExpMul.Name = "lDLFogExpMul";
        	this.lDLFogExpMul.Size = new System.Drawing.Size(173, 19);
        	this.lDLFogExpMul.TabIndex = 8;
        	this.lDLFogExpMul.Text = "Exponential distance multiplier";
        	this.lDLFogExpMul.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// udDLFogExpMul
        	// 
        	this.udDLFogExpMul.DecimalPlaces = 1;
        	this.udDLFogExpMul.Enabled = false;
        	this.udDLFogExpMul.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogExpMul.Location = new System.Drawing.Point(198, 127);
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
        	this.udDLFogExpMul.Size = new System.Drawing.Size(50, 20);
        	this.udDLFogExpMul.TabIndex = 7;
        	this.udDLFogExpMul.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLFogExpMul.Value = new decimal(new int[] {
        	        	        	4,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLFogExpMul.ValueChanged += new System.EventHandler(this.udDLFogExpMul_ValueChanged);
        	// 
        	// lDLFogI
        	// 
        	this.lDLFogI.Location = new System.Drawing.Point(22, 78);
        	this.lDLFogI.Name = "lDLFogI";
        	this.lDLFogI.Size = new System.Drawing.Size(116, 19);
        	this.lDLFogI.TabIndex = 0;
        	this.lDLFogI.Text = "Distant Interiors Fog";
        	this.lDLFogI.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// udDLFogIEnd
        	// 
        	this.udDLFogIEnd.DecimalPlaces = 2;
        	this.udDLFogIEnd.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogIEnd.Location = new System.Drawing.Point(198, 78);
        	this.udDLFogIEnd.Maximum = new decimal(new int[] {
        	        	        	10,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLFogIEnd.Minimum = new decimal(new int[] {
        	        	        	10,
        	        	        	0,
        	        	        	0,
        	        	        	131072});
        	this.udDLFogIEnd.Name = "udDLFogIEnd";
        	this.udDLFogIEnd.Size = new System.Drawing.Size(50, 20);
        	this.udDLFogIEnd.TabIndex = 5;
        	this.udDLFogIEnd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLFogIEnd.Value = new decimal(new int[] {
        	        	        	20,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogIEnd.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
        	// 
        	// udDLFogIStart
        	// 
        	this.udDLFogIStart.DecimalPlaces = 2;
        	this.udDLFogIStart.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogIStart.Location = new System.Drawing.Point(140, 78);
        	this.udDLFogIStart.Maximum = new decimal(new int[] {
        	        	        	990,
        	        	        	0,
        	        	        	0,
        	        	        	131072});
        	this.udDLFogIStart.Minimum = new decimal(new int[] {
        	        	        	90,
        	        	        	0,
        	        	        	0,
        	        	        	-2147352576});
        	this.udDLFogIStart.Name = "udDLFogIStart";
        	this.udDLFogIStart.Size = new System.Drawing.Size(50, 20);
        	this.udDLFogIStart.TabIndex = 4;
        	this.udDLFogIStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLFogIStart.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
        	// 
        	// udDLFogBEnd
        	// 
        	this.udDLFogBEnd.DecimalPlaces = 1;
        	this.udDLFogBEnd.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogBEnd.Location = new System.Drawing.Point(198, 54);
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
        	this.udDLFogBEnd.Size = new System.Drawing.Size(50, 20);
        	this.udDLFogBEnd.TabIndex = 3;
        	this.udDLFogBEnd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLFogBEnd.Value = new decimal(new int[] {
        	        	        	3,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogBEnd.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
        	// 
        	// cbDLFogExp
        	// 
        	this.cbDLFogExp.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
        	this.cbDLFogExp.Location = new System.Drawing.Point(22, 104);
        	this.cbDLFogExp.Name = "cbDLFogExp";
        	this.cbDLFogExp.Size = new System.Drawing.Size(226, 18);
        	this.cbDLFogExp.TabIndex = 6;
        	this.cbDLFogExp.Text = "Use high quality (e&xponential) fog";
        	this.cbDLFogExp.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	this.cbDLFogExp.UseVisualStyleBackColor = true;
        	this.cbDLFogExp.CheckedChanged += new System.EventHandler(this.cbDLFogExp_CheckedChanged);
        	// 
        	// udDLFogBStart
        	// 
        	this.udDLFogBStart.DecimalPlaces = 1;
        	this.udDLFogBStart.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogBStart.Location = new System.Drawing.Point(140, 54);
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
        	this.udDLFogBStart.Size = new System.Drawing.Size(50, 20);
        	this.udDLFogBStart.TabIndex = 2;
        	this.udDLFogBStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLFogBStart.Value = new decimal(new int[] {
        	        	        	5,
        	        	        	0,
        	        	        	0,
        	        	        	-2147418112});
        	this.udDLFogBStart.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
        	// 
        	// udDLFogAEnd
        	// 
        	this.udDLFogAEnd.DecimalPlaces = 1;
        	this.udDLFogAEnd.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogAEnd.Location = new System.Drawing.Point(198, 30);
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
        	this.udDLFogAEnd.Size = new System.Drawing.Size(50, 20);
        	this.udDLFogAEnd.TabIndex = 1;
        	this.udDLFogAEnd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLFogAEnd.Value = new decimal(new int[] {
        	        	        	5,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLFogAEnd.ValueChanged += new System.EventHandler(this.udDLFogAEnd_ValueChanged);
        	// 
        	// udDLFogAStart
        	// 
        	this.udDLFogAStart.DecimalPlaces = 1;
        	this.udDLFogAStart.Increment = new decimal(new int[] {
        	        	        	1,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogAStart.Location = new System.Drawing.Point(140, 30);
        	this.udDLFogAStart.Maximum = new decimal(new int[] {
        	        	        	2999,
        	        	        	0,
        	        	        	0,
        	        	        	65536});
        	this.udDLFogAStart.Name = "udDLFogAStart";
        	this.udDLFogAStart.Size = new System.Drawing.Size(50, 20);
        	this.udDLFogAStart.TabIndex = 0;
        	this.udDLFogAStart.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udDLFogAStart.Value = new decimal(new int[] {
        	        	        	2,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udDLFogAStart.ValueChanged += new System.EventHandler(this.ValidateDLSettings);
        	// 
        	// lDLFogB
        	// 
        	this.lDLFogB.Location = new System.Drawing.Point(20, 54);
        	this.lDLFogB.Name = "lDLFogB";
        	this.lDLFogB.Size = new System.Drawing.Size(118, 19);
        	this.lDLFogB.TabIndex = 0;
        	this.lDLFogB.Text = "Below Water Fog";
        	this.lDLFogB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// lDLFogA
        	// 
        	this.lDLFogA.Location = new System.Drawing.Point(22, 30);
        	this.lDLFogA.Name = "lDLFogA";
        	this.lDLFogA.Size = new System.Drawing.Size(116, 19);
        	this.lDLFogA.TabIndex = 0;
        	this.lDLFogA.Text = "Above Water Fog";
        	this.lDLFogA.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
        	// 
        	// lDLFogStart
        	// 
        	this.lDLFogStart.AutoSize = true;
        	this.lDLFogStart.Location = new System.Drawing.Point(137, 16);
        	this.lDLFogStart.Name = "lDLFogStart";
        	this.lDLFogStart.Size = new System.Drawing.Size(29, 13);
        	this.lDLFogStart.TabIndex = 0;
        	this.lDLFogStart.Text = "Start";
        	// 
        	// lDLFogEnd
        	// 
        	this.lDLFogEnd.AutoSize = true;
        	this.lDLFogEnd.Location = new System.Drawing.Point(195, 16);
        	this.lDLFogEnd.Name = "lDLFogEnd";
        	this.lDLFogEnd.Size = new System.Drawing.Size(26, 13);
        	this.lDLFogEnd.TabIndex = 0;
        	this.lDLFogEnd.Text = "End";
        	// 
        	// tpConfig
        	// 
        	this.tpConfig.Controls.Add(this.gbMainUI);
        	this.tpConfig.Controls.Add(this.gbMainInfo);
        	this.tpConfig.Controls.Add(this.gbMainSettings);
        	this.tpConfig.Location = new System.Drawing.Point(4, 21);
        	this.tpConfig.Name = "tpConfig";
        	this.tpConfig.Size = new System.Drawing.Size(578, 420);
        	this.tpConfig.TabIndex = 0;
        	this.tpConfig.Text = "Config";
        	this.tpConfig.ToolTipText = "Load/save all MGE settings.";
        	this.tpConfig.UseVisualStyleBackColor = true;
        	// 
        	// gbMainUI
        	// 
        	this.gbMainUI.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.gbMainUI.Controls.Add(this.pLanguage);
        	this.gbMainUI.Controls.Add(this.cmbTipReadSpd);
        	this.gbMainUI.Controls.Add(this.lTipReadSpd);
        	this.gbMainUI.Controls.Add(this.lTipRSpdUnit);
        	this.gbMainUI.Location = new System.Drawing.Point(8, 336);
        	this.gbMainUI.Name = "gbMainUI";
        	this.gbMainUI.Size = new System.Drawing.Size(562, 76);
        	this.gbMainUI.TabIndex = 2;
        	this.gbMainUI.TabStop = false;
        	this.gbMainUI.Text = "User Interface";
        	// 
        	// pLanguage
        	// 
        	this.pLanguage.Controls.Add(this.cmbUILanguage);
        	this.pLanguage.Controls.Add(this.cbUILangAuto);
        	this.pLanguage.Controls.Add(this.lUILanguage);
        	this.pLanguage.Location = new System.Drawing.Point(8, 25);
        	this.pLanguage.Name = "pLanguage";
        	this.pLanguage.Size = new System.Drawing.Size(156, 37);
        	this.pLanguage.TabIndex = 0;
        	// 
        	// cmbUILanguage
        	// 
        	this.cmbUILanguage.FormattingEnabled = true;
        	this.cmbUILanguage.Location = new System.Drawing.Point(0, 16);
        	this.cmbUILanguage.Name = "cmbUILanguage";
        	this.cmbUILanguage.Size = new System.Drawing.Size(156, 21);
        	this.cmbUILanguage.TabIndex = 1;
        	this.cmbUILanguage.SelectedIndexChanged += new System.EventHandler(this.cmbUILanguage_SelectedIndexChanged);
        	this.cmbUILanguage.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
        	// 
        	// cbUILangAuto
        	// 
        	this.cbUILangAuto.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.cbUILangAuto.AutoSize = true;
        	this.cbUILangAuto.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
        	this.cbUILangAuto.Location = new System.Drawing.Point(78, -1);
        	this.cbUILangAuto.Name = "cbUILangAuto";
        	this.cbUILangAuto.Size = new System.Drawing.Size(78, 17);
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
        	this.lUILanguage.Size = new System.Drawing.Size(55, 13);
        	this.lUILanguage.TabIndex = 0;
        	this.lUILanguage.Text = "Language";
        	// 
        	// cmbTipReadSpd
        	// 
        	this.cmbTipReadSpd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
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
        	this.cmbTipReadSpd.Location = new System.Drawing.Point(398, 41);
        	this.cmbTipReadSpd.Name = "cmbTipReadSpd";
        	this.cmbTipReadSpd.Size = new System.Drawing.Size(48, 21);
        	this.cmbTipReadSpd.TabIndex = 2;
        	this.cmbTipReadSpd.Text = "15";
        	this.cmbTipReadSpd.SelectedIndexChanged += new System.EventHandler(this.cmbMainTipReadSpd_SelectedIndexChanged);
        	this.cmbTipReadSpd.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKey);
        	// 
        	// lTipReadSpd
        	// 
        	this.lTipReadSpd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.lTipReadSpd.AutoSize = true;
        	this.lTipReadSpd.Location = new System.Drawing.Point(395, 25);
        	this.lTipReadSpd.Name = "lTipReadSpd";
        	this.lTipReadSpd.Size = new System.Drawing.Size(109, 13);
        	this.lTipReadSpd.TabIndex = 0;
        	this.lTipReadSpd.Text = "Tooltip reading speed";
        	// 
        	// lTipRSpdUnit
        	// 
        	this.lTipRSpdUnit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.lTipRSpdUnit.AutoSize = true;
        	this.lTipRSpdUnit.Location = new System.Drawing.Point(449, 44);
        	this.lTipRSpdUnit.Name = "lTipRSpdUnit";
        	this.lTipRSpdUnit.Size = new System.Drawing.Size(58, 13);
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
        	this.gbMainInfo.Size = new System.Drawing.Size(562, 50);
        	this.gbMainInfo.TabIndex = 0;
        	this.gbMainInfo.TabStop = false;
        	this.gbMainInfo.Text = "Information";
        	// 
        	// bViewCaps
        	// 
        	this.bViewCaps.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
        	this.bViewCaps.Location = new System.Drawing.Point(6, 18);
        	this.bViewCaps.Name = "bViewCaps";
        	this.bViewCaps.Size = new System.Drawing.Size(160, 25);
        	this.bViewCaps.TabIndex = 0;
        	this.bViewCaps.Text = "Report max AA and AF";
        	this.bViewCaps.Click += new System.EventHandler(this.bViewCaps_Click);
        	// 
        	// bHelp
        	// 
        	this.bHelp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bHelp.Enabled = false;
        	this.bHelp.Location = new System.Drawing.Point(396, 18);
        	this.bHelp.Name = "bHelp";
        	this.bHelp.Size = new System.Drawing.Size(160, 25);
        	this.bHelp.TabIndex = 1;
        	this.bHelp.Text = "Help";
        	this.bHelp.Click += new System.EventHandler(this.bHelp_Click);
        	// 
        	// bAbout
        	// 
        	this.bAbout.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
        	this.bAbout.Location = new System.Drawing.Point(201, 18);
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
        	this.gbMainSettings.Location = new System.Drawing.Point(8, 64);
        	this.gbMainSettings.Name = "gbMainSettings";
        	this.gbMainSettings.Size = new System.Drawing.Size(562, 76);
        	this.gbMainSettings.TabIndex = 1;
        	this.gbMainSettings.TabStop = false;
        	this.gbMainSettings.Text = "Settings";
        	// 
        	// bResetSettings
        	// 
        	this.bResetSettings.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
        	this.bResetSettings.Location = new System.Drawing.Point(6, 44);
        	this.bResetSettings.Name = "bResetSettings";
        	this.bResetSettings.Size = new System.Drawing.Size(160, 25);
        	this.bResetSettings.TabIndex = 1;
        	this.bResetSettings.Text = "Reset settings";
        	this.bResetSettings.Click += new System.EventHandler(this.bResetSettings_Click);
        	// 
        	// bImport
        	// 
        	this.bImport.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
        	this.bImport.Enabled = false;
        	this.bImport.Location = new System.Drawing.Point(201, 44);
        	this.bImport.Name = "bImport";
        	this.bImport.Size = new System.Drawing.Size(160, 25);
        	this.bImport.TabIndex = 3;
        	this.bImport.Text = "Import settings";
        	this.bImport.Click += new System.EventHandler(this.bImport_Click);
        	// 
        	// bExport
        	// 
        	this.bExport.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bExport.Enabled = false;
        	this.bExport.Location = new System.Drawing.Point(396, 44);
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
        	this.cbClearINI.Location = new System.Drawing.Point(8, 24);
        	this.cbClearINI.Name = "cbClearINI";
        	this.cbClearINI.Size = new System.Drawing.Size(121, 17);
        	this.cbClearINI.TabIndex = 0;
        	this.cbClearINI.Text = "Clear saved settings";
        	this.cbClearINI.UseVisualStyleBackColor = true;
        	// 
        	// tpInstructions
        	// 
        	this.tpInstructions.Controls.Add(this.lInstructions);
        	this.tpInstructions.Location = new System.Drawing.Point(4, 21);
        	this.tpInstructions.Name = "tpInstructions";
        	this.tpInstructions.Size = new System.Drawing.Size(578, 420);
        	this.tpInstructions.TabIndex = 8;
        	this.tpInstructions.Text = "Instructions";
        	this.tpInstructions.ToolTipText = "A guide to setting up MGE XE.";
        	this.tpInstructions.UseVisualStyleBackColor = true;
        	// 
        	// lInstructions
        	// 
        	this.lInstructions.AutoSize = true;
        	this.lInstructions.Location = new System.Drawing.Point(18, 20);
        	this.lInstructions.Name = "lInstructions";
        	this.lInstructions.Size = new System.Drawing.Size(507, 364);
        	this.lInstructions.TabIndex = 0;
        	this.lInstructions.Text = resources.GetString("lInstructions.Text");
        	// 
        	// SShotFolderDialog
        	// 
        	this.SShotFolderDialog.Description = "Select output folder for screenshots taken in game:";
        	// 
        	// MainForm
        	// 
        	this.ClientSize = new System.Drawing.Size(586, 445);
        	this.Controls.Add(this.tabControl);
        	this.Icon = global::MGEgui.Properties.Resources.AppIcon;
        	this.MaximizeBox = false;
        	this.MinimumSize = new System.Drawing.Size(600, 478);
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
        	this.gbInputOpts.ResumeLayout(false);
        	this.gbInputOpts.PerformLayout();
        	this.tpGlobal.ResumeLayout(false);
        	this.gbSShot.ResumeLayout(false);
        	this.gbSShot.PerformLayout();
        	this.tableLayoutPanel1.ResumeLayout(false);
        	this.tableLayoutPanel1.PerformLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udSShotNum)).EndInit();
        	this.gbScene.ResumeLayout(false);
        	this.gbScene.PerformLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udFPSLimit)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udHDR)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udLOD)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udFOV)).EndInit();
        	this.gbDisplay.ResumeLayout(false);
        	this.gbDisplay.PerformLayout();
        	this.tableLayoutDisplay.ResumeLayout(false);
        	this.tableLayoutDisplay.PerformLayout();
        	this.tabControl.ResumeLayout(false);
        	this.tpDL.ResumeLayout(false);
        	this.tpDL.PerformLayout();
        	this.gbDistantLand.ResumeLayout(false);
        	this.gbDistantLand.PerformLayout();
        	this.pDLStatics.ResumeLayout(false);
        	this.pDLStatics.PerformLayout();
        	this.gbDLStatics.ResumeLayout(false);
        	this.gbDLStatics.PerformLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udDLDistVeryFar)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLDistFar)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLDistNear)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLSizeVeryFar)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLSizeFar)).EndInit();
        	this.gbDLAutoDist.ResumeLayout(false);
        	this.gbDLAutoDist.PerformLayout();
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
        	this.gbDLDrawDist.ResumeLayout(false);
        	((System.ComponentModel.ISupportInitialize)(this.udDLDrawDist)).EndInit();
        	this.gbDLFog.ResumeLayout(false);
        	this.gbDLFog.PerformLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogExpMul)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogIEnd)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogIStart)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogBEnd)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogBStart)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogAEnd)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udDLFogAStart)).EndInit();
        	this.tpConfig.ResumeLayout(false);
        	this.gbMainUI.ResumeLayout(false);
        	this.gbMainUI.PerformLayout();
        	this.pLanguage.ResumeLayout(false);
        	this.pLanguage.PerformLayout();
        	this.gbMainInfo.ResumeLayout(false);
        	this.gbMainSettings.ResumeLayout(false);
        	this.gbMainSettings.PerformLayout();
        	this.tpInstructions.ResumeLayout(false);
        	this.tpInstructions.PerformLayout();
        	this.ResumeLayout(false);
        }
        private System.Windows.Forms.Button bMWLightSettings;
        public System.Windows.Forms.CheckBox cbDLReflInterior;
        private System.Windows.Forms.TableLayoutPanel tableLayoutDisplay;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label lHDR2;
        private System.Windows.Forms.Button bMWLightingReset;
        private System.Windows.Forms.Label lInstructions;
        private System.Windows.Forms.TabPage tpInstructions;
        private System.Windows.Forms.Button bAutoFOV;
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
        public Label lHDR;
        public TabPage tpInput;
        public Button bRemapper;
        public CheckBox cbAltCombat;
        public CheckBox cbSkipMovie;
        public Button bMacroEd;
        public Label lLOD;
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
        public Button bCalcResolution;
        public Label lResolution;
        public CheckBox cbWindowed;
        public Button bCalcRefresh;
        public Label lRefreshRate;
        public ComboBox cmbRefreshRate;
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
        public NumericUpDown udLOD;
        public NumericUpDown udHDR;
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
        public Label lSShotNum;
        public NumericUpDown udSShotNum;
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
        private GroupBox gbDLWater;
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
        private GroupBox gbDLAutoDist;
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