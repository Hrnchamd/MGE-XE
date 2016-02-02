using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MGEgui {
    public class ShaderFlagsEd : Form {
#region form designer stuff
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.cbSFNotSunVis = new System.Windows.Forms.CheckBox();
            this.cbSFSunVis = new System.Windows.Forms.CheckBox();
            this.cbSFNotAboveWater = new System.Windows.Forms.CheckBox();
            this.cbSFNotUnderwater = new System.Windows.Forms.CheckBox();
            this.cbSFNotIntExt = new System.Windows.Forms.CheckBox();
            this.cbSFNotExt = new System.Windows.Forms.CheckBox();
            this.cbSFNotInt = new System.Windows.Forms.CheckBox();
            this.bOK = new System.Windows.Forms.Button();
            this.bCancel = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cbSFNotSunVis
            // 
            this.cbSFNotSunVis.AutoSize = true;
            this.cbSFNotSunVis.Dock = System.Windows.Forms.DockStyle.Top;
            this.cbSFNotSunVis.Location = new System.Drawing.Point(3, 153);
            this.cbSFNotSunVis.Name = "cbSFNotSunVis";
            this.cbSFNotSunVis.Size = new System.Drawing.Size(359, 19);
            this.cbSFNotSunVis.TabIndex = 13;
            this.cbSFNotSunVis.Text = "Disabled when sun is not visible (i.e. sun opacity is zero)";
            this.cbSFNotSunVis.UseVisualStyleBackColor = false;
            // 
            // cbSFSunVis
            // 
            this.cbSFSunVis.AutoSize = true;
            this.cbSFSunVis.Dock = System.Windows.Forms.DockStyle.Top;
            this.cbSFSunVis.Location = new System.Drawing.Point(3, 128);
            this.cbSFSunVis.Name = "cbSFSunVis";
            this.cbSFSunVis.Size = new System.Drawing.Size(359, 19);
            this.cbSFSunVis.TabIndex = 12;
            this.cbSFSunVis.Text = "Disabled when sun is visible";
            this.cbSFSunVis.UseVisualStyleBackColor = false;
            // 
            // cbSFNotAboveWater
            // 
            this.cbSFNotAboveWater.AutoSize = true;
            this.cbSFNotAboveWater.Dock = System.Windows.Forms.DockStyle.Top;
            this.cbSFNotAboveWater.Location = new System.Drawing.Point(3, 103);
            this.cbSFNotAboveWater.Name = "cbSFNotAboveWater";
            this.cbSFNotAboveWater.Size = new System.Drawing.Size(359, 19);
            this.cbSFNotAboveWater.TabIndex = 11;
            this.cbSFNotAboveWater.Text = "Disabled when above water";
            this.cbSFNotAboveWater.UseVisualStyleBackColor = false;
            // 
            // cbSFNotUnderwater
            // 
            this.cbSFNotUnderwater.AutoSize = true;
            this.cbSFNotUnderwater.Dock = System.Windows.Forms.DockStyle.Top;
            this.cbSFNotUnderwater.Location = new System.Drawing.Point(3, 78);
            this.cbSFNotUnderwater.Name = "cbSFNotUnderwater";
            this.cbSFNotUnderwater.Size = new System.Drawing.Size(359, 19);
            this.cbSFNotUnderwater.TabIndex = 10;
            this.cbSFNotUnderwater.Text = "Disabled when underwater";
            this.cbSFNotUnderwater.UseVisualStyleBackColor = false;
            // 
            // cbSFNotIntExt
            // 
            this.cbSFNotIntExt.AutoSize = true;
            this.cbSFNotIntExt.Dock = System.Windows.Forms.DockStyle.Top;
            this.cbSFNotIntExt.Location = new System.Drawing.Point(3, 53);
            this.cbSFNotIntExt.Name = "cbSFNotIntExt";
            this.cbSFNotIntExt.Size = new System.Drawing.Size(359, 19);
            this.cbSFNotIntExt.TabIndex = 9;
            this.cbSFNotIntExt.Text = "Disabled in interiors acting like exteriors (like Mournhold)";
            this.cbSFNotIntExt.UseVisualStyleBackColor = false;
            // 
            // cbSFNotExt
            // 
            this.cbSFNotExt.AutoSize = true;
            this.cbSFNotExt.Dock = System.Windows.Forms.DockStyle.Top;
            this.cbSFNotExt.Location = new System.Drawing.Point(3, 28);
            this.cbSFNotExt.Name = "cbSFNotExt";
            this.cbSFNotExt.Size = new System.Drawing.Size(359, 19);
            this.cbSFNotExt.TabIndex = 8;
            this.cbSFNotExt.Text = "Disabled in exteriors";
            this.cbSFNotExt.UseVisualStyleBackColor = false;
            // 
            // cbSFNotInt
            // 
            this.cbSFNotInt.AutoSize = true;
            this.cbSFNotInt.Dock = System.Windows.Forms.DockStyle.Top;
            this.cbSFNotInt.Location = new System.Drawing.Point(3, 3);
            this.cbSFNotInt.Name = "cbSFNotInt";
            this.cbSFNotInt.Size = new System.Drawing.Size(359, 19);
            this.cbSFNotInt.TabIndex = 7;
            this.cbSFNotInt.Text = "Disabled in interiors";
            this.cbSFNotInt.UseVisualStyleBackColor = false;
            // 
            // bOK
            // 
            this.bOK.Location = new System.Drawing.Point(221, 216);
            this.bOK.Name = "bOK";
            this.bOK.Size = new System.Drawing.Size(75, 23);
            this.bOK.TabIndex = 0;
            this.bOK.Text = "OK";
            this.bOK.UseVisualStyleBackColor = true;
            this.bOK.Click += new System.EventHandler(this.bClose_Click);
            // 
            // bCancel
            // 
            this.bCancel.Location = new System.Drawing.Point(302, 216);
            this.bCancel.Name = "bCancel";
            this.bCancel.Size = new System.Drawing.Size(75, 23);
            this.bCancel.TabIndex = 1;
            this.bCancel.Text = "Cancel";
            this.bCancel.UseVisualStyleBackColor = true;
            this.bCancel.Click += new System.EventHandler(this.bCancel_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.cbSFNotInt, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.cbSFNotExt, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.cbSFNotIntExt, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.cbSFNotSunVis, 0, 6);
            this.tableLayoutPanel1.Controls.Add(this.cbSFNotUnderwater, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.cbSFSunVis, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.cbSFNotAboveWater, 0, 4);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 12);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 7;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(365, 188);
            this.tableLayoutPanel1.TabIndex = 14;
            // 
            // ShaderFlagsEd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(389, 251);
            this.ControlBox = false;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.bCancel);
            this.Controls.Add(this.bOK);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MaximumSize = new System.Drawing.Size(395, 280);
            this.MinimumSize = new System.Drawing.Size(395, 280);
            this.Name = "ShaderFlagsEd";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Shader flags";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
        }
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;

        #endregion

        private System.Windows.Forms.CheckBox cbSFNotSunVis;
        private System.Windows.Forms.CheckBox cbSFSunVis;
        private System.Windows.Forms.CheckBox cbSFNotAboveWater;
        private System.Windows.Forms.CheckBox cbSFNotUnderwater;
        private System.Windows.Forms.CheckBox cbSFNotIntExt;
        private System.Windows.Forms.CheckBox cbSFNotExt;
        private System.Windows.Forms.CheckBox cbSFNotInt;
        private System.Windows.Forms.Button bOK;

#endregion

        private ShaderEditorForm _parent;
        private Button bCancel;
    
        public ShaderEditorForm parent{get{return _parent;} set {_parent = value;}}
        private int flags;

        public ShaderFlagsEd() {
            InitializeComponent();
            Statics.Localizations.Apply(this);
        }

        public void setCheckboxes(UInt32 flags){
            cbSFNotInt.Checked          = ((flags &  1) ==  1);
            cbSFNotExt.Checked          = ((flags &  2) ==  2);
            cbSFNotIntExt.Checked       = ((flags &  4) ==  4);
            cbSFNotUnderwater.Checked   = ((flags &  8) ==  8);
            cbSFNotAboveWater.Checked   = ((flags & 16) == 16);
            cbSFSunVis.Checked          = ((flags & 32) == 32);
            cbSFNotSunVis.Checked       = ((flags & 64) == 64);
        }

        public int getFlags() {
            return flags;
        }

        private void bClose_Click(object sender, EventArgs e) {
            flags = 0;
            if (cbSFNotInt.Checked) flags += 1;
            if (cbSFNotExt.Checked) flags += 2;
            if (cbSFNotIntExt.Checked) flags += 4;
            if (cbSFNotUnderwater.Checked) flags += 8;
            if (cbSFNotAboveWater.Checked) flags += 16;
            if (cbSFSunVis.Checked) flags += 32;
            if (cbSFNotSunVis.Checked) flags += 64;

            if (parent != null) parent.updateShaderFlags(flags);

            this.Close();
        }

        private void bCancel_Click(object sender, EventArgs e) {
            this.Close();
        }

    }
}
