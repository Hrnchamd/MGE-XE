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
            this.SuspendLayout();
            // 
            // lbOverrideList
            // 
            this.lbOverrideList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                                    | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.lbOverrideList.FormattingEnabled = true;
            this.lbOverrideList.IntegralHeight = false;
            this.lbOverrideList.Location = new System.Drawing.Point(12, 12);
            this.lbOverrideList.Name = "lbOverrideList";
            this.lbOverrideList.Size = new System.Drawing.Size(456, 187);
            this.lbOverrideList.TabIndex = 0;
            // 
            // bClear
            // 
            this.bClear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bClear.Location = new System.Drawing.Point(474, 12);
            this.bClear.Name = "bClear";
            this.bClear.Size = new System.Drawing.Size(98, 23);
            this.bClear.TabIndex = 1;
            this.bClear.Text = "Clear";
            this.bClear.UseVisualStyleBackColor = true;
            this.bClear.Click += new System.EventHandler(this.bClear_Click);
            // 
            // bAdd
            // 
            this.bAdd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bAdd.Location = new System.Drawing.Point(474, 41);
            this.bAdd.Name = "bAdd";
            this.bAdd.Size = new System.Drawing.Size(98, 23);
            this.bAdd.TabIndex = 2;
            this.bAdd.Text = "Add";
            this.bAdd.UseVisualStyleBackColor = true;
            this.bAdd.Click += new System.EventHandler(this.bAdd_Click);
            // 
            // bRemove
            // 
            this.bRemove.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.bRemove.Location = new System.Drawing.Point(474, 70);
            this.bRemove.Name = "bRemove";
            this.bRemove.Size = new System.Drawing.Size(98, 23);
            this.bRemove.TabIndex = 3;
            this.bRemove.Text = "Remove";
            this.bRemove.UseVisualStyleBackColor = true;
            this.bRemove.Click += new System.EventHandler(this.bRemove_Click);
            // 
            // bUp
            // 
            this.bUp.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.bUp.Location = new System.Drawing.Point(474, 99);
            this.bUp.Name = "bUp";
            this.bUp.Size = new System.Drawing.Size(46, 41);
            this.bUp.TabIndex = 4;
            this.bUp.Text = "Move\r\nUp";
            this.bUp.UseVisualStyleBackColor = true;
            this.bUp.Click += new System.EventHandler(this.bUp_Click);
            // 
            // bDown
            // 
            this.bDown.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.bDown.Location = new System.Drawing.Point(526, 99);
            this.bDown.Name = "bDown";
            this.bDown.Size = new System.Drawing.Size(46, 41);
            this.bDown.TabIndex = 5;
            this.bDown.Text = "Move\r\nDown";
            this.bDown.UseVisualStyleBackColor = true;
            this.bDown.Click += new System.EventHandler(this.bDown_Click);
            // 
            // bCancel
            // 
            this.bCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.bCancel.Location = new System.Drawing.Point(474, 147);
            this.bCancel.Name = "bCancel";
            this.bCancel.Size = new System.Drawing.Size(98, 23);
            this.bCancel.TabIndex = 6;
            this.bCancel.Text = "Cancel";
            this.bCancel.UseVisualStyleBackColor = true;
            // 
            // bSave
            // 
            this.bSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bSave.Location = new System.Drawing.Point(474, 176);
            this.bSave.Name = "bSave";
            this.bSave.Size = new System.Drawing.Size(98, 23);
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
            // OverrideListForm
            // 
            this.AcceptButton = this.bSave;
            this.CancelButton = this.bCancel;
            this.ClientSize = new System.Drawing.Size(584, 211);
            this.Controls.Add(this.lbOverrideList);
            this.Controls.Add(this.bClear);
            this.Controls.Add(this.bAdd);
            this.Controls.Add(this.bRemove);
            this.Controls.Add(this.bUp);
            this.Controls.Add(this.bDown);
            this.Controls.Add(this.bCancel);
            this.Controls.Add(this.bSave);
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MinimumSize = new System.Drawing.Size(480, 250);
            this.Name = "OverrideListForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Selected Static Override Lists";
            this.ResumeLayout(false);
        }

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
