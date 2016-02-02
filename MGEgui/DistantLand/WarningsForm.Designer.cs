namespace MGEgui.DistantLand
{
    partial class WarningsForm
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
            this.dgvWarnings = new System.Windows.Forms.DataGridView();
            this.warnId = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.warnText = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.bClose = new System.Windows.Forms.Button();
            this.lTotal = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dgvWarnings)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvWarnings
            // 
            this.dgvWarnings.AllowUserToAddRows = false;
            this.dgvWarnings.AllowUserToDeleteRows = false;
            this.dgvWarnings.AllowUserToOrderColumns = true;
            this.dgvWarnings.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                                    | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.dgvWarnings.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dgvWarnings.BackgroundColor = System.Drawing.SystemColors.Window;
            this.dgvWarnings.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dgvWarnings.ColumnHeadersHeight = 24;
            this.dgvWarnings.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            this.dgvWarnings.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
                                    this.warnId,
                                    this.warnText});
            this.dgvWarnings.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.dgvWarnings.Location = new System.Drawing.Point(0, 0);
            this.dgvWarnings.Name = "dgvWarnings";
            this.dgvWarnings.ReadOnly = true;
            this.dgvWarnings.RowHeadersVisible = false;
            this.dgvWarnings.RowHeadersWidth = 5;
            this.dgvWarnings.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dgvWarnings.RowTemplate.Height = 18;
            this.dgvWarnings.RowTemplate.ReadOnly = true;
            this.dgvWarnings.Size = new System.Drawing.Size(692, 344);
            this.dgvWarnings.TabIndex = 0;
            // 
            // warnId
            // 
            this.warnId.Frozen = true;
            this.warnId.HeaderText = "No.";
            this.warnId.Name = "warnId";
            this.warnId.ReadOnly = true;
            this.warnId.Width = 32;
            // 
            // warnText
            // 
            this.warnText.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.warnText.HeaderText = "Description";
            this.warnText.Name = "warnText";
            this.warnText.ReadOnly = true;
            // 
            // bClose
            // 
            this.bClose.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bClose.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.bClose.Location = new System.Drawing.Point(605, 350);
            this.bClose.Name = "bClose";
            this.bClose.Size = new System.Drawing.Size(75, 23);
            this.bClose.TabIndex = 1;
            this.bClose.Text = "Close";
            this.bClose.UseVisualStyleBackColor = true;
            // 
            // lTotal
            // 
            this.lTotal.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lTotal.AutoSize = true;
            this.lTotal.Location = new System.Drawing.Point(12, 355);
            this.lTotal.Name = "lTotal";
            this.lTotal.Size = new System.Drawing.Size(94, 15);
            this.lTotal.TabIndex = 0;
            this.lTotal.Text = "Total warnings:  ";
            // 
            // WarningsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.CancelButton = this.bClose;
            this.ClientSize = new System.Drawing.Size(692, 380);
            this.Controls.Add(this.lTotal);
            this.Controls.Add(this.bClose);
            this.Controls.Add(this.dgvWarnings);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MinimumSize = new System.Drawing.Size(700, 410);
            this.Name = "WarningsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Warnings of Distant Land Setup Wizard latest actions";
            ((System.ComponentModel.ISupportInitialize)(this.dgvWarnings)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.DataGridView dgvWarnings;
        private System.Windows.Forms.Button bClose;
        private System.Windows.Forms.Label lTotal;
        private System.Windows.Forms.DataGridViewTextBoxColumn warnId;
        private System.Windows.Forms.DataGridViewTextBoxColumn warnText;
    }
}