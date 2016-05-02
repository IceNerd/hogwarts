using System;
using System.Collections.Generic;
using System.Text;
using OpOverloading;

namespace InLab4
{
    class Program
    {
        static void Main(string[] args)
        {
            ComplexNumber[] raCmplx = new ComplexNumber[4];
            ComplexNumber TempCmplx = new ComplexNumber();

            Console.WriteLine("Initial Values");
            for (int i = 0; i < 4; ++i)
            {
                raCmplx[i] = new ComplexNumber();
                raCmplx[i].Real = (i*2);
                raCmplx[i].Imaginary = (i*2) + 1;

                Console.WriteLine(raCmplx[i].ToString());
            }

            Console.WriteLine("Test Operator Overloading");
            TempCmplx = raCmplx[0] + raCmplx[1];
            Console.WriteLine("C1 + C2 = {0}", TempCmplx.ToString());

            TempCmplx = raCmplx[3] - raCmplx[2];
            Console.WriteLine("C4 - C3 = {0}", TempCmplx.ToString());

            Console.ReadKey();
        }
    }
}
