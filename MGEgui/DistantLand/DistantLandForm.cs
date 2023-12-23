using System;
using StringBuilder = System.Text.StringBuilder;
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

            this.saveStaticListDialog.InitialDirectory = Path.Combine(Statics.runDir, Statics.fn_dlOverridesPath);
            Exists = exists;
            if (Exists) {
                StaticsExist = File.Exists(Statics.fn_usagedata);
            }
            LoadSettings();
            Directory.CreateDirectory(Statics.fn_dl);

            statusText.Text = strings["LoadBSAInit"];
            statusProgress.Style = ProgressBarStyle.Marquee;
            backgroundWorker.DoWork += workerInitBSAs;
            backgroundWorker.RunWorkerCompleted += workerFInitBSAs;
            statusWarnings.Text = strings["NoWarnings"]; 
            statusWarnings.Enabled = false;
            allWarnings = new List<string>();
            lastFileProcessed = "";
            lTexDesc.Text += DXMain.mCaps.MaxTexSize.ToString();
            DXMain.CreateDevice(this);
            LTEX.ReleaseCache();
            backgroundWorker.RunWorkerAsync();
        }

        public static Dictionary<string, string> strings = new Dictionary<string, string>();

        #region tooltip_messages
        public Dictionary<string, string[]> tooltip_messages = new Dictionary<string, string[]> {
            { "StaticMinSize", new string [] { "lStatMinSize", "cmbStatMinSize" } },
            { "StaticGrassDensity", new string [] { "lStatGrassDensity", "cmbStatGrassDensity" } },
            { "StaticSkipMips", new string [] { "lStatSkipMipLevels", "cmbStatSkipMipLevels" } },
            { "IncludeLargeInt", new string [] { "cbStatLargeInt" } },
            { "IncludeIntExt", new string [] { "cbStatIntExt" } },
            { "IncludeIntWater", new string [] { "cbStatIntWater" } },
            { "IncludeActivators", new string [] { "cbStatActivators" } },
            { "IncludeMisc", new string [] { "cbStatIncludeMisc" } },
            { "EditOverrideList", new string [] { "bStatOverrideList" } },
            { "ExportOverrideList", new string [] { "bStatExportStatics" } },
        };
        #endregion

        /* Static methods */

        private static void DumpError(Exception ex) {
            var str = new StringBuilder(ex.ToString());
            while ((ex = ex.InnerException) != null) {
                str.AppendLine();
                str.Append(ex.ToString());
            }
            File.WriteAllText(Statics.fn_dlLog, str.ToString());
        }

        /* Common properties */

        private bool ChangingPage;
        private bool Exists;
        private bool StaticsExist;
        private string[] files;
        private List<string> warnings;
        private List<string> allWarnings;
        private string lastFileProcessed;

        // Keeps track of map extents in terms of cells
        private int MapSize = 0;
        private int MapMaxX = Int32.MinValue;
        private int MapMaxY = Int32.MinValue;
        private int MapMinX = Int32.MaxValue;
        private int MapMinY = Int32.MaxValue;

        private int CellCount;

        private readonly LAND DefaultLand = new LAND();
        private static LTEX DefaultTex;
        private static LAND[,] LandMap;
        private List<AtlasRegion> Atlas;
        private int AtlasSpanX, AtlasSpanY;

        /* Common handlers */

        private void IgnoreKeyPress(object sender, KeyPressEventArgs e) {
            e.Handled = true;
        }

        private void statusWarnings_ButtonClick(object sender, EventArgs e) {
            (new WarningsForm(warnings)).ShowDialog();
        }

        private void UpdateProgress(object sender, System.ComponentModel.ProgressChangedEventArgs e) {
            statusProgress.Value = e.ProgressPercentage;
            if (e.UserState != null) {
                statusText.Text = (string)e.UserState;
            }
        }

        private void tabControl_Selecting(object sender, TabControlCancelEventArgs e) {
            if (ChangingPage) {
                ChangingPage = false;
            } else {
                e.Cancel = true;
            }
        }

        private void DistantLandForm_FormClosing(object sender, FormClosingEventArgs e) {
            if (!ChangingPage) {
                if (backgroundWorker.IsBusy) {
                    e.Cancel = true;
                    MessageBox.Show(strings["PleaseWait"], Statics.strings["Error"]);
                } else {
                    if (MessageBox.Show(strings["ConfirmExit"], Statics.strings["Warning"], MessageBoxButtons.YesNo) != DialogResult.Yes) {
                        e.Cancel = true;
                    }
                }
            }
        }

        // Used for override ListBox items
        public class OverrideListItem {
            public string FileName { get; set; }
            public string ShortName { get; set; }

            public OverrideListItem(string s) {
                FileName = s;
                ShortName = Path.GetFileName(s);
            }
        }

        /* Common methods */

        private void saveWarnings(string source) {
            try {
                File.AppendAllText(Statics.fn_dlLog, "### " + source + " ###\r\n\r\n" + string.Join("\r\n", warnings.ToArray()) + "\r\n\r\n");
            } catch {
            }
        }

        public static void ModCell(ref int cell, ref int tex) {
            if (tex < 0) {
                cell--;
                tex += 16;
            } else if (tex >= 16) {
                cell++;
                tex -= 16;
            }
        }

        static public LTEX GetTex(int cellx, int celly, int texx, int texy) {
            LTEX t = DefaultTex;
            var c = LandMap[cellx, celly];
            if (c != null) {
                t = c.Textures[c.Tex[texx, texy]];
            }
            return t;
        }

        /* Configuration properties */

        // INI dictionaries

        private static Dictionary<string, double> sortOrder = new Dictionary<string, double> {
            { "Name", 0 },
            { "Type", 1 },
            { "Load order", 2 }
        };

        private static Dictionary<string, double> texRes = new Dictionary<string, double> {
            { "128", 0 },
            { "256", 1 },
            { "512", 2 },
            { "1024", 3 },
            { "2048", 4 },
            { "4096", 5 },
            { "8192", 6 }
        };

        private static Dictionary<string, double> wMeshDet = new Dictionary<string, double> {
            { "Auto", -1 },
            { "Ultra High", 0 },
            { "Very High", 1 },
            { "High", 2 },
            { "Medium", 3 },
            { "Low", 4 }
        };

        private static Dictionary<string, double> sMeshDet = new Dictionary<string, double> {
            { "Full", 0 },
            { "90%", 1 },
            { "75%", 2 },
            { "50%", 3 },
            { "25%", 4 }
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
        private static INIFile.INIVariableDef iniStatLargeInt = new INIFile.INIVariableDef("StatLargeInt", iniDLWizardSets, "Statics for large interiors", INIFile.INIBoolType.OnOff, "On");
        private static INIFile.INIVariableDef iniStatIntExt = new INIFile.INIVariableDef("StatIntExt", iniDLWizardSets, "Statics for behave like exterior cells", INIFile.INIBoolType.OnOff, "On");
        private static INIFile.INIVariableDef iniStatIntWater = new INIFile.INIVariableDef("StatIntWater", iniDLWizardSets, "Statics for interiors with water", INIFile.INIBoolType.OnOff, "Off");
        private static INIFile.INIVariableDef iniActivators = new INIFile.INIVariableDef("Activators", iniDLWizardSets, "Include activators", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniMiscObj = new INIFile.INIVariableDef("MiscObj", iniDLWizardSets, "Include misc objects", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniUseStatOvr = new INIFile.INIVariableDef("UseStatOvr", iniDLWizardSets, "Use static overrides", INIFile.INIBoolType.Text, "True");

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
            iniStatLargeInt,
            iniStatIntExt,
            iniStatIntWater,
            iniActivators, 
            iniMiscObj, 
            iniUseStatOvr
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
            iniStatLargeInt,
            iniStatIntExt,
            iniStatIntWater,
            iniActivators, 
            iniMiscObj, 
            iniUseStatOvr
        };

        // configuration of setup steps
        private Dictionary<string, bool> SetupFlags = new Dictionary<string, bool>() {
            { "RunSetup", false },
            { "AutoRun", false },
            { "Debug", false },
            { "ChkLandTex", true },
            { "ChkLandMesh", true },
            { "ChkLandAuto", true },
            { "ChkStatics", true },
            { "EnaLandTex", true },
            { "EnaLandMesh", true },
            { "EnaLandAuto", true },
            { "EnaStatics", true },
        };

        private bool configure;

        /* Configuration methods */

        // loading all settings
        private void LoadSettings() {
            var iniFile = new INIFile(Statics.fn_inifile, iniDLWizardVars, true);
            configure = !iniFile.hasSection(iniDLWizardSets);
            if (configure) {
                iniFile.initialize();
                iniFile.save();
            }

            pluginDirs = new List<string>();
            var pluginDirsTmp = new List<string>(iniFile.getSectList(iniDLWizardPlugDirs));
            pluginDirsTmp.Sort();

            string lastDir = "";
            foreach (string s in pluginDirsTmp) {
                string casefoldDir = s.ToLowerInvariant();
                if (casefoldDir != lastDir) {
                    pluginDirs.Add(s);
                }
                lastDir = casefoldDir;
            }

            pluginList = new MWPlugins(Statics.fn_dataFiles, pluginDirs);
            switch ((int)iniFile.getKeyValue("PlugSort")) {
                case 0:
                    rbPlugsName.Checked = true;
                    break;
                case 1:
                    rbPlugsType.Checked = true;
                    break;
                case 2:
                    rbPlugsLoad.Checked = true;
                    break;
            }
            pluginsSort(null, null);
            preselectedPlugins = iniFile.getSectList(iniDLWizardPlugs);
            SelectPlugins(preselectedPlugins);

            cmbTexWorldResolution.SelectedIndex = (int)iniFile.getKeyValue("TexRes");
            cmbTexWorldNormalRes.SelectedIndex = (int)iniFile.getKeyValue("NormRes");
            cmbMeshWorldDetail.SelectedIndex = (int)iniFile.getKeyValue("WorldMesh");
            udStatMinSize.Value = (int)iniFile.getKeyValue("MinStat");
            udStatGrassDensity.Value = (int)iniFile.getKeyValue("GrassDens");
            cmbStatSkipMipLevels.SelectedIndex = (int)iniFile.getKeyValue("SkipMip");
            cbStatLargeInt.Checked = (iniFile.getKeyValue("StatLargeInt") == 1);
            cbStatIntExt.Checked = (iniFile.getKeyValue("StatIntExt") == 1);
            cbStatIntWater.Checked = (iniFile.getKeyValue("StatIntWater") == 1);
            cbStatActivators.Checked = (iniFile.getKeyValue("Activators") == 1);
            cbStatIncludeMisc.Checked = (iniFile.getKeyValue("MiscObj") == 1);
            cbStatOverrideList.Checked = (iniFile.getKeyValue("UseStatOvr") == 1);

            lbStatOverrideList.Items.Clear();
            lbStatOverrideList.BeginUpdate();
            foreach (string overrideFile in iniFile.getSectList(iniDLWizardStatOvr)) {
                lbStatOverrideList.Items.Add(new OverrideListItem(overrideFile));
            }
            lbStatOverrideList.EndUpdate();
            lStatOverrideList.Enabled = (lbStatOverrideList.Items.Count == 0);
        }

        // saving settings after plugin selection
        private void SavePlugsSettings() {
            var iniFile = new INIFile(Statics.fn_inifile, iniPlugsTab, true);
            double temp;
            if (rbPlugsName.Checked) {
                temp = 0;
            } else if (rbPlugsType.Checked) {
                temp = 1;
            } else if (rbPlugsLoad.Checked) {
                temp = 2;
            } else {
                temp = 1;
            }
            iniFile.setKey("PlugSort", temp);
            iniFile.setSectList(iniDLWizardPlugDirs, pluginDirs.ToArray());

            var tempList = new List<string>();
            foreach (string s in clbPlugsModList.CheckedItems) {
                tempList.Add(s);
            }
            iniFile.setSectList(iniDLWizardPlugs, tempList.ToArray());
            iniFile.save();
        }

        // saving settings after land texture creation
        private void SaveTexSettings() {
            var iniFile = new INIFile(Statics.fn_inifile, iniTexTab, true);
            iniFile.setKey("TexRes", cmbTexWorldResolution.SelectedIndex);
            iniFile.setKey("NormRes", cmbTexWorldNormalRes.SelectedIndex);
            iniFile.save();
        }

        // saving settings after land mesh creation
        private void SaveMeshSettings() {
            var iniFile = new INIFile(Statics.fn_inifile, iniMeshTab, true);
            iniFile.setKey("WorldMesh", (cmbMeshWorldDetail_auto ? -1 : (double)cmbMeshWorldDetail.SelectedIndex));
            iniFile.save();
        }

        // saving settings after statics creation
        private void SaveStatSettings() {
            var iniFile = new INIFile(Statics.fn_inifile, iniStatTab, true);
            iniFile.setKey("MinStat", (double)udStatMinSize.Value);
            iniFile.setKey("GrassDens", (double)udStatGrassDensity.Value);
            iniFile.setKey("SkipMip", cmbStatSkipMipLevels.SelectedIndex);
            iniFile.setKey("StatLargeInt", cbStatLargeInt.Checked);
            iniFile.setKey("StatIntExt", cbStatIntExt.Checked);
            iniFile.setKey("StatIntWater", cbStatIntWater.Checked);
            iniFile.setKey("Activators", cbStatActivators.Checked);
            iniFile.setKey("MiscObj", cbStatIncludeMisc.Checked);
            iniFile.setKey("UseStatOvr", cbStatOverrideList.Checked);

            var tempList = new List<string>();
            foreach (OverrideListItem item in lbStatOverrideList.Items) {
                tempList.Add(item.FileName);
            }
            iniFile.setSectOrderedList(iniDLWizardStatOvr, tempList.ToArray());
            iniFile.save();
        }

        /* Background workers */

        private void workerInitBSAs(object sender, System.ComponentModel.DoWorkEventArgs e) {
            try {
                File.Delete(Statics.fn_dlLog);
            } catch {
            }
            BSA.InitBSAs();
        }

        private void workerFInitBSAs(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e.Error != null) {
                DumpError(e.Error);
                MessageBox.Show(strings["LoadBSAError"] + "\n\n" + e.Error.ToString());
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
            LandMap = (LAND[,])Array.CreateInstance(typeof(LAND), new int[] {
                501,
                801
            }, new int[] {
                -250,
                -250
            });

            DefaultTex = new LTEX();
            DefaultTex.FilePath = "_land_default.tga";
            DefaultTex.index = 0;
            try {
                DefaultTex.LoadTexture();
            } catch (Exception ex) {
                throw new ApplicationException("Failed to load default ground texture (" + ex.Message + ")", ex);
            }

            const int invalidCellCoord = -99999;
            CellCount = 0;
            int progress = 0;
            var warnings = new List<string>();

            foreach (string file in files) {
                if (DEBUG) {
                    allWarnings.Add("Loading plugin: " + file);
                }
                lastFileProcessed = file;
                var br = new BinaryReader(File.OpenRead(file), Statics.ESPEncoding);
                var rr = new RecordReader(br);
                var Textures = new Dictionary<int, LTEX>();
                Textures.Add(0, DefaultTex);

                while (rr.NextRecord()) {
                    if (rr.Tag == "LAND") {
                        var land = new LAND();
                        land.Textures = Textures;
                        int lx = invalidCellCoord, ly = invalidCellCoord;
                        bool usesVertexHeights = true;

                        while (rr.NextSubrecord()) {
                            switch (rr.SubTag) {
                                case "INTV":
                                    lx = br.ReadInt32();
                                    ly = br.ReadInt32();
                                    land.xpos = lx;
                                    land.ypos = ly;
                                    break;
                                case "DATA":
                                    int flags = br.ReadInt32();
                                    usesVertexHeights = (flags & 1) == 1;
                                    break;
                                case "VHGT":
                                    int offset = (int)br.ReadSingle();
                                    for (int y = 0; y < 65; y++) {
                                        for (int x = 0; x < 65; x++) {
                                            offset += br.ReadSByte();
                                            land.Heights[x, y] = offset;
                                        }
                                        offset = land.Heights[0, y];
                                    }
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

                                    // Verify land texture index records exist
                                    bool warningLatch = false;
                                    for (int y = 0; y < 16; y++) {
                                        for (int x = 0; x < 16; x++) {
                                            int t = land.Tex[x, y];
                                            if (!land.Textures.ContainsKey(t)) {
                                                if (!warningLatch) {
                                                    String warn = String.Format(strings["MissingLandTexture"], lx, ly, file);
                                                    MessageBox.Show(warn, "Warning", MessageBoxButtons.OK);
                                                    warnings.Add(warn);
                                                    warningLatch = true;
                                                }
                                                // Reset missing index to use default texture
                                                land.Tex[x, y] = 0;
                                            }
                                        }
                                    }
                                    break;
                            }
                        }
                        if (usesVertexHeights && lx != invalidCellCoord && ly != invalidCellCoord) {
                            if (lx >= LandMap.GetLowerBound(0) && lx <= LandMap.GetUpperBound(0)
                                && ly >= LandMap.GetLowerBound(1) && ly <= LandMap.GetUpperBound(1)) {
                                // Keep track of map extents
                                MapMinX = Math.Min(MapMinX, lx);
                                MapMaxX = Math.Max(MapMaxX, lx);
                                MapMinY = Math.Min(MapMinY, ly);
                                MapMaxY = Math.Max(MapMaxY, ly);
    
                                int maxDimension = Math.Max(MapMaxX - MapMinX, MapMaxY - MapMinY);
                                MapSize = Math.Max(MapSize, maxDimension);
    
                                // Add land to map
                                if (LandMap[lx, ly] == null) {
                                    CellCount++;
                                }
                                LandMap[lx, ly] = land;
                            }
                            else {
                                warnings.Add("Cell (" + lx + "," + ly + ") in plugin '" + file + "' is too far from the map centre. It will not be generated.");
                            }
                        }
                    } else if (rr.Tag == "LTEX") {
                        var tex = new LTEX();
                        while (rr.NextSubrecord()) {
                            if (rr.SubTag == "INTV") {
                                tex.index = br.ReadInt32() + 1;
                            } else if (rr.SubTag == "DATA") {
                                tex.FilePath = rr.ReadCString().ToLowerInvariant();
                            }
                        }
                        try {
                            tex.LoadTexture();
                        } catch (Exception ex) {
                            // Log texture errors, except for known errors in morrowind.esm
                            var fi = new FileInfo(file);
                            if (fi.Name.ToLowerInvariant() != "morrowind.esm") {
                                warnings.Add("Texture '" + tex.FilePath + "' in plugin '" + file + "' failed to load (" + ex.Message + ")");
                            }
                            tex.tex = DefaultTex.tex;
                        }
                        Textures.Add(tex.index, tex);
                    }
                }
                br.Close();
                backgroundWorker.ReportProgress(++progress);
            }
            if (warnings.Count > 0) {
                e.Result = warnings;
            }

            // Calculate texture atlas for both texture and land gen texture UVs
            AtlasSetup();
        }

        private void workerFLoadPlugins(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e.Error != null) {
                DumpError(e.Error);
                MessageBox.Show(strings["LoadLandError"] + "\n<" + lastFileProcessed + ">\n\n" + e.Error.ToString());
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
            if (DEBUG) {
                allWarnings.Add("Plugin land data loaded");
            }
            statusText.Text = strings["LoadLandStatus"];
            backgroundWorker.DoWork -= workerLoadPlugins;
            backgroundWorker.RunWorkerCompleted -= workerFLoadPlugins;
            SavePlugsSettings();
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(1);
                if (SetupFlags["ChkLandTex"]) {
                    bTexRun_Click(null, null);
                } else {
                    bTexSkip_Click(null, null);
                }
            } else {
                bTexSkip.Enabled = true;
                bTexRun.Enabled = true;
            }
        }

        private struct CreateTextureArgs {
            public int WorldRes;
            public int WorldNormal;
        }

        void workerCreateTextures(object sender, System.ComponentModel.DoWorkEventArgs e) {
            var args = (CreateTextureArgs)e.Argument;
            var ctc = new CellTexCreator(args.WorldRes);
            int count = 0;
            backgroundWorker.ReportProgress(count, strings["LandTextureCreate"]);

            // Render world texture
            var wtc = new WorldTexCreator(args.WorldRes, AtlasSpanX, AtlasSpanY);
            wtc.Begin();
            ctc.Begin();
            foreach (var r in Atlas) {
                for (int y = r.MinY; y <= r.MaxY; y++) {
                    backgroundWorker.ReportProgress(Math.Min(++count, statusProgress.Maximum));
                    for (int x = r.MinX; x <= r.MaxX; x++) {
                        if (LandMap[x, y] == null || LandMap[x, y] == DefaultLand) {
                            ctc.SetDefaultCell(DefaultTex);
                        } else {
                            // Set the colors and normals
                            ctc.SetCell(LandMap[x, y]);
                        }
                        float x_pos = ((float)(x - r.MinX + r.OffsetX) + 0.5f) * wtc.x_spacing - 1.0f;
                        float y_pos = ((float)(y - r.MinY + r.OffsetY) + 0.5f) * wtc.y_spacing - 1.0f;
                        ctc.Render(x_pos, y_pos, wtc.x_scale, wtc.y_scale);
                    }
                }
            }
            ctc.End();
            // Save the world texture.
            wtc.FinishCompressed(Statics.fn_worldds, true);
            wtc.Dispose();

            // World normal map
            wtc = new WorldTexCreator(args.WorldNormal, AtlasSpanX, AtlasSpanY);
            wtc.Begin();
            ctc.BeginNormalMap();
            foreach (var r in Atlas) {
                for (int y = r.MinY; y <= r.MaxY; y++) {
                    backgroundWorker.ReportProgress(Math.Min(++count, statusProgress.Maximum));
                    for (int x = r.MinX; x <= r.MaxX; x++) {
                        if (LandMap[x, y] == null || LandMap[x, y] == DefaultLand) {
                            ctc.SetDefaultCell(DefaultTex);
                        } else {
                            // Set the colors and normals
                            ctc.SetCell(LandMap[x, y]);
                        }
                        float x_pos = ((float)(x - r.MinX + r.OffsetX) + 0.5f) * wtc.x_spacing - 1.0f;
                        float y_pos = ((float)(y - r.MinY + r.OffsetY) + 0.5f) * wtc.y_spacing - 1.0f;
                        ctc.RenderNormalMap(x_pos, y_pos, wtc.x_scale, wtc.y_scale);
                    }
                }
            }
            ctc.EndNormalMap();
            wtc.FinishUncompressed(Statics.fn_worldn, false);
            wtc.Dispose();

            ctc.Dispose();
        }

        private class AtlasRegion {
            public int Id;
            public int MinX, MinY, MaxX, MaxY;
            public int OffsetX, OffsetY;
        }

        void AtlasSetup() {
            // Merge cells into atlas regions
            var regions = new List<AtlasRegion>();
            int currentAtlasId = 0;

            for (int y = MapMinY; y <= MapMaxY; y++) {
                for (int x = MapMinX; x <= MapMaxX; x++) {
                    LAND land = LandMap[x, y];
                    if (land == null || land == DefaultLand || land.atlasId >= 0) {
                        continue;
                    }

                    // Found new starting cell
                    var r = new AtlasRegion();
                    regions.Add(r);
                    r.Id = currentAtlasId;
                    land.atlasId = currentAtlasId;

                    // Search for connecting cells on the atlas border
                    r.MinX = r.MaxX = x;
                    r.MinY = r.MaxY = y;
                    bool continueSearch = true, extend = false;

                    while (continueSearch) {
                        continueSearch = false;

                        extend = false;
                        for (int searchX = r.MinX - 1; searchX <= r.MaxX + 1; searchX++) {
                            LAND searchLand = LandMap[searchX, r.MinY - 1];
                            if (searchLand != null && searchLand != DefaultLand) {
                                searchLand.atlasId = currentAtlasId;
                                extend = true;
                            }
                        }
                        if (extend) {
                            r.MinY--;
                            continueSearch = true;
                        }

                        extend = false;
                        for (int searchX = r.MinX - 1; searchX <= r.MaxX + 1; searchX++) {
                            LAND searchLand = LandMap[searchX, r.MaxY + 1];
                            if (searchLand != null && searchLand != DefaultLand) {
                                searchLand.atlasId = currentAtlasId;
                                extend = true;
                            }
                        }
                        if (extend) {
                            r.MaxY++;
                            continueSearch = true;
                        }

                        extend = false;
                        for (int searchY = r.MinY - 1; searchY <= r.MaxY + 1; searchY++) {
                            LAND searchLand = LandMap[r.MinX - 1, searchY];
                            if (searchLand != null && searchLand != DefaultLand) {
                                searchLand.atlasId = currentAtlasId;
                                extend = true;
                            }
                        }
                        if (extend) {
                            r.MinX--;
                            continueSearch = true;
                        }

                        extend = false;
                        for (int searchY = r.MinY - 1; searchY <= r.MaxY + 1; searchY++) {
                            LAND searchLand = LandMap[r.MaxX + 1, searchY];
                            if (searchLand != null && searchLand != DefaultLand) {
                                searchLand.atlasId = currentAtlasId;
                                extend = true;
                            }
                        }
                        if (extend) {
                            r.MaxX++;
                            continueSearch = true;
                        }
                    }

                    currentAtlasId++;
                }
            }

            // Pack regions closely into a square texture
            int currentOffsetX = 0, currentOffsetY = 0;
            Atlas = new List<AtlasRegion>();

            // Sort regions by width, largest first
            regions.Sort((a, b) => (b.MaxX - b.MinX).CompareTo(a.MaxX - a.MinX));

            // Pack first (widest) region
            var first = regions[0];
            Atlas.Add(first);
            regions.RemoveAt(0);

            AtlasSpanX = first.MaxX - first.MinX + 1;
            AtlasSpanY = first.MaxY - first.MinY + 1;
            currentOffsetY += AtlasSpanY;

            // Pack wide regions
            int widthLimit = AtlasSpanX * 3 / 4;

            while (regions.Count > 0) {
                var r = regions[0];
                int width = r.MaxX - r.MinX + 1, height = r.MaxY - r.MinY + 1;
                if (width < widthLimit) {
                    break;
                }

                r.OffsetX = 0;
                r.OffsetY = currentOffsetY;
                currentOffsetY += height;
                AtlasSpanY += height;

                Atlas.Add(r);
                regions.RemoveAt(0);
            }

            // Sort remaining regions by height, largest first
            regions.Sort((a, b) => (b.MaxY - b.MinY).CompareTo(a.MaxY - a.MinY));

            // Pack smaller regions
            while (regions.Count > 0) {
                var r = regions[0];
                int width = r.MaxX - r.MinX + 1, height = r.MaxY - r.MinY + 1;
                if (currentOffsetX + width > AtlasSpanX) {
                    currentOffsetX = 0;
                    currentOffsetY = AtlasSpanY;
                }
                if (currentOffsetX == 0) {
                    AtlasSpanY += height;
                }

                r.OffsetX = currentOffsetX;
                r.OffsetY = currentOffsetY;
                currentOffsetX += width;

                Atlas.Add(r);
                regions.RemoveAt(0);
            }
            
            // Log atlas generation
            var atlas_log = new StringBuilder("### World atlas ###\r\n\r\n");
            int n = 0;
            foreach (var a in Atlas) {
                atlas_log.AppendFormat("World atlas {0}: Cells ({1},{2}) to ({3},{4})\r\n", n, a.MinX, a.MinY, a.MaxX, a.MaxY);
                n++;
            }
            atlas_log.AppendLine();
            File.AppendAllText(Statics.fn_dlLog, atlas_log.ToString());
        }

        void workerFCreateTextures(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e.Error != null) {
                DumpError(e.Error);
                MessageBox.Show(strings["LandTextureError"] + "\n\n" + e.Error.ToString());
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
            if (DEBUG) {
                allWarnings.Add("Landscape textures created");
            }
            statusText.Text = strings["LandTextureStatus"];
            backgroundWorker.DoWork -= workerCreateTextures;
            backgroundWorker.RunWorkerCompleted -= workerFCreateTextures;
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(2);
                if (SetupFlags["ChkLandMesh"]) {
                    bMeshRun_Click(null, null);
                } else {
                    bMeshSkip_Click(null, null);
                }
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
            var cma = (CreateMeshArgs)e.Argument;
            backgroundWorker.ReportProgress(0, strings["LandMeshCreate"]);
            GenerateWorldMesh(cma.MeshDetail, Statics.fn_world);
            // Dispose of map object, high memory use
            LandMap = null;
        }

        void workerFCreateMeshes(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e != null) {
                LTEX.ReleaseCache();
                if (e.Error != null) {
                    DumpError(e.Error);
                    MessageBox.Show(strings["LandMeshError"] + "\n\n" + e.Error.ToString());
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
                if (DEBUG) {
                    allWarnings.Add("Landscape meshes created");
                }
                statusText.Text = strings["LandMeshStatus"];
                backgroundWorker.DoWork -= workerCreateMeshes;
                backgroundWorker.RunWorkerCompleted -= workerFCreateMeshes;
                if (SetupFlags["AutoRun"]) {
                    setFinishDesc(3);
                    if (SetupFlags["ChkStatics"]) {
                        bStatRun_Click(null, null);
                    } else {
                        bStatSkip_Click(null, null);
                    }
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
            public List<string> OverrideFiles;
            public bool UseOverrideList;
            public bool Activators;
            public bool Misc;
        }

        private void GrassDensityThreshold(float GrassDensity, KeyValuePair<string, Dictionary<string, StaticReference>> cellStatics, KeyValuePair<string, StaticReference> pair, Random rnd, List<StaticToRemove> UsedStaticsToRemove) {
            if (GrassDensity < 1.0f) {
                // remove some of the grass to improve performance
                if (rnd.NextDouble() >= GrassDensity) {
                    UsedStaticsToRemove.Add(new StaticToRemove(cellStatics.Key, pair.Key));
                }
            } else if (GrassDensity == 0.0f) {
                // Remove all grass
                UsedStaticsToRemove.Add(new StaticToRemove(cellStatics.Key, pair.Key));
            }
        }

        enum OverrideFileSection {
            Default, Names, Interiors, DynamicVis
        }

        private void ParseOverrideFiles(List<string> overrideFiles, Dictionary<string, StaticOverride> overrideList, Dictionary<string, bool> namedObjectDisables, Dictionary<string, bool> interiorEnables, DynamicVisDataSet dynamicVisDataSet, List<string> staticsWarnings) {
            foreach (string filename in overrideFiles) {
                if (DEBUG) {
                    allWarnings.Add("Loading override: " + filename);
                }

                try {
                    using (var sr = new StreamReader(filename)) {
                        OverrideFileSection section = OverrideFileSection.Default;
                        string line, key, value;
                        int index;

                        while (!sr.EndOfStream) {
                            // Read line, trim and remove comment
                            line = sr.ReadLine().ToLower(Statics.Culture);

                            index = 0;
                            while (index != -1) {
                                index = line.IndexOf(':', index);
                                if (index == -1) { break; }

                                // Check for escaped comment character
                                if (index > 0 && line[index-1] == '\\') {
                                    ++index;
                                }
                                else {
                                    line = line.Substring(0, index);
                                    break;
                                }
                            }
                            line = line.Trim();

                            // Skip blank lines
                            if (line.Length == 0) { continue; }

                            // Check for section change
                            if (line.StartsWith("[") && line.EndsWith("]") && !line.EndsWith("\\]")) {
                                string section_name = line.Substring(1, line.Length - 2);

                                if (section_name == "names") { section = OverrideFileSection.Names; }
                                else if (section_name == "interiors") { section = OverrideFileSection.Interiors; }
                                else if (section_name == "dynamic_vis") { section = OverrideFileSection.DynamicVis; }

                                continue;
                            }

                            // Key-value parse
                            index = line.LastIndexOf('=');
                            if (index != -1) {
                                key = line.Substring(0, index).Trim();
                                value = line.Substring(index + 1).Trim();
                            }
                            else {
                                key = null;
                                value = null;
                            }

                            switch (section) {
                                case OverrideFileSection.Default:
                                    if (key != null) {
                                        overrideList[key] = new StaticOverride(value);
                                    } else {
                                        staticsWarnings.Add("Warning: Failed to parse line in override list '" + filename + "': '" + line + "'");
                                    }
                                    break;
                                case OverrideFileSection.Names:
                                    if (key != null) {
                                        switch (value) {
                                            case "enable":
                                                namedObjectDisables[key] = false;
                                                break;
                                            case "disable":
                                                namedObjectDisables[key] = true;
                                                break;
                                            default:
                                                staticsWarnings.Add("Warning: Invalid keyword in override names '" + filename + "': '" + line + "'");
                                                break;
                                        }
                                    }
                                    else {
                                        // Object name only, disable object by default
                                        namedObjectDisables[line] = true;
                                    }
                                    break;
                                case OverrideFileSection.Interiors:
                                    if (key != null) {
                                        switch (value) {
                                            case "enable":
                                                interiorEnables[key] = true;
                                                break;
                                            case "disable":
                                                interiorEnables[key] = false;
                                                break;
                                            default:
                                                staticsWarnings.Add("Warning: Invalid keyword in override cells '" + filename + "': '" + line + "'");
                                                break;
                                        }
                                    }
                                    else {
                                        // Cell name only, enable interior by default
                                        interiorEnables[line] = true;
                                    }
                                    break;
                                case OverrideFileSection.DynamicVis:
                                    bool valid = false;

                                    if (key != null) {
                                        var dvg = new DynamicVisGroup(key, value);
                                        if (dvg.Valid) {
                                            // Add new / re-use existing vis group
                                            dvg = dynamicVisDataSet.AddMerge(dvg);
                                            // Assign to objects
                                            dynamicVisDataSet.Assign(key, dvg);
                                            valid = true;
                                        }
                                    }
                                    if (!valid) {
                                        staticsWarnings.Add("Warning: Failed to parse line in dynamic vis '" + filename + "': '" + line + "'");
                                    }
                                    break;
                            }
                        }
                    }
                } catch (Exception ex) {
                    staticsWarnings.Add("Error: Could not import statics override list '" + filename + "'\r\n" + ex.Message);
                }
            }

            // Assign unique indexes to dynamic vis groups, starting at 1
            int i = 1;
            foreach (var v in dynamicVisDataSet.visGroups) {
                v.Index = i++;
            }
        }

        void workerCreateStatics(object sender, System.ComponentModel.DoWorkEventArgs e) {
            var args = (CreateStaticsArgs)e.Argument;
            var staticsWarnings = new List<string>();
            var overrideList = new Dictionary<string, StaticOverride>();
            var namedObjectDisables = new Dictionary<string, bool>();
            var interiorEnables = new Dictionary<string, bool>();
            var dynamicVisDataSet = new DynamicVisDataSet();

            StaticsList.Clear();
            UsedStaticsList.Clear();
            StaticMap.Clear();

            if (args.UseOverrideList && args.OverrideFiles.Count > 0) {
                ParseOverrideFiles(args.OverrideFiles, overrideList, namedObjectDisables, interiorEnables, dynamicVisDataSet, staticsWarnings);
            }

            Directory.CreateDirectory(Statics.fn_statics);
            foreach (string file in files) {
                if (DEBUG) {
                    allWarnings.Add("Parsing for statics definitions: " + file);
                }
                var br = new BinaryReader(File.OpenRead(file), Statics.ESPEncoding);
                try {
                    ParseFileForStatics(br, overrideList, args.Activators, args.Misc, namedObjectDisables, null, dynamicVisDataSet);
                } catch (Exception ex) {
                    staticsWarnings.Add("Parse statics failed on \"" + file + "\"\n\n" + ex.ToString());
                }
                br.Close();
            }

            backgroundWorker.ReportProgress(1, strings["StaticsGenerate1"]);
            UsedStaticsList.Add("", new Dictionary<string, StaticReference>());
            foreach (string file in files) {
                if (DEBUG) {
                    allWarnings.Add("Parsing for used statics: " + file);
                }
                var br = new BinaryReader(File.OpenRead(file), Statics.ESPEncoding);
                var fi = new FileInfo(file);
                try {
                    ParseFileForInteriors(br, interiorEnables);
                    br.BaseStream.Position = 0;
                    ParseFileForCells(br, fi.Name, namedObjectDisables, interiorEnables);
                } catch (Exception ex) {
                    staticsWarnings.Add("Parsing cells failed on \"" + file + "\"\n\n" + ex.ToString());
                }
                br.Close();
            }

            // Generate a list of the NIF files we need to load
            backgroundWorker.ReportProgress(2, strings["StaticsGenerate2"]);
            var UsedNifList = new List<string>();
            foreach (KeyValuePair<string, Dictionary<string, StaticReference>> cellStatics in UsedStaticsList) {
                foreach (KeyValuePair<string, StaticReference> pair in cellStatics.Value) {
                    string nif_name = StaticsList[pair.Value.Name].Model;
                    if (!UsedNifList.Contains(nif_name)) {
                        UsedNifList.Add(nif_name);
                    }
                }
            }

            backgroundWorker.ReportProgress(3, strings["StaticsGenerate3"]);
            unsafe {
                NativeMethods.BeginStaticCreation((IntPtr)DXMain.device.ComPointer, Statics.fn_statmesh);
            }
            var rnd = new Random();
            try {
                // Try to load the NIFs and remove any from the list that fail or are too small
                for (int i = 0; i < UsedNifList.Count; i++) {
                    string name = UsedNifList[i];
                    byte[] data;

                    // Set default simplification level to None until the simplifier code is fixed.
                    float simplify = 1.0f;

                    // Try to load a version of the file that ends with '_dist' first.
                    // This allows people to supply a different version of the NIF to be
                    // rendered by distant land.  For example, a low poly nif.
                    string file_name = name;
                    string extension = "";
                    int dot_pos = file_name.LastIndexOf('.');
                    if (dot_pos != -1) {
                        extension = file_name.Substring(dot_pos, file_name.Length - dot_pos);
                        file_name = file_name.Substring(0, dot_pos);
                    }
                    string dist_name = file_name + "_dist" + extension;
                    try {
                        data = BSA.GetNif(dist_name);
                        // Do not simplify '_dist' NIFs.
                        simplify = 1.0f;
                    } catch {
                        // We didn't find a NIF file with '_dist' in its name,
                        // so search for the normal NIF file now.
                        try {
                            data = BSA.GetNif(name);
                        } catch {
                            data = null;
                        }
                    }

                    if (data == null) {
                        // Remove entry if loading failed
                        UsedNifList.RemoveAt(i--);
                    } else {
                        try {
                            backgroundWorker.ReportProgress(3, strings["StaticsGenerate3Nif"] + name);
                            if (DEBUG) {
                                allWarnings.Add("Processing NIF: " + name);
                            }

                            float size = -1;
                            if (overrideList.ContainsKey(name)) {
                                StaticOverride so = overrideList[name];
                                if (!so.Ignore || so.NamesNoIgnore) {
                                    //simplify = so.Simplify.HasValue ? so.Simplify.Value : simplify;
                                    size = NativeMethods.ProcessNif(data, data.Length, simplify, args.MinSize, (byte)so.Type);
                                }
                            } else {
                                // Set static classification based on the file path
                                StaticType classifier = StaticType.Auto;
                                if (name.StartsWith("grass\\")) {
                                    classifier = StaticType.Grass;
                                } else if (name.StartsWith("trees\\")) {
                                    classifier = StaticType.Tree;
                                } else if (name.StartsWith("x\\")) {
                                    classifier = StaticType.Building;
                                }

                                size = NativeMethods.ProcessNif(data, data.Length, simplify, args.MinSize, (byte)classifier);
                            }

                            if (size < 0) {
                                // Remove entry if processing failed
                                UsedNifList.RemoveAt(i--);
                            }
                        } catch (Exception ex) {
                            staticsWarnings.Add("Failed to process NIF " + name + "\n    " + ex.ToString());
                            UsedNifList.RemoveAt(i--);
                        }
                    }
                }
            } finally {
                NativeMethods.EndStaticCreation();
            }

            // Reset used distant static ID numbers to match NIF list order
            var NifMap = new Dictionary<string, uint>();
            uint count = 0;
            foreach (string name in UsedNifList) {
                NifMap[name] = count++;
            }

            // Determine floating point grass density
            var UsedStaticsToRemove = new List<StaticToRemove>();
            float GrassDensity = (float)udStatGrassDensity.Value / 100.0f;

            foreach (var cellStatics in UsedStaticsList) {
                foreach (var pair in cellStatics.Value) {
                    string nif_name = StaticsList[pair.Value.Name].Model;
                    if (NifMap.ContainsKey(nif_name)) {
                        pair.Value.StaticID = NifMap[nif_name];
                    } else {
                        UsedStaticsToRemove.Add(new StaticToRemove(cellStatics.Key, pair.Key));
                    }
                    if (nif_name.StartsWith("grass\\") || (overrideList.ContainsKey(nif_name) && overrideList[nif_name].Type == StaticType.Grass)) {
                        if (overrideList.ContainsKey(nif_name)) {
                            if (overrideList[nif_name].Density >= 0) {
                                GrassDensityThreshold(overrideList[nif_name].Density, cellStatics, pair, rnd, UsedStaticsToRemove);
                            } else {
                                GrassDensityThreshold(GrassDensity, cellStatics, pair, rnd, UsedStaticsToRemove);
                            }
                        } else {
                            GrassDensityThreshold(GrassDensity, cellStatics, pair, rnd, UsedStaticsToRemove);
                        }
                    }
                }
            }
            foreach (StaticToRemove key in UsedStaticsToRemove) {
                UsedStaticsList[key.Worldspace].Remove(key.Reference);
            }

            backgroundWorker.ReportProgress(4, strings["StaticsGenerate4"]);
            using (var bw = new BinaryWriter(File.Create(Statics.fn_usagedata), Statics.ESPEncoding)) {
                bw.Write(UsedNifList.Count);

                // Write dynamic vis data
                bw.Write(dynamicVisDataSet.visGroups.Count);
                foreach (var vis in dynamicVisDataSet.visGroups) {
                    vis.Write(bw);
                }

                // Write main worldspace statics usage
                var mainWorldspace = UsedStaticsList[""];
                bw.Write(mainWorldspace.Count);
                foreach (KeyValuePair<string, StaticReference> pair in mainWorldspace) {
                    pair.Value.Write(bw);
                }

                mainWorldspace.Clear();
                UsedStaticsList.Remove("");

                // Write cells' statics usage
                foreach (var cellStatics in UsedStaticsList) {
                    int cellStaticsCount = cellStatics.Value.Count;
                    // Don't write cells with zero distant statics, as it would be confused with the terminator
                    if (cellStaticsCount == 0) {
                        continue;
                    }

                    bw.Write(cellStaticsCount);
                    bw.Write(cellStatics.Key.PadRight(64, '\0').ToCharArray());
                    foreach (var pair in cellStatics.Value) {
                        pair.Value.Write(bw);
                    }
                }

                // Write terminator
                bw.Write((int)0);
                bw.Write((float)Convert.ToSingle(udStatMinSize.Value));
            }

            if (!File.Exists(Statics.fn_statmesh)) {
                return;
            }

            setFinishDesc(4);
            backgroundWorker.ReportProgress(5, strings["StaticsGenerate5"]);
            {
                var stc = new StaticTexCreator(args.MipSkip);
                int vert_size = NativeMethods.GetCompressedVertSize(), face_size = 6;

                using (var br = new BinaryReader(File.OpenRead(Statics.fn_statmesh), Statics.ESPEncoding)) {
                    foreach (var name in UsedNifList) {
                        int nodes = br.ReadInt32();
                        br.BaseStream.Position += 16; // Byte count: 4 - radius, 12 - center
                        int type = br.BaseStream.ReadByte();
                        for (int j = 0; j < nodes; j++) {
                            br.BaseStream.Position += 40; // Byte count: 4 - radius, 12 - center, 12 - AABB min, 12 - AABB max
                            int verts = br.ReadInt32();
                            int faces = br.ReadInt32();
                            br.BaseStream.Position += verts * vert_size + faces * face_size;
                            br.BaseStream.Position += 2; // Byte count: 2 - flags
                            short chars = br.ReadInt16();
                            string path = new string(br.ReadChars(chars - 1));
                            br.BaseStream.Position += 1;

                            try {
                                if (type != (int)StaticType.Grass && type != (int)StaticType.Tree) {
                                    bool ok = stc.LoadTexture(path);
                                    if (!ok) {
                                        String warn = String.Format(strings["MissingTexture"], path, name);
                                        // MessageBox.Show(warn, "Warning", MessageBoxButtons.OK);
                                        staticsWarnings.Add(warn);
                                    }
                                }
                            } catch (ArgumentException) {
                                // warnings.Add("Warning: Texture '"+path+"' on subset "+j+" of mesh '"+pair.Key+"' could not be found");
                            }
                        }
                    }
                }
                stc.Dispose();
            }

            if (staticsWarnings.Count > 0) {
                e.Result = staticsWarnings;
            }
        }

        void workerFCreateStatics(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e != null) {
                if (e.Error != null) {
                    DumpError(e.Error);
                    MessageBox.Show(strings["StaticsError"] + "\n\n" + e.Error.ToString());
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
                if (DEBUG) {
                    allWarnings.Add("Distant statics created");
                }
                statusText.Text = strings["StaticsStatus"];
                backgroundWorker.DoWork -= workerCreateStatics;
                backgroundWorker.RunWorkerCompleted -= workerFCreateStatics;
                SaveStatSettings();
                // Enable distant statics since the user generated them
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
                File.AppendAllText(Statics.fn_dlLog, "### DEBUG ###\r\n\r\n" + string.Join("\r\n", warnings.ToArray()) + "\r\n\r\n");
                // File.AppendAllText(Statics.fn_dllog, SlimDX.ObjectTable.ReportLeaks());
            }
            var di = new DirectoryInfo(Statics.fn_dl);
            long fileSize = 0;
            int filecount = di.GetFiles().Length;
            int cells = ((filecount - 2) / 2);
            int statics;
            foreach (FileInfo fi in di.GetFiles()) {
                fileSize += fi.Length;
            }
            di = new DirectoryInfo(Statics.fn_statics);
            if (di.Exists) {
                statics = di.GetFiles().Length;
                foreach (FileInfo fi in di.GetFiles()) {
                    fileSize += fi.Length;
                }
                filecount += statics;
            } else {
                statics = 2;
            }
            di = new DirectoryInfo(Statics.fn_stattex);
            if (di.Exists) {
                filecount += di.GetFiles().Length;
                foreach (FileInfo fi in di.GetFiles()) {
                    fileSize += fi.Length;
                }
            }
            string summary = strings["Complete"] + "\r\n"
                             + strings["TotalFiles"] + filecount + "\r\n"
                             + strings["TotalSize"] + (fileSize / (1024 * 1024)) + " MB";/* + "\r\n"
                + "Total processed cells: " + cells + "\r\n"
                + "Total unique statics: " + (statics - 2);*/
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(5);
                lFinishDesc.Text += "________________________________________\r\n" + summary;
            } else {
                lFinishDesc.Text = summary;
            }
            try {
                File.AppendAllText(Statics.fn_dlLog, "########################################\r\n" + summary);
            } catch {
            }
            bFinish.Enabled = true;
        }

        private struct ExportStaticsArgs {
            public string Filename;
            public float MinSize;
            public bool Activators;
            public bool Misc;
        }

        void workerExportStatics(object sender, System.ComponentModel.DoWorkEventArgs e) {
            var args = (ExportStaticsArgs)e.Argument;
            var interiorEnables = new Dictionary<string, bool>();
            var noScriptList = new Dictionary<string, string>();

            StaticsList.Clear();
            UsedStaticsList.Clear();
            StaticMap.Clear();

            foreach (string file in files) {
                lastFileProcessed = file;
                var br = new BinaryReader(File.OpenRead(file), Statics.ESPEncoding);
                ParseFileForStatics(br, null, args.Activators, args.Misc, null, noScriptList, null);
                br.BaseStream.Position = 0;
                ParseFileForInteriors(br, interiorEnables);
                br.Close();
            }
            unsafe {
                NativeMethods.BeginStaticCreation((IntPtr)DXMain.device.ComPointer, null);
            }
            var refsToRemove = new List<string>();
            foreach (var pair in StaticsList) {
                byte[] data;
                try {
                    data = BSA.GetNif(pair.Value.Model);
                } catch {
                    data = null;
                }
                if (data == null) {
                    refsToRemove.Add(pair.Key);
                } else {
                    try {
                        float size = NativeMethods.ProcessNif(data, data.Length, 1, 1, 1);
                        if (size < 0) {
                            refsToRemove.Add(pair.Key);
                        } else {
                            pair.Value.Size = size;
                        }
                    } catch (Exception) {
                        refsToRemove.Add(pair.Key);
                    }
                }
            }
            foreach (string s in refsToRemove) {
                StaticsList.Remove(s);
            }
            foreach (string file in files) {
                var br = new BinaryReader(File.OpenRead(file));
                try {
                    ParseFileForCellsExport(br, interiorEnables, noScriptList);
                } catch {
                }
                br.Close();
            }
            var sw = new StreamWriter(args.Filename, false);
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
            + ": Where multiple objects share the same mesh, individual objects can be enabled or disabled by adding the [names] section, followed by a list of edid's, one per line\r\n"
            + ":     <object edid>[=<keyword>]\r\n"
            + ": Use 'enable' to make distant static of this object rendered even if its mesh is set to be ignored or it has disable script attached\r\n"
            + ": You may use 'disable' keyword or leave only the object edid alone (without '=') in line to disable creation of its distant static\r\n"
            + "\r\n"
            + ": There is possibility of adding (or removing) distant statics to interiors through exception list\r\n"
            + ": To do it you need to add only cell name (for enabling) or cell name followed by keyword to [interiors] section\r\n"
            + ":     <cell name>[=<keyword>]\r\n"
            + ": Where keyword can be either 'enable' for enabling generation of distant statics for specified interior, or 'disable' for disabling generation of distant statics for previously enabled interior (also behaving like exterior)\r\n"
            + "\r\n"
            + ": Distant land can support dynamic visibility of distant objects by matching either a journal index, script id or persistent unique object edid\r\n"
            + ": Visibility is updated on cell change\r\n"
            + ": See the file mge3/MGE XE Default Statics Classifiers for examples\r\n"
            + ": In the [dynamic_vis] section you can use these for dynamic visibility of scripted objects:\r\n"
            + ": All objects with the script id will have dynamic visibility. Ranges indicate when the object is visible. For ranges, the end value is not included in the range. Note that journal entries can have multiple end states >= 100.\r\n"
            + ":     <script id> = journal <journal id> start1(-end1)? [ start2(-end2)? .... start8(-end8)? ]\r\n"
            + ":     <script id> = global <global var> start1(-end1)? [ start2(-end2)? .... start8(-end8)? ]\r\n"
            + ": For dynamic visibility of unique objects with refs persist, the order is different. The unique persistent object goes first, and the dynamic visibility is read from its reference\r\n"
            + ": The right side optionally adds other objects that inherit that visibility.\r\n"
            + ":     <unique object edid> = unique_object [ 0 - 8 additional object edids ]\r\n"
            + "\r\n"
            + ": The '\\' (backslash) character is treated specially. A character directly following it will have no special meaning, and won't be converted by MGE distant statics list parser\r\n"
            + ": To use a ':' (colon) character as a part of object edid, and not a comment, you must precede it by '\\'. Then to use also a '\\' character in edid, you must precede it by another '\\' (this only applies to other than main sections)\r\n"
            + "\r\n"
            + ": NOTE: This file needs UTF-8 character encoding for non-ASCII characters that can be used in name of file or entity or interior\r\n"
            + ": If you don't see here '«»' something like '<<>>' then your text editor's current character encoding is not set to UTF-8\r\n");
            sw.Write(": This list was generated with 'min. static size' = ");
            sw.WriteLine(args.MinSize);
            sw.WriteLine();

            // Filter statics in use, merge duplicates and sort NIF paths
            var meshList = new SortedDictionary<string, Static>();
            foreach (var pair in StaticsList) {
                if (StaticMap.ContainsKey(pair.Key)) {
                    meshList[pair.Value.Model] = pair.Value;
                }
            }
            foreach (var pair in meshList) {
                sw.Write(pair.Key);
                if (pair.Key.StartsWith("grass\\")) {
                    sw.Write("=grass\t\t: size: ");
                } else if (pair.Key.StartsWith("trees\\")) {
                    sw.Write("=tree\t\t: size: ");
                } else if (pair.Key.StartsWith("x\\")) {
                    if (pair.Value.Size * 2.0f >= args.MinSize) {
                        sw.Write("=building\t\t: size: ");
                    } else {
                        sw.Write("=ignore\t\t: size: ");
                    }
                } else {
                    if (pair.Value.Size >= args.MinSize) {
                        if (pair.Key == "f\\active_blight_large.nif") {
                            sw.Write("=ignore\t\t: exception, size: ");
                        } else {
                            sw.Write("=auto\t\t: size: ");
                        }
                    } else {
                        sw.Write("=ignore\t\t: size: ");
                    }
                }
                sw.WriteLine(pair.Value.Size);
            }

            // Filter no-script statics in use, merge duplicates and sort NIF paths
            var noScriptLines = new SortedSet<string>();
            foreach (var pair in noScriptList) {
                if (StaticMap.ContainsKey(pair.Key)) {
                    noScriptLines.Add(pair.Value);
                }
            }
            foreach (var key in noScriptLines) {
                sw.WriteLine(":" + key + "=no_script\t\t: script contains disable, uncomment to ignore script");
            }

            sw.WriteLine("\r\n[names]\r\nchargen boat\r\nchargen_plank");

            sw.WriteLine("\r\n[interiors]");
            foreach (var interior in interiorEnables) {
                // Escape comment character
                sw.WriteLine(interior.Key.Replace(":", "\\:"));
            }

            sw.Close();
        }

        void workerFExportStatics(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e) {
            if (e.Error != null) {
                DumpError(e.Error);
                MessageBox.Show(strings["ExportListError"] + "\n<" + lastFileProcessed + ">\n\n" + e.Error.ToString());
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
                FullName = file.FullName.ToLowerInvariant();
                ESM = file.Extension.ToLowerInvariant() == ".esm";
                LoadOrder = file.LastWriteTimeUtc;
                Checked = CheckState.Unchecked;
            }

            public MWPlugin(FileInfo file, string dir) {
                ShortName = file.Name;
                Name = file.Name + " > " + dir;
                FullName = file.FullName.ToLowerInvariant();
                Dir = dir;
                ESM = file.Extension.ToLowerInvariant() == ".esm";
                LoadOrder = file.LastWriteTimeUtc;
                Checked = CheckState.Unchecked;
            }

            public MWPlugin(FileInfo file, bool ESM) {
                ShortName = file.Name;
                Name = file.Name;
                FullName = file.FullName.ToLowerInvariant();
                this.ESM = ESM;
                LoadOrder = file.LastWriteTimeUtc;
                Checked = CheckState.Unchecked;
            }

            public MWPlugin(FileInfo file, string dir, bool ESM) {
                ShortName = file.Name;
                Name = file.Name + " > " + dir;
                FullName = file.FullName.ToLowerInvariant();
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
                var dir = new DirectoryInfo(main);
                datafiles = dir.FullName.ToLowerInvariant();
                while (dirs.IndexOf(datafiles) != -1) {
                    dirs.Remove(datafiles);
                }

                Plugins = new Dictionary<string, MWPlugin>();
                Dirs = new List<string>(dirs);
                FileInfo[] files = dir.GetFiles("*.esm");
                foreach (FileInfo file in files) {
                    Plugins.Add(file.Name.ToLowerInvariant(), new MWPlugin(file, true));
                }
                files = dir.GetFiles("*.esp");
                foreach (FileInfo file in files) {
                    Plugins.Add(file.Name.ToLowerInvariant(), new MWPlugin(file, false));
                }
                var removeDirs = new List<string>();
                foreach (string dirName in Dirs) {
                    if (!addPluginsFromDir(dirName)) {
                        removeDirs.Add(dirName);
                    }
                }
                foreach (string dirName in removeDirs) {
                    dirs.Remove(dirName);
                }
            }

            public void SetDirs(List<string> dirs) {
                foreach (string dirName in Dirs) {
                    if (dirs.IndexOf(dirName) == -1) {
                        var entries = new List<string>();
                        foreach (KeyValuePair<string, MWPlugin> entry in Plugins) {
                            if (entry.Value.Dir != null && string.Equals(dirName, entry.Value.Dir, StringComparison.OrdinalIgnoreCase)) {
                                entries.Add(entry.Key);
                            }
                        }
                        foreach (string entry in entries) {
                            Plugins.Remove(entry);
                        }
                    }
                }
                var removeDirs = new List<string>();
                foreach (string dirName in dirs) {
                    if (Dirs.IndexOf(dirName) == -1) {
                        if (!addPluginsFromDir(dirName)) {
                            removeDirs.Add(dirName);
                        }
                    }
                }
                foreach (string dirName in removeDirs) {
                    dirs.Remove(dirName);
                }
                Dirs.Clear();
                Dirs.AddRange(dirs);
            }

            private bool addPluginsFromDir(string srcDir) {
                var dir = new DirectoryInfo(srcDir);
                string casefoldDir = srcDir.ToLowerInvariant();
                if (dir.Exists) {
                    FileInfo[] files = dir.GetFiles("*.esm");
                    foreach (FileInfo file in files) {
                        Plugins.Add(file.Name.ToLowerInvariant() + " > " + casefoldDir, new MWPlugin(file, srcDir, true));
                    }
                    files = dir.GetFiles("*.esp");
                    foreach (FileInfo file in files) {
                        Plugins.Add(file.Name.ToLowerInvariant() + " > " + casefoldDir, new MWPlugin(file, srcDir, false));
                    }
                    return true;
                }
                return false;
            }

            public KeyValuePair<string, MWPlugin>[] ByName {
                get {
                    var temp = new List<KeyValuePair<string, MWPlugin>>(Plugins);
                    temp.Sort(delegate(KeyValuePair<string, MWPlugin> firstPair, KeyValuePair<string, MWPlugin> nextPair) {
                        return string.Compare(firstPair.Value.ShortName, nextPair.Value.ShortName, StringComparison.CurrentCulture);
                    });
                    return temp.ToArray();
                }
            }

            public KeyValuePair<string, MWPlugin>[] ByType {
                get {
                    var temp = new List<KeyValuePair<string, MWPlugin>>(Plugins);
                    temp.Sort(delegate(KeyValuePair<string, MWPlugin> firstPair, KeyValuePair<string, MWPlugin> nextPair) {
                        if (firstPair.Value.ESM != nextPair.Value.ESM) {
                            return firstPair.Value.ESM ? -1 : 1;
                        }
                        if (firstPair.Value.Dir != nextPair.Value.Dir) {
                            return string.Compare(firstPair.Value.FullName, nextPair.Value.FullName, StringComparison.CurrentCulture);
                        }
                        return string.Compare(firstPair.Value.ShortName, nextPair.Value.ShortName, StringComparison.CurrentCulture);
                    });
                    return temp.ToArray();
                }
            }

            public KeyValuePair<string, MWPlugin>[] ByLoadOrder {
                get {
                    var temp = new List<KeyValuePair<string, MWPlugin>>(Plugins);
                    temp.Sort(delegate(KeyValuePair<string, MWPlugin> firstPair, KeyValuePair<string, MWPlugin> nextPair) {
                        if (firstPair.Value.ESM != nextPair.Value.ESM) {
                            return firstPair.Value.ESM ? -1 : 1;
                        }
                        return firstPair.Value.LoadOrder.CompareTo(nextPair.Value.LoadOrder);
                    });
                    return temp.ToArray();
                }
            }

            public string[] getSelected() {
                var s = new List<string>();
                foreach (KeyValuePair<string, MWPlugin> temp in Plugins) {
                    if (temp.Value.Checked == CheckState.Checked) {
                        s.Add(temp.Key);
                    }
                }
                return s.ToArray();
            }
        }

        /* Plugins tab handlers */

        private void bPlugsFromINI_Click(object sender, EventArgs e) {
            // morrowind.ini uses system codepage
            var sr = new StreamReader(Statics.fn_mwini, System.Text.Encoding.Default);

            bool InModList = false;
            var ActivePlugins = new List<string>();
            while (!sr.EndOfStream) {
                string s = sr.ReadLine().Trim().ToLower(Statics.Culture);
                if (s.Length == 0) {
                    continue;
                }
                if (!InModList) {
                    if (s == "[game files]") {
                        InModList = true;
                    }
                } else {
                    if (s[0] == '[' && s.EndsWith("]")) {
                        InModList = false;
                        continue;
                    }
                    if (s.StartsWith("gamefile")) {
                        int index = s.IndexOf(';');
                        if (index != -1) {
                            s = s.Remove(index, s.Length - index);
                        }
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
            // Check that at least one mod is selected
            if (clbPlugsModList.CheckedItems.Count == 0) {
                MessageBox.Show(strings["NoPluginsSelected"], Statics.strings["Error"]);
                return;
            }

            // Create list of files
            files = new string[clbPlugsModList.CheckedItems.Count];
            if (files.Length != preselectedPlugins.Length) {
                pluginListChanged = true;
            } else {
                var tmp1 = new List<string>(pluginList.getSelected());
                var tmp2 = new List<string>(preselectedPlugins);
                tmp1.Sort();
                tmp2.Sort();
                for (int i = 0; i < tmp1.Count; i++) {
                    if (!string.Equals(tmp1[i], tmp2[i], StringComparison.OrdinalIgnoreCase)) {
                        pluginListChanged = true;
                        break;
                    }
                }
            }

            KeyValuePair<string, MWPlugin>[] list = pluginList.ByLoadOrder;
            int j = 0;
            foreach (KeyValuePair<string, MWPlugin> item in list) {
                if (item.Value.Checked == CheckState.Checked) {
                    files[j++] = item.Value.FullName;
                }
            }

            // Continue
            if (configure) {
                startSetup();
            } else {
                SetupFlags["ChkLandAuto"] = pluginListChanged || cmbMeshWorldDetail.SelectedIndex == -1;
                SetupFlags["EnaLandAuto"] = cmbMeshWorldDetail.SelectedIndex != -1;
                SetupFlags["EnaLandTex"] = Exists;
                SetupFlags["EnaLandMesh"] = Exists;
                SetupFlags["EnaStatics"] = Exists;

                var runSetupForm = new RunSetupForm(SetupFlags);
                runSetupForm.FormClosed += new FormClosedEventHandler(runSetupForm_FormClosed);
                runSetupForm.ShowDialog();
            }
        }

        private void clbPlugsModList_ItemCheck(object sender, System.Windows.Forms.ItemCheckEventArgs e) {
            string s = clbPlugsModList.Items[e.Index].ToString();
            pluginList.Plugins[s.ToLowerInvariant()].Checked = e.NewValue;
        }

        private void bPlugsClear_Click(object sender, EventArgs e) {
            if (clbPlugsModList.Items.Count > 0) {
                for (int i = 0; i < clbPlugsModList.Items.Count; i++) {
                    clbPlugsModList.SetItemChecked(i, false);
                }
            }
        }

        private void bPlugsAll_Click(object sender, EventArgs e) {
            if (clbPlugsModList.Items.Count > 0) {
                for (int i = 0; i < clbPlugsModList.Items.Count; i++) {
                    clbPlugsModList.SetItemChecked(i, true);
                }
            }
        }

        private void bPlugsDirs_Click(object sender, EventArgs e) {
            var dirsForm = new DirectoriesForm(datafiles, pluginDirs);
            dirsForm.FormClosed += new FormClosedEventHandler(dirsForm_FormClosed);
            dirsForm.ShowDialog();
        }

        private void dirsForm_FormClosed(object sender, EventArgs e) {
            pluginList.SetDirs(pluginDirs);
            pluginsSort(sender, e);
        }

        private bool DEBUG = false;

        private void runSetupForm_FormClosed(object sender, EventArgs e) {
            if (SetupFlags["AutoRun"]) {
                pluginListChanged = SetupFlags["ChkLandAuto"];
            }
            DEBUG = SetupFlags["Debug"];
            if (SetupFlags["RunSetup"]) {
                startSetup();
            }
        }

        /* Plugins tab methods */

        private void pluginsSort(object sender, EventArgs e) {
            if (pluginList == null) {
                return;
            }
            KeyValuePair<string, MWPlugin>[] list;
            if (rbPlugsName.Checked) {
                list = pluginList.ByName;
            } else if (rbPlugsType.Checked) {
                list = pluginList.ByType;
            } else {
                list = pluginList.ByLoadOrder;
            }
            clbPlugsModList.Items.Clear();
            foreach (var item in list) {
                int index = clbPlugsModList.Items.Count;
                clbPlugsModList.Items.Add(item.Value.Name);
                clbPlugsModList.SetItemCheckState(index, item.Value.Checked);
            }
        }

        private void SelectPlugins(string[] plugins) {
            foreach (string s in plugins) {
                if (!pluginList.Plugins.ContainsKey(s.ToLowerInvariant())) {
                    continue;
                }
                int index = clbPlugsModList.Items.IndexOf(pluginList.Plugins[s.ToLowerInvariant()].Name);
                if (index != -1) {
                    clbPlugsModList.SetItemChecked(index, true);
                }
            }
        }

        private void startSetup() {
            ChangingPage = true;
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(0);
                tabControl.SelectedIndex = 4;
            } else {
                tabControl.SelectedIndex = 1;
            }
            if (DEBUG) {
                allWarnings.Add("Loading plugin land data");
            }
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
            if (cmbMeshWorldDetail.SelectedIndex == -1) {
                cmbMeshWorldDetail_auto = true;
                cmbMeshWorldDetail.SelectedIndex = 2;
                cmbMeshWorldDetail.SelectedIndexChanged += new EventHandler(cmbMeshWorldDetail_SelectedIndexChanged);
                lMeshAutoInfo.Visible = true;
                if (DEBUG) {
                    allWarnings.Add("World mesh auto-set to " + cmbMeshWorldDetail.Text);
                }
            } else {
                lMeshAutoInfo.Visible = false;
            }
            LTEX.ReleaseCache();
            statusText.Text = strings["LandTextureSkip"];
            statusWarnings.Text = strings["NoWarnings"];
            statusWarnings.Enabled = false;
            if (SetupFlags["AutoRun"]) {
                setFinishDesc(2);
                if (SetupFlags["ChkLandMesh"]) {
                    bMeshRun_Click(null, null);
                } else {
                    bMeshSkip_Click(null, null);
                }
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
            if (cmbMeshWorldDetail.SelectedIndex == -1) {
                cmbMeshWorldDetail_auto = true;
                cmbMeshWorldDetail.SelectedIndex = 2;
                cmbMeshWorldDetail.SelectedIndexChanged += new EventHandler(cmbMeshWorldDetail_SelectedIndexChanged);
                lMeshAutoInfo.Visible = true;
                if (DEBUG) {
                    allWarnings.Add("World mesh auto-set to " + cmbMeshWorldDetail.Text);
                }
            } else {
                lMeshAutoInfo.Visible = false;
            }
            if (!SetupFlags["AutoRun"]) {
                ChangingPage = true;
                tabControl.SelectedIndex = 2;
            }
            if (DEBUG) {
                allWarnings.Add("Creating world textures");
            }
            statusText.Text = strings["LandTextureCreate"];
            statusProgress.Maximum = AtlasSpanY * Atlas.Count;
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.DoWork += workerCreateTextures;
            backgroundWorker.RunWorkerCompleted += workerFCreateTextures;
            statusWarnings.Text = strings["NoWarnings"];
            statusWarnings.Enabled = false;

            var args = new CreateTextureArgs();
            args.WorldRes = 128 << cmbTexWorldResolution.SelectedIndex;
            args.WorldNormal = 128 << cmbTexWorldNormalRes.SelectedIndex;
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
            if (lbStatOverrideList.Items.Count == 0) {
                lStatOverrideList.Visible = true;
            }
            if (!SetupFlags["AutoRun"]) {
                ChangingPage = true;
                tabControl.SelectedIndex = 3;
            }
            if (DEBUG) {
                allWarnings.Add("Creating world meshes");
            }
            statusText.Text = strings["LandMeshCreate"];
            statusProgress.Maximum = 100;
            backgroundWorker.WorkerReportsProgress = true;
            backgroundWorker.DoWork += workerCreateMeshes;
            backgroundWorker.RunWorkerCompleted += workerFCreateMeshes;
            statusWarnings.Text = strings["NoWarnings"];
            statusWarnings.Enabled = false;

            var cma = new CreateMeshArgs();
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
                if (SetupFlags["ChkStatics"]) {
                    bStatRun_Click(null, null);
                } else {
                    bStatSkip_Click(null, null);
                }
            } else {
                if (lbStatOverrideList.Items.Count == 0) {
                    lStatOverrideList.Visible = true;
                }
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
            var bw = new BinaryWriter(File.Create(path));

            for (int x = 0; x < 65; x++) {
                for (int y = 0; y < 65; y++) {
                    bw.Write((float)(x * 128));
                    bw.Write((float)(y * 128));
                    bw.Write((float)(land.Heights[x, y] * 8));
                    bw.Write(land.Normals[x, y].X);
                    bw.Write(land.Normals[x, y].Y);
                    bw.Write(land.Normals[x, y].Z);
                    // Need to offset the border texcoords slightly to avoid lines between meshes
                    if (x == 0) {
                        bw.Write(0.005f);
                    } else if (x == 64) {
                        bw.Write(0.997f);
                    } else {
                        bw.Write((float)x / 64.0f);
                    }
                    if (y == 0) {
                        bw.Write(0.005f);
                    } else if (y == 64) {
                        bw.Write(0.997f);
                    } else {
                        bw.Write((float)y / 64.0f);
                    }
                }
            }
            bw.Close();
        }

        /* Land mesh methods */

        private void GenerateWorldMesh(int detail, string path) {
            // Landscape detail selection
            float tolerance = 125.0f;
            if (detail >= 0 && detail <= 4) {
                var toleranceOptions = new float[] { 15.0f, 70.0f, 125.0f, 180.0f, 235.0f };
                tolerance = toleranceOptions[detail];
            }

            // Produce packed atlas data
            var atlas_data = new float[8 * Atlas.Count];
            var iAtlas = 0;
            foreach (var r in Atlas) {
                atlas_data[iAtlas + 0] = r.MinX * 8192.0f;
                atlas_data[iAtlas + 1] = r.MaxX * 8192.0f;
                atlas_data[iAtlas + 2] = r.MinY * 8192.0f;
                atlas_data[iAtlas + 3] = r.MaxY * 8192.0f;
                atlas_data[iAtlas + 4] = r.OffsetX * 8192.0f;
                atlas_data[iAtlas + 5] = r.OffsetY * 8192.0f;
                atlas_data[iAtlas + 6] = AtlasSpanX * 8192.0f;
                atlas_data[iAtlas + 7] = AtlasSpanY * 8192.0f;
                iAtlas += 8;
            }

            // Ensure previous landscape data is erased
            if (File.Exists(path)) {
                File.Delete(path);
            }

            // Generate optimized landscape mesh
            foreach (var r in Atlas) {
                // Produce atlas region heightmap array
                int RegionSpanX = r.MaxX - r.MinX + 1;
                int RegionSpanY = r.MaxY - r.MinY + 1;
                int DataSpanX = RegionSpanX * 64;
                int DataSpanY = RegionSpanY * 64;
                var height_data = new float[DataSpanX * DataSpanY];
    
                for (int y1 = r.MinY; y1 <= r.MaxY; y1++) {
                    for (int y2 = 0; y2 < 64; y2++) {
                        for (int x1 = r.MinX; x1 <= r.MaxX; x1++) {
                            for (int x2 = 0; x2 < 64; x2++) {
                                int y = (y1 - r.MinY) * 64 + y2;
                                int x = (x1 - r.MinX) * 64 + x2;
                                if (LandMap[x1, y1] != null) {
                                    height_data[y * DataSpanX + x] = (float)LandMap[x1, y1].Heights[x2, y2] * 8.0f;
                                } else {
                                    height_data[y * DataSpanX + x] = -2048.0f;
                                }
                            }
                        }
                    }
                }
    
                float minX = (float)r.MinX * 8192.0f;
                float maxX = (float)(r.MaxX + 1) * 8192.0f;
                float minY = (float)r.MinY * 8192.0f;
                float maxY = (float)(r.MaxY + 1) * 8192.0f;
    
                backgroundWorker.ReportProgress(10, strings["LandTessellating"]);
                NativeMethods.TessellateLandscapeAtlased(path, height_data, (uint)DataSpanX, (uint)DataSpanY, atlas_data, (uint)Atlas.Count, minX, minY, maxX, maxY, tolerance);
            }
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
        }

        private class StaticToRemove {

            public readonly string Worldspace;
            public readonly string Reference;

            public StaticToRemove(string worldspace, string reference) {
                Worldspace = worldspace;
                Reference = reference;
            }

        }

        private class Static {

            public readonly string Name;
            public readonly string Model;
            public float Size;
            public int VisIndex;

            public Static(string name, string model) {
                Name = name.ToLower(Statics.Culture);
                Model = model.ToLower(Statics.Culture);
                Size = 0;
                VisIndex = 0;
            }

        }

        private class StaticReference {

            public string Name;
            public float X, Y, Z;
            public float Yaw, Pitch, Roll;
            public float Scale;
            public uint StaticID;
            public int VisIndex;

            public void SetID(Static s, Dictionary<string, uint> staticMap) {
                string file = s.Model;

                if (staticMap.ContainsKey(file)) {
                    StaticID = staticMap[file];
                } else {
                    StaticID = (uint)staticMap.Count;
                    staticMap[file] = StaticID;
                }

                VisIndex = s.VisIndex;
            }

            public void Write(BinaryWriter bw) {
                bw.Write(StaticID);
                bw.Write((ushort)VisIndex);
                bw.Write(X);
                bw.Write(Y);
                bw.Write(Z);
                bw.Write(Yaw);
                bw.Write(Pitch);
                bw.Write(Roll);
                bw.Write(Scale);
            }

        }

        private class StaticOverride {

            public bool Ignore;
            public StaticType Type;
            public float? Simplify;
            public float Density;
            public bool NoScript;
            public bool NamesNoIgnore;

            public StaticOverride(string value) {
                Ignore = false;
                Type = StaticType.Auto;
                Simplify = null;
                Density = -1;
                NoScript = false;
                NamesNoIgnore = false;

                string[] keys = value.ToLowerInvariant().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                foreach (string s in keys) {
                    if (s == "ignore") {
                        Ignore = true;
                    } else if (s == "near") {
                        Type = StaticType.Near;
                    } else if (s == "auto") {
                        Type = StaticType.Auto;
                    } else if (s == "far") {
                        Type = StaticType.Far;
                    } else if (s == "very_far") {
                        Type = StaticType.VeryFar;
                    } else if (s.StartsWith("grass")) {
                        float percent;
                        Type = StaticType.Grass;
                        if (s.Length > 6 && float.TryParse(s.Remove(0, 6), out percent) && percent >= 0) {
                            if (percent > 100) {
                                Density = 1.0f;
                            } else {
                                Density = percent / 100.0f;
                            }
                        }
                    } else if (s == "tree") {
                        Type = StaticType.Tree;
                    } else if (s == "building") {
                        Type = StaticType.Building;
                    } else if (s == "no_script") {
                        NoScript = true;
                    } else if (s.StartsWith("reduction_")) {
                        float percent;
                        if (float.TryParse(s.Remove(0, 10), out percent) && percent >= 0 && percent <= 100) {
                            Simplify = percent / 100.0f;
                        }
                    }
                }
            }

            public StaticOverride(StaticOverride value, bool enabledInNames) {
                Ignore = value.Ignore;
                Type = value.Type;
                Simplify = value.Simplify;
                Density = value.Density;
                NoScript = value.NoScript;
                NamesNoIgnore = enabledInNames;
            }

        }

        private class DynamicVisGroup {
            
            public int Index;
            public bool Valid;
            public readonly string JournalId, GlobalId, UniqueObjId;
            public readonly List<Tuple<int, int>> EnabledRanges;
            public readonly List<string> LinkedObjIds;

            public DynamicVisGroup(string key, string value) {
                Index = -1;
                Valid = false;
                JournalId = null;
                GlobalId = null;
                UniqueObjId = null;
                EnabledRanges = new List<Tuple<int, int>>();
                LinkedObjIds = new List<string>();

                string[] tokens = value.ToLowerInvariant().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                if (tokens[0] == "journal" && tokens.Length >= 2) {
                    JournalId = tokens[1];
                }
                else if (tokens[0] == "global" && tokens.Length >= 2) {
                    GlobalId = tokens[1];
                }
                else if (tokens[0] == "unique_object") {
                    UniqueObjId = key;
                }
                else {
                    return;
                }

                if (JournalId != null || GlobalId != null) {
                    // Parse up to 8 range parameters of the format (int | int-int)
                    for (int i = 2; i < tokens.Length; ++i) {
                        string s = tokens[i];
                        int index = s.IndexOf('-');
                        int start = 0, end = 0;
                        bool ok;
    
                        if (index != -1) {
                            ok = Int32.TryParse(s.Substring(0, index), out start);
                            ok = ok && Int32.TryParse(s.Substring(index+1), out end);
                        }
                        else {
                            ok = Int32.TryParse(s, out start);
                            end = start + 1;
                        }
                        if (ok && EnabledRanges.Count < 8) {
                            EnabledRanges.Add(new Tuple<int,int>(start, end));
                        }
                    }
                    Valid = true;
                }
                else if (UniqueObjId != null) {
                    // Enabled objects have state 1
                    EnabledRanges.Add(new Tuple<int, int>(1, 2));

                    // Take list of object names, replace "unique_object" with vis source object name
                    LinkedObjIds = new List<string>(tokens);
                    LinkedObjIds[0] = key;
                    Valid = true;
                }
            }
            
            public override bool Equals(object obj) {
                DynamicVisGroup other = obj as DynamicVisGroup;
                if (other == null) { return false; }
                
                return JournalId == other.JournalId
                    && GlobalId == other.GlobalId
                    && UniqueObjId == other.UniqueObjId
                    && System.Linq.Enumerable.SequenceEqual(EnabledRanges, other.EnabledRanges)
                    && System.Linq.Enumerable.SequenceEqual(LinkedObjIds, other.LinkedObjIds);
            }
            
            public override int GetHashCode() {
                return 17*JournalId.GetHashCode() + 53*GlobalId.GetHashCode() + 109*UniqueObjId.GetHashCode();
            }

            private enum DataSource {
                Journal = 1,
                Global = 2,
                UniqueObject = 3
            }

            public void Write(BinaryWriter bw) {
                if (JournalId != null) {
                    bw.Write((byte)DataSource.Journal);
                    bw.Write(JournalId.PadRight(64, '\0').ToCharArray());
                }
                else if (GlobalId != null) {
                    bw.Write((byte)DataSource.Global);
                    bw.Write(GlobalId.PadRight(64, '\0').ToCharArray());
                }
                else if (UniqueObjId != null) {
                    bw.Write((byte)DataSource.UniqueObject);
                    bw.Write(UniqueObjId.PadRight(64, '\0').ToCharArray());
                }
                else {
                    throw new InvalidOperationException("Invalid DynamicVisGroup state");
                }

                bw.Write((byte)EnabledRanges.Count);
                foreach (var range in EnabledRanges) {
                    bw.Write(range.Item1);
                    bw.Write(range.Item2);
                }
                for (int filler = 8 - EnabledRanges.Count; filler > 0; filler--) {
                    bw.Write((Int64)0);
                }
            }
        }
        
        class DynamicVisDataSet {
            public List<DynamicVisGroup> visGroups;
            public Dictionary<string, DynamicVisGroup> scripts;
            public Dictionary<string, DynamicVisGroup> uniqueObjects;
            
            public DynamicVisDataSet() {
                visGroups = new List<DynamicVisGroup>();
                scripts = new Dictionary<string, DynamicVisGroup>();
                uniqueObjects = new Dictionary<string, DynamicVisGroup>();
            }
            
            public DynamicVisGroup AddMerge(DynamicVisGroup visGroup) {
                // Return existing vis group if there is a match, else add it to the collection.
                foreach (var v in visGroups) {
                    if (v.Equals(visGroup)) {
                        return v;
                    }
                }
                visGroups.Add(visGroup);
                return visGroup;
            }
            
            public void Assign(string key, DynamicVisGroup visGroup) {
                if (visGroup.JournalId != null || visGroup.GlobalId != null) {
                   scripts[key] = visGroup;
                }
                else if (visGroup.UniqueObjId != null) {
                    foreach (var o in visGroup.LinkedObjIds) {
                        uniqueObjects[o] = visGroup;
                    }
                }
            }
        }

        /* Statics tab handlers */

        private void bStatExportStatics_Click(object sender, EventArgs e) {
            if (saveStaticListDialog.ShowDialog() != DialogResult.OK) {
                return;
            }
            bStatExportStatics.Enabled = false;
            bStatSkip.Enabled = false;
            bStatRun.Enabled = false;

            var args = new ExportStaticsArgs();
            args.Filename = saveStaticListDialog.FileName;
            args.Activators = cbStatActivators.Checked;
            args.Misc = cbStatIncludeMisc.Checked;
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
                if (!StaticsExist && MessageBox.Show(strings["ConfirmSkipStatics"], Statics.strings["Warning"], MessageBoxButtons.YesNo) != DialogResult.Yes) {
                    return;
                }
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
                Directory.Delete(Statics.fn_statics, true);
            }
            ushort temp = (ushort)udStatMinSize.Value;
            var csa = new CreateStaticsArgs();
            csa.MinSize = temp;
            // Save the value of the minimum static size to the main screen
            Statics.mf.tbDLNearSize.Text = udStatMinSize.Text;
            csa.MipSkip = cmbStatSkipMipLevels.SelectedIndex;
            csa.Activators = cbStatActivators.Checked;
            csa.Misc = cbStatIncludeMisc.Checked;
            csa.UseOverrideList = cbStatOverrideList.Checked;
            csa.OverrideFiles = new List<string>();
            csa.OverrideFiles.Add(Statics.fn_dlDefaultOverride);
            foreach (OverrideListItem item in lbStatOverrideList.Items) {
                csa.OverrideFiles.Add(item.FileName);
            }
            if (!SetupFlags["AutoRun"]) {
                ChangingPage = true;
                tabControl.SelectedIndex = 4;
            }
            if (DEBUG) {
                allWarnings.Add("Parsing plugins for possible statics");
            }
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

        private void ParseFileForDisableScripts(BinaryReader br) {
            var rr = new RecordReader(br);
            while (rr.NextRecord()) {
                if (rr.Tag == "SCPT") {
                    string text = null;
                    string name = null;
                    while (rr.NextSubrecord()) {
                        switch (rr.SubTag) {
                            case "SCHD":
                                name = rr.ReadCString().ToLower(Statics.Culture);
                                break;
                            case "SCTX":
                                text = new string(br.ReadChars((int)rr.SubrecordSize)).ToLower(Statics.Culture);
                                break;
                        }
                    }
                    if (name != null && text != null) {
                        if (text.Contains("disable")) {
                            DisableScripts[name] = true;
                        }
                    }
                }
            }
        }

        private void ParseFileForStatics(BinaryReader br, Dictionary<string, StaticOverride> overrideList, bool includeActivators, bool includeMisc, Dictionary<string, bool> namedObjectDisables, Dictionary<string, string> noScriptList, DynamicVisDataSet dynamicVisDataSet) {
            int DEBUG_statics = 0;
            int DEBUG_ignored = 0;

            // Look for any scripts that might be disabling activators
            if (includeActivators) {
                ParseFileForDisableScripts(br);
                // Reset file position
                br.BaseStream.Position = 0;
            }

            var rr = new RecordReader(br);
            while (rr.NextRecord()) {
                bool staticTag = rr.Tag == "STAT" || rr.Tag == "GCVR"; // GCVR extension in OpenCS
                bool activatorTag = rr.Tag == "ACTI";
                bool miscTag = rr.Tag == "DOOR" || rr.Tag == "CONT" || rr.Tag == "LIGH";
                
                if (staticTag || activatorTag || miscTag) {
                    string name = null;
                    string model = null;
                    string script = null;

                    while (rr.NextSubrecord()) {
                        switch (rr.SubTag) {
                            case "NAME":
                                name = rr.ReadCString().ToLower(Statics.Culture);
                                break;
                            case "MODL":
                                model = rr.ReadCString().ToLower(Statics.Culture);
                                break;
                            case "SCRI":
                                script = rr.ReadCString().ToLowerInvariant();
                                break;
                        }
                    }

                    if (name != null && model != null && model.Trim() != string.Empty) {
                        // Dynamic vis, match on script or object ID
                        if (dynamicVisDataSet != null) {
                            DynamicVisGroup dvg = null;

                            if (script != null) {
                                dynamicVisDataSet.scripts.TryGetValue(script, out dvg);
                            }
                            if (dvg == null) {
                                dynamicVisDataSet.uniqueObjects.TryGetValue(name, out dvg);
                            }

                            if (dvg != null) {
                                // Set object with vis group
                                var s = new Static(name, model);
                                s.VisIndex = dvg.Index;
                                StaticsList[name] = s;
    
                                DEBUG_statics++;
                                continue;
                            }
                        }

                        // no_script override
                        if (script != null && overrideList != null && overrideList.ContainsKey(model) && overrideList[model].NoScript) {
                            script = null;
                        }

                        // Named exceptions
                        if (namedObjectDisables != null && namedObjectDisables.ContainsKey(name)) {
                            if (!namedObjectDisables[name]) {
                                // Object set to enabled, bypassing nif ignore and disable script
                                StaticsList[name] = new Static(name, model);

                                // Flag that the nif is used despite the ignore flag
                                if (overrideList != null && overrideList.ContainsKey(model) && overrideList[model].Ignore) {
                                    overrideList[model] = new StaticOverride(overrideList[model], true);
                                }
                                DEBUG_statics++;
                                continue;
                            }
                            DEBUG_ignored++;
                            continue;
                        }

                        bool ignore;
                        if (overrideList != null && overrideList.ContainsKey(model)) {
                            ignore = overrideList[model].Ignore;
                        } else {
                            ignore = (miscTag && !includeMisc) || (activatorTag && !includeActivators);
                        }

                        if (!ignore && script != null && DisableScripts != null && DisableScripts.ContainsKey(script) && DisableScripts[script]) {
                            // no_script detection for static list exporter
                            if (noScriptList != null) {
                                noScriptList[name] = model;
                            }
                            ignore = true;
                        }

                        if (!ignore) {
                            StaticsList[name] = new Static(name, model);
                            DEBUG_statics++;
                        }
                        else {
                            DEBUG_ignored++;
                        }
                    }
                }
            }
            if (DEBUG) {
                allWarnings.Add("Static definitions: " + DEBUG_statics + "; Ignored definitions: " + DEBUG_ignored);
            }
        }

        private void ParseFileForCells(BinaryReader br, string pluginName, Dictionary<string, bool> namedObjectDisables, Dictionary<string, bool> interiorEnables) {
            var masters = new List<string>() { pluginName.ToLower(Statics.Culture) };

            if (DEBUG) {
                allWarnings.Add("PLUGIN=" + masters[0]);
            }
            int DEBUG_cells = 0;
            int DEBUG_refs = 0;
            int DEBUG_added = 0;
            int DEBUG_moved = 0;
            int DEBUG_deleted = 0;

            var rr = new RecordReader(br);
            while (rr.NextRecord()) {
                switch (rr.Tag) {
                    case "TES3":
                        while (rr.NextSubrecord()) {
                            if (rr.SubTag == "MAST") {
                                masters.Add(rr.ReadSubrecordString().ToLower(Statics.Culture));
                                if (DEBUG) {
                                    allWarnings.Add("MASTER[" + (masters.Count - 1) + "]=" + masters[masters.Count - 1]);
                                }
                            }
                        }
                        break;
                    case "CELL":
                        if (DEBUG) {
                            DEBUG_cells++;
                        }
                        string cellName = "";
                        bool isValidCell = false;
                        bool inReference = false;
                        bool referenceHasScale = false;
                        bool referenceDeleted = false;
                        bool readData = false;
                        bool isInterior = false;
                        uint refID = 0;
                        int mastID = 0;
                        int cellX = 0;
                        int cellY = 0;

                        var sr = new StaticReference();
                        while (rr.NextSubrecord()) {
                            switch (rr.SubTag) {
                                case "DATA":
                                    if (!inReference) {
                                        if (readData) {
                                            break;
                                        }
                                        uint flags = br.ReadUInt32();
                                        bool isInteriorExterior = (flags & 0x81) == 0x81;
                                        bool isInteriorWater = (flags & 0x83) == 0x03;
                                        isInterior = (flags & 0x1) == 0x1;
                                        if (!isInterior || (cbStatIntExt.Checked && isInteriorExterior) || (cbStatIntWater.Checked && isInteriorWater)) {
                                            isValidCell = true;
                                        }
                                        if (isInterior && interiorEnables.ContainsKey(cellName.ToLower(Statics.Culture))) {
                                            isValidCell = interiorEnables[cellName.ToLower(Statics.Culture)];
                                        }
                                        cellX = br.ReadInt32();
                                        cellY = br.ReadInt32();
                                        readData = true;
                                    } else {
                                        sr.X = br.ReadSingle();
                                        sr.Y = br.ReadSingle();
                                        sr.Z = br.ReadSingle();
                                        sr.Yaw = br.ReadSingle();
                                        sr.Pitch = br.ReadSingle();
                                        sr.Roll = br.ReadSingle();
                                    }
                                    break;
                                case "FRMR":
                                    if (DEBUG) {
                                        DEBUG_refs++;
                                    }
                                    if (!isValidCell) {
                                        break;
                                    }
                                    if (inReference) {
                                        if (!referenceHasScale) {
                                            sr.Scale = 1;
                                        }

                                        Static stat;
                                        StaticsList.TryGetValue(sr.Name, out stat);
                                        if (stat != null && (stat.VisIndex > 0 || !namedObjectDisables.ContainsKey(sr.Name) || !namedObjectDisables[sr.Name])) {
                                            sr.SetID(stat, StaticMap);
                                            string worldspace = isInterior ? cellName : "";
                                            string referenceFullyQualified = masters[mastID] + "\u0001" + (isInterior ? "" : cellX + "\u0002" + cellY + "\u0001") + refID;
                                            if (referenceDeleted) {
                                                if (UsedStaticsList.ContainsKey(worldspace) && UsedStaticsList[worldspace].ContainsKey(referenceFullyQualified)) {
                                                    UsedStaticsList[worldspace].Remove(referenceFullyQualified);
                                                }
                                            } else {
                                                if (!UsedStaticsList.ContainsKey(worldspace)) {
                                                    UsedStaticsList.Add(worldspace, new Dictionary<string, StaticReference>());
                                                }
                                                UsedStaticsList[worldspace][referenceFullyQualified] = sr;
                                            }
                                            if (DEBUG) {
                                                if (referenceDeleted) {
                                                    ++DEBUG_deleted;
                                                } else if (mastID > 0) {
                                                    ++DEBUG_moved;
                                                } else {
                                                    ++DEBUG_added;
                                                }
                                            }
                                        }
                                    }
                                    refID = br.ReadUInt32();
                                    mastID = (int)(refID >> 24);
                                    refID &= 0x00FFFFFF;
                                    sr = new StaticReference();
                                    inReference = true;
                                    referenceHasScale = false;
                                    referenceDeleted = false;
                                    break;
                                case "DELE":
                                    referenceDeleted = true;
                                    break;
                                case "NAME":
                                    if (inReference) {
                                        sr.Name = rr.ReadSubrecordString().ToLower(Statics.Culture);
                                    } else {
                                        cellName = rr.ReadSubrecordString();
                                    }
                                    break;
                                case "XSCL":
                                    if (!inReference) {
                                        break;
                                    }
                                    sr.Scale = br.ReadSingle();
                                    if (sr.Scale == 0) { sr.Scale = 1.0f; }
                                    referenceHasScale = true;
                                    break;
                            }
                        }
                        if (inReference) {
                            if (!referenceHasScale) {
                                sr.Scale = 1;
                            }

                            Static stat;
                            StaticsList.TryGetValue(sr.Name, out stat);
                            if (stat != null && (stat.VisIndex > 0 || !namedObjectDisables.ContainsKey(sr.Name) || !namedObjectDisables[sr.Name])) {
                                sr.SetID(stat, StaticMap);
                                string worldspace = isInterior ? cellName : "";
                                string referenceFullyQualified = masters[mastID] + "\u0001" + (isInterior ? "" : cellX + "\u0002" + cellY + "\u0001") + refID;

                                if (referenceDeleted) {
                                    if (UsedStaticsList.ContainsKey(worldspace) && UsedStaticsList[worldspace].ContainsKey(referenceFullyQualified)) {
                                        UsedStaticsList[worldspace].Remove(referenceFullyQualified);
                                    }
                                } else {
                                    if (!UsedStaticsList.ContainsKey(worldspace)) {
                                        UsedStaticsList.Add(worldspace, new Dictionary<string, StaticReference>());
                                    }
                                    UsedStaticsList[worldspace][referenceFullyQualified] = sr;
                                }
                                if (DEBUG) {
                                    if (referenceDeleted) {
                                        ++DEBUG_deleted;
                                    } else if (mastID > 0) {
                                        ++DEBUG_moved;
                                    } else {
                                        ++DEBUG_added;
                                    }
                                }
                            }
                        }
                        break;
                }
            }
            if (DEBUG) {
                allWarnings.Add("Scanning summary for: " + pluginName + " : " + DEBUG_cells + " cells : " + DEBUG_refs + " refs : " + DEBUG_added + " added : " + DEBUG_moved + " moved : " + DEBUG_deleted + " deleted");
            }
        }

        private void ParseFileForCellsExport(BinaryReader br, Dictionary<string, bool> interiorEnables, Dictionary<string, string> noScriptList) {
            var rr = new RecordReader(br);
            while (rr.NextRecord()) {
                if (rr.Tag == "CELL") {
                    string cellName = "";
                    bool isValidCell = false;
                    bool isInterior = false;
                    bool inReference = false;
                    bool readData = false;

                    while (rr.NextSubrecord()) {
                        switch (rr.SubTag) {
                            case "DATA":
                                if (!inReference && !readData) {
                                    uint flags = br.ReadUInt32();
                                    isInterior = (flags & 0x1) == 0x1;
                                    readData = true;
                                }
                                break;
                            case "FRMR":
                                isValidCell = !isInterior || interiorEnables.ContainsKey(cellName.ToLower(Statics.Culture));
                                inReference = true;
                                break;
                            case "NAME":
                                if (inReference) {
                                    string sname = rr.ReadCString().ToLower(Statics.Culture);
                                    if (StaticsList.ContainsKey(sname) || noScriptList.ContainsKey(sname)) {
                                        StaticMap[sname] = 1;
                                    }
                                } else {
                                    cellName = rr.ReadSubrecordString();
                                }
                                break;
                        }
                        if (inReference && !isValidCell) {
                            break;
                        }
                    }
                }
            }
        }

        private void ParseFileForInteriors(BinaryReader br, Dictionary<string, bool> interiorEnables) {
            var rr = new RecordReader(br);
            while (rr.NextRecord()) {
                if (rr.Tag == "CELL") {
                    string cellName = "";
                    bool inReference = false;
                    bool readData = false;
                    bool isInterior = false;
                    uint cellFlags = 0;
                    float cellMinX = float.MaxValue, cellMinY = float.MaxValue, cellMinZ = float.MaxValue;
                    float cellMaxX = float.MinValue, cellMaxY = float.MinValue, cellMaxZ = float.MinValue;

                    while (rr.NextSubrecord()) {
                        switch (rr.SubTag) {
                            case "DATA":
                                if (!inReference && !readData) {
                                    cellFlags = br.ReadUInt32();
                                    readData = true;
                                    isInterior = (cellFlags & 0x1) == 0x1;
                                } else if (inReference) {
                                    float x = br.ReadSingle();
                                    float y = br.ReadSingle();
                                    float z = br.ReadSingle();
                                    cellMinX = Math.Min(cellMinX, x);
                                    cellMinY = Math.Min(cellMinY, y);
                                    cellMinZ = Math.Min(cellMinZ, z);
                                    cellMaxX = Math.Max(cellMaxX, x);
                                    cellMaxY = Math.Max(cellMaxY, y);
                                    cellMaxZ = Math.Max(cellMaxZ, z);
                                }
                                break;
                            case "FRMR":
                                inReference = true;
                                break;
                            case "NAME":
                                if (!inReference) {
                                    cellName = rr.ReadSubrecordString();
                                }
                                break;
                        }

                        if (readData && !isInterior) {
                            break;
                        }
                    }

                    if (isInterior) {
                        const float largeCellSpan = 10000.0f;
                        bool isInteriorExterior = (cellFlags & 0x81) == 0x81;
                        bool isInteriorWater = (cellFlags & 0x83) == 0x03;
                        float span = cellMaxX - cellMinX;
                        span = Math.Max(span, cellMaxY - cellMinY);
                        span = Math.Max(span, cellMaxZ - cellMinZ);

                        if ((cbStatIntExt.Checked && isInteriorExterior)
                            || (cbStatIntWater.Checked && isInteriorWater)
                            || (cbStatLargeInt.Checked && span >= largeCellSpan)) {
                            interiorEnables[cellName.ToLower(Statics.Culture)] = true;
                        }
                    }
                }
            }
        }

        /* Finish tab handlers */

        private void bFinish_Click(object sender, EventArgs e) {
            File.WriteAllBytes(Statics.fn_dlver, new byte[] { Statics.DistantLandVersion });
            // If the user generated everything they need for distant land, go ahead and enable it
            if (File.Exists(Statics.fn_dlver) && File.Exists(Statics.fn_world) && File.Exists(Statics.fn_worldds) && File.Exists(Statics.fn_worldn)) {
                Statics.mf.cbDLDistantLand.Checked = true;
            }
            ChangingPage = true;
            Statics.mf.tabControl.SelectedIndex = 7;
            Close();
        }

        /* Finish tab methods */

        private void setFinishDesc(int stage) {
            const string spc = "   ";
            const string mark = "» ";
            var text = new StringBuilder();

            if (SetupFlags["ChkLandTex"]) {
                text.AppendLine((stage == 1 ? mark : spc) + (stage > 1 ? strings["SummaryStage1Complete"] : strings["SummaryStage1Working"]));
            } else {
                text.AppendLine((stage == 1 ? mark : spc) + strings["SummaryStage1Skip"]);
            }

            if (SetupFlags["ChkLandMesh"]) {
                text.AppendLine((stage == 2 ? mark : spc) + (stage > 2 ? strings["SummaryStage2Complete"] : strings["SummaryStage2Working"]));
            } else {
                text.AppendLine((stage == 2 ? mark : spc) + strings["SummaryStage2Skip"]);
            }

            if (SetupFlags["ChkStatics"]) {
                text.AppendLine((stage == 3 ? mark : spc) + (stage > 3 ? strings["SummaryStage3Complete"] : strings["SummaryStage3Working"]));
            } else {
                text.AppendLine((stage == 3 ? mark : spc) + strings["SummaryStage3Skip"]);
            }

            if (SetupFlags["ChkStatics"]) {
                text.AppendLine((stage == 4 ? mark : spc) + (stage > 4 ? strings["SummaryStage4Complete"] : strings["SummaryStage4Working"]));
            } else {
                text.AppendLine((stage == 4 ? mark : spc) + strings["SummaryStage4Skip"]);
            }

            Action update = () => lFinishDesc.Text = text.ToString();
            lFinishDesc.BeginInvoke(update);
        }

        void cmbTexWorldResolution_SelectedIndexChanged(object sender, EventArgs e) {
            // Calcuate usage for DXT1 texture with mip-maps
            Int64 extent = 128 << cmbTexWorldResolution.SelectedIndex;
            extent = (extent * extent * 1333 / 1000 + 1048576) / 2097152;

            lTexWorldMemUse.Text = strings["VideoMemUse"] + extent.ToString() + "MB";
        }

        void cmbTexWorldNormalRes_SelectedIndexChanged(object sender, EventArgs e) {
            // Calcuate usage for uncompressed texture with mip-maps
            Int64 extent = 128 << cmbTexWorldNormalRes.SelectedIndex;
            extent = (extent * extent * 1333 / 1000 + 131072) / 262144;

            lTexNormalMemUse.Text = strings["VideoMemUse"] + extent.ToString() + "MB";
        }
    }
}
