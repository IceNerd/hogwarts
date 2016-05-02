class HelloWorld
{
    public static void Main()
    {
        int iConvert = -1;

        try
        {
            // for part 11
            //checked
            //{
            //    int Big = 64000;
            //    short Little = (short)(Big);
            //}
            //// end for part 11

            System.Console.WriteLine(System.Environment.MachineName.ToString());
            System.Console.WriteLine(System.Environment.OSVersion.ToString());
            System.Console.WriteLine(System.Environment.ProcessorCount.ToString());
            System.Console.WriteLine(System.Environment.Version.ToString());
            System.Console.WriteLine(System.Environment.UserName.ToString());
            System.Console.WriteLine(System.Environment.UserDomainName.ToString());

            iConvert = System.Convert.ToInt32(System.Console.ReadLine());
            if (iConvert > 2000 || iConvert < 0)
            {
                throw new System.Exception("Invalid Input From User");
            }
            System.Console.WriteLine(ConvertToRoman(iConvert));
        }
        catch(System.OverflowException)
        {
            System.Console.WriteLine("Overflow Exception Caught");
        }
        catch (System.Exception errStd)
        {
            System.Console.Write("EXCEPTION: ");
            System.Console.WriteLine(errStd.GetType().ToString());
            System.Console.Write("Stack Trace: ");
            System.Console.WriteLine(errStd.StackTrace);
            System.Console.Write("Target Site: ");
            System.Console.WriteLine(errStd.TargetSite);
        }
        finally
        {
            System.Console.WriteLine("*** Program Done *** Press any key to quit");
            System.Console.ReadKey();
        }
    }

    private static string ConvertToRoman(int iConvert)
    {
        string strReturn = "";

        while (iConvert >= 1000)
        {
            strReturn += "M";
            iConvert -= 1000;
        }

        while (iConvert >= 500)
        {
            strReturn += "D";
            iConvert -= 500;
        }

        while (iConvert >= 100)
        {
            strReturn += "C";
            iConvert -= 100;
        }

        while (iConvert >= 50)
        {
            strReturn += "L";
            iConvert -= 50;
        }

        while (iConvert >= 10)
        {
            strReturn += "X";
            iConvert -= 10;
        }

        while (iConvert >= 5)
        {
            strReturn += "V";
            iConvert -= 5;
        }

        while (iConvert >= 1)
        {
            strReturn += "I";
            iConvert -= 1;
        }

        return strReturn;
    }
}