using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using ArrayList=System.Collections.ArrayList;

namespace MGEgui {
    
    public class MacroEditorForm : Form {
#region FormDesigner
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components=null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if(disposing&&(components!=null)) {
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
        	this.b00 = new System.Windows.Forms.Button();
        	this.b3b = new System.Windows.Forms.Button();
        	this.b3c = new System.Windows.Forms.Button();
        	this.b3d = new System.Windows.Forms.Button();
        	this.b3e = new System.Windows.Forms.Button();
        	this.b3f = new System.Windows.Forms.Button();
        	this.b40 = new System.Windows.Forms.Button();
        	this.b41 = new System.Windows.Forms.Button();
        	this.b42 = new System.Windows.Forms.Button();
        	this.b43 = new System.Windows.Forms.Button();
        	this.b44 = new System.Windows.Forms.Button();
        	this.b57 = new System.Windows.Forms.Button();
        	this.b58 = new System.Windows.Forms.Button();
        	this.bb7 = new System.Windows.Forms.Button();
        	this.b46 = new System.Windows.Forms.Button();
        	this.bc5 = new System.Windows.Forms.Button();
        	this.b29 = new System.Windows.Forms.Button();
        	this.b02 = new System.Windows.Forms.Button();
        	this.b03 = new System.Windows.Forms.Button();
        	this.b04 = new System.Windows.Forms.Button();
        	this.b05 = new System.Windows.Forms.Button();
        	this.b07 = new System.Windows.Forms.Button();
        	this.b08 = new System.Windows.Forms.Button();
        	this.b09 = new System.Windows.Forms.Button();
        	this.b06 = new System.Windows.Forms.Button();
        	this.b0a = new System.Windows.Forms.Button();
        	this.b0b = new System.Windows.Forms.Button();
        	this.b0c = new System.Windows.Forms.Button();
        	this.b0d = new System.Windows.Forms.Button();
        	this.b0e = new System.Windows.Forms.Button();
        	this.bd2 = new System.Windows.Forms.Button();
        	this.bc7 = new System.Windows.Forms.Button();
        	this.bc9 = new System.Windows.Forms.Button();
        	this.bd3 = new System.Windows.Forms.Button();
        	this.bd1 = new System.Windows.Forms.Button();
        	this.bcf = new System.Windows.Forms.Button();
        	this.b0f = new System.Windows.Forms.Button();
        	this.b10 = new System.Windows.Forms.Button();
        	this.b19 = new System.Windows.Forms.Button();
        	this.b1a = new System.Windows.Forms.Button();
        	this.b1b = new System.Windows.Forms.Button();
        	this.b18 = new System.Windows.Forms.Button();
        	this.b17 = new System.Windows.Forms.Button();
        	this.b16 = new System.Windows.Forms.Button();
        	this.b15 = new System.Windows.Forms.Button();
        	this.b14 = new System.Windows.Forms.Button();
        	this.b13 = new System.Windows.Forms.Button();
        	this.b12 = new System.Windows.Forms.Button();
        	this.b11 = new System.Windows.Forms.Button();
        	this.b3a = new System.Windows.Forms.Button();
        	this.b1f = new System.Windows.Forms.Button();
        	this.b20 = new System.Windows.Forms.Button();
        	this.b21 = new System.Windows.Forms.Button();
        	this.b22 = new System.Windows.Forms.Button();
        	this.b23 = new System.Windows.Forms.Button();
        	this.b24 = new System.Windows.Forms.Button();
        	this.b25 = new System.Windows.Forms.Button();
        	this.b26 = new System.Windows.Forms.Button();
        	this.b2b = new System.Windows.Forms.Button();
        	this.b28 = new System.Windows.Forms.Button();
        	this.b27 = new System.Windows.Forms.Button();
        	this.b1e = new System.Windows.Forms.Button();
        	this.b1c = new System.Windows.Forms.Button();
        	this.b2a = new System.Windows.Forms.Button();
        	this.b2c = new System.Windows.Forms.Button();
        	this.b2d = new System.Windows.Forms.Button();
        	this.b2e = new System.Windows.Forms.Button();
        	this.b2f = new System.Windows.Forms.Button();
        	this.b30 = new System.Windows.Forms.Button();
        	this.b31 = new System.Windows.Forms.Button();
        	this.b32 = new System.Windows.Forms.Button();
        	this.b33 = new System.Windows.Forms.Button();
        	this.b36 = new System.Windows.Forms.Button();
        	this.b35 = new System.Windows.Forms.Button();
        	this.b34 = new System.Windows.Forms.Button();
        	this.b56 = new System.Windows.Forms.Button();
        	this.bc8 = new System.Windows.Forms.Button();
        	this.b1d = new System.Windows.Forms.Button();
        	this.bdb = new System.Windows.Forms.Button();
        	this.b38 = new System.Windows.Forms.Button();
        	this.b9d = new System.Windows.Forms.Button();
        	this.bdd = new System.Windows.Forms.Button();
        	this.bdc = new System.Windows.Forms.Button();
        	this.bb8 = new System.Windows.Forms.Button();
        	this.b39 = new System.Windows.Forms.Button();
        	this.bcd = new System.Windows.Forms.Button();
        	this.bcb = new System.Windows.Forms.Button();
        	this.bd0 = new System.Windows.Forms.Button();
        	this.b45 = new System.Windows.Forms.Button();
        	this.bb5 = new System.Windows.Forms.Button();
        	this.b37 = new System.Windows.Forms.Button();
        	this.b4a = new System.Windows.Forms.Button();
        	this.b47 = new System.Windows.Forms.Button();
        	this.b48 = new System.Windows.Forms.Button();
        	this.b49 = new System.Windows.Forms.Button();
        	this.b4e = new System.Windows.Forms.Button();
        	this.b4b = new System.Windows.Forms.Button();
        	this.b4f = new System.Windows.Forms.Button();
        	this.b52 = new System.Windows.Forms.Button();
        	this.b4d = new System.Windows.Forms.Button();
        	this.b4c = new System.Windows.Forms.Button();
        	this.b51 = new System.Windows.Forms.Button();
        	this.b50 = new System.Windows.Forms.Button();
        	this.b9c = new System.Windows.Forms.Button();
        	this.b53 = new System.Windows.Forms.Button();
        	this.rbTap = new System.Windows.Forms.RadioButton();
        	this.rbUp = new System.Windows.Forms.RadioButton();
        	this.rbDown = new System.Windows.Forms.RadioButton();
        	this.bSave = new System.Windows.Forms.Button();
        	this.bCancel = new System.Windows.Forms.Button();
        	this.cbMacroType = new System.Windows.Forms.ComboBox();
        	this.DudMenu = new System.Windows.Forms.ContextMenu();
        	this.lMacroType = new System.Windows.Forms.Label();
        	this.cbFunction = new System.Windows.Forms.ComboBox();
        	this.lMacroFunction = new System.Windows.Forms.Label();
        	this.cbTrigger = new System.Windows.Forms.ComboBox();
        	this.lTriggerNum = new System.Windows.Forms.Label();
        	this.tbTimeDelay = new System.Windows.Forms.TextBox();
        	this.lTriggerDelay = new System.Windows.Forms.Label();
        	this.tbCLen = new System.Windows.Forms.TextBox();
        	this.lCommandLength = new System.Windows.Forms.Label();
        	this.tbCDesc = new System.Windows.Forms.TextBox();
        	this.lCommandDesc = new System.Windows.Forms.Label();
        	this.bClear = new System.Windows.Forms.Button();
        	this.cbTriggerEnabled = new System.Windows.Forms.CheckBox();
        	this.b100 = new System.Windows.Forms.Button();
        	this.b101 = new System.Windows.Forms.Button();
        	this.b102 = new System.Windows.Forms.Button();
        	this.b103 = new System.Windows.Forms.Button();
        	this.b104 = new System.Windows.Forms.Button();
        	this.b105 = new System.Windows.Forms.Button();
        	this.b106 = new System.Windows.Forms.Button();
        	this.b107 = new System.Windows.Forms.Button();
        	this.b108 = new System.Windows.Forms.Button();
        	this.b109 = new System.Windows.Forms.Button();
        	this.SuspendLayout();
        	// 
        	// b00
        	// 
        	this.b00.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b00.Location = new System.Drawing.Point(12, 12);
        	this.b00.Name = "b00";
        	this.b00.Size = new System.Drawing.Size(32, 32);
        	this.b00.TabIndex = 1;
        	this.b00.Text = "Esc";
        	this.b00.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b3b
        	// 
        	this.b3b.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b3b.Location = new System.Drawing.Point(76, 12);
        	this.b3b.Name = "b3b";
        	this.b3b.Size = new System.Drawing.Size(32, 32);
        	this.b3b.TabIndex = 2;
        	this.b3b.Text = "F1";
        	this.b3b.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b3c
        	// 
        	this.b3c.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b3c.Location = new System.Drawing.Point(108, 12);
        	this.b3c.Name = "b3c";
        	this.b3c.Size = new System.Drawing.Size(32, 32);
        	this.b3c.TabIndex = 3;
        	this.b3c.Text = "F2";
        	this.b3c.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b3d
        	// 
        	this.b3d.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b3d.Location = new System.Drawing.Point(140, 12);
        	this.b3d.Name = "b3d";
        	this.b3d.Size = new System.Drawing.Size(32, 32);
        	this.b3d.TabIndex = 4;
        	this.b3d.Text = "F3";
        	this.b3d.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b3e
        	// 
        	this.b3e.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b3e.Location = new System.Drawing.Point(172, 12);
        	this.b3e.Name = "b3e";
        	this.b3e.Size = new System.Drawing.Size(32, 32);
        	this.b3e.TabIndex = 5;
        	this.b3e.Text = "F4";
        	this.b3e.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b3f
        	// 
        	this.b3f.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b3f.Location = new System.Drawing.Point(220, 12);
        	this.b3f.Name = "b3f";
        	this.b3f.Size = new System.Drawing.Size(32, 32);
        	this.b3f.TabIndex = 6;
        	this.b3f.Text = "F5";
        	this.b3f.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b40
        	// 
        	this.b40.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b40.Location = new System.Drawing.Point(252, 12);
        	this.b40.Name = "b40";
        	this.b40.Size = new System.Drawing.Size(32, 32);
        	this.b40.TabIndex = 7;
        	this.b40.Text = "F6";
        	this.b40.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b41
        	// 
        	this.b41.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b41.Location = new System.Drawing.Point(284, 12);
        	this.b41.Name = "b41";
        	this.b41.Size = new System.Drawing.Size(32, 32);
        	this.b41.TabIndex = 8;
        	this.b41.Text = "F7";
        	this.b41.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b42
        	// 
        	this.b42.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b42.Location = new System.Drawing.Point(316, 12);
        	this.b42.Name = "b42";
        	this.b42.Size = new System.Drawing.Size(32, 32);
        	this.b42.TabIndex = 9;
        	this.b42.Text = "F8";
        	this.b42.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b43
        	// 
        	this.b43.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b43.Location = new System.Drawing.Point(364, 12);
        	this.b43.Name = "b43";
        	this.b43.Size = new System.Drawing.Size(32, 32);
        	this.b43.TabIndex = 10;
        	this.b43.Text = "F9";
        	this.b43.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b44
        	// 
        	this.b44.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b44.Location = new System.Drawing.Point(396, 12);
        	this.b44.Name = "b44";
        	this.b44.Size = new System.Drawing.Size(32, 32);
        	this.b44.TabIndex = 11;
        	this.b44.Text = "F10";
        	this.b44.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b57
        	// 
        	this.b57.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b57.Location = new System.Drawing.Point(428, 12);
        	this.b57.Name = "b57";
        	this.b57.Size = new System.Drawing.Size(32, 32);
        	this.b57.TabIndex = 12;
        	this.b57.Text = "F11";
        	this.b57.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b58
        	// 
        	this.b58.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b58.Location = new System.Drawing.Point(460, 12);
        	this.b58.Name = "b58";
        	this.b58.Size = new System.Drawing.Size(32, 32);
        	this.b58.TabIndex = 13;
        	this.b58.Text = "F12";
        	this.b58.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bb7
        	// 
        	this.bb7.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.bb7.Location = new System.Drawing.Point(508, 12);
        	this.bb7.Name = "bb7";
        	this.bb7.Size = new System.Drawing.Size(32, 32);
        	this.bb7.TabIndex = 76;
        	this.bb7.Text = "Prt Scr";
        	this.bb7.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b46
        	// 
        	this.b46.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.b46.Location = new System.Drawing.Point(540, 12);
        	this.b46.Name = "b46";
        	this.b46.Size = new System.Drawing.Size(32, 32);
        	this.b46.TabIndex = 77;
        	this.b46.Text = "Scr Lck";
        	this.b46.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bc5
        	// 
        	this.bc5.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.5F);
        	this.bc5.Location = new System.Drawing.Point(572, 12);
        	this.bc5.Name = "bc5";
        	this.bc5.Size = new System.Drawing.Size(32, 32);
        	this.bc5.TabIndex = 78;
        	this.bc5.Text = "Ps";
        	this.bc5.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b29
        	// 
        	this.b29.Location = new System.Drawing.Point(12, 60);
        	this.b29.Name = "b29";
        	this.b29.Size = new System.Drawing.Size(32, 32);
        	this.b29.TabIndex = 14;
        	this.b29.Text = "`";
        	this.b29.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b02
        	// 
        	this.b02.Location = new System.Drawing.Point(44, 60);
        	this.b02.Name = "b02";
        	this.b02.Size = new System.Drawing.Size(32, 32);
        	this.b02.TabIndex = 15;
        	this.b02.Text = "1";
        	this.b02.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b03
        	// 
        	this.b03.Location = new System.Drawing.Point(76, 60);
        	this.b03.Name = "b03";
        	this.b03.Size = new System.Drawing.Size(32, 32);
        	this.b03.TabIndex = 16;
        	this.b03.Text = "2";
        	this.b03.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b04
        	// 
        	this.b04.Location = new System.Drawing.Point(108, 60);
        	this.b04.Name = "b04";
        	this.b04.Size = new System.Drawing.Size(32, 32);
        	this.b04.TabIndex = 17;
        	this.b04.Text = "3";
        	this.b04.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b05
        	// 
        	this.b05.Location = new System.Drawing.Point(140, 60);
        	this.b05.Name = "b05";
        	this.b05.Size = new System.Drawing.Size(32, 32);
        	this.b05.TabIndex = 18;
        	this.b05.Text = "4";
        	this.b05.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b07
        	// 
        	this.b07.Location = new System.Drawing.Point(204, 60);
        	this.b07.Name = "b07";
        	this.b07.Size = new System.Drawing.Size(32, 32);
        	this.b07.TabIndex = 20;
        	this.b07.Text = "6";
        	this.b07.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b08
        	// 
        	this.b08.Location = new System.Drawing.Point(236, 60);
        	this.b08.Name = "b08";
        	this.b08.Size = new System.Drawing.Size(32, 32);
        	this.b08.TabIndex = 21;
        	this.b08.Text = "7";
        	this.b08.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b09
        	// 
        	this.b09.Location = new System.Drawing.Point(268, 60);
        	this.b09.Name = "b09";
        	this.b09.Size = new System.Drawing.Size(32, 32);
        	this.b09.TabIndex = 22;
        	this.b09.Text = "8";
        	this.b09.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b06
        	// 
        	this.b06.Location = new System.Drawing.Point(172, 60);
        	this.b06.Name = "b06";
        	this.b06.Size = new System.Drawing.Size(32, 32);
        	this.b06.TabIndex = 19;
        	this.b06.Text = "5";
        	this.b06.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b0a
        	// 
        	this.b0a.Location = new System.Drawing.Point(300, 60);
        	this.b0a.Name = "b0a";
        	this.b0a.Size = new System.Drawing.Size(32, 32);
        	this.b0a.TabIndex = 23;
        	this.b0a.Text = "9";
        	this.b0a.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b0b
        	// 
        	this.b0b.Location = new System.Drawing.Point(332, 60);
        	this.b0b.Name = "b0b";
        	this.b0b.Size = new System.Drawing.Size(32, 32);
        	this.b0b.TabIndex = 24;
        	this.b0b.Text = "0";
        	this.b0b.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b0c
        	// 
        	this.b0c.Location = new System.Drawing.Point(364, 60);
        	this.b0c.Name = "b0c";
        	this.b0c.Size = new System.Drawing.Size(32, 32);
        	this.b0c.TabIndex = 25;
        	this.b0c.Text = "-";
        	this.b0c.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b0d
        	// 
        	this.b0d.Location = new System.Drawing.Point(396, 60);
        	this.b0d.Name = "b0d";
        	this.b0d.Size = new System.Drawing.Size(32, 32);
        	this.b0d.TabIndex = 26;
        	this.b0d.Text = "=";
        	this.b0d.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b0e
        	// 
        	this.b0e.Location = new System.Drawing.Point(428, 60);
        	this.b0e.Name = "b0e";
        	this.b0e.Size = new System.Drawing.Size(64, 32);
        	this.b0e.TabIndex = 27;
        	this.b0e.Text = "<-----";
        	this.b0e.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bd2
        	// 
        	this.bd2.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bd2.Location = new System.Drawing.Point(508, 60);
        	this.bd2.Name = "bd2";
        	this.bd2.Size = new System.Drawing.Size(32, 32);
        	this.bd2.TabIndex = 79;
        	this.bd2.Text = "Ins";
        	this.bd2.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bc7
        	// 
        	this.bc7.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bc7.Location = new System.Drawing.Point(540, 60);
        	this.bc7.Name = "bc7";
        	this.bc7.Size = new System.Drawing.Size(32, 32);
        	this.bc7.TabIndex = 80;
        	this.bc7.Text = "Hm";
        	this.bc7.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bc9
        	// 
        	this.bc9.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bc9.Location = new System.Drawing.Point(572, 60);
        	this.bc9.Name = "bc9";
        	this.bc9.Size = new System.Drawing.Size(32, 32);
        	this.bc9.TabIndex = 81;
        	this.bc9.Text = "Pg Up";
        	this.bc9.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bd3
        	// 
        	this.bd3.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bd3.Location = new System.Drawing.Point(508, 92);
        	this.bd3.Name = "bd3";
        	this.bd3.Size = new System.Drawing.Size(32, 32);
        	this.bd3.TabIndex = 82;
        	this.bd3.Text = "Del";
        	this.bd3.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bd1
        	// 
        	this.bd1.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bd1.Location = new System.Drawing.Point(572, 92);
        	this.bd1.Name = "bd1";
        	this.bd1.Size = new System.Drawing.Size(32, 32);
        	this.bd1.TabIndex = 84;
        	this.bd1.Text = "Pg Dn";
        	this.bd1.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bcf
        	// 
        	this.bcf.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bcf.Location = new System.Drawing.Point(540, 92);
        	this.bcf.Name = "bcf";
        	this.bcf.Size = new System.Drawing.Size(32, 32);
        	this.bcf.TabIndex = 83;
        	this.bcf.Text = "End";
        	this.bcf.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b0f
        	// 
        	this.b0f.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b0f.Location = new System.Drawing.Point(12, 92);
        	this.b0f.Name = "b0f";
        	this.b0f.Size = new System.Drawing.Size(48, 32);
        	this.b0f.TabIndex = 28;
        	this.b0f.Text = "Tab";
        	this.b0f.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b10
        	// 
        	this.b10.Location = new System.Drawing.Point(60, 92);
        	this.b10.Name = "b10";
        	this.b10.Size = new System.Drawing.Size(32, 32);
        	this.b10.TabIndex = 29;
        	this.b10.Text = "q";
        	this.b10.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b19
        	// 
        	this.b19.Location = new System.Drawing.Point(348, 92);
        	this.b19.Name = "b19";
        	this.b19.Size = new System.Drawing.Size(32, 32);
        	this.b19.TabIndex = 38;
        	this.b19.Text = "p";
        	this.b19.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b1a
        	// 
        	this.b1a.Location = new System.Drawing.Point(380, 92);
        	this.b1a.Name = "b1a";
        	this.b1a.Size = new System.Drawing.Size(32, 32);
        	this.b1a.TabIndex = 39;
        	this.b1a.Text = "[";
        	this.b1a.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b1b
        	// 
        	this.b1b.Location = new System.Drawing.Point(412, 92);
        	this.b1b.Name = "b1b";
        	this.b1b.Size = new System.Drawing.Size(32, 32);
        	this.b1b.TabIndex = 40;
        	this.b1b.Text = "]";
        	this.b1b.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b18
        	// 
        	this.b18.Location = new System.Drawing.Point(316, 92);
        	this.b18.Name = "b18";
        	this.b18.Size = new System.Drawing.Size(32, 32);
        	this.b18.TabIndex = 37;
        	this.b18.Text = "o";
        	this.b18.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b17
        	// 
        	this.b17.Location = new System.Drawing.Point(284, 92);
        	this.b17.Name = "b17";
        	this.b17.Size = new System.Drawing.Size(32, 32);
        	this.b17.TabIndex = 36;
        	this.b17.Text = "i";
        	this.b17.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b16
        	// 
        	this.b16.Location = new System.Drawing.Point(252, 92);
        	this.b16.Name = "b16";
        	this.b16.Size = new System.Drawing.Size(32, 32);
        	this.b16.TabIndex = 35;
        	this.b16.Text = "u";
        	this.b16.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b15
        	// 
        	this.b15.Location = new System.Drawing.Point(220, 92);
        	this.b15.Name = "b15";
        	this.b15.Size = new System.Drawing.Size(32, 32);
        	this.b15.TabIndex = 34;
        	this.b15.Text = "y";
        	this.b15.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b14
        	// 
        	this.b14.Location = new System.Drawing.Point(188, 92);
        	this.b14.Name = "b14";
        	this.b14.Size = new System.Drawing.Size(32, 32);
        	this.b14.TabIndex = 33;
        	this.b14.Text = "t";
        	this.b14.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b13
        	// 
        	this.b13.Location = new System.Drawing.Point(156, 92);
        	this.b13.Name = "b13";
        	this.b13.Size = new System.Drawing.Size(32, 32);
        	this.b13.TabIndex = 32;
        	this.b13.Text = "r";
        	this.b13.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b12
        	// 
        	this.b12.Location = new System.Drawing.Point(124, 92);
        	this.b12.Name = "b12";
        	this.b12.Size = new System.Drawing.Size(32, 32);
        	this.b12.TabIndex = 31;
        	this.b12.Text = "e";
        	this.b12.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b11
        	// 
        	this.b11.Location = new System.Drawing.Point(92, 92);
        	this.b11.Name = "b11";
        	this.b11.Size = new System.Drawing.Size(32, 32);
        	this.b11.TabIndex = 30;
        	this.b11.Text = "w";
        	this.b11.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b3a
        	// 
        	this.b3a.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b3a.Location = new System.Drawing.Point(12, 124);
        	this.b3a.Name = "b3a";
        	this.b3a.Size = new System.Drawing.Size(56, 32);
        	this.b3a.TabIndex = 41;
        	this.b3a.Text = "Caps Lock";
        	this.b3a.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b1f
        	// 
        	this.b1f.Location = new System.Drawing.Point(100, 124);
        	this.b1f.Name = "b1f";
        	this.b1f.Size = new System.Drawing.Size(32, 32);
        	this.b1f.TabIndex = 43;
        	this.b1f.Text = "s";
        	this.b1f.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b20
        	// 
        	this.b20.Location = new System.Drawing.Point(132, 124);
        	this.b20.Name = "b20";
        	this.b20.Size = new System.Drawing.Size(32, 32);
        	this.b20.TabIndex = 44;
        	this.b20.Text = "d";
        	this.b20.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b21
        	// 
        	this.b21.Location = new System.Drawing.Point(164, 124);
        	this.b21.Name = "b21";
        	this.b21.Size = new System.Drawing.Size(32, 32);
        	this.b21.TabIndex = 45;
        	this.b21.Text = "f";
        	this.b21.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b22
        	// 
        	this.b22.Location = new System.Drawing.Point(196, 124);
        	this.b22.Name = "b22";
        	this.b22.Size = new System.Drawing.Size(32, 32);
        	this.b22.TabIndex = 46;
        	this.b22.Text = "g";
        	this.b22.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b23
        	// 
        	this.b23.Location = new System.Drawing.Point(228, 124);
        	this.b23.Name = "b23";
        	this.b23.Size = new System.Drawing.Size(32, 32);
        	this.b23.TabIndex = 47;
        	this.b23.Text = "h";
        	this.b23.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b24
        	// 
        	this.b24.Location = new System.Drawing.Point(260, 124);
        	this.b24.Name = "b24";
        	this.b24.Size = new System.Drawing.Size(32, 32);
        	this.b24.TabIndex = 48;
        	this.b24.Text = "j";
        	this.b24.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b25
        	// 
        	this.b25.Location = new System.Drawing.Point(292, 124);
        	this.b25.Name = "b25";
        	this.b25.Size = new System.Drawing.Size(32, 32);
        	this.b25.TabIndex = 49;
        	this.b25.Text = "k";
        	this.b25.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b26
        	// 
        	this.b26.Location = new System.Drawing.Point(324, 124);
        	this.b26.Name = "b26";
        	this.b26.Size = new System.Drawing.Size(32, 32);
        	this.b26.TabIndex = 50;
        	this.b26.Text = "l";
        	this.b26.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b2b
        	// 
        	this.b2b.Location = new System.Drawing.Point(420, 124);
        	this.b2b.Name = "b2b";
        	this.b2b.Size = new System.Drawing.Size(32, 32);
        	this.b2b.TabIndex = 53;
        	this.b2b.Text = "#";
        	this.b2b.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b28
        	// 
        	this.b28.Location = new System.Drawing.Point(388, 124);
        	this.b28.Name = "b28";
        	this.b28.Size = new System.Drawing.Size(32, 32);
        	this.b28.TabIndex = 52;
        	this.b28.Text = "\'";
        	this.b28.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b27
        	// 
        	this.b27.Location = new System.Drawing.Point(356, 124);
        	this.b27.Name = "b27";
        	this.b27.Size = new System.Drawing.Size(32, 32);
        	this.b27.TabIndex = 51;
        	this.b27.Text = ";";
        	this.b27.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b1e
        	// 
        	this.b1e.Location = new System.Drawing.Point(68, 124);
        	this.b1e.Name = "b1e";
        	this.b1e.Size = new System.Drawing.Size(32, 32);
        	this.b1e.TabIndex = 42;
        	this.b1e.Text = "a";
        	this.b1e.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b1c
        	// 
        	this.b1c.Location = new System.Drawing.Point(452, 92);
        	this.b1c.Name = "b1c";
        	this.b1c.Size = new System.Drawing.Size(40, 64);
        	this.b1c.TabIndex = 54;
        	this.b1c.Text = "Ret";
        	this.b1c.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b2a
        	// 
        	this.b2a.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b2a.Location = new System.Drawing.Point(12, 156);
        	this.b2a.Name = "b2a";
        	this.b2a.Size = new System.Drawing.Size(40, 32);
        	this.b2a.TabIndex = 55;
        	this.b2a.Text = "L Shift";
        	this.b2a.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b2c
        	// 
        	this.b2c.Location = new System.Drawing.Point(84, 156);
        	this.b2c.Name = "b2c";
        	this.b2c.Size = new System.Drawing.Size(32, 32);
        	this.b2c.TabIndex = 57;
        	this.b2c.Text = "z";
        	this.b2c.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b2d
        	// 
        	this.b2d.Location = new System.Drawing.Point(116, 156);
        	this.b2d.Name = "b2d";
        	this.b2d.Size = new System.Drawing.Size(32, 32);
        	this.b2d.TabIndex = 58;
        	this.b2d.Text = "x";
        	this.b2d.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b2e
        	// 
        	this.b2e.Location = new System.Drawing.Point(148, 156);
        	this.b2e.Name = "b2e";
        	this.b2e.Size = new System.Drawing.Size(32, 32);
        	this.b2e.TabIndex = 59;
        	this.b2e.Text = "c";
        	this.b2e.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b2f
        	// 
        	this.b2f.Location = new System.Drawing.Point(180, 156);
        	this.b2f.Name = "b2f";
        	this.b2f.Size = new System.Drawing.Size(32, 32);
        	this.b2f.TabIndex = 60;
        	this.b2f.Text = "v";
        	this.b2f.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b30
        	// 
        	this.b30.Location = new System.Drawing.Point(212, 156);
        	this.b30.Name = "b30";
        	this.b30.Size = new System.Drawing.Size(32, 32);
        	this.b30.TabIndex = 61;
        	this.b30.Text = "b";
        	this.b30.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b31
        	// 
        	this.b31.Location = new System.Drawing.Point(244, 156);
        	this.b31.Name = "b31";
        	this.b31.Size = new System.Drawing.Size(32, 32);
        	this.b31.TabIndex = 62;
        	this.b31.Text = "n";
        	this.b31.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b32
        	// 
        	this.b32.Location = new System.Drawing.Point(276, 156);
        	this.b32.Name = "b32";
        	this.b32.Size = new System.Drawing.Size(32, 32);
        	this.b32.TabIndex = 63;
        	this.b32.Text = "m";
        	this.b32.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b33
        	// 
        	this.b33.Location = new System.Drawing.Point(308, 156);
        	this.b33.Name = "b33";
        	this.b33.Size = new System.Drawing.Size(32, 32);
        	this.b33.TabIndex = 64;
        	this.b33.Text = ",";
        	this.b33.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b36
        	// 
        	this.b36.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b36.Location = new System.Drawing.Point(404, 156);
        	this.b36.Name = "b36";
        	this.b36.Size = new System.Drawing.Size(88, 32);
        	this.b36.TabIndex = 67;
        	this.b36.Text = "R Shift";
        	this.b36.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b35
        	// 
        	this.b35.Location = new System.Drawing.Point(372, 156);
        	this.b35.Name = "b35";
        	this.b35.Size = new System.Drawing.Size(32, 32);
        	this.b35.TabIndex = 66;
        	this.b35.Text = "/";
        	this.b35.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b34
        	// 
        	this.b34.Location = new System.Drawing.Point(340, 156);
        	this.b34.Name = "b34";
        	this.b34.Size = new System.Drawing.Size(32, 32);
        	this.b34.TabIndex = 65;
        	this.b34.Text = ".";
        	this.b34.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b56
        	// 
        	this.b56.Location = new System.Drawing.Point(52, 156);
        	this.b56.Name = "b56";
        	this.b56.Size = new System.Drawing.Size(32, 32);
        	this.b56.TabIndex = 56;
        	this.b56.Text = "\\";
        	this.b56.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bc8
        	// 
        	this.bc8.Location = new System.Drawing.Point(540, 156);
        	this.bc8.Name = "bc8";
        	this.bc8.Size = new System.Drawing.Size(32, 32);
        	this.bc8.TabIndex = 85;
        	this.bc8.Text = "^";
        	this.bc8.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b1d
        	// 
        	this.b1d.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b1d.Location = new System.Drawing.Point(12, 188);
        	this.b1d.Name = "b1d";
        	this.b1d.Size = new System.Drawing.Size(40, 32);
        	this.b1d.TabIndex = 68;
        	this.b1d.Text = "L Ctrl";
        	this.b1d.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bdb
        	// 
        	this.bdb.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bdb.Location = new System.Drawing.Point(52, 188);
        	this.bdb.Name = "bdb";
        	this.bdb.Size = new System.Drawing.Size(40, 32);
        	this.bdb.TabIndex = 69;
        	this.bdb.Text = "L Win";
        	this.bdb.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b38
        	// 
        	this.b38.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b38.Location = new System.Drawing.Point(92, 188);
        	this.b38.Name = "b38";
        	this.b38.Size = new System.Drawing.Size(40, 32);
        	this.b38.TabIndex = 70;
        	this.b38.Text = "L Alt";
        	this.b38.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b9d
        	// 
        	this.b9d.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b9d.Location = new System.Drawing.Point(452, 188);
        	this.b9d.Name = "b9d";
        	this.b9d.Size = new System.Drawing.Size(40, 32);
        	this.b9d.TabIndex = 75;
        	this.b9d.Text = "R Ctrl";
        	this.b9d.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bdd
        	// 
        	this.bdd.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bdd.Location = new System.Drawing.Point(412, 188);
        	this.bdd.Name = "bdd";
        	this.bdd.Size = new System.Drawing.Size(40, 32);
        	this.bdd.TabIndex = 74;
        	this.bdd.Text = "App";
        	this.bdd.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bdc
        	// 
        	this.bdc.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bdc.Location = new System.Drawing.Point(372, 188);
        	this.bdc.Name = "bdc";
        	this.bdc.Size = new System.Drawing.Size(40, 32);
        	this.bdc.TabIndex = 73;
        	this.bdc.Text = "R Win";
        	this.bdc.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bb8
        	// 
        	this.bb8.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.bb8.Location = new System.Drawing.Point(332, 188);
        	this.bb8.Name = "bb8";
        	this.bb8.Size = new System.Drawing.Size(40, 32);
        	this.bb8.TabIndex = 72;
        	this.bb8.Text = "R Alt";
        	this.bb8.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b39
        	// 
        	this.b39.Location = new System.Drawing.Point(132, 188);
        	this.b39.Name = "b39";
        	this.b39.Size = new System.Drawing.Size(200, 32);
        	this.b39.TabIndex = 71;
        	this.b39.Text = "Space";
        	this.b39.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bcd
        	// 
        	this.bcd.Location = new System.Drawing.Point(572, 188);
        	this.bcd.Name = "bcd";
        	this.bcd.Size = new System.Drawing.Size(32, 32);
        	this.bcd.TabIndex = 88;
        	this.bcd.Text = ">";
        	this.bcd.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bcb
        	// 
        	this.bcb.Location = new System.Drawing.Point(508, 188);
        	this.bcb.Name = "bcb";
        	this.bcb.Size = new System.Drawing.Size(32, 32);
        	this.bcb.TabIndex = 86;
        	this.bcb.Text = "<";
        	this.bcb.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bd0
        	// 
        	this.bd0.Location = new System.Drawing.Point(540, 188);
        	this.bd0.Name = "bd0";
        	this.bd0.Size = new System.Drawing.Size(32, 32);
        	this.bd0.TabIndex = 87;
        	this.bd0.Text = "v";
        	this.bd0.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b45
        	// 
        	this.b45.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b45.Location = new System.Drawing.Point(620, 60);
        	this.b45.Name = "b45";
        	this.b45.Size = new System.Drawing.Size(32, 32);
        	this.b45.TabIndex = 89;
        	this.b45.Text = "NmLck";
        	this.b45.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// bb5
        	// 
        	this.bb5.Location = new System.Drawing.Point(652, 60);
        	this.bb5.Name = "bb5";
        	this.bb5.Size = new System.Drawing.Size(32, 32);
        	this.bb5.TabIndex = 90;
        	this.bb5.Text = "/";
        	this.bb5.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b37
        	// 
        	this.b37.Location = new System.Drawing.Point(684, 60);
        	this.b37.Name = "b37";
        	this.b37.Size = new System.Drawing.Size(32, 32);
        	this.b37.TabIndex = 91;
        	this.b37.Text = "*";
        	this.b37.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b4a
        	// 
        	this.b4a.Location = new System.Drawing.Point(716, 60);
        	this.b4a.Name = "b4a";
        	this.b4a.Size = new System.Drawing.Size(32, 32);
        	this.b4a.TabIndex = 92;
        	this.b4a.Text = "-";
        	this.b4a.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b47
        	// 
        	this.b47.Location = new System.Drawing.Point(620, 92);
        	this.b47.Name = "b47";
        	this.b47.Size = new System.Drawing.Size(32, 32);
        	this.b47.TabIndex = 93;
        	this.b47.Text = "7";
        	this.b47.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b48
        	// 
        	this.b48.Location = new System.Drawing.Point(652, 92);
        	this.b48.Name = "b48";
        	this.b48.Size = new System.Drawing.Size(32, 32);
        	this.b48.TabIndex = 94;
        	this.b48.Text = "8";
        	this.b48.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b49
        	// 
        	this.b49.Location = new System.Drawing.Point(684, 92);
        	this.b49.Name = "b49";
        	this.b49.Size = new System.Drawing.Size(32, 32);
        	this.b49.TabIndex = 95;
        	this.b49.Text = "9";
        	this.b49.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b4e
        	// 
        	this.b4e.Location = new System.Drawing.Point(716, 92);
        	this.b4e.Name = "b4e";
        	this.b4e.Size = new System.Drawing.Size(32, 64);
        	this.b4e.TabIndex = 99;
        	this.b4e.Text = "+";
        	this.b4e.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b4b
        	// 
        	this.b4b.Location = new System.Drawing.Point(620, 124);
        	this.b4b.Name = "b4b";
        	this.b4b.Size = new System.Drawing.Size(32, 32);
        	this.b4b.TabIndex = 96;
        	this.b4b.Text = "4";
        	this.b4b.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b4f
        	// 
        	this.b4f.Location = new System.Drawing.Point(620, 156);
        	this.b4f.Name = "b4f";
        	this.b4f.Size = new System.Drawing.Size(32, 32);
        	this.b4f.TabIndex = 100;
        	this.b4f.Text = "1";
        	this.b4f.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b52
        	// 
        	this.b52.Location = new System.Drawing.Point(620, 188);
        	this.b52.Name = "b52";
        	this.b52.Size = new System.Drawing.Size(64, 32);
        	this.b52.TabIndex = 103;
        	this.b52.Text = "0";
        	this.b52.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b4d
        	// 
        	this.b4d.Location = new System.Drawing.Point(684, 124);
        	this.b4d.Name = "b4d";
        	this.b4d.Size = new System.Drawing.Size(32, 32);
        	this.b4d.TabIndex = 98;
        	this.b4d.Text = "6";
        	this.b4d.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b4c
        	// 
        	this.b4c.Location = new System.Drawing.Point(652, 124);
        	this.b4c.Name = "b4c";
        	this.b4c.Size = new System.Drawing.Size(32, 32);
        	this.b4c.TabIndex = 97;
        	this.b4c.Text = "5";
        	this.b4c.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b51
        	// 
        	this.b51.Location = new System.Drawing.Point(684, 156);
        	this.b51.Name = "b51";
        	this.b51.Size = new System.Drawing.Size(32, 32);
        	this.b51.TabIndex = 102;
        	this.b51.Text = "3";
        	this.b51.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b50
        	// 
        	this.b50.Location = new System.Drawing.Point(652, 156);
        	this.b50.Name = "b50";
        	this.b50.Size = new System.Drawing.Size(32, 32);
        	this.b50.TabIndex = 101;
        	this.b50.Text = "2";
        	this.b50.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b9c
        	// 
        	this.b9c.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b9c.Location = new System.Drawing.Point(716, 156);
        	this.b9c.Name = "b9c";
        	this.b9c.Size = new System.Drawing.Size(32, 64);
        	this.b9c.TabIndex = 105;
        	this.b9c.Text = "Entr";
        	this.b9c.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b53
        	// 
        	this.b53.Location = new System.Drawing.Point(684, 188);
        	this.b53.Name = "b53";
        	this.b53.Size = new System.Drawing.Size(32, 32);
        	this.b53.TabIndex = 104;
        	this.b53.Text = ".";
        	this.b53.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// rbTap
        	// 
        	this.rbTap.Location = new System.Drawing.Point(12, 264);
        	this.rbTap.Name = "rbTap";
        	this.rbTap.Size = new System.Drawing.Size(50, 17);
        	this.rbTap.TabIndex = 116;
        	this.rbTap.Text = "Tap";
        	// 
        	// rbUp
        	// 
        	this.rbUp.Location = new System.Drawing.Point(12, 310);
        	this.rbUp.Name = "rbUp";
        	this.rbUp.Size = new System.Drawing.Size(45, 17);
        	this.rbUp.TabIndex = 118;
        	this.rbUp.Text = "Up";
        	// 
        	// rbDown
        	// 
        	this.rbDown.Location = new System.Drawing.Point(12, 287);
        	this.rbDown.Name = "rbDown";
        	this.rbDown.Size = new System.Drawing.Size(59, 17);
        	this.rbDown.TabIndex = 117;
        	this.rbDown.Text = "Down";
        	// 
        	// bSave
        	// 
        	this.bSave.Location = new System.Drawing.Point(702, 267);
        	this.bSave.Name = "bSave";
        	this.bSave.Size = new System.Drawing.Size(50, 23);
        	this.bSave.TabIndex = 126;
        	this.bSave.Text = "Save";
        	this.bSave.Click += new System.EventHandler(this.bSave_Click);
        	// 
        	// bCancel
        	// 
        	this.bCancel.Location = new System.Drawing.Point(702, 296);
        	this.bCancel.Name = "bCancel";
        	this.bCancel.Size = new System.Drawing.Size(50, 23);
        	this.bCancel.TabIndex = 127;
        	this.bCancel.Text = "Cancel";
        	this.bCancel.Click += new System.EventHandler(this.bCancel_Click);
        	// 
        	// cbMacroType
        	// 
        	this.cbMacroType.ContextMenu = this.DudMenu;
        	this.cbMacroType.Items.AddRange(new object[] {
        	        	        	"Unused",
        	        	        	"Console1",
        	        	        	"Console2",
        	        	        	"Hammer1",
        	        	        	"Hammer2",
        	        	        	"Unhammer",
        	        	        	"AHammer1",
        	        	        	"AHammer2",
        	        	        	"AUnhammer",
        	        	        	"Press1",
        	        	        	"Press2",
        	        	        	"Unpress",
        	        	        	"Start Trigger",
        	        	        	"End Trigger",
        	        	        	"Function"});
        	this.cbMacroType.Location = new System.Drawing.Point(72, 264);
        	this.cbMacroType.Name = "cbMacroType";
        	this.cbMacroType.Size = new System.Drawing.Size(156, 21);
        	this.cbMacroType.TabIndex = 119;
        	this.cbMacroType.Text = "Unused";
        	this.cbMacroType.SelectedIndexChanged += new System.EventHandler(this.cbMacroType_SelectedIndexChanged);
        	this.cbMacroType.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKeypress);
        	// 
        	// lMacroType
        	// 
        	this.lMacroType.AutoSize = true;
        	this.lMacroType.Location = new System.Drawing.Point(234, 268);
        	this.lMacroType.Name = "lMacroType";
        	this.lMacroType.Size = new System.Drawing.Size(60, 13);
        	this.lMacroType.TabIndex = 0;
        	this.lMacroType.Text = "Macro type";
        	// 
        	// cbFunction
        	// 
        	this.cbFunction.Items.AddRange(new object[] {
        	        	        	"See data source"});
        	this.cbFunction.Location = new System.Drawing.Point(72, 291);
        	this.cbFunction.Name = "cbFunction";
        	this.cbFunction.Size = new System.Drawing.Size(156, 21);
        	this.cbFunction.TabIndex = 120;
        	this.cbFunction.Text = "None";
        	// 
        	// lMacroFunction
        	// 
        	this.lMacroFunction.AutoSize = true;
        	this.lMacroFunction.Location = new System.Drawing.Point(234, 294);
        	this.lMacroFunction.Name = "lMacroFunction";
        	this.lMacroFunction.Size = new System.Drawing.Size(48, 13);
        	this.lMacroFunction.TabIndex = 0;
        	this.lMacroFunction.Text = "Function";
        	// 
        	// cbTrigger
        	// 
        	this.cbTrigger.ContextMenu = this.DudMenu;
        	this.cbTrigger.Items.AddRange(new object[] {
        	        	        	"-- trigger--",
        	        	        	"1",
        	        	        	"2",
        	        	        	"3",
        	        	        	"4"});
        	this.cbTrigger.Location = new System.Drawing.Point(309, 266);
        	this.cbTrigger.Name = "cbTrigger";
        	this.cbTrigger.Size = new System.Drawing.Size(72, 21);
        	this.cbTrigger.TabIndex = 121;
        	this.cbTrigger.Text = "-- trigger --";
        	this.cbTrigger.SelectedIndexChanged += new System.EventHandler(this.cbTrigger_SelectedIndexChanged);
        	this.cbTrigger.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.IgnoreKeypress);
        	// 
        	// lTriggerNum
        	// 
        	this.lTriggerNum.AutoSize = true;
        	this.lTriggerNum.Location = new System.Drawing.Point(387, 269);
        	this.lTriggerNum.Name = "lTriggerNum";
        	this.lTriggerNum.Size = new System.Drawing.Size(40, 13);
        	this.lTriggerNum.TabIndex = 0;
        	this.lTriggerNum.Text = "Trigger";
        	// 
        	// tbTimeDelay
        	// 
        	this.tbTimeDelay.Location = new System.Drawing.Point(309, 294);
        	this.tbTimeDelay.MaxLength = 4;
        	this.tbTimeDelay.Name = "tbTimeDelay";
        	this.tbTimeDelay.Size = new System.Drawing.Size(72, 20);
        	this.tbTimeDelay.TabIndex = 122;
        	this.tbTimeDelay.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.NumKeysOnly);
        	// 
        	// lTriggerDelay
        	// 
        	this.lTriggerDelay.AutoSize = true;
        	this.lTriggerDelay.Location = new System.Drawing.Point(387, 295);
        	this.lTriggerDelay.Name = "lTriggerDelay";
        	this.lTriggerDelay.Size = new System.Drawing.Size(68, 13);
        	this.lTriggerDelay.TabIndex = 0;
        	this.lTriggerDelay.Text = "Trigger delay";
        	// 
        	// tbCLen
        	// 
        	this.tbCLen.Location = new System.Drawing.Point(474, 266);
        	this.tbCLen.Name = "tbCLen";
        	this.tbCLen.ReadOnly = true;
        	this.tbCLen.Size = new System.Drawing.Size(102, 20);
        	this.tbCLen.TabIndex = 124;
        	// 
        	// lCommandLength
        	// 
        	this.lCommandLength.AutoSize = true;
        	this.lCommandLength.Location = new System.Drawing.Point(582, 270);
        	this.lCommandLength.Name = "lCommandLength";
        	this.lCommandLength.Size = new System.Drawing.Size(86, 13);
        	this.lCommandLength.TabIndex = 0;
        	this.lCommandLength.Text = "Command length";
        	// 
        	// tbCDesc
        	// 
        	this.tbCDesc.Location = new System.Drawing.Point(474, 292);
        	this.tbCDesc.Name = "tbCDesc";
        	this.tbCDesc.Size = new System.Drawing.Size(102, 20);
        	this.tbCDesc.TabIndex = 125;
        	// 
        	// lCommandDesc
        	// 
        	this.lCommandDesc.Location = new System.Drawing.Point(582, 294);
        	this.lCommandDesc.Name = "lCommandDesc";
        	this.lCommandDesc.Size = new System.Drawing.Size(115, 13);
        	this.lCommandDesc.TabIndex = 0;
        	this.lCommandDesc.Text = "Command description";
        	// 
        	// bClear
        	// 
        	this.bClear.Location = new System.Drawing.Point(620, 12);
        	this.bClear.Name = "bClear";
        	this.bClear.Size = new System.Drawing.Size(128, 32);
        	this.bClear.TabIndex = 0;
        	this.bClear.Text = "Clear console command";
        	this.bClear.Click += new System.EventHandler(this.bClear_Click);
        	// 
        	// cbTriggerEnabled
        	// 
        	this.cbTriggerEnabled.AutoSize = true;
        	this.cbTriggerEnabled.Location = new System.Drawing.Point(368, 321);
        	this.cbTriggerEnabled.Name = "cbTriggerEnabled";
        	this.cbTriggerEnabled.Size = new System.Drawing.Size(100, 17);
        	this.cbTriggerEnabled.TabIndex = 123;
        	this.cbTriggerEnabled.Text = "Trigger enabled";
        	// 
        	// b100
        	// 
        	this.b100.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b100.Location = new System.Drawing.Point(12, 226);
        	this.b100.Name = "b100";
        	this.b100.Size = new System.Drawing.Size(64, 32);
        	this.b100.TabIndex = 106;
        	this.b100.Text = "Mouse 1";
        	this.b100.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b101
        	// 
        	this.b101.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b101.Location = new System.Drawing.Point(82, 226);
        	this.b101.Name = "b101";
        	this.b101.Size = new System.Drawing.Size(64, 32);
        	this.b101.TabIndex = 107;
        	this.b101.Text = "Mouse 2";
        	this.b101.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b102
        	// 
        	this.b102.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b102.Location = new System.Drawing.Point(152, 226);
        	this.b102.Name = "b102";
        	this.b102.Size = new System.Drawing.Size(64, 32);
        	this.b102.TabIndex = 108;
        	this.b102.Text = "Mouse 3";
        	this.b102.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b103
        	// 
        	this.b103.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b103.Location = new System.Drawing.Point(222, 226);
        	this.b103.Name = "b103";
        	this.b103.Size = new System.Drawing.Size(64, 32);
        	this.b103.TabIndex = 109;
        	this.b103.Text = "Mouse 4";
        	this.b103.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b104
        	// 
        	this.b104.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b104.Location = new System.Drawing.Point(292, 226);
        	this.b104.Name = "b104";
        	this.b104.Size = new System.Drawing.Size(64, 32);
        	this.b104.TabIndex = 110;
        	this.b104.Text = "Mouse 5";
        	this.b104.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b105
        	// 
        	this.b105.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b105.Location = new System.Drawing.Point(362, 226);
        	this.b105.Name = "b105";
        	this.b105.Size = new System.Drawing.Size(64, 32);
        	this.b105.TabIndex = 111;
        	this.b105.Text = "Mouse 6";
        	this.b105.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b106
        	// 
        	this.b106.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b106.Location = new System.Drawing.Point(432, 226);
        	this.b106.Name = "b106";
        	this.b106.Size = new System.Drawing.Size(64, 32);
        	this.b106.TabIndex = 112;
        	this.b106.Text = "Mouse 7";
        	this.b106.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b107
        	// 
        	this.b107.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b107.Location = new System.Drawing.Point(502, 226);
        	this.b107.Name = "b107";
        	this.b107.Size = new System.Drawing.Size(64, 32);
        	this.b107.TabIndex = 113;
        	this.b107.Text = "Mouse 8";
        	this.b107.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b108
        	// 
        	this.b108.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b108.Location = new System.Drawing.Point(572, 226);
        	this.b108.Name = "b108";
        	this.b108.Size = new System.Drawing.Size(80, 32);
        	this.b108.TabIndex = 114;
        	this.b108.Text = "Mouse wheel up";
        	this.b108.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// b109
        	// 
        	this.b109.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.25F);
        	this.b109.Location = new System.Drawing.Point(658, 226);
        	this.b109.Name = "b109";
        	this.b109.Size = new System.Drawing.Size(80, 32);
        	this.b109.TabIndex = 115;
        	this.b109.Text = "Mouse wheel down";
        	this.b109.Click += new System.EventHandler(this.Keyboard_Click);
        	// 
        	// MacroEditorForm
        	// 
        	this.ClientSize = new System.Drawing.Size(764, 343);
        	this.Controls.Add(this.b109);
        	this.Controls.Add(this.b108);
        	this.Controls.Add(this.b107);
        	this.Controls.Add(this.b106);
        	this.Controls.Add(this.b105);
        	this.Controls.Add(this.b104);
        	this.Controls.Add(this.b103);
        	this.Controls.Add(this.b102);
        	this.Controls.Add(this.b101);
        	this.Controls.Add(this.b100);
        	this.Controls.Add(this.cbTriggerEnabled);
        	this.Controls.Add(this.bClear);
        	this.Controls.Add(this.lCommandDesc);
        	this.Controls.Add(this.tbCDesc);
        	this.Controls.Add(this.lCommandLength);
        	this.Controls.Add(this.tbCLen);
        	this.Controls.Add(this.lTriggerDelay);
        	this.Controls.Add(this.tbTimeDelay);
        	this.Controls.Add(this.lTriggerNum);
        	this.Controls.Add(this.cbTrigger);
        	this.Controls.Add(this.bCancel);
        	this.Controls.Add(this.lMacroFunction);
        	this.Controls.Add(this.lMacroType);
        	this.Controls.Add(this.cbFunction);
        	this.Controls.Add(this.cbMacroType);
        	this.Controls.Add(this.bSave);
        	this.Controls.Add(this.rbDown);
        	this.Controls.Add(this.rbUp);
        	this.Controls.Add(this.rbTap);
        	this.Controls.Add(this.b53);
        	this.Controls.Add(this.b9c);
        	this.Controls.Add(this.b50);
        	this.Controls.Add(this.b51);
        	this.Controls.Add(this.b4c);
        	this.Controls.Add(this.b4d);
        	this.Controls.Add(this.b52);
        	this.Controls.Add(this.b4f);
        	this.Controls.Add(this.b4b);
        	this.Controls.Add(this.b4e);
        	this.Controls.Add(this.b49);
        	this.Controls.Add(this.b48);
        	this.Controls.Add(this.b47);
        	this.Controls.Add(this.b4a);
        	this.Controls.Add(this.b37);
        	this.Controls.Add(this.bb5);
        	this.Controls.Add(this.b45);
        	this.Controls.Add(this.bd0);
        	this.Controls.Add(this.bcb);
        	this.Controls.Add(this.bcd);
        	this.Controls.Add(this.b39);
        	this.Controls.Add(this.bb8);
        	this.Controls.Add(this.bdc);
        	this.Controls.Add(this.bdd);
        	this.Controls.Add(this.b9d);
        	this.Controls.Add(this.b38);
        	this.Controls.Add(this.bdb);
        	this.Controls.Add(this.b1d);
        	this.Controls.Add(this.bc8);
        	this.Controls.Add(this.b2c);
        	this.Controls.Add(this.b2d);
        	this.Controls.Add(this.b2e);
        	this.Controls.Add(this.b2f);
        	this.Controls.Add(this.b30);
        	this.Controls.Add(this.b31);
        	this.Controls.Add(this.b32);
        	this.Controls.Add(this.b33);
        	this.Controls.Add(this.b36);
        	this.Controls.Add(this.b35);
        	this.Controls.Add(this.b34);
        	this.Controls.Add(this.b56);
        	this.Controls.Add(this.b2a);
        	this.Controls.Add(this.b1c);
        	this.Controls.Add(this.b1f);
        	this.Controls.Add(this.b20);
        	this.Controls.Add(this.b21);
        	this.Controls.Add(this.b22);
        	this.Controls.Add(this.b23);
        	this.Controls.Add(this.b24);
        	this.Controls.Add(this.b25);
        	this.Controls.Add(this.b26);
        	this.Controls.Add(this.b2b);
        	this.Controls.Add(this.b28);
        	this.Controls.Add(this.b27);
        	this.Controls.Add(this.b1e);
        	this.Controls.Add(this.b3a);
        	this.Controls.Add(this.b11);
        	this.Controls.Add(this.b12);
        	this.Controls.Add(this.b13);
        	this.Controls.Add(this.b14);
        	this.Controls.Add(this.b15);
        	this.Controls.Add(this.b16);
        	this.Controls.Add(this.b17);
        	this.Controls.Add(this.b18);
        	this.Controls.Add(this.b1b);
        	this.Controls.Add(this.b1a);
        	this.Controls.Add(this.b19);
        	this.Controls.Add(this.b10);
        	this.Controls.Add(this.b0f);
        	this.Controls.Add(this.bcf);
        	this.Controls.Add(this.bd1);
        	this.Controls.Add(this.bd3);
        	this.Controls.Add(this.bc9);
        	this.Controls.Add(this.bc7);
        	this.Controls.Add(this.bd2);
        	this.Controls.Add(this.b0e);
        	this.Controls.Add(this.b0d);
        	this.Controls.Add(this.b0c);
        	this.Controls.Add(this.b0b);
        	this.Controls.Add(this.b0a);
        	this.Controls.Add(this.b06);
        	this.Controls.Add(this.b09);
        	this.Controls.Add(this.b08);
        	this.Controls.Add(this.b07);
        	this.Controls.Add(this.b05);
        	this.Controls.Add(this.b04);
        	this.Controls.Add(this.b03);
        	this.Controls.Add(this.b02);
        	this.Controls.Add(this.b29);
        	this.Controls.Add(this.bc5);
        	this.Controls.Add(this.b46);
        	this.Controls.Add(this.bb7);
        	this.Controls.Add(this.b58);
        	this.Controls.Add(this.b57);
        	this.Controls.Add(this.b44);
        	this.Controls.Add(this.b43);
        	this.Controls.Add(this.b42);
        	this.Controls.Add(this.b41);
        	this.Controls.Add(this.b40);
        	this.Controls.Add(this.b3f);
        	this.Controls.Add(this.b3e);
        	this.Controls.Add(this.b3d);
        	this.Controls.Add(this.b3c);
        	this.Controls.Add(this.b3b);
        	this.Controls.Add(this.b00);
        	this.Icon = global::MGEgui.Properties.Resources.AppIcon;
        	this.Name = "MacroEditorForm";
        	this.Text = "Macro editor";
        	this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MacroEditorForm_Closing);
        	this.ResumeLayout(false);
        	this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.Button b00;
        private System.Windows.Forms.Button b3b;
        private System.Windows.Forms.Button b3c;
        private System.Windows.Forms.Button b3d;
        private System.Windows.Forms.Button b3e;
        private System.Windows.Forms.Button b3f;
        private System.Windows.Forms.Button b40;
        private System.Windows.Forms.Button b41;
        private System.Windows.Forms.Button b42;
        private System.Windows.Forms.Button b43;
        private System.Windows.Forms.Button b44;
        private System.Windows.Forms.Button b57;
        private System.Windows.Forms.Button b58;
        private System.Windows.Forms.Button bb7;
        private System.Windows.Forms.Button b46;
        private System.Windows.Forms.Button bc5;
        private System.Windows.Forms.Button b29;
        private System.Windows.Forms.Button b02;
        private System.Windows.Forms.Button b03;
        private System.Windows.Forms.Button b04;
        private System.Windows.Forms.Button b05;
        private System.Windows.Forms.Button b07;
        private System.Windows.Forms.Button b08;
        private System.Windows.Forms.Button b09;
        private System.Windows.Forms.Button b06;
        private System.Windows.Forms.Button b0a;
        private System.Windows.Forms.Button b0b;
        private System.Windows.Forms.Button b0c;
        private System.Windows.Forms.Button b0d;
        private System.Windows.Forms.Button b0e;
        private System.Windows.Forms.Button bd2;
        private System.Windows.Forms.Button bc7;
        private System.Windows.Forms.Button bc9;
        private System.Windows.Forms.Button bd3;
        private System.Windows.Forms.Button bd1;
        private System.Windows.Forms.Button bcf;
        private System.Windows.Forms.Button b0f;
        private System.Windows.Forms.Button b10;
        private System.Windows.Forms.Button b19;
        private System.Windows.Forms.Button b1a;
        private System.Windows.Forms.Button b1b;
        private System.Windows.Forms.Button b18;
        private System.Windows.Forms.Button b17;
        private System.Windows.Forms.Button b16;
        private System.Windows.Forms.Button b15;
        private System.Windows.Forms.Button b14;
        private System.Windows.Forms.Button b13;
        private System.Windows.Forms.Button b12;
        private System.Windows.Forms.Button b11;
        private System.Windows.Forms.Button b3a;
        private System.Windows.Forms.Button b1f;
        private System.Windows.Forms.Button b20;
        private System.Windows.Forms.Button b21;
        private System.Windows.Forms.Button b22;
        private System.Windows.Forms.Button b23;
        private System.Windows.Forms.Button b24;
        private System.Windows.Forms.Button b25;
        private System.Windows.Forms.Button b26;
        private System.Windows.Forms.Button b2b;
        private System.Windows.Forms.Button b28;
        private System.Windows.Forms.Button b27;
        private System.Windows.Forms.Button b1e;
        private System.Windows.Forms.Button b1c;
        private System.Windows.Forms.Button b2a;
        private System.Windows.Forms.Button b2c;
        private System.Windows.Forms.Button b2d;
        private System.Windows.Forms.Button b2e;
        private System.Windows.Forms.Button b2f;
        private System.Windows.Forms.Button b30;
        private System.Windows.Forms.Button b31;
        private System.Windows.Forms.Button b32;
        private System.Windows.Forms.Button b33;
        private System.Windows.Forms.Button b36;
        private System.Windows.Forms.Button b35;
        private System.Windows.Forms.Button b34;
        private System.Windows.Forms.Button b56;
        private System.Windows.Forms.Button bc8;
        private System.Windows.Forms.Button b1d;
        private System.Windows.Forms.Button bdb;
        private System.Windows.Forms.Button b38;
        private System.Windows.Forms.Button b9d;
        private System.Windows.Forms.Button bdd;
        private System.Windows.Forms.Button bdc;
        private System.Windows.Forms.Button bb8;
        private System.Windows.Forms.Button b39;
        private System.Windows.Forms.Button bcd;
        private System.Windows.Forms.Button bcb;
        private System.Windows.Forms.Button bd0;
        private System.Windows.Forms.Button b45;
        private System.Windows.Forms.Button bb5;
        private System.Windows.Forms.Button b37;
        private System.Windows.Forms.Button b4a;
        private System.Windows.Forms.Button b47;
        private System.Windows.Forms.Button b48;
        private System.Windows.Forms.Button b49;
        private System.Windows.Forms.Button b4e;
        private System.Windows.Forms.Button b4b;
        private System.Windows.Forms.Button b4f;
        private System.Windows.Forms.Button b52;
        private System.Windows.Forms.Button b4d;
        private System.Windows.Forms.Button b4c;
        private System.Windows.Forms.Button b51;
        private System.Windows.Forms.Button b50;
        private System.Windows.Forms.Button b9c;
        private System.Windows.Forms.Button b53;
        private System.Windows.Forms.RadioButton rbTap;
        private System.Windows.Forms.RadioButton rbUp;
        private System.Windows.Forms.RadioButton rbDown;
        private System.Windows.Forms.Button bSave;
        private System.Windows.Forms.Button bCancel;
        private System.Windows.Forms.ComboBox cbMacroType;
        private System.Windows.Forms.Label lMacroType;
        private System.Windows.Forms.ContextMenu DudMenu;
        private System.Windows.Forms.ComboBox cbFunction;
        private System.Windows.Forms.Label lMacroFunction;
        private System.Windows.Forms.ComboBox cbTrigger;
        private System.Windows.Forms.Label lTriggerNum;
        private System.Windows.Forms.TextBox tbTimeDelay;
        private System.Windows.Forms.Label lTriggerDelay;
        private System.Windows.Forms.TextBox tbCLen;
        private System.Windows.Forms.Label lCommandLength;
        private System.Windows.Forms.TextBox tbCDesc;
        private System.Windows.Forms.Label lCommandDesc;
        private System.Windows.Forms.Button bClear;
        private System.Windows.Forms.CheckBox cbTriggerEnabled;
        private Button b100;
        private Button b101;
        private Button b102;
        private Button b103;
        private Button b104;
        private Button b105;
        private Button b106;
        private Button b107;
        private Button b108;
        private Button b109;
#endregion
        /// <summary>
        /// Which macro is being edited atm, or -1 if in selection mode
        /// </summary>
        public int Editing=-1;
        public MacroType savedMacroType;
        public MacroFormType formtype=MacroFormType.Editor;
        public bool[] Active=new bool[Statics.MACROS];
        public ArrayList ConsoleCommand=new ArrayList();

        private List<byte> macroOrdering = new List<byte> {
        	0, 13, 14, 27, 7, 8, 9, 11, 12, 21, 22, 28, 29, 36, 37, 38,
        	39, 40, 5, 41, 42, 30, 43, 31, 44, 32, 33, 45, 34, 46, 35, 48,
        	49, 50, 51, 52, 53
        };
        private List<MacroFunc> macroFuncData = new List<MacroFunc>();
        public static Dictionary<string, string> strings = new Dictionary<string, string>();
        
        public MacroEditorForm() {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            
            foreach(byte m in macroOrdering) {
            	macroFuncData.Add(new MacroFunc(m, strings["Macro"+m.ToString("D3")]));
            }
            
            cbFunction.DataSource = macroFuncData;
            cbFunction.DisplayMember = "Description";
            cbFunction.ValueMember = "Id";
            ValidateMacros();
            EndMacro();
        }

        /// <summary>
        /// Validate macro function ids for backwards compatibility
        /// </summary>
        public void ValidateMacros() {
            // Disable macros for deprecated functions
            foreach(Macro m in Statics.Macros) {
                if(m.Type == MacroType.Graphics) {
                    if(!IsValidMacroFunction(m.Graphics.function))
                        m.Type = MacroType.Unused;
                }
            }
        }

        /// </summary>
        /// <summary>
        /// Stops editing a macro and goes back to the macro select screen
        /// </summary>
        /// <param name="Partial">true to not change any form properties</param>
        public void EndMacro() {
            Text=strings["NormalTitle"];
            formtype=MacroFormType.Editor;
            cbFunction.Enabled=false;
            cbMacroType.Enabled=false;
            bSave.Enabled=false;
            bCancel.Enabled=false;
            rbDown.Enabled=false;
            rbTap.Enabled=false;
            rbUp.Enabled=false;
            tbCDesc.Enabled=false;
            cbTrigger.Enabled=true;
            cbFunction.SelectedIndex=0;
            cbTrigger.SelectedIndex=0;
            cbTriggerEnabled.Enabled=false;
            tbTimeDelay.Enabled=false;
            tbCLen.Text="";
            bClear.Enabled=false;
            ConsoleCommand.Clear();
            Editing=-1;
            foreach(Control c in Controls) {
                if(c is Button&&c.Name.StartsWith("b")&&(c.Name.Length==3||c.Name.Length==4)) {
                    c.Enabled=true;
                    if(Statics.Macros[GetCode((Button)c)].Type!=MacroType.Unused)
                        c.BackColor=Color.LightBlue;
                    else
                        c.BackColor=SystemColors.Control;
                }
            }
        }

        /// <summary>
        /// One seriously complicated function
        /// </summary>
        /// <param name="Code">The macro to start editing</param>
        public void StartMacro(int Code) {
            Text=strings["EditModeTitle"]+" 0x"+Code.ToString("x");
            Editing=Code;
            Active=new bool[Statics.MACROS];
            Array.Copy(Statics.Macros[Code].Press.KeyStates,Active,Statics.MACROS);
            ConsoleCommand.Clear();
            for(int i=0;i<Statics.Macros[Code].Console.Length;i++) {
                ConsoleCommand.Add(Statics.Macros[Code].Console.KeyCodes[i]);
            }
            tbCLen.Text=ConsoleCommand.Count.ToString();
            tbCDesc.Text=Statics.Macros[Code].Console.Description;
            cbFunction.SelectedValue=Statics.Macros[Code].Graphics.function;
            cbTriggerEnabled.Enabled=false;
            tbTimeDelay.Enabled=false;
            switch(Statics.Macros[Code].Type) {
                case MacroType.Console1:case MacroType.Console2:
                    formtype=MacroFormType.Console;
                    break;
                case MacroType.Hammer1:case MacroType.Hammer2:case MacroType.Unhammer:
                case MacroType.AHammer1:case MacroType.AHammer2:case MacroType.AUnhammer:
                case MacroType.Press1:case MacroType.Press2:case MacroType.Unpress:
                    formtype=MacroFormType.Press;
                    break;
                case MacroType.BeginTimer:case MacroType.EndTimer:
                    formtype=MacroFormType.Timer;
                    break;
                case MacroType.Graphics:
                    formtype=MacroFormType.Function;
                    break;
                default:
                    formtype=MacroFormType.Unknown;
                    break;
            }
            //Have to put this down here, or it causes all sorts of problems
            cbTrigger.SelectedIndex=Statics.Macros[Code].Timer.TimerID+1;
            bSave.Enabled=true;
            bCancel.Enabled=true;
            cbMacroType.Enabled=true;
            tbTimeDelay.Enabled=false;
            cbMacroType.SelectedIndex=(int)Statics.Macros[Code].Type;

            if(formtype==MacroFormType.Console||formtype==MacroFormType.Press||formtype==MacroFormType.Trigger) {
                foreach(Control c in Controls) {
                    if(c is Button&&c.Name.StartsWith("b")&&(c.Name.Length==3||c.Name.Length==4)) {
                        int i=GetCode((Button)c);
                        if(formtype==MacroFormType.Console) {
                            c.BackColor=SystemColors.Control;
                            if(i<256) { c.Enabled=true; } else { c.Enabled=false; }
                        } else {
                            if(i<264) { c.Enabled=true; } else { c.Enabled=false; }
                            if(Active[GetCode((Button)c)])
                                c.BackColor=Color.LightBlue;
                            else
                                c.BackColor=SystemColors.Control;
                        }
                    }
                    
                }
            } else {
                foreach(Control c in Controls) {
                    if(c is Button&&c.Name.StartsWith("b")&&(c.Name.Length==3||c.Name.Length==4)) {
                        c.Enabled=false;
                        c.BackColor=SystemColors.Control;
                    }
                }
            }
            if(formtype==MacroFormType.Console) {
                rbDown.Enabled=true;
                rbTap.Enabled=true;
                rbUp.Enabled=true;
                rbTap.Checked=true;
                tbCDesc.Enabled=true;
                bClear.Enabled=true;
            } else {
                rbDown.Enabled=false;
                rbTap.Enabled=false;
                rbUp.Enabled=false;
                tbCDesc.Enabled=false;
                bClear.Enabled=false;
            }
            if(formtype==MacroFormType.Function) {
                cbFunction.Enabled=true;
            } else {
                cbFunction.Enabled=false;
            }
            if(formtype==MacroFormType.Timer) {
                cbTrigger.Enabled=true;
            } else {
                cbTrigger.Enabled=false;
            }
        }

        private void StartTrigger(int Code) {
            Editing=Code;
            Text="Editing trigger "+Code.ToString();
            formtype=MacroFormType.Trigger;
            //Same as EndMacro() so probably not needed
            cbFunction.Enabled=false;
            cbMacroType.Enabled=false;
            rbDown.Enabled=false;
            rbTap.Enabled=false;
            rbUp.Enabled=false;
            tbCDesc.Enabled=false;
            tbCLen.Text="";
            //Changes
            bSave.Enabled=true;
            bCancel.Enabled=true;
            cbTrigger.Enabled=false;
            tbTimeDelay.Enabled=true;
            cbTriggerEnabled.Enabled=true;
            //Set up initial data
            Array.Copy(Statics.Triggers[Code].data.KeyStates,Active,Statics.MACROS);
            tbTimeDelay.Text=Statics.Triggers[Code].TimeInterval.ToString();
            cbTriggerEnabled.Checked=Statics.Triggers[Code].Active;
            //Setup the buttons
            foreach(Control c in Controls) {
                if(c is Button&&c.Name.StartsWith("b")&&(c.Name.Length==3||c.Name.Length==4)) {
                    if(GetCode((Button)c)<264) {c.Enabled=true;} else {c.Enabled=false;}
                    if(Active[GetCode((Button)c)])
                        c.BackColor=Color.LightBlue;
                    else
                        c.BackColor=SystemColors.Control;
                }
            }
        }

        private Button GetButton(byte code) {
            foreach(Button b in this.Controls) {
                if(b.Name=="b"+code.ToString("x")) return b;
            }
            return null;
        }

        private int GetCode(Button b) {
            return Convert.ToInt32(b.Name.Remove(0,1),16);
        }

        private void Keyboard_Click(object sender,EventArgs e) {
            Button button=(Button)sender;
            switch(formtype) {
                case MacroFormType.Editor:
                    // Select function type for new macros, the most commonly used type
                    savedMacroType = Statics.Macros[GetCode(button)].Type;
                    if(savedMacroType == MacroType.Unused)
                        Statics.Macros[GetCode(button)].Type = MacroType.Graphics;
                    StartMacro(GetCode(button));
                    return;
                case MacroFormType.Press:case MacroFormType.Trigger:
                    Active[GetCode(button)]=!Active[GetCode(button)];
                    if(Active[GetCode(button)])
                        button.BackColor=Color.LightBlue;
                    else
                        button.BackColor=SystemColors.Control;
                    return;
                case MacroFormType.Console:
                    if(ConsoleCommand.Count>=255) {
                    	MessageBox.Show(strings["CommandLengthExceeded"],Statics.strings["Error"]);
                        break;
                    }
                    if(rbDown.Checked) {
                        ConsoleCommand.Add(new KeyPress((byte)GetCode(button),true));
                    } else if(rbUp.Checked) {
                        ConsoleCommand.Add(new KeyPress((byte)GetCode(button),false));
                    } else {
                        ConsoleCommand.Add(new KeyPress((byte)GetCode(button),true));
                        ConsoleCommand.Add(new KeyPress((byte)GetCode(button),false));
                    }
                    tbCLen.Text=ConsoleCommand.Count.ToString();
                    return;
                default:
                    MessageBox.Show(strings["KeyboardError"],Statics.strings["Error"]);
                    return;
            }
        }

        private void IgnoreKeypress(object sender,KeyPressEventArgs e) {
            e.Handled=true;
        }

        private void MacroEditorForm_Closing(object sender, FormClosingEventArgs e) {
            if(Editing != -1)
                Statics.Macros[Editing].Type = savedMacroType;
        }
        
        private void bCancel_Click(object sender,EventArgs e) {
            Statics.Macros[Editing].Type = savedMacroType;            
            EndMacro();
        }

        private void bSave_Click(object sender,EventArgs e) {
            if(formtype==MacroFormType.Trigger) {
                Array.Copy(Active,Statics.Triggers[Editing].data.KeyStates,Statics.MACROS);
                try {
                    Statics.Triggers[Editing].TimeInterval=Convert.ToUInt32(tbTimeDelay.Text);
                } catch {
                    Statics.Triggers[Editing].TimeInterval=10;
                }
                Statics.Triggers[Editing].Active=cbTriggerEnabled.Checked;
            } else {
                ConsoleCommand.CopyTo(Statics.Macros[Editing].Console.KeyCodes);
                Statics.Macros[Editing].Console.Length=(byte)ConsoleCommand.Count;
                Statics.Macros[Editing].Console.Description=tbCDesc.Text;
                Array.Copy(Active,Statics.Macros[Editing].Press.KeyStates,Statics.MACROS);
                Statics.Macros[Editing].Graphics.function=(byte)cbFunction.SelectedValue;
                if(cbTrigger.SelectedIndex>0) {
                    Statics.Macros[Editing].Timer.TimerID=(byte)(cbTrigger.SelectedIndex-1);
                } else {
                    Statics.Macros[Editing].Timer.TimerID=0;
                }
            }
            EndMacro();
        }

        private void cbMacroType_SelectedIndexChanged(object sender,EventArgs e) {
        	if(Editing == -1) return;
            int i=Editing;
            Statics.Macros[i].Type=(MacroType)(cbMacroType.SelectedIndex);
            StartMacro(i);
        }

        private void bClear_Click(object sender,EventArgs e) {
            ConsoleCommand.Clear();
            tbCDesc.Text="";
            tbCLen.Text="0";
        }

        private void cbTrigger_SelectedIndexChanged(object sender,EventArgs e) {
            if(cbTrigger.SelectedIndex==0) return;
            if(formtype==MacroFormType.Editor) {
                StartTrigger(cbTrigger.SelectedIndex-1);
            }
        }

        private void NumKeysOnly(object sender,KeyPressEventArgs e) {
            switch(e.KeyChar) {
                case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
                    return;
                default:
                    e.Handled=true;
                    return;
            }
        }

        private struct MacroFunc
        {
            private byte id;
            private string description;
            
            public MacroFunc(byte i, string d) { id = i; description = d; }
            public byte Id { get { return id; } }
            public string Description { get { return description; } }
        }
        
        private bool IsValidMacroFunction(byte f)
        {
            foreach(MacroFunc mf in macroFuncData) {
                if(f == mf.Id) return true;
            }
            return false;
        }
        
    }
}
