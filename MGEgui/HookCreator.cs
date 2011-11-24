using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

namespace MGEgui {
    public class HookCreator : Form {
        #region FormDesignerGunk
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
            this.SaveHookDialog = new System.Windows.Forms.SaveFileDialog();
            this.cbEffect = new System.Windows.Forms.CheckBox();
            this.tbTex = new System.Windows.Forms.TextBox();
            this.lTexPath = new System.Windows.Forms.Label();
            this.tbEffect = new System.Windows.Forms.TextBox();
            this.lEffPath = new System.Windows.Forms.Label();
            this.bCancel = new System.Windows.Forms.Button();
            this.bSave = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // SaveHookDialog
            // 
            this.SaveHookDialog.DefaultExt = "dds";
            this.SaveHookDialog.Filter = "texture files (dds, tga, bmp)|*.dds;*.tga;*.bmp";
            this.SaveHookDialog.RestoreDirectory = true;
            this.SaveHookDialog.Title = "Save file as";
            // 
            // cbEffect
            // 
            this.cbEffect.Location = new System.Drawing.Point(12, 38);
            this.cbEffect.Name = "cbEffect";
            this.cbEffect.Size = new System.Drawing.Size(146, 24);
            this.cbEffect.TabIndex = 1;
            this.cbEffect.Text = "Attach shader";
            this.cbEffect.CheckedChanged += new System.EventHandler(this.cbEffect_CheckedChanged);
            // 
            // tbTex
            // 
            this.tbTex.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tbTex.Location = new System.Drawing.Point(12, 12);
            this.tbTex.Name = "tbTex";
            this.tbTex.Size = new System.Drawing.Size(155, 22);
            this.tbTex.TabIndex = 0;
            // 
            // lTexPath
            // 
            this.lTexPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lTexPath.AutoSize = true;
            this.lTexPath.Location = new System.Drawing.Point(173, 15);
            this.lTexPath.Name = "lTexPath";
            this.lTexPath.Size = new System.Drawing.Size(71, 13);
            this.lTexPath.TabIndex = 0;
            this.lTexPath.Text = "Texture path";
            // 
            // tbEffect
            // 
            this.tbEffect.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tbEffect.Enabled = false;
            this.tbEffect.Location = new System.Drawing.Point(12, 68);
            this.tbEffect.Name = "tbEffect";
            this.tbEffect.Size = new System.Drawing.Size(155, 22);
            this.tbEffect.TabIndex = 2;
            // 
            // lEffPath
            // 
            this.lEffPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lEffPath.AutoSize = true;
            this.lEffPath.Location = new System.Drawing.Point(173, 71);
            this.lEffPath.Name = "lEffPath";
            this.lEffPath.Size = new System.Drawing.Size(63, 13);
            this.lEffPath.TabIndex = 0;
            this.lEffPath.Text = "Effect path";
            // 
            // bCancel
            // 
            this.bCancel.Location = new System.Drawing.Point(12, 106);
            this.bCancel.Name = "bCancel";
            this.bCancel.Size = new System.Drawing.Size(75, 23);
            this.bCancel.TabIndex = 3;
            this.bCancel.Text = "Cancel";
            this.bCancel.Click += new System.EventHandler(this.bCancel_Click);
            // 
            // bSave
            // 
            this.bSave.Location = new System.Drawing.Point(165, 106);
            this.bSave.Name = "bSave";
            this.bSave.Size = new System.Drawing.Size(75, 23);
            this.bSave.TabIndex = 4;
            this.bSave.Text = "Save";
            this.bSave.Click += new System.EventHandler(this.bSave_Click);
            // 
            // HookCreator
            // 
            this.ClientSize = new System.Drawing.Size(252, 141);
            this.Controls.Add(this.bSave);
            this.Controls.Add(this.bCancel);
            this.Controls.Add(this.lEffPath);
            this.Controls.Add(this.tbEffect);
            this.Controls.Add(this.lTexPath);
            this.Controls.Add(this.tbTex);
            this.Controls.Add(this.cbEffect);
            this.Name = "HookCreator";
            this.Text = "HookCreator";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private SaveFileDialog SaveHookDialog;
        private CheckBox cbEffect;
        private TextBox tbTex;
        private Label lTexPath;
        private TextBox tbEffect;
        private Label lEffPath;
        private Button bCancel;
        private Button bSave;
        #endregion
        public HookCreator() {
            InitializeComponent();
        }

        private void bCancel_Click(object sender, EventArgs e) {
            Close();
        }

        private static bool IsSafeString(string str) {
            str=str.ToLower();
            int pointer=0;
            char c;
            if(str[0]=='.'||str[0]=='\\') return false;
            bool LastWasDot=true;
            while((c=str[pointer++])!='\0') {
                if(!((c>='a'&&c<='z')||(c>='0'||c<='9')||c=='.'||c=='_'||c=='\\'||c==' '||c=='#')) return false;
                if(c=='.') {
                    if(LastWasDot) return false;
                    else LastWasDot=true;
                } else LastWasDot=false;
            }
            if(pointer>64) return false;
            else return true;
        }

        private void bSave_Click(object sender, EventArgs e) {
            if(tbTex.Text=="") {
                MessageBox.Show("You must enter a valid texture filename");
                return;
            }
            if(!IsSafeString(tbTex.Text+'\0')) {
                MessageBox.Show("Your texture filename is not valid");
                return;
            }
            if(cbEffect.Checked) {
                if(tbEffect.Text==""||!IsSafeString(tbEffect.Text+'\0')) {
                    MessageBox.Show("Your shader filename is not valid");
                    return;
                }
            }
            if(SaveHookDialog.ShowDialog()==DialogResult.OK) {
                BinaryWriter bw=new BinaryWriter(File.Open(SaveHookDialog.FileName, FileMode.Create));
                bw.Write((byte)'M');
                bw.Write((byte)'G');
                bw.Write((byte)'E');
                for(int i=0;i<tbTex.Text.Length;i++) bw.Write((byte)tbTex.Text[i]);
                bw.Write((byte)0);
                if(cbEffect.Checked) {
                    for(int i=0;i<tbEffect.Text.Length;i++) bw.Write((byte)tbEffect.Text[i]);
                }
                bw.Write((byte)0);
                bw.Close();
                MessageBox.Show("File saved");
                Close();
            }
        }

        private void cbEffect_CheckedChanged(object sender, EventArgs e) {
            tbEffect.Enabled=cbEffect.Checked;
        }
    }
}
