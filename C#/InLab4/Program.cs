using System;
using System.Collections.Generic;
using System.Text;

namespace InLab4
{
    class Program
    {
        static void Main(string[] args)
        {
            employee[] raEmps = new employee[3];
            raEmps[0] = new employee("Alberto Martinez");
            raEmps[1] = new ContractEmp("Shawn Hupp");
            raEmps[2] = new SalariedEmp("Pedro Infante");

            for (int i = 0; i < 3; ++i)
            {
                raEmps[i].CalcPay();
            }

            Console.ReadKey();
        }
    }
}
