using System;
using System.Collections.Generic;
using System.Text;

namespace CollegeXP
{
    class CollegeExperiences
    {
        private string mstrWhat;
        private DateTime mdtWhen;

        public string WhatHappened
        {
            get
            {
                return this.mstrWhat;
            }
            set
            {
                this.mstrWhat = value;
            }
        }

        public DateTime WhenItHappened
        {
            get
            {
                return this.mdtWhen;
            }
            set
            {
                this.mdtWhen = value;
            }
        }

        override public string ToString()
        {
            StringBuilder strTemp = new StringBuilder();

            strTemp.Append(this.mdtWhen.ToLongDateString());
            strTemp.Append(" : ");
            strTemp.Append(this.mstrWhat);

            return strTemp.ToString();
        }
    }
}
