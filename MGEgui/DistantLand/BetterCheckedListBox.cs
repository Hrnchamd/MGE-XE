using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace MGEgui.DistantLand {
    /// <summary>
    /// An improvement of CheckedListBox. Only toggles if the actual checkbox is clicked, or the list entry is double-clicked.
    /// </summary>
    public class BetterCheckedListBox : System.Windows.Forms.CheckedListBox {
        private bool ignoreCheck;

        public BetterCheckedListBox() {
            CheckOnClick = true;
            ignoreCheck = false;
        }

        protected override void OnMouseClick(MouseEventArgs e) {
            ignoreCheck = e.X > SystemInformation.MenuCheckSize.Width;
            base.OnClick(e);
        }

        protected override void OnMouseUp(MouseEventArgs e) {
            ignoreCheck = false;
            base.OnMouseUp(e);
        }

        protected override void OnItemCheck(ItemCheckEventArgs e) {
            if (ignoreCheck) {
                e.NewValue = e.CurrentValue;
            }
            base.OnItemCheck(e);
        }
    }
}
