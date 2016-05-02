using System;
using System.Collections.Generic;
using System.Text;

namespace OpOverloading
{
    class ComplexNumber
    {
        private int miReal;
        private int miImaginary;

        public int Real
        {
            get
            {
                return this.miReal;
            }
            set
            {
                this.miReal = value;
            }
        }

        public int Imaginary
        {
            get
            {
                return this.miImaginary;
            }
            set
            {
                this.miImaginary = value;
            }
        }

        // override ToString()
        public override string ToString()
        {
            StringBuilder strBuild = new StringBuilder();
            strBuild.Append("(");
            strBuild.Append(this.miReal);
            strBuild.Append("+");
            strBuild.Append(this.miImaginary);
            strBuild.Append("i)");
            return strBuild.ToString();
        }

        // operator overloading
        public static ComplexNumber operator +(ComplexNumber Left, ComplexNumber Right)
        {
            ComplexNumber Temp = new ComplexNumber();
            Temp.Real = Left.Real + Right.Real;
            Temp.Imaginary = Left.Imaginary + Right.Imaginary;
            return Temp;
        }

        public static ComplexNumber operator -(ComplexNumber Left, ComplexNumber Right)
        {
            ComplexNumber Temp = new ComplexNumber();
            Temp.Real = Left.Real - Right.Real;
            Temp.Imaginary = Left.Imaginary - Right.Imaginary;
            return Temp;
        }

    }
}
