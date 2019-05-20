using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Win32;
using System.IO;
using System.Collections.Generic;

namespace MGEgui {
    public class ResolutionForm : Form {

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
            if (disposing && (components != null)) {
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
            this.cmbRes = new System.Windows.Forms.ComboBox();
            this.tbWidth = new System.Windows.Forms.TextBox();
            this.tbHeight = new System.Windows.Forms.TextBox();
            this.lScrWdth = new System.Windows.Forms.Label();
            this.lScrHght = new System.Windows.Forms.Label();
            this.lArbRes = new System.Windows.Forms.Label();
            this.bCancel = new System.Windows.Forms.Button();
            this.bOK = new System.Windows.Forms.Button();
            this.DudMenu = new System.Windows.Forms.ContextMenu();
            this.lResolution = new System.Windows.Forms.Label();
            this.cmbRefreshRate = new System.Windows.Forms.ComboBox();
            this.lRefreshRate = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // cmbRes
            // 
            this.cmbRes.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbRes.Location = new System.Drawing.Point(12, 12);
            this.cmbRes.Name = "cmbRes";
            this.cmbRes.Size = new System.Drawing.Size(104, 23);
            this.cmbRes.TabIndex = 0;
            this.cmbRes.SelectedIndexChanged += new System.EventHandler(this.cmbRes_SelectedIndexChanged);
            this.cmbRes.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.cmbRes_KeyPress);
            // 
            // tbWidth
            // 
            this.tbWidth.Location = new System.Drawing.Point(46, 48);
            this.tbWidth.Name = "tbWidth";
            this.tbWidth.Size = new System.Drawing.Size(70, 23);
            this.tbWidth.TabIndex = 1;
            this.tbWidth.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // tbHeight
            // 
            this.tbHeight.Location = new System.Drawing.Point(46, 74);
            this.tbHeight.Name = "tbHeight";
            this.tbHeight.Size = new System.Drawing.Size(70, 23);
            this.tbHeight.TabIndex = 2;
            this.tbHeight.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // lScrWdth
            // 
            this.lScrWdth.AutoSize = true;
            this.lScrWdth.Location = new System.Drawing.Point(122, 51);
            this.lScrWdth.Name = "lScrWdth";
            this.lScrWdth.Size = new System.Drawing.Size(77, 15);
            this.lScrWdth.TabIndex = 0;
            this.lScrWdth.Text = "Screen Width";
            // 
            // lScrHght
            // 
            this.lScrHght.AutoSize = true;
            this.lScrHght.Location = new System.Drawing.Point(122, 77);
            this.lScrHght.Name = "lScrHght";
            this.lScrHght.Size = new System.Drawing.Size(81, 15);
            this.lScrHght.TabIndex = 0;
            this.lScrHght.Text = "Screen Height";
            // 
            // lArbRes
            // 
            this.lArbRes.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lArbRes.AutoSize = true;
            this.lArbRes.Location = new System.Drawing.Point(12, 108);
            this.lArbRes.MaximumSize = new System.Drawing.Size(370, 0);
            this.lArbRes.Name = "lArbRes";
            this.lArbRes.Size = new System.Drawing.Size(304, 15);
            this.lArbRes.TabIndex = 0;
            this.lArbRes.Text = "Arbitrary resolutions can only be set in windowed mode.";
            // 
            // bCancel
            // 
            this.bCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bCancel.Location = new System.Drawing.Point(297, 151);
            this.bCancel.Name = "bCancel";
            this.bCancel.Size = new System.Drawing.Size(85, 23);
            this.bCancel.TabIndex = 3;
            this.bCancel.Text = "Cancel";
            this.bCancel.Click += new System.EventHandler(this.bCancel_Click);
            // 
            // bOK
            // 
            this.bOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bOK.Location = new System.Drawing.Point(206, 151);
            this.bOK.Name = "bOK";
            this.bOK.Size = new System.Drawing.Size(85, 23);
            this.bOK.TabIndex = 4;
            this.bOK.Text = "OK";
            this.bOK.Click += new System.EventHandler(this.bOK_Click);
            // 
            // lResolution
            // 
            this.lResolution.AutoSize = true;
            this.lResolution.Location = new System.Drawing.Point(122, 15);
            this.lResolution.Name = "lResolution";
            this.lResolution.Size = new System.Drawing.Size(63, 15);
            this.lResolution.TabIndex = 5;
            this.lResolution.Text = "Resolution";
            // 
            // cmbRefreshRate
            // 
            this.cmbRefreshRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbRefreshRate.Location = new System.Drawing.Point(221, 12);
            this.cmbRefreshRate.Name = "cmbRefreshRate";
            this.cmbRefreshRate.Size = new System.Drawing.Size(70, 23);
            this.cmbRefreshRate.TabIndex = 6;
            // 
            // lRefreshRate
            // 
            this.lRefreshRate.AutoSize = true;
            this.lRefreshRate.Location = new System.Drawing.Point(297, 15);
            this.lRefreshRate.Name = "lRefreshRate";
            this.lRefreshRate.Size = new System.Drawing.Size(69, 15);
            this.lRefreshRate.TabIndex = 7;
            this.lRefreshRate.Text = "Refresh rate";
            this.lRefreshRate.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // ResolutionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(394, 186);
            this.Controls.Add(this.lRefreshRate);
            this.Controls.Add(this.cmbRefreshRate);
            this.Controls.Add(this.lResolution);
            this.Controls.Add(this.bOK);
            this.Controls.Add(this.bCancel);
            this.Controls.Add(this.lArbRes);
            this.Controls.Add(this.lScrHght);
            this.Controls.Add(this.lScrWdth);
            this.Controls.Add(this.tbHeight);
            this.Controls.Add(this.tbWidth);
            this.Controls.Add(this.cmbRes);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MaximizeBox = false;
            this.Name = "ResolutionForm";
            this.Text = "Select Resolution";
            this.ResumeLayout(false);
            this.PerformLayout();
        }
        private System.Windows.Forms.Label lRefreshRate;
        private System.Windows.Forms.ComboBox cmbRefreshRate;
        private System.Windows.Forms.Label lResolution;

        #endregion
        private ComboBox cmbRes;
        private TextBox tbWidth;
        private TextBox tbHeight;
        private Label lScrWdth;
        private Label lScrHght;
        private Label lArbRes;
        private Button bCancel;
        private ContextMenu DudMenu;
        private Button bOK;
        #endregion

        public static Dictionary<string, string> strings = new Dictionary<string, string>();

        private class Resolution {
            Point res;
            public int X { get { return res.X; } }
            public int Y { get { return res.Y; } }

            public Resolution(Point r) {
                res = r;
            }
            public override string ToString() {
                return res.X.ToString() + " x " + res.Y.ToString();
            }
        }

        static int sWidth, sHeight, sRefresh;
        static bool Fullscreen;
        static int Adaptor;
        static List<Resolution> Resolutions;

        public ResolutionForm() {
            InitializeComponent();
            Statics.Localizations.Apply(this);

            cmbRes.ContextMenu = DudMenu;

            if (Fullscreen) {
                tbWidth.Enabled = false;
                tbHeight.Enabled = false;
            } else {
                lArbRes.Visible = false;
            }

            tbWidth.Text = sWidth.ToString();
            tbHeight.Text = sHeight.ToString();
            cmbRefreshRate.Items.Add(Statics.strings["Default"]);

            foreach (Resolution p in Resolutions) {
                cmbRes.Items.Add(p);

                if (p.X == sWidth && p.Y == sHeight) {
                    cmbRes.SelectedIndex = cmbRes.Items.Count - 1;
                }
            }

            cmbRefreshRate.SelectedIndex = cmbRefreshRate.FindStringExact(sRefresh.ToString());
            if (cmbRefreshRate.SelectedIndex == -1) {
                cmbRefreshRate.SelectedIndex = 0;
            }
        }

        public static bool ShowDialog(out Point p, out int refresh, bool Windowed) {
            // Fetch data from the registry
            RegistryKey key = Registry.LocalMachine.OpenSubKey(@"Software\Bethesda Softworks\Morrowind");
            sWidth = (int)key.GetValue("Screen Width", 640);
            sHeight = (int)key.GetValue("Screen Height", 480);
            sRefresh = (int)key.GetValue("Refresh Rate", 0);
            Adaptor = DirectX.DXMain.Adapter;
            Fullscreen = !Windowed;
            key.Close();

            // Get the list of valid resolutions
            Resolutions = new List<Resolution>();
            foreach (Point r in DirectX.DXMain.GetResolutions()) {
                Resolutions.Add(new Resolution(r));
            }

            // Show the dialog
            ResolutionForm rf = new ResolutionForm();
            if (rf.ShowDialog() == DialogResult.OK) {
                // Write new data to the registry
                try {
                    key = Registry.LocalMachine.OpenSubKey(@"Software\Bethesda Softworks\Morrowind", true);
                } catch {
                    MessageBox.Show(Statics.strings["UnableToWriteReg"], Statics.strings["Error"]);
                }
                if (key != null) {
                    key.SetValue("Screen Width", sWidth);
                    key.SetValue("Screen Height", sHeight);
                    key.SetValue("Refresh Rate", sRefresh);
                    key.Close();
                }
                // Return
                p = new Point(sWidth, sHeight);
                refresh = sRefresh;
                return true;
            }
            p = new Point();
            refresh = 0;
            return false;
        }

        private void bOK_Click(object sender, EventArgs e) {
            int width, height, refresh;

            try {
                width = Convert.ToInt32(tbWidth.Text);
            } catch {
                MessageBox.Show(strings["InvalidWidth"]);
                return;
            }
            try {
                height = Convert.ToInt32(tbHeight.Text);
            } catch {
                MessageBox.Show(strings["InvalidHeight"]);
                return;
            }
            if (width <= 0 || height <= 0) {
                MessageBox.Show(strings["DimensionError"]);
                return;
            }
            try {
                refresh = Convert.ToInt32(cmbRefreshRate.Text);
            } catch {
                refresh = 0;
            }

            sWidth = width;
            sHeight = height;
            sRefresh = refresh;
            DialogResult = DialogResult.OK;
            Close();
        }

        private void bCancel_Click(object sender, EventArgs e) {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void cmbRes_SelectedIndexChanged(object sender, EventArgs e) {
            string[] str = cmbRes.Text.Trim(new char[] { ' ', '*' }).Split('x');
            tbWidth.Text = str[0].Trim();
            tbHeight.Text = str[1].Trim();

            string previousRefresh = cmbRefreshRate.Text;
            cmbRefreshRate.Items.Clear();
            cmbRefreshRate.Items.Add(Statics.strings["Default"]);
            foreach (int i in DirectX.DXMain.GetRefreshRates(Convert.ToInt32(tbWidth.Text), Convert.ToInt32(tbHeight.Text))) {
                cmbRefreshRate.Items.Add(i.ToString());
            }

            cmbRefreshRate.SelectedIndex = cmbRefreshRate.FindStringExact(previousRefresh);
            if (cmbRefreshRate.SelectedIndex == -1) {
                cmbRefreshRate.SelectedIndex = 0;
            }
        }

        private void cmbRes_KeyPress(object sender, KeyPressEventArgs e) {
            e.Handled = true;
        }
    }
}
