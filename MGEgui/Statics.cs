using System;
using FileVersionInfo = System.Diagnostics.FileVersionInfo;
using Process = System.Diagnostics.Process;
using File = System.IO.File;
using Directory = System.IO.Directory;
using Serializer = System.Runtime.Serialization.Formatters.Binary.BinaryFormatter;
using Application = System.Windows.Forms.Application;
using MessageBox = System.Windows.Forms.MessageBox;
using MessageBoxButtons = System.Windows.Forms.MessageBoxButtons;
using DialogResult = System.Windows.Forms.DialogResult;
using Registry = Microsoft.Win32.Registry;
using RegistryKey = Microsoft.Win32.RegistryKey;
using System.Windows.Forms;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using MGEgui.DirectX;
using MGEgui.Localization;
using MGEgui.INI;


namespace MGEgui {

    [Serializable]
    public class Technique {
        public string Description;
        public string Name;
        public string[] Lines;

        public Technique() {
            Description = "Description";
            Name = "Unnamed";
            Lines = new string[0];
        }
    }

    /// <summary>
    /// The list of different macro types
    /// </summary>
    /// <remarks>
    /// Copied from input.h
    /// Make sure that this is always up to date (Needs Console3, Console4, Offhammer)
    /// </remarks>
    public enum MacroType : byte {
        Unused = 0,
        // This key isn't assigned to anything
        // FD_Console
        Console1 = 1,
        // Enter console command, exit console
        Console2 = 2,
        // Dont open or close console
        // FD_Press
        Hammer1 = 3,
        // Hammer a key while pressed
        Hammer2 = 4,
        // Start hammering a key
        Unhammer = 5,
        // Stop hammering a key
        AHammer1 = 6,
        // As Hammer except hammers in alternate frames
        AHammer2 = 7,
        AUnhammer = 8,
        Press1 = 9,
        // Other keys pressed while this is pressed
        Press2 = 10,
        // Press keys when this is pressed, but dont depress
        Unpress = 11,
        // Depress any pressed keys
        // FD_Timer
        BeginTimer = 12,
        // Start a timer trigger
        EndTimer = 13,
        // End a timer trigger
        // FD_Graphics
        Graphics = 14
        // Perform a graphics function
    }

    /// <summary>
    /// What a particular MacroEditerForm is being used for
    /// </summary>
    public enum MacroFormType {
        Unknown,
        Editor,
        Console,
        Press,
        Function,
        Timer,
        Trigger

    }

    [Serializable]
    public struct KeyPress {
        public bool Down;
        public byte Code;

        public KeyPress(byte code, bool down) {
            Down = down;
            Code = code;
        }
    }

    [Serializable]
    public class FD_Console {
        public byte Length;
        // The size of the string
        public KeyPress[] KeyCodes;
        // A list of keycodes
        public string Description;
        // A description of the command
        public FD_Console() {
            Length = 0;
            KeyCodes = new KeyPress[Statics.MACROS];
            Description = "";
        }
    }
    [Serializable]
    public class FD_Press {
        public bool[] KeyStates;
        // Last 8 for mouse
        public FD_Press() {
            KeyStates = new bool[Statics.MACROS];
        }
    }
    [Serializable]
    public class FD_Timer {
        public byte TimerID;
        // The timer to activate/deactivate
        public FD_Timer() {
            TimerID = 0;
        }
    }
    [Serializable]
    public class FD_Graphics {
        public byte function;
        // The GraphicsFuncs to call in the fake d3d dll
    }

    [Serializable]
    public class Macro {
        public MacroType Type;
        public FD_Console Console;
        public FD_Press Press;
        public FD_Timer Timer;
        public FD_Graphics Graphics;

        public Macro() {
            Console = new FD_Console();
            Press = new FD_Press();
            Timer = new FD_Timer();
            Graphics = new FD_Graphics();
        }
    }
    [Serializable]
    public class Trigger {
        public uint TimeInterval;
        public bool Active;
        public FD_Press data;

        public Trigger() {
            TimeInterval = 0;
            Active = false;
            data = new FD_Press();
        }
    }

    public static class MutexCheck {
        private const string MutexName = "MGEguiMutex";
        private static System.Threading.Mutex mutex;

        internal static bool PerformCheck() {
            bool n;
            mutex = new System.Threading.Mutex(true, MutexName, out n);
            return n;
        }
    }

    /// <summary>
    /// Contains some constant variables, misc static functions and the program entry point
    /// </summary>
    public class Statics {
        /// <summary>
        /// Used to ensure that created options files match the dll versions
        /// </summary>
        public const string programName = "Morrowind Graphics Extender XE";
        public const string versionNumber = "0.11.2";
        public const string versionString = "v" + versionNumber;
        public const byte SaveVersion = 47;
        public const byte DistantLandVersion = 6;

        public const int MACROS = 266;
        public const int TRIGGERS = 4;

        /* names of used files */
        public const string fn_nul = "NUL";
        public const string fn_mwini = "Morrowind.ini";
        public const string fn_runtimelog = "mgeXE.log";
        public const string fn_inifile = "MGE3/MGE.ini";
        public const string fn_didata = "MGE3/DInput.data";
        public const string fn_macro = "MGE3/Macros.sav";
        public const string fn_triger = "MGE3/Triggers.sav";
        public const string fn_remap = "MGE3/remap.data";
        public const string fn_dldefaultoverride = "MGE3/MGE XE Default Statics Classifiers.ovr";
        public const string fn_dllog = "MGE3/DistantLand.log";
        public const string fn_datafiles = "Data files";
        public const string fn_dl = "Data files/distantland";
        public const string fn_dlver = "Data files/distantland/version";
        public const string fn_world = "Data files/distantland/world";
        public const string fn_worldds = "Data files/distantland/world.dds";
        public const string fn_worldn = "Data files/distantland/world_n.dds";
        public const string fn_statics = "Data files/distantland/statics";
        public const string fn_usagedata = "Data files/distantland/statics/usage.data";
        public const string fn_statmesh = "Data files/distantland/statics/static_meshes";
        public const string fn_stattex = "Data files/distantland/statics/textures";
        public const string pathShaders = @"data files\shaders\XEshaders";
        /* registry keys */
        public const string reg_mw = @"Software\Bethesda Softworks\Morrowind";

        public static string runDir;

        public static int tipReadSpeed;

        public static LocalizationInterface Localizations;
        public static Dictionary<string, string> strings = new Dictionary<string, string>();

        public static MainForm mf;

        public static Macro[] Macros = new Macro[MACROS];
        public static Trigger[] Triggers = new Trigger[TRIGGERS];
        public static byte[] Remapper = new byte[256];

        public static readonly Serializer formatter = new Serializer();

        public static readonly System.Globalization.CultureInfo Culture = new System.Globalization.CultureInfo("en-US", false);
        public static readonly System.Globalization.NumberFormatInfo NumFormat = Culture.NumberFormat;
        public static readonly System.Text.Encoding UTF8NoPreamble = new System.Text.UTF8Encoding(false);

        private struct CommandArgs {
            public readonly bool styles;
            public readonly bool mutex;

            public CommandArgs(string[] args) {
                styles = true;
                mutex = true;
                foreach (string s in args) {
                    switch (s) {
                        case "-nostyles":
                            styles = false;
                            break;
                        case "-nomutex":
                            mutex = false;
                            break;
                    }
                }
            }
        }

        public static Control [] GetChildControls(Control ctrl) {
            ArrayList controls = new ArrayList();
            foreach (Control c in ctrl.Controls) {
                controls.Add(c);
                controls.AddRange(GetChildControls(c));
            }
            return (Control[])controls.ToArray(typeof(Control));
        }

        /// <summary>
        /// Entry point for this program
        /// </summary>
        [STAThread]
        public static void Main(string[] sargs) {
            Thread.CurrentThread.CurrentUICulture = Culture;
            CommandArgs args = new CommandArgs(sargs);

            if (args.styles) {
                Application.EnableVisualStyles();
            }

            // Damn .NET text rendering
            Application.SetCompatibleTextRenderingDefault(false);

            Directory.SetCurrentDirectory(System.IO.Path.GetDirectoryName(Application.ExecutablePath));

            Localizations = new LocalizationInterface();
            try {
                string[] langfiles = Directory.GetFiles("MGE3", "*.lng");
                foreach (string langfile in langfiles) {
                    Localizations.Add(langfile);
                }
            } catch {
            }

            string language = "English (default)";
            bool autoLanguage = true;
            try {
                INIFile MGEini = new INIFile(fn_inifile, new INIFile.INIVariableDef [] {
                    INIFile.iniDefEmpty,
                    MainForm.iniLanguage,
                    MainForm.iniAutoLang
                });
                language = MGEini.getKeyString("Language");
                autoLanguage = (MGEini.getKeyValue("AutoLang") == 1);
            } catch {
            }
            Localizations.Current = language;
            Localizations.ApplyStrings("", strings);

            if (args.mutex && !MutexCheck.PerformCheck()) {
                MessageBox.Show(strings["MGEguiRunning"], strings["Error"]);
                return;
            }
            Process[] morrowind = Process.GetProcessesByName("Morrowind");
            foreach (Process p in morrowind) {
                MessageBox.Show(strings["MWRunning"], strings["Error"]);
                return;
            }

            if (!File.Exists("./morrowind.exe") || !File.Exists("./morrowind.ini") || !Directory.Exists("data files")) {
                MessageBox.Show(strings["NotMWDir"], strings["Error"]);
                return;
            }
            if (!Directory.Exists("MGE3") || !File.Exists("./MGE3/MGEfuncs.dll") || !File.Exists("./d3d8.dll") || !File.Exists("./dinput8.dll")) {
                MessageBox.Show(strings["MGEMissing"], strings["Error"]);
                return;
            }
            // Morrowind version info
            try {
                FileVersionInfo MorrowVersion = FileVersionInfo.GetVersionInfo("Morrowind.exe");
                if (MorrowVersion.FileMajorPart != 1 || MorrowVersion.FileMinorPart < 6) {
                    MessageBox.Show(strings["MWIncompat"], strings["Error"]);
                    return;
                }
            } catch {
                MessageBox.Show(strings["MWCorrupt"], strings["Error"]);
                return;
            }

            runDir = System.Windows.Forms.Application.StartupPath;

            // Create some structures
            for (int i = 0; i < MACROS; i++) {
                Macros[i] = new Macro();
            }
            for (int i = 0; i < TRIGGERS; i++) {
                Triggers[i] = new Trigger();
            }
            DXMain.GetDeviceCaps();
            mf = new MainForm(autoLanguage);
            Application.Run(mf);
        }

    }
}