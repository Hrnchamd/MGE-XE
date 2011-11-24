using System;
using System.Reflection;
using System.Security;
using System.Collections.Generic;
using System.Globalization;
using System.Windows.Forms;
using System.Text;
using MGEgui.INI;

namespace MGEgui.Localization {

    public class LocalizationInterface {

        public class Localization {

            public string FileName;
            public string Language;
            public INIFile langFile;
            public string Translator;

            private const string secLang = "## Language ##";
            private const string entLang = "lang";
            private const string entTtor = "ttor";

            private static INIFile.INIVariableDef [] langINI = new INIFile.INIVariableDef [] {
                INIFile.iniDefEmpty,
                new INIFile.INIVariableDef (entLang, secLang, "Name", INIFile.INIVariableType.String, ""),
                new INIFile.INIVariableDef (entTtor, secLang, "Translator", INIFile.INIVariableType.String, "")
            };

            public Localization (string fileName) {
                FileName = fileName;
                langFile = new INIFile (fileName, langINI);
                Language = langFile.getKeyString (entLang);
                Translator = langFile.getKeyString (entTtor);
            }

        }

        public static string SysLang {
            get {
                return (SysLangOrg + " (" + SysLangEng + ")");
            }
        }

        public static string SysLangRev {
            get {
                return (SysLangEng + " (" + SysLangOrg + ")");
            }
        }

        public static string SysLangEng {
            get {
                string s = CultureInfo.CurrentCulture.EnglishName;
                int i = s.IndexOf ('(');
                if (i > 0) s = (s.Substring (0, i)).Trim ();
                return s;
            }
        }

        public static string SysLangOrg {
            get {
                string s = CultureInfo.CurrentCulture.NativeName;
                int i = s.IndexOf ('(');
                if (i > 0) s = (s.Substring (0, i)).Trim ();
                return s;
            }
        }

        private Dictionary<string, Localization> localizations;

        public LocalizationInterface () {
            localizations = new Dictionary<string, Localization> ();
        }

        public void Add (Localization localization) {
            localizations.Add (localization.Language, localization);
        }

        public void Add (string fileName) {
            if (fileName != null && fileName != "") {
                Localization localization = new Localization (fileName);
                if (localization.Language != "") localizations.Add (localization.Language, localization);
            }
        }

        public string [] Languages {
            get {
                List<string> list = new List<string> (localizations.Keys);
                list.Sort ();
                return list.ToArray ();
            }
        }

        public Localization this [string Language] {
            get {
                if (localizations.ContainsKey (Language)) return localizations [Language];
                else return null;
            }
            set {
                if (localizations.ContainsKey (Language)) localizations [Language] = value;
                else localizations.Add (Language, value);
            }
        }

        public int Count {
            get { return localizations.Count; }
        }

        public void ApplyStrings (string name, Dictionary<string, Str> messages, string Language) {
            if (localizations.ContainsKey (Language)) {
                Localization localization = localizations [Language];
                ApplyStrings (name, messages, localization);
            }
        }

        public void ApplyStrings (string name, Dictionary<string, Str> messages, Localization localization) {
            Dictionary<string, string> dict;
            dict = localization.langFile.getSectionKeys (name + ".Strings");
            foreach (KeyValuePair<string, string> entry in dict) {
                if (messages.ContainsKey (entry.Key)) messages [entry.Key].text = entry.Value;
            }
        }

        public void Apply (Form form, string Language) {
            if (localizations.ContainsKey (Language)) {
                Localization localization = localizations [Language];
                Dictionary<string, string> dict;
                dict = localization.langFile.getSectionKeys (form.Name + ".Text");
                foreach (KeyValuePair<string, string> entry in dict) {
                    Control [] controls = form.Controls.Find (entry.Key, true);
                    foreach (Control control in controls) if (!(control is ComboBox)) control.Text = entry.Value;
                }
                FieldInfo messages_field;
                messages_field = form.GetType ().GetField ("strings");
                if (messages_field != null) {
                    Dictionary<string, Str> messages = new Dictionary<string, Str> ();
                    if (messages_field.FieldType == messages.GetType ()) {
                        messages = messages_field.GetValue (form) as Dictionary<string, Str>;
                        ApplyStrings (form.Name, messages, localization);
                    }
                }
                messages_field = form.GetType ().GetField ("tooltip_messages");
                if (messages_field != null) {
                    Dictionary<string, Tip> tips = new Dictionary<string, Tip> ();
                    if (messages_field.FieldType == tips.GetType ()) {
                        tips = messages_field.GetValue (form) as Dictionary<string, Tip>;
                        dict = localization.langFile.getSectionKeys (form.Name + ".ToolTips");
                        foreach (KeyValuePair<string, string> entry in dict) {
                            if (tips.ContainsKey (entry.Key)) tips [entry.Key].tip = entry.Value;
                            else {
                                Control [] controls = form.Controls.Find (entry.Key, true);
                                foreach (Control control in controls) if (control is TabPage) (control as TabPage).ToolTipText = entry.Value;
                            }
                        }
                    }
                }
            }
        }

    }

}
