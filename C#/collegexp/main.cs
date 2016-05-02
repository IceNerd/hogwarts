using System;

namespace CollegeXP
{
    class StudentDriver
    {
        public static void Main(string[] args)
        {
            try
            {
                Student myStudent = new Student();
                CollegeExperiences myXP = new CollegeExperiences();
                CollegeExperiences myXP2 = new CollegeExperiences();
                CollegeExperiences myXPSuspended = new CollegeExperiences();

                myXP.WhatHappened = "Study";
                myXP.WhenItHappened = DateTime.Now;

                myXP2.WhatHappened = "Test";
                myXP2.WhenItHappened = DateTime.Now;

                myXPSuspended.WhatHappened = "Suspended";
                myXPSuspended.WhenItHappened = DateTime.Now;

                myStudent.HaveCollegeExperience(myXP);
                myStudent.HaveCollegeExperience(myXP2);
                myStudent.HaveCollegeExperience(myXPSuspended);
                myStudent.HaveCollegeExperience(myXP);
                myStudent.HaveCollegeExperience(myXP2);
                //myStudent.HaveCollegeExperience(myXPSuspended);

                Console.WriteLine(myStudent.FunStuff);
            }
            catch (StudentException err)
            {
                Console.WriteLine(err.ToString());
            }
            finally
            {
                Console.WriteLine("Program Done: Please press any key to quit");
                Console.ReadKey();
            }
        }
    }
}