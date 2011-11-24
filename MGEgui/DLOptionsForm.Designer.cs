namespace MGEgui
{
    partial class DLOptionsForm
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
            this.components = new System.ComponentModel.Container ();
            this.cbDLNotInt = new System.Windows.Forms.CheckBox ();
            this.cbDLMWBlendOff = new System.Windows.Forms.CheckBox ();
            this.bOK = new System.Windows.Forms.Button ();
            this.cbDLInitOff = new System.Windows.Forms.CheckBox ();
            this.toolTip = new System.Windows.Forms.ToolTip (this.components);
            this.SuspendLayout ();
            // 
            // cbDLNotInt
            // 
            this.cbDLNotInt.AutoSize = true;
            this.cbDLNotInt.Location = new System.Drawing.Point (12, 12);
            this.cbDLNotInt.Name = "cbDLNotInt";
            this.cbDLNotInt.Size = new System.Drawing.Size (197, 17);
            this.cbDLNotInt.TabIndex = 1;
            this.cbDLNotInt.Text = "Don\'t enable Distant Land in interiors";
            this.cbDLNotInt.UseVisualStyleBackColor = true;
            this.cbDLNotInt.CheckedChanged += new System.EventHandler (this.cb_CheckedChanged);
            // 
            // cbDLMWBlendOff
            // 
            this.cbDLMWBlendOff.AutoSize = true;
            this.cbDLMWBlendOff.Location = new System.Drawing.Point (12, 58);
            this.cbDLMWBlendOff.Name = "cbDLMWBlendOff";
            this.cbDLMWBlendOff.Size = new System.Drawing.Size (197, 17);
            this.cbDLMWBlendOff.TabIndex = 3;
            this.cbDLMWBlendOff.Text = "MW/MGE blending initially turned off";
            this.cbDLMWBlendOff.UseVisualStyleBackColor = true;
            this.cbDLMWBlendOff.CheckedChanged += new System.EventHandler (this.cb_CheckedChanged);
            // 
            // bOK
            // 
            this.bOK.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.bOK.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.bOK.Location = new System.Drawing.Point (12, 90);
            this.bOK.Name = "bOK";
            this.bOK.Size = new System.Drawing.Size (270, 23);
            this.bOK.TabIndex = 0;
            this.bOK.Text = "OK";
            this.bOK.UseVisualStyleBackColor = true;
            // 
            // cbDLInitOff
            // 
            this.cbDLInitOff.AutoSize = true;
            this.cbDLInitOff.Location = new System.Drawing.Point (12, 35);
            this.cbDLInitOff.Name = "cbDLInitOff";
            this.cbDLInitOff.Size = new System.Drawing.Size (165, 17);
            this.cbDLInitOff.TabIndex = 2;
            this.cbDLInitOff.Text = "Distant Land initially turned off";
            this.cbDLInitOff.UseVisualStyleBackColor = true;
            this.cbDLInitOff.CheckedChanged += new System.EventHandler (this.cb_CheckedChanged);
            // 
            // toolTip
            // 
            this.toolTip.AutoPopDelay = 10000;
            this.toolTip.InitialDelay = 500;
            this.toolTip.ReshowDelay = 100;
            // 
            // DLOptionsForm
            // 
            this.CancelButton = this.bOK;
            this.ClientSize = new System.Drawing.Size (294, 122);
            this.Controls.Add (this.bOK);
            this.Controls.Add (this.cbDLInitOff);
            this.Controls.Add (this.cbDLMWBlendOff);
            this.Controls.Add (this.cbDLNotInt);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size (300, 150);
            this.Name = "DLOptionsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Distant Land Options";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler (this.DLOptionsForm_FormClosed);
            this.ResumeLayout (false);
            this.PerformLayout ();

        }

        #endregion

        private System.Windows.Forms.CheckBox cbDLNotInt;
        private System.Windows.Forms.CheckBox cbDLMWBlendOff;
        private System.Windows.Forms.Button bOK;
        private System.Windows.Forms.CheckBox cbDLInitOff;
        private System.Windows.Forms.ToolTip toolTip;

    }
}