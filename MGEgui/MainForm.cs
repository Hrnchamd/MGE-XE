using System;
using CancelEventArgs = System.ComponentModel.CancelEventArgs;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Drawing;
using RegistryKey = Microsoft.Win32.RegistryKey;
using Registry = Microsoft.Win32.Registry;
using System.IO;
using MGEgui.DirectX;
using MGEgui.INI;
using MGEgui.Localization;
using System.Runtime.InteropServices;

namespace MGEgui {

    public partial class MainForm : Form {
        // imports to check for shared memory feature support
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern IntPtr LoadLibraryA(string dllToLoad);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool FreeLibrary(IntPtr hModule);

        private bool Save = true;
        private bool loading = true;
        private string clearedSSDir;

        public MainForm(bool AutoLang) {
            InitializeComponent();
            // Attach dud context menus to combo boxes
            cmbAntiAlias.ContextMenu = DudMenu;
            cmbAnisoLevel.ContextMenu = DudMenu;
            cmbFogMode.ContextMenu = DudMenu;
            cmbVWait.ContextMenu = DudMenu;
            cmbSShotSuffix.ContextMenu = DudMenu;
            cmbSShotFormat.ContextMenu = DudMenu;
            cmbTipReadSpd.ContextMenu = DudMenu;
            cmbMsgsLocale.ContextMenu = DudMenu;
            cmbUILanguage.ContextMenu = DudMenu;
            // Set initial directories
            this.OpenFileDialog.InitialDirectory = this.SaveFileDialog.InitialDirectory = Statics.runDir + "\\MGE3";
            // Title
            Text = Statics.programName + " " + Statics.versionNumber;
            // Set default tooltip text reading speed
            Statics.tipReadSpeed = (int)(1000 / double.Parse(cmbTipReadSpd.Text));
            // set a handler for each control which sets tooltip popup timeout dependent on tooltip text length
            Control[] controls = Statics.GetChildControls(this);
            foreach (Control control in controls) {
                control.MouseHover += new EventHandler(TooltipTimeoutHandler);
            }
            // Save control text
            clearedSSDir = tbSShotDir.Text;
            // Get available UI localizations and set UI language
            cmbUILanguage.Items.AddRange(Statics.Localizations.Languages);
            if (AutoLang) {
                cbUILangAuto.Checked = true;
            } else {
                cmbUILanguage.SelectedIndex = cmbUILanguage.FindStringExact(Statics.Localizations.Current);
            }

            // Load settings
            LoadSettings();
        }

        public static Dictionary<string, string> strings = new Dictionary<string, string>();

#region tooltip_messages
        public Dictionary<string, string[]> tooltip_messages = new Dictionary<string, string[]> {
            /* Settings */
            { "ClearINI", new string [] { "cbClearINI" } },
            { "ResetSettings", new string [] { "bResetSettings" } },
            { "Help", new string [] { "bHelp" } },
            { "Import", new string [] { "bImport" } },
            { "Export", new string [] { "bExport" } },
            { "ViewCaps", new string [] { "bViewCaps" } },
            { "About", new string [] { "bAbout" } },
            { "UILanguage", new string [] { "lUILanguage", "cmbUILanguage" } },
            { "UILangAuto", new string [] { "cbUILangAuto" } },
            { "TipReadSpd", new string [] { "lTipReadSpd", "cmbTipReadSpd", "lTipRSpdUnit" } },

            /* Graphics */
            { "Resolution", new string [] { "tbResolution", "lResolution" } },
            { "SelectResolution", new string [] { "bSelectResolution" } },
            { "Windowed", new string [] { "cbWindowed" } },
            { "Borderless", new string [] { "cbBorderless" } },
            { "Aspect", new string [] { "tbAspect", "lAspect" } },
            { "RefreshRate", new string [] { "tbRefreshRate", "lRefreshRate" } },
            { "AntiAlias", new string [] { "cmbAntiAlias", "lAntiAlias" } },
            { "AnisoLevel", new string [] { "cmbAnisoLevel", "lAnisoLevel" } },
            { "VWait", new string [] { "cmbVWait", "lVWait" } },
            { "HWShader", new string [] { "cbHWShader" } },
            { "ShaderEd", new string [] { "bShaderEd" } },
            { "FPSCounter", new string [] { "cbFPSCounter" } },
            { "ReduceTextureMemUse", new string[] { "cbReduceTextureMemUse" } },
            { "FOV", new string [] { "udFOV", "lFOV" } },
            { "AutoFOV", new string [] { "cbAutoFOV" } },
            { "FPSLimit", new string [] { "udFPSLimit", "lFPSLimit" } },
            { "LOD", new string [] { "udLOD", "lLOD" } },
            { "UIScale", new string [] { "udUIScale", "lUIScale" } },
            { "FogMode", new string [] { "cmbFogMode", "lFogMode" } },
            { "SShotFormat", new string [] { "cmbSShotFormat", "lSShotFormat" } },
            { "SShotName", new string [] { "lSShotName", "tbSShotName" } },
            { "SShotSuffix", new string [] { "cmbSShotSuffix", "lSShotSuffix" } },
            { "SShotDir", new string [] { "lSShotDir", "tbSShotDir" } },
            { "SShotDirBrowse", new string [] { "bSShotDirBrowse" } },
            { "SShotDirClear", new string [] { "bSShotDirClear" } },
            { "UseSharedMemory", new string [] { "cbUseSharedMemory" } },

            /* Distant Land */
            { "DistantLandWizard", new string [] { "bDistantLandWizard" } },
            { "DLDistantLand", new string [] { "cbDLDistantLand" } },
            { "DLDrawDist", new string [] { "udDLDrawDist", "lDLDrawDist" } },
            { "DLAutoDist", new string [] { "cbDLAutoDist" } },
            { "DLAutoByDrawDist", new string [] { "rbDLAutoByDrawDist" } },
            { "DLAutoByAFogEnd", new string [] { "rbDLAutoByAFogEnd" } },
            { "DLDistantStatics", new string [] { "cbDLDistantStatics" } },
            { "DLDynRipples", new string [] { "cbDLDynRipples" } },
            { "DLNearSize", new string [] { "tbDLNearSize" } },
            { "DLDistNear", new string [] { "udDLDistNear" } },
            { "DLSizeFar", new string [] { "udDLSizeFar" } },
            { "DLDistFar", new string [] { "udDLDistFar" } },
            { "DLSizeVeryFar", new string [] { "udDLSizeVeryFar" } },
            { "DLDistVeryFar", new string [] { "udDLDistVeryFar" } },
            { "DLFogAStart", new string [] { "udDLFogAStart" } },
            { "DLFogAEnd", new string [] { "udDLFogAEnd" } },
            { "DLFogBStart", new string [] { "udDLFogBStart" } },
            { "DLFogBEnd", new string [] { "udDLFogBEnd" } },
            { "DLFogExp", new string [] { "cbDLFogExp" } },
            { "DLFogExpMul", new string [] { "lDLFogExpMul", "udDLFogExpMul" } },
            { "DLFogIStart", new string [] { "udDLFogIStart" } },
            { "DLFogIEnd", new string [] { "udDLFogIEnd" } },
            { "DLReflBlur", new string [] { "cbDLReflBlur" } },
            { "DLReflLand", new string [] { "cbDLReflLand" } },
            { "DLReflNStatics", new string [] { "cbDLReflNStatics" } },
            { "DLReflIntr", new string [] { "cbDLReflInterior" } },
            { "DLScatter", new string [] { "cbDLScattering" } },
            { "DLSkyRefl", new string [] { "cbDLSkyRefl" } },
            { "DLWthr", new string [] { "bDLWthr" } },
            { "DLWtrCaust", new string [] { "udDLWtrCaust", "lDLWtrCaust" } },
            { "DLWtrWave", new string [] { "udDLWtrWave", "lDLWtrWave" } },
            { "DLSunShadows", new string[] { "cbDLSunShadows" } },
            { "PerPixelLighting", new string[] { "cbPerPixelLighting" } },
            { "LightSettings", new string[] { "bMWLightSettings" } },

            /* In-game */
            { "DisableMGE", new string [] { "cbDisableMGE" } },
            { "DisableMWSE", new string [] { "cbDisableMWSE" } },
            { "D3D8To9Only", new String [] { "cbD3D8To9Only" } },
            { "SkipMovie", new string [] { "cbSkipMovie" } },
            { "AltCombat", new string [] { "cbAltCombat" } },
            { "AutoCrosshair", new string [] { "cbAutoCrosshair" } },
            { "MenuCaching", new string [] { "cbMenuCaching" } },
            { "MacroEd", new string [] { "bMacroEd" } },
            { "Remapper", new string [] { "bRemapper" } },
            { "Cam3rdPrsn", new string [] { "cbCam3rdPrsn" } },
            { "Cam3rdX", new string [] { "lCam3rdX", "udCam3rdX" } },
            { "Cam3rdY", new string [] { "lCam3rdY", "udCam3rdY" } },
            { "Cam3rdZ", new string [] { "lCam3rdZ", "udCam3rdZ" } },
            { "DisplayMessages", new string [] { "cbDisplayMessages" } },
            { "MsgsTime", new string [] { "lMsgsTime", "udMsgsTime", "lMsgsTimeUnit" } },

            /* Morrowind.ini */
            { "Screenshots", new string [] { "cbScreenshots" } },
            { "YesToAll", new string [] { "cbYesToAll" } },
            { "HQShadows", new string [] { "cbHQShadows" } },
            { "ThreadLoad", new string [] { "cbThreadLoad" } },
            { "ShowFPS", new string [] { "cbShowFPS" } },
            { "Audio", new string [] { "cbAudio" } },
            { "Subtitles", new string [] { "cbSubtitles" } },
            { "HitFader", new string [] { "cbHitFader" } },
            { "MWLighting", new string [] { "gbMWLighting", "udLightingQuad", "udLightingLinear", "udLightingConst" } },
        };
#endregion

        private const string smwiniGeneral = "General";
        private const string smwiniLighting = "LightAttenuation";

#region morrowind_ini_variable_definitions
        private static INIFile.INIVariableDef mwiniFPSLimit = new INIFile.INIVariableDef("FPSLimit", smwiniGeneral, "Max FPS", INIFile.INIVariableType.Int32, "240");
        private static INIFile.INIVariableDef mwiniSSEnable = new INIFile.INIVariableDef("SSEnable", smwiniGeneral, "Screen Shot Enable", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniNoThread = new INIFile.INIVariableDef("NoThread", smwiniGeneral, "DontThreadLoad", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniYesToAll = new INIFile.INIVariableDef("YesToAll", smwiniGeneral, "allowyestoall", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniHDShadow = new INIFile.INIVariableDef("HDShadow", smwiniGeneral, "High Detail Shadows", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniShowFPS = new INIFile.INIVariableDef("ShowFPS", smwiniGeneral, "Show FPS", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniAudioOff = new INIFile.INIVariableDef("AudioOff", smwiniGeneral, "Disable Audio", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniSubtitles = new INIFile.INIVariableDef("Subtitles", smwiniGeneral, "Subtitles", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniHitFader = new INIFile.INIVariableDef("HitFader", smwiniGeneral, "ShowHitFader", INIFile.INIBoolType.Number, "1");
        private static INIFile.INIVariableDef mwiniMultiCS = new INIFile.INIVariableDef("MultiCS", smwiniGeneral, "AllowMultipleEditors", INIFile.INIBoolType.Number, "0");

        private static INIFile.INIVariableDef mwiniLightUseConst = new INIFile.INIVariableDef("UseConstant", smwiniLighting, "UseConstant", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniLightUseLin = new INIFile.INIVariableDef("UseLinear", smwiniLighting, "UseLinear", INIFile.INIBoolType.Number, "1");
        private static INIFile.INIVariableDef mwiniLightUseQuad = new INIFile.INIVariableDef("UseQuadratic", smwiniLighting, "UseQuadratic", INIFile.INIBoolType.Number, "0");
        private static INIFile.INIVariableDef mwiniLightValConst = new INIFile.INIVariableDef("ConstantValue", smwiniLighting, "ConstantValue", INIFile.INIVariableType.Single, "0", 0, 100, 3);
        private static INIFile.INIVariableDef mwiniLightValLin = new INIFile.INIVariableDef("LinearValue", smwiniLighting, "LinearValue", INIFile.INIVariableType.Single, "3", 0, 100, 3);
        private static INIFile.INIVariableDef mwiniLightValQuad = new INIFile.INIVariableDef("QuadraticValue", smwiniLighting, "QuadraticValue", INIFile.INIVariableType.Single, "0", 0, 100, 3);
#endregion

        private static INIFile.INIVariableDef[] mwSettings = new INIFile.INIVariableDef [] {
            mwiniFPSLimit, mwiniSSEnable, mwiniNoThread, mwiniYesToAll, mwiniHDShadow,
            mwiniShowFPS, mwiniAudioOff, mwiniSubtitles, mwiniHitFader,
            mwiniMultiCS, mwiniLightUseConst, mwiniLightValConst, mwiniLightUseLin,
            mwiniLightValLin, mwiniLightUseQuad, mwiniLightValQuad
        };

        private void LoadMWINI() {
            // morrowind.ini uses system codepage
            var mwini = new INIFile(Statics.fn_mwini, mwSettings, System.Text.Encoding.Default);

            // Clamp to FPS control maximum
            udFPSLimit.Value = Math.Min(new Decimal(mwini.getKeyValue("FPSLimit")), udFPSLimit.Maximum);

            cbScreenshots.Checked = (mwini.getKeyValue("SSEnable") == 1);
            cbThreadLoad.Checked = (mwini.getKeyValue("NoThread") != 1);
            cbYesToAll.Checked = (mwini.getKeyValue("YesToAll") == 1);
            cbHQShadows.Checked = (mwini.getKeyValue("HDShadow") == 1);
            cbShowFPS.Checked = (mwini.getKeyValue("ShowFPS") == 1);
            cbAudio.Checked = (mwini.getKeyValue("AudioOff") == 1);
            cbSubtitles.Checked = (mwini.getKeyValue("Subtitles") == 1);
            cbHitFader.Checked = (mwini.getKeyValue("HitFader") == 1);

            if (mwini.getKeyValue("UseConstant") == 1) {
                udLightingConst.Value = new Decimal(mwini.getKeyValue("ConstantValue"));
            }
            if (mwini.getKeyValue("UseLinear") == 1) {
                udLightingLinear.Value = new Decimal(mwini.getKeyValue("LinearValue"));
            }
            if (mwini.getKeyValue("UseQuadratic") == 1) {
                udLightingQuad.Value = new Decimal(mwini.getKeyValue("QuadraticValue"));
            }
        }

        private static Dictionary<string, double> antiAliasDict = new Dictionary<string, double> {
            { "None", 0 },
            { "2x", 1 },
            { "4x", 2 },
            { "8x", 3 }
        };

        private static Dictionary<string, double> zBufferDict = new Dictionary<string, double> {
            { "D24S8", 0 },
            { "D24X8", 1 },
            { "D32", 2 },
            { "D16", 3 },
            { "D16L", 4 },
            { "D32FL", 5 },
            { "INTZ", 6 },
            { "RAWZ", 7 },
            { "DF16", 8 },
            { "DF24", 9 }
        };

        private static Dictionary<string, double> vWaitDict = new Dictionary<string, double> {
            { "Immediate", 0 },
            { "1", 1 },
            { "2", 2 },
            { "3", 3 },
            { "4", 4 }
        };

        private static Dictionary<string, double> refreshDict = new Dictionary<string, double> {
            { "Default", 0 }
        };

        private static Dictionary<string, double> ssFormatDict = new Dictionary<string, double> {
            { "BMP", 0 },
            { "JPEG", 1 },
            { "DDS", 2 },
            { "PNG", 3 },
            { "TGA", 4 }
        };

        private static Dictionary<string, double> ssSuffixDict = new Dictionary<string, double> {
            { "Timestamp", 0 },
            { "Ordinal", 1 },
            { "Character Name, Ordinal", 2 },
            { "Character Name, Game Time, Ordinal", 3 }
        };

        private static Dictionary<string, double> anisoLevelDict = new Dictionary<string, double> {
            { "Off", 0 },
            { "2x", 1 },
            { "4x", 2 },
            { "8x", 3 },
            { "16x", 4 }
        };

        private static Dictionary<string, double> fogModeDict = new Dictionary<string, double> {
            { "Depth pixel", 0 },
            { "Depth vertex", 1 },
            { "Range vertex", 2 }
        };

        private static Dictionary<string, double> autoDistDict = new Dictionary<string, double> {
            { "By Draw Distance", 1 },
            { "By Above Water Fog End", 2 }
        };

        private static Dictionary<string, double> pplFlagsDict = new Dictionary<string, double> {
            { "Always", 0 },
            { "Interiors only", 1 }
        };
        
        private static Dictionary<string, double> windowAlignDict = new Dictionary<string, double> {
            { "Left", 0 },
            { "Center", 1 },
            { "Right", 2 }
        };

        private static Dictionary<string, double> tipSpeedDict = new Dictionary<string, double> {
            { "5cps", 0 },
            { "6.25cps", 1 },
            { "7.5cps", 2 },
            { "8.75cps", 3 },
            { "10cps", 4 },
            { "12.5cps", 5 },
            { "15cps", 6 },
            { "17.5cps", 7 },
            { "20cps", 8 },
            { "25cps", 9 },
            { "30cps", 10 },
            { "35cps", 11 },
            { "40cps", 12 },
            { "50cps", 13 },
            { "60cps", 14 },
            { "70cps", 15 }
        };

        private const string siniMain = "Main";
        private const string siniGlobGraph = "Global Graphics";
        private const string siniRendState = "Render State";
        private const string siniInput = "Input";
        private const string siniMisc = "Misc";
        private const string siniDL = "Distant Land";

#region mge_ini_variable_definitions
        // Config
        private static INIFile.INIVariableDef iniVersion = new INIFile.INIVariableDef("Version", siniMain, "Version", INIFile.INIVariableType.String, Statics.versionString);
        private static INIFile.INIVariableDef iniTipSpeed = new INIFile.INIVariableDef("TipSpeed", siniMain, "Tooltip Reading Speed", INIFile.INIVariableType.Dictionary, "15cps", tipSpeedDict);
        public static INIFile.INIVariableDef iniLanguage = new INIFile.INIVariableDef("Language", siniMain, "GUI Language", INIFile.INIVariableType.String, "English (default)");
        public static INIFile.INIVariableDef iniAutoLang = new INIFile.INIVariableDef("AutoLang", siniMain, "Language Autodetection", INIFile.INIBoolType.Text, "True");
        // Graphics
        private static INIFile.INIVariableDef iniAntiAlias = new INIFile.INIVariableDef("AntiAlias", siniGlobGraph, "Antialiasing Level", INIFile.INIVariableType.Dictionary, "None", antiAliasDict);
        private static INIFile.INIVariableDef iniVWait = new INIFile.INIVariableDef("VWait", siniGlobGraph, "VWait", INIFile.INIVariableType.Dictionary, "Immediate", vWaitDict);
        private static INIFile.INIVariableDef iniRefresh = new INIFile.INIVariableDef("Refresh", siniGlobGraph, "Refresh Rate", INIFile.INIVariableType.Byte, "Default", refreshDict, 0, 240);
        private static INIFile.INIVariableDef iniBorderless = new INIFile.INIVariableDef("Borderless", siniGlobGraph, "Borderless Window", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniAnisoLvl = new INIFile.INIVariableDef("AnisoLvl", siniRendState, "Anisotropic Filtering Level", INIFile.INIVariableType.Dictionary, "8x", anisoLevelDict);
        private static INIFile.INIVariableDef iniFogMode = new INIFile.INIVariableDef("FogMode", siniRendState, "Fog Mode", INIFile.INIVariableType.Dictionary, "Range vertex", fogModeDict);
        private static INIFile.INIVariableDef iniTransparencyAA = new INIFile.INIVariableDef("TrAA", siniRendState, "Transparency Antialiasing", INIFile.INIBoolType.OnOff, "On");
        private static INIFile.INIVariableDef iniMessages = new INIFile.INIVariableDef("Messages", siniRendState, "MGE Messages", INIFile.INIBoolType.OnOff, "On");
        private static INIFile.INIVariableDef iniMsgTime = new INIFile.INIVariableDef("MsgTime", siniRendState, "MGE Messages Timeout", INIFile.INIVariableType.UInt16, "2000", 500, 50000);
        private static INIFile.INIVariableDef iniHWShader = new INIFile.INIVariableDef("HWShader", siniRendState, "Hardware Shader", INIFile.INIBoolType.OnOff, "Off");
        private static INIFile.INIVariableDef iniFPSCount = new INIFile.INIVariableDef("FPSCount", siniRendState, "MGE FPS Counter", INIFile.INIBoolType.OnOff, "Off");
        private static INIFile.INIVariableDef iniReduceTexMemUse = new INIFile.INIVariableDef("ReduceTexMemUse", siniRendState, "Reduce Texture Memory Use", INIFile.INIBoolType.OnOff, "On");
        private static INIFile.INIVariableDef iniHDRTime = new INIFile.INIVariableDef("HDRTime", siniRendState, "HDR Reaction Time", INIFile.INIVariableType.Single, "2", 0.01, 30, 2);
        private static INIFile.INIVariableDef iniFOVAuto = new INIFile.INIVariableDef("FOVAuto", siniRendState, "Match FOV To Aspect Ratio", INIFile.INIBoolType.OnOff, "On");
        private static INIFile.INIVariableDef iniFOV = new INIFile.INIVariableDef("FOV", siniRendState, "Horizontal Screen FOV", INIFile.INIVariableType.Single, "75", 5, 150, 2);
        private static INIFile.INIVariableDef iniUIScale = new INIFile.INIVariableDef("UIScale", siniRendState, "UI Scaling", INIFile.INIVariableType.Single, "1", 0.5, 5, 3);
        private static INIFile.INIVariableDef iniWindowAlignX = new INIFile.INIVariableDef("WindowAlignX", siniRendState, "Window Align X", INIFile.INIVariableType.Dictionary, "Center", windowAlignDict);
        private static INIFile.INIVariableDef iniWindowAlignY = new INIFile.INIVariableDef("WindowAlignY", siniRendState, "Window Align Y", INIFile.INIVariableType.Dictionary, "Center", windowAlignDict);
        private static INIFile.INIVariableDef iniSSFormat = new INIFile.INIVariableDef("SSFormat", siniRendState, "Screenshot Format", INIFile.INIVariableType.Dictionary, "PNG", ssFormatDict);
        private static INIFile.INIVariableDef iniSSSuffix = new INIFile.INIVariableDef("SSSuffix", siniRendState, "Screenshot Name Suffix", INIFile.INIVariableType.Dictionary, "Timestamp", ssSuffixDict);
        private static INIFile.INIVariableDef iniSSName = new INIFile.INIVariableDef("SSName", siniRendState, "Screenshot Name Prefix", INIFile.INIVariableType.String, "Morrowind");
        private static INIFile.INIVariableDef iniSSDir = new INIFile.INIVariableDef("SSDir", siniRendState, "Screenshot Output Directory", INIFile.INIVariableType.String, "");
        private static INIFile.INIVariableDef iniUseSharedMemory = new INIFile.INIVariableDef("UseSharedMemory", siniMisc, "Use Shared Memory", INIFile.INIBoolType.Text, "False");
        // In-game
        private static INIFile.INIVariableDef iniDisableMGE = new INIFile.INIVariableDef("DisableMGE", siniMisc, "MGE Disabled", INIFile.INIBoolType.Text, "False");
        private static INIFile.INIVariableDef iniDisableMWSE = new INIFile.INIVariableDef("DisableMWSE", siniMisc, "Internal MWSE Disabled", INIFile.INIBoolType.Text, "False");
        private static INIFile.INIVariableDef iniD3D8To9Only = new INIFile.INIVariableDef("D3D8To9Only", siniMisc, "Only Proxy D3D8To9", INIFile.INIBoolType.Text, "False");
        private static INIFile.INIVariableDef iniSkipIntro = new INIFile.INIVariableDef("SkipIntro", siniMisc, "Skip Intro Movies", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniAltCombat = new INIFile.INIVariableDef("AltCombat", siniMisc, "Daggerfall Combat Controls", INIFile.INIBoolType.Text, "False");
        private static INIFile.INIVariableDef iniCam3rdCustom = new INIFile.INIVariableDef("Cam3rdCustom", siniMisc, "Customize 3rd Person Camera", INIFile.INIBoolType.Text, "False");
        private static INIFile.INIVariableDef iniCam3rdX = new INIFile.INIVariableDef("Cam3rdX", siniMisc, "Initial 3rd Person Camera X", INIFile.INIVariableType.Single, "0", -125, 125, 1);
        private static INIFile.INIVariableDef iniCam3rdY = new INIFile.INIVariableDef("Cam3rdY", siniMisc, "Initial 3rd Person Camera Y", INIFile.INIVariableType.Single, "-160", -2500, -25, 1);
        private static INIFile.INIVariableDef iniCam3rdZ = new INIFile.INIVariableDef("Cam3rdZ", siniMisc, "Initial 3rd Person Camera Z", INIFile.INIVariableType.Single, "0", -125, 125, 1);
        private static INIFile.INIVariableDef iniAutoCrosshair = new INIFile.INIVariableDef("AutoCrosshair", siniMisc, "Crosshair Autohide", INIFile.INIBoolType.Text, "False");
        private static INIFile.INIVariableDef iniMenuCaching = new INIFile.INIVariableDef("MenuCaching", siniMisc, "Use Menu Background Caching", INIFile.INIBoolType.Text, "True");
        // Distant Land
        private static INIFile.INIVariableDef iniDistLand = new INIFile.INIVariableDef("DistLand", siniDL, "Distant Land", INIFile.INIBoolType.OnOff, "Off");
        private static INIFile.INIVariableDef iniDrawDist = new INIFile.INIVariableDef("DrawDist", siniDL, "Draw Distance", INIFile.INIVariableType.Single, "5", 1, 300, 1);
        private static INIFile.INIVariableDef iniAutoDist = new INIFile.INIVariableDef("AutoDist", siniDL, "Auto Distances", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniAutoDistBy = new INIFile.INIVariableDef("AutoDistBy", siniDL, "Auto Distances Choice", INIFile.INIVariableType.Dictionary, "By Draw Distance", autoDistDict);
        private static INIFile.INIVariableDef iniDistStat = new INIFile.INIVariableDef("DistStat", siniDL, "Distant Statics", INIFile.INIBoolType.OnOff, "Off");
        private static INIFile.INIVariableDef iniSizeFar = new INIFile.INIVariableDef("SizeFar", siniDL, "Far Static Min Size", INIFile.INIVariableType.UInt16, "600", 0, 9999);
        private static INIFile.INIVariableDef iniSizeVFar = new INIFile.INIVariableDef("SizeVFar", siniDL, "Very Far Static Min Size", INIFile.INIVariableType.UInt16, "800", 0, 9999);
        private static INIFile.INIVariableDef iniEndNear = new INIFile.INIVariableDef("EndNear", siniDL, "Near Statics End", INIFile.INIVariableType.Single, "2", 2, 299.8, 1);
        private static INIFile.INIVariableDef iniEndFar = new INIFile.INIVariableDef("EndFar", siniDL, "Far Statics End", INIFile.INIVariableType.Single, "4", 2.1, 299.9, 1);
        private static INIFile.INIVariableDef iniEndVFar = new INIFile.INIVariableDef("EndVFar", siniDL, "Very Far Statics End", INIFile.INIVariableType.Single, "5", 2.2, 300, 1);
        private static INIFile.INIVariableDef iniAboveBeg = new INIFile.INIVariableDef("AboveBeg", siniDL, "Above Water Fog Start", INIFile.INIVariableType.Single, "2", 0, 299.9, 1);
        private static INIFile.INIVariableDef iniAboveEnd = new INIFile.INIVariableDef("AboveEnd", siniDL, "Above Water Fog End", INIFile.INIVariableType.Single, "5", 0.1, 300, 1);
        private static INIFile.INIVariableDef iniBelowBeg = new INIFile.INIVariableDef("BelowBeg", siniDL, "Below Water Fog Start", INIFile.INIVariableType.Single, "-0.5", -99.9, 299.9, 1);
        private static INIFile.INIVariableDef iniBelowEnd = new INIFile.INIVariableDef("BelowEnd", siniDL, "Below Water Fog End", INIFile.INIVariableType.Single, "0.3", 0.1, 300, 1);
        private static INIFile.INIVariableDef iniInterBeg = new INIFile.INIVariableDef("InterBeg", siniDL, "Interior Fog Start", INIFile.INIVariableType.Single, "0", -0.9, 299.9, 2);
        private static INIFile.INIVariableDef iniInterEnd = new INIFile.INIVariableDef("InterEnd", siniDL, "Interior Fog End", INIFile.INIVariableType.Single, "2.0", 0.1, 300, 2);
        private static INIFile.INIVariableDef iniReflLand = new INIFile.INIVariableDef("ReflLand", siniDL, "Water Reflects Land", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniReflNear = new INIFile.INIVariableDef("ReflNear", siniDL, "Water Reflects Near Statics", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniReflIntr = new INIFile.INIVariableDef("ReflIntr", siniDL, "Water Reflects Interiors", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniSkyRefl = new INIFile.INIVariableDef("SkyRefl", siniDL, "Enable Sky Reflections", INIFile.INIBoolType.Text, "True");
        private static INIFile.INIVariableDef iniDynRipples = new INIFile.INIVariableDef("DynRipples", siniDL, "Dynamic Ripples", INIFile.INIBoolType.Text, "False");
        private static INIFile.INIVariableDef iniReflBlur = new INIFile.INIVariableDef("ReflBlur", siniDL, "Blur Water Reflections", INIFile.INIBoolType.OnOff, "Off");
        private static INIFile.INIVariableDef iniExpFog = new INIFile.INIVariableDef("ExpFog", siniDL, "Use Exponential Fog", INIFile.INIBoolType.YesNo, "Yes");
        private static INIFile.INIVariableDef iniDLExpMul = new INIFile.INIVariableDef("DLExpMul", siniDL, "Exponential Distance Multiplier", INIFile.INIVariableType.Single, "4.0", 2.5, 5.0, 2);
        private static INIFile.INIVariableDef iniScattering = new INIFile.INIVariableDef("Scatter", siniDL, "Use Atmosphere Scattering", INIFile.INIBoolType.YesNo, "Yes");
        private static INIFile.INIVariableDef iniWaveHght = new INIFile.INIVariableDef("WaveHght", siniDL, "Water Wave Height", INIFile.INIVariableType.Byte, "50", 0, 250);
        private static INIFile.INIVariableDef iniCaustics = new INIFile.INIVariableDef("Caustics", siniDL, "Water Caustics Intensity", INIFile.INIVariableType.Byte, "50", 0, 100);
        private static INIFile.INIVariableDef iniShadows = new INIFile.INIVariableDef("SunShadows", siniDL, "Sun Shadows", INIFile.INIBoolType.OnOff, "On");
        private static INIFile.INIVariableDef iniShadowDetail = new INIFile.INIVariableDef("SunShadowDetail", siniDL, "Sun Shadow Map Resolution", INIFile.INIVariableType.UInt32, "2048", 1024, 2048);
        private static INIFile.INIVariableDef iniPixelLighting = new INIFile.INIVariableDef("PPLighting", siniDL, "Per Pixel Shader", INIFile.INIBoolType.OnOff, "Off");
        private static INIFile.INIVariableDef iniPixelLightingFlags = new INIFile.INIVariableDef("PPLightingFlags", siniDL, "Per Pixel Shader Flags", INIFile.INIVariableType.Dictionary, "Always", pplFlagsDict);
#endregion

        private static INIFile.INIVariableDef[] iniSettings = {
            INIFile.iniDefEmpty,
            // Main
            iniVersion, iniTipSpeed, iniLanguage, iniAutoLang,
            // Graphics
            iniAntiAlias, iniAnisoLvl, iniTransparencyAA, iniVWait, iniRefresh, iniBorderless,
            iniFOVAuto, iniFOV, iniUIScale, iniWindowAlignX, iniWindowAlignY,
            iniFogMode, iniHWShader, iniHDRTime, iniFPSCount, iniReduceTexMemUse,
            iniSSFormat, iniSSSuffix, iniSSName, iniSSDir, iniUseSharedMemory,
            // In-game
            iniDisableMGE, iniDisableMWSE, iniD3D8To9Only,
            iniSkipIntro, iniAltCombat,
            iniCam3rdCustom, iniCam3rdX, iniCam3rdY, iniCam3rdZ,
            iniAutoCrosshair, iniMenuCaching,
            iniMessages, iniMsgTime,
            // Distant Land
            iniDistLand, iniDrawDist,
            iniDistStat, iniAutoDist, iniAutoDistBy,
            iniEndNear, iniEndFar, iniEndVFar, iniSizeFar,
            iniSizeVFar, iniReflLand, iniReflNear, iniReflIntr,
            iniAboveBeg, iniAboveEnd, iniBelowBeg, iniBelowEnd,
            iniInterBeg, iniInterEnd, iniSkyRefl, iniDynRipples,
            iniReflBlur, iniExpFog, iniDLExpMul,
            iniScattering, iniWaveHght, iniCaustics,
            iniShadows, iniShadowDetail, iniPixelLighting, iniPixelLightingFlags
        };

        private void LoadGraphicsSettings() {
            LoadGraphicsSettings(false, true);
        }

        private void LoadGraphicsSettings(bool reset) {
            LoadGraphicsSettings(reset, false);
        }

        private bool IsSharedMemoryFeatureSupported() {
            var hModule = LoadLibraryA("kernelbase.dll");
            if (hModule == IntPtr.Zero) {
                return false;
            }

            var addr = GetProcAddress(hModule, "MapViewOfFile3");
            FreeLibrary(hModule);
            return addr != IntPtr.Zero;
        }

        private void LoadGraphicsSettings(bool reset, bool save) {
            var iniFile = new INIFile(reset ? Statics.fn_nul : Statics.fn_inifile, iniSettings, true);
            if (reset) {
                iniFile.fileName = Statics.fn_inifile;
            }
            if (save) {
                iniFile.initialize();
                iniFile.save();
            }

            var canUseSharedMemory = IsSharedMemoryFeatureSupported();

            loading = true;
            // Config
            cmbTipReadSpd.SelectedIndex = (int)iniFile.getKeyValue("TipSpeed");
            // Graphics
            cmbAntiAlias.SelectedIndex = (int)iniFile.getKeyValue("AntiAlias");
            cmbVWait.SelectedIndex = (int)iniFile.getKeyValue("VWait");
            tbRefreshRate.Text = iniFile.getKeyValue("Refresh").ToString();
            if (tbRefreshRate.Text == "0") {
                tbRefreshRate.Text = "Default";
            }
            cbBorderless.Checked = (iniFile.getKeyValue("Borderless") == 1);
            cbHWShader.Checked = (iniFile.getKeyValue("HWShader") == 1);
            cbFPSCounter.Checked = (iniFile.getKeyValue("FPSCount") == 1);
            cbReduceTextureMemUse.Checked = (iniFile.getKeyValue("ReduceTexMemUse") == 1);
            cmbAnisoLevel.SelectedIndex = (int)iniFile.getKeyValue("AnisoLvl");
            cbAutoFOV.Checked = (iniFile.getKeyValue("FOVAuto") == 1);
            udFOV.Value = (decimal)iniFile.getKeyValue("FOV");
            udUIScale.Value = (decimal)iniFile.getKeyValue("UIScale");
            setWindowAlignState((int)iniFile.getKeyValue("WindowAlignX"), (int)iniFile.getKeyValue("WindowAlignY"));
            cmbFogMode.SelectedIndex = (int)iniFile.getKeyValue("FogMode");
            cmbSShotFormat.SelectedIndex = (int)iniFile.getKeyValue("SSFormat");
            cmbSShotSuffix.SelectedIndex = (int)iniFile.getKeyValue("SSSuffix");
            tbSShotDir.Text = iniFile.getKeyString("SSDir");
            if (tbSShotDir.Text.Length == 0) {
                bSSDirClear_Click(null, null);
            }
            tbSShotName.Text = iniFile.getKeyString("SSName");
            cbDisplayMessages.Checked = (iniFile.getKeyValue("Messages") == 1);
            udMsgsTime.Value = (decimal)iniFile.getKeyValue("MsgTime");
            cbUseSharedMemory.Checked = (iniFile.getKeyValue("UseSharedMemory") == 1 && canUseSharedMemory);
            if (!canUseSharedMemory) {
                cbUseSharedMemory.Enabled = false;
            }
            // In-game
            cbDisableMGE.Checked = (iniFile.getKeyValue("DisableMGE") == 1);
            cbDisableMWSE.Checked = (iniFile.getKeyValue("DisableMWSE") == 1);
            cbD3D8To9Only.Checked = (iniFile.getKeyValue("D3D8To9Only") == 1);
            cbSkipMovie.Checked = (iniFile.getKeyValue("SkipIntro") == 1);
            cbAltCombat.Checked = (iniFile.getKeyValue("AltCombat") == 1);
            cbCam3rdPrsn.Checked = (iniFile.getKeyValue("Cam3rdCustom") == 1);
            udCam3rdX.Value = (decimal)iniFile.getKeyValue("Cam3rdX");
            udCam3rdY.Value = (decimal)iniFile.getKeyValue("Cam3rdY");
            udCam3rdZ.Value = (decimal)iniFile.getKeyValue("Cam3rdZ");
            cbAutoCrosshair.Checked = (iniFile.getKeyValue("AutoCrosshair") == 1);
            cbMenuCaching.Checked = (iniFile.getKeyValue("MenuCaching") == 1);
            // Distant Land
            cbDLDistantLand.Checked = (iniFile.getKeyValue("DistLand") == 1);
            cbDLDistantStatics.Checked = (iniFile.getKeyValue("DistStat") == 1);
            udDLDrawDist.Value = (decimal)iniFile.getKeyValue("DrawDist");
            udDLDistNear.Value = (decimal)iniFile.getKeyValue("EndNear");
            udDLDistFar.Value = (decimal)iniFile.getKeyValue("EndFar");
            udDLDistVeryFar.Value = (decimal)iniFile.getKeyValue("EndVFar");
            udDLSizeFar.Value = (decimal)iniFile.getKeyValue("SizeFar");
            udDLSizeVeryFar.Value = (decimal)iniFile.getKeyValue("SizeVFar");
            cbDLReflLand.Checked = (iniFile.getKeyValue("ReflLand") == 1);
            cbDLReflNStatics.Checked = (iniFile.getKeyValue("ReflNear") == 1);
            cbDLReflInterior.Checked = (iniFile.getKeyValue("ReflIntr") == 1);
            udDLFogAStart.Value = (decimal)iniFile.getKeyValue("AboveBeg");
            udDLFogAEnd.Value = (decimal)iniFile.getKeyValue("AboveEnd");
            udDLFogBStart.Value = (decimal)iniFile.getKeyValue("BelowBeg");
            udDLFogBEnd.Value = (decimal)iniFile.getKeyValue("BelowEnd");
            udDLFogIStart.Value = (decimal)iniFile.getKeyValue("InterBeg");
            udDLFogIEnd.Value = (decimal)iniFile.getKeyValue("InterEnd");
            cbDLSkyRefl.Checked = (iniFile.getKeyValue("SkyRefl") == 1);
            cbDLDynRipples.Checked = (iniFile.getKeyValue("DynRipples") == 1);
            cbDLReflBlur.Checked = (iniFile.getKeyValue("ReflBlur") == 1);
            udDLFogExpMul.Value = (decimal)iniFile.getKeyValue("DLExpMul");
            cbDLFogExp.Checked = (iniFile.getKeyValue("ExpFog") == 1);
            cbDLScattering.Checked = (iniFile.getKeyValue("Scatter") == 1);
            udDLWtrWave.Value = (decimal)iniFile.getKeyValue("WaveHght");
            udDLWtrCaust.Value = (decimal)iniFile.getKeyValue("Caustics");
            int autoDistBy = (int)iniFile.getKeyValue("AutoDistBy");
            rbDLAutoByDrawDist.Checked = (autoDistBy == 1);
            rbDLAutoByAFogEnd.Checked = (autoDistBy == 2);
            cbDLAutoDist.Checked = (iniFile.getKeyValue("AutoDist") == 1);
            cbDLSunShadows.Checked = (iniFile.getKeyValue("SunShadows") == 1);
            cmbDLShadowDetail.SelectedIndex = (iniFile.getKeyValue("SunShadowDetail") == 2048) ? 1 : 0;
            cbPerPixelLighting.Checked = (iniFile.getKeyValue("PPLighting") == 1);
            cmbPerPixelLightFlags.SelectedIndex = (int)iniFile.getKeyValue("PPLightingFlags");
            loading = false;
        }

        private void SaveGraphicsSettings() {
            var iniFile = new INIFile(Statics.fn_inifile, iniSettings, true);
            // Config
            iniFile.setKey("Version", Statics.versionString);
            iniFile.setKey("TipSpeed", cmbTipReadSpd.SelectedIndex);
            iniFile.setKey("Language", cmbUILanguage.Text);
            iniFile.setKey("AutoLang", cbUILangAuto.Checked);
            // Graphics
            iniFile.setKey("AntiAlias", cmbAntiAlias.SelectedIndex);
            iniFile.setKey("VWait", cmbVWait.SelectedIndex);
            iniFile.setKey("Refresh", tbRefreshRate.Text);
            iniFile.setKey("Borderless", cbBorderless.Checked);
            iniFile.setKey("AnisoLvl", cmbAnisoLevel.SelectedIndex);
            iniFile.setKey("HWShader", cbHWShader.Checked);
            iniFile.setKey("FPSCount", cbFPSCounter.Checked);
            iniFile.setKey("ReduceTexMemUse", cbReduceTextureMemUse.Checked);
            iniFile.setKey("FOVAuto", cbAutoFOV.Checked);
            iniFile.setKey("FOV", (double)udFOV.Value);
            iniFile.setKey("UIScale", (double)udUIScale.Value);
            {
                int alignX, alignY;
                getWindowAlignState(out alignX, out alignY);
                iniFile.setKey("WindowAlignX", alignX);
                iniFile.setKey("WindowAlignY", alignY);
            }
            iniFile.setKey("FogMode", cmbFogMode.SelectedIndex);
            iniFile.setKey("Messages", cbDisplayMessages.Checked);
            iniFile.setKey("MsgTime", (double)udMsgsTime.Value);
            iniFile.setKey("SSFormat", cmbSShotFormat.SelectedIndex);
            iniFile.setKey("SSSuffix", cmbSShotSuffix.SelectedIndex);
            if (tbSShotDir.TextAlign == HorizontalAlignment.Left) {
                iniFile.setKey("SSDir", tbSShotDir.Text);
            } else {
                iniFile.setKey("SSDir", "");
            }
            iniFile.setKey("SSName", tbSShotName.Text.TrimEnd());
            iniFile.setKey("UseSharedMemory", cbUseSharedMemory.Checked && cbUseSharedMemory.Enabled);
            // In-game
            iniFile.setKey("DisableMGE", cbDisableMGE.Checked);
            iniFile.setKey("DisableMWSE", cbDisableMWSE.Checked);
            iniFile.setKey("D3D8To9Only", cbD3D8To9Only.Checked);
            iniFile.setKey("SkipIntro", cbSkipMovie.Checked);
            iniFile.setKey("AltCombat", cbAltCombat.Checked);
            iniFile.setKey("Cam3rdCustom", cbCam3rdPrsn.Checked);
            iniFile.setKey("Cam3rdX", (double)udCam3rdX.Value);
            iniFile.setKey("Cam3rdY", (double)udCam3rdY.Value);
            iniFile.setKey("Cam3rdZ", (double)udCam3rdZ.Value);
            iniFile.setKey("AutoCrosshair", cbAutoCrosshair.Checked);
            iniFile.setKey("MenuCaching", cbMenuCaching.Checked);
            // Distant Land
            iniFile.setKey("DistLand", cbDLDistantLand.Checked);
            iniFile.setKey("DistStat", cbDLDistantStatics.Checked);
            iniFile.setKey("DrawDist", (double)udDLDrawDist.Value);
            iniFile.setKey("AutoDist", cbDLAutoDist.Checked);
            iniFile.setKey("AutoDistBy", rbDLAutoByAFogEnd.Checked ? 2 : 1);
            iniFile.setKey("EndNear", (double)udDLDistNear.Value);
            iniFile.setKey("EndFar", (double)udDLDistFar.Value);
            iniFile.setKey("EndVFar", (double)udDLDistVeryFar.Value);
            iniFile.setKey("SizeFar", (double)udDLSizeFar.Value);
            iniFile.setKey("SizeVFar", (double)udDLSizeVeryFar.Value);
            iniFile.setKey("ReflLand", cbDLReflLand.Checked);
            iniFile.setKey("ReflNear", cbDLReflNStatics.Checked);
            iniFile.setKey("ReflIntr", cbDLReflInterior.Checked);
            iniFile.setKey("SkyRefl", cbDLSkyRefl.Checked);
            iniFile.setKey("ReflBlur", cbDLReflBlur.Checked);
            iniFile.setKey("DynRipples", cbDLDynRipples.Checked);
            iniFile.setKey("WaveHght", (double)udDLWtrWave.Value);
            iniFile.setKey("Caustics", (double)udDLWtrCaust.Value);
            iniFile.setKey("AboveBeg", (double)udDLFogAStart.Value);
            iniFile.setKey("AboveEnd", (double)udDLFogAEnd.Value);
            iniFile.setKey("BelowBeg", (double)udDLFogBStart.Value);
            iniFile.setKey("BelowEnd", (double)udDLFogBEnd.Value);
            iniFile.setKey("InterBeg", (double)udDLFogIStart.Value);
            iniFile.setKey("InterEnd", (double)udDLFogIEnd.Value);
            iniFile.setKey("ExpFog", cbDLFogExp.Checked);
            iniFile.setKey("DLExpMul", (double)udDLFogExpMul.Value);
            iniFile.setKey("Scatter", cbDLScattering.Checked);
            iniFile.setKey("SunShadows", cbDLSunShadows.Checked);
            iniFile.setKey("SunShadowDetail", cmbDLShadowDetail.SelectedIndex == 1 ? 2048 : 1024);
            iniFile.setKey("PPLighting", cbPerPixelLighting.Checked);
            iniFile.setKey("PPLightingFlags", cmbPerPixelLightFlags.SelectedIndex);
            iniFile.save();
            try {
                RegistryKey key = Registry.LocalMachine.OpenSubKey(Statics.reg_mw, true);
                if (key != null) {
                    key.SetValue("Pixelshader", new byte [] { Convert.ToByte(cbDisableMGE.Checked) });
                    key.Close();
                }
            } catch {
            }
        }

        private decimal udValue(NumericUpDown target, double value) {
            return ((decimal)value < target.Minimum ? target.Minimum : ((decimal)value > target.Maximum ? target.Maximum : (decimal)value));
        }

        private void LoadInputSaveFile() {
            byte version;
            if (!File.Exists(Statics.fn_didata)) {
                return;
            }
            var br = new BinaryReader(File.OpenRead(Statics.fn_didata));
            version = br.ReadByte();
            if (version < 39) {
                throw new Exception(strings["InpTooOld"]);
            }
            if (version > Statics.SaveVersion) {
                throw new Exception(strings["InpTooNew"]);
            }
            br.ReadBoolean(); // was skip movie
            br.ReadBoolean(); // was disable console
            cbAltCombat.Checked = br.ReadBoolean();
            try {
                UnserializeMacroSaves();
            } catch {
                MessageBox.Show(strings["MacrTrigErr"], Statics.strings["Error"]);
                for (int i = 0; i < 266; i++) {
                    Statics.Macros[i].Type = (MacroType)br.ReadByte();
                    switch (Statics.Macros[i].Type) {
                        case MacroType.Console1:
                        case MacroType.Console2:
                            Statics.Macros[i].Console.Length = br.ReadByte();
                            for (int j = 0; j < 266; j++) {
                                Statics.Macros[i].Console.KeyCodes[j].Code = br.ReadByte();
                            }
                            for (int j = 0; j < 266; j++) {
                                Statics.Macros[i].Console.KeyCodes[j].Down = br.ReadBoolean();
                            }
                            break;
                        case MacroType.Press1:
                        case MacroType.Press2:
                        case MacroType.Unpress:
                        case MacroType.Hammer1:
                        case MacroType.Hammer2:
                        case MacroType.Unhammer:
                        case MacroType.AHammer1:
                        case MacroType.AHammer2:
                        case MacroType.AUnhammer:
                            for (int j = 0; j < 266; j++) {
                                Statics.Macros[i].Press.KeyStates[j] = br.ReadBoolean();
                            }
                            for (int j = 0; j < 267; j++) {
                                br.ReadByte();
                            }
                            break;
                        case MacroType.BeginTimer:
                        case MacroType.EndTimer:
                            Statics.Macros[i].Timer.TimerID = br.ReadByte();
                            for (int j = 0; j < 266 * 2; j++) {
                                br.ReadByte();
                            }
                            break;
                        case MacroType.Graphics:
                            Statics.Macros[i].Graphics.function = br.ReadByte();
                            for (int j = 0; j < 266 * 2; j++) {
                                br.ReadByte();
                            }
                            break;
                        default:
                            for (int j = 0; j < 266 * 2 + 1; j++) {
                                br.ReadByte();
                            }
                            break;
                    }
                }
                for (int i = 0; i < 4; i++) {
                    Statics.Triggers[i].TimeInterval = br.ReadUInt32();
                    Statics.Triggers[i].Active = br.ReadBoolean();
                    for (int j = 0; j < Statics.MACROS; j++) {
                        Statics.Triggers[i].data.KeyStates[j] = br.ReadBoolean();
                    }
                    br.ReadByte();  // Needed for memory alignment reasons
                }
            }
            br.Close();
            if (version < Statics.SaveVersion) {
                MessageBox.Show(strings["OldInpImp"], Statics.strings["Message"]);
            }
        }

        private void UnserializeMacroSaves() {
            FileStream fs;
            fs = File.OpenRead(Statics.fn_macro);
            Statics.Macros = (Macro[])Statics.formatter.Deserialize(fs);
            fs.Close();
            fs = File.OpenRead(Statics.fn_triger);
            Statics.Triggers = (Trigger[])Statics.formatter.Deserialize(fs);
            fs.Close();
        }

        private void LoadInputSettings() {
            var iniFile = new INIFile(Statics.fn_inifile, iniSettings, true);

            for (int i = 0; i < Statics.MACROS; ++i) {
                Statics.Macros[i] = new Macro();
            }
            for (int i = 0; i < Statics.TRIGGERS; ++i) {
                Statics.Triggers[i] = new Trigger();
            }
            for (int i = 0; i < Statics.Remapper.Length; ++i) {
                Statics.Remapper[i] = 0;
            }

            var macroDesc = iniFile.getSectionKeys("MacrosDesc");
            foreach (var entry in iniFile.getSectionKeys("Macros")) {
                int i;
                if (!(entry.Key.StartsWith("M") && int.TryParse(entry.Key.Substring(1), out i))) {
                    continue;
                }

                Macro m = Statics.Macros[i];
                string[] values = entry.Value.Split(',');

                try {
                    m.Type = (MacroType)Enum.Parse(typeof(MacroType), values[0], true);
                } catch (ArgumentException) {
                    continue;
                }

                switch (m.Type) {
                    case MacroType.Console1:
                    case MacroType.Console2:
                        m.Console.Length = 0;
                        for (int j = 1; j < values.Length; j += 2, m.Console.Length++) {
                            m.Console.KeyCodes[m.Console.Length].Code = byte.Parse(values[j]);
                            m.Console.KeyCodes[m.Console.Length].Down = bool.Parse(values[j + 1]);
                        }
                        macroDesc.TryGetValue(entry.Key, out m.Console.Description);
                        if (m.Console.Description == null) {
                            m.Console.Description = "";
                        }
                        break;
                    case MacroType.Press1:
                    case MacroType.Press2:
                    case MacroType.Unpress:
                    case MacroType.Hammer1:
                    case MacroType.Hammer2:
                    case MacroType.Unhammer:
                    case MacroType.AHammer1:
                    case MacroType.AHammer2:
                    case MacroType.AUnhammer:
                        for (int j = 1; j < values.Length; ++j) {
                            m.Press.KeyStates[int.Parse(values[j])] = true;
                        }
                        break;
                    case MacroType.BeginTimer:
                    case MacroType.EndTimer:
                        m.Timer.TimerID = byte.Parse(values[1]);
                        break;
                    case MacroType.Graphics:
                        m.Graphics.function = byte.Parse(values[1]);
                        break;
                }
            }

            foreach (var entry in iniFile.getSectionKeys("InputTriggers")) {
                int i;
                if (entry.Key.StartsWith("T") && int.TryParse(entry.Key.Substring(1), out i)) {
                    Trigger t = Statics.Triggers[i];
                    string[] values = entry.Value.Split(',');

                    t.Active = bool.Parse(values[0]);
                    t.TimeInterval = uint.Parse(values[1]);

                    for (int j = 2; j < values.Length; ++j) {
                        t.data.KeyStates[int.Parse(values[j])] = true;
                    }
                }
            }

            foreach (var entry in iniFile.getSectionKeys("InputRemap")) {
                int i;
                if (entry.Key.StartsWith("R") && int.TryParse(entry.Key.Substring(1), out i)) {
                    Statics.Remapper[i] = byte.Parse(entry.Value);
                }
            }
        }

        private void SaveMWINI() {
            // morrowind.ini uses system codepage
            var mwini = new INIFile(Statics.fn_mwini, mwSettings, System.Text.Encoding.Default, true);

            mwini.setKey("FPSLimit", (int)udFPSLimit.Value);
            mwini.setKey("SSEnable", cbScreenshots.Checked);
            mwini.setKey("NoThread", !cbThreadLoad.Checked);
            mwini.setKey("YesToAll", cbYesToAll.Checked);
            mwini.setKey("HDShadow", cbHQShadows.Checked);
            mwini.setKey("ShowFPS", cbShowFPS.Checked);
            mwini.setKey("AudioOff", cbAudio.Checked);
            mwini.setKey("Subtitles", cbSubtitles.Checked);
            mwini.setKey("HitFader", cbHitFader.Checked);

            mwini.setKey("UseConstant", true);
            mwini.setKey("ConstantValue", Decimal.ToSingle(udLightingConst.Value));
            mwini.setKey("UseLinear", true);
            mwini.setKey("LinearValue", Decimal.ToSingle(udLightingLinear.Value));
            mwini.setKey("UseQuadratic", true);
            mwini.setKey("QuadraticValue", Decimal.ToSingle(udLightingQuad.Value));

            mwini.save();
        }

        private void SaveInputSettings() {
            var iniFile = new INIFile(Statics.fn_inifile, iniSettings, true);

            var text = new List<string>();
            var macroDesc = new List<string>();
            for (int i = 0; i < Statics.MACROS; ++i) {
                Macro m = Statics.Macros[i];
                string s = string.Format("M{0}={1}", i, m.Type);
                switch (m.Type) {
                    case MacroType.Console1:
                    case MacroType.Console2:
                        if (m.Console.Description.Length > 0) {
                            macroDesc.Add(string.Format("M{0}={1}", i, m.Console.Description));
                        }
                        for (int j = 0; j < m.Console.Length; ++j) {
                            s += string.Format(",{0},{1}", m.Console.KeyCodes[j].Code, m.Console.KeyCodes[j].Down);
                        }
                        break;
                    case MacroType.Press1:
                    case MacroType.Press2:
                    case MacroType.Unpress:
                    case MacroType.Hammer1:
                    case MacroType.Hammer2:
                    case MacroType.Unhammer:
                    case MacroType.AHammer1:
                    case MacroType.AHammer2:
                    case MacroType.AUnhammer:
                        for (int j = 0; j < Statics.MACROS; ++j) {
                            if (m.Press.KeyStates[j]) {
                                s += string.Format(",{0}", j);
                            }
                        }
                        break;
                    case MacroType.BeginTimer:
                    case MacroType.EndTimer:
                        s += string.Format(",{0}", m.Timer.TimerID);
                        break;
                    case MacroType.Graphics:
                        s += string.Format(",{0}", m.Graphics.function);
                        break;
                    default:
                        continue;
                }
                text.Add(s);
            }
            iniFile.setSectOrderedList("Macros", text.ToArray());
            iniFile.setSectOrderedList("MacrosDesc", macroDesc.ToArray());

            text.Clear();
            for (int i = 0; i < Statics.TRIGGERS; i++) {
                Trigger t = Statics.Triggers[i];
                string s = "";

                for (int j = 0; j < Statics.MACROS; j++) {
                    if (t.data.KeyStates[j]) {
                        s += string.Format(",{0}", j);
                    }
                }
                if (s.Length > 0) {
                    text.Add(string.Format("T{0}={1},{2}{3}", i, t.Active, t.TimeInterval, s));
                }
            }
            iniFile.setSectOrderedList("InputTriggers", text.ToArray());

            text.Clear();
            for (int i = 0; i < Statics.Remapper.Length; i++) {
                if (Statics.Remapper[i] != 0) {
                    text.Add(string.Format("R{0}={1}", i, Statics.Remapper[i]));
                }
            }
            iniFile.setSectOrderedList("InputRemap", text.ToArray());

            iniFile.save();
        }

        private void SaveSettings() {
            SaveMWINI();
            SaveGraphicsSettings();
            SaveInputSettings();
        }

        private void LoadSettings() {
            RegistryKey key = Registry.LocalMachine.CreateSubKey(Statics.reg_mw);
            int width, height;
            try {
                width = (int)key.GetValue("Screen Width");
                height = (int)key.GetValue("Screen Height");
            } catch {
                // If Morrowind hasn't run yet, no keys exist
                Rectangle screen = Screen.FromControl(this).Bounds;
                width = screen.Width;
                height = screen.Height;
                key.SetValue("Screen Width", width);
                key.SetValue("Screen Height", height);
                key.SetValue("Refresh Rate", 0);
                key.SetValue("Fullscreen", new byte[] { (byte)1 });
            }
            tbResolution.Text = width.ToString() + " x " + height.ToString();
            CalcAspectRatio(width, height);
            try {
                cbWindowed.Checked = !Convert.ToBoolean(((byte[])key.GetValue("Fullscreen"))[0]);
            } catch {
                MessageBox.Show(strings["RegWinMode"], Statics.strings["Error"]);
                cbWindowed.Checked = false;
            }
            key.Close();

            LoadGraphicsSettings(false);
            LoadMWINI();

            if (File.Exists(Statics.fn_didata)) {
                // Convert 0.9.x macro and remap settings
                try {
                    LoadInputSaveFile();
                    File.Delete(Statics.fn_didata);
                    if (File.Exists(Statics.fn_macro)) {
                        File.Delete(Statics.fn_macro);
                    }
                    if (File.Exists(Statics.fn_triger)) {
                        File.Delete(Statics.fn_triger);
                    }

                    if (File.Exists(Statics.fn_remap)) {
                        FileStream fs = File.OpenRead(Statics.fn_remap);
                        fs.Read(Statics.Remapper, 0, 256);
                        fs.Close();
                        File.Delete(Statics.fn_remap);
                    }
                } catch (Exception ex) {
                    loading = false;
                    MessageBox.Show(String.Format(strings["ErrLdInp"], ex.Message), Statics.strings["Error"]);
                }
            } else {
                try {
                    LoadInputSettings();
                } catch (Exception ex) {
                    loading = false;
                    MessageBox.Show(String.Format(strings["ErrLdInp"], ex.Message), Statics.strings["Error"]);
                }
            }
            if (File.Exists(Statics.fn_dlver) && File.Exists(Statics.fn_usagedata)) {
                byte[] bytes = File.ReadAllBytes(Statics.fn_dlver);
                if (bytes.Length == 1 && bytes[0] == (byte)Statics.DistantLandVersion) {
                    var br = new BinaryReader(File.OpenRead(Statics.fn_usagedata));
                    br.BaseStream.Position = br.BaseStream.Length - 4;
                    tbDLNearSize.Text = br.ReadSingle().ToString();
                    br.Close();
                }
            }
            ValidateDistances(null, null);
            UpdateFOV();
        }

        private void IgnoreKey(object sender, KeyPressEventArgs e) {
            e.Handled = true;
        }

        private void bMacroEd_Click(object sender, EventArgs e) {
            (new MacroEditorForm()).ShowDialog();
        }

        private void MainForm_FormClosing(object sender, CancelEventArgs e) {
            if (Save) {
                SaveSettings();
            }
        }

        private void bHelp_Click(object sender, EventArgs e) {
            try {
                System.Diagnostics.Process p = System.Diagnostics.Process.Start(@"https://www.nexusmods.com/morrowind/mods/41102");
                p.Close();
            } catch {
            }
        }

        private void bShaderEd_Click(object sender, EventArgs e) {
            var SetActiveForm = new ShaderActive();
            SetActiveForm.ShowDialog();
            SetActiveForm.Dispose();
        }

        private void cbWindowed_CheckedChanged(object sender, EventArgs e) {
            RegistryKey key = null;
            try {
                key = Registry.LocalMachine.OpenSubKey(Statics.reg_mw, true);
                if (key != null) {
                    key.SetValue("Fullscreen", new byte [] { Convert.ToByte(!cbWindowed.Checked) });
                    key.Close();
                }
                cbBorderless.Enabled = cbWindowed.Checked;
            } catch {
                MessageBox.Show(strings["RegNotWrit"], Statics.strings["Error"]);
            }
        }

        private void bExport_Click(object sender, EventArgs e) {
            if (SaveFileDialog.ShowDialog() == DialogResult.OK) {
                SaveSettings();
                try {
                    File.Copy(Statics.fn_inifile, SaveFileDialog.FileName, true);
                } catch (Exception ex) {
                    MessageBox.Show("Error when exporting config:\n\n" + ex.ToString());
                }
            }
        }

        private void bImport_Click(object sender, EventArgs e) {
            if (OpenFileDialog.ShowDialog() == DialogResult.OK) {
                try {
                    File.Copy(SaveFileDialog.FileName, Statics.fn_inifile, true);
                    LoadSettings();
                } catch (Exception ex) {
                    MessageBox.Show("Error when importing config:\n\n" + ex.ToString());
                }
            }
        }

        private void bViewCaps_Click(object sender, EventArgs e) {
            MessageBox.Show(String.Format(strings["ViewCaps"], DXMain.mCaps.MaxFullscreenAA.ToString(),
                DXMain.mCaps.MaxWindowedAA.ToString(), DXMain.mCaps.MaxAF.ToString()), strings["GraphCaps"]);
        }

        private void cbDisplayMessages_CheckedChanged(object sender, EventArgs e) {
            bool status = cbDisplayMessages.Checked;
            cbFPSCounter.Checked &= status;
            cbFPSCounter.Enabled = status;
            gbMsgs.Enabled = status;
        }

        private void bSelectResolution_Click(object sender, EventArgs e) {
            System.Drawing.Point p;
            int refresh;

            if (ResolutionForm.ShowDialog(out p, out refresh, cbWindowed.Checked)) {
                tbResolution.Text = p.X.ToString() + " x " + p.Y.ToString();
                tbRefreshRate.Text = (refresh == 0) ? "Default" : refresh.ToString();
                CalcAspectRatio(p.X, p.Y);
                UpdateFOV();
            }
        }

        private class AboutForm : Form {
            private System.Timers.Timer OpacityTimer;
            private System.ComponentModel.IContainer components = null;
            delegate void SetOpacityCallback(double opacity);
            public AboutForm(string message, string title, string close) {
                this.SuspendLayout();
                // bClose
                System.Windows.Forms.Button bClose = new System.Windows.Forms.Button();
                bClose.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
                bClose.DialogResult = System.Windows.Forms.DialogResult.Cancel;
                bClose.Location = new System.Drawing.Point(194, 143);
                bClose.Size = new System.Drawing.Size(128, 25);
                bClose.TabIndex = 0;
                bClose.UseVisualStyleBackColor = true;
                bClose.Text = close;
                // lBody
                System.Windows.Forms.Label lBody = new System.Windows.Forms.Label();
                lBody.Anchor = System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right;
                lBody.AutoEllipsis = true;
                lBody.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
                lBody.Location = new System.Drawing.Point(116, 9);
                lBody.Size = new System.Drawing.Size(292, 131);
                lBody.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
                lBody.UseMnemonic = false;
                lBody.Text = message;
                // this
                this.AcceptButton = bClose;
                this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
                this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
                this.AutoSize = true;
                this.CancelButton = bClose;
                this.ClientSize = new System.Drawing.Size(420, 180);
                this.Controls.Add(lBody);
                this.Controls.Add(bClose);
                this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
                this.MaximizeBox = false;
                this.MinimizeBox = false;
                this.Opacity = 0;
                this.ShowIcon = false;
                this.ShowInTaskbar = false;
                this.StartPosition = FormStartPosition.CenterScreen;
                this.Text = title;
                this.ResumeLayout(false);
                // alphaTimer
                this.OpacityTimer = new System.Timers.Timer();
                this.OpacityTimer.Elapsed += new System.Timers.ElapsedEventHandler(IncreaseOpacityEvent);
                this.OpacityTimer.Interval = 25;
                this.OpacityTimer.Start();
            }
            protected override void Dispose(bool disposing) {
                if (disposing && (components != null)) {
                    components.Dispose();
                }
                base.Dispose(disposing);
            }
            protected override void OnPaint(System.Windows.Forms.PaintEventArgs e) {
                Graphics graphics = e.Graphics;
                Icon ic = new Icon(Properties.Resources.AppIcon, 96, 96);
                graphics.DrawIcon(ic, 12, 24);
                graphics.Dispose();
            }
            private void SetOpacity(double opacity) {
                if (this.InvokeRequired) {
                    SetOpacityCallback d = new SetOpacityCallback(SetOpacity);
                    this.Invoke(d, new object [] { opacity });
                } else {
                    this.Opacity = opacity;
                }
            }
            private void IncreaseOpacityEvent(object source, System.Timers.ElapsedEventArgs e) {
                if (this.Opacity < 0.9) {
                    this.SetOpacity(this.Opacity + 0.03);
                } else {
                    OpacityTimer.Elapsed -= IncreaseOpacityEvent;
                }
            }
        }

        private void bAbout_Click(object sender, EventArgs e) {
            string s = String.Format("{0}\n{1}\n\n{2} Timeslip, LizTail, Krzymar, Phal, Hrnchamd", Statics.programName, Statics.versionString, strings["CreatedBy"], strings["FurtherDevel"]);
            if (cmbUILanguage.SelectedIndex > 0) {
                string ttn = Statics.strings["Translation"];
                string ttr = Statics.Localizations[cmbUILanguage.Text].Translator;
                if (ttn != "" && ttr != "") {
                    s += String.Format("\n\n{0}: {1}", ttn, ttr);
                }
            }
            (new AboutForm(s, strings["About"], Statics.strings["Close"])).ShowDialog(this);
        }

        private void bRemapper_Click(object sender, EventArgs e) {
            (new KeyRemapper()).ShowDialog();
        }

        private void cmbFogMode_SelectedIndexChanged(object sender, EventArgs e) {
        }

        private void cmbAlias_SelectedIndexChanged(object sender, EventArgs e) {
            if (cmbAntiAlias.SelectedIndex == 0) {
                return;
            }
            if (!DXMain.CheckAALevel(cmbAntiAlias.SelectedIndex, cbWindowed.Checked)) {
                MessageBox.Show(strings["TooHighAA"], Statics.strings["Error"]);
                cmbAntiAlias.SelectedIndex = 0;
            }
        }

        private void cmbAnsiLevel_SelectedIndexChanged(object sender, EventArgs e) {
            if (cmbAnisoLevel.SelectedIndex > 0) {
                if (1 << cmbAnisoLevel.SelectedIndex > DXMain.mCaps.MaxAF) {
                    MessageBox.Show(strings["TooHighAF"], Statics.strings["Error"]);
                    cmbAnisoLevel.SelectedIndex = 0;
                }
            }
        }

        private void cbDLReflectiveWater_CheckedChanged(object sender, EventArgs e) {
            cbDLReflNStatics.Enabled = cbDLDistantLand.Checked && cbDLReflLand.Checked && cbDLDistantStatics.Checked;
        }

        private void cbDistantStatics_CheckedChanged(object sender, EventArgs e) {
            bool status = cbDLDistantStatics.Checked;
            if (status && !File.Exists(Statics.fn_usagedata)) {
                cbDLDistantStatics.Checked = false;
                MessageBox.Show(strings["DSMissing"], Statics.strings["Error"]);
                return;
            }
            gbDLStatics.Enabled = status;
            lDLFogI.Enabled = udDLFogIStart.Enabled = udDLFogIEnd.Enabled = status && !cbDLAutoDist.Checked;
            cbDLReflNStatics.Enabled = status && cbDLReflLand.Checked && cbDLDistantStatics.Checked;
            cbDLReflInterior.Enabled = status && cbDLDistantStatics.Checked;
        }

        private void cbDistantLand_CheckedChanged(object sender, EventArgs e) {
            if (cbDLDistantLand.Checked) {
                if (!File.Exists(Statics.fn_dlver) || !File.Exists(Statics.fn_world) || !File.Exists(Statics.fn_worldds) || !File.Exists(Statics.fn_worldn)) {
                    cbDLDistantLand.Checked = false;
                    MessageBox.Show(strings["NoDLOrOld"], Statics.strings["Warning"]);
                    return;
                }
                byte[] bytes = File.ReadAllBytes(Statics.fn_dlver);
                if (bytes.Length != 1 || bytes[0] != Statics.DistantLandVersion) {
                    cbDLDistantLand.Checked = false;
                    MessageBox.Show(strings["DLDiffer"], Statics.strings["Warning"]);
                    return;
                }
                gbDistantLand.Enabled = true;
            } else {
                gbDistantLand.Enabled = false;
            }
            cbDLReflNStatics.Enabled = cbDLDistantLand.Checked && cbDLReflLand.Checked && cbDLDistantStatics.Checked;
            cbDLReflInterior.Enabled = cbDLDistantLand.Checked && cbDLDistantStatics.Checked;
        }

        enum AutoDistance {
            none,
            byDrawDist,
            byAFogEnd
        }
        
        private AutoDistance autoDistances = AutoDistance.none;

        // Corrects any distant land settings that cause known problems
        private void ValidateDLSettings(object sender, EventArgs e) {
            if (loading) {
                return;
            }
            if (autoDistances == AutoDistance.none) {
                ValidateDistances(sender, e);
            } else if (sender == udDLFogAStart) {
                ValidateDistances(udDLFogAEnd, e);
            }
        }

        // Corrects any distant land settings that cause known problems
        private void ValidateDistances(object sender, EventArgs e) {
            if (loading) {
                return;
            }
            loading = true;

            int near_size, far_size, v_far_size;
            near_size = Convert.ToInt32(tbDLNearSize.Text);
            far_size = (int)udDLSizeFar.Value;
            v_far_size = (int)udDLSizeVeryFar.Value;
            if (far_size < near_size) {
                far_size = near_size;
            }
            if (sender == udDLSizeVeryFar && (v_far_size >= near_size && v_far_size < far_size)) {
                far_size = v_far_size;
            }
            if (v_far_size < far_size) {
                v_far_size = far_size;
            }
            udDLSizeFar.Value = far_size;
            udDLSizeVeryFar.Value = v_far_size;

            double draw_dist, fog_start_above, fog_end_above, fog_start_below, fog_end_below, fog_start_int, fog_end_int, near_dist, far_dist, v_far_dist;
            draw_dist = (double)udDLDrawDist.Value;
            fog_start_above = (double)udDLFogAStart.Value;
            fog_end_above = (double)udDLFogAEnd.Value;
            fog_start_below = (double)udDLFogBStart.Value;
            fog_end_below = (double)udDLFogBEnd.Value;
            fog_start_int = (double)udDLFogIStart.Value;
            fog_end_int = (double)udDLFogIEnd.Value;
            near_dist = (double)udDLDistNear.Value;
            far_dist = (double)udDLDistFar.Value;
            v_far_dist = (double)udDLDistVeryFar.Value;
            if (draw_dist < fog_end_above || sender == udDLFogAEnd) {
                if (draw_dist < fog_end_above) {
                    if (sender == udDLFogAEnd) {
                        draw_dist = fog_end_above;
                    } else {
                        fog_end_above = draw_dist;
                    }
                }
                if (fog_start_above >= fog_end_above) {
                    fog_start_above = fog_end_above - 0.1;
                }
            }
            // Prevent fog end from being less than or equal to fog start
            if (fog_start_above < 0) {
                fog_start_above = 0;
            }
            if (fog_end_above <= fog_start_above) {
                fog_end_above = fog_start_above + 0.1;
            }
            if (draw_dist < fog_end_below || sender == udDLFogBEnd) {
                if (draw_dist < fog_end_below) {
                    fog_end_below = draw_dist;
                }
                if (fog_start_below >= fog_end_below) {
                    fog_start_below = fog_end_below - 0.1;
                }
            }
            if (fog_start_below < -99.9) {
                fog_start_below = -99.9;
            }
            if (fog_end_below <= fog_start_below) {
                fog_end_below = fog_start_below + 0.1;
            }

            if (fog_end_int < 1.0 && fog_end_int > draw_dist) {
                fog_end_int = draw_dist;
                sender = null;
            }
            if (fog_start_int >= fog_end_int && sender != udDLFogIStart) {
                fog_start_int = fog_end_int - 0.1;
            }
            if (fog_end_int <= fog_start_int) {
                fog_end_int = fog_start_int + 0.1;
            }

            if (sender == udDLDistFar && (near_dist >= far_dist)) {
                near_dist = far_dist;
            }
            if (sender == udDLDistVeryFar && (far_dist >= v_far_dist)) {
                far_dist = v_far_dist;
                if (near_dist >= far_dist) {
                    near_dist = far_dist;
                }
            }
            // Prevent the near static distance from ever being less than Morrowind's draw distance
            if (near_dist < 2) {
                near_dist = 2;
            }
            // Prevent any distant static distance from being less than or equal to the one before it.
            if (far_dist <= near_dist) {
                far_dist = near_dist;
            }
            if (v_far_dist <= far_dist) {
                v_far_dist = far_dist;
            }

            udDLFogAStart.Value = (decimal)fog_start_above;
            udDLFogAEnd.Value = (decimal)fog_end_above;
            udDLFogBStart.Value = (decimal)fog_start_below;
            udDLFogBEnd.Value = (decimal)fog_end_below;
            udDLFogIStart.Value = (decimal)fog_start_int;
            udDLFogIEnd.Value = (decimal)fog_end_int;
            udDLDistNear.Value = (decimal)near_dist;
            udDLDistFar.Value = (decimal)far_dist;
            udDLDistVeryFar.Value = (decimal)v_far_dist;
            udDLDrawDist.Value = (decimal)draw_dist;
            loading = false;
        }

        private void AutoSetDistances(object sender, EventArgs e) {
            double draw_distance, minStaticDist;
            loading = true;

            if (autoDistances == AutoDistance.byAFogEnd) {
                decimal distance = udDLFogAEnd.Value;
                if (distance < 1.0M) {
                    distance = 1.0M;
                } else if (distance > 300.0M) {
                    distance = 300.0M;
                }
                udDLDrawDist.Value = distance;
            }
            draw_distance = (double)udDLDrawDist.Value;
            minStaticDist = Math.Min(draw_distance, 4.0);

            if (autoDistances != AutoDistance.byAFogEnd) {
                udDLFogAStart.Value = (decimal)(draw_distance * 0.24 + 0.4);
                udDLFogAEnd.Value = (decimal)draw_distance;
            }
            udDLFogBStart.Value = -0.5M;
            udDLFogBEnd.Value = 0.3M;
            udDLFogIStart.Value = 0.0M;
            udDLFogIEnd.Value = (decimal)(draw_distance * 0.5 + 0.5);
            udDLDistNear.Value = (decimal)Math.Max(draw_distance * 0.3, minStaticDist);
            udDLDistFar.Value = (decimal)Math.Max(draw_distance * 0.67, minStaticDist);
            udDLDistVeryFar.Value = (decimal)Math.Max(draw_distance * 0.98, minStaticDist);

            // Make sure improper values have not been generated
            loading = false;
            ValidateDistances(sender, e);
        }

        private void UpdateFOV() {
            if (cbAutoFOV.Checked) {
                try {
                    RegistryKey key = Registry.LocalMachine.OpenSubKey(Statics.reg_mw);

                    // Morrowind standard horizontal FOV is 75 degrees at 4:3 aspect ratio
                    const double basefov = 75.0 * Math.PI / 180.0;
                    double aspect = (double)(int)key.GetValue("Screen Width") / (double)(int)key.GetValue("Screen Height");
                    double x = 2.0 * Math.Atan((aspect / (4.0 / 3.0)) * Math.Tan(0.5 * basefov));

                    udFOV.Value = (Decimal)(x * 180.0 / Math.PI);
                } catch {
                }
            }
        }

        private void bResetSettings_Click(object sender, EventArgs e) {
            bool delete = cbClearINI.Checked;
            DialogResult res = MessageBox.Show(String.Format(strings["AskReset"], (delete ? strings["ResetSaved"] : "")), strings["ResetAsk"], MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button2);
            if (res == DialogResult.Yes) {
                LoadGraphicsSettings(true, delete);
                var iniFile = new INIFile(Statics.fn_inifile, DLWeatherForm.iniWeatherSettings, true);
                iniFile.reinitialize();
                iniFile.save();
                cbSkipMovie.Checked = true;
                cbClearINI.Checked = false;
                cbAltCombat.Checked = false;
            }
        }

        private void bDLWthr_Click(object sender, EventArgs e) {
            (new DLWeatherForm()).ShowDialog();
        }

        private void bMWLightSettings_Click(object sender, EventArgs e) {
            (new LightingForm()).ShowDialog();
        }

        private void bDistantLandWizard_Click(object sender, EventArgs e) {
            bool exists = false;
            
            if (Directory.Exists(Statics.fn_dl)) {
                if (!File.Exists(Statics.fn_dlver) || !File.Exists(Statics.fn_world) || !File.Exists(Statics.fn_worldds) || !File.Exists(Statics.fn_worldn)) {
                    if (MessageBox.Show(strings["DLDelOldCorrupt"], Statics.strings["Warning"], MessageBoxButtons.YesNo) != DialogResult.Yes) {
                        return;
                    }
                    Directory.Delete(Statics.fn_dl, true);
                } else {
                    byte[] b = File.ReadAllBytes(Statics.fn_dlver);
                    if (b.Length != 1 || b[0] != Statics.DistantLandVersion) {
                        if (MessageBox.Show(strings["DLDelDifferent"], Statics.strings["Warning"], MessageBoxButtons.YesNo) != DialogResult.Yes) {
                            return;
                        }
                        Directory.Delete(Statics.fn_dl, true);
                    } else {
                        exists = true;
                    }
                }
            }
            (new DistantLand.DistantLandForm(exists)).ShowDialog();
        }

        private void CalcAspectRatio(int x, int y) {
            int dx = x;
            int dy = y;
            while (dx != dy) {
                if (dx > dy) {
                    dx = dx - dy;
                } else {
                    dy = dy - dx;
                }
            }
            tbAspect.Text = (x / dx).ToString() + ":" + (y / dx).ToString();
        }

        private void tbSSDir_TextAlignChanged(object sender, EventArgs e) {
            bSShotDirClear.Enabled = (tbSShotDir.TextAlign == HorizontalAlignment.Left);
        }

        private void bSSDirClear_Click(object sender, EventArgs e) {
            tbSShotDir.TextAlign = HorizontalAlignment.Center;
            tbSShotDir.Text = clearedSSDir;
        }

        private void bSShotDirBrowse_Click(object sender, EventArgs e) {
            if (tbSShotDir.TextAlign == HorizontalAlignment.Left) {
                SShotFolderDialog.SelectedPath = tbSShotDir.Text;
            } else {
                SShotFolderDialog.SelectedPath = Statics.runDir;
            }
            if (SShotFolderDialog.ShowDialog() == DialogResult.OK) {
                tbSShotDir.TextAlign = HorizontalAlignment.Left;
                tbSShotDir.Text = SShotFolderDialog.SelectedPath;
            }
        }

        private void fileNameFilter_KeyPress(object sender, KeyPressEventArgs e) {
            switch (e.KeyChar) {
                case '*':
                case '?':
                case '"':
                case '/':
                case '\\':
                case ':':
                case '|':
                case '>':
                case '<':
                    e.Handled = true;
                    break;
            }
        }

        private void cbDisableMGE_CheckedChanged(object sender, EventArgs e) {
            bool status = !this.cbDisableMGE.Checked;
            this.gbScene.Enabled = status;
            this.gbSShot.Enabled = status;
            this.gbMsgs.Enabled = status;
            this.gbInputTools.Enabled = status;
            this.bDistantLandWizard.Enabled = status;
            this.cbDLDistantLand.Enabled = status;
            this.gbDistantLand.Enabled = status && this.cbDLDistantLand.Checked;
            this.pCam3rdPrsn.Enabled = status;
            this.gbMainSettings.Enabled = status;
        }

        private void udDLDrawDist_ValueChanged(object sender, EventArgs e) {
            if (loading) {
                return;
            }
            if (autoDistances == AutoDistance.byDrawDist) {
                AutoSetDistances(sender, e);
            } else {
                ValidateDLSettings(sender, e);
            }
        }

        private void udDLFogAEnd_ValueChanged(object sender, EventArgs e) {
            if (loading) {
                return;
            }
            if (autoDistances == AutoDistance.byAFogEnd) {
                AutoSetDistances(sender, e);
                ValidateDistances(null, null);
            } else {
                ValidateDLSettings(sender, e);
            }
        }

        private void cbAutoSetDistances_CheckedChanged(object sender, EventArgs e) {
            bool status = cbDLAutoDist.Checked;
            gbDLAutoDist.Enabled = status;
            gbDLDrawDist.Enabled = !status || !rbDLAutoByAFogEnd.Checked;
            udDLFogAStart.Enabled = !status || !rbDLAutoByDrawDist.Checked;
            udDLFogAEnd.Enabled = !status || !rbDLAutoByDrawDist.Checked;
            udDLFogBStart.Enabled = !status;
            udDLFogBEnd.Enabled = !status;
            udDLFogIStart.Enabled = udDLFogIEnd.Enabled = !status && cbDLDistantStatics.Checked;
            udDLDistNear.Enabled = !status;
            udDLDistFar.Enabled = !status;
            udDLDistVeryFar.Enabled = !status;
            if (status) {
                autoDistances = rbDLAutoByDrawDist.Checked ? AutoDistance.byDrawDist :  AutoDistance.byAFogEnd;
                if (!loading) {
                    AutoSetDistances(sender, e);
                }
            } else {
                autoDistances = AutoDistance.none;
            }
        }

        private void cbDLFogExp_CheckedChanged(object sender, EventArgs e) {
            bool status = cbDLFogExp.Checked;
            lDLFogExpMul.Enabled = status;
            udDLFogExpMul.Enabled = status;
            cbDLScattering.Enabled = status;
            cbDLScattering.Checked &= status;
            if (loading) {
                return;
            }

            if (cbDLAutoDist.Checked) {
                AutoSetDistances(sender, e);
            }
        }

        private void udDLFogExpMul_ValueChanged(object sender, EventArgs e) {
            if (loading) {
                return;
            }
            if (cbDLAutoDist.Checked) {
                AutoSetDistances(sender, e);
            } else {
                ValidateDistances(sender, e);
            }
        }

        private void rbDLAutoDist_CheckedChanged(object sender, EventArgs e) {
            bool status = cbDLAutoDist.Checked;
            gbDLDrawDist.Enabled = !status || !rbDLAutoByAFogEnd.Checked;
            udDLFogAStart.Enabled = !status || !rbDLAutoByDrawDist.Checked;
            udDLFogAEnd.Enabled = !status || !rbDLAutoByDrawDist.Checked;
            if (status) {
                autoDistances = rbDLAutoByDrawDist.Checked ? AutoDistance.byDrawDist : AutoDistance.byAFogEnd;
                if (!loading) {
                    AutoSetDistances(sender, e);
                }
            } else {
                autoDistances = AutoDistance.none;
            }
        }

        private void TooltipTimeoutHandler(object sender, EventArgs e) {
            Control control = (sender as Control);
            int delay = toolTip.GetToolTip(control).Length * Statics.tipReadSpeed;
            toolTip.AutoPopDelay = (delay < 32768 ? delay : 32767);
        }

        private void cmbMainTipReadSpd_SelectedIndexChanged(object sender, EventArgs e) {
            Statics.tipReadSpeed = (int)(1000 / double.Parse(cmbTipReadSpd.Text));
        }

        private void cbDLDynRipples_CheckedChanged(object sender, EventArgs e) {
            bool status = cbDLDynRipples.Checked;
            gbDLWtrWave.Enabled = status;
        }

        private void cmbUILanguage_SelectedIndexChanged(object sender, EventArgs e) {
            Statics.Localizations.Current = cmbUILanguage.Text;
            string s = tbSShotDir.Text;

            loading = true;
            Statics.Localizations.ApplyStrings("", Statics.strings);
            Statics.Localizations.Apply(this);
            Statics.Localizations.ApplyDialogs(this, new string[] { "OpenFileDialog", "SaveFileDialog", "SShotFolderDialog" });
            clearedSSDir = tbSShotDir.Text;
            if (tbSShotDir.TextAlign != HorizontalAlignment.Center) {
                tbSShotDir.Text = s;
            }
            loading = false;
        }

        private void cbUILangAuto_CheckedChanged(object sender, EventArgs e) {
            bool status = cbUILangAuto.Checked;
            cmbUILanguage.Enabled = !status;
            if (status) {
                int index = cmbUILanguage.FindStringExact(LocalizationInterface.SysLang);
                if (index == -1) {
                    index = cmbUILanguage.FindStringExact(LocalizationInterface.SysLangRev);
                }
                if (index == -1) {
                    index = cmbUILanguage.FindString(LocalizationInterface.SysLangOrg);
                }
                if (index == -1) {
                    index = cmbUILanguage.FindString(LocalizationInterface.SysLangEng);
                }
                if (index == -1) {
                    index = cmbUILanguage.FindString(Statics.Localizations.Current);
                }
                cmbUILanguage.SelectedIndex = index;
            }
        }

        private void cbCam3rdPrsn_CheckedChanged(object sender, EventArgs e) {
            gbCam3rdPrsn.Enabled = cbCam3rdPrsn.Checked;
        }

        private void cbAutoFOV_CheckedChanged(object sender, EventArgs e) {
            if (cbAutoFOV.Checked) {
                UpdateFOV();
            }
        }

        private void bMWLightingReset_Click(object sender, EventArgs e) {
            if (cbPerPixelLighting.Checked) {
                udLightingConst.Value = 0.36M;
                udLightingLinear.Value = 0;
                udLightingQuad.Value = 3.25M;
            } else {
                udLightingConst.Value = 0;
                udLightingLinear.Value = 3.0M;
                udLightingQuad.Value = 0;
            }
        }

        private void cbPerPixelLighting_CheckedChanged(object sender, EventArgs e) {
            cmbPerPixelLightFlags.Enabled = cbPerPixelLighting.Enabled;
            if (loading) {
                return;
            }

            if (cbPerPixelLighting.Checked) {
                MessageBox.Show(strings["LightOverrideOn"], Statics.strings["Warning"]);
            } else {
                MessageBox.Show(strings["LightOverrideOff"], Statics.strings["Warning"]);
            }
            bMWLightingReset_Click(null, null);
        }

        private void bReportingShowLog_Click(object sender, EventArgs e) {
            displayLogFile(Statics.fn_runtimelog);
        }

        private void bReportingShowDLWizardLog_Click(object sender, EventArgs e) {
            displayLogFile(Statics.fn_dlLog);
        }

        private void displayLogFile(string path) {
            if (File.Exists(path)) {
                var f = new LogViewerForm(path);
                f.ShowDialog();
            }
        }

        private void getWindowAlignState(out int alignX, out int alignY) {
            // Default to center alignment.
            alignX = alignY = 1;

            // Read alignment from tag string of active control.
            foreach (RadioButton alignButton in panelWindowAlign.Controls) {
                if (alignButton.Checked) {
                    String[] s = (alignButton.Tag as string).Split(',');
                    alignX = Int32.Parse(s[0]);
                    alignY = Int32.Parse(s[1]);
                    return;
                }
            }
        }
        
        private void setWindowAlignState(int alignX, int alignY) {
            // Match alignment with tag string.
            string t = String.Format("{0},{1}", alignX, alignY);

            foreach (RadioButton alignButton in panelWindowAlign.Controls) {
                if (t == (alignButton.Tag as string)) {
                    alignButton.Checked = true;
                    return;
                }
            }
        }
    }

}