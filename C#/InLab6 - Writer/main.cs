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
            // write
            XmlTextWriter myWriter = new XmlTextWriter("test.xml", null);
            myWriter.Formatting = Formatting.Indented;
            myWriter.Indentation = 5;
            myWriter.Namespaces = false;

            myWriter.WriteStartDocument();

            myWriter.WriteStartElement("", "XmlDoc", "");

            myWriter.WriteStartElement("", "Number", "");
            myWriter.WriteString("1234");
            myWriter.WriteEndElement();

            myWriter.WriteStartElement("", "String", "");
            myWriter.WriteString("Hola");
            myWriter.WriteEndElement();

            myWriter.WriteStartElement("", "Number", "");
            myWriter.WriteString("4321");
            myWriter.WriteEndElement();

            myWriter.WriteStartElement("", "String", "");
            myWriter.WriteString("Adios");
            myWriter.WriteEndElement();

            myWriter.WriteEndElement();
            myWriter.Flush();

            // close
            myWriter.Close();
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