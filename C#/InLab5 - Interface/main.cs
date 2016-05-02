using System;
using System.IO;
using System.Collections;

class HelloWorld
{
    public static void Main()
    {
        try
        {
            // ByTwos ---------------------------
            ByTwos myByTwos = new ByTwos();

            Console.WriteLine("Calling GetNext() 5 times from default");
            for (int i = 0; i < 5; ++i)
            {
                Console.WriteLine("{0,2}: {1}", i, myByTwos.GetNext());
            }

            myByTwos.SetStart(50);
            Console.WriteLine("Calling GetNext() 5 times from SetStart(50)");
            for (int i = 0; i < 5; ++i)
            {
                Console.WriteLine("{0,2}: {1}", i, myByTwos.GetNext());
            }

            // ByFives --------------------------
            ByFives myByFives = new ByFives();

            Console.WriteLine("Calling GetNext() 5 times from default");
            for (int i = 0; i < 5; ++i)
            {
                Console.WriteLine("{0,2}: {1}", i, myByFives.GetNext());
            }

            myByFives.SetStart(50);
            Console.WriteLine("Calling GetNext() 5 times from SetStart(50)");
            for (int i = 0; i < 5; ++i)
            {
                Console.WriteLine("{0,2}: {1}", i, myByFives.GetNext());
            }

            // Interface Reference --------------
            ISeries myRef = myByTwos;
            Console.WriteLine("Using interface reference to call GetNext() 5 times");
            Console.WriteLine("Which class is being referred to?");
            for (int i = 0; i < 5; ++i)
            {
                Console.WriteLine("{0,2}: {1}", i, myRef.GetNext());
            }
        }
        catch(System.OverflowException)
        {
            Console.WriteLine("Overflow Exception Caught");
        }
        catch (System.Exception errStd)
        {
            Console.Write("EXCEPTION: ");
            Console.WriteLine(errStd.GetType().ToString());
            Console.Write("Stack Trace: ");
            Console.WriteLine(errStd.StackTrace);
            Console.Write("Target Site: ");
            Console.WriteLine(errStd.TargetSite);
        }
        finally
        {
            Console.WriteLine("*** Program Done *** Press any key to quit");
            Console.ReadKey();
        }
    }
}