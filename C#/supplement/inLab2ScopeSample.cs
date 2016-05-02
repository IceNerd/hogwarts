//*************************************************************************
//*					Filename:  inLab2ScopeSample.cs
//*		 		    CST 346 - C# -- Some Weird Code
//* Step 1:  Look at the goofy code briefly before running it - will it compile ok?
//* Step 2:  Try it...
//* Step 3:  See note below and of course fix
//* NOTE:  Remember, every obj must be defined within a function or a class.
//*        BEFORE an obj can be read to/written from - it must be initialized
//*        Uses 'static flow analysis' - says hey, the while loop may just
//*		   not ever fire -- so we got a potential problem.  Think you can see 
//*		   the 2 second fix.  Also - notice what the if expression must evaluate to!
//*		   Again - remember to read about boxing/unboxing/ref and value types!
//*****************************************************************************
using System;
class Scope 
{
	static void Main()
	{
		string name ;      // could have initialized - but didn't
		int attempts = 0; // Notice - intialized it!
		const int maxAttempts = 3; // obvious
		while (attempts < maxAttempts)
		{
			attempts++;
			Console.Write("Enter your name: ");
			name = Console.ReadLine();
			if (name.Equals("SET")) // Notice the effect of Equals with a string vs most other REFERENCE types? Check it!
				attempts = 99;
			
		}
		Console.WriteLine("Hey {0} Major!", name);
		
		// Just a reminder on somthing else too
		int x = 1;
	//	if (x) // What do you think?  Try it...
	//		Console.WriteLine("SAY GOOD BYE TO THIS");
	
	}
}
