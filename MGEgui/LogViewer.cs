using System;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

namespace MGEgui
{
	/// <summary>
	/// Log file viewer.
	/// </summary>
	public partial class LogViewerForm : Form
	{
		public LogViewerForm(string path)
		{
            InitializeComponent();
            Statics.Localizations.Apply(this);
            
            StreamReader sr = new StreamReader(File.OpenRead(path));
            rtbLog.Text = sr.ReadToEnd().Trim(new char[] { '\n', '\r' });
            this.Text += " - " + path;
            sr.Close();
		}
	}
}
