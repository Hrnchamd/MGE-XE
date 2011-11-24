using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Win32;
using System.IO;
using ArrayList=System.Collections.ArrayList;

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
        	this.cmbRes = new System.Windows.Forms.ComboBox();
        	this.tbWidth = new System.Windows.Forms.TextBox();
        	this.tbHeight = new System.Windows.Forms.TextBox();
        	this.lScrWdth = new System.Windows.Forms.Label();
        	this.lScrHght = new System.Windows.Forms.Label();
        	this.lArbRes = new System.Windows.Forms.Label();
        	this.bCancel = new System.Windows.Forms.Button();
        	this.bOK = new System.Windows.Forms.Button();
        	this.DudMenu = new System.Windows.Forms.ContextMenu();
        	this.SuspendLayout();
        	// 
        	// cmbRes
        	// 
        	this.cmbRes.Location = new System.Drawing.Point(12, 12);
        	this.cmbRes.Name = "cmbRes";
        	this.cmbRes.Size = new System.Drawing.Size(121, 21);
        	this.cmbRes.TabIndex = 0;
        	this.cmbRes.SelectedIndexChanged += new System.EventHandler(this.cmbRes_SelectedIndexChanged);
        	this.cmbRes.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.cmbRes_KeyPress);
        	// 
        	// tbWidth
        	// 
        	this.tbWidth.Location = new System.Drawing.Point(12, 39);
        	this.tbWidth.Name = "tbWidth";
        	this.tbWidth.Size = new System.Drawing.Size(100, 20);
        	this.tbWidth.TabIndex = 1;
        	// 
        	// tbHeight
        	// 
        	this.tbHeight.Location = new System.Drawing.Point(12, 65);
        	this.tbHeight.Name = "tbHeight";
        	this.tbHeight.Size = new System.Drawing.Size(100, 20);
        	this.tbHeight.TabIndex = 2;
        	// 
        	// lScrWdth
        	// 
        	this.lScrWdth.AutoSize = true;
        	this.lScrWdth.Location = new System.Drawing.Point(118, 42);
        	this.lScrWdth.Name = "lScrWdth";
        	this.lScrWdth.Size = new System.Drawing.Size(72, 13);
        	this.lScrWdth.TabIndex = 0;
        	this.lScrWdth.Text = "Screen Width";
        	// 
        	// lScrHght
        	// 
        	this.lScrHght.AutoSize = true;
        	this.lScrHght.Location = new System.Drawing.Point(118, 68);
        	this.lScrHght.Name = "lScrHght";
        	this.lScrHght.Size = new System.Drawing.Size(75, 13);
        	this.lScrHght.TabIndex = 0;
        	this.lScrHght.Text = "Screen Height";
        	// 
        	// lArbRes
        	// 
        	this.lArbRes.AutoSize = true;
        	this.lArbRes.Location = new System.Drawing.Point(12, 88);
        	this.lArbRes.Name = "lArbRes";
        	this.lArbRes.Size = new System.Drawing.Size(264, 13);
        	this.lArbRes.TabIndex = 0;
        	this.lArbRes.Text = "Arbitrary resolutions can only be set in windowed mode";
        	// 
        	// bCancel
        	// 
        	this.bCancel.Location = new System.Drawing.Point(12, 108);
        	this.bCancel.Name = "bCancel";
        	this.bCancel.Size = new System.Drawing.Size(75, 23);
        	this.bCancel.TabIndex = 3;
        	this.bCancel.Text = "Cancel";
        	this.bCancel.Click += new System.EventHandler(this.bCancel_Click);
        	// 
        	// bOK
        	// 
        	this.bOK.Location = new System.Drawing.Point(201, 108);
        	this.bOK.Name = "bOK";
        	this.bOK.Size = new System.Drawing.Size(75, 23);
        	this.bOK.TabIndex = 4;
        	this.bOK.Text = "OK";
        	this.bOK.Click += new System.EventHandler(this.bOK_Click);
        	// 
        	// ResolutionForm
        	// 
        	this.ClientSize = new System.Drawing.Size(294, 143);
        	this.Controls.Add(this.bOK);
        	this.Controls.Add(this.bCancel);
        	this.Controls.Add(this.lArbRes);
        	this.Controls.Add(this.lScrHght);
        	this.Controls.Add(this.lScrWdth);
        	this.Controls.Add(this.tbHeight);
        	this.Controls.Add(this.tbWidth);
        	this.Controls.Add(this.cmbRes);
        	this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
        	this.Icon = global::MGEgui.Properties.Resources.AppIcon;
        	this.MaximizeBox = false;
        	this.Name = "ResolutionForm";
        	this.Text = "Select Resolution";
        	this.ResumeLayout(false);
        	this.PerformLayout();
        }

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

        public ResolutionForm() {
            InitializeComponent();
            cmbRes.ContextMenu = DudMenu;
            if(Fullscreen) {
                tbWidth.ReadOnly=true;
                tbHeight.ReadOnly=true;
            } else {
                lArbRes.Visible=false;
            }
            tbWidth.Text=sWidth.ToString();
            tbHeight.Text=sHeight.ToString();
            foreach(Point p in Resolutions) {
                string s = p.X.ToString() + " x " + p.Y.ToString();
                if((float)p.Y/(float)p.X!=0.75f) s+=" *";
                cmbRes.Items.Add(s);
            }
        }

        static int sWidth;
        static int sHeight;
        static bool Fullscreen;
        static int Adaptor;
        static Point[] Resolutions;
        public static bool ShowDialog(out Point p, bool Windowed) {
            //Fetch data from the registry
            RegistryKey key=Registry.LocalMachine.OpenSubKey(@"Software\Bethesda Softworks\Morrowind");
            sWidth=(int)key.GetValue("Screen Width");
            sHeight=(int)key.GetValue("Screen Height");
            Adaptor=DirectX.DXMain.Adapter;
            Fullscreen=!Windowed;
            key.Close();
            //Get the list of valid resolutions
            Resolutions=DirectX.DXMain.GetResolutions();
            //Show the dialog
            ResolutionForm rf=new ResolutionForm();
            if(rf.ShowDialog()==DialogResult.OK) {
                //Write new dtat to the registry
                try {
                    key = Registry.LocalMachine.OpenSubKey(@"Software\Bethesda Softworks\Morrowind", true);
                } catch {
                    MessageBox.Show("Could not write Morrowind registry key. MGE needs to be launched as Administrator.", "Error");
                }
                if (key != null) {
                    key.SetValue("Screen Width", sWidth);
                    key.SetValue("Screen Height", sHeight);
                    key.Close();
                }
                //Return
                p=new Point(sWidth, sHeight);
                return true;
            }
            p=new Point();
            return false;
        }

        private void bOK_Click(object sender, EventArgs e) {
            int width, height;
            try {
                width=Convert.ToInt32(tbWidth.Text);
            } catch {
                MessageBox.Show("Invalid value entered for screen width");
                return;
            }
            try {
                height=Convert.ToInt32(tbHeight.Text);
            } catch {
                MessageBox.Show("Invalid value entered for screen height");
                return;
            }
            if(width<=0||height<=0) {
                MessageBox.Show("Screen width and height must be greater than 0");
                return;
            }
            DialogResult=DialogResult.OK;
            sWidth=width;
            sHeight=height;
            Close();
        }

        private void bCancel_Click(object sender, EventArgs e) {
            DialogResult=DialogResult.Cancel;
            Close();
        }

        private void cmbRes_SelectedIndexChanged(object sender, EventArgs e) {
            string[] str=cmbRes.Text.Trim(new char[] { ' ', '*' }).Split('x');
            tbWidth.Text = str[0].Trim();
            tbHeight.Text = str[1].Trim();
        }

        private void cmbRes_KeyPress(object sender, KeyPressEventArgs e) {
            e.Handled=true;
        }
    }
}
