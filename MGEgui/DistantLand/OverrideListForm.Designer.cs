namespace MGEgui.DistantLand
{
    partial class OverrideListForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
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
            this.lbOverrideList = new System.Windows.Forms.ListBox();
            this.bClear = new System.Windows.Forms.Button();
            this.bAdd = new System.Windows.Forms.Button();
            this.bRemove = new System.Windows.Forms.Button();
            this.bUp = new System.Windows.Forms.Button();
            this.bDown = new System.Windows.Forms.Button();
            this.bCancel = new System.Windows.Forms.Button();
            this.bSave = new System.Windows.Forms.Button();
            this.openStaticListDialog = new System.Windows.Forms.OpenFileDialog();
            this.panelDPIScalingLimiter = new System.Windows.Forms.Panel();
            this.panelDPIScalingLimiter.SuspendLayout();
            this.SuspendLayout();
            // 
            // lbOverrideList
            // 
            this.lbOverrideList.DisplayMember = "FileName";
            this.lbOverrideList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lbOverrideList.FormattingEnabled = true;
            this.lbOverrideList.HorizontalScrollbar = true;
            this.lbOverrideList.IntegralHeight = false;
            this.lbOverrideList.ItemHeight = 15;
            this.lbOverrideList.Location = new System.Drawing.Point(0, 0);
            this.lbOverrideList.Margin = new System.Windows.Forms.Padding(0);
            this.lbOverrideList.Name = "lbOverrideList";
            this.lbOverrideList.Size = new System.Drawing.Size(435, 212);
            this.lbOverrideList.TabIndex = 0;
            // 
            // bClear
            // 
            this.bClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bClear.AutoSize = true;
            this.bClear.Location = new System.Drawing.Point(453, 12);
            this.bClear.Name = "bClear";
            this.bClear.Size = new System.Drawing.Size(119, 25);
            this.bClear.TabIndex = 1;
            this.bClear.Text = "Clear";
            this.bClear.UseVisualStyleBackColor = true;
            this.bClear.Click += new System.EventHandler(this.bClear_Click);
            // 
            // bAdd
            // 
            this.bAdd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bAdd.AutoSize = true;
            this.bAdd.Location = new System.Drawing.Point(453, 43);
            this.bAdd.Name = "bAdd";
            this.bAdd.Size = new System.Drawing.Size(119, 25);
            this.bAdd.TabIndex = 2;
            this.bAdd.Text = "Add";
            this.bAdd.UseVisualStyleBackColor = true;
            this.bAdd.Click += new System.EventHandler(this.bAdd_Click);
            // 
            // bRemove
            // 
            this.bRemove.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bRemove.AutoSize = true;
            this.bRemove.Location = new System.Drawing.Point(453, 74);
            this.bRemove.Name = "bRemove";
            this.bRemove.Size = new System.Drawing.Size(119, 25);
            this.bRemove.TabIndex = 3;
            this.bRemove.Text = "Remove";
            this.bRemove.UseVisualStyleBackColor = true;
            this.bRemove.Click += new System.EventHandler(this.bRemove_Click);
            // 
            // bUp
            // 
            this.bUp.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bUp.AutoSize = true;
            this.bUp.Location = new System.Drawing.Point(453, 105);
            this.bUp.MaximumSize = new System.Drawing.Size(56, 0);
            this.bUp.Name = "bUp";
            this.bUp.Size = new System.Drawing.Size(56, 40);
            this.bUp.TabIndex = 4;
            this.bUp.Text = "Move\r\nUp";
            this.bUp.UseVisualStyleBackColor = true;
            this.bUp.Click += new System.EventHandler(this.bUp_Click);
            // 
            // bDown
            // 
            this.bDown.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bDown.AutoSize = true;
            this.bDown.Location = new System.Drawing.Point(516, 105);
            this.bDown.MaximumSize = new System.Drawing.Size(56, 0);
            this.bDown.Name = "bDown";
            this.bDown.Size = new System.Drawing.Size(56, 40);
            this.bDown.TabIndex = 5;
            this.bDown.Text = "Move\r\nDown";
            this.bDown.UseVisualStyleBackColor = true;
            this.bDown.Click += new System.EventHandler(this.bDown_Click);
            // 
            // bCancel
            // 
            this.bCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bCancel.AutoSize = true;
            this.bCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.bCancel.Location = new System.Drawing.Point(453, 168);
            this.bCancel.Name = "bCancel";
            this.bCancel.Size = new System.Drawing.Size(119, 25);
            this.bCancel.TabIndex = 6;
            this.bCancel.Text = "Cancel";
            this.bCancel.UseVisualStyleBackColor = true;
            // 
            // bSave
            // 
            this.bSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bSave.AutoSize = true;
            this.bSave.Location = new System.Drawing.Point(453, 199);
            this.bSave.Name = "bSave";
            this.bSave.Size = new System.Drawing.Size(119, 25);
            this.bSave.TabIndex = 7;
            this.bSave.Text = "Save";
            this.bSave.UseVisualStyleBackColor = true;
            this.bSave.Click += new System.EventHandler(this.bSave_Click);
            // 
            // openStaticListDialog
            // 
            this.openStaticListDialog.DefaultExt = "ovr";
            this.openStaticListDialog.Filter = "Static overrides (*.ovr)|*.ovr|Text files (*.txt)|*.txt|All files|*.*";
            this.openStaticListDialog.Multiselect = true;
            this.openStaticListDialog.RestoreDirectory = true;
            // 
            // panelDPIScalingLimiter
            // 
            this.panelDPIScalingLimiter.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                                    | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.panelDPIScalingLimiter.Controls.Add(this.lbOverrideList);
            this.panelDPIScalingLimiter.Location = new System.Drawing.Point(12, 12);
            this.panelDPIScalingLimiter.Name = "panelDPIScalingLimiter";
            this.panelDPIScalingLimiter.Size = new System.Drawing.Size(435, 212);
            this.panelDPIScalingLimiter.TabIndex = 8;
            // 
            // OverrideListForm
            // 
            this.AcceptButton = this.bSave;
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.CancelButton = this.bCancel;
            this.ClientSize = new System.Drawing.Size(584, 236);
            this.Controls.Add(this.panelDPIScalingLimiter);
            this.Controls.Add(this.bClear);
            this.Controls.Add(this.bAdd);
            this.Controls.Add(this.bRemove);
            this.Controls.Add(this.bUp);
            this.Controls.Add(this.bDown);
            this.Controls.Add(this.bCancel);
            this.Controls.Add(this.bSave);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MinimumSize = new System.Drawing.Size(480, 275);
            this.Name = "OverrideListForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Selected Static Override Lists";
            this.panelDPIScalingLimiter.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();
        }
        private System.Windows.Forms.Panel panelDPIScalingLimiter;

        #endregion

        private System.Windows.Forms.ListBox lbOverrideList;
        private System.Windows.Forms.Button bClear;
        private System.Windows.Forms.Button bAdd;
        private System.Windows.Forms.Button bRemove;
        private System.Windows.Forms.Button bUp;
        private System.Windows.Forms.Button bDown;
        private System.Windows.Forms.Button bCancel;
        private System.Windows.Forms.Button bSave;
        public System.Windows.Forms.OpenFileDialog openStaticListDialog;

    }
}
