using System;
using System.Windows.Forms;
using System.IO;
using System.ComponentModel;
using System.Collections.Generic;
using ArrayList = System.Collections.ArrayList;
using System.Text.RegularExpressions;

namespace MGEgui {
    public class ShaderEditorForm : Form {
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ShaderEditorForm));
            this.rtbTechnique = new System.Windows.Forms.RichTextBox();
            this.tbMessage = new System.Windows.Forms.TextBox();
            this.bValidate = new System.Windows.Forms.Button();
            this.bPreview = new System.Windows.Forms.Button();
            this.OpenImage = new System.Windows.Forms.OpenFileDialog();
            this.bSetImage = new System.Windows.Forms.Button();
            this.bPreviewChain = new System.Windows.Forms.Button();
            this.bSetDepthImage = new System.Windows.Forms.Button();
            this.OpenShader = new System.Windows.Forms.OpenFileDialog();
            this.SaveShader = new System.Windows.Forms.SaveFileDialog();
            this.FileToolStrip = new System.Windows.Forms.ToolStrip();
            this.bShaderNew = new System.Windows.Forms.ToolStripButton();
            this.bShaderOpen = new System.Windows.Forms.ToolStripButton();
            this.bShaderSave = new System.Windows.Forms.ToolStripButton();
            this.bShaderSaveAs = new System.Windows.Forms.ToolStripButton();
            this.bShaderFlags = new System.Windows.Forms.Button();
            this.MenuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.undoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.redoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.cutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pasteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.flowLayoutPanel2 = new System.Windows.Forms.FlowLayoutPanel();
            this.FileToolStrip.SuspendLayout();
            this.MenuStrip.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.flowLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // rtbTechnique
            // 
            this.rtbTechnique.AcceptsTab = true;
            this.rtbTechnique.DetectUrls = false;
            this.rtbTechnique.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rtbTechnique.Font = new System.Drawing.Font("Courier New", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rtbTechnique.Location = new System.Drawing.Point(0, 31);
            this.rtbTechnique.Margin = new System.Windows.Forms.Padding(0, 6, 0, 6);
            this.rtbTechnique.Name = "rtbTechnique";
            this.rtbTechnique.Size = new System.Drawing.Size(640, 377);
            this.rtbTechnique.TabIndex = 5;
            this.rtbTechnique.Text = "";
            this.rtbTechnique.WordWrap = false;
            this.rtbTechnique.TextChanged += new System.EventHandler(this.rtbTechnique_TextChanged);
            this.rtbTechnique.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.rtbTechnique_KeyPress);
            // 
            // tbMessage
            // 
            this.tbMessage.BackColor = System.Drawing.Color.White;
            this.tbMessage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbMessage.Location = new System.Drawing.Point(0, 414);
            this.tbMessage.Margin = new System.Windows.Forms.Padding(0);
            this.tbMessage.Multiline = true;
            this.tbMessage.Name = "tbMessage";
            this.tbMessage.ReadOnly = true;
            this.tbMessage.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbMessage.Size = new System.Drawing.Size(640, 50);
            this.tbMessage.TabIndex = 6;
            // 
            // bValidate
            // 
            this.bValidate.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bValidate.AutoSize = true;
            this.bValidate.Location = new System.Drawing.Point(0, 0);
            this.bValidate.Margin = new System.Windows.Forms.Padding(0, 0, 3, 0);
            this.bValidate.Name = "bValidate";
            this.bValidate.Size = new System.Drawing.Size(80, 25);
            this.bValidate.TabIndex = 7;
            this.bValidate.Text = "Validate";
            this.bValidate.Click += new System.EventHandler(this.bValidate_Click);
            // 
            // bPreview
            // 
            this.bPreview.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bPreview.AutoSize = true;
            this.bPreview.Location = new System.Drawing.Point(83, 0);
            this.bPreview.Margin = new System.Windows.Forms.Padding(0, 0, 3, 0);
            this.bPreview.Name = "bPreview";
            this.bPreview.Size = new System.Drawing.Size(80, 25);
            this.bPreview.TabIndex = 8;
            this.bPreview.Text = "Preview";
            this.bPreview.Click += new System.EventHandler(this.bPreview_Click);
            // 
            // OpenImage
            // 
            this.OpenImage.DefaultExt = "tga";
            this.OpenImage.Filter = "Texture file (tga,bmp,dds,jpg)|*.tga;*.bmp;*.jpg;*.jpeg;*.dds;*.dib";
            this.OpenImage.InitialDirectory = "mge3";
            this.OpenImage.RestoreDirectory = true;
            this.OpenImage.Title = "Select image";
            // 
            // bSetImage
            // 
            this.bSetImage.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bSetImage.AutoSize = true;
            this.bSetImage.Location = new System.Drawing.Point(46, 0);
            this.bSetImage.Margin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.bSetImage.Name = "bSetImage";
            this.bSetImage.Size = new System.Drawing.Size(125, 25);
            this.bSetImage.TabIndex = 10;
            this.bSetImage.Text = "Set <thisframe>";
            this.bSetImage.Click += new System.EventHandler(this.bSetImage_Click);
            // 
            // bPreviewChain
            // 
            this.bPreviewChain.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.bPreviewChain.AutoSize = true;
            this.bPreviewChain.Location = new System.Drawing.Point(166, 0);
            this.bPreviewChain.Margin = new System.Windows.Forms.Padding(0, 0, 3, 0);
            this.bPreviewChain.Name = "bPreviewChain";
            this.bPreviewChain.Size = new System.Drawing.Size(134, 25);
            this.bPreviewChain.TabIndex = 4;
            this.bPreviewChain.Text = "Preview active chain";
            this.bPreviewChain.Click += new System.EventHandler(this.bPreviewChain_Click);
            // 
            // bSetDepthImage
            // 
            this.bSetDepthImage.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bSetDepthImage.AutoSize = true;
            this.bSetDepthImage.Location = new System.Drawing.Point(174, 0);
            this.bSetDepthImage.Margin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.bSetDepthImage.Name = "bSetDepthImage";
            this.bSetDepthImage.Size = new System.Drawing.Size(125, 25);
            this.bSetDepthImage.TabIndex = 12;
            this.bSetDepthImage.Text = "Set <depthframe>";
            this.bSetDepthImage.Click += new System.EventHandler(this.bSetDepthImage_click);
            // 
            // OpenShader
            // 
            this.OpenShader.DefaultExt = "fx";
            this.OpenShader.Filter = "Shader effect file (fx)|*.fx";
            this.OpenShader.RestoreDirectory = true;
            this.OpenShader.Title = "Open shader";
            // 
            // SaveShader
            // 
            this.SaveShader.DefaultExt = "fx";
            this.SaveShader.Filter = "Shader effect file (fx)|*.fx";
            this.SaveShader.RestoreDirectory = true;
            this.SaveShader.Title = "Save shader";
            // 
            // FileToolStrip
            // 
            this.FileToolStrip.CanOverflow = false;
            this.FileToolStrip.ImageScalingSize = new System.Drawing.Size(22, 22);
            this.FileToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
                this.bShaderNew,
                this.bShaderOpen,
                this.bShaderSave,
                this.bShaderSaveAs
            });
            this.FileToolStrip.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.FileToolStrip.Location = new System.Drawing.Point(0, 24);
            this.FileToolStrip.Name = "FileToolStrip";
            this.FileToolStrip.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.FileToolStrip.Size = new System.Drawing.Size(664, 26);
            this.FileToolStrip.TabIndex = 0;
            // 
            // bShaderNew
            // 
            this.bShaderNew.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bShaderNew.Image = ((System.Drawing.Image)(resources.GetObject("bShaderNew.Image")));
            this.bShaderNew.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.bShaderNew.Margin = new System.Windows.Forms.Padding(0);
            this.bShaderNew.Name = "bShaderNew";
            this.bShaderNew.Size = new System.Drawing.Size(26, 26);
            this.bShaderNew.Text = "New";
            this.bShaderNew.Click += new System.EventHandler(this.bShaderNew_Click);
            // 
            // bShaderOpen
            // 
            this.bShaderOpen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bShaderOpen.Image = ((System.Drawing.Image)(resources.GetObject("bShaderOpen.Image")));
            this.bShaderOpen.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.bShaderOpen.Margin = new System.Windows.Forms.Padding(0);
            this.bShaderOpen.Name = "bShaderOpen";
            this.bShaderOpen.Size = new System.Drawing.Size(26, 26);
            this.bShaderOpen.Text = "Open";
            this.bShaderOpen.Click += new System.EventHandler(this.bShaderOpen_Click);
            // 
            // bShaderSave
            // 
            this.bShaderSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bShaderSave.Image = ((System.Drawing.Image)(resources.GetObject("bShaderSave.Image")));
            this.bShaderSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.bShaderSave.Margin = new System.Windows.Forms.Padding(0);
            this.bShaderSave.Name = "bShaderSave";
            this.bShaderSave.Size = new System.Drawing.Size(26, 26);
            this.bShaderSave.Text = "Save";
            this.bShaderSave.Click += new System.EventHandler(this.bShaderSave_Click);
            // 
            // bShaderSaveAs
            // 
            this.bShaderSaveAs.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bShaderSaveAs.Image = ((System.Drawing.Image)(resources.GetObject("bShaderSaveAs.Image")));
            this.bShaderSaveAs.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.bShaderSaveAs.Margin = new System.Windows.Forms.Padding(0);
            this.bShaderSaveAs.Name = "bShaderSaveAs";
            this.bShaderSaveAs.Size = new System.Drawing.Size(26, 26);
            this.bShaderSaveAs.Text = "Save As";
            this.bShaderSaveAs.Click += new System.EventHandler(this.bShaderSaveAs_Click);
            // 
            // bShaderFlags
            // 
            this.bShaderFlags.AutoSize = true;
            this.bShaderFlags.Dock = System.Windows.Forms.DockStyle.Right;
            this.bShaderFlags.Location = new System.Drawing.Point(497, 0);
            this.bShaderFlags.Margin = new System.Windows.Forms.Padding(3, 0, 3, 0);
            this.bShaderFlags.Name = "bShaderFlags";
            this.bShaderFlags.Size = new System.Drawing.Size(140, 25);
            this.bShaderFlags.TabIndex = 13;
            this.bShaderFlags.Text = "Edit shader flags";
            this.bShaderFlags.Click += new System.EventHandler(this.bShaderFlags_Click);
            // 
            // MenuStrip
            // 
            this.MenuStrip.GripMargin = new System.Windows.Forms.Padding(0);
            this.MenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
                this.fileToolStripMenuItem,
                this.editToolStripMenuItem
            });
            this.MenuStrip.Location = new System.Drawing.Point(0, 0);
            this.MenuStrip.Name = "MenuStrip";
            this.MenuStrip.Padding = new System.Windows.Forms.Padding(0);
            this.MenuStrip.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            this.MenuStrip.Size = new System.Drawing.Size(664, 24);
            this.MenuStrip.TabIndex = 15;
            this.MenuStrip.Text = "MenuStrip";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
                this.newToolStripMenuItem,
                this.openToolStripMenuItem,
                this.toolStripSeparator,
                this.saveToolStripMenuItem,
                this.saveAsToolStripMenuItem,
                this.toolStripSeparator2,
                this.exitToolStripMenuItem
            });
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 24);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("newToolStripMenuItem.Image")));
            this.newToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.bShaderNew_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("openToolStripMenuItem.Image")));
            this.openToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.bShaderOpen_Click);
            // 
            // toolStripSeparator
            // 
            this.toolStripSeparator.Name = "toolStripSeparator";
            this.toolStripSeparator.Size = new System.Drawing.Size(183, 6);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("saveToolStripMenuItem.Image")));
            this.saveToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.bShaderSave_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("saveAsToolStripMenuItem.Image")));
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Shift)
            | System.Windows.Forms.Keys.S)));
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.bShaderSaveAs_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(183, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
                this.undoToolStripMenuItem,
                this.redoToolStripMenuItem,
                this.toolStripSeparator3,
                this.cutToolStripMenuItem,
                this.copyToolStripMenuItem,
                this.pasteToolStripMenuItem,
                this.toolStripSeparator4,
                this.selectAllToolStripMenuItem
            });
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 24);
            this.editToolStripMenuItem.Text = "&Edit";
            // 
            // undoToolStripMenuItem
            // 
            this.undoToolStripMenuItem.Name = "undoToolStripMenuItem";
            this.undoToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.undoToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.undoToolStripMenuItem.Text = "&Undo";
            this.undoToolStripMenuItem.Click += new System.EventHandler(this.undoToolStripMenuItem_Click);
            // 
            // redoToolStripMenuItem
            // 
            this.redoToolStripMenuItem.Name = "redoToolStripMenuItem";
            this.redoToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y)));
            this.redoToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.redoToolStripMenuItem.Text = "&Redo";
            this.redoToolStripMenuItem.Click += new System.EventHandler(this.redoToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(161, 6);
            // 
            // cutToolStripMenuItem
            // 
            this.cutToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("cutToolStripMenuItem.Image")));
            this.cutToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cutToolStripMenuItem.Name = "cutToolStripMenuItem";
            this.cutToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.cutToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.cutToolStripMenuItem.Text = "Cu&t";
            this.cutToolStripMenuItem.Click += new System.EventHandler(this.cutToolStripMenuItem_Click);
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("copyToolStripMenuItem.Image")));
            this.copyToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.copyToolStripMenuItem.Text = "&Copy";
            this.copyToolStripMenuItem.Click += new System.EventHandler(this.copyToolStripMenuItem_Click);
            // 
            // pasteToolStripMenuItem
            // 
            this.pasteToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("pasteToolStripMenuItem.Image")));
            this.pasteToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.pasteToolStripMenuItem.Name = "pasteToolStripMenuItem";
            this.pasteToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.pasteToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.pasteToolStripMenuItem.Text = "&Paste";
            this.pasteToolStripMenuItem.Click += new System.EventHandler(this.pasteToolStripMenuItem_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(161, 6);
            // 
            // selectAllToolStripMenuItem
            // 
            this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
            this.selectAllToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(164, 22);
            this.selectAllToolStripMenuItem.Text = "Select &All";
            this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.selectAllToolStripMenuItem_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.tbMessage, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.bShaderFlags, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.rtbTechnique, 0, 1);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 53);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(640, 464);
            this.tableLayoutPanel1.TabIndex = 16;
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.flowLayoutPanel1.Controls.Add(this.bValidate);
            this.flowLayoutPanel1.Controls.Add(this.bPreview);
            this.flowLayoutPanel1.Controls.Add(this.bPreviewChain);
            this.flowLayoutPanel1.Location = new System.Drawing.Point(12, 524);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(335, 25);
            this.flowLayoutPanel1.TabIndex = 17;
            this.flowLayoutPanel1.WrapContents = false;
            // 
            // flowLayoutPanel2
            // 
            this.flowLayoutPanel2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.flowLayoutPanel2.Controls.Add(this.bSetDepthImage);
            this.flowLayoutPanel2.Controls.Add(this.bSetImage);
            this.flowLayoutPanel2.FlowDirection = System.Windows.Forms.FlowDirection.RightToLeft;
            this.flowLayoutPanel2.Location = new System.Drawing.Point(353, 524);
            this.flowLayoutPanel2.Name = "flowLayoutPanel2";
            this.flowLayoutPanel2.Size = new System.Drawing.Size(299, 25);
            this.flowLayoutPanel2.TabIndex = 18;
            this.flowLayoutPanel2.WrapContents = false;
            // 
            // ShaderEditorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(664, 561);
            this.Controls.Add(this.flowLayoutPanel2);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.FileToolStrip);
            this.Controls.Add(this.MenuStrip);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MainMenuStrip = this.MenuStrip;
            this.MinimumSize = new System.Drawing.Size(520, 440);
            this.Name = "ShaderEditorForm";
            this.Text = "New file - Shader Editor";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.ShaderEditorForm_FormClosing);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ShaderEditorForm_FormClosing);
            this.FileToolStrip.ResumeLayout(false);
            this.FileToolStrip.PerformLayout();
            this.MenuStrip.ResumeLayout(false);
            this.MenuStrip.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.flowLayoutPanel2.ResumeLayout(false);
            this.flowLayoutPanel2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();
        }
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel2;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;

        #endregion

        private System.Windows.Forms.RichTextBox rtbTechnique;
        private System.Windows.Forms.TextBox tbMessage;
        private System.Windows.Forms.Button bValidate;
        private System.Windows.Forms.Button bPreview;
        public OpenFileDialog OpenImage;
        private Button bSetImage;
        private Button bPreviewChain;
        private Button bSetDepthImage;
        public OpenFileDialog OpenShader;
        public SaveFileDialog SaveShader;
        private ToolStrip FileToolStrip;
        private ToolStripButton bShaderNew;
        private ToolStripButton bShaderOpen;
        private ToolStripButton bShaderSave;
        private ToolStripButton bShaderSaveAs;
        private Button bShaderFlags;
        private MenuStrip MenuStrip;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem newToolStripMenuItem;
        private ToolStripMenuItem openToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator;
        private ToolStripMenuItem saveToolStripMenuItem;
        private ToolStripMenuItem saveAsToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator2;
        private ToolStripMenuItem exitToolStripMenuItem;
        private ToolStripMenuItem editToolStripMenuItem;
        private ToolStripMenuItem undoToolStripMenuItem;
        private ToolStripMenuItem redoToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator3;
        private ToolStripMenuItem cutToolStripMenuItem;
        private ToolStripMenuItem copyToolStripMenuItem;
        private ToolStripMenuItem pasteToolStripMenuItem;
        private ToolStripSeparator toolStripSeparator4;
        private ToolStripMenuItem selectAllToolStripMenuItem;
        #endregion

        private string FramePath = null;
        private string DepthPath = null;
        private string FullFileName = null;
        private string EditingName = null;
        private bool ShaderModified = false;

        public static Dictionary<string, string> strings = new Dictionary<string, string>();

        public ShaderEditorForm(string shaderfile) {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            Statics.Localizations.ApplyDialogs(this, new string[] {
                "OpenImage",
                "OpenShader",
                "SaveShader"
            });

            // High DPI aware resizing of 22x22 icons
            using (var g = this.CreateGraphics()) {
                double scale = Math.Max(g.DpiX, g.DpiY) / 96.0;
                int measure = (int)(22 * scale);
                this.FileToolStrip.ImageScalingSize = new System.Drawing.Size(measure, measure);
                this.FileToolStrip.AutoSize = false;
                this.FileToolStrip.PerformLayout();
                this.FileToolStrip.AutoSize = true;
                this.FileToolStrip.PerformLayout();
            }

            this.OpenImage.InitialDirectory = Statics.runDir + @"\mge3";
            this.OpenShader.InitialDirectory = this.SaveShader.InitialDirectory = Statics.runDir + @"\" + Statics.pathShaders;
            EditingName = strings["NewFile"];

            if (shaderfile != null) {
                FullFileName = shaderfile;
                EditingName = shaderfile.Substring(FullFileName.LastIndexOf('\\') + 1);

                StreamReader sr = new StreamReader(File.OpenRead(FullFileName));
                rtbTechnique.Text = sr.ReadToEnd().Trim(new char[] {
                    '\n',
                    '\r'
                });
                sr.Close();

                ShaderModified = false;
            }

            this.Text = EditingName + " - " + strings["ShaderEditor"];
        }

        private bool Validate(IntPtr handle, bool Render) {
            tbMessage.Text = strings["Compiling"];
            tbMessage.Refresh();
            bool result = false;

            string error = null;

            if (ShaderModified || FullFileName == null) {
                string tempfile = (FullFileName == null)
                    ? Statics.runDir + "\\" + Statics.pathShaders + "\\_TempShader"
                    : FullFileName + ".tmp";

                StreamWriter sw = new StreamWriter(File.Open(tempfile, FileMode.Create));
                sw.WriteLine(rtbTechnique.Text);
                sw.Close();

                error = DirectX.Shaders.CompileShader(Render, FramePath, DepthPath, tempfile);

                File.Delete(tempfile);
            } else {
                error = DirectX.Shaders.CompileShader(Render, FramePath, DepthPath, FullFileName);
            }

            if (error == null) {
                tbMessage.Text = strings["CompileSuccess"];
                result = true;
            } else {
                tbMessage.Text = error;
            }
            return result;
        }

        private void bValidate_Click(object sender, EventArgs e) {
            DirectX.DXMain.CreateDevice(this);
            Validate(this.Handle, false);
            DirectX.DXMain.CloseDevice();
        }

        private void bPreview_Click(object sender, EventArgs e) {
            RenderWindow rw = new RenderWindow();
            DirectX.DXMain.CreateDevice(RenderWindow.panel);
            if (Validate(RenderWindow.panel.Handle, true)) {
                rw.ShowDialog();
            }
            rw.Close();
            DirectX.DXMain.CloseDevice();
        }

        private void ShaderEditorForm_FormClosing(object sender, CancelEventArgs e) {
            Directory.SetCurrentDirectory(Statics.runDir);
        }

        private void IgnoreKeyPress(object sender, KeyPressEventArgs e) {
            e.Handled = true;
        }

        private void bSetImage_Click(object sender, EventArgs e) {
            OpenImage.FileName = (FramePath == null) ? Statics.runDir + @"\mge3\preview_frame.dds" : FramePath;
            if (OpenImage.ShowDialog() == DialogResult.OK) {
                FramePath = OpenImage.FileName;
            }
        }

        private void bSetDepthImage_click(object sender, EventArgs e) {
            OpenImage.FileName = (DepthPath == null) ? Statics.runDir + @"\mge3\preview_depth.dds" : DepthPath;
            if (OpenImage.ShowDialog() == DialogResult.OK) {
                DepthPath = OpenImage.FileName;
            }
        }

        private void bPreviewChain_Click(object sender, EventArgs e) {
            RenderWindow rw = new RenderWindow();
            DirectX.DXMain.CreateDevice(RenderWindow.panel);
            string error = DirectX.Shaders.PreviewShaderChain(FramePath, DepthPath);
            if (error == null) {
                rw.ShowDialog();
            } else {
                MessageBox.Show(strings["PreviewChainError"] + "\n" + error, Statics.strings["Error"]);
            }
            rw.Close();
            DirectX.DXMain.CloseDevice();
        }

        private DialogResult saveShaderAs() {
            DialogResult res = SaveShader.ShowDialog();
            if (res == DialogResult.OK) {
                FullFileName = SaveShader.FileName;
                EditingName = FullFileName.Substring(FullFileName.LastIndexOf('\\') + 1);
                saveShader();
            }
            return res;
        }

        private void saveShader() {
            if (FullFileName == null) {
                saveShaderAs();
                return;
            }
            StreamWriter sw = new StreamWriter(File.Open(FullFileName, FileMode.Create));
            sw.WriteLine(rtbTechnique.Text);
            sw.Close();

            ShaderModified = false;
            this.Text = EditingName + " - " + strings["ShaderEditor"];
        }

        private void bShaderNew_Click(object sender, EventArgs e) {
            if (ShaderModified) {
                DialogResult res = MessageBox.Show(strings["SavePrompt"], strings["Save"], MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                if (res == DialogResult.Cancel) {
                    return;
                } else if (res == DialogResult.Yes) {
                    if (FullFileName == null) {
                        if (saveShaderAs() != DialogResult.OK) {
                            return;
                        }
                    } else {
                        saveShader();
                    }
                }
            }
            FullFileName = null;
            EditingName = strings["NewFile"];
            rtbTechnique.Text = "";

            ShaderModified = false;
            this.Text = EditingName + " - " + strings["ShaderEditor"];
            tbMessage.Text = "";
        }

        private void bShaderOpen_Click(object sender, EventArgs e) {
            if (ShaderModified) {
                DialogResult res = MessageBox.Show(strings["SavePrompt"], strings["Save"], MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                if (res == DialogResult.Cancel) {
                    return;
                } else if (res == DialogResult.Yes) {
                    if (FullFileName == null) {
                        if (saveShaderAs() != DialogResult.OK) {
                            return;
                        }
                    } else {
                        saveShader();
                    }
                }
            }
            if (OpenShader.ShowDialog() == DialogResult.OK) {
                FullFileName = OpenShader.FileName;
                EditingName = FullFileName.Substring(FullFileName.LastIndexOf('\\') + 1);
                this.Text = EditingName + " - " + strings["ShaderEditor"];

                StreamReader sr = new StreamReader(File.OpenRead(FullFileName));
                rtbTechnique.Text = sr.ReadToEnd().Trim(new char[] {
                    '\n',
                    '\r'
                });
                sr.Close();

                ShaderModified = false;
                this.Text = EditingName + " - " + strings["ShaderEditor"];
                tbMessage.Text = "";
            }
        }

        private void bShaderSaveAs_Click(object sender, EventArgs e) {
            saveShaderAs();
        }

        private void bShaderSave_Click(object sender, EventArgs e) {
            if (FullFileName == null) {
                saveShaderAs();
            } else {
                saveShader();
            }
        }

        private void rtbTechnique_TextChanged(object sender, EventArgs e) {
            if (!ShaderModified) {
                ShaderModified = true;
                this.Text = EditingName + "* - " + strings["ShaderEditor"];
            }
        }

        private void ShaderEditorForm_FormClosing(object sender, FormClosingEventArgs e) {
            if (ShaderModified) {
                DialogResult res = MessageBox.Show(strings["SavePrompt"], strings["Save"], MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                if (res == DialogResult.Cancel) {
                    e.Cancel = true;
                    return;
                } else if (res == DialogResult.Yes) {
                    if (FullFileName == null) {
                        if (saveShaderAs() != DialogResult.OK) {
                            e.Cancel = true;
                            return;
                        }
                    } else {
                        saveShader();
                    }
                }
            }
            this.Dispose();
        }

        private void bShaderFlags_Click(object sender, EventArgs e) {
            // read current shader flags from code
            UInt32 flags = 0;
            Match m = Regex.Match(rtbTechnique.Text, @".*int[ \t]*mgeflags[ \t]*=[ \t]*[0-9]*.*", RegexOptions.IgnoreCase); // RegexOptions.Singleline | 
            if (m.Success) {
                try {
                    flags = Convert.ToUInt32(Regex.Replace(m.ToString(), @".*int[ \t]*mgeflags[ \t]*=[ \t]*([0-9]*).*", @"$1", RegexOptions.IgnoreCase));
                } catch {
                    MessageBox.Show(strings["CannotReadFlags"], Statics.strings["Error"]);
                    return;
                }
            }
            ShaderFlagsEd shfled = new ShaderFlagsEd();
            shfled.setCheckboxes(flags);
            shfled.parent = this;
            shfled.ShowDialog();
            shfled.Dispose();
        }

        // Shader flags
        // #define SFLAG_NOTINTERIOR      1
        // #define SFLAG_NOTEXTERIOR      2
        // #define SFLAG_NOTINTEXT        4
        // #define SFLAG_NOTUNDERWATER    8
        // #define SFLAG_NOTABOVEWATER    16
        // #define SFLAG_SUNVIS           32
        // #define SFLAG_NOTSUNVIS        64
        public void updateShaderFlags(int flags) {
            // Find "int mgeflags = xx" expression in code and replace it with the new shader flags
            Match m = Regex.Match(rtbTechnique.Text, @"int[ \t]*mgeflags[ \t]*=[ \t]*([0-9]*)", RegexOptions.IgnoreCase);
            if (m.Success) {
                rtbTechnique.Text = Regex.Replace(rtbTechnique.Text, @"int[ \t]*mgeflags[ \t]*=[ \t]*([0-9]*)", @"int mgeflags = " + flags.ToString(), RegexOptions.IgnoreCase);
            } else {
                // if the expression was not found, add a new line
                rtbTechnique.Text = "int mgeflags = " + flags.ToString() + ";" + Environment.NewLine + rtbTechnique.Text;
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e) {
            this.Close();
        }

        private void undoToolStripMenuItem_Click(object sender, EventArgs e) {
            rtbTechnique.Undo();
        }

        private void redoToolStripMenuItem_Click(object sender, EventArgs e) {
            rtbTechnique.Redo();
        }

        private void cutToolStripMenuItem_Click(object sender, EventArgs e) {
            rtbTechnique.Cut();
        }

        private void copyToolStripMenuItem_Click(object sender, EventArgs e) {
            rtbTechnique.Copy();
        }

        private void pasteToolStripMenuItem_Click(object sender, EventArgs e) {
            rtbTechnique.Paste();
        }

        private void selectAllToolStripMenuItem_Click(object sender, EventArgs e) {
            rtbTechnique.SelectAll();
        }

        private void rtbTechnique_KeyPress(object sender, KeyPressEventArgs e) {
            if (e.KeyChar == '\t') {
                rtbTechnique.SelectedText = "    ";
                e.Handled = true;
            }
        }
    }
}
