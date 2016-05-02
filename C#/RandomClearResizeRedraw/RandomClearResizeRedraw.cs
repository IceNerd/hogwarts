//------------------------------------------------------
// RandomClearResizeRedraw.cs © 2001 by Charles Petzold
// Comments added by Randy
//------------------------------------------------------
using System;
using System.Drawing;
using System.Windows.Forms;

class RandomClearResizeRedraw: Form
{
     public static void Main()      
     {
          Application.Run(new RandomClearResizeRedraw());
     }
     public RandomClearResizeRedraw()      
     {
          Text = "Random Clear with Resize Redraw";
          // now have activated in the ctor - use whenever something
		 //  in your form is not being updated correctly
		  ResizeRedraw = true;	// Not currently in RandomClear file...
     }
     protected override void OnPaint(PaintEventArgs pea)
     {
          // Good time to check out this class!  It should
		  // look somewhat familiar in relation to Win32 programming.
		 //  Hey, what if you wanted to display something within a
		 //  non-OnPaint handler - how could you do it?
		  Graphics grfx = pea.Graphics;
          Random   rand = new Random();

          grfx.Clear(Color.FromArgb(rand.Next(256),
                                    rand.Next(256),
                                    rand.Next(256)));
     }

    protected override void OnResize(EventArgs ea)
    {
        base.OnResize(ea);
    }
}