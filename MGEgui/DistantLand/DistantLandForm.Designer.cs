namespace MGEgui.DistantLand {
    partial class DistantLandForm {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if(disposing && (components != null)) {
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
        	System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DistantLandForm));
        	this.backgroundWorker = new System.ComponentModel.BackgroundWorker();
        	this.statusBar = new System.Windows.Forms.StatusStrip();
        	this.statusProgress = new System.Windows.Forms.ToolStripProgressBar();
        	this.statusWarnings = new System.Windows.Forms.ToolStripSplitButton();
        	this.statusText = new System.Windows.Forms.ToolStripStatusLabel();
        	this.DudMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
        	this.tabControl = new System.Windows.Forms.TabControl();
        	this.tabPlugs = new System.Windows.Forms.TabPage();
        	this.lInstructions = new System.Windows.Forms.Label();
        	this.lPlugsModList = new System.Windows.Forms.Label();
        	this.clbPlugsModList = new System.Windows.Forms.CheckedListBox();
        	this.bPlugsFromINI = new System.Windows.Forms.Button();
        	this.bPlugsAll = new System.Windows.Forms.Button();
        	this.bPlugsClear = new System.Windows.Forms.Button();
        	this.bPlugsDirs = new System.Windows.Forms.Button();
        	this.gbPlugsSort = new System.Windows.Forms.GroupBox();
        	this.rbPlugsName = new System.Windows.Forms.RadioButton();
        	this.rbPlugsType = new System.Windows.Forms.RadioButton();
        	this.rbPlugsLoad = new System.Windows.Forms.RadioButton();
        	this.bPlugsRun = new System.Windows.Forms.Button();
        	this.tabTex = new System.Windows.Forms.TabPage();
        	this.lTexNormalMemUse = new System.Windows.Forms.Label();
        	this.lTexWorldMemUse = new System.Windows.Forms.Label();
        	this.lTexDesc = new System.Windows.Forms.Label();
        	this.cmbTexWorldResolution = new System.Windows.Forms.ComboBox();
        	this.lTexWorldResolution = new System.Windows.Forms.Label();
        	this.cmbTexWorldNormalRes = new System.Windows.Forms.ComboBox();
        	this.lTexWorldNormalRes = new System.Windows.Forms.Label();
        	this.lTexTwoStepDesc = new System.Windows.Forms.Label();
        	this.cbTexTwoStep = new System.Windows.Forms.CheckBox();
        	this.bTexSkip = new System.Windows.Forms.Button();
        	this.bTexRun = new System.Windows.Forms.Button();
        	this.tabMesh = new System.Windows.Forms.TabPage();
        	this.lMeshDesc = new System.Windows.Forms.Label();
        	this.cmbMeshWorldDetail = new System.Windows.Forms.ComboBox();
        	this.lMeshWorldDetail = new System.Windows.Forms.Label();
        	this.lMeshAutoInfo = new System.Windows.Forms.Label();
        	this.bMeshSkip = new System.Windows.Forms.Button();
        	this.bMeshRun = new System.Windows.Forms.Button();
        	this.tabStat = new System.Windows.Forms.TabPage();
        	this.lStatDesc = new System.Windows.Forms.Label();
        	this.udStatMinSize = new System.Windows.Forms.NumericUpDown();
        	this.lStatMinSize = new System.Windows.Forms.Label();
        	this.udStatGrassDensity = new System.Windows.Forms.NumericUpDown();
        	this.lStatGrassDensity = new System.Windows.Forms.Label();
        	this.cmbStatSimplifyMeshes = new System.Windows.Forms.ComboBox();
        	this.lStatSimplifyMeshes = new System.Windows.Forms.Label();
        	this.cmbStatSkipMipLevels = new System.Windows.Forms.ComboBox();
        	this.lStatSkipMipLevels = new System.Windows.Forms.Label();
        	this.lStatSkipMipDesc = new System.Windows.Forms.Label();
        	this.cbStatActivators = new System.Windows.Forms.CheckBox();
        	this.cbStatIncludeMisc = new System.Windows.Forms.CheckBox();
        	this.cbStatIntWater = new System.Windows.Forms.CheckBox();
        	this.bStatOverrideList = new System.Windows.Forms.Button();
        	this.lStatOverrideList = new System.Windows.Forms.Label();
        	this.lbStatOverrideList = new System.Windows.Forms.ListBox();
        	this.cbStatIntExt = new System.Windows.Forms.CheckBox();
        	this.bStatExportStatics = new System.Windows.Forms.Button();
        	this.bStatSkip = new System.Windows.Forms.Button();
        	this.bStatRun = new System.Windows.Forms.Button();
        	this.cbStatOverrideList = new System.Windows.Forms.CheckBox();
        	this.tabFinish = new System.Windows.Forms.TabPage();
        	this.lFinishDesc = new System.Windows.Forms.Label();
        	this.bFinish = new System.Windows.Forms.Button();
        	this.saveStaticListDialog = new System.Windows.Forms.SaveFileDialog();
        	this.statusBar.SuspendLayout();
        	this.tabControl.SuspendLayout();
        	this.tabPlugs.SuspendLayout();
        	this.gbPlugsSort.SuspendLayout();
        	this.tabTex.SuspendLayout();
        	this.tabMesh.SuspendLayout();
        	this.tabStat.SuspendLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udStatMinSize)).BeginInit();
        	((System.ComponentModel.ISupportInitialize)(this.udStatGrassDensity)).BeginInit();
        	this.tabFinish.SuspendLayout();
        	this.SuspendLayout();
        	// 
        	// backgroundWorker
        	// 
        	this.backgroundWorker.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.UpdateProgress);
        	// 
        	// statusBar
        	// 
        	this.statusBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
        	        	        	this.statusProgress,
        	        	        	this.statusWarnings,
        	        	        	this.statusText});
        	this.statusBar.Location = new System.Drawing.Point(0, 299);
        	this.statusBar.Name = "statusBar";
        	this.statusBar.Size = new System.Drawing.Size(472, 22);
        	this.statusBar.TabIndex = 0;
        	this.statusBar.Text = "statusStrip1";
        	// 
        	// statusProgress
        	// 
        	this.statusProgress.Name = "statusProgress";
        	this.statusProgress.Size = new System.Drawing.Size(100, 16);
        	// 
        	// statusWarnings
        	// 
        	this.statusWarnings.Enabled = false;
        	this.statusWarnings.ForeColor = System.Drawing.Color.Red;
        	this.statusWarnings.Image = ((System.Drawing.Image)(resources.GetObject("statusWarnings.Image")));
        	this.statusWarnings.ImageTransparentColor = System.Drawing.Color.Transparent;
        	this.statusWarnings.Name = "statusWarnings";
        	this.statusWarnings.Size = new System.Drawing.Size(82, 20);
        	this.statusWarnings.Text = "Warnings";
        	this.statusWarnings.ToolTipText = "View warnings from last setup step";
        	this.statusWarnings.ButtonClick += new System.EventHandler(this.statusWarnings_ButtonClick);
        	// 
        	// statusText
        	// 
        	this.statusText.Name = "statusText";
        	this.statusText.Size = new System.Drawing.Size(0, 17);
        	// 
        	// DudMenu
        	// 
        	this.DudMenu.Name = "DudMenu";
        	this.DudMenu.Size = new System.Drawing.Size(61, 4);
        	// 
        	// tabControl
        	// 
        	this.tabControl.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
        	this.tabControl.Controls.Add(this.tabPlugs);
        	this.tabControl.Controls.Add(this.tabTex);
        	this.tabControl.Controls.Add(this.tabMesh);
        	this.tabControl.Controls.Add(this.tabStat);
        	this.tabControl.Controls.Add(this.tabFinish);
        	this.tabControl.Dock = System.Windows.Forms.DockStyle.Fill;
        	this.tabControl.Location = new System.Drawing.Point(0, 0);
        	this.tabControl.Name = "tabControl";
        	this.tabControl.SelectedIndex = 0;
        	this.tabControl.Size = new System.Drawing.Size(472, 299);
        	this.tabControl.TabIndex = 1;
        	this.tabControl.Selecting += new System.Windows.Forms.TabControlCancelEventHandler(this.tabControl_Selecting);
        	// 
        	// tabPlugs
        	// 
        	this.tabPlugs.Controls.Add(this.lInstructions);
        	this.tabPlugs.Controls.Add(this.lPlugsModList);
        	this.tabPlugs.Controls.Add(this.clbPlugsModList);
        	this.tabPlugs.Controls.Add(this.bPlugsFromINI);
        	this.tabPlugs.Controls.Add(this.bPlugsAll);
        	this.tabPlugs.Controls.Add(this.bPlugsClear);
        	this.tabPlugs.Controls.Add(this.bPlugsDirs);
        	this.tabPlugs.Controls.Add(this.gbPlugsSort);
        	this.tabPlugs.Controls.Add(this.bPlugsRun);
        	this.tabPlugs.Location = new System.Drawing.Point(4, 25);
        	this.tabPlugs.Name = "tabPlugs";
        	this.tabPlugs.Padding = new System.Windows.Forms.Padding(3);
        	this.tabPlugs.Size = new System.Drawing.Size(464, 270);
        	this.tabPlugs.TabIndex = 0;
        	this.tabPlugs.Text = "Plugins";
        	this.tabPlugs.UseVisualStyleBackColor = true;
        	// 
        	// lInstructions
        	// 
        	this.lInstructions.AutoSize = true;
        	this.lInstructions.Location = new System.Drawing.Point(6, 251);
        	this.lInstructions.Name = "lInstructions";
        	this.lInstructions.Size = new System.Drawing.Size(308, 13);
        	this.lInstructions.TabIndex = 7;
        	this.lInstructions.Text = "Standard usage: Click \"Use current load order\" then \"Continue\"";
        	// 
        	// lPlugsModList
        	// 
        	this.lPlugsModList.AutoSize = true;
        	this.lPlugsModList.Location = new System.Drawing.Point(3, 5);
        	this.lPlugsModList.Name = "lPlugsModList";
        	this.lPlugsModList.Size = new System.Drawing.Size(202, 13);
        	this.lPlugsModList.TabIndex = 0;
        	this.lPlugsModList.Text = "Select plugins to use in distant land setup";
        	// 
        	// clbPlugsModList
        	// 
        	this.clbPlugsModList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
        	        	        	| System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.clbPlugsModList.ContextMenuStrip = this.DudMenu;
        	this.clbPlugsModList.FormattingEnabled = true;
        	this.clbPlugsModList.IntegralHeight = false;
        	this.clbPlugsModList.Location = new System.Drawing.Point(6, 25);
        	this.clbPlugsModList.Name = "clbPlugsModList";
        	this.clbPlugsModList.Size = new System.Drawing.Size(319, 215);
        	this.clbPlugsModList.TabIndex = 0;
        	this.clbPlugsModList.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.clbPlugsModList_ItemCheck);
        	// 
        	// bPlugsFromINI
        	// 
        	this.bPlugsFromINI.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bPlugsFromINI.Location = new System.Drawing.Point(331, 217);
        	this.bPlugsFromINI.Name = "bPlugsFromINI";
        	this.bPlugsFromINI.Size = new System.Drawing.Size(125, 23);
        	this.bPlugsFromINI.TabIndex = 1;
        	this.bPlugsFromINI.Text = "Use current load order";
        	this.bPlugsFromINI.UseVisualStyleBackColor = true;
        	this.bPlugsFromINI.Click += new System.EventHandler(this.bPlugsFromINI_Click);
        	// 
        	// bPlugsAll
        	// 
        	this.bPlugsAll.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bPlugsAll.Location = new System.Drawing.Point(331, 25);
        	this.bPlugsAll.Name = "bPlugsAll";
        	this.bPlugsAll.Size = new System.Drawing.Size(125, 23);
        	this.bPlugsAll.TabIndex = 2;
        	this.bPlugsAll.Text = "Select all";
        	this.bPlugsAll.UseVisualStyleBackColor = true;
        	this.bPlugsAll.Click += new System.EventHandler(this.bPlugsAll_Click);
        	// 
        	// bPlugsClear
        	// 
        	this.bPlugsClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bPlugsClear.Location = new System.Drawing.Point(331, 54);
        	this.bPlugsClear.Name = "bPlugsClear";
        	this.bPlugsClear.Size = new System.Drawing.Size(125, 23);
        	this.bPlugsClear.TabIndex = 3;
        	this.bPlugsClear.Text = "Clear selected";
        	this.bPlugsClear.UseVisualStyleBackColor = true;
        	this.bPlugsClear.Click += new System.EventHandler(this.bPlugsClear_Click);
        	// 
        	// bPlugsDirs
        	// 
        	this.bPlugsDirs.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bPlugsDirs.Location = new System.Drawing.Point(331, 83);
        	this.bPlugsDirs.Name = "bPlugsDirs";
        	this.bPlugsDirs.Size = new System.Drawing.Size(125, 23);
        	this.bPlugsDirs.TabIndex = 4;
        	this.bPlugsDirs.Text = "Plugin directories...";
        	this.bPlugsDirs.UseVisualStyleBackColor = true;
        	this.bPlugsDirs.Click += new System.EventHandler(this.bPlugsDirs_Click);
        	// 
        	// gbPlugsSort
        	// 
        	this.gbPlugsSort.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.gbPlugsSort.Controls.Add(this.rbPlugsName);
        	this.gbPlugsSort.Controls.Add(this.rbPlugsType);
        	this.gbPlugsSort.Controls.Add(this.rbPlugsLoad);
        	this.gbPlugsSort.Location = new System.Drawing.Point(331, 112);
        	this.gbPlugsSort.Name = "gbPlugsSort";
        	this.gbPlugsSort.Size = new System.Drawing.Size(125, 89);
        	this.gbPlugsSort.TabIndex = 5;
        	this.gbPlugsSort.TabStop = false;
        	this.gbPlugsSort.Text = "Sort view:";
        	// 
        	// rbPlugsName
        	// 
        	this.rbPlugsName.AutoSize = true;
        	this.rbPlugsName.Location = new System.Drawing.Point(6, 19);
        	this.rbPlugsName.Name = "rbPlugsName";
        	this.rbPlugsName.Size = new System.Drawing.Size(65, 17);
        	this.rbPlugsName.TabIndex = 0;
        	this.rbPlugsName.Text = "by name";
        	this.rbPlugsName.UseVisualStyleBackColor = true;
        	this.rbPlugsName.CheckedChanged += new System.EventHandler(this.pluginsSort);
        	// 
        	// rbPlugsType
        	// 
        	this.rbPlugsType.AutoSize = true;
        	this.rbPlugsType.Location = new System.Drawing.Point(6, 42);
        	this.rbPlugsType.Name = "rbPlugsType";
        	this.rbPlugsType.Size = new System.Drawing.Size(59, 17);
        	this.rbPlugsType.TabIndex = 1;
        	this.rbPlugsType.TabStop = true;
        	this.rbPlugsType.Text = "by type";
        	this.rbPlugsType.UseVisualStyleBackColor = true;
        	this.rbPlugsType.CheckedChanged += new System.EventHandler(this.pluginsSort);
        	// 
        	// rbPlugsLoad
        	// 
        	this.rbPlugsLoad.AutoSize = true;
        	this.rbPlugsLoad.Location = new System.Drawing.Point(6, 65);
        	this.rbPlugsLoad.Name = "rbPlugsLoad";
        	this.rbPlugsLoad.Size = new System.Drawing.Size(86, 17);
        	this.rbPlugsLoad.TabIndex = 2;
        	this.rbPlugsLoad.Text = "by load order";
        	this.rbPlugsLoad.UseVisualStyleBackColor = true;
        	this.rbPlugsLoad.CheckedChanged += new System.EventHandler(this.pluginsSort);
        	// 
        	// bPlugsRun
        	// 
        	this.bPlugsRun.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bPlugsRun.Enabled = false;
        	this.bPlugsRun.Location = new System.Drawing.Point(331, 246);
        	this.bPlugsRun.Name = "bPlugsRun";
        	this.bPlugsRun.Size = new System.Drawing.Size(125, 23);
        	this.bPlugsRun.TabIndex = 6;
        	this.bPlugsRun.Text = "Continue";
        	this.bPlugsRun.UseVisualStyleBackColor = true;
        	this.bPlugsRun.Click += new System.EventHandler(this.bPlugsRun_Click);
        	// 
        	// tabTex
        	// 
        	this.tabTex.Controls.Add(this.lTexNormalMemUse);
        	this.tabTex.Controls.Add(this.lTexWorldMemUse);
        	this.tabTex.Controls.Add(this.lTexDesc);
        	this.tabTex.Controls.Add(this.cmbTexWorldResolution);
        	this.tabTex.Controls.Add(this.lTexWorldResolution);
        	this.tabTex.Controls.Add(this.cmbTexWorldNormalRes);
        	this.tabTex.Controls.Add(this.lTexWorldNormalRes);
        	this.tabTex.Controls.Add(this.lTexTwoStepDesc);
        	this.tabTex.Controls.Add(this.cbTexTwoStep);
        	this.tabTex.Controls.Add(this.bTexSkip);
        	this.tabTex.Controls.Add(this.bTexRun);
        	this.tabTex.Location = new System.Drawing.Point(4, 25);
        	this.tabTex.Name = "tabTex";
        	this.tabTex.Padding = new System.Windows.Forms.Padding(3);
        	this.tabTex.Size = new System.Drawing.Size(464, 270);
        	this.tabTex.TabIndex = 1;
        	this.tabTex.Text = "Land Textures";
        	this.tabTex.UseVisualStyleBackColor = true;
        	// 
        	// lTexNormalMemUse
        	// 
        	this.lTexNormalMemUse.AutoSize = true;
        	this.lTexNormalMemUse.Location = new System.Drawing.Point(273, 77);
        	this.lTexNormalMemUse.Name = "lTexNormalMemUse";
        	this.lTexNormalMemUse.Size = new System.Drawing.Size(73, 13);
        	this.lTexNormalMemUse.TabIndex = 6;
        	this.lTexNormalMemUse.Text = "VRAM usage:";
        	// 
        	// lTexWorldMemUse
        	// 
        	this.lTexWorldMemUse.AutoSize = true;
        	this.lTexWorldMemUse.Location = new System.Drawing.Point(273, 41);
        	this.lTexWorldMemUse.Name = "lTexWorldMemUse";
        	this.lTexWorldMemUse.Size = new System.Drawing.Size(73, 13);
        	this.lTexWorldMemUse.TabIndex = 5;
        	this.lTexWorldMemUse.Text = "VRAM usage:";
        	// 
        	// lTexDesc
        	// 
        	this.lTexDesc.AutoSize = true;
        	this.lTexDesc.Location = new System.Drawing.Point(8, 3);
        	this.lTexDesc.Name = "lTexDesc";
        	this.lTexDesc.Size = new System.Drawing.Size(305, 26);
        	this.lTexDesc.TabIndex = 0;
        	this.lTexDesc.Text = "Higher resolutions look better at the expense of a greater fps hit\r\nMaximum textu" +
        	"re size:  ";
        	// 
        	// cmbTexWorldResolution
        	// 
        	this.cmbTexWorldResolution.ContextMenuStrip = this.DudMenu;
        	this.cmbTexWorldResolution.FormattingEnabled = true;
        	this.cmbTexWorldResolution.Items.AddRange(new object[] {
        	        	        	"128",
        	        	        	"256",
        	        	        	"512",
        	        	        	"1024",
        	        	        	"2048",
        	        	        	"4096"});
        	this.cmbTexWorldResolution.Location = new System.Drawing.Point(11, 38);
        	this.cmbTexWorldResolution.Name = "cmbTexWorldResolution";
        	this.cmbTexWorldResolution.Size = new System.Drawing.Size(100, 21);
        	this.cmbTexWorldResolution.TabIndex = 0;
        	this.cmbTexWorldResolution.SelectedIndexChanged += new System.EventHandler(this.cmbTexWorldResolution_SelectedIndexChanged);
        	this.cmbTexWorldResolution.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKeyPress);
        	// 
        	// lTexWorldResolution
        	// 
        	this.lTexWorldResolution.AutoSize = true;
        	this.lTexWorldResolution.Location = new System.Drawing.Point(117, 41);
        	this.lTexWorldResolution.Name = "lTexWorldResolution";
        	this.lTexWorldResolution.Size = new System.Drawing.Size(118, 13);
        	this.lTexWorldResolution.TabIndex = 0;
        	this.lTexWorldResolution.Text = "World texture resolution";
        	// 
        	// cmbTexWorldNormalRes
        	// 
        	this.cmbTexWorldNormalRes.ContextMenuStrip = this.DudMenu;
        	this.cmbTexWorldNormalRes.FormattingEnabled = true;
        	this.cmbTexWorldNormalRes.Items.AddRange(new object[] {
        	        	        	"128",
        	        	        	"256",
        	        	        	"512",
        	        	        	"1024",
        	        	        	"2048",
        	        	        	"4096"});
        	this.cmbTexWorldNormalRes.Location = new System.Drawing.Point(11, 74);
        	this.cmbTexWorldNormalRes.Name = "cmbTexWorldNormalRes";
        	this.cmbTexWorldNormalRes.Size = new System.Drawing.Size(100, 21);
        	this.cmbTexWorldNormalRes.TabIndex = 1;
        	this.cmbTexWorldNormalRes.SelectedIndexChanged += new System.EventHandler(this.cmbTexWorldNormalRes_SelectedIndexChanged);
        	this.cmbTexWorldNormalRes.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKeyPress);
        	// 
        	// lTexWorldNormalRes
        	// 
        	this.lTexWorldNormalRes.AutoSize = true;
        	this.lTexWorldNormalRes.Location = new System.Drawing.Point(117, 77);
        	this.lTexWorldNormalRes.Name = "lTexWorldNormalRes";
        	this.lTexWorldNormalRes.Size = new System.Drawing.Size(137, 13);
        	this.lTexWorldNormalRes.TabIndex = 0;
        	this.lTexWorldNormalRes.Text = "World normalmap resolution";
        	// 
        	// lTexTwoStepDesc
        	// 
        	this.lTexTwoStepDesc.AutoSize = true;
        	this.lTexTwoStepDesc.Location = new System.Drawing.Point(8, 122);
        	this.lTexTwoStepDesc.Name = "lTexTwoStepDesc";
        	this.lTexTwoStepDesc.Size = new System.Drawing.Size(385, 13);
        	this.lTexTwoStepDesc.TabIndex = 0;
        	this.lTexTwoStepDesc.Text = "Check this option to reduce vram consumption when creating very large textures";
        	// 
        	// cbTexTwoStep
        	// 
        	this.cbTexTwoStep.AutoSize = true;
        	this.cbTexTwoStep.Location = new System.Drawing.Point(11, 142);
        	this.cbTexTwoStep.Name = "cbTexTwoStep";
        	this.cbTexTwoStep.Size = new System.Drawing.Size(179, 17);
        	this.cbTexTwoStep.TabIndex = 2;
        	this.cbTexTwoStep.Text = "Create world texture in two steps";
        	this.cbTexTwoStep.UseVisualStyleBackColor = true;
        	// 
        	// bTexSkip
        	// 
        	this.bTexSkip.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bTexSkip.Enabled = false;
        	this.bTexSkip.Location = new System.Drawing.Point(331, 217);
        	this.bTexSkip.Name = "bTexSkip";
        	this.bTexSkip.Size = new System.Drawing.Size(125, 23);
        	this.bTexSkip.TabIndex = 3;
        	this.bTexSkip.Text = "Skip Texture Creation";
        	this.bTexSkip.UseVisualStyleBackColor = true;
        	this.bTexSkip.Click += new System.EventHandler(this.bTexSkip_Click);
        	// 
        	// bTexRun
        	// 
        	this.bTexRun.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bTexRun.Enabled = false;
        	this.bTexRun.Location = new System.Drawing.Point(331, 246);
        	this.bTexRun.Name = "bTexRun";
        	this.bTexRun.Size = new System.Drawing.Size(125, 23);
        	this.bTexRun.TabIndex = 4;
        	this.bTexRun.Text = "Create Land Textures";
        	this.bTexRun.UseVisualStyleBackColor = true;
        	this.bTexRun.Click += new System.EventHandler(this.bTexRun_Click);
        	// 
        	// tabMesh
        	// 
        	this.tabMesh.Controls.Add(this.lMeshDesc);
        	this.tabMesh.Controls.Add(this.cmbMeshWorldDetail);
        	this.tabMesh.Controls.Add(this.lMeshWorldDetail);
        	this.tabMesh.Controls.Add(this.lMeshAutoInfo);
        	this.tabMesh.Controls.Add(this.bMeshSkip);
        	this.tabMesh.Controls.Add(this.bMeshRun);
        	this.tabMesh.Location = new System.Drawing.Point(4, 25);
        	this.tabMesh.Name = "tabMesh";
        	this.tabMesh.Size = new System.Drawing.Size(464, 270);
        	this.tabMesh.TabIndex = 2;
        	this.tabMesh.Text = "Land Meshes";
        	this.tabMesh.UseVisualStyleBackColor = true;
        	// 
        	// lMeshDesc
        	// 
        	this.lMeshDesc.AutoSize = true;
        	this.lMeshDesc.Location = new System.Drawing.Point(8, 3);
        	this.lMeshDesc.Name = "lMeshDesc";
        	this.lMeshDesc.Size = new System.Drawing.Size(288, 13);
        	this.lMeshDesc.TabIndex = 0;
        	this.lMeshDesc.Text = "Higher detail looks better at the expense of a greater fps hit.";
        	// 
        	// cmbMeshWorldDetail
        	// 
        	this.cmbMeshWorldDetail.ContextMenuStrip = this.DudMenu;
        	this.cmbMeshWorldDetail.FormattingEnabled = true;
        	this.cmbMeshWorldDetail.Items.AddRange(new object[] {
        	        	        	"Ultra High",
        	        	        	"Very High",
        	        	        	"High",
        	        	        	"Medium",
        	        	        	"Low"});
        	this.cmbMeshWorldDetail.Location = new System.Drawing.Point(11, 38);
        	this.cmbMeshWorldDetail.Name = "cmbMeshWorldDetail";
        	this.cmbMeshWorldDetail.Size = new System.Drawing.Size(100, 21);
        	this.cmbMeshWorldDetail.TabIndex = 0;
        	this.cmbMeshWorldDetail.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKeyPress);
        	// 
        	// lMeshWorldDetail
        	// 
        	this.lMeshWorldDetail.AutoSize = true;
        	this.lMeshWorldDetail.Location = new System.Drawing.Point(117, 41);
        	this.lMeshWorldDetail.Name = "lMeshWorldDetail";
        	this.lMeshWorldDetail.Size = new System.Drawing.Size(91, 13);
        	this.lMeshWorldDetail.TabIndex = 0;
        	this.lMeshWorldDetail.Text = "World mesh detail";
        	// 
        	// lMeshAutoInfo
        	// 
        	this.lMeshAutoInfo.Location = new System.Drawing.Point(8, 83);
        	this.lMeshAutoInfo.Name = "lMeshAutoInfo";
        	this.lMeshAutoInfo.Size = new System.Drawing.Size(448, 48);
        	this.lMeshAutoInfo.TabIndex = 0;
        	this.lMeshAutoInfo.Text = resources.GetString("lMeshAutoInfo.Text");
        	// 
        	// bMeshSkip
        	// 
        	this.bMeshSkip.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bMeshSkip.Enabled = false;
        	this.bMeshSkip.Location = new System.Drawing.Point(331, 217);
        	this.bMeshSkip.Name = "bMeshSkip";
        	this.bMeshSkip.Size = new System.Drawing.Size(125, 23);
        	this.bMeshSkip.TabIndex = 1;
        	this.bMeshSkip.Text = "Skip Mesh Creation";
        	this.bMeshSkip.UseVisualStyleBackColor = true;
        	this.bMeshSkip.Click += new System.EventHandler(this.bMeshSkip_Click);
        	// 
        	// bMeshRun
        	// 
        	this.bMeshRun.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bMeshRun.Enabled = false;
        	this.bMeshRun.Location = new System.Drawing.Point(331, 246);
        	this.bMeshRun.Name = "bMeshRun";
        	this.bMeshRun.Size = new System.Drawing.Size(125, 23);
        	this.bMeshRun.TabIndex = 2;
        	this.bMeshRun.Text = "Create Land Meshes";
        	this.bMeshRun.UseVisualStyleBackColor = true;
        	this.bMeshRun.Click += new System.EventHandler(this.bMeshRun_Click);
        	// 
        	// tabStat
        	// 
        	this.tabStat.Controls.Add(this.lStatDesc);
        	this.tabStat.Controls.Add(this.udStatMinSize);
        	this.tabStat.Controls.Add(this.lStatMinSize);
        	this.tabStat.Controls.Add(this.udStatGrassDensity);
        	this.tabStat.Controls.Add(this.lStatGrassDensity);
        	this.tabStat.Controls.Add(this.cmbStatSimplifyMeshes);
        	this.tabStat.Controls.Add(this.lStatSimplifyMeshes);
        	this.tabStat.Controls.Add(this.cmbStatSkipMipLevels);
        	this.tabStat.Controls.Add(this.lStatSkipMipLevels);
        	this.tabStat.Controls.Add(this.lStatSkipMipDesc);
        	this.tabStat.Controls.Add(this.cbStatActivators);
        	this.tabStat.Controls.Add(this.cbStatIncludeMisc);
        	this.tabStat.Controls.Add(this.cbStatIntWater);
        	this.tabStat.Controls.Add(this.bStatOverrideList);
        	this.tabStat.Controls.Add(this.lStatOverrideList);
        	this.tabStat.Controls.Add(this.lbStatOverrideList);
        	this.tabStat.Controls.Add(this.cbStatIntExt);
        	this.tabStat.Controls.Add(this.bStatExportStatics);
        	this.tabStat.Controls.Add(this.bStatSkip);
        	this.tabStat.Controls.Add(this.bStatRun);
        	this.tabStat.Controls.Add(this.cbStatOverrideList);
        	this.tabStat.Location = new System.Drawing.Point(4, 25);
        	this.tabStat.Name = "tabStat";
        	this.tabStat.Size = new System.Drawing.Size(464, 270);
        	this.tabStat.TabIndex = 3;
        	this.tabStat.Text = "Statics";
        	this.tabStat.UseVisualStyleBackColor = true;
        	// 
        	// lStatDesc
        	// 
        	this.lStatDesc.AutoSize = true;
        	this.lStatDesc.Location = new System.Drawing.Point(5, 8);
        	this.lStatDesc.Name = "lStatDesc";
        	this.lStatDesc.Size = new System.Drawing.Size(386, 26);
        	this.lStatDesc.TabIndex = 0;
        	this.lStatDesc.Text = "The static size represents the minimum size of a mesh in ingame Morrowind units.\r" +
        	"\nSmaller numbers increase the number of statics drawn.";
        	// 
        	// udStatMinSize
        	// 
        	this.udStatMinSize.Increment = new decimal(new int[] {
        	        	        	10,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udStatMinSize.Location = new System.Drawing.Point(8, 44);
        	this.udStatMinSize.Maximum = new decimal(new int[] {
        	        	        	9999,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udStatMinSize.Name = "udStatMinSize";
        	this.udStatMinSize.Size = new System.Drawing.Size(48, 20);
        	this.udStatMinSize.TabIndex = 1;
        	this.udStatMinSize.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udStatMinSize.Value = new decimal(new int[] {
        	        	        	150,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	// 
        	// lStatMinSize
        	// 
        	this.lStatMinSize.AutoSize = true;
        	this.lStatMinSize.Location = new System.Drawing.Point(62, 46);
        	this.lStatMinSize.Name = "lStatMinSize";
        	this.lStatMinSize.Size = new System.Drawing.Size(97, 13);
        	this.lStatMinSize.TabIndex = 0;
        	this.lStatMinSize.Text = "Minimum static size";
        	// 
        	// udStatGrassDensity
        	// 
        	this.udStatGrassDensity.Increment = new decimal(new int[] {
        	        	        	5,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	this.udStatGrassDensity.Location = new System.Drawing.Point(8, 70);
        	this.udStatGrassDensity.Name = "udStatGrassDensity";
        	this.udStatGrassDensity.Size = new System.Drawing.Size(48, 20);
        	this.udStatGrassDensity.TabIndex = 1;
        	this.udStatGrassDensity.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
        	this.udStatGrassDensity.Value = new decimal(new int[] {
        	        	        	100,
        	        	        	0,
        	        	        	0,
        	        	        	0});
        	// 
        	// lStatGrassDensity
        	// 
        	this.lStatGrassDensity.AutoSize = true;
        	this.lStatGrassDensity.Location = new System.Drawing.Point(61, 72);
        	this.lStatGrassDensity.Name = "lStatGrassDensity";
        	this.lStatGrassDensity.Size = new System.Drawing.Size(109, 13);
        	this.lStatGrassDensity.TabIndex = 0;
        	this.lStatGrassDensity.Text = "Grass density percent";
        	// 
        	// cmbStatSimplifyMeshes
        	// 
        	this.cmbStatSimplifyMeshes.ContextMenuStrip = this.DudMenu;
        	this.cmbStatSimplifyMeshes.FormattingEnabled = true;
        	this.cmbStatSimplifyMeshes.Items.AddRange(new object[] {
        	        	        	"Full",
        	        	        	"90%",
        	        	        	"75%",
        	        	        	"50%",
        	        	        	"25%"});
        	this.cmbStatSimplifyMeshes.Location = new System.Drawing.Point(8, 96);
        	this.cmbStatSimplifyMeshes.Name = "cmbStatSimplifyMeshes";
        	this.cmbStatSimplifyMeshes.Size = new System.Drawing.Size(48, 21);
        	this.cmbStatSimplifyMeshes.TabIndex = 2;
        	this.cmbStatSimplifyMeshes.Text = "Full";
        	this.cmbStatSimplifyMeshes.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKeyPress);
        	// 
        	// lStatSimplifyMeshes
        	// 
        	this.lStatSimplifyMeshes.AutoSize = true;
        	this.lStatSimplifyMeshes.Location = new System.Drawing.Point(62, 99);
        	this.lStatSimplifyMeshes.Name = "lStatSimplifyMeshes";
        	this.lStatSimplifyMeshes.Size = new System.Drawing.Size(61, 13);
        	this.lStatSimplifyMeshes.TabIndex = 0;
        	this.lStatSimplifyMeshes.Text = "Mesh detail";
        	// 
        	// cmbStatSkipMipLevels
        	// 
        	this.cmbStatSkipMipLevels.ContextMenuStrip = this.DudMenu;
        	this.cmbStatSkipMipLevels.FormattingEnabled = true;
        	this.cmbStatSkipMipLevels.Items.AddRange(new object[] {
        	        	        	"0",
        	        	        	"1",
        	        	        	"2",
        	        	        	"3"});
        	this.cmbStatSkipMipLevels.Location = new System.Drawing.Point(8, 123);
        	this.cmbStatSkipMipLevels.Name = "cmbStatSkipMipLevels";
        	this.cmbStatSkipMipLevels.Size = new System.Drawing.Size(48, 21);
        	this.cmbStatSkipMipLevels.TabIndex = 3;
        	this.cmbStatSkipMipLevels.Text = "1";
        	this.cmbStatSkipMipLevels.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKeyPress);
        	// 
        	// lStatSkipMipLevels
        	// 
        	this.lStatSkipMipLevels.AutoSize = true;
        	this.lStatSkipMipLevels.Location = new System.Drawing.Point(62, 126);
        	this.lStatSkipMipLevels.Name = "lStatSkipMipLevels";
        	this.lStatSkipMipLevels.Size = new System.Drawing.Size(108, 13);
        	this.lStatSkipMipLevels.TabIndex = 0;
        	this.lStatSkipMipLevels.Text = "Mipmap levels to skip";
        	// 
        	// lStatSkipMipDesc
        	// 
        	this.lStatSkipMipDesc.AutoSize = true;
        	this.lStatSkipMipDesc.Location = new System.Drawing.Point(5, 151);
        	this.lStatSkipMipDesc.Name = "lStatSkipMipDesc";
        	this.lStatSkipMipDesc.Size = new System.Drawing.Size(158, 26);
        	this.lStatSkipMipDesc.TabIndex = 0;
        	this.lStatSkipMipDesc.Text = "Skipping mipmap levels reduces\r\nthe required vram in-game";
        	// 
        	// cbStatActivators
        	// 
        	this.cbStatActivators.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.cbStatActivators.AutoSize = true;
        	this.cbStatActivators.Location = new System.Drawing.Point(240, 45);
        	this.cbStatActivators.Name = "cbStatActivators";
        	this.cbStatActivators.Size = new System.Drawing.Size(110, 17);
        	this.cbStatActivators.TabIndex = 4;
        	this.cbStatActivators.Text = "Include activators";
        	this.cbStatActivators.UseVisualStyleBackColor = true;
        	// 
        	// cbStatIncludeMisc
        	// 
        	this.cbStatIncludeMisc.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.cbStatIncludeMisc.AutoSize = true;
        	this.cbStatIncludeMisc.Location = new System.Drawing.Point(240, 74);
        	this.cbStatIncludeMisc.Name = "cbStatIncludeMisc";
        	this.cbStatIncludeMisc.Size = new System.Drawing.Size(122, 17);
        	this.cbStatIncludeMisc.TabIndex = 5;
        	this.cbStatIncludeMisc.Text = "Include misc objects";
        	this.cbStatIncludeMisc.UseVisualStyleBackColor = true;
        	// 
        	// cbStatIntWater
        	// 
        	this.cbStatIntWater.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.cbStatIntWater.AutoSize = true;
        	this.cbStatIntWater.Location = new System.Drawing.Point(240, 125);
        	this.cbStatIntWater.Name = "cbStatIntWater";
        	this.cbStatIntWater.Size = new System.Drawing.Size(186, 30);
        	this.cbStatIntWater.TabIndex = 7;
        	this.cbStatIntWater.Text = "Include reflective water in interiors\r\n(increases load time)";
        	this.cbStatIntWater.UseVisualStyleBackColor = true;
        	// 
        	// bStatOverrideList
        	// 
        	this.bStatOverrideList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
        	this.bStatOverrideList.Location = new System.Drawing.Point(8, 211);
        	this.bStatOverrideList.Name = "bStatOverrideList";
        	this.bStatOverrideList.Size = new System.Drawing.Size(48, 56);
        	this.bStatOverrideList.TabIndex = 10;
        	this.bStatOverrideList.Text = "Edit\r\nlist";
        	this.bStatOverrideList.UseVisualStyleBackColor = true;
        	this.bStatOverrideList.Click += new System.EventHandler(this.bStatOverrideList_Click);
        	// 
        	// lStatOverrideList
        	// 
        	this.lStatOverrideList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.lStatOverrideList.Location = new System.Drawing.Point(66, 215);
        	this.lStatOverrideList.Name = "lStatOverrideList";
        	this.lStatOverrideList.Size = new System.Drawing.Size(255, 48);
        	this.lStatOverrideList.TabIndex = 0;
        	this.lStatOverrideList.Text = "NO STATIC OVERRIDES PRESENT";
        	this.lStatOverrideList.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
        	this.lStatOverrideList.Visible = false;
        	// 
        	// lbStatOverrideList
        	// 
        	this.lbStatOverrideList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.lbStatOverrideList.BackColor = System.Drawing.SystemColors.Control;
        	this.lbStatOverrideList.FormattingEnabled = true;
        	this.lbStatOverrideList.Location = new System.Drawing.Point(62, 211);
        	this.lbStatOverrideList.Name = "lbStatOverrideList";
        	this.lbStatOverrideList.SelectionMode = System.Windows.Forms.SelectionMode.None;
        	this.lbStatOverrideList.Size = new System.Drawing.Size(263, 56);
        	this.lbStatOverrideList.TabIndex = 11;
        	// 
        	// cbStatIntExt
        	// 
        	this.cbStatIntExt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.cbStatIntExt.AutoSize = true;
        	this.cbStatIntExt.Location = new System.Drawing.Point(240, 102);
        	this.cbStatIntExt.Name = "cbStatIntExt";
        	this.cbStatIntExt.Size = new System.Drawing.Size(203, 17);
        	this.cbStatIntExt.TabIndex = 6;
        	this.cbStatIntExt.Text = "Include interiors behaving like exterior";
        	this.cbStatIntExt.UseVisualStyleBackColor = true;
        	// 
        	// bStatExportStatics
        	// 
        	this.bStatExportStatics.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bStatExportStatics.Enabled = false;
        	this.bStatExportStatics.Location = new System.Drawing.Point(331, 188);
        	this.bStatExportStatics.Name = "bStatExportStatics";
        	this.bStatExportStatics.Size = new System.Drawing.Size(125, 23);
        	this.bStatExportStatics.TabIndex = 12;
        	this.bStatExportStatics.Text = "Export list of statics";
        	this.bStatExportStatics.UseVisualStyleBackColor = true;
        	this.bStatExportStatics.Click += new System.EventHandler(this.bStatExportStatics_Click);
        	// 
        	// bStatSkip
        	// 
        	this.bStatSkip.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bStatSkip.Enabled = false;
        	this.bStatSkip.Location = new System.Drawing.Point(331, 217);
        	this.bStatSkip.Name = "bStatSkip";
        	this.bStatSkip.Size = new System.Drawing.Size(125, 23);
        	this.bStatSkip.TabIndex = 13;
        	this.bStatSkip.Text = "Skip Static Creation";
        	this.bStatSkip.UseVisualStyleBackColor = true;
        	this.bStatSkip.Click += new System.EventHandler(this.bStatSkip_Click);
        	// 
        	// bStatRun
        	// 
        	this.bStatRun.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bStatRun.Enabled = false;
        	this.bStatRun.Location = new System.Drawing.Point(331, 246);
        	this.bStatRun.Name = "bStatRun";
        	this.bStatRun.Size = new System.Drawing.Size(125, 23);
        	this.bStatRun.TabIndex = 14;
        	this.bStatRun.Text = "Create Statics";
        	this.bStatRun.UseVisualStyleBackColor = true;
        	this.bStatRun.Click += new System.EventHandler(this.bStatRun_Click);
        	// 
        	// cbStatOverrideList
        	// 
        	this.cbStatOverrideList.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
        	this.cbStatOverrideList.AutoSize = true;
        	this.cbStatOverrideList.Location = new System.Drawing.Point(8, 192);
        	this.cbStatOverrideList.Name = "cbStatOverrideList";
        	this.cbStatOverrideList.Size = new System.Drawing.Size(264, 17);
        	this.cbStatOverrideList.TabIndex = 9;
        	this.cbStatOverrideList.Text = "Use lists of statics overriding parameters set above";
        	this.cbStatOverrideList.UseVisualStyleBackColor = true;
        	// 
        	// tabFinish
        	// 
        	this.tabFinish.Controls.Add(this.lFinishDesc);
        	this.tabFinish.Controls.Add(this.bFinish);
        	this.tabFinish.Location = new System.Drawing.Point(4, 25);
        	this.tabFinish.Name = "tabFinish";
        	this.tabFinish.Size = new System.Drawing.Size(464, 270);
        	this.tabFinish.TabIndex = 4;
        	this.tabFinish.Text = "Finished";
        	this.tabFinish.UseVisualStyleBackColor = true;
        	// 
        	// lFinishDesc
        	// 
        	this.lFinishDesc.AutoSize = true;
        	this.lFinishDesc.Location = new System.Drawing.Point(8, 3);
        	this.lFinishDesc.Name = "lFinishDesc";
        	this.lFinishDesc.Size = new System.Drawing.Size(202, 13);
        	this.lFinishDesc.TabIndex = 0;
        	this.lFinishDesc.Text = "Waiting for statics generation to complete";
        	// 
        	// bFinish
        	// 
        	this.bFinish.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bFinish.Enabled = false;
        	this.bFinish.Location = new System.Drawing.Point(331, 246);
        	this.bFinish.Name = "bFinish";
        	this.bFinish.Size = new System.Drawing.Size(125, 23);
        	this.bFinish.TabIndex = 1;
        	this.bFinish.Text = "Finish";
        	this.bFinish.UseVisualStyleBackColor = true;
        	this.bFinish.Click += new System.EventHandler(this.bFinish_Click);
        	// 
        	// saveStaticListDialog
        	// 
        	this.saveStaticListDialog.DefaultExt = "ovr";
        	this.saveStaticListDialog.Filter = "Static overrides (*.ovr)|*.ovr|Text files (*.txt)|*.txt|All files|*.*";
        	this.saveStaticListDialog.RestoreDirectory = true;
        	// 
        	// DistantLandForm
        	// 
        	this.ClientSize = new System.Drawing.Size(472, 321);
        	this.Controls.Add(this.tabControl);
        	this.Controls.Add(this.statusBar);
        	this.Icon = global::MGEgui.Properties.Resources.AppIcon;
        	this.MinimumSize = new System.Drawing.Size(480, 351);
        	this.Name = "DistantLandForm";
        	this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
        	this.Text = "Distant Land Setup Wizard";
        	this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.DistantLandForm_FormClosing);
        	this.statusBar.ResumeLayout(false);
        	this.statusBar.PerformLayout();
        	this.tabControl.ResumeLayout(false);
        	this.tabPlugs.ResumeLayout(false);
        	this.tabPlugs.PerformLayout();
        	this.gbPlugsSort.ResumeLayout(false);
        	this.gbPlugsSort.PerformLayout();
        	this.tabTex.ResumeLayout(false);
        	this.tabTex.PerformLayout();
        	this.tabMesh.ResumeLayout(false);
        	this.tabMesh.PerformLayout();
        	this.tabStat.ResumeLayout(false);
        	this.tabStat.PerformLayout();
        	((System.ComponentModel.ISupportInitialize)(this.udStatMinSize)).EndInit();
        	((System.ComponentModel.ISupportInitialize)(this.udStatGrassDensity)).EndInit();
        	this.tabFinish.ResumeLayout(false);
        	this.tabFinish.PerformLayout();
        	this.ResumeLayout(false);
        	this.PerformLayout();
        }
        private System.Windows.Forms.Label lInstructions;
        private System.Windows.Forms.Label lTexWorldMemUse;
        private System.Windows.Forms.Label lTexNormalMemUse;

        #endregion

        private System.ComponentModel.BackgroundWorker backgroundWorker;
        private System.Windows.Forms.StatusStrip statusBar;
        private System.Windows.Forms.ToolStripProgressBar statusProgress;
        private System.Windows.Forms.ToolStripSplitButton statusWarnings;
        private System.Windows.Forms.ToolStripStatusLabel statusText;
        private System.Windows.Forms.ContextMenuStrip DudMenu;
        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tabPlugs;
        private System.Windows.Forms.TabPage tabTex;
        private System.Windows.Forms.TabPage tabMesh;
        private System.Windows.Forms.TabPage tabStat;
        private System.Windows.Forms.TabPage tabFinish;
        private System.Windows.Forms.Label lPlugsModList;
        private System.Windows.Forms.CheckedListBox clbPlugsModList;
        private System.Windows.Forms.Button bPlugsFromINI;
        private System.Windows.Forms.Button bPlugsAll;
        private System.Windows.Forms.Button bPlugsClear;
        private System.Windows.Forms.Button bPlugsDirs;
        private System.Windows.Forms.GroupBox gbPlugsSort;
        private System.Windows.Forms.RadioButton rbPlugsName;
        private System.Windows.Forms.RadioButton rbPlugsType;
        private System.Windows.Forms.RadioButton rbPlugsLoad;
        private System.Windows.Forms.Button bPlugsRun;
        private System.Windows.Forms.Label lTexDesc;
        private System.Windows.Forms.ComboBox cmbTexWorldResolution;
        private System.Windows.Forms.Label lTexWorldResolution;
        private System.Windows.Forms.ComboBox cmbTexWorldNormalRes;
        private System.Windows.Forms.Label lTexWorldNormalRes;
        private System.Windows.Forms.Label lTexTwoStepDesc;
        private System.Windows.Forms.CheckBox cbTexTwoStep;
        private System.Windows.Forms.Button bTexSkip;
        private System.Windows.Forms.Button bTexRun;
        private System.Windows.Forms.Label lMeshDesc;
        private System.Windows.Forms.ComboBox cmbMeshWorldDetail;
        private System.Windows.Forms.Label lMeshWorldDetail;
        private System.Windows.Forms.Label lMeshAutoInfo;
        private System.Windows.Forms.Button bMeshSkip;
        private System.Windows.Forms.Button bMeshRun;
        private System.Windows.Forms.Label lStatDesc;
        private System.Windows.Forms.NumericUpDown udStatMinSize;
        private System.Windows.Forms.Label lStatMinSize;
        private System.Windows.Forms.NumericUpDown udStatGrassDensity;
        private System.Windows.Forms.Label lStatGrassDensity;
        private System.Windows.Forms.ComboBox cmbStatSimplifyMeshes;
        private System.Windows.Forms.Label lStatSimplifyMeshes;
        private System.Windows.Forms.ComboBox cmbStatSkipMipLevels;
        private System.Windows.Forms.Label lStatSkipMipLevels;
        private System.Windows.Forms.Label lStatSkipMipDesc;
        private System.Windows.Forms.CheckBox cbStatActivators;
        private System.Windows.Forms.CheckBox cbStatIncludeMisc;
        private System.Windows.Forms.CheckBox cbStatIntWater;
        private System.Windows.Forms.CheckBox cbStatOverrideList;
        private System.Windows.Forms.Button bStatOverrideList;
        private System.Windows.Forms.Label lStatOverrideList;
        private System.Windows.Forms.ListBox lbStatOverrideList;
        private System.Windows.Forms.CheckBox cbStatIntExt;
        private System.Windows.Forms.Button bStatExportStatics;
        private System.Windows.Forms.Button bStatSkip;
        private System.Windows.Forms.Button bStatRun;
        private System.Windows.Forms.Label lFinishDesc;
        private System.Windows.Forms.Button bFinish;
        private System.Windows.Forms.SaveFileDialog saveStaticListDialog;
    }
}