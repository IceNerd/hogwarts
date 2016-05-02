using System;
using System.Collections.Generic;
using System.Text;

    class ByTwos : ISeries
    {
        private int iStart;
        private int iVal;

        public ByTwos()
        {
            iStart = 0;
            iVal = 0;
        }

        public int GetNext()
        {
            iVal += 2;

            return iVal;
        }

        public void ResetIt()
        {
            iVal = iStart;
        }

        public void SetStart(int iSet)
        {
            iStart = iSet;
            this.ResetIt();
        }
    }
