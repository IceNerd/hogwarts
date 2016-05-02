using System;
using System.Collections.Generic;
using System.Text;

namespace InLab4
{
    class employee
    {
        protected string mstrName;

        public employee(string strInit)
        {
            
            this.mstrName = strInit;
        }

        public string Name
        {
            get
            {
                return this.mstrName;
            }
        }

        virtual public void CalcPay()
        {
            Console.WriteLine("Employee: {0}", this.mstrName);
        }
    }

    class ContractEmp : employee
    {
        public ContractEmp(string strInit) : base(strInit)
        {
        }

        public override void CalcPay()
        {
            Console.WriteLine("Contract Employee: {0}", base.mstrName);
        }
    }

    class SalariedEmp : employee
    {
        public SalariedEmp(string strInit)
            : base(strInit)
        {
        }

        public override void CalcPay()
        {
            Console.WriteLine("Salaried Employee: {0}", base.mstrName);
        }
    }
}
