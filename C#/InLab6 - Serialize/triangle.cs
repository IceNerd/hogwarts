using System;
using System.Collections.Generic;
using System.Text;

/// <summary>
/// Simple class which holds 2 integer data members.
/// </summary>
public class Triangle
{
    private int miUno;
    private int miDos;

    // default public constructor
    public Triangle()
    {
    }

    /// <summary>
    /// Makes private member miUno a property
    /// </summary>
    public int Uno
    {
        get
        {
            return miUno;
        }
        set
        {
            this.miUno = value;
        }
    }

    /// <summary>
    /// Makes private member miDos a property
    /// </summary>
    public int Dos
    {
        get
        {
            return miDos;
        }
        set
        {
            this.miDos = value;
        }
    }
}
