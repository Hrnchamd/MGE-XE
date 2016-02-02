using System;
using System.Windows.Forms;
using System.Threading;
using System.ComponentModel;
using System.Collections.Generic;

namespace MGEgui {
    public class RenderWindow : Form {
#region Form designer stuff
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
            this.components = new System.ComponentModel.Container();
            this.cbShader = new System.Windows.Forms.CheckBox();
            this.fpsLabel = new System.Windows.Forms.Label();
            this.fpsTimer = new System.Windows.Forms.Timer(this.components);
            this.RenderPanel = new System.Windows.Forms.Panel();
            this.bBenchmark = new System.Windows.Forms.Button();
            this.cmbCycles = new System.Windows.Forms.ComboBox();
            this.DudMenu = new System.Windows.Forms.ContextMenu();
            this.var_HDR = new System.Windows.Forms.NumericUpDown();
            this.hdrLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.var_HDR)).BeginInit();
            this.SuspendLayout();
            // 
            // cbShader
            // 
            this.cbShader.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cbShader.AutoSize = true;
            this.cbShader.Checked = true;
            this.cbShader.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbShader.Location = new System.Drawing.Point(12, 559);
            this.cbShader.Name = "cbShader";
            this.cbShader.Size = new System.Drawing.Size(99, 19);
            this.cbShader.TabIndex = 0;
            this.cbShader.Text = "Enable shader";
            this.cbShader.CheckedChanged += new System.EventHandler(this.cbShader_CheckedChanged);
            // 
            // fpsLabel
            // 
            this.fpsLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.fpsLabel.AutoSize = true;
            this.fpsLabel.Location = new System.Drawing.Point(159, 560);
            this.fpsLabel.Name = "fpsLabel";
            this.fpsLabel.Size = new System.Drawing.Size(38, 15);
            this.fpsLabel.TabIndex = 0;
            this.fpsLabel.Text = "FPS: 0";
            // 
            // fpsTimer
            // 
            this.fpsTimer.Enabled = true;
            this.fpsTimer.Interval = 1000;
            this.fpsTimer.Tick += new System.EventHandler(this.fpsTimer_Tick);
            // 
            // RenderPanel
            // 
            this.RenderPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
                                    | System.Windows.Forms.AnchorStyles.Left) 
                                    | System.Windows.Forms.AnchorStyles.Right)));
            this.RenderPanel.Location = new System.Drawing.Point(12, 12);
            this.RenderPanel.Name = "RenderPanel";
            this.RenderPanel.Size = new System.Drawing.Size(960, 541);
            this.RenderPanel.TabIndex = 0;
            // 
            // bBenchmark
            // 
            this.bBenchmark.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bBenchmark.Location = new System.Drawing.Point(862, 556);
            this.bBenchmark.Name = "bBenchmark";
            this.bBenchmark.Size = new System.Drawing.Size(110, 25);
            this.bBenchmark.TabIndex = 2;
            this.bBenchmark.Text = "Benchmark";
            this.bBenchmark.Click += new System.EventHandler(this.bBenchmark_Click);
            // 
            // cmbCycles
            // 
            this.cmbCycles.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbCycles.ContextMenu = this.DudMenu;
            this.cmbCycles.Items.AddRange(new object[] {
                                    "50 frames",
                                    "100 frames",
                                    "500 frames",
                                    "1000 frames"});
            this.cmbCycles.Location = new System.Drawing.Point(763, 557);
            this.cmbCycles.Name = "cmbCycles";
            this.cmbCycles.Size = new System.Drawing.Size(89, 23);
            this.cmbCycles.TabIndex = 1;
            this.cmbCycles.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.cmbCycles_KeyPress);
            // 
            // var_HDR
            // 
            this.var_HDR.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.var_HDR.DecimalPlaces = 2;
            this.var_HDR.Increment = new decimal(new int[] {
                                    5,
                                    0,
                                    0,
                                    131072});
            this.var_HDR.Location = new System.Drawing.Point(297, 557);
            this.var_HDR.Maximum = new decimal(new int[] {
                                    1,
                                    0,
                                    0,
                                    0});
            this.var_HDR.Name = "var_HDR";
            this.var_HDR.Size = new System.Drawing.Size(82, 23);
            this.var_HDR.TabIndex = 3;
            this.var_HDR.Value = new decimal(new int[] {
                                    2,
                                    0,
                                    0,
                                    65536});
            // 
            // hdrLabel
            // 
            this.hdrLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.hdrLabel.AutoSize = true;
            this.hdrLabel.Location = new System.Drawing.Point(257, 560);
            this.hdrLabel.Name = "hdrLabel";
            this.hdrLabel.Size = new System.Drawing.Size(34, 15);
            this.hdrLabel.TabIndex = 4;
            this.hdrLabel.Text = "HDR:";
            // 
            // RenderWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(986, 583);
            this.Controls.Add(this.hdrLabel);
            this.Controls.Add(this.var_HDR);
            this.Controls.Add(this.RenderPanel);
            this.Controls.Add(this.cmbCycles);
            this.Controls.Add(this.fpsLabel);
            this.Controls.Add(this.bBenchmark);
            this.Controls.Add(this.cbShader);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = global::MGEgui.Properties.Resources.AppIcon;
            this.MinimumSize = new System.Drawing.Size(480, 320);
            this.Name = "RenderWindow";
            this.Text = "Preview Window";
            this.Closing += new System.ComponentModel.CancelEventHandler(this.RenderWindow_FormClosing);
            this.Shown += new System.EventHandler(this.RenderWindow_Shown);
            ((System.ComponentModel.ISupportInitialize)(this.var_HDR)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        private CheckBox cbShader;
        private Label fpsLabel;
        private Panel RenderPanel;
        private Button bBenchmark;
        private ComboBox cmbCycles;
        private ContextMenu DudMenu;
		private NumericUpDown var_HDR;
		private Label hdrLabel;
        private System.Windows.Forms.Timer fpsTimer;

        #endregion
#endregion
        public static Dictionary<string, string> strings = new Dictionary<string, string>();
        
        public RenderWindow() {
            InitializeComponent();
            Statics.Localizations.Apply(this);
            
            panel=RenderPanel;
            UseShader=true;
            This=this;
            cmbCycles.SelectedIndex=1;
        }

        private static RenderWindow This;
        public static Control panel;
        public static Thread thread;
        private static volatile float fps=0;
        private static volatile bool UseShader;
        private static volatile bool Exit=false;

        public static void ThreadStart() {
            int frames;
            DateTime now, then;
            TimeSpan second=TimeSpan.FromSeconds(1);
            while(true) {
                now=DateTime.Now;
                then=now+second;
                frames=0;
                while(DateTime.Now<then) {
                    try { DirectX.Shaders.RenderFrame(UseShader, This.var_HDR.Value); } catch { }
                    frames++;
                }
                fps=(float)frames/(float)(DateTime.Now-now).TotalSeconds;

                if(Exit) return;
            }
        }

        private void RenderWindow_FormClosing(object sender,CancelEventArgs e) {
            if(thread!=null) {
                Exit=true;
                thread.Join();
                Exit=false;
            }
        }

        private void fpsTimer_Tick(object sender,EventArgs e) {
        	fpsLabel.Text = strings["FPS"] + Math.Round(fps, 2).ToString();
        }

        private void cbShader_CheckedChanged(object sender,EventArgs e) {
            UseShader=cbShader.Checked;
        }

        private void cmbCycles_KeyPress(object sender,KeyPressEventArgs e) {
            e.Handled=true;
        }

        private void bBenchmark_Click(object sender,EventArgs e) {
            int cycles;
            switch(cmbCycles.SelectedIndex) {
                case 0: cycles=50; break;
                case 1: cycles=100; break;
                case 2: cycles=500; break;
                case 3: cycles=1000; break;
                default: cycles=100; break;
            }
            thread.Suspend();
            DateTime start;
            TimeSpan standard,shader;
            start=DateTime.Now;
            for(int i=0;i<cycles;i++) {
				DirectX.Shaders.RenderFrame(false, This.var_HDR.Value);
            }
            standard=DateTime.Now-start;
            start=DateTime.Now;
            for(int i=0;i<cycles;i++) {
				DirectX.Shaders.RenderFrame(true, This.var_HDR.Value);
            }
            shader=DateTime.Now-start;
            
            double reduction = Math.Min(1, (double)standard.Ticks/(double)shader.Ticks);
            double perfhit = (1.0 - reduction) * 100.0;
            double frametime = ((double)shader.Milliseconds/1000.0)/(double)cycles;
            
            MessageBox.Show(strings["Benchmark1"]+cycles.ToString()+strings["Benchmark2"]+"\n\n"+
                strings["Benchmark3"]+standard.ToString()+"\n"+
                strings["Benchmark4"]+shader.ToString()+"\n"+
                strings["Benchmark5"]+frametime.ToString("G5")+strings["Benchmark6"]+"\n"+
                strings["Benchmark7"]+perfhit.ToString("G5")+"%\n\n"+
                strings["Benchmark8"]+"\n"+
                "60: "+(60*reduction).ToString("G5")+"\n"+
                "50: "+(50*reduction).ToString("G5")+"\n"+
                "40: "+(40*reduction).ToString("G5")+"\n"+
                "30: "+(30*reduction).ToString("G5")+"\n"+
                "20: "+(20*reduction).ToString("G5")+"\n"+
                "10: "+(10*reduction).ToString("G5")+"\n\n"+
                strings["Benchmark9"],
                bBenchmark.Text);
            thread.Resume();
        }

        private void RenderWindow_Shown(object sender, EventArgs e) {
            thread=new Thread(new ThreadStart(ThreadStart));
            thread.Priority=ThreadPriority.BelowNormal;
            RenderWindow.thread.Start();
        }

    }
}
