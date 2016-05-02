using System;

class Crypto
{
    public Crypto(int iKey)
    {
        SetKey(iKey);
    }

    private int miKey;
    public void SetKey(int iKey)
    {
        this.miKey = iKey;
    }

    public int GetKey()
    {
        return miKey;
    }

    public string Encrypt(string strInput)
    {
        System.Text.StringBuilder strBuild = new System.Text.StringBuilder();
        foreach (char i in strInput)
        {
            strBuild.Append((char)((int)(i) + miKey));
        }

        return strBuild.ToString();
    }

    public string UnEncrypt(string strInput)
    {
        System.Text.StringBuilder strBuild = new System.Text.StringBuilder();
        foreach (char i in strInput)
        {
            strBuild.Append((char)((int)(i) - miKey));
        }

        return strBuild.ToString();
    }
}

class Caesar
{
    public static void Main(string[] args)
    {// args[0] = C or U | args[1] = integer key

        int iKey = args[1][0];
        System.IO.StreamReader Reader = new System.IO.StreamReader("text.txt");
        System.IO.StreamWriter Writer = new System.IO.StreamWriter("output.txt");
        Crypto myCrypto = new Crypto(iKey);
        string strLine;

        switch (args[0][0])
        {
            case 'C':// encode
                while (!Reader.EndOfStream)
                {
                    strLine = Reader.ReadLine();
                    Writer.WriteLine(myCrypto.Encrypt(strLine));
                }
            break;

            case 'U':// unencode
                while (!Reader.EndOfStream)
                {
                    strLine = Reader.ReadLine();
                    Writer.WriteLine(myCrypto.UnEncrypt(strLine));
                }
            break;

            default:
                Console.WriteLine("Usage: <exec> <U | C> <int key>");
            break;
        }

        Reader.Close();
        Writer.Close();
        Console.WriteLine("Program Done, press any key to quit");
        Console.ReadKey();
    }
}