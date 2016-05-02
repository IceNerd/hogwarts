/*******************************************************************************
* CST 346 - R. Albert - based off Chapter 2 - Petzold - and Chapter 20 - Troelsen
* Hello World --  InLab #4 - HelloWorld.cs
* Startup Code... Make sure you check out the on-line help within here folks AND 
* that YOU have REVIEWED THE LINKS TO ARTICLES I PROVIDED!
* NOTE:  don't foget to setup/add your References in Solution Explorer for the
*        necessary .dll's!  Please make it a point to refer to Petzold, Troelsen or 
*        the online help as needed.
* Also - make sure you check out some of the other useful windows under the 
*		 View menu option (like Class View, etc.)
* So, is a 'using'  the same as including the DLL?  NOOOOO!  Not at all like in C++!
*********************************************************************************/

// These 3 guys will usually be the MINIMUM you will need for your apps!
using System;  // These are NOT equivalent to #include stmts in C++!
using System.Drawing; // They exist just so you don't have to fully qualify class names
using System.Windows.Forms; // Things like the class defintions, type declarations, etc are provided via the DLL's!

class HelloWorld: Form   // no surprise here right
{
	public static void Main()
	{
		// Check out Application.Run - this guys is IMPT!  
		// He starts  running your app's message loop.
		Application.Run(new HelloWorld());
	}
	public HelloWorld()
	{
		Text = "Hello Windows Forms!";
		// I put these in just for fun and to illustrate the value of the drop down choices shown by 'this'
		this.Width = 400;
		Height = 300;  // this implied right?
		
	}
	#region OnPaint region for Fun!
	// Best also review OnPaint too!  Petzold gives a good review of this - as does the help - it is impt!
	protected override void OnPaint(PaintEventArgs pea)
	{    base.OnPaint(pea); // you will read about later in this weeks lab!
		//Graphics - Encapsulates a GDI+ drawing surface. This class cannot be inherited.
		// Please take a look at the Graphics class on-line help NOW - impressive isn't it :-)
       
		Graphics grfx = pea.Graphics;

		grfx.DrawString("Hello SET/CET Seniors and the Rest of the World", Font, Brushes.Black, 0, 0);
		grfx.DrawString("Aren't YOU glad you have completed your Petition to Graduate already!", Font, Brushes.Blue, 50, 50);

	}
		#endregion

}