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
            Triangle myTriangle = new Triangle();
            myTriangle.Uno = 1;
            myTriangle.Dos = 2;

            System.Xml.Serialization.XmlSerializer mySerializer = new System.Xml.Serialization.XmlSerializer(typeof(Triangle));
            TextWriter myWriter = new StreamWriter("test.xml");
            mySerializer.Serialize(myWriter, myTriangle);
            myWriter.Close();

            Triangle UnTriangle;
            TextReader myReader = new StreamReader("test.xml");
            UnTriangle = (Triangle)mySerializer.Deserialize(myReader);
            myReader.Close();

            Console.WriteLine("Triangle: {0}, {1}", UnTriangle.Uno, UnTriangle.Dos);
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