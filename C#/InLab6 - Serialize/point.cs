using System;
using System.Collections.Generic;
using System.Text;

public class Point
{
    private int[] miraLoc;

    public Point()
    {
        miraLoc = new int[3];
        miraLoc[0] = 0;
        miraLoc[1] = 0;
        miraLoc[2] = 0;
    }

    public int[] Loc
    {
        get
        {
            return miraLoc;
        }

        set
        {
            if (value == null)
            {
                return;
            }

            int[] iraRetrieve = (int[])value;
            for (int i = 0; i < 3; ++i)
            {
                miraLoc[i] = iraRetrieve[i];
            }
        }
    }
    }
