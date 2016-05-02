using System;
using System.Collections.Generic;
using System.Text;

class ByFives : ISeries
{
    private int iStart;
    private int iVal;

    public ByFives()
    {
        iStart = 0;
        iVal = 0;
    }

    public int GetNext()
    {
        iVal += 5;

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
