using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing; // They exist just so you don't have to fully qualify class names
using System.Windows.Forms; // Things like the class defintions, type declarations, etc are provided via the DLL's!

class HelloForm : Form
{
    public HelloForm()
	{
		Text = "Hello Windows Forms!";
		// I put these in just for fun and to illustrate the value of the drop down choices shown by 'this'
		this.Width = 400;
		Height = 300;  // this implied right?
        MessageBox.Show("My First Windows App in C#", "CST 346", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
        this.BackColor = System.Drawing.Color.Aquamarine;
        this.CenterToScreen();
        this.MaximizeBox = false;
        this.Cursor = System.Windows.Forms.Cursors.Cross;
        this.Opacity = .5;

        Console.WriteLine("Window Created");
	}

    // Best also review OnPaint too!  Petzold gives a good review of this - as does the help - it is impt!
    protected override void OnPaint(PaintEventArgs pea)
    {
        base.OnPaint(pea); // you will read about later in this weeks lab!
        //Graphics - Encapsulates a GDI+ drawing surface. This class cannot be inherited.
        // Please take a look at the Graphics class on-line help NOW - impressive isn't it :-)

        Graphics grfx = pea.Graphics;

        StringFormat strToDraw = new StringFormat();

        Pen myPen = new Pen(Color.Bisque);

        grfx.DrawEllipse(myPen, 50f, 50f, 25, 25);

        strToDraw.Alignment = StringAlignment.Center;
        grfx.DrawString("Alberto Martinez", Font, Brushes.Blue, this.ClientSize.Width / 2, this.ClientSize.Height / 2, strToDraw);

        strToDraw.Alignment = StringAlignment.Near;
        grfx.DrawString("23", Font, Brushes.Black, 0.0f, 0.0f, strToDraw);

        strToDraw.Alignment = StringAlignment.Far;
        grfx.DrawString("503-409-9079", Font, Brushes.Black, this.ClientSize.Width, 0.0f, strToDraw);

    }
}
