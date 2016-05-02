using System;
using System.Collections;
using System.Text;

namespace CollegeXP
{
    class StudentException : Exception
    {
        public override string ToString()
        {
            return "You cannot be suspended twice!";
        }
    }

    class Student
    {
        public Student()
        {
            mraXP = new ArrayList();
        }

        private string mstrName;
        private ArrayList mraXP;

        public string Name
        {
            get
            {
                return mstrName;
            }

            set
            {
                mstrName = value;
            }
        }

        public ArrayList Experiences
        {
            get
            {
                return mraXP;
            }

            set
            {
                mraXP = value;
            }
        }

        public string FunStuff
        {
            get
            {
                return "Write Code";
            }
        }

        public void HaveCollegeExperience(CollegeExperiences AddMe)
        {
            if (AddMe.WhatHappened.ToLower().Equals("suspended"))
            {
                foreach (CollegeExperiences i in mraXP)
                {
                    if (i.WhatHappened.ToLower().Equals("suspended"))
                    {
                        //throw exception
                        throw new StudentException();
                    }
                }
            }
            mraXP.Add(AddMe);
        }
    }
}
