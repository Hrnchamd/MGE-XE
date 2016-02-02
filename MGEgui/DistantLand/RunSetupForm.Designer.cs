namespace MGEgui.DistantLand
{
    partial class RunSetupForm
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
            this.bRun = new System.Windows.Forms.Button();
            this.bSetup = new System.Windows.Forms.Button();
            this.cbTex = new System.Windows.Forms.CheckBox();
            this.cbMesh = new System.Windows.Forms.CheckBox();
            this.cbMeshAuto = new System.Windows.Forms.CheckBox();
            this.cbStat = new System.Windows.Forms.CheckBox();
            this.cbDebug = new System.Windows.Forms.CheckBox();
            this.bAutoSetup = new System.Windows.Forms.Button();
            this.gbSeparator1 = new System.Windows.Forms.GroupBox();
            this.lSetupAuto = new System.Windows.Forms.Label();
            this.lSetupUpdate = new System.Windows.Forms.Label();
            this.lSetupCustom = new System.Windows.Forms.Label();
            this.gbSeparator2 = new System.Windows.Forms.GroupBox();
            this.SuspendLayout();
            // 
            // bRun
            // 
            this.bRun.Location = new System.Drawing.Point(39, 214);
            this.bRun.Name = "bRun";
            this.bRun.Size = new System.Drawing.Size(268, 25);
            this.bRun.TabIndex = 0;
            this.bRun.Text = "Run above steps using saved / default settings";
            this.bRun.UseVisualStyleBackColor = true;
            this.bRun.Click += new System.EventHandler(this.bRun_Click);
            // 
            // bSetup
            // 
            this.bSetup.Location = new System.Drawing.Point(39, 286);
            this.bSetup.Name = "bSetup";
            this.bSetup.Size = new System.Drawing.Size(268, 25);
            this.bSetup.TabIndex = 1;
            this.bSetup.Text = "Distant Land configuration setup...";
            this.bSetup.UseVisualStyleBackColor = true;
            this.bSetup.Click += new System.EventHandler(this.bSetup_Click);
            // 
            // cbTex
            // 
            this.cbTex.AutoSize = true;
            this.cbTex.Checked = true;
            this.cbTex.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbTex.Location = new System.Drawing.Point(39, 122);
            this.cbTex.Name = "cbTex";
            this.cbTex.Size = new System.Drawing.Size(169, 19);
            this.cbTex.TabIndex = 2;
            this.cbTex.Text = "Create distant land textures";
            this.cbTex.UseVisualStyleBackColor = true;
            // 
            // cbMesh
            // 
            this.cbMesh.AutoSize = true;
            this.cbMesh.Checked = true;
            this.cbMesh.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbMesh.Location = new System.Drawing.Point(39, 145);
            this.cbMesh.Name = "cbMesh";
            this.cbMesh.Size = new System.Drawing.Size(168, 19);
            this.cbMesh.TabIndex = 3;
            this.cbMesh.Text = "Create distant land meshes";
            this.cbMesh.UseVisualStyleBackColor = true;
            this.cbMesh.CheckedChanged += new System.EventHandler(this.cbMesh_CheckedChanged);
            // 
            // cbMeshAuto
            // 
            this.cbMeshAuto.AutoSize = true;
            this.cbMeshAuto.Checked = true;
            this.cbMeshAuto.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbMeshAuto.Location = new System.Drawing.Point(58, 168);
            this.cbMeshAuto.Name = "cbMeshAuto";
            this.cbMeshAuto.Size = new System.Drawing.Size(233, 19);
            this.cbMeshAuto.TabIndex = 4;
            this.cbMeshAuto.Text = "Use auto-calculated world mesh details";
            this.cbMeshAuto.UseVisualStyleBackColor = true;
            // 
            // cbStat
            // 
            this.cbStat.AutoSize = true;
            this.cbStat.Checked = true;
            this.cbStat.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbStat.Location = new System.Drawing.Point(39, 191);
            this.cbStat.Name = "cbStat";
            this.cbStat.Size = new System.Drawing.Size(135, 19);
            this.cbStat.TabIndex = 5;
            this.cbStat.Text = "Create distant statics";
            this.cbStat.UseVisualStyleBackColor = true;
            // 
            // cbDebug
            // 
            this.cbDebug.AutoSize = true;
            this.cbDebug.ForeColor = System.Drawing.Color.Red;
            this.cbDebug.Location = new System.Drawing.Point(229, 95);
            this.cbDebug.Name = "cbDebug";
            this.cbDebug.Size = new System.Drawing.Size(63, 19);
            this.cbDebug.TabIndex = 7;
            this.cbDebug.Text = "DEBUG";
            this.cbDebug.UseVisualStyleBackColor = true;
            this.cbDebug.Visible = false;
            // 
            // bAutoSetup
            // 
            this.bAutoSetup.AutoSize = true;
            this.bAutoSetup.Location = new System.Drawing.Point(39, 43);
            this.bAutoSetup.Name = "bAutoSetup";
            this.bAutoSetup.Size = new System.Drawing.Size(268, 32);
            this.bAutoSetup.TabIndex = 8;
            this.bAutoSetup.Text = "Automatic setup everything";
            this.bAutoSetup.UseVisualStyleBackColor = true;
            this.bAutoSetup.Click += new System.EventHandler(this.bAutoSetup_click);
            // 
            // gbSeparator1
            // 
            this.gbSeparator1.Enabled = false;
            this.gbSeparator1.Location = new System.Drawing.Point(12, 86);
            this.gbSeparator1.Margin = new System.Windows.Forms.Padding(3, 8, 3, 8);
            this.gbSeparator1.Name = "gbSeparator1";
            this.gbSeparator1.Size = new System.Drawing.Size(320, 2);
            this.gbSeparator1.TabIndex = 9;
            this.gbSeparator1.TabStop = false;
            // 
            // lSetupAuto
            // 
            this.lSetupAuto.AutoSize = true;
            this.lSetupAuto.Location = new System.Drawing.Point(12, 17);
            this.lSetupAuto.Margin = new System.Windows.Forms.Padding(3, 0, 3, 8);
            this.lSetupAuto.Name = "lSetupAuto";
            this.lSetupAuto.Size = new System.Drawing.Size(95, 15);
            this.lSetupAuto.TabIndex = 10;
            this.lSetupAuto.Text = "Automatic setup";
            // 
            // lSetupUpdate
            // 
            this.lSetupUpdate.AutoSize = true;
            this.lSetupUpdate.Location = new System.Drawing.Point(12, 96);
            this.lSetupUpdate.Margin = new System.Windows.Forms.Padding(3, 0, 3, 8);
            this.lSetupUpdate.Name = "lSetupUpdate";
            this.lSetupUpdate.Size = new System.Drawing.Size(153, 15);
            this.lSetupUpdate.TabIndex = 11;
            this.lSetupUpdate.Text = "Update existing distant land";
            // 
            // lSetupCustom
            // 
            this.lSetupCustom.AutoSize = true;
            this.lSetupCustom.Location = new System.Drawing.Point(12, 260);
            this.lSetupCustom.Margin = new System.Windows.Forms.Padding(3, 0, 3, 8);
            this.lSetupCustom.Name = "lSetupCustom";
            this.lSetupCustom.Size = new System.Drawing.Size(95, 15);
            this.lSetupCustom.TabIndex = 12;
            this.lSetupCustom.Text = "Customize setup";
            // 
            // gbSeparator2
            // 
            this.gbSeparator2.Enabled = false;
            this.gbSeparator2.Location = new System.Drawing.Point(12, 250);
            this.gbSeparator2.Margin = new System.Windows.Forms.Padding(3, 8, 3, 8);
            this.gbSeparator2.Name = "gbSeparator2";
            this.gbSeparator2.Size = new System.Drawing.Size(320, 2);
            this.gbSeparator2.TabIndex = 10;
            this.gbSeparator2.TabStop = false;
            // 
            // RunSetupForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(344, 331);
            this.Controls.Add(this.gbSeparator2);
            this.Controls.Add(this.lSetupCustom);
            this.Controls.Add(this.lSetupUpdate);
            this.Controls.Add(this.lSetupAuto);
            this.Controls.Add(this.gbSeparator1);
            this.Controls.Add(this.bAutoSetup);
            this.Controls.Add(this.cbDebug);
            this.Controls.Add(this.cbStat);
            this.Controls.Add(this.cbMeshAuto);
            this.Controls.Add(this.cbMesh);
            this.Controls.Add(this.cbTex);
            this.Controls.Add(this.bSetup);
            this.Controls.Add(this.bRun);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.HelpButton = true;
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "RunSetupForm";
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Distant Land Generator";
            this.ResumeLayout(false);
            this.PerformLayout();
        }
        private System.Windows.Forms.GroupBox gbSeparator2;
        private System.Windows.Forms.Label lSetupCustom;
        private System.Windows.Forms.Label lSetupUpdate;
        private System.Windows.Forms.Label lSetupAuto;
        private System.Windows.Forms.GroupBox gbSeparator1;
        private System.Windows.Forms.Button bAutoSetup;

        #endregion

        private System.Windows.Forms.Button bRun;
        private System.Windows.Forms.Button bSetup;
        private System.Windows.Forms.CheckBox cbTex;
        private System.Windows.Forms.CheckBox cbMesh;
        private System.Windows.Forms.CheckBox cbMeshAuto;
        private System.Windows.Forms.CheckBox cbStat;
        private System.Windows.Forms.CheckBox cbDebug;
    }
}