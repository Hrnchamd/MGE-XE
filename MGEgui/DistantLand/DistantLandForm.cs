using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;
using MGEgui.DirectX;
using MGEgui.INI;

namespace MGEgui.DistantLand {

    public partial class DistantLandForm : Form {

        public DistantLandForm(bool exists) {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            Statics.Localizations.ApplyDialogs(this, new string[] { "saveStaticListDialog" });

            this.saveStaticListDialog.InitialDirectory = Statics.runDir + "\\MGE3";
            Exists = exists;
            if (Exists) StaticsExist = File.Exists(Statics.fn_usagedata);
            LoadSettings();
            Directory.CreateDirectory(Statics.fn_dl);

            statusText.Text = strings["LoadBSAInit"];
            statusProgress.Style = ProgressBarStyle.Marquee;
            backgroundWorker.DoWork += workerInitBSAs;
            backgroundWorker.RunWorkerCompleted += workerFInitBSAs;
            statusWarnings.Text = strings["NoWarnings"]; 
            statusWarnings.Enabled = false;
            allWarnings = new List<string>();
            lTexDesc.Text += DXMain.mCaps.MaxTexSize.ToString();
            DXMain.CreateDevice(this);
            LTEX.ReleaseCache();
            backgroundWorker.RunWorkerAsync();
        }

        public static Dictionary<string, string> strings = new Dictionary<string, string>();
        
        /* Static methods */

        private static void DumpError(Exception ex) {
            string str = ex.ToString();
            while ((ex = ex.InnerException) != null) str += Environment.NewLine + Environment.NewLine + str.ToString();
            File.WriteAllText(Statics.fn_dlcrash, str);
        }

        private static string ReadString(BinaryReader br) {
            return new string(br.ReadChars(4));
        }

        private static string ReadCString(BinaryReader br) {
            List<char> chars = new List<char>();
            while (true) {
                char c = br.ReadChar();
                if (c == '\0') return new string(chars.ToArray());
                else chars.Add(c);
            }
        }

        private static string ReadCString(BinaryReader br, int max) {
            List<char> chars = new List<char>();
            while (true) {
                char c = br.ReadChar();
                if (max-- == 0 || c == '\0') return new string(chars.ToArray());
                else chars.Add(c);
            }
        }

        /* Common properties */

        private bool ChangingPage;
        private bool Exists;
        private bool StaticsExist;
        private string[] files;
        private List<string> warnings;
        private List<string> allWarnings;

        //Keeps track of map extents in terms of cells
        private int MapSize = 0;
        private int MapMaxX = Int32.MinValue;
        private int MapMaxY = Int32.MinValue;
        private int MapMinX = Int32.MaxValue;
        private int MapMinY = Int32.MaxValue;

        private int CellCount;
        public int VeryHigh = int.MinValue;
        public int VeryLow = int.MaxValue;

        private static LAND[,] map;
        private readonly LAND defaultland = new LAND();
        private static LTEX DefaultTex;

        /* Common handlers */

        private void IgnoreKeyPress(object sender, KeyPressEventArgs e) {
            e.Handled = true;
        }

        private void statusWarnings_ButtonClick(object sender, EventArgs e) {
            (new WarningsForm(warnings)).ShowDialog();
        }

        private void UpdateProgress(object sender, System.ComponentModel.ProgressChangedEventArgs e) {
            statusProgress.Value = e.ProgressPercentage;
            if (e.UserState != null) statusText.Text = (string)e.UserState;
        }

        private void tabControl_Selecting(object sender, TabControlCancelEventArgs e) {
            if (ChangingPage) ChangingPage = false;
            else e.Cancel = true;
        }

        private void DistantLandForm_FormClosing(object sender, FormClosingEventArgs e) {
            if (!ChangingPage) {
                if (backgroundWorker.IsBusy) {
                    e.Cancel = true;
                    MessageBox.Show(strings["PleaseWait"], Statics.strings["Error"]);
                } else {
                    if (MessageBox.Show(strings["ConfirmExit"], Statics.strings["Warning"], MessageBoxButtons.YesNo) != DialogResult.Yes) e.Cancel = true;
                }
            }
        }

        /* Common methods */

        private void saveWarnings(string source) {
            try {
                File.AppendAllText(Statics.fn_dllog, "### " + source + " ###\r\n\r\n" + string.Join("\r\n", warnings.ToArray()) + "\r\n\r\n");
            } catch { }
        }

        public static void ModCell(ref int cell, ref int tex) {
            if (tex < 0) { cell--; tex += 16; } else if (tex >= 16) { cell++; tex -= 16; }
        }

        static public LTEX GetTex(int cellx, int celly, int texx, int texy) {
            if (map[cellx, celly] != null) return map[cellx, celly].Textures[map[cellx, celly].Tex[texx, texy]];
            else return DefaultTex;
        }

        /* Configuration properties */
        
        // INI dictionaries
        
        private static Dictionary<string, double> sortOrder = new Dictionary<string, double> {
            {"Name", 0},
            {"Type", 1},
            {"Load order", 2}
        };

        private static Dictionary<string, double> texRes = new Dictionary<string, double> {
            {"128", 0},
            {"256", 1},
            {"512", 2},
            {"1024", 3},
            {"2048", 4},
            {"4096", 5}
        };

        private static Dictionary<string, double> wMeshDet = new Dictionary<string, double> {
            {"Auto", -1},
            {"Ultra High", 0},
            {"Very High", 1},
            {"High", 2},
            {"Medium", 3},
            {"Low", 4}
        };

        private static Dictionary<string, double> sMeshDet = new Dictionary<string, double> {
            {"Full", 0},
            {"90%", 1},
            {"75%", 2},
            {"50%", 3},
            {"25%", 4}
        };
        
        // INI sections
        private const string iniDLWizardSets = "DLWizard Settings";
        private const string iniDLWizardPlugDirs = "DLWizard Plugin Dirs";
        private const string iniDLWizardPlugs = "DLWizard Plugins";
        private const string iniDLWizardStatOvr = "DLWizard Static Overrides";
        
        // INI key definitions
        private static INIFile.INIVariableDef iniPlugSort = new INIFile.INIVariableDef("PlugSort", iniDLWizardSets, "Plugins view sort order", INIFile.INIVariableType.Dictionary, "Load order", sortOrder);
        private static INIFile.INIVariableDef iniTexRes = new INIFile.INIVariableDef("TexRes", iniDLWizardSets, "World texture resolution", INIFile.INIVariableType.Dictionary, "2048", texRes);
        private static INIFile.INIVariableDef iniNormRes = new INIFile.INIVariableDef("NormRes", iniDLWizardSets, "World normalmap resolution", INIFile.INIVariableType.Dictionary, "1024", texRes);
        private static INIFile.INIVariableDef iniTex2Step = new INIFile.INIVariableDef("Tex2Step", iniDLWizardSets, "Create world texture in two steps", INIFile.INIBoolType.Text, "False");
        private static INIFile.INIVariableDef iniWorldMesh = new INIFile.INIVariableDef("WorldMesh", iniDLWizardSets, "World mesh detail", INIFile.INIVariableType.Dictionary, "Auto", wMeshDet);
        private static INIFile.INIVariableDef iniMinStat = new INIFile.INIVariableDef("MinStat", iniDLWizardSets, "Minimum static size", INIFile.INIVariableType.UInt16, "150", 0, 9999);
        private static INIFile.INIVariableDef iniGrassDens = new INIFile.INIVariableDef("GrassDens", iniDLWizardSets, "Grass density", INIFile.INIVariableType.Byte, "100", 0, 100);
        private static INIFile.INIVariableDef iniStatMesh = new INIFile.INIVariableDef("StatMesh", iniDLWizardSets, "Mesh detail", INIFile.INIVariableType.Dictionary, "Full", sMeshDet);
        private static INIFile.INIVariableDef iniSkipMip = new INIFile.INIVariableDef("SkipMip", iniDLWizardSets, "Skip mipmap levels", INIFile.INIVariableType.Byte, "1", 0, 3);
        private static INIFile.INIVariableDef iniActivators = new INIFile.INIVariableDef("Activators", iniDLWizardSets, "Include activators", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniMiscObj = new INIFile.INIVariableDef("MiscObj", iniDLWizardSets, "Include misc objects", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniUseStatOvr = new INIFile.INIVariableDef("UseStatOvr", iniDLWizardSets, "Use static overrides", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniStatIntExt = new INIFile.INIVariableDef("StatIntExt", iniDLWizardSets, "Statics for behave like exterior cells", INIFile.INIBoolType.OnOff, "On");
        private static INIFile.INIVariableDef iniStatIntWater = new INIFile.INIVariableDef("StatIntWater", iniDLWizardSets, "Statics for interiors with water", INIFile.INIBoolType.OnOff, "Off");

        // set of keys to read at form creation
        private static INIFile.INIVariableDef[] iniDLWizardVars = {
            INIFile.iniDefEmpty,
            iniPlugSort,
            iniTexRes,
            iniNormRes,
            iniTex2Step,
            iniWorldMesh,
            iniMinStat,
            iniGrassDens, 
            iniStatMesh, 
            iniSkipMip,
            iniActivators, 
            iniMiscObj, 
            iniUseStatOvr,
            iniStatIntExt,
            iniStatIntWater
        };

	// set of keys to write after plugin selection
        private static INIFile.INIVariableDef[] iniPlugsTab = {
            INIFile.iniDefEmpty,
            iniPlugSort
        };

        // set of keys to write after land texture created
        private static INIFile.INIVariableDef[] iniTexTab = {
            INIFile.iniDefEmpty,
            iniTexRes,
            iniNormRes,
            iniTex2Step
        };

        // set of keys to write after land mesh created
        private static INIFile.INIVariableDef[] iniMeshTab = {
            INIFile.iniDefEmpty,
            iniWorldMesh
        };

        // set of keys to write after statics created
        private static INIFile.INIVariableDef[] iniStatTab = {
            INIFile.iniDefEmpty,
            iniMinStat,
            iniGrassDens,
            iniStatMesh,
            iniSkipMip,
            iniActivators,
            iniMiscObj,
            iniUseStatOvr,
            iniStatIntExt,
            iniStatIntWater
        };

        // configuration of setup steps
        private Dictionary<string, bool> SetupFlags = new Dictionary<string, bool>(){
            {"RunSetup", false},
            {"AutoRun", false},
            {"Debug", false},
            {"ChkLandTex", true},
            {"ChkLandMesh", true},
            {"ChkLandAuto", true},
            {"ChkStatics", true},
            {"EnaLandTex", true},
            {"EnaLandMesh", true},
            {"EnaLandAuto", true},
            {"EnaStatics", true},
        };

        private bool configure;

        /* Configuration methods */
        
        // loading all settings
        private void LoadSettings() {
            INIFile iniFile = new INIFile(Statics.iniFileName, iniDLWizardVars, true);
            configure = !iniFile.hasSection(iniDLWizardSets);
            if (configure) {
                iniFile.initialize();
                iniFile.save();
            }
            pluginDirs = new List<string>(iniFile.getSectList(iniDLWizardPlugDirs));
            pluginDirs.Sort();
            string dir2 = "";
            foreach (string s in pluginDirs) {
                string dir1 = s.ToLower(Statics.Culture);
                if (dir1 == dir2) pluginDirs.Remove(s);
                dir2 = dir1;
            }
            pluginList = new MWPlugins(Statics.fn_datafiles, pluginDirs);
            switch ((int)iniFile.getKeyValue("PlugSort")) {
                case 0: rbPlugsName.Checked = true; break;
                case 1: rbPlugsType.Checked = true; break;
                case 2: rbPlugsLoad.Checked = true; break;
            }
            pluginsSort(null, null);
            preselectedPlugins = iniFile.getSectList(iniDLWizardPlugs);
            SelectPlugins(preselectedPlugins);
            cmbTexWorldResolution.SelectedIndex = (int)iniFile.getKeyValue("TexRes");
            cmbTexWorldNormalRes.SelectedIndex = (int)iniFile.getKeyValue("NormRes");
            cbTexTwoStep.Checked = (iniFile.getKeyValue("Tex2Step") == 1);
            cmbMeshWorldDetail.SelectedIndex = (int)iniFile.getKeyValue("WorldMesh");
            udStatMinSize.Value = (int)iniFile.getKeyValue("MinStat");
            udStatGrassDensity.Value = (int)iniFile.getKeyValue("GrassDens");
            cmbStatSimplifyMeshes.SelectedIndex = (int)iniFile.getKeyValue("StatMesh");
            cmbStatSkipMipLevels.SelectedIndex = (int)iniFile.getKeyValue("SkipMip");
            cbStatActivators.Checked = (iniFile.getKeyValue("Activators") == 1);
            cbStatIncludeMisc.Checked = (iniFile.getKeyValue("MiscObj") == 1);
            cbStatOverrideList.Checked = (iniFile.getKeyValue("UseStatOvr") == 1);
            cbStatIntExt.Checked = (iniFile.getKeyValue("StatIntExt") == 1);
            cbStatIntWater.Checked = (iniFile.getKeyValue("StatIntWater") == 1);
            lbStatOverrideList.Items.Clear();
            lbStatOverrideList.Items.AddRange(iniFile.getSectList(iniDLWizardStatOvr));
            lStatOverrideList.Enabled = (lbStatOverrideList.Items.Count == 0);
        }

        // saving settings after plugin selection
        private void SavePlugsSettings() {
            INIFile iniFile = new INIFile(Statics.iniFileName, iniPlugsTab, true);
            double temp;
            if (rbPlugsName.Checked) temp = 0;
            else if (rbPlugsType.Checked) temp = 1;
            else if (rbPlugsLoad.Checked) temp = 2;
            else temp = 1;
            iniFile.setKey("PlugSort", temp);
            iniFile.setSectList(iniDLWizardPlugDirs, pluginDirs.ToArray());
            List<string> tempList = new List<string>();
            foreach (string s in clbPlugsModList.CheckedItems) tempList.Add(s);
            iniFile.setSectList(iniDLWizardPlugs, tempList.ToArray());
            iniFile.save();
        }

        // saving settings after land texture creation
        private void SaveTexSettings() {
            INIFile iniFile = new INIFile(Statics.iniFileName, iniTexTab, true);
            iniFile.setKey("TexRes", cmbTexWorldResolution.SelectedIndex);
            iniFile.setKey("NormRes", cmbTexWorldNormalRes.SelectedIndex);
            iniFile.setKey("Tex2Step", cbTexTwoStep.Checked);
            iniFile.save();
        }

        // saving settings after land mesh creation
        private void SaveMeshSettings() {
            INIFile iniFile = new INIFile(Statics.iniFileName, iniMeshTab, true);
            iniFile.setKey("WorldMesh", (cmbMeshWorldDetail_auto ? -1 : (double)cmbMeshWorldDetail.SelectedIndex));
            iniFile.save();
        }

        // saving settings after statics creation
        private void SaveStatSettings() {
            INIFile iniFile = new INIFile(Statics.iniFileName, iniStatTab, true);
            iniFile.setKey("MinStat", (double)udStatMinSize.Value);
            iniFile.setKey("GrassDens", (double)udStatGrassDensity.Value);
            iniFile.setKey("StatMesh", cmbStatSimplifyMeshes.SelectedIndex);
            iniFile.setKey("SkipMip", cmbStatSkipMipLevels.SelectedIndex);
            iniFile.setKey("Activators", cbStatActivators.Checked);
            iniFile.setKey("MiscObj", cbStatIncludeMisc.Checked);
            iniFile.setKey("UseStatOvr", cbStatOverrideList.Checked);
            iniFile.setKey("StatIntExt", cbStatIntExt.Checked);
            iniFile.setKey("StatIntWater", cbStatIntWater.Checked);
            List<string> tempList = new List<string>();
            foreach (string s in lbStatOverrideList.Items) tempList.Add(s);
            iniFile.setSectOrderedList(iniDLWizardStatOvr, tempList.ToArray());
            iniFile.save();
        }

        /* Background workers */

        private void workerInitBSAs(object sender, System.ComponentModel.DoWorkEventArgs e) {
            try { File.Delete(Statics.fn_dllog); } catch { }
            BSA.InitBSAs();
        }

        private void workerFInitBSAs(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e.Error != null) {
                DumpError(e.Error);
                MessageBox.Show(strings["LoadBSAError"] + "\n" + e.Error.Message);
                ChangingPage = true;
                Close();
                return;
            }
            if (e.Result != null) {
                warnings = (List<string>)e.Result;
                allWarnings.AddRange(warnings);
                saveWarnings("BSAs");
                if (!SetupFlags["AutoRun"]) {
                    statusWarnings.Text = warnings.Count + " " + strings["WarningCount"];
                    statusWarnings.Enabled = true;
                }
            }
            statusText.Text = strings["LoadBSAStatus"];
            statusProgress.Style = ProgressBarStyle.Continuous;
            backgroundWorker.DoWork -= workerInitBSAs;
            backgroundWorker.RunWorkerCompleted -= workerFInitBSAs;
            bPlugsRun.Enabled = true;
        }

        private void workerLoadPlugins(object sender, System.ComponentModel.DoWorkEventArgs e) {
            map = (LAND[,])Array.CreateInstance(typeof(LAND), new int[] { 501, 501 }, new int[] { -250, -250 });
            DefaultTex = new LTEX();
            DefaultTex.FilePath = "_land_default.tga";
            DefaultTex.index = 0;
            try {
                DefaultTex.LoadTexture();
            } catch (Exception ex) {
                throw new ApplicationException("Failed to load default ground texture (" + ex.Message + ")", ex);
            }
            CellCount = 0;
            int progress = 0;
            List<string> errors = new List<string>();
            foreach (string file in files) {
                if (DEBUG) allWarnings.Add("Loading plugin: " + file);
                BinaryReader br = new BinaryReader(File.OpenRead(file), System.Text.Encoding.Default);
                List<LTEX> Textures = new List<LTEX>();
                //Add the default texture first, because all vtex id's are +1 compared to the ltex ids
                Textures.Add(DefaultTex);
                string s = "";
                while (br.BaseStream.Position < br.BaseStream.Length) {
                    s = ReadString(br);
                    if (s == "LAND") {
                        int size = br.ReadInt32();
                        int read = 0;
                        br.BaseStream.Position += 8;
                        LAND land = new LAND();
                        land.Textures = Textures;
                        int lx = -999;
                        int ly = -999;
                        while (read < size) {
                            s = ReadString(br);
                            int size2 = br.ReadInt32();
                            read += size2 + 8;
                            switch (s) {
                                case "INTV":
                                    lx = br.ReadInt32();
                                    ly = br.ReadInt32();
                                    land.xpos = lx;
                                    land.ypos = ly;
                                    break;
                                case "VHGT":
                                    int offset = (int)br.ReadSingle();
                                    for (int y = 0; y < 65; y++) {
                                        offset += br.ReadSByte();
                                        land.Heights[0, y] = offset;
                                        int pos = offset;
                                        for (int x = 1; x < 65; x++) {
                                            pos += br.ReadSByte();
                                            land.Heights[x, y] = pos;
                                            if (pos > VeryHigh) VeryHigh = pos;
                                            if (pos < VeryLow) VeryLow = pos;
                                        }
                                    }
                                    br.BaseStream.Seek(3, SeekOrigin.Current);
                                    break;
                                case "VNML":
                                    for (int y = 0; y < 65; y++) {
                                        for (int x = 0; x < 65; x++) {
                                            sbyte vx, vy, vz;
                                            vx = br.ReadSByte();
                                            vy = br.ReadSByte();
                                            vz = br.ReadSByte();
                                            land.Normals[x, y] = new Normal(vx, vy, vz);
                                        }
                                    }
                                    break;
                                case "VCLR":
                                    for (int y = 0; y < 65; y++) {
                                        for (int x = 0; x < 65; x++) {
                                            land.Color[x, y] = new RGB(br.ReadByte(), br.ReadByte(), br.ReadByte());
                                        }
                                    }
                                    break;
                                case "VTEX":
                                    for (int y1 = 0; y1 < 4; y1++) {
                                        for (int x1 = 0; x1 < 4; x1++) {
                                            for (int y2 = 0; y2 < 4; y2++) {
                                                for (int x2 = 0; x2 < 4; x2++) {
                                                    land.Tex[x1 * 4 + x2, y1 * 4 + y2] = br.ReadInt16();
                                                }
                                            }
                                        }
                                    }
                                    break;
                                default:
                                    br.BaseStream.Position += size2;
                                    break;
                            }
                        }
                        if (lx != -999 && ly != -999) {
                            //Keep track of map extents
                            if (lx > MapMaxX) { MapMaxX = lx; }
                            if (ly > MapMaxY) { MapMaxY = ly; }
                            if (lx < MapMinX) { MapMinX = lx; }
                            if (ly < MapMinY) { MapMinY = ly; }
                            int max = Math.Max(MapMaxX - MapMinX, MapMaxY - MapMinY);
                            if (max > MapSize) MapSize = max;
                            if (map[lx, ly] == null) CellCount++;
                            map[lx, ly] = land;
                        }
                    } else if (s == "LTEX") {
                        //TODO: Fix!
                        //Presumably, not all LTEX's have the subrecords in an identical order
                        LTEX tex = new LTEX();
                        int size = br.ReadInt32();
                        long pos = br.BaseStream.Position + 8;
                        br.BaseStream.Position += 16;
                        ReadCString(br);
                        br.BaseStream.Position += 8;
                        tex.index = br.ReadInt32() + 1;
                        br.BaseStream.Position += 8;
                        tex.FilePath = ReadCString(br).ToLower(Statics.Culture);
                        try {
                            tex.LoadTexture();
                        } catch (Exception ex) {
                            errors.Add("Texture '" + tex.FilePath + "' in plugin '" + file + "' failed to load (" + ex.Message + ")");
                            tex.tex = DefaultTex.tex;
                        }
                        Textures.Add(tex);
                        br.BaseStream.Position = pos + size;
                    } else {
                        int size = br.ReadInt32();
                        br.BaseStream.Position += size + 8;
                    }
                }
                br.Close();
                Textures.Sort(new LTEXSorter());
                backgroundWorker.ReportProgress(++progress);
            }
        }

        private void workerFLoadPlugins(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e.Error != null) {
                DumpError(e.Error);
                MessageBox.Show(strings["LoadLandError"] + "\n" + e.Error.Message);
                ChangingPage = true;
                Close();
                return;
            }
            statusProgress.Value = 0;
            if (e.Result != null) {
                warnings = (List<string>)e.Result;
                allWarnings.AddRange(warnings);
                saveWarnings("Plugins");
                if (!SetupFlags["AutoRun"]) {
                    statusWarnings.Text = warnings.Count + " " + strings["WarningCount"];
                    statusWarnings.Enabled = true;
                }
            }
            if (DEBUG) allWarnings.Add("Plugin land data loaded");
            statusText.Text = strings["LoadLandStatus"];
            backgroundWorker.DoWork -= workerLoadPlugins;
            backgroundWorker.RunWorkerCompleted -= workerFLoadPlugins;
            SavePlugsSettings();
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(1);
                if (SetupFlags["ChkLandTex"]) bTexRun_Click(null, null);
                else bTexSkip_Click(null, null);
            } else {
                bTexSkip.Enabled = true;
                bTexRun.Enabled = true;
            }
        }

        private struct CreateTextureArgs {
            public int WorldRes;
            public int WorldNormal;
            public bool twoStep;
        }

        void workerCreateTextures(object sender, System.ComponentModel.DoWorkEventArgs e) {
            CreateTextureArgs args = (CreateTextureArgs)e.Argument;
            DirectX.CellTexCreator ctc = new CellTexCreator(4);
            int count = 0;
            backgroundWorker.ReportProgress(count, strings["LandTextureCreate"]);
            //Render world texture
            WorldTexCreator wtc = new WorldTexCreator(args.WorldRes, MapMinX, MapMaxX, MapMinY, MapMaxY);
            wtc.Begin();
            ctc.Begin();
            for (int y = MapMinY; y <= MapMaxY; y++) {
                backgroundWorker.ReportProgress(++count);
                for (int x = MapMinX; x <= MapMaxX; x++) {
                    if (map[x, y] == null || map[x, y] == defaultland) ctc.SetDefaultCell(DefaultTex);
                    //Set the colors and normals
                    else ctc.SetCell(map[x, y]);
                    float x_pos = (((float)(x - MapMinX) + 0.5f) * wtc.x_spacing) - 1.0f;
                    float y_pos = (((float)(y - MapMinY) + 0.5f) * wtc.y_spacing) - 1.0f;
                    ctc.Render(x_pos, y_pos, wtc.x_scale, wtc.y_scale);
                }
            }
            ctc.End();
            //Save the world texture.
            wtc.FinishCompressed(Statics.fn_worldds, args.twoStep);
            wtc.Dispose();
            wtc = new WorldTexCreator(args.WorldNormal, MapMinX, MapMaxX, MapMinY, MapMaxY);
            wtc.Begin();
            ctc.BeginNormalMap();
            for (int y = MapMinY; y <= MapMaxY; y++) {
                backgroundWorker.ReportProgress(++count);
                for (int x = MapMinX; x <= MapMaxX; x++) {
                    if (map[x, y] == null || map[x, y] == defaultland) ctc.SetDefaultCell(DefaultTex);
                    //Set the colors and normals
                    else ctc.SetCell(map[x, y]);
                    float x_pos = (((float)(x - MapMinX) + 0.5f) * wtc.x_spacing) - 1.0f;
                    float y_pos = (((float)(y - MapMinY) + 0.5f) * wtc.y_spacing) - 1.0f;
                    ctc.RenderNormalMap(x_pos, y_pos, wtc.x_scale, wtc.y_scale);
                }
            }
            ctc.EndNormalMap();
            wtc.FinishUncompressed(Statics.fn_worldn);
            wtc.Dispose();
            ctc.Dispose();
        }

        void workerFCreateTextures(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e.Error != null) {
                DumpError(e.Error);
                MessageBox.Show(strings["LandTextureError"] + "\n" + e.Error.Message);
                ChangingPage = true;
                Close();
                return;
            }
            statusProgress.Value = 0;
            if (e.Result != null) {
                warnings = (List<string>)e.Result;
                allWarnings.AddRange(warnings);
                saveWarnings("Textures");
                if (!SetupFlags["AutoRun"]) {
                    statusWarnings.Text = warnings.Count + " " + strings["WarningCount"];
                    statusWarnings.Enabled = true;
                }
            }
            if (DEBUG) allWarnings.Add("Landscape textures created");
            statusText.Text = strings["LandTextureStatus"];
            backgroundWorker.DoWork -= workerCreateTextures;
            backgroundWorker.RunWorkerCompleted -= workerFCreateTextures;
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(2);
                if (SetupFlags["ChkLandMesh"]) bMeshRun_Click(null, null);
                else bMeshSkip_Click(null, null);
            } else {
                SaveTexSettings();
                bMeshSkip.Enabled = true;
                bMeshRun.Enabled = true;
            }
        }

        private struct CreateMeshArgs {
            public int MeshDetail;
        }

        void workerCreateMeshes(object sender, System.ComponentModel.DoWorkEventArgs e) {
            CreateMeshArgs cma = (CreateMeshArgs)e.Argument;
            int count = 0;
            backgroundWorker.ReportProgress(count, strings["LandMeshCreate"]);
            GenerateWorldMesh(cma.MeshDetail, Statics.fn_world);
            // Dispose of map object, high memory use
            map = null;
        }

        void workerFCreateMeshes(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e != null) {
                LTEX.ReleaseCache();
                if (e.Error != null) {
                    DumpError(e.Error);
                    MessageBox.Show(strings["LandMeshError"] + "\n" + e.Error.Message);
                    ChangingPage = true;
                    Close();
                    return;
                }
                statusProgress.Value = 0;
                if (e.Result != null) {
                    warnings = (List<string>)e.Result;
                    allWarnings.AddRange(warnings);
                    saveWarnings("Meshes");
                    if (!SetupFlags["AutoRun"]) {
                        statusWarnings.Text = warnings.Count + " " + strings["WarningCount"];
                        statusWarnings.Enabled = true;
                    }
                }
                if (DEBUG) allWarnings.Add("Landscape meshes created");
                statusText.Text = strings["LandMeshStatus"];
                backgroundWorker.DoWork -= workerCreateMeshes;
                backgroundWorker.RunWorkerCompleted -= workerFCreateMeshes;
                if (SetupFlags["AutoRun"]) {
                    setFinishDesc(3);
                    if (SetupFlags["ChkStatics"]) bStatRun_Click(null, null);
                    else bStatSkip_Click(null, null);
                } else {
                    SaveMeshSettings();
                    bStatExportStatics.Enabled = true;
                    bStatRun.Enabled = true;
                    bStatSkip.Enabled = true;
                }
            }
        }

        private struct CreateStaticsArgs {
            public float MinSize;
            public int MipSkip;
            public List<string> OverrideList;
            public bool useOverrideList;
            public bool activators;
            public bool misc;
            public float simplify;
            public bool oldSimplify;
        }

        private void GrassDensityThreshold (float GrassDensity, KeyValuePair<string, Dictionary<string, StaticReference>> cellStatics, KeyValuePair<string, StaticReference> pair, Random rnd, List<StaticToRemove> UsedStaticsToRemove) {
            if (GrassDensity < 1.0f) {
                //remove some of the grass to improve performance
                if (rnd.NextDouble () >= GrassDensity) UsedStaticsToRemove.Add (new StaticToRemove (cellStatics.Key, pair.Key));
            } else if (GrassDensity == 0.0f) {
                //Remove all grass
                UsedStaticsToRemove.Add (new StaticToRemove (cellStatics.Key, pair.Key));
            }
        }

        void workerCreateStatics(object sender, System.ComponentModel.DoWorkEventArgs e) {
            CreateStaticsArgs args = (CreateStaticsArgs)e.Argument;
            List<string> warnings = new List<string>();
            Dictionary<string, staticOverride> OverrideList = new Dictionary<string, staticOverride>();
            Dictionary<string, bool> IgnoreList = new Dictionary<string, bool>();
            Dictionary<string, bool> CellList = new Dictionary<string, bool>();
            StaticsList.Clear();
            UsedStaticsList.Clear();
            StaticMap.Clear();
            if (args.useOverrideList && args.OverrideList.Count > 0) foreach (string overrideList in args.OverrideList) {
                if (DEBUG) allWarnings.Add("Loading override: " + overrideList);
                StreamReader sr = null;
                try { sr = new StreamReader(File.OpenRead(overrideList)); }
                catch { warnings.Add("Error: Could not import statics list '" + overrideList + "'"); }
                if (sr != null) {
                    int index; string section = ""; string line; string escape;
                    while (!sr.EndOfStream) switch (section) {
                        case "":
                            line = sr.ReadLine().ToLower(Statics.Culture);
                            index = line.IndexOf(':');
                            if (index != -1) line = line.Substring(0, index);
                            line = line.Trim();
                            if (line.Length > 0 && line[0] != '#') {
                                if (line.StartsWith("[") && line.EndsWith("]")) {
                                    section = line.Substring(1, line.Length - 2);
                                    continue;
                                }
                                index = line.LastIndexOf('=');
                                if (index != -1) {
                                    string mesh = line.Substring(0, index);
                                    string value = line.Substring(index + 1);
                                    byte type;
                                    if (byte.TryParse(value, out type)) {
                                        if (type != 3 && type <= 6) OverrideList[line] = new staticOverride(type);
                                        else if (type > 6) warnings.Add("Warning: Invalid type specified in statics list '" + overrideList + "' line '" + line + "'");
                                    } else OverrideList[mesh] = new staticOverride(value);
                                } else {
                                	warnings.Add("Warning: Failed to parse line in statics list '" + overrideList + "': '" + line + "'");
                                }
                            }
                            break;
                        case "names":
                            line = sr.ReadLine().ToLower(Statics.Culture);
                            index = line.IndexOf(':');
                            escape = line;
                            if (index != -1) escape = escape.Substring(0, index);
                            escape = escape.Trim();
                            if (escape.Length > 0 && escape.StartsWith("[") && escape.EndsWith("]") && !escape.EndsWith("\\]")) {
                                section = escape.Substring(1, escape.Length - 2);
                                continue;
                            }
                            if (line.IndexOf('\u0001') != -1) continue;
                            escape = "";
                            while ((index = line.IndexOf('\\') + 1) != 0) {
                                if (index == line.Length) break;
                                escape += line[index];
                                line = line.Substring(0, index - 1) + "\u0001" + (line.Length >= index ? line.Substring(index + 1) : "");
                            }
                            index = line.IndexOf(':');
                            if (index != -1) line = line.Substring(0, index);
                            line = line.Trim();
                            int equals_index = line.LastIndexOf('=');
                            for (var i = 0; (index = line.IndexOf ('\u0001')) != -1; i++) {
                                line = line.Substring(0, index) + escape[i] + (line.Length >= index ? line.Substring(index + 1) : "");
                            }
                            if (line.Length > 0) {
                                if (equals_index == -1) IgnoreList[line] = true;
                                else {
                                    string value = line.Substring(equals_index + 1);
                                    line = line.Substring(0, equals_index);
                                    switch (value) {
                                        case "enable":
                                            IgnoreList[line] = false;
                                            break;
                                        case "disable":
                                            IgnoreList[line] = true;
                                            break;
                                        default:
                                            warnings.Add("Warning: Invalid keyword in statics list line '" + line + "'");
                                            break;
                                    }
                                }
                            }
                            break;
                        case "interiors":
                            line = sr.ReadLine().ToLower(Statics.Culture);
                            index = line.IndexOf (':');
                            escape = line;
                            if (index != -1) escape = escape.Substring (0, index);
                            escape = escape.Trim();
                            if (escape.Length > 0 && escape.StartsWith("[") && escape.EndsWith("]") && !escape.EndsWith("\\]")) {
                                section = escape.Substring(1, escape.Length - 2);
                                continue;
                            }
                            if (line.IndexOf ('\u0001') != -1) continue;
                            escape = "";
                            while ((index = line.IndexOf('\\') + 1) != 0) {
                                if (index == line.Length) break;
                                escape += line[index];
                                line = line.Substring(0, index - 1) + "\u0001" + (line.Length >= index ? line.Substring(index + 1) : "");
                            }
                            index = line.IndexOf(':');
                            if (index != -1) line = line.Substring(0, index);
                            line = line.Trim();
                            equals_index = line.LastIndexOf('=');
                            for (var i = 0; (index = line.IndexOf('\u0001')) != -1; i++) {
                                line = line.Substring(0, index) + escape[i] + (line.Length >= index ? line.Substring(index + 1) : "");
                            }
                            if (line.Length > 0) {
                                if (equals_index == -1) CellList[line] = true;
                                else {
                                    string value = line.Substring(equals_index + 1);
                                    line = line.Substring(0, equals_index);
                                    switch (value) {
                                        case "enable":
                                            CellList[line] = true;
                                            break;
                                        case "disable":
                                            CellList[line] = false;
                                            break;
                                        default:
                                            warnings.Add("Warning: Invalid keyword in statics cell list line '" + line + "'");
                                            break;
                                    }
                                }
                            }
                            break;
                    }
                    sr.Close();
                }
            }
            Directory.CreateDirectory(Statics.fn_statics);
            foreach (string file in files) {
                if (DEBUG) allWarnings.Add("Parsing for statics definitions: " + file);
                BinaryReader br = new BinaryReader(File.OpenRead(file), System.Text.Encoding.Default);
                ParseFileForStatics(br, OverrideList, args.activators, args.misc, IgnoreList);
                br.Close();
            }
            backgroundWorker.ReportProgress(1, strings["StaticsGenerate1"]);
            UsedStaticsList.Add("", new Dictionary<string, StaticReference>());
            foreach (string file in files) {
                if (DEBUG) allWarnings.Add("Parsing for used statics: " + file);
                BinaryReader br = new BinaryReader(File.OpenRead(file), System.Text.Encoding.Default);
                FileInfo fi = new FileInfo(file);
                try {
                    ParseFileForCells(br, fi.Name, IgnoreList, CellList);
                } catch (Exception ex) {
                    warnings.Add("Non-fatal error in ParseFileForCells(\"" + file + "\"): " + ex.Message);
                }
                br.Close();
            }
            //Generate a list of the NIF files we need to load
            backgroundWorker.ReportProgress(2, strings["StaticsGenerate2"]);
            List<string> UsedNifList = new List<string>();
            foreach (KeyValuePair<string, Dictionary<string, StaticReference>> cellStatics in UsedStaticsList) {
                foreach (KeyValuePair<string, StaticReference> pair in cellStatics.Value) {
                    string nif_name = StaticsList[pair.Value.name].mesh;
                    if (!UsedNifList.Contains(nif_name)) UsedNifList.Add(nif_name);
                }
            }
            backgroundWorker.ReportProgress(3, strings["StaticsGenerate3"]);
            unsafe {
                NativeMethods.BeginStaticCreation((IntPtr)DXMain.device.ComPointer, Statics.fn_statmesh);
            }
            Random rnd = new Random();
            try {
                //Try to load the NIFs and remove any from the list that fail or are too small
                for (int i = 0; i < UsedNifList.Count; i++) {
                    string name = UsedNifList[i];
                    byte[] data;

                    //Try to load a version of the file that ends with '_dist' first.
                    // This allows people to supply a different version of the NIF to be
                    // rendered by distant land.  For example, a low poly nif.
                    string file_name = name;
                    string extention = "";
                    int dot_pos = file_name.LastIndexOf ('.');
                    if (dot_pos != -1) {
                        extention = file_name.Substring (dot_pos, file_name.Length - dot_pos);
                        file_name = file_name.Substring (0, dot_pos);
                    }
                    string dist_name = file_name + "_dist" + extention;
                    try {
                        data = BSA.GetNif (dist_name);
                    } catch {
                        // We didn't find a NIF file with '_dist' in its name,
                        // so search for the normal NIF file now.
                        try {
                            data = BSA.GetNif (name);
                        } catch {
                            data = null;
                        }
                    }
                    if (data == null) {
                        UsedNifList.RemoveAt (i--);
                    } else {
                        try {
                            if (DEBUG) {
                                statusText.Text = strings["StaticsGenerate3Nif"] + name;
                                allWarnings.Add ("Processing NIF: " + name);
                            }
                            float size = -1;
                            if (OverrideList.ContainsKey (name)) {
                                staticOverride so = OverrideList[name];
                                if (!so.Ignore || so.NamesNoIgnore) size = NativeMethods.ProcessNif (data, data.Length, so.overrideSimplify ? so.Simplify : args.simplify, args.MinSize, (byte)so.Type, (so.OldSimplify ? (byte)1 : (byte)0));
                            } else {
                                // Set static classification based on the file path
                                if (name.StartsWith ("grass\\")) size = NativeMethods.ProcessNif (data, data.Length, args.simplify, args.MinSize, (byte)StaticType.Grass, 0);
                                else if (name.StartsWith ("trees\\")) size = NativeMethods.ProcessNif (data, data.Length, args.simplify, args.MinSize, (byte)StaticType.Tree, 0);
                                else if (name.StartsWith ("x\\")) size = NativeMethods.ProcessNif (data, data.Length, args.simplify, args.MinSize, (byte)StaticType.Building, 0);
                                else size = NativeMethods.ProcessNif (data, data.Length, args.simplify, args.MinSize, (byte)StaticType.Auto, 0);
                            }
                            if (size < 0) UsedNifList.RemoveAt (i--);
                        } catch (Exception) {
                            warnings.Add ("Failed to process " + name);
                            UsedNifList.RemoveAt (i--);
                        }
                    }
                }
            } finally {
                NativeMethods.EndStaticCreation();
            }
            //Reset used distant static ID numbers to match NIF list order
            Dictionary<string, uint> NifMap = new Dictionary<string, uint>();
            uint count = 0;
            foreach (string name in UsedNifList) NifMap[name] = count++;
            List<StaticToRemove> UsedStaticsToRemove = new List<StaticToRemove>();
            //Determine floating point grass density
            float GrassDensity = (float)udStatGrassDensity.Value / 100.0f;
            foreach (KeyValuePair<string, Dictionary<string, StaticReference>> cellStatics in UsedStaticsList) {
                foreach (KeyValuePair<string, StaticReference> pair in cellStatics.Value) {
                    string nif_name = StaticsList[pair.Value.name].mesh;
                    if (NifMap.ContainsKey(nif_name)) pair.Value.staticID = NifMap[nif_name];
                    else UsedStaticsToRemove.Add(new StaticToRemove(cellStatics.Key, pair.Key));
                    if (nif_name.StartsWith("grass\\") || (OverrideList.ContainsKey (nif_name) && OverrideList[nif_name].Type == StaticType.Grass)) {
                        if (OverrideList.ContainsKey (nif_name)) {
                            if (OverrideList[nif_name].Density >= 0) GrassDensityThreshold (OverrideList[nif_name].Density, cellStatics, pair, rnd, UsedStaticsToRemove);
                            else GrassDensityThreshold (GrassDensity, cellStatics, pair, rnd, UsedStaticsToRemove);
                        } else GrassDensityThreshold (GrassDensity, cellStatics, pair, rnd, UsedStaticsToRemove);
                    }
                }
            }
            foreach (StaticToRemove key in UsedStaticsToRemove) UsedStaticsList[key.worldspace].Remove(key.reference);
            backgroundWorker.ReportProgress(4, strings["StaticsGenerate4"]);
            BinaryWriter bw = new BinaryWriter(File.Create(Statics.fn_usagedata), System.Text.Encoding.Default);
            bw.Write(UsedNifList.Count);
            bw.Write(UsedStaticsList[""].Count);
            //uint UseRef = 0;
            foreach (KeyValuePair<string, StaticReference> pair in UsedStaticsList[""]) pair.Value.Write(bw/*, UseRef++*/);
            UsedStaticsList[""].Clear();
            UsedStaticsList.Remove("");
            char[] cellName = new char[64];
            foreach (KeyValuePair<string, Dictionary<string, StaticReference>> cellStatics in UsedStaticsList) {
                bw.Write((int)(cellStatics.Value as Dictionary<string, StaticReference>).Count);
                int i; for (i = 0; i < 64; ++i) cellName[i] = '\0'; i = 0;
                foreach (char c in cellStatics.Key) cellName[i++] = c;
                bw.Write(cellName, 0, 64);
                foreach (KeyValuePair<string, StaticReference> pair in cellStatics.Value) pair.Value.Write(bw/*, UseRef++*/);
            }
            bw.Write((int)0);
            bw.Write((float)Convert.ToSingle(udStatMinSize.Value));
            bw.Close();
            
            if (!File.Exists(Statics.fn_statmesh)) return;
            setFinishDesc(4);
            backgroundWorker.ReportProgress(5, strings["StaticsGenerate5"]);
            {
                StaticTexCreator stc = new StaticTexCreator(args.MipSkip);
                BinaryReader br = new BinaryReader(File.OpenRead(Statics.fn_statmesh), System.Text.Encoding.Default);
                foreach (string name in UsedNifList) {
                    int nodes = br.ReadInt32();
                    br.BaseStream.Position += 16; //4 - radius, 12 - center
                    int type = br.BaseStream.ReadByte();
                    for (int j = 0; j < nodes; j++) {
                        br.BaseStream.Position += 40; //4 - radius, 12 - center, 12 - min, 12 - center
                        int verts = br.ReadInt32();
                        int faces = br.ReadInt32();
                        int vert_size = NativeMethods.GetCompressedVertSize();
                        br.BaseStream.Position += verts * vert_size + faces * 6;
                        short chars = br.ReadInt16();
                        string path = new string(br.ReadChars(chars - 1));
                        br.BaseStream.Position += 1;
                        try {
                            if (type != (int)StaticType.Grass && type != (int)StaticType.Tree)
                            {
                                bool ok = stc.LoadTexture(path);
                                if(!ok) warnings.Add("Warning: Texture '"+path+"' could not be converted to a distant texture, original texture will be used");
                            }
                        } catch (ArgumentException) {
                            //warnings.Add("Warning: Texture '"+path+"' on subset "+j+" of mesh '"+pair.Key+"' could not be found");
                        }
                    }
                }
                br.Close();
                stc.Dispose();
            }
            if (warnings.Count > 0) e.Result = warnings;
        }

        void workerFCreateStatics(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e != null) {
                if (e.Error != null) {
                    DumpError(e.Error);
                    MessageBox.Show(strings["StaticsError"] + "\n" + e.Error.Message);
                    ChangingPage = true;
                    Close();
                    return;
                }
                statusProgress.Value = 0;
                if (e.Result != null) {
                    warnings = (List<string>)e.Result;
                    allWarnings.AddRange(warnings);
                    saveWarnings("Statics");
                    if (!SetupFlags["AutoRun"]) {
                        statusWarnings.Text = warnings.Count + " " + strings["WarningCount"];
                        statusWarnings.Enabled = true;
                    }
                }
                if (DEBUG) allWarnings.Add("Distant statics created");
                statusText.Text = strings["StaticsStatus"];
                backgroundWorker.DoWork -= workerCreateStatics;
                backgroundWorker.RunWorkerCompleted -= workerFCreateStatics;
                SaveStatSettings();
                //Enable distant statics since the user generated them
                Statics.mf.cbDLDistantStatics.Checked = true;
            }
            if (!DEBUG && SetupFlags["AutoRun"] && allWarnings.Count > 0) {
                warnings.Clear();
                warnings.AddRange(allWarnings);
                statusWarnings.Text = warnings.Count + " " + strings["WarningCount"];
                statusWarnings.Enabled = true;
            }
            if (DEBUG) {
                warnings = new List<string>(allWarnings);
                statusWarnings.Text = warnings.Count + " " + strings["WarningCount"];
                statusWarnings.Enabled = true;
                File.AppendAllText(Statics.fn_dllog, "### DEBUG ###\r\n\r\n" + string.Join("\r\n", warnings.ToArray()) + "\r\n\r\n");
                //File.AppendAllText(Statics.fn_dllog, SlimDX.ObjectTable.ReportLeaks());
            }
            DirectoryInfo di = new DirectoryInfo(Statics.fn_dl);
            long fileSize = 0;
            int filecount = di.GetFiles().Length;
            int cells = ((filecount - 2) / 2);
            int statics;
            foreach (FileInfo fi in di.GetFiles()) fileSize += fi.Length;
            di = new DirectoryInfo(Statics.fn_statics);
            if (di.Exists) {
                statics = di.GetFiles().Length;
                foreach (FileInfo fi in di.GetFiles()) fileSize += fi.Length;
                filecount += statics;
            } else statics = 2;
            di = new DirectoryInfo(Statics.fn_stattex);
            if (di.Exists) {
                filecount += di.GetFiles().Length;
                foreach (FileInfo fi in di.GetFiles()) fileSize += fi.Length;
            }
            string summary = strings["Complete"] + "\r\n"
                + strings["TotalFiles"] + filecount + "\r\n"
                + strings["TotalSize"] + (fileSize / (1024 * 1024)) + " MB";/* + "\r\n"
                + "Total processed cells: " + cells + "\r\n"
                + "Total unique statics: " + (statics - 2);*/
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(5);
                lFinishDesc.Text += "________________________________________\r\n" + summary;
            }
            else lFinishDesc.Text = summary;
            try {
                File.AppendAllText(Statics.fn_dllog, "########################################\r\n" + summary);
            } catch { }
            bFinish.Enabled = true;
        }

        private struct ExportStaticsArgs {
            public string filename;
            public float MinSize;
            public bool activators;
            public bool misc;
        }

        void workerExportStatics(object sender, System.ComponentModel.DoWorkEventArgs e) {
            ExportStaticsArgs args = (ExportStaticsArgs)e.Argument;
            StaticsList.Clear();
            UsedStaticsList.Clear();
            StaticMap.Clear();
            foreach (string file in files) {
                BinaryReader br = new BinaryReader(File.OpenRead(file), System.Text.Encoding.Default);
                ParseFileForStatics(br, null, args.activators, args.misc, null);
                br.Close();
            }
            unsafe {
                NativeMethods.BeginStaticCreation((IntPtr)DXMain.device.ComPointer, null);
            }
            List<string> refsToRemove = new List<string>();
            foreach (KeyValuePair<string, Static> pair in StaticsList) {
                byte[] data;
                try { data = BSA.GetNif(pair.Value.mesh); } catch { data = null; }
                if (data == null) refsToRemove.Add(pair.Key);
                else {
                    try {
                        float size = NativeMethods.ProcessNif(data, data.Length, 1, 1, 1, 0);
                        if (size < 0) refsToRemove.Add(pair.Key);
                        else pair.Value.size = size;
                    } catch (Exception) { refsToRemove.Add(pair.Key); }
                }
            }
            foreach (string s in refsToRemove) StaticsList.Remove(s);
            foreach (string file in files) {
                BinaryReader br = new BinaryReader(File.OpenRead(file));
                try { ParseFileForCells2(br); } catch { }
                br.Close();
            }
            StreamWriter sw = new StreamWriter(args.filename, false);
            sw.WriteLine(": MGE distant statics list (for MGE 3.8.1 SVN rev.120 or later)\r\n"
                + "\r\n"
                + ": Syntax is <nif file name>=<keywords>\r\n"
                + ": Use 'ignore', 'auto', 'near', 'far' or 'very_far', to override the normal cutoff rules\r\n"
                + ": Use 'grass', 'grass_xxx' or 'tree' to force a mesh to render using the grass shader.  Meshes marked 'grass' and 'grass_xxx' will only render close by, and meshes marked with 'grass_xxx', where xxx is percentage of grass density, will be created with forced density, overriding global setting for this mesh during statics creation.  Note this will not keep Morrowind from drawing the mesh.  To do so, you will need to disable plugin using this grass or tree mesh in Morrowind Launcher.\r\n"
                + ": Use 'building' to cause a mesh to be treated as being twice as large as it really is for the purpose of classifying it as a near, far, or very far static, and determining whether it meets the minimum size criteria to be generated.\r\n"
                + ": Use 'no_script' to cause the disable script of objects using this mesh to be ignored\r\n"
                + ": Use 'use_old_reduction' to use the old mesh simplification algorithm\r\n"
                + ": Use 'reduction_xx' where xx is the desired percentage to override static simplification amount\r\n"
                + ": e.g. 'x\\ex_vivec_ps_01.nif=very_far reduction_50' will cause the mesh 'x\\ex_vivec_ps_01.nif' to always be visible and be reduced by 50%\r\n"
                + "\r\n"
                + ": Colon character (':') is treated as an inline comment. It can be used on any position of line and is delimited by the end of line\r\n"
                + ": Using old comment character '#' at the beginning of line is deprecated. Parser will try to process those lines, and eventually give warnings about deprecated use of comment\r\n"
                + ": All comments and blank lines will be completely ignored by MGE\r\n"
                + "\r\n"
                + ": If the same mesh is specified multiple times, the entry closest towards the end of this file will be used\r\n"
                + ": If a mesh is not specified at all, that static will obey the normal cutoff rules\r\n"
                + "\r\n"
                + ": Where multiple objects share the same mesh, individual objects can be enabled or disabled by adding the line [names] followed by a list of edid's, one per line\r\n"
                + ": Syntax is <object edid>[=<keyword>]\r\n"
                + ": Use 'enable' to make distant static of this object rendered even if its mesh is set to be ignored or it has disable script attached\r\n"
                + ": You may use 'disable' keyword or leave only the object edid alone (without '=') in line to disable creation of its distant static\r\n"
                + "\r\n"
                + ": There is possibility of adding (or removing) distant statics to interiors through exception list (feature added in MGE 3.8.0 SVN rev.112)\r\n"
                + ": To do it you need to add only cell name (for enabling) or cell name followed by keyword to [interiors] section\r\n"
                + ": Syntax is <cell name>[=<keyword>]\r\n"
                + ": Where keyword can be either 'enable' for enabling generation of distant statics for specified interior, or 'disable' for disabling generation of distant statics for previously enabled interior (also behaving like exterior)\r\n"
                + "\r\n"
                + ": The '\\' (backslash) character is treated specially in [names] and [interiors] sections. A character directly following it will have no special meaning, and won't be converted by MGE distant statics list parser\r\n"
                + ": To use a ':' (colon) character as a part of object edid, and not a comment, you must precede it by '\\'. Then to use also a '\\' character in edid, you must precede it by another '\\' (this only applies to other than main sections)\r\n"
                + "\r\n"
                + ": NOTE: This file needs UTF-8 character encoding for non-ASCII characters that can be used in name of file or entity or interior\r\n"
                + ": If you don't see here '«»' something like '<<>>' then your text editor's current character encoding is not set to UTF-8\r\n");
            sw.Write(": This list was generated with 'min. static size' = ");
            sw.WriteLine(args.MinSize);
            sw.WriteLine();
            foreach (KeyValuePair<string, Static> pair in StaticsList) {
                if (StaticMap.ContainsKey(pair.Key)) {
                    sw.Write(pair.Value.mesh);
                    if (pair.Value.mesh.StartsWith("grass\\")) sw.Write("=grass\t\t: size: ");
                    else if (pair.Value.mesh.StartsWith("trees\\")) sw.Write("=tree\t\t: size: ");
                    else if (pair.Value.mesh.StartsWith("x\\")) {
                        if (pair.Value.size * 2.0f >= args.MinSize) sw.Write("=building\t\t: size: ");
                        else sw.Write("=ignore\t\t: size: ");
                    } else {
                        if (pair.Value.size >= args.MinSize) {
                            if (pair.Value.mesh == "f\\active_blight_large.nif") sw.Write("=ignore\t\t: exception, size: ");
                            else sw.Write("=auto\t\t: size: ");
                        }
                        else sw.Write("=ignore\t\t: size: ");
                    }
                    sw.WriteLine(pair.Value.size);
                }
            }
            sw.WriteLine("\r\n[names]\r\nchargen boat\r\nchargen_plank");
            sw.Close();
        }

        void workerFExportStatics(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e.Error != null) {
                DumpError(e.Error);
                MessageBox.Show(strings["ExportListError"] + "\n" + e.Error.Message);
            }
            statusProgress.Value = 0;
            statusProgress.Style = ProgressBarStyle.Continuous;
            if (e.Result != null) {
                warnings = (List<string>)e.Result;
                saveWarnings("Export Statics");
                statusWarnings.Text = warnings.Count + " " + strings["WarningCount"];
                statusWarnings.Enabled = true;
            }
            statusText.Text = strings["ExportListStatus"];
            backgroundWorker.DoWork -= workerExportStatics;
            backgroundWorker.RunWorkerCompleted -= workerFExportStatics;
            bStatExportStatics.Enabled = true;
            bStatRun.Enabled = true;
            bStatSkip.Enabled = true;
        }

        /* Plugins tab properties */

        private static string datafiles;
        private List<string> pluginDirs;
        private MWPlugins pluginList;
        private string[] preselectedPlugins;
        private bool pluginListChanged = false;

        /* Plugins tab definitions */

        private class MWPlugin {

            public string Name;
            public string ShortName;
            public string FullName;
            public bool ESM;
            public DateTime LoadOrder;
            public CheckState Checked;
            public string Dir;

            public MWPlugin(FileInfo file) {
                ShortName = file.Name;
                Name = file.Name;
                FullName = file.FullName.ToLower(Statics.Culture);
                ESM = file.Extension.ToLower(Statics.Culture) == ".esm";
                LoadOrder = file.LastWriteTimeUtc;
                Checked = CheckState.Unchecked;
            }

            public MWPlugin(FileInfo file, string dir) {
                ShortName = file.Name;
                Name = file.Name + " > " + dir;
                FullName = file.FullName.ToLower(Statics.Culture);
                Dir = dir;
                ESM = file.Extension.ToLower(Statics.Culture) == ".esm";
                LoadOrder = file.LastWriteTimeUtc;
                Checked = CheckState.Unchecked;
            }

            public MWPlugin(FileInfo file, bool ESM) {
                ShortName = file.Name;
                Name = file.Name;
                FullName = file.FullName.ToLower(Statics.Culture);
                this.ESM = ESM;
                LoadOrder = file.LastWriteTimeUtc;
                Checked = CheckState.Unchecked;
            }

            public MWPlugin(FileInfo file, string dir, bool ESM) {
                ShortName = file.Name;
                Name = file.Name + " > " + dir;
                FullName = file.FullName.ToLower(Statics.Culture);
                Dir = dir;
                this.ESM = ESM;
                LoadOrder = file.LastWriteTimeUtc;
                Checked = CheckState.Unchecked;
            }

        }

        private class MWPlugins {

            public Dictionary<string, MWPlugin> Plugins;
            public List<string> Dirs;

            public MWPlugins(string main, List<string> dirs) {
                DirectoryInfo dir = new DirectoryInfo(main);
                datafiles = dir.FullName.ToLower(Statics.Culture);
                while (dirs.IndexOf(datafiles) != -1) dirs.Remove(datafiles);
                FileInfo[] files;
                Plugins = new Dictionary<string, MWPlugin>();
                Dirs = new List<string>(dirs);
                files = dir.GetFiles("*.esm");
                foreach (FileInfo file in files) Plugins.Add(file.Name.ToLower(Statics.Culture), new MWPlugin(file, true));
                files = dir.GetFiles("*.esp");
                foreach (FileInfo file in files) Plugins.Add(file.Name.ToLower(Statics.Culture), new MWPlugin(file, false));
                List<string> removeDirs = new List<string>();
                foreach (string dirName in Dirs) {
                    dir = new DirectoryInfo(dirName);
                    if (dir.Exists) {
                        files = dir.GetFiles("*.esm");
                        foreach (FileInfo file in files) Plugins.Add(file.Name.ToLower(Statics.Culture) + " > " + dirName, new MWPlugin(file, dirName, true));
                        files = dir.GetFiles("*.esp");
                        foreach (FileInfo file in files) Plugins.Add(file.Name.ToLower(Statics.Culture) + " > " + dirName, new MWPlugin(file, dirName, false));
                    } else removeDirs.Add(dirName);
                }
                foreach (string dirName in removeDirs) dirs.Remove(dirName);
            }

            public void SetDirs(List<string> dirs) {
                foreach (string dirName in Dirs) if (dirs.IndexOf(dirName) == -1) {
                    List<string> entries = new List<string>();
                    foreach (KeyValuePair<string, MWPlugin> entry in Plugins) if (entry.Value.Dir != null && dirName.CompareTo(entry.Value.Dir) == 0) entries.Add(entry.Key);
                    foreach (string entry in entries) Plugins.Remove(entry);
                }
                List<string> removeDirs = new List<string>();
                foreach (string dirName in dirs) if (Dirs.IndexOf(dirName) == -1) {
                    DirectoryInfo dir = new DirectoryInfo(dirName);
                    if (dir.Exists) {
                        FileInfo[] files = dir.GetFiles("*.esm");
                        foreach (FileInfo file in files) Plugins.Add(file.Name.ToLower(Statics.Culture) + " > " + dirName, new MWPlugin(file, dirName, true));
                        files = dir.GetFiles("*.esp");
                        foreach (FileInfo file in files) Plugins.Add(file.Name.ToLower(Statics.Culture) + " > " + dirName, new MWPlugin(file, dirName, false));
                    } else removeDirs.Add(dirName);
                }
                foreach (string dirName in removeDirs) dirs.Remove(dirName);
                Dirs.Clear();
                Dirs.AddRange(dirs);
            }

            public KeyValuePair<string, MWPlugin>[] ByName {
                get {
                    List<KeyValuePair<string, MWPlugin>> temp = new List<KeyValuePair<string, MWPlugin>>(Plugins);
                    temp.Sort(delegate(KeyValuePair<string, MWPlugin> firstPair, KeyValuePair<string, MWPlugin> nextPair) {
                        return firstPair.Value.ShortName.CompareTo(nextPair.Value.ShortName);
                    });
                    return temp.ToArray();
                }
            }

            public KeyValuePair<string, MWPlugin>[] ByType {
                get {
                    List<KeyValuePair<string, MWPlugin>> temp = new List<KeyValuePair<string, MWPlugin>>(Plugins);
                    temp.Sort(delegate(KeyValuePair<string, MWPlugin> firstPair, KeyValuePair<string, MWPlugin> nextPair) {
                        return ((firstPair.Value.ESM != nextPair.Value.ESM && firstPair.Value.ESM) ? -1 : (firstPair.Value.Dir == nextPair.Value.Dir ? firstPair.Value.ShortName.CompareTo(nextPair.Value.ShortName) : (firstPair.Value.Dir == null ? -1 : firstPair.Value.FullName.CompareTo(nextPair.Value.FullName))));
                    });
                    return temp.ToArray();
                }
            }

            public KeyValuePair<string, MWPlugin>[] ByLoadOrder {
                get {
                    List<KeyValuePair<string, MWPlugin>> temp = new List<KeyValuePair<string, MWPlugin>>(Plugins);
                    temp.Sort(delegate(KeyValuePair<string, MWPlugin> firstPair, KeyValuePair<string, MWPlugin> nextPair) {
                        return (firstPair.Value.ESM != nextPair.Value.ESM && firstPair.Value.ESM) ? -1 : firstPair.Value.LoadOrder.CompareTo(nextPair.Value.LoadOrder);
                    });
                    return temp.ToArray();
                }
            }

            public string[] getSelected() {
                List<string> s = new List<string>();
                foreach (KeyValuePair<string, MWPlugin> temp in Plugins) if (temp.Value.Checked == CheckState.Checked) s.Add(temp.Key);
                return s.ToArray();
            }
        }

        /* Plugins tab handlers */

        private void bPlugsFromINI_Click(object sender, EventArgs e) {
            StreamReader sr = new StreamReader(Statics.fn_mwini, System.Text.Encoding.Default);
            bool InModList = false;
            List<string> ActivePlugins = new List<string>();
            while (!sr.EndOfStream) {
                string s = sr.ReadLine().Trim().ToLower(Statics.Culture);
                if (s.Length == 0) continue;
                if (!InModList) {
                    if (s == "[game files]") InModList = true;
                } else {
                    if (s[0] == '[' && s.EndsWith("]")) {
                        InModList = false;
                        continue;
                    }
                    if (s.StartsWith("gamefile")) {
                        int index = s.IndexOf(';');
                        if (index != -1) s = s.Remove(index, s.Length - index);
                        index = s.IndexOf('=');
                        if (index != -1) {
                            s = s.Remove(0, index + 1).Trim();
                            ActivePlugins.Add(s);
                        }
                    }
                }
            }
            sr.Close();
            bPlugsClear_Click(sender, e);
            SelectPlugins(ActivePlugins.ToArray());
        }

        private void bPlugsRun_Click(object sender, EventArgs e) {
            //Check that at least one mod is selected
            if (clbPlugsModList.CheckedItems.Count == 0) {
                MessageBox.Show(strings["NoPluginsSelected"], Statics.strings["Error"]);
                return;
            }
            int i;
            //Create list of files
            files = new string[clbPlugsModList.CheckedItems.Count];
            if (files.Length != preselectedPlugins.Length) pluginListChanged = true;
            else {
                List<string> tmp1 = new List<string>(pluginList.getSelected());
                List<string> tmp2 = new List<string>(preselectedPlugins);
                tmp1.Sort();
                tmp2.Sort();
                for (i = 0; i < tmp1.Count; i++) if (tmp1[i].CompareTo(tmp2[i].ToLower(Statics.Culture)) != 0) {
                    pluginListChanged = true;
                    break;
                }
            }
            KeyValuePair<string, MWPlugin>[] list = pluginList.ByLoadOrder;
            i = 0;
            foreach (KeyValuePair<string, MWPlugin> item in list) if (item.Value.Checked == CheckState.Checked) {
                files[i++] = item.Value.FullName;
            }
            //Continue
            if (configure) startSetup();
            else {
                SetupFlags["ChkLandAuto"] = pluginListChanged || cmbMeshWorldDetail.SelectedIndex == -1;
                SetupFlags["EnaLandAuto"] = cmbMeshWorldDetail.SelectedIndex != -1;
                SetupFlags["EnaLandTex"] = Exists;
                SetupFlags["EnaLandMesh"] = Exists;
                RunSetupForm runSetupForm = new RunSetupForm(SetupFlags);
                runSetupForm.FormClosed += new FormClosedEventHandler(runSetupForm_FormClosed);
                runSetupForm.ShowDialog();
            }
        }

        private void clbPlugsModList_ItemCheck(object sender, System.Windows.Forms.ItemCheckEventArgs e) {
            pluginList.Plugins[clbPlugsModList.Items[e.Index].ToString().ToLower(Statics.Culture)].Checked = e.NewValue;
        }

        private void bPlugsClear_Click(object sender, EventArgs e) {
            if (clbPlugsModList.Items.Count > 0) for (int i = 0; i < clbPlugsModList.Items.Count; i++) clbPlugsModList.SetItemChecked(i, false);
        }

        private void bPlugsAll_Click(object sender, EventArgs e) {
            if (clbPlugsModList.Items.Count > 0) for (int i = 0; i < clbPlugsModList.Items.Count; i++) clbPlugsModList.SetItemChecked(i, true);
        }

        private void bPlugsDirs_Click(object sender, EventArgs e) {
            DirectoriesForm dirsForm = new DirectoriesForm(datafiles, pluginDirs);
            dirsForm.FormClosed += new FormClosedEventHandler(dirsForm_FormClosed);
            dirsForm.ShowDialog();
        }

        private void dirsForm_FormClosed(object sender, EventArgs e) {
            pluginList.SetDirs(pluginDirs);
            pluginsSort(sender, e);
        }

        private bool DEBUG = false;

        private void runSetupForm_FormClosed(object sender, EventArgs e) {
            if (SetupFlags["AutoRun"]) pluginListChanged = SetupFlags["ChkLandAuto"];
            DEBUG = SetupFlags["Debug"];
            if (SetupFlags["RunSetup"]) startSetup();
        }

        /* Plugins tab methods */

        private void pluginsSort(object sender, EventArgs e) {
            if (pluginList == null) return;
            KeyValuePair<string, MWPlugin>[] list;
            if (rbPlugsName.Checked) list = pluginList.ByName;
            else if (rbPlugsType.Checked) list = pluginList.ByType;
            else list = pluginList.ByLoadOrder;
            clbPlugsModList.Items.Clear();
            foreach (KeyValuePair<string, MWPlugin> item in list) {
                int index = clbPlugsModList.Items.Count;
                clbPlugsModList.Items.Add(item.Value.Name);
                clbPlugsModList.SetItemCheckState(index, item.Value.Checked);
            }
        }

        private void SelectPlugins(string[] plugins) {
            foreach (string s in plugins) {
                if (!pluginList.Plugins.ContainsKey(s.ToLower(Statics.Culture))) continue;
                int index = clbPlugsModList.Items.IndexOf(pluginList.Plugins[s.ToLower(Statics.Culture)].Name);
                if (index != -1) clbPlugsModList.SetItemChecked(index, true);
            }
        }

        private void startSetup() {
            ChangingPage = true;
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(0);
                tabControl.SelectedIndex = 4;
            }
            else tabControl.SelectedIndex = 1;
            if (DEBUG) allWarnings.Add("Loading plugin land data");
            statusText.Text = strings["LoadLandData"];
            statusProgress.Maximum = clbPlugsModList.Items.Count;
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.DoWork += workerLoadPlugins;
            backgroundWorker.RunWorkerCompleted += workerFLoadPlugins;
            statusWarnings.Text = strings["NoWarnings"]; 
            statusWarnings.Enabled = false;
            backgroundWorker.RunWorkerAsync();
        }

        /* Land texture tab handlers */

        private void bTexSkip_Click(object sender, EventArgs e) {
            if (!Exists) {
                MessageBox.Show(strings["CantSkipLand"], Statics.strings["Error"]);
                return;
            }
            int VertsRequired = (MapSize * 2 + 1) * (MapSize * 2 + 1) * 64 * 64 + (MapSize * 2 + 1) * 128 + 1;
            int PrimsRequired = (MapSize * 2 + 1) * (MapSize * 2 + 1) * 64 * 64 * 2;
            int index = 0;
            while ((VertsRequired > DXMain.mCaps.MaxIndicies || PrimsRequired > DXMain.mCaps.MaxPrimitives) && ++index < cmbMeshWorldDetail.Items.Count - 1) {
                VertsRequired /= 4;
                PrimsRequired /= 4;
            }
            if (pluginListChanged || cmbMeshWorldDetail.SelectedIndex == -1) {
                cmbMeshWorldDetail_auto = true;
                cmbMeshWorldDetail.SelectedIndex = index;
                cmbMeshWorldDetail.SelectedIndexChanged += new EventHandler(cmbMeshWorldDetail_SelectedIndexChanged);
                lMeshAutoInfo.Visible = true;
                if (DEBUG) allWarnings.Add("World mesh auto-calculated to " + cmbMeshWorldDetail.Text);
            } else lMeshAutoInfo.Visible = false;
            LTEX.ReleaseCache();
            statusText.Text = strings["LandTextureSkip"];
            statusWarnings.Text = strings["NoWarnings"];
            statusWarnings.Enabled = false;
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(2);
                if (SetupFlags["ChkLandMesh"]) bMeshRun_Click(null, null);
                else bMeshSkip_Click(null, null);
            } else {
                ChangingPage = true;
                tabControl.SelectedIndex = 2;
                bMeshRun.Enabled = true;
                bMeshSkip.Enabled = true;
            }
        }

        private void bTexRun_Click(object sender, EventArgs e) {
            if ((128 << cmbTexWorldResolution.SelectedIndex > DXMain.mCaps.MaxTexSize) || (128 << cmbTexWorldNormalRes.SelectedIndex > DXMain.mCaps.MaxTexSize)) {
                MessageBox.Show(strings["TexResError"], Statics.strings["Error"]);
                return;
            }
            //Set max mesh detail here
            int VertsRequired = (MapSize * 2 + 1) * (MapSize * 2 + 1) * 64 * 64 + (MapSize * 2 + 1) * 128 + 1;
            int PrimsRequired = (MapSize * 2 + 1) * (MapSize * 2 + 1) * 64 * 64 * 2;
            int index = 0;
            while ((VertsRequired > DXMain.mCaps.MaxIndicies || PrimsRequired > DXMain.mCaps.MaxPrimitives) && ++index < cmbMeshWorldDetail.Items.Count - 1) {
                VertsRequired /= 4;
                PrimsRequired /= 4;
            }
            if (pluginListChanged || cmbMeshWorldDetail.SelectedIndex == -1) {
                cmbMeshWorldDetail_auto = true;
                cmbMeshWorldDetail.SelectedIndex = index;
                cmbMeshWorldDetail.SelectedIndexChanged += new EventHandler(cmbMeshWorldDetail_SelectedIndexChanged);
                lMeshAutoInfo.Visible = true;
                if (DEBUG) allWarnings.Add("World mesh auto-calculated to " + cmbMeshWorldDetail.Text);
            }
            else lMeshAutoInfo.Visible = false;
            if (!SetupFlags["AutoRun"]) {
                ChangingPage = true;
                tabControl.SelectedIndex = 2;
            }
            if (DEBUG) allWarnings.Add("Creating world textures");
            statusText.Text = strings["LandTextureCreate"];
            statusProgress.Maximum = (MapMaxY - MapMinY + 1) * 2;
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.DoWork += workerCreateTextures;
            backgroundWorker.RunWorkerCompleted += workerFCreateTextures;
            statusWarnings.Text = strings["NoWarnings"];
            statusWarnings.Enabled = false;
            CreateTextureArgs args = new CreateTextureArgs();
            args.WorldRes = 128 << cmbTexWorldResolution.SelectedIndex;
            args.WorldNormal = 128 << cmbTexWorldNormalRes.SelectedIndex;
            args.twoStep = cbTexTwoStep.Checked;
            backgroundWorker.RunWorkerAsync(args);
        }

        /* Land mesh tab properties */

        private bool cmbMeshWorldDetail_auto = false;

        /* Land mesh tab handlers */

        private void cmbMeshWorldDetail_SelectedIndexChanged(object sender, EventArgs e) {
            cmbMeshWorldDetail_auto = false;
            cmbMeshWorldDetail.SelectedIndexChanged -= cmbMeshWorldDetail_SelectedIndexChanged;
        }

        private void bMeshRun_Click(object sender, EventArgs e) {
            if (lbStatOverrideList.Items.Count == 0) lStatOverrideList.Visible = true;
            if (!SetupFlags["AutoRun"]) {
                ChangingPage = true;
                tabControl.SelectedIndex = 3;
            }
            if (DEBUG) allWarnings.Add("Creating world meshes");
            statusText.Text = strings["LandMeshCreate"];
            statusProgress.Maximum = 100;
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.DoWork += workerCreateMeshes;
            backgroundWorker.RunWorkerCompleted += workerFCreateMeshes;
            statusWarnings.Text = strings["NoWarnings"];
            statusWarnings.Enabled = false;
            CreateMeshArgs cma = new CreateMeshArgs();
            cma.MeshDetail = cmbMeshWorldDetail.SelectedIndex;
            backgroundWorker.RunWorkerAsync(cma);
        }

        private void bMeshSkip_Click(object sender, EventArgs e) {
            if (!Exists) {
                MessageBox.Show(strings["CantSkipMesh"], Statics.strings["Error"]);
                return;
            }
            LTEX.ReleaseCache();
            statusText.Text = strings["LandMeshSkip"];
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(3);
                if (SetupFlags["ChkStatics"]) bStatRun_Click(null, null);
                else bStatSkip_Click(null, null);
            } else {
                if (lbStatOverrideList.Items.Count == 0) lStatOverrideList.Visible = true;
                ChangingPage = true;
                tabControl.SelectedIndex = 3;
                statusWarnings.Text = strings["NoWarnings"];
                statusWarnings.Enabled = false;
                bStatExportStatics.Enabled = true;
                bStatRun.Enabled = true;
                bStatSkip.Enabled = true;
            }
        }

        private static void GenerateMesh(LAND land, string path) {
            Directory.CreateDirectory(Path.GetDirectoryName(path));
            BinaryWriter bw = new BinaryWriter(File.Create(path));
            for (int x = 0; x < 65; x++) {
                for (int y = 0; y < 65; y++) {
                    bw.Write((float)(x * 128));
                    bw.Write((float)(y * 128));
                    bw.Write((float)(land.Heights[x, y] * 8));
                    bw.Write(land.Normals[x, y].X);
                    bw.Write(land.Normals[x, y].Y);
                    bw.Write(land.Normals[x, y].Z);
                    //Need to offset the border texcoords slightly to avoid lines between meshes
                    if (x == 0) bw.Write(0.005f);
                    else if (x == 64) bw.Write(0.997f);
                    else bw.Write((float)x / 64.0f);
                    if (y == 0) bw.Write(0.005f);
                    else if (y == 64) bw.Write(0.997f);
                    else bw.Write((float)y / 64.0f);
                }
            }
            bw.Close();
        }

        /* Land mesh methods */

        private void GenerateWorldMesh(int detail, string path) {
            int vCount = 64 / (1 << detail);
            float vSpacing = 128f * (float)(1 << detail);
            int VertsAcross = (MapMaxX - MapMinX + 1) * vCount;
            int VertsDown = (MapMaxY - MapMinY + 1) * vCount;
            int tFaces = (VertsAcross - 1) * (VertsDown - 1) * 2;
            int tVerts = VertsAcross * VertsDown;
            float texMultX = 1 / (float)VertsAcross;
            float texMultY = 1 / (float)VertsDown;
            //Generate optimized landscape mesh
            int MapSpanX = MapMaxX - MapMinX + 1;
            int MapSpanY = MapMaxY - MapMinY + 1;
            int MapOffsetX = 0 - MapMinX;
            int MapOffsetY = 0 - MapMinY;
            int DataSpanX = MapSpanX * 64;
            int DataSpanY = MapSpanY * 64;
            float[] height_data = new float[DataSpanX * DataSpanY];
            for (int y1 = MapMinY; y1 <= MapMaxY; y1++) {
                for (int y2 = 0; y2 < 64; y2++) {
                    for (int x1 = MapMinX; x1 <= MapMaxX; x1++) {
                        for (int x2 = 0; x2 < 64; x2++) {
                            int y = (y1 + MapOffsetY) * 64 + y2;
                            int x = (x1 + MapOffsetX) * 64 + x2;
                            if (map[x1, y1] != null && x1 > map.GetLowerBound(0) && x1 < map.GetUpperBound(0) && y1 > map.GetLowerBound(1) && y1 < map.GetUpperBound(1)) {
                                height_data[y * DataSpanX + x] = (float)map[x1, y1].Heights[x2, y2] * 8.0f;
                            } else height_data[y * DataSpanX + x] = -2048.0f;
                        }
                    }
                }
            }
            float left = ((float)MapMinX * 64) * 128.0f;
            float right = ((float)(MapMaxX * 64 + 64)) * 128.0f;
            float bottom = ((float)MapMinY * 64) * 128.0f;
            float top = ((float)(MapMaxY * 64 + 64)) * 128.0f;
            backgroundWorker.ReportProgress(10, strings["LandTessellating"]);
            float et = 125.0f;
            switch (detail) {
                case 0:
                    et = 15.0f;
                    break;
                case 1:
                    et = 70.0f;
                    break;
                case 2:
                    et = 125.0f;
                    break;
                case 3:
                    et = 180.0f;
                    break;
                case 4:
                    et = 235.0f;
                    break;
            }
            NativeMethods.TessellateLandscape(path, height_data, (uint)DataSpanY, (uint)DataSpanX, top, left, bottom, right, et);
        }

        /* Statics tab properties */

        private readonly Dictionary<string, Static> StaticsList = new Dictionary<string, Static>();
        private readonly Dictionary<string, Dictionary<string, StaticReference>> UsedStaticsList = new Dictionary<string,Dictionary<string,StaticReference>>();
        private readonly Dictionary<string, uint> StaticMap = new Dictionary<string, uint>();
        private readonly Dictionary<string, bool> DisableScripts = new Dictionary<string, bool>();

        /* Statics tab definitions */

        public enum StaticType {
            Auto = 0,
            Near = 1,
            Far = 2,
            VeryFar = 3,
            Grass = 4,
            Tree = 5,
            Building = 6
        };

        private struct StaticToRemove {

            public readonly string worldspace;
            public readonly string reference;

            public StaticToRemove(string Worldspace, string Reference) {
                worldspace = Worldspace;
                reference = Reference;
            }

        }

        private class Static {

            public readonly string name;
            public readonly string mesh;
            public float size;

            public Static(string Name, string Mesh) {
                name = Name.ToLower(Statics.Culture);
                mesh = Mesh.ToLower(Statics.Culture);
                size = 0;
            }

        }

        private class StaticReference {

            public string name;
            public float x, y, z;
            public float yaw, pitch, roll;
            public float scale;
            public uint staticID;

            public void SetID(Dictionary<string, Static> StaticsList, Dictionary<string, uint> StaticMap) {
                string file = StaticsList[name].mesh;
                if (StaticMap.ContainsKey(file)) staticID = StaticMap[file];
                else {
                    staticID = (uint)StaticMap.Count;
                    StaticMap[file] = staticID;
                }
            }

            public void Write(BinaryWriter bw) {
                bw.Write(staticID);
                bw.Write(x);
                bw.Write(y);
                bw.Write(z);
                bw.Write(yaw);
                bw.Write(pitch);
                bw.Write(roll);
                bw.Write(scale);
            }

        }

        private struct staticOverride {

            public bool Ignore;
            public StaticType Type;
            public bool OldSimplify;
            public bool overrideSimplify;
            public float Simplify;
            public float Density;
            public bool StaticsOnly;
            public bool NoScript;
            public bool NamesNoIgnore;

            public staticOverride(byte value) {
                OldSimplify = false;
                Simplify = 1;
                Density = -1;
                overrideSimplify = false;
                Ignore = false;
                StaticsOnly = false;
                Type = StaticType.Auto;
                NoScript = false;
                NamesNoIgnore = false;
                switch (value) {
                    case 0:
                        Ignore = true;
                        break;
                    case 1:
                        Type = StaticType.Near;
                        break;
                    case 2:
                        Type = StaticType.Far;
                        break;
                    case 3:
                        break;
                    case 4:
                        overrideSimplify = true;
                        Type = StaticType.Near;
                        break;
                    case 5:
                        overrideSimplify = true;
                        Type = StaticType.Far;
                        break;
                    case 6:
                        overrideSimplify = true;
                        break;
                }
            }

            public staticOverride(string value) {
                Ignore = false;
                Type = StaticType.Auto;
                OldSimplify = false;
                overrideSimplify = false;
                Simplify = 1;
                Density = -1;
                StaticsOnly = false;
                NoScript = false;
                NamesNoIgnore = false;
                string[] keys = value.ToLowerInvariant().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                foreach (string s in keys) {
                    if (s == "ignore") Ignore = true;
                    else if (s == "near") Type = StaticType.Near;
                    else if (s == "auto") Type = StaticType.Auto;
                    else if (s == "far") Type = StaticType.Far;
                    else if (s == "very_far") Type = StaticType.VeryFar;
                    else if (s.StartsWith ("grass")) {
                        float percent;
                        Type = StaticType.Grass;
                        if (s.Length > 6 && float.TryParse (s.Remove (0, 6), out percent) && percent >= 0) {
                            if (percent > 100) Density = 1.0f;
                            else Density = percent / 100.0f;
                        }
                    } else if (s == "tree") Type = StaticType.Tree;
                    else if (s == "building") Type = StaticType.Building;
                    else if (s == "no_script") NoScript = true;
                    else if (s == "use_old_reduction") OldSimplify = true;
                    else if (s.StartsWith ("reduction_")) {
                        float percent;
                        if (float.TryParse (s.Remove (0, 10), out percent) && percent >= 0 && percent <= 100) {
                            overrideSimplify = true;
                            Simplify = percent / 100.0f;
                        }
                    } else if (s == "static_only") StaticsOnly = true;
                }
            }

            public staticOverride(staticOverride value, bool enabledInNames) {
                OldSimplify = value.OldSimplify;
                Simplify = value.Simplify;
                Density = value.Density;
                overrideSimplify = value.overrideSimplify;
                Ignore = value.Ignore;
                StaticsOnly = value.StaticsOnly;
                Type = value.Type;
                NoScript = value.NoScript;
                NamesNoIgnore = enabledInNames;
            }

        }

        /* Statics tab handlers */

        private void bStatExportStatics_Click(object sender, EventArgs e) {
            if (saveStaticListDialog.ShowDialog() != DialogResult.OK) return;
            bStatExportStatics.Enabled = false;
            bStatSkip.Enabled = false;
            bStatRun.Enabled = false;
            ExportStaticsArgs args = new ExportStaticsArgs();
            args.filename = saveStaticListDialog.FileName;
            args.activators = cbStatActivators.Checked;
            args.misc = cbStatIncludeMisc.Checked;
            args.MinSize = (ushort)udStatMinSize.Value;
            statusText.Text = "Exporting list of statics";
            statusProgress.Style = ProgressBarStyle.Marquee;
            backgroundWorker.WorkerReportsProgress = false;
            backgroundWorker.DoWork += workerExportStatics;
            backgroundWorker.RunWorkerCompleted += workerFExportStatics;
            backgroundWorker.RunWorkerAsync(args);
        }

        private void bStatSkip_Click(object sender, EventArgs e) {
            if (!SetupFlags["AutoRun"]) {
                if (!StaticsExist && MessageBox.Show(strings["ConfirmSkipStatics"],
                    Statics.strings["Warning"], MessageBoxButtons.YesNo) != DialogResult.Yes) return;
                ChangingPage = true;
                tabControl.SelectedIndex = 4;
            }
            statusText.Text = strings["StaticsSkip"];
            statusWarnings.Text = strings["NoWarnings"];
            statusWarnings.Enabled = false;
            workerFCreateStatics(null, null);
        }

        private void bStatRun_Click(object sender, EventArgs e) {
            if (StaticsExist) {
                if (!SetupFlags["AutoRun"] && MessageBox.Show(strings["ConfirmRecreate"],
                    Statics.strings["Warning"], MessageBoxButtons.YesNo) != DialogResult.Yes) return;
                Directory.Delete(Statics.fn_statics, true);
            }
            ushort temp = (ushort)udStatMinSize.Value;
            CreateStaticsArgs csa = new CreateStaticsArgs();
            csa.MinSize = temp;
            //Save the value of the minimum static size to the main screen
            Statics.mf.tbDLNearSize.Text = udStatMinSize.Text;
            switch (cmbStatSimplifyMeshes.SelectedIndex) {
                case 1:
                    csa.simplify = 0.9f;
                    break;
                case 2:
                    csa.simplify = 0.75f;
                    break;
                case 3:
                    csa.simplify = 0.5f;
                    break;
                case 4:
                    csa.simplify = 0.25f;
                    break;
                default:
                    csa.simplify = 1.0f;
                    break;
            }
            csa.MipSkip = cmbStatSkipMipLevels.SelectedIndex;
            csa.activators = cbStatActivators.Checked;
            csa.misc = cbStatIncludeMisc.Checked;
            csa.oldSimplify = false;
            csa.useOverrideList = cbStatOverrideList.Checked;
            csa.OverrideList = new List<string>();
            csa.OverrideList.Add(Statics.fn_dldefaultoverride);
            foreach (string s in lbStatOverrideList.Items) csa.OverrideList.Add(s);
            if (!SetupFlags["AutoRun"]) {
                ChangingPage = true;
                tabControl.SelectedIndex = 4;
            }
            if (DEBUG) allWarnings.Add("Parsing plugins for possible statics");
            statusText.Text = strings["StaticsGenerate1"];
            statusProgress.Style = ProgressBarStyle.Continuous;
            statusProgress.Maximum = 6;
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.DoWork += workerCreateStatics;
            backgroundWorker.RunWorkerCompleted += workerFCreateStatics;
            statusWarnings.Text = strings["NoWarnings"];
            statusWarnings.Enabled = false;
            backgroundWorker.RunWorkerAsync(csa);
        }

        private void bStatOverrideList_Click(object sender, EventArgs e) {
            (new OverrideListForm(lbStatOverrideList, lStatOverrideList)).ShowDialog();
        }

        /* Statics tab methods */

        private void ParseFileForDisableScripts(BinaryReader br, Dictionary<string, staticOverride> OverrideList) {
            string s = "";
            while (br.BaseStream.Position < br.BaseStream.Length) {
                s = ReadString(br);
                int size = br.ReadInt32();
                br.BaseStream.Position += 8;
                if (s == "SCPT") {
                    int read = 0;
                    string text = null;
                    string name = null;
                    while (read < size) {
                        s = ReadString(br);
                        int size2 = br.ReadInt32();
                        read += size2 + 8;
                        long next_pos = br.BaseStream.Position + size2;
                        switch (s) {
                            case "SCHD":
                                name = ReadCString(br).ToLower(Statics.Culture);
                                break;
                            case "SCTX":
                                text = s = new string(br.ReadChars(size2));
                                text = text.ToLower(Statics.Culture);
                                break;
                        }
                        br.BaseStream.Position = next_pos;
                    }
                    if (name != null && text != null) {
                        if (name == "ghostfencescript") {
                            continue;
                        }
                        if (text.Contains("disable")) DisableScripts[name] = true;
                    }
                } else br.BaseStream.Position += size;
            }
        }

        private void ParseFileForStatics(BinaryReader br, Dictionary<string, staticOverride> OverrideList, bool activators, bool includemisc, Dictionary<string, bool> IgnoreList) {
            int DEBUG_statics = 0;
            int DEBUG_ignored = 0;
            //Look for any scripts that might be disabling activators
            if (activators) {
                ParseFileForDisableScripts(br, OverrideList);
                //Rest file position
                br.BaseStream.Position = 0;
            }
            string s = "";
            while (br.BaseStream.Position < br.BaseStream.Length) {
                s = ReadString(br);
                int size = br.ReadInt32();
                br.BaseStream.Position += 8;
                if (s == "STAT" || s == "ACTI" || s == "DOOR" || s == "CONT" || s == "LIGH") {
                    int read = 0;
                    bool activator = s == "ACTI";
                    bool misc = s == "DOOR" || s == "CONT" || s == "LIGH";
                    string name = null;
                    string model = null;
                    string script = null;
                    while (read < size) {
                        s = ReadString(br);
                        int size2 = br.ReadInt32();
                        read += size2 + 8;
                        switch (s) {
                            case "NAME":
                                name = ReadCString(br).ToLower(Statics.Culture);
                                break;
                            case "MODL":
                                model = ReadCString(br).ToLower(Statics.Culture);
                                break;
                            case "SCRI":
                                script = ReadCString(br).ToLower(Statics.Culture);
                                break;
                            default:
                                br.BaseStream.Position += size2;
                                break;
                        }
                    }
                    if (name != null && model != null && model.Trim () != null) {
                        //Named exceptions
                        if (IgnoreList != null && IgnoreList.ContainsKey(name)) {
                            if (!IgnoreList[name]) {
                                StaticsList[name] = new Static(name, model);
                                if (OverrideList != null && OverrideList.ContainsKey(model) && OverrideList[model].Ignore) {
                                    OverrideList[model] = new staticOverride(OverrideList[model], true);
                                    if (DEBUG) { DEBUG_statics++; continue; }
                                }
                            }
                            if (DEBUG) DEBUG_ignored++;
                            continue;
                        }
                        //NoScript override
                        if (script != null && OverrideList != null && OverrideList.ContainsKey(model) && OverrideList[model].NoScript) {
                            script = null;
                        }
                        //Special exceptions
                        if (name == "chargen boat" || name == "chargen_plank") {
                            if (DEBUG) DEBUG_ignored++;
                            continue;
                        }
                        //Special model exceptions
                        if (model == "f\\active_blight_large.nif") {
                            if (OverrideList != null && !OverrideList.ContainsKey(model)) {
                                if (DEBUG) DEBUG_ignored++;
                                continue;
                            }
                        }
                        if ((misc && !includemisc) || activator && !activators) {
                            if (OverrideList != null && OverrideList.ContainsKey(model) && !OverrideList[model].Ignore) {
                                if (script != null && DisableScripts != null && DisableScripts.ContainsKey(script) && DisableScripts[script] == true) {
                                    if (DEBUG) DEBUG_ignored++;
                                    continue;
                                }
                                StaticsList[name] = new Static(name, model);
                                if (DEBUG) DEBUG_statics++;
                            }
                        } else {
                            if (OverrideList == null || !OverrideList.ContainsKey(model) || !OverrideList[model].Ignore) {
                                if (script != null && DisableScripts != null && DisableScripts.ContainsKey(script) && DisableScripts[script] == true) {
                                    if (DEBUG) DEBUG_ignored++;
                                    continue;
                                }
                                StaticsList[name] = new Static(name, model);
                                if (DEBUG) DEBUG_statics++;
                            }
                        }
                    }
                } else br.BaseStream.Position += size;
            }
            if (DEBUG) allWarnings.Add("Static definitions: " + DEBUG_statics + "; Ignored definitions: " + DEBUG_ignored);
        }

        private void ParseFileForCells(BinaryReader br, string PluginName, Dictionary<string, bool> IgnoreList, Dictionary<string, bool> CellList) {
            List<string> Masters = new List<string>() { PluginName.ToLower(Statics.Culture) };
            if (DEBUG) allWarnings.Add("PLUGIN=" + Masters[0]);
            int DEBUG_cells = 0;
            int DEBUG_refs = 0;
            int DEBUG_added = 0;
            int DEBUG_moved = 0;
            int DEBUG_deleted = 0;
            while (br.BaseStream.Position < br.BaseStream.Length) {
                string s = ReadString(br);
                int size = br.ReadInt32();
                br.BaseStream.Position += 8;
                switch (s) {
                    case "TES3":
                        int read = 0;
                        while (read < size) {
                            s = ReadString(br);
                            int size2 = br.ReadInt32();
                            read += size2 + 8;
                            long pos = br.BaseStream.Position;
                            switch (s) {
                                case "MAST":
                                    Masters.Add(ReadCString(br, size2).ToLower(Statics.Culture));
                                    if (DEBUG) allWarnings.Add("MASTER[" + (Masters.Count - 1) + "]=" + Masters[Masters.Count-1]);
                                    break;
                            }
                            br.BaseStream.Position = pos + size2;
                        }
                        break;
                    case "CELL":
                        if (DEBUG) DEBUG_cells++;
                        string CellName = "";
                        bool IsValidCell = false;
                        bool InReference = false;
                        bool ReferenceHasScale = false;
                        bool ReferenceDeleted = false;
                        bool ReadData = false;
                        bool Interior = false;
                        uint RefID = 0;
                        int MastID = 0;
                        int CellX = 0;
                        int CellY = 0;
                        StaticReference sr = new StaticReference();
                        read = 0;
                        while (read < size) {
                            s = ReadString(br);
                            int size2 = br.ReadInt32();
                            read += size2 + 8;
                            long pos = br.BaseStream.Position;
                            switch (s) {
                                case "DATA":
                                    if (!InReference) {
                                        if (ReadData) break;
                                        uint flags = br.ReadUInt32();
                                        if ((flags & 0x01) == 0 || (cbStatIntExt.Checked && (flags & 0x81) == 0x81) || (cbStatIntWater.Checked && (flags & 0x83) == 0x03)) IsValidCell = true;
                                        if ((flags & 0x01) != 0) {
                                            Interior = true;
                                            if (CellList.ContainsKey(CellName.ToLower(Statics.Culture))) IsValidCell = CellList[CellName.ToLower(Statics.Culture)];
                                        }
                                        else Interior = false;
                                        CellX = br.ReadInt32();
                                        CellY = br.ReadInt32();
                                        ReadData = true;
                                    } else {
                                        sr.x = br.ReadSingle();
                                        sr.y = br.ReadSingle();
                                        sr.z = br.ReadSingle();
                                        sr.yaw = br.ReadSingle();
                                        sr.pitch = br.ReadSingle();
                                        sr.roll = br.ReadSingle();
                                    }
                                    break;
                                case "FRMR":
                                    if (DEBUG) DEBUG_refs++;
                                    if (!IsValidCell) break;
                                    if (InReference) {
                                        if (!ReferenceHasScale) sr.scale = 1;
                                        if (StaticsList.ContainsKey(sr.name) && (!IgnoreList.ContainsKey(sr.name) || !IgnoreList[sr.name])) {
                                            sr.SetID(StaticsList, StaticMap);
                                            string Worldspace = Interior ? CellName : "";
                                            string Reference = Masters[MastID] + "\u0001" + (Interior ? "" : CellX + "\u0002" + CellY + "\u0001") + RefID;
                                            if (ReferenceDeleted) {
                                                if (UsedStaticsList.ContainsKey(Worldspace) && UsedStaticsList[Worldspace].ContainsKey(Reference)) UsedStaticsList[Worldspace].Remove(Reference);
                                            }
                                            else {
                                                if (!UsedStaticsList.ContainsKey(Worldspace)) UsedStaticsList.Add(Worldspace, new Dictionary<string, StaticReference>());
                                                UsedStaticsList[Worldspace][Reference] = sr;
                                            }
                                            if (DEBUG) {
                                                if (ReferenceDeleted) ++DEBUG_deleted;
                                                else if (MastID > 0) ++DEBUG_moved;
                                                else ++DEBUG_added;
                                            }
                                        }
                                    }
                                    RefID = br.ReadUInt32();
                                    MastID = (int)(RefID >> 24);
                                    RefID &= 0x00FFFFFF;
                                    sr = new StaticReference();
                                    InReference = true;
                                    ReferenceHasScale = false;
                                    ReferenceDeleted = false;
                                    break;
                                case "DELE":
                                    ReferenceDeleted = true;
                                    break;
                                case "NAME":
                                    if (InReference) sr.name = ReadCString(br, size2).ToLower(Statics.Culture);
                                    else CellName = ReadCString(br, size2);
                                    break;
                                case "XSCL":
                                    if (!InReference) break;
                                    sr.scale = br.ReadSingle();
                                    ReferenceHasScale = true;
                                    break;
                            }
                            br.BaseStream.Position = pos + size2;
                        }
                        if (InReference) {
                            if (!ReferenceHasScale) sr.scale = 1;
                            if (StaticsList.ContainsKey(sr.name) && (!IgnoreList.ContainsKey(sr.name) || !IgnoreList[sr.name])) {
                                sr.SetID(StaticsList, StaticMap);
                                string Worldspace = Interior ? CellName : "";
                                string Reference = Masters[MastID] + "\u0001" + (Interior ? "" : CellX + "\u0002" + CellY + "\u0001") + RefID;
                                if (ReferenceDeleted) {
                                    if (UsedStaticsList.ContainsKey(Worldspace) && UsedStaticsList[Worldspace].ContainsKey(Reference)) UsedStaticsList[Worldspace].Remove(Reference);
                                }
                                else {
                                    if (!UsedStaticsList.ContainsKey(Worldspace)) UsedStaticsList.Add(Worldspace, new Dictionary<string, StaticReference>());
                                    UsedStaticsList[Worldspace][Reference] = sr;
                                }
                                if (DEBUG) {
                                    if (ReferenceDeleted) ++DEBUG_deleted;
                                    else if (MastID > 0) ++DEBUG_moved;
                                    else ++DEBUG_added;
                                }
                            }
                        }
                        break;
                    default:
                        br.BaseStream.Position += size;
                        break;
                }
            }
            if (DEBUG) allWarnings.Add("Scanning summary for: " + PluginName + " : " + DEBUG_cells + " cells : " + DEBUG_refs + " refs : " + DEBUG_added + " added : " + DEBUG_moved + " moved : " + DEBUG_deleted + " deleted");
        }

        private void ParseFileForCells2(BinaryReader br) {
            string s = "";
            while (br.BaseStream.Position < br.BaseStream.Length) {
                s = ReadString(br);
                int size = br.ReadInt32();
                br.BaseStream.Position += 8;
                if (s == "CELL") {
                    bool IsValidCell = false;
                    bool InReference = false;
                    bool ReadData = false;
                    int read = 0;
                    long end = br.BaseStream.Position + size;
                    while (read < size) {
                        s = ReadString(br);
                        int size2 = br.ReadInt32();
                        read += size2 + 8;
                        switch (s) {
                            case "DATA":
                                if (!InReference && !ReadData) {
                                    uint flags = br.ReadUInt32();
                                    if ((flags & 0x1) == 0 || (cbStatIntExt.Checked && (flags & 0x81) == 0x81) || (cbStatIntWater.Checked && (flags & 0x83) == 0x03)) IsValidCell = true;
                                    else {
                                        read = size;
                                        br.BaseStream.Position = end;
                                        break;
                                    }
                                    br.BaseStream.Position += 8;
                                    ReadData = true;
                                    break;
                                } else goto default;
                            case "FRMR":
                                if (!IsValidCell) goto default;
                                br.ReadInt32();
                                InReference = true;
                                break;
                            case "NAME":
                                if (!InReference) goto default;
                                string sname = ReadCString(br).ToLower(Statics.Culture);
                                if (StaticsList.ContainsKey(sname)) StaticMap[sname] = 1;
                                break;
                            default:
                                br.BaseStream.Position += size2;
                                break;
                        }
                    }
                } else br.BaseStream.Position += size;
            }
        }

        /* Finish tab handlers */

        private void bFinish_Click(object sender, EventArgs e) {
            File.WriteAllBytes(Statics.fn_dlver, new byte[] { Statics.DistantLandVersion });
            //If the user generated everything they need for distant land, go ahead and enable it
            if (File.Exists(Statics.fn_dlver) && File.Exists(Statics.fn_world) && File.Exists(Statics.fn_worldds) && File.Exists(Statics.fn_worldn)) Statics.mf.cbDLDistantLand.Checked = true;
            ChangingPage = true;
            Statics.mf.tabControl.SelectedIndex = 7;
            Close();
        }

        /* Finish tab methods */

        private void setFinishDesc(int stage) {
            lFinishDesc.Text = "";
            string spc = "   ";
            string mark = "» ";
            
            if (SetupFlags["ChkLandTex"])
                lFinishDesc.Text += (stage == 1 ? mark : spc) + (stage > 1 ? strings["SummaryStage1Complete"] : strings["SummaryStage1Working"]) + "\r\n";
            else
                lFinishDesc.Text += (stage == 1 ? mark : spc) + strings["SummaryStage1Skip"] + "\r\n";
            
            if (SetupFlags["ChkLandMesh"])
                lFinishDesc.Text += (stage == 2 ? mark : spc) + (stage > 2 ? strings["SummaryStage2Complete"] : strings["SummaryStage2Working"]) + "\r\n";
            else
                lFinishDesc.Text += (stage == 2 ? mark : spc) + strings["SummaryStage2Skip"] + "\r\n";
            
            if (SetupFlags["ChkStatics"])
                lFinishDesc.Text += (stage == 3 ? mark : spc) + (stage > 3 ? strings["SummaryStage3Complete"] : strings["SummaryStage3Working"]) + "\r\n";
            else
                lFinishDesc.Text += (stage == 3 ? mark : spc) + strings["SummaryStage3Skip"] + "\r\n";
            
            if (SetupFlags["ChkStatics"])
                lFinishDesc.Text += (stage == 4 ? mark : spc) + (stage > 4 ? strings["SummaryStage4Complete"] : strings["SummaryStage4Working"]) + "\r\n";
            else
                lFinishDesc.Text += (stage == 4 ? mark : spc) + strings["SummaryStage4Skip"] + "\r\n";
        }

        void cmbTexWorldResolution_SelectedIndexChanged(object sender, EventArgs e) {
            // Calcuate usage for DXT1 texture
            int extent = 128 << cmbTexWorldResolution.SelectedIndex;
            extent = (extent * extent + 1048576) / 2097152;
            
            lTexWorldMemUse.Text = strings["VideoMemUse"] + extent.ToString() + "MB";
        }
        
        void cmbTexWorldNormalRes_SelectedIndexChanged(object sender, EventArgs e) {
            // Calcuate usage for uncompressed texture
            int extent = 128 << cmbTexWorldNormalRes.SelectedIndex;
            extent = (extent * extent + 131072) / 262144;
            
            lTexNormalMemUse.Text = strings["VideoMemUse"] + extent.ToString() + "MB";
        }
    }
}
