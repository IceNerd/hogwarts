using System;
using System.IO;
using System.Collections;

// Interface to implementation of IComparer that we may use to sort our arraylist of strings
class CustomCompare : IComparer
{
    // comparison for two string with respect to their length
    public int Compare(object objLeft, object objRight)
    {
        int iReturn = 0;
        string strLeft = (string)objLeft;
        string strRight = (string)objRight;

        if (strLeft.Length < strRight.Length)
        {
            // left has a lesser sorting value than right
            iReturn = -1;
        }
        else if( strLeft.Length > strRight.Length)
        {
            // right has a lesser sorting value than left
            iReturn = 1;
        }

        //iReturn remains 0 if the lengths are equal
        return iReturn;
    } 
}

class HelloWorld
{
    public static void Main()
    {
        try
        {
            ArrayList raStrings = new ArrayList();
            foreach (string str in Directory.GetFiles("C:\\"))
            {
                raStrings.Add(str);
            }

            // call a sort on our ArrayList using the IComparer I made
            raStrings.Sort(new CustomCompare());

            int iCount = 0;
            foreach( object i in raStrings)
            {
                Console.WriteLine("{0,2}({2,2}): {1}", iCount++, i.ToString(), i.ToString().Length);
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