﻿namespace MGEgui.DistantLand
{
    partial class DirectoriesForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.bClear = new System.Windows.Forms.Button();
            this.bAdd = new System.Windows.Forms.Button();
            this.bRemove = new System.Windows.Forms.Button();
            this.bCancel = new System.Windows.Forms.Button();
            this.bSave = new System.Windows.Forms.Button();
            this.lbDirectories = new System.Windows.Forms.ListBox();
            this.lDirectories = new System.Windows.Forms.Label();
            this.folderAdd = new System.Windows.Forms.FolderBrowserDialog();
            this.panelDPIScalingLimiter = new System.Windows.Forms.Panel();
            this.panelDPIScalingLimiter.SuspendLayout();
            this.SuspendLayout();
            // 
            // bClear
            // 
            this.bClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bClear.Location = new System.Drawing.Point(416, 25);
            this.bClear.Name = "bClear";
            this.bClear.Size = new System.Drawing.Size(118, 25);
            this.bClear.TabIndex = 0;
            this.bClear.Text = "Clear";
            this.bClear.UseVisualStyleBackColor = true;
            this.bClear.Click += new System.EventHandler(this.bClear_Click);
            // 
            // bAdd
            // 
            this.bAdd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bAdd.Location = new System.Drawing.Point(416, 54);
            this.bAdd.Name = "bAdd";
            this.bAdd.Size = new System.Drawing.Size(118, 25);
            this.bAdd.TabIndex = 1;
            this.bAdd.Text = "Add";
            this.bAdd.UseVisualStyleBackColor = true;
            this.bAdd.Click += new System.EventHandler(this.bAdd_Click);
            // 
            // bRemove
            // 
            this.bRemove.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bRemove.Location = new System.Drawing.Point(416, 85);
            this.bRemove.Name = "bRemove";
            this.bRemove.Size = new System.Drawing.Size(118, 25);
            this.bRemove.TabIndex = 2;
            this.bRemove.Text = "Remove";
            this.bRemove.UseVisualStyleBackColor = true;
            this.bRemove.Click += new System.EventHandler(this.bRemove_Click);
            // 
            // bCancel
            // 
            this.bCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.bCancel.Location = new System.Drawing.Point(416, 143);
            this.bCancel.Name = "bCancel";
            this.bCancel.Size = new System.Drawing.Size(118, 25);
            this.bCancel.TabIndex = 3;
            this.bCancel.Text = "Cancel";
            this.bCancel.UseVisualStyleBackColor = true;
            // 
            // bSave
            // 
            this.bSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bSave.Location = new System.Drawing.Point(416, 174);
            this.bSave.Name = "bSave";
            this.bSave.Size = new System.Drawing.Size(118, 25);
            this.bSave.TabIndex = 4;
            this.bSave.Text = "Save";
            this.bSave.UseVisualStyleBackColor = true;
            this.bSave.Click += new System.EventHandler(this.bSave_Click);
            // 
            // lbDirectories
            // 
            this.lbDirectories.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lbDirectories.FormattingEnabled = true;
            this.lbDirectories.HorizontalScrollbar = true;
            this.lbDirectories.IntegralHeight = false;
            this.lbDirectories.ItemHeight = 15;
            this.lbDirectories.Location = new System.Drawing.Point(0, 0);
            this.lbDirectories.Margin = new System.Windows.Forms.Padding(0);
            this.lbDirectories.Name = "lbDirectories";
            this.lbDirectories.Size = new System.Drawing.Size(398, 174);
            this.lbDirectories.Sorted = true;
            this.lbDirectories.TabIndex = 5;
            // 
            // lDirectories
            // 
            this.lDirectories.AutoSize = true;
            this.lDirectories.Location = new System.Drawing.Point(9, 5);
            this.lDirectories.Name = "lDirectories";
            this.lDirectories.Size = new System.Drawing.Size(291, 15);
            this.lDirectories.TabIndex = 0;
            this.lDirectories.Text = "Additional directories that will be scanned for plugins:";
            // 
            // folderAdd
            // 
            this.folderAdd.Description = "Choose folder to be added to list of additional directories scanned for plugins:";
            this.folderAdd.RootFolder = System.Environment.SpecialFolder.MyComputer;
            this.folderAdd.ShowNewFolderButton = false;
            // 
            // panelDPIScalingLimiter
            // 
            this.panelDPIScalingLimiter.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                                    | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.panelDPIScalingLimiter.Controls.Add(this.lbDirectories);
            this.panelDPIScalingLimiter.Location = new System.Drawing.Point(12, 25);
            this.panelDPIScalingLimiter.Name = "panelDPIScalingLimiter";
            this.panelDPIScalingLimiter.Size = new System.Drawing.Size(398, 174);
            this.panelDPIScalingLimiter.TabIndex = 6;
            // 
            // DirectoriesForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.CancelButton = this.bCancel;
            this.ClientSize = new System.Drawing.Size(541, 211);
            this.Controls.Add(this.panelDPIScalingLimiter);
            this.Controls.Add(this.lDirectories);
            this.Controls.Add(this.bSave);
            this.Controls.Add(this.bCancel);
            this.Controls.Add(this.bRemove);
            this.Controls.Add(this.bAdd);
            this.Controls.Add(this.bClear);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MinimumSize = new System.Drawing.Size(540, 250);
            this.Name = "DirectoriesForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Plugin Directories";
            this.panelDPIScalingLimiter.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();
        }
        private System.Windows.Forms.Panel panelDPIScalingLimiter;

        #endregion

        private System.Windows.Forms.Button bClear;
        private System.Windows.Forms.Button bAdd;
        private System.Windows.Forms.Button bRemove;
        private System.Windows.Forms.Button bCancel;
        private System.Windows.Forms.Button bSave;
        private System.Windows.Forms.ListBox lbDirectories;
        private System.Windows.Forms.Label lDirectories;
        public System.Windows.Forms.FolderBrowserDialog folderAdd;
    }
}