using System;
using System.IO;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * INIFile class for loading/saving settings to INI files.
 * Created from scratch by krzymar / krzymark (Krzysztof Markowski)
 *
 * Changelog:
 *	v.1.00 (2009-03-15):
 *	 - initial version
 *	v.1.01 (2009-03-16):
 *	 - fixed ini save function to truncate file before writing to it
 *	 - dictionary and boolean types are using only their dictionary entries
 *	v.1.02 (2009-03-21):
 *	 - added hasSection method for checking if given section is initialized
 *	 - changed ToLower functions to use predefined static instead of new Culture
 *	v.1.03 (2009-04-12):
 *	 - added variable intialization method
 *	 - added boolean overloaded method to set key
 *	 - fixed setting key to string
 *	v.1.04 (2009-04-16):
 *	 - fixed decimal separator conversion
 *	v.1.05 (2009-04-26):
 *	 - added string key type handling
 *	 - fixed key / value separator to be first spotted '=' instead of last one
 *	v.1.06 (2009-06-05):
 *	 - added support for file character encoding other than UTF-8
 *	v.1.07 (2009-07-07):
 *	 - added support for escape character in quoted strings and keys
 *	v.1.08 (2010-04-02):
 *	 - changed default encoding for saving files to UTF-8 without preable
 *	v.1.09 (2010-04-26):
 *	 - added Yes/No type boolean support
 *	v.1.10 (2010-05-14):
 *	 - added getSectionKeys that returns Dictionary of a pair <Key,qsValue>
 *	 - fixed qsValue to return unescaped string with removed quotes for undefined entry type
 *	v.1.11 (2010-05-19):
 *	 - added saving with selected precision for floating point variables
 *	 - fixed escaping and unescaping strings and made escape and unescape methods static
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

namespace MGEgui.INI {

    public class INIFile {

        public static string INIComment = ";";
        public static char INIQuotation = '\"';
        public static char INIEscape = '\\';
        public static char[] unescapedChars = { '\u0008', '\u0009', '\u000a', '\u000d' };
        public static char[] escapedChars = { 'b', 't', 'n', 'r' };

        
        public static INIFile.INIVariableDef iniDefEmpty = new INIFile.INIVariableDef();

        public static Dictionary<string, double> INIBools = new Dictionary<string, double> {
            {"True", 1},
            {"False", 0},
            {"On", 1},
            {"Off", 0},
            {"Yes", 1},
            {"No", 0},
            {"1", 1},
            {"0", 0}
        };

        public enum INIEntryType {
            Comment = 0,
            Section = 1,
            Entry = 2
        }

        public enum INIBoolType {
            Text = 0,
            OnOff = 1,
            YesNo = 2,
            Number = 3
        }

        public enum INIVariableType {
            None = 0,
            Boolean = 1,
            Byte = 2,
            SByte = 3,
            Int16 = 4,
            UInt16 = 5,
            Int32 = 6,
            UInt32 = 7,
            Int64 = 8,
            UInt64 = 9,
            Single = 10,
            Double = 11,
            Char = 12,
            String = 13,
            Dictionary = 14,
            Flags = 15
        }

        public struct INIVariableDef {

            public string var;
            public string section;
            public string key;
            public INIVariableType type;
            public INIBoolType boolType;
            public string defValue;
            public Dictionary<string, double> dict;
            public double min;
            public double max;
            public sbyte precision;
            public bool useMinMax;

            public INIVariableDef(string section, string defValue) {
                this.var = null;
                this.section = section;
                this.key = null;
                this.type = INIVariableType.None;
                this.boolType = INIBoolType.Text;
                this.defValue = defValue;
                this.dict = null;
                this.min = 0;
                this.max = 0;
                this.precision = -1;
                this.useMinMax = false;
            }

            public INIVariableDef(string var, string section, string variable, INIBoolType type, string defValue) {
                this.var = var;
                this.section = section;
                this.key = variable;
                this.type = INIVariableType.Boolean;
                this.boolType = type;
                this.defValue = defValue;
                this.dict = INIBools;
                this.min = 0;
                this.max = 0;
                this.precision = -1;
                this.useMinMax = false;
            }

            public INIVariableDef(string var, string section, string variable, INIVariableType type, string defValue) {
                this.var = var;
                this.section = section;
                this.key = variable;
                this.type = type;
                this.boolType = INIBoolType.Text;
                this.defValue = defValue;
                this.dict = (type == INIVariableType.Boolean ? INIBools : null);
                this.min = 0;
                this.max = 0;
                this.precision = -1;
                this.useMinMax = false;
            }

            public INIVariableDef(string var, string section, string variable, INIVariableType type, string defValue, Dictionary<string, double> dict) {
                this.var = var;
                this.section = section;
                this.key = variable;
                this.type = type;
                this.boolType = INIBoolType.Text;
                this.defValue = defValue;
                this.dict = dict;
                this.min = 0;
                this.max = 0;
                this.precision = -1;
                this.useMinMax = false;
            }

            public INIVariableDef(string var, string section, string variable, INIVariableType type, string defValue, double min, double max) {
                this.var = var;
                this.section = section;
                this.key = variable;
                this.type = type;
                this.boolType = INIBoolType.Text;
                this.defValue = defValue;
                this.dict = (type == INIVariableType.Boolean ? INIBools : null);
                this.min = min;
                this.max = max;
                this.precision = -1;
                this.useMinMax = true;
            }

            public INIVariableDef (string var, string section, string variable, INIVariableType type, string defValue, double min, double max, sbyte precision) {
                this.var = var;
                this.section = section;
                this.key = variable;
                this.type = type;
                this.boolType = INIBoolType.Text;
                this.defValue = defValue;
                this.dict = (type == INIVariableType.Boolean ? INIBools : null);
                this.min = min;
                this.max = max;
                this.precision = precision;
                this.useMinMax = true;
            }

            public INIVariableDef (string var, string section, string variable, INIVariableType type, string defValue, Dictionary<string, double> dict, double min, double max) {
                this.var = var;
                this.section = section;
                this.key = variable;
                this.type = type;
                this.boolType = INIBoolType.Text;
                this.defValue = defValue;
                this.dict = dict;
                this.min = min;
                this.max = max;
                this.precision = -1;
                this.useMinMax = true;
            }
        }

        public class INILine {

            protected static string curSection = "";
            public static bool modified = false;
            public string section;
            public string entry;
            public string key;
            public string value;
            public string comment;
            public INIVariableType varType;
            public INIBoolType varBool;
            public Dictionary<string, double> varDict;
            public double min;
            public double max;
            public bool useMinMax;
            public string defVal;

            public static string setSection {
                get { return curSection; }
                set { curSection = value.ToLower(Statics.Culture); }
            }

            public string iEntry {
                get { return entry.ToLower(Statics.Culture); }
            }

            public string iKey {
                get { return key.ToLower(Statics.Culture); }
            }

            public string iValue {
                get { return value.ToLower(Statics.Culture); }
            }

            private static string escape(string value) {
                List<char> unesc = new List<char>(unescapedChars);
                List<char> esc = new List<char>(escapedChars);
                unesc.AddRange(new char[] {INIEscape, INIQuotation});
                esc.AddRange(new char[] {INIEscape, INIQuotation});
                string retstring = "";
                foreach (char c in value) {
                    if (unesc.Contains(c)) retstring += INIEscape.ToString () + esc[unesc.IndexOf(c)].ToString ();
                    else retstring += c.ToString ();
                }
                return retstring;
            }

            private static string unescape (string value) {
                List<char> unesc = new List<char>(unescapedChars);
                List<char> esc = new List<char>(escapedChars);
                unesc.AddRange(new char[] {INIEscape, INIQuotation});
                esc.AddRange(new char[] {INIEscape, INIQuotation});
                bool escaped = false;
                string retstring = "";
                foreach (char c in value) {
                    if (escaped) {
                        escaped = false;
                        if (esc.Contains(c)) retstring += unesc[esc.IndexOf(c)].ToString ();
                        else retstring += c.ToString ();
                    } else if (c == INIEscape) {
                        escaped = true;
                    } else retstring += c.ToString ();
                }
                return retstring;
            }

            public string sValue {
                set {
                    if (this.varType == INIVariableType.String) this.value = INIQuotation + value + INIQuotation;
                    else this.value = value;
                    this.entry = this.key + "=" + this.value;
                }
                get {
                    if (this.varType == INIVariableType.String) {
                        if (this.value.Length > 1 && this.value.StartsWith(INIQuotation.ToString()) && this.value.EndsWith(INIQuotation.ToString())) return this.value.Substring(1, this.value.Length - 2);
                        //return this.value;
                    }
                    return this.value;
                }
            }

            public string qsValue {
                set {
                    if (this.varType == INIVariableType.String) this.value = INIQuotation + escape(value) + INIQuotation;
                    else this.value = value;
                    this.entry = this.key + "=" + this.value;
                }
                get {
                    if (this.varType == INIVariableType.String || this.varType == INIVariableType.None) {
                        if (this.value.Length > 1 && this.value.StartsWith(INIQuotation.ToString()) && this.value.EndsWith(INIQuotation.ToString())) return unescape(this.value.Substring(1, this.value.Length - 2));
                        else return unescape(this.value);
                    }
                    return this.value;
                }
            }

            public double dValue {
                get {
                    double ret = 0;
                    if (varDict != null) foreach (KeyValuePair<string, double> vd in varDict) {
                        if (iValue.CompareTo(vd.Key.ToLower(Statics.Culture)) == 0) {
                            return vd.Value;
                        }
                    }
                    if (varType == INIVariableType.Boolean) {
                        if (varDict != null) foreach (KeyValuePair<string, double> vd in varDict) {
                            if (defVal.ToLower(Statics.Culture).CompareTo(vd.Key.ToLower(Statics.Culture)) == 0) {
                                return vd.Value;
                            }
                        }
                    } else if (varType == INIVariableType.Dictionary) {
                        if (varDict != null) foreach (KeyValuePair<string, double> vd in varDict) {
                            if (defVal.ToLower(Statics.Culture).CompareTo(vd.Key.ToLower(Statics.Culture)) == 0) {
                                return vd.Value;
                            }
                        }
                    }
                    else try {
                        ret = double.Parse(value, Statics.NumFormat);
                    } catch {
                        if (varDict == null) try { ret = double.Parse(defVal, Statics.NumFormat); } catch { ret = 0; }
                        else foreach (KeyValuePair<string, double> vd in varDict) {
                            if (defVal.ToLower(Statics.Culture).CompareTo(vd.Key.ToLower(Statics.Culture)) == 0) {
                                return vd.Value;
                            }
                        }
                    }
                    if (useMinMax) {
                        if (ret < min) ret = min;
                        else if (ret > max) ret = max;
                    }
                    return ret;
                }
                set {
                    bool useDict = false;
                    int dictPos;
                    if (varType == INIVariableType.Boolean) dictPos = (int)varBool * 2;
                    else dictPos = 0;
                    if (varDict != null) foreach (KeyValuePair<string, double> vd in varDict) {
                        if (dictPos-- > 0) continue;
                        if (vd.Value == value) {
                            this.value = vd.Key;
                            useDict = true;
                            break;
                        }
                    }
                    if (varType != INIVariableType.Dictionary) {
                        double temp = value;
                        if (!useDict && useMinMax) {
                            if (temp < min) { temp = min; useDict = true; }
                            else if (temp > max) { temp = max; useDict = true; }
                            if (useDict && varDict != null) {
                                useDict = false;
                                foreach (KeyValuePair<string, double> vd in varDict) if (vd.Value == temp) {
                                    this.value = vd.Key;
                                    useDict = true;
                                    break;
                                }
                            }
                        }
                        if (!useDict) this.value = temp.ToString (Statics.NumFormat);
                    } else if (!useDict) this.value = defVal;
                    this.entry = this.key + "=" + this.value;
                }
            }

            private int[] ScanQuotes(string line) {
                List<int> quots = new List<int>();
                int beginning = -1;
                while (line.Length > beginning + 1 && (beginning = line.IndexOf(INIQuotation, beginning + 1)) != -1) {
                    if (quots.Count % 2 != 1 || line[beginning - 1] != '\\') quots.Add(beginning);
                }
                return quots.ToArray();
            }

            public INILine(string line) {
                entry = "";
                key = "";
                value = "";
                comment = "";
                int[] quot = ScanQuotes(line);
                int quots = quot.Length / 2;
                int index = -1;
                int beginning = 0;
                if (quots > 0) for (int i = 0; i < quots; ++i) {
                    index = line.IndexOf(INIComment, beginning);
                    if (index == -1) break;
                    if (index > quot[i * 2] && index < quot[i * 2 + 1]) index = -1;
                    beginning = quot[i * 2 + 1];
                } else index = line.IndexOf(INIComment); 
                if (index != -1) {
                    if (index > 0) entry = line.Substring(0, index).Trim();
                    comment = line.Substring(entry.Length);
                } else entry = line.Trim();
                if (entry.Length > 0 && entry[0] == '[' && entry.EndsWith("]")) {
                    setSection = entry.Length > 2 ? entry.Substring(1, entry.Length - 2) : "";
                }
                index = entry.IndexOf('=');
                if (index != -1) {
                    if (index > 0) key = entry.Substring(0, index).Trim();
                    value = entry.Substring(index + 1).Trim();
                }
                section = curSection;
            }

            public INILine(INIEntryType entryType, string entryText, string entryComment) {
                entry = "";
                key = "";
                value = "";
                comment = (entryComment != "" ? "\t\t" + INIComment + " " + entryComment : "");
                switch (entryType) {
                    case INIEntryType.Comment:
                        comment = INIComment + " " + entryText + comment;
                        break;
                    case INIEntryType.Section:
                        entry = "[" + entryText + "]";
                        setSection = entryText;
                        break;
                    case INIEntryType.Entry:
                        entry = entryText;
                        break;
                }
                section = curSection;
                modified = true;
    	    }

            public INILine(string stringVar, string stringVal) {
                entry = "";
                key = stringVar;
                value = stringVal;
                comment = "";
                section = curSection;
                modified = true;
            }

            public INILine(string boolVar, bool boolVal, INIBoolType boolType) {
                entry = "";
                key = boolVar;
                value = (boolVal ? (boolType == INIBoolType.Text ? "True" : (boolType == INIBoolType.OnOff ? "On" : (boolType == INIBoolType.YesNo ? "Yes" : "1"))) : (boolType == INIBoolType.Text ? "False" : (boolType == INIBoolType.OnOff ? "Off" : (boolType == INIBoolType.YesNo ? "No" : "0"))));
                comment = "";
                section = curSection;
                modified = true;
            }

        }

        public List<INILine> iniContent;
        public INIVariableDef[] varDefn;
        public string fileName;
        public bool modified = false;
        public bool saveDef = false;
        public Encoding encoding = Statics.UTF8NoPreamble;

        public INIFile(string file, INIVariableDef[] varDefn, bool saveDef) {
            this.fileName = file;
            this.varDefn = varDefn;
            this.saveDef = saveDef;
            this.iniContent = new List<INILine>();
            loadINI();
        }

        public INIFile(string file, INIVariableDef[] varDefn) : this(file, varDefn, false) { }

        public INIFile(string file, INIVariableDef[] varDefn, Encoding encoding, bool saveDef) {
            this.fileName = file;
            this.varDefn = varDefn;
            this.saveDef = saveDef;
            this.encoding = encoding;
            this.iniContent = new List<INILine>();
            loadINI();
        }

        public INIFile(string file, INIVariableDef[] varDefn, Encoding encoding) : this(file, varDefn, encoding, false) { }

        private INIVariableDef getVarDefn(string section, string key) {
            string iSection = section.ToLower(Statics.Culture);
            string iKey = key.ToLower(Statics.Culture);
            foreach (INIVariableDef defn in varDefn) if (defn.section != null && iSection.CompareTo(defn.section.ToLower(Statics.Culture)) == 0 && iKey.CompareTo(defn.key.ToLower(Statics.Culture)) == 0) {
                return defn;
            }
            return varDefn[0];
        }

        private INIVariableDef getVarDefn(string variable) {
            INIVariableDef ret = varDefn[0];
            foreach (INIVariableDef defn in varDefn) if (defn.var != null && variable.CompareTo(defn.var) == 0) {
                return defn;
            }
            return varDefn[0];
        }

        private void loadINI() {
            iniContent.Clear();
            StreamReader sr = null;
            try { sr = new StreamReader(File.OpenRead(fileName), encoding); } catch { }
            INILine.setSection = "";
            if (sr != null) {
                while (!sr.EndOfStream) {
                    INILine line = new INILine(sr.ReadLine());
                    INIVariableDef vd = getVarDefn(line.section, line.key);
                    line.defVal = vd.defValue;
                    line.varType = vd.type;
                    line.varDict = vd.dict;
                    line.varBool = vd.boolType;
                    line.useMinMax = vd.useMinMax;
                    line.max = vd.max;
                    line.min = vd.min;
                    iniContent.Add(line);
                }
                sr.Close();
            }
        }

        public void initialize() {
            int i = 0;
            foreach (INIVariableDef def in varDefn) {
                if (i++ == 0 || isKeySet(def.var)) continue;
                setKey(def.var, def.defValue);
            }
        }

        public void reinitialize() {
            int i = 0;
            foreach (INIVariableDef def in varDefn) {
                if (i++ == 0) continue;
                setKey(def.var, def.defValue);
            }
        }

        public bool isKeySet(string variable) {
            INIVariableDef vd = getVarDefn(variable);
            return isKeySet(vd.section, vd.key);
        }

        public bool isKeySet(string section, string key) {
            string iSection = section.ToLower(Statics.Culture);
            string iKey = key.ToLower(Statics.Culture);
            foreach (INILine line in iniContent) if (iSection.CompareTo(line.section) == 0 && iKey.CompareTo(line.iKey.ToLower(Statics.Culture)) == 0) {
                return true;
            }
            return false;
        }

        public bool save() {
            if (modified) {
                StreamWriter sw = null;
                try { sw = new StreamWriter(File.Create(fileName), encoding); } catch { return false; }
                if (sw != null) {
                    foreach (INILine line in iniContent) sw.WriteLine(line.entry + line.comment);
                    sw.Close();
                } else return false;
            }
            return true;
        }

        private bool isDefault(string section, string key, string sValue) {
            INIVariableDef vd = getVarDefn(section, key);
            string iValue = sValue.ToLower(Statics.Culture);
            if (vd.defValue != null) {
                string def = vd.defValue.ToLower(Statics.Culture);
                if (iValue == def) return true;
                bool useDict = false;
                double dVal = double.NegativeInfinity, dDef = double.PositiveInfinity;
                if (vd.dict != null) {
                    foreach (KeyValuePair<string, double> dict in vd.dict) if (dict.Key.ToLower(Statics.Culture) == iValue) {
                        dVal = dict.Value;
                        useDict = true;
                        break;
                    }
                    if (useDict) foreach (KeyValuePair<string, double> dict in vd.dict) if (dict.Key.ToLower(Statics.Culture) == def) {
                        dDef = dict.Value;
                        break;
                    }
                    if (dVal == dDef) return true;
                }
            }
            return false;
        }

        private bool isDefault(string section, string key, double dValue) {
            INIVariableDef vd = getVarDefn(section, key);
            if (vd.defValue != null) {
                string def = vd.defValue.ToLower(Statics.Culture);
                bool useDict = false;
                double dDef = double.NaN;
                if (vd.dict != null) {
                    foreach (KeyValuePair<string, double> dict in vd.dict) if (dict.Key.ToLower(Statics.Culture) == def) {
                        dDef = dict.Value;
                        useDict = true;
                        break;
                    }
                    if (useDict && dValue == dDef) return true;
                }
                try {
                    //dDef = Convert.ToDouble(def);
                    dDef = double.Parse(def, Statics.NumFormat);
                    if (dValue == dDef) return true;
                } catch { }
            }
            return false;
        }

        public string getKeyString(string variable) {
            INIVariableDef vd = getVarDefn(variable);
            return getKeyString(vd.section, vd.key);
        }

        public string getKeyString(string section, string key) {
            string iSection = section.ToLower(Statics.Culture);
            string iKey = key.ToLower(Statics.Culture);
            foreach (INILine line in iniContent) if (iSection.CompareTo(line.section) == 0 && iKey.CompareTo(line.iKey.ToLower(Statics.Culture)) == 0) {
                return line.sValue;
            }
            foreach (INIVariableDef def in varDefn) {
                if (def.section != null && iSection.CompareTo(def.section.ToLower(Statics.Culture)) == 0 && iKey.CompareTo(def.key.ToLower(Statics.Culture)) == 0) {
                    try { return def.defValue; }
                    catch { break; }
                }
            }
            return "";
        }

        public double getKeyValue(string variable) {
            INIVariableDef vd = getVarDefn(variable);
            return getKeyValue(vd.section, vd.key);
        }

        public double getKeyValue(string section, string key) {
            string iSection = section.ToLower(Statics.Culture);
            string iKey = key.ToLower(Statics.Culture);
            foreach (INILine line in iniContent) if (iSection.CompareTo(line.section) == 0 && iKey.CompareTo(line.iKey.ToLower(Statics.Culture)) == 0) {
                return line.dValue;
            }
            foreach (INIVariableDef def in varDefn) {
                if (def.section != null && iSection.CompareTo(def.section.ToLower(Statics.Culture)) == 0 && iKey.CompareTo(def.key.ToLower(Statics.Culture)) == 0) {
                    string defVal = def.defValue;
                    if (def.dict != null) foreach (KeyValuePair<string, double> dict in def.dict) {
                        if (def.defValue.ToLower(Statics.Culture) == dict.Key.ToLower(Statics.Culture)) return dict.Value;
                    }
                    try { return double.Parse(def.defValue, Statics.NumFormat); } catch { break; }
                }
            }
            return 0;
        }

        public bool hasSection(string section) {
            foreach (INILine line in iniContent) if (line.section.CompareTo(section.ToLower(Statics.Culture)) == 0) return true;
            return false;
        }

        public void setKey(string variable, string sValue) {
            INIVariableDef vd = getVarDefn(variable);
            keySet(vd.section, vd.key, true, sValue, double.NaN);
        }

        public void setKey(string variable, double dValue) {
            INIVariableDef vd = getVarDefn(variable);
            keySet(vd.section, vd.key, false, null, dValue);
        }

        public void setKey(string variable, bool bValue) {
            INIVariableDef vd = getVarDefn(variable);
            keySet(vd.section, vd.key, false, null, bValue ? 1 : 0);
        }

        public void setKey(string section, string key, string sValue) {
            keySet(section, key, true, sValue, double.NaN);
        }

        public void setKey(string section, string key, bool bValue) {
            keySet(section, key, false, null, bValue ? 1 : 0);
        }

        private void keySet(string section, string key, bool useString, string sValue, double dValue) {
            List<string> sections = new List<string>();
            List<string> keys = new List<string>();
            List<string> comments = new List<string>();
            foreach (INILine line in iniContent) {
                sections.Add(line.section);
                keys.Add(line.iKey);
                comments.Add(line.comment);
            }
            bool isDef = useString ? isDefault(section, key, sValue) : isDefault(section, key, dValue);
            INIVariableDef vd = getVarDefn(section, key);
            string iSection = section.ToLower(Statics.Culture);
            string iKey = key.ToLower(Statics.Culture);
            int firstIndex = sections.IndexOf(iSection);
            int lastIndex = sections.LastIndexOf(iSection);
            int index = keys.IndexOf(iKey);
            INILine.setSection = section;
            INILine tmp = new INILine(key + "=");
            tmp.defVal = vd.defValue;
            tmp.varType = vd.type;
            tmp.varDict = vd.dict;
            tmp.varBool = vd.boolType;
            tmp.useMinMax = vd.useMinMax;
            tmp.min = vd.min;
            tmp.max = vd.max;
            if (useString) tmp.sValue = sValue;
            else {
                if (vd.precision != -1) dValue = double.Parse (dValue.ToString ("F" + vd.precision.ToString ()));
                tmp.dValue = dValue;
            }
            if (firstIndex == -1) {
                if (!saveDef && isDef) return;
                if (iniContent.Count > 0) {
                    INILine line = iniContent[iniContent.Count - 1];
                    if (line.entry != "" || line.comment != "") {
                        INILine.setSection = line.section;
                        iniContent.Add(new INILine(""));
                        firstIndex++;
                    }
                }
                INILine.setSection = section;
                iniContent.Add(new INILine("[" + section + "]"));
                iniContent.Add(tmp);
                iniContent.Add(new INILine(""));
            } else if (index >= firstIndex && index <= lastIndex) {
                if (!saveDef && isDef && comments[index] == "") iniContent.RemoveAt(index);
                else if (useString && iniContent[index].value == sValue || !useString && iniContent[index].dValue == dValue) return;
                else if (useString) iniContent[index].sValue = sValue;
                else iniContent[index].dValue = dValue;
            } else {
                if (!saveDef && isDef) return;
                INILine line = iniContent[lastIndex++];
                if (line.entry != "" || line.comment != "") {
                    iniContent.Insert(lastIndex, new INILine(""));
                    iniContent.Insert(lastIndex, tmp);
                } else iniContent.Insert(lastIndex - 1, tmp);
            }
            modified = true;
        }

        public void setSectOrderedList(string section, string[] tab) {
            List<string> sections = new List<string>();
            foreach (INILine line in iniContent) sections.Add(line.section);
            string iSection = section.ToLower(Statics.Culture);
            int firstIndex = sections.IndexOf(iSection);
            int lastIndex = sections.LastIndexOf(iSection);
            if (firstIndex == -1) {
                if (iniContent.Count > 0) {
                    INILine line = iniContent[iniContent.Count - 1];
                    if (line.entry != "" || line.comment != "") {
                        INILine.setSection = line.section;
                        iniContent.Add(new INILine(""));
                        firstIndex++;
                    }
                }
                INILine.setSection = section;
                firstIndex = lastIndex = iniContent.Count;
                iniContent.Add(new INILine("[" + section + "]"));
            }
            int tabIndex = 0;
            int tabCount = tab.Length - 1;
            while (++firstIndex <= lastIndex && tabIndex <= tabCount) {
                INILine line = iniContent[firstIndex];
                if (line.entry != "" && line.comment != "") {
                    line.entry = INIComment + line.entry;
                }
                else if (line.comment != "") continue;
                else {
                    line.entry = tab[tabIndex++];
                }
            }
            while (firstIndex <= lastIndex) iniContent.RemoveAt(lastIndex--);
            iniContent.Insert(firstIndex, new INILine(""));
            INILine.setSection = section;
            while (tabCount >= tabIndex) {
                iniContent.Insert(firstIndex, new INILine(tab[tabCount--]));
            }
            modified = true;
        }

        public void setSectList(string section, string[] tab) {
            List<string> sections = new List<string>();
            foreach (INILine line in iniContent) sections.Add(line.section);
            string iSection = section.ToLower(Statics.Culture);
            int firstIndex = sections.IndexOf(iSection);
            int lastIndex = sections.LastIndexOf(iSection);
            List<string> iTab = new List<string>();
            List<string> lTab = new List<string>();
            foreach (string tmpStr in tab) {
                iTab.Add(tmpStr.ToLower(Statics.Culture));
                lTab.Add(tmpStr);
            }
            if (firstIndex == -1) {
                if (iniContent.Count > 0) {
                    INILine line = iniContent[iniContent.Count - 1];
                    if (line.entry != "" || line.comment != "") {
                        INILine.setSection = line.section;
                        iniContent.Add(new INILine(""));
                        firstIndex++;
                    }
                }
                INILine.setSection = section;
                firstIndex = lastIndex = iniContent.Count;
                iniContent.Add(new INILine("[" + section + "]"));
            }
            for (int i = lastIndex; i > firstIndex; i--) {
                INILine line = iniContent[i];
                int index = iTab.IndexOf(line.iEntry);
                if (index != -1) {
                    iTab.RemoveAt(index);
                    lTab.RemoveAt(index);
                } else if (line.comment != "") {
                    line.entry = INIComment + line.entry;
                    modified = true;
                } else {
                    iniContent.RemoveAt(i);
                    lastIndex--;
                    modified = true;
                }
            }
            INILine.setSection = section;
            if (iniContent[lastIndex].entry != "" || iniContent[lastIndex].comment != "") iniContent.Insert(++lastIndex, new INILine(""));
            for (int i = lTab.Count - 1; i >= 0; i--) {
                iniContent.Insert(lastIndex, new INILine(lTab[i]));
                modified = true;
            }
        }

        public string[] getSectList(string section) {
            List<string> ret = new List<string>();
            List<string> sections = new List<string>();
            foreach (INILine line in iniContent) sections.Add(line.section);
            string iSection = section.ToLower(Statics.Culture);
            int firstIndex = sections.IndexOf(iSection);
            int lastIndex = sections.LastIndexOf(iSection);
            if (firstIndex != -1) while (++firstIndex <= lastIndex) {
                if (iniContent[firstIndex].entry != "") ret.Add(iniContent[firstIndex].entry);
            }
            return ret.ToArray();
        }

        public Dictionary<string, string> getSectionKeys (string section) {
            Dictionary<string, string> ret = new Dictionary<string, string> ();
            List<string> sections = new List<string> ();
            foreach (INILine line in iniContent) sections.Add (line.section);
            string iSection = section.ToLower (Statics.Culture);
            int firstIndex = sections.IndexOf (iSection);
            int lastIndex = sections.LastIndexOf (iSection);
            if (firstIndex != -1) while (++firstIndex <= lastIndex) {
                if (iniContent [firstIndex].key != "") ret.Add (iniContent [firstIndex].key, iniContent [firstIndex].qsValue);
            }
            return ret;
        }

    }

}