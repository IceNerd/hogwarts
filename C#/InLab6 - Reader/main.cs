using System;
using System.IO;
using System.Xml;
using System.Collections;

class HelloWorld
{
    public static void Main()
    {
        try
        {
            //read
            XmlReader myReader = new XmlTextReader("schedule.xml");

            while( myReader.Read() )
            {
                Console.WriteLine( myReader.ReadString() );
            }

            // close the file that has been read from
            myReader.Close();
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