using System;

class Program
{
    public static void Main(string[] args)
    {
        // title as per (3) of assignment
        string inLab2Title =
        @"        CST 346- C# - Fall 2005
        Name: Alberto Martinez
        Date: 4/24/2007
        InLab: 2    ";

        const string strDelims = " !.-_=,";

        Console.WriteLine(inLab2Title);
        Console.WriteLine();
        Console.Write("Please Input File Name: ");
        string strInput = Console.ReadLine();

        // open file and dump to screen
        System.IO.StreamReader FileReader = new System.IO.StreamReader(strInput);
        while (!FileReader.EndOfStream)
        {
            string strLine = FileReader.ReadLine();

            string[] raWords = strLine.Split(strDelims.ToCharArray(), StringSplitOptions.RemoveEmptyEntries);
            foreach (string i in raWords)
            {
                Console.WriteLine(i);
            }
        }
        FileReader.Close();
        Console.Write("Press any key to continue");
        Console.ReadKey();
    }
}
