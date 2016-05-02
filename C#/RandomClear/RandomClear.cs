//------------------------------------------------------------
// RandomClear.cs © 2001 by Charles Petzold
// Comments added by Randy
// Please review this code carefully - notice
// that the program randomly calculates a new
// color and uses the Clear method to display
// the new color.
// ToDo:  Try resizing the form
// NOTICE:  what is the Clear method actually clearing here -
// the whole form or the invalid area?
// Now check out next sample - RandomClearResizeRedraw.cs

//------------------------------------------------------------
using System;
using System.Drawing;
using System.Windows.Forms;

class RandomClear: Form 
{
     public static void Main()
     {
          Application.Run(new RandomClear());
     }
     public RandomClear()      
     {
          Text = "Random Clear";
     }
	// Notice how this method is overriding an existing method???
	// Since this class is derived from Control - you don't have to
	// (but you could) install a Paint event handler - we are simply
	// overriding the protected OnPaint meth.  Note that all EVENTS
	// defined in Windows Forms are the same - the method name consists of
	// the word On followed by the event name.  There IS however one other
	// thing you should do when you override these event handlers as noted
	// in our class notes and the inlab.  Do it.
	protected override void OnPaint(PaintEventArgs pea) 
							
     {
          Graphics grfx = pea.Graphics;
          Random   rand = new Random();
		  // Check out the help on this method
          grfx.Clear(Color.FromArgb(rand.Next(256),
                                    rand.Next(256),
                                    rand.Next(256)));
     }
}