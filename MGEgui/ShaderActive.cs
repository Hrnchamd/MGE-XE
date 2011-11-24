using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;
using MGEgui.INI;

namespace MGEgui {
    public class ShaderActive : Form {
        private Button bMoveUp;
        private ListBox lbSelected;
        private ListBox lbAvailable;
        private Button bMoveDown;
        private Button bSave;
        private Button bClear;
        private Button bCancel;

        public static string iniShaderChain = "Shader Chain";
        public static INIFile.INIVariableDef[] iniShaderWhat = {
            INIFile.iniDefEmpty
        };
        
        #region FormDesignerGunk
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
        	System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ShaderActive));
        	this.bMoveUp = new System.Windows.Forms.Button();
        	this.lbSelected = new System.Windows.Forms.ListBox();
        	this.lbAvailable = new System.Windows.Forms.ListBox();
        	this.bMoveDown = new System.Windows.Forms.Button();
        	this.bSave = new System.Windows.Forms.Button();
        	this.bClear = new System.Windows.Forms.Button();
        	this.bCancel = new System.Windows.Forms.Button();
        	this.lAvailableList = new System.Windows.Forms.Label();
        	this.lActiveList = new System.Windows.Forms.Label();
        	this.bEditor = new System.Windows.Forms.Button();
        	this.lShaderUsage = new System.Windows.Forms.Label();
        	this.SuspendLayout();
        	// 
        	// bMoveUp
        	// 
        	this.bMoveUp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bMoveUp.Location = new System.Drawing.Point(210, 281);
        	this.bMoveUp.Name = "bMoveUp";
        	this.bMoveUp.Size = new System.Drawing.Size(75, 23);
        	this.bMoveUp.TabIndex = 4;
        	this.bMoveUp.Text = "Move up";
        	this.bMoveUp.Click += new System.EventHandler(this.bMoveUp_Click);
        	// 
        	// lbSelected
        	// 
        	this.lbSelected.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.lbSelected.Location = new System.Drawing.Point(12, 271);
        	this.lbSelected.Name = "lbSelected";
        	this.lbSelected.Size = new System.Drawing.Size(187, 121);
        	this.lbSelected.TabIndex = 3;
        	this.lbSelected.DoubleClick += new System.EventHandler(this.lbSelected_DoubleClick);
        	// 
        	// lbAvailable
        	// 
        	this.lbAvailable.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
        	        	        	| System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.lbAvailable.Location = new System.Drawing.Point(12, 29);
        	this.lbAvailable.Name = "lbAvailable";
        	this.lbAvailable.Size = new System.Drawing.Size(187, 212);
        	this.lbAvailable.TabIndex = 2;
        	this.lbAvailable.DoubleClick += new System.EventHandler(this.lbAvailable_DoubleClick);
        	// 
        	// bMoveDown
        	// 
        	this.bMoveDown.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bMoveDown.Location = new System.Drawing.Point(210, 310);
        	this.bMoveDown.Name = "bMoveDown";
        	this.bMoveDown.Size = new System.Drawing.Size(75, 23);
        	this.bMoveDown.TabIndex = 5;
        	this.bMoveDown.Text = "Move down";
        	this.bMoveDown.Click += new System.EventHandler(this.bMoveDown_Click);
        	// 
        	// bSave
        	// 
        	this.bSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bSave.Location = new System.Drawing.Point(210, 32);
        	this.bSave.Name = "bSave";
        	this.bSave.Size = new System.Drawing.Size(75, 23);
        	this.bSave.TabIndex = 0;
        	this.bSave.Text = "Save";
        	this.bSave.Click += new System.EventHandler(this.bSave_Click);
        	// 
        	// bClear
        	// 
        	this.bClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
        	this.bClear.Location = new System.Drawing.Point(210, 359);
        	this.bClear.Name = "bClear";
        	this.bClear.Size = new System.Drawing.Size(75, 23);
        	this.bClear.TabIndex = 6;
        	this.bClear.Text = "Clear";
        	this.bClear.Click += new System.EventHandler(this.bClear_Click);
        	// 
        	// bCancel
        	// 
        	this.bCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
        	this.bCancel.Location = new System.Drawing.Point(210, 61);
        	this.bCancel.Name = "bCancel";
        	this.bCancel.Size = new System.Drawing.Size(75, 23);
        	this.bCancel.TabIndex = 1;
        	this.bCancel.Text = "Cancel";
        	this.bCancel.Click += new System.EventHandler(this.bCancel_Click);
        	// 
        	// lAvailableList
        	// 
        	this.lAvailableList.AutoSize = true;
        	this.lAvailableList.Location = new System.Drawing.Point(12, 12);
        	this.lAvailableList.Name = "lAvailableList";
        	this.lAvailableList.Size = new System.Drawing.Size(90, 13);
        	this.lAvailableList.TabIndex = 7;
        	this.lAvailableList.Text = "Available shaders";
        	// 
        	// lActiveList
        	// 
        	this.lActiveList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
        	        	        	| System.Windows.Forms.AnchorStyles.Right)));
        	this.lActiveList.AutoSize = true;
        	this.lActiveList.Location = new System.Drawing.Point(12, 254);
        	this.lActiveList.Name = "lActiveList";
        	this.lActiveList.Size = new System.Drawing.Size(79, 13);
        	this.lActiveList.TabIndex = 8;
        	this.lActiveList.Text = "Active Shaders";
        	// 
        	// bEditor
        	// 
        	this.bEditor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
        	this.bEditor.AutoSize = true;
        	this.bEditor.Location = new System.Drawing.Point(210, 118);
        	this.bEditor.Name = "bEditor";
        	this.bEditor.Size = new System.Drawing.Size(75, 23);
        	this.bEditor.TabIndex = 9;
        	this.bEditor.Text = "Editor";
        	this.bEditor.UseVisualStyleBackColor = true;
        	this.bEditor.Click += new System.EventHandler(this.bEditor_Click);
        	// 
        	// lShaderUsage
        	// 
        	this.lShaderUsage.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
        	this.lShaderUsage.Location = new System.Drawing.Point(7, 406);
        	this.lShaderUsage.Name = "lShaderUsage";
        	this.lShaderUsage.Size = new System.Drawing.Size(280, 94);
        	this.lShaderUsage.TabIndex = 10;
        	this.lShaderUsage.Text = resources.GetString("lShaderUsage.Text");
        	// 
        	// ShaderActive
        	// 
        	this.AcceptButton = this.bSave;
        	this.CancelButton = this.bCancel;
        	this.ClientSize = new System.Drawing.Size(296, 516);
        	this.Controls.Add(this.lShaderUsage);
        	this.Controls.Add(this.bEditor);
        	this.Controls.Add(this.lActiveList);
        	this.Controls.Add(this.lAvailableList);
        	this.Controls.Add(this.bCancel);
        	this.Controls.Add(this.bClear);
        	this.Controls.Add(this.bSave);
        	this.Controls.Add(this.bMoveDown);
        	this.Controls.Add(this.lbAvailable);
        	this.Controls.Add(this.lbSelected);
        	this.Controls.Add(this.bMoveUp);
        	this.Icon = global::MGEgui.Properties.Resources.AppIcon;
        	this.MinimumSize = new System.Drawing.Size(310, 310);
        	this.Name = "ShaderActive";
        	this.Text = "Set active shaders";
        	this.ResumeLayout(false);
        	this.PerformLayout();
        }
        private System.Windows.Forms.Label lShaderUsage;
        private System.Windows.Forms.Button bEditor;
        private System.Windows.Forms.Label lActiveList;
        private System.Windows.Forms.Label lAvailableList;

        #endregion
        #endregion
        
        public ShaderActive() {
            InitializeComponent();

            foreach (String s in Directory.GetFiles(Statics.runDir + "\\" + Statics.pathShaders)) {
                if(s.EndsWith(".fx")) lbAvailable.Items.Add(Path.GetFileNameWithoutExtension(s));
            }

            INIFile iniFile = new INIFile(Statics.iniFileName, iniShaderWhat, true);
            List<string> shaderList = new List<string>(iniFile.getSectList(iniShaderChain));
            foreach (string s in shaderList) {
				if (File.Exists(Statics.runDir + "\\" + Statics.pathShaders + "\\" + s + ".fx")) {
	                lbSelected.Items.Add(s);
            	}
            }
        }

        private void lbAvailable_DoubleClick(object sender,EventArgs e) {
            if(lbSelected.Items.Count>=32) return;
            if(lbAvailable.SelectedIndex==-1) return;

            DirectX.DXMain.CreateDevice(this);
            if (DirectX.Shaders.CompileShader(false, null, null, null, Statics.runDir + "\\" + Statics.pathShaders + "\\" + (string)lbAvailable.SelectedItem + ".fx") != null) {
                MessageBox.Show("That shader does not currently compile.");
            } else {
                lbSelected.Items.Add(string.Copy((string)lbAvailable.SelectedItem));
            }
            DirectX.DXMain.CloseDevice();
        }

        private void lbSelected_DoubleClick(object sender,EventArgs e) {
            if(lbSelected.SelectedIndex!=-1) lbSelected.Items.RemoveAt(lbSelected.SelectedIndex);
        }

        private void bCancel_Click(object sender,EventArgs e) {
            Close();
        }

        private void bSave_Click(object sender,EventArgs e) {
            INIFile iniFile = new INIFile(Statics.iniFileName, iniShaderWhat, true);
            List<string> tempList = new List<string>();
            foreach (string s in lbSelected.Items) tempList.Add(s);
            iniFile.setSectOrderedList(iniShaderChain, tempList.ToArray());
            iniFile.save();

            Close();
        }

        private void bMoveUp_Click(object sender,EventArgs e) {
            if(lbSelected.SelectedIndex>0) {
                string s=(string)lbSelected.Items[lbSelected.SelectedIndex];
                lbSelected.Items[lbSelected.SelectedIndex]=lbSelected.Items[lbSelected.SelectedIndex-1];
                lbSelected.Items[lbSelected.SelectedIndex-1]=s;
                lbSelected.SelectedIndex--;
            }
        }

        private void bMoveDown_Click(object sender,EventArgs e) {
            if(lbSelected.SelectedIndex!=-1&&lbSelected.SelectedIndex!=lbSelected.Items.Count-1) {
                string s=(string)lbSelected.Items[lbSelected.SelectedIndex];
                lbSelected.Items[lbSelected.SelectedIndex]=lbSelected.Items[lbSelected.SelectedIndex+1];
                lbSelected.Items[lbSelected.SelectedIndex+1]=s;
                lbSelected.SelectedIndex++;
            }
        }

        private void bClear_Click(object sender,EventArgs e) {
            lbSelected.Items.Clear();
        }

        private void bEditor_Click(object sender, EventArgs e)
        {
        	string shader = null;
            if(lbAvailable.SelectedIndex != -1)
				shader = Statics.runDir + "\\" + Statics.pathShaders + "\\" + (string)lbAvailable.SelectedItem + ".fx";

            ShaderEditorForm ed = new ShaderEditorForm(shader);
            ed.ShowDialog();
        }
    }
}
