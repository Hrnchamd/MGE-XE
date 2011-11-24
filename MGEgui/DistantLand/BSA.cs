//TODO: When reading in the BSAs, ignore anything that isn't a texture
using System;
using System.Collections.Generic;
using System.IO;

namespace MGEgui.DistantLand {
    struct BSAEntry : IComparable<BSAEntry> {
        public readonly BinaryReader bsafile;
        public readonly string entryname;
        public readonly int offset;
        public readonly int size;

        public int CompareTo(BSAEntry entry) { return string.Compare(entryname, entry.entryname); }

        public BSAEntry(BinaryReader file, string ename, int _offset, int _size) {
            bsafile=file;
            entryname=ename.ToLower();
            offset=_offset;
            size=_size;
        }

        public static bool operator==(BSAEntry a, BSAEntry b) {
            return a.entryname==b.entryname;
        }
        public static bool operator==(BSAEntry a, string b) {
            return a.entryname==b.ToLower();
        }
        public static bool operator!=(BSAEntry a, BSAEntry b) {
            return a.entryname!=b.entryname;
        }
        public static bool operator!=(BSAEntry a, string b) {
            return a.entryname!=b.ToLower(); ;
        }
        public override bool Equals(object obj) {
            if(obj is string) return this==(string)obj;
            if(obj is BSAEntry) return this==(BSAEntry)obj;
            return false;
        }
        public override int GetHashCode() {
            return entryname.GetHashCode();
        }
    }

    static class BSA {
        //Should be a hash dictionary. Sorted anyway, so little difference
        private static readonly List<BSAEntry> entries=new List<BSAEntry>(16384);
        private static readonly List<BinaryReader> files=new List<BinaryReader>();

        public static void InitBSAs() {
            if(entries.Count>0) return; //Already been init-ed
            string[] bsas=Directory.GetFiles("data files", "*.bsa");
            foreach(string s in bsas) {
                BinaryReader br=new BinaryReader(File.OpenRead(s));
                br.BaseStream.Position+=4;
                int hashoffset=br.ReadInt32();
                int numfiles=br.ReadInt32();
                for(int i=0;i<numfiles;i++) {
                    br.BaseStream.Position=12+i*8;
                    int size=br.ReadInt32();
                    int offset=br.ReadInt32()+12+hashoffset+numfiles*8;
                    br.BaseStream.Position=12+numfiles*8+i*4;
                    br.BaseStream.Position=br.ReadInt32()+12+numfiles*12;
                    string name="";
                    while(true) {
                        byte b=br.ReadByte();
                        if(b==0) break;
                        name+=(char)b;
                    }
                    entries.Add(new BSAEntry(br, "data files\\"+name, offset, size));
                }
                files.Add(br);
            }
            entries.Sort();
        }

        public static byte[] GetTexture(string name) {
            name=name.ToLower();

            int index;
            if(Path.IsPathRooted(name)) {
                throw new ArgumentException("Something tried to load a texture using an absolute path.");
            } else name="data files\\textures\\"+name.ToLower();
            if(File.Exists(Path.ChangeExtension(name, ".dds"))) {
                return File.ReadAllBytes(Path.ChangeExtension(name, ".dds"));
            } else if(File.Exists(name)) {
                return File.ReadAllBytes(name);
            } else {
                if(Path.GetExtension(name) != ".dds") {
                    index = entries.BinarySearch(new BSAEntry(null, Path.ChangeExtension(name, ".dds"), 0, 0));
                    if(index < 0) index = entries.BinarySearch(new BSAEntry(null, name, 0, 0));
                } else index = entries.BinarySearch(new BSAEntry(null, name, 0, 0));
                if(index < 0) throw new ArgumentException("No entry matching specified filename was found");
                entries[index].bsafile.BaseStream.Position = entries[index].offset;
                byte[] result = entries[index].bsafile.ReadBytes(entries[index].size);
                return result;
            }
        }

        public static byte[] GetNif(string name) {
            name=name.ToLower();
            if(Path.IsPathRooted(name)) {
                throw new ArgumentException("Something tried to load a nif using an absolute path.");
            }

            string path=Path.Combine(@"data files\mge meshes\distantland\", name);
            if(File.Exists(path)) return File.ReadAllBytes(path);
            path=Path.Combine(@"data files\meshes\", name);
            if(File.Exists(path)) return File.ReadAllBytes(path);

            int index = entries.BinarySearch(new BSAEntry(null, path, 0, 0));
            if(index < 0) throw new ArgumentException("No nif matching the specified filename was found");
            entries[index].bsafile.BaseStream.Position = entries[index].offset;
            byte[] data = entries[index].bsafile.ReadBytes(entries[index].size);
            return data;
        }

        public static void CloseFiles() {
            foreach(BinaryReader br in files) br.Close();
            files.Clear();
            entries.Clear();
        }
    }
}
