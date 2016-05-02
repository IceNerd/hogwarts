using System;

class Program
{
    public struct MyStruct
    {
        public int x;
        public int y;
    }

    public static void Main(string[] args)
    {
        int[] raInts = new int[3] { 1, 2, 3 };

        Console.WriteLine("--- Contents of Integer Array ---");
        foreach (int i in raInts)
        {
            Console.WriteLine(i.ToString());
        }

        raInts[0] = FooInt(raInts[0]);
        raInts[1] = FooInt32(raInts[1]);
        raInts[2] = FooIntByRef(ref raInts[2]);

        Console.WriteLine("--- Contents of Integer Array After Calls ---");
        foreach (int i in raInts)
        {
            Console.WriteLine(i.ToString());
        }

        //----------------------------------------------------------------

        MyStruct[] raStruct = new MyStruct[4];
        for (int i = 0; i < 4; ++i)
        {
            raStruct[i].x = 123;
            raStruct[i].y = 456;
        }

        // box these up before making calls
        Object SendSetObject = raStruct[1];
        Object SendSetObjectRef = raStruct[3];

        // make the calls to each of the methods to test boxing
        raStruct[0] = SetStructure(raStruct[0]);
        raStruct[1] = (MyStruct)SetObject(SendSetObject);
        raStruct[2] = SetStructureRef(ref raStruct[2]);
        raStruct[3] = (MyStruct)SetObjectRef(ref SendSetObjectRef);

        Console.WriteLine("--- Contents of Structs After Calls ---");
        foreach (MyStruct structure in raStruct)
        {
            Console.WriteLine("X:{0} Y:{1}", structure.x, structure.y);
        }

        //----------------------------------------------------------------

        Console.WriteLine("Press any key to continue");
        Console.ReadKey();
    }

    public static int FooInt(int iInput)
    {
        iInput += 1;
        return iInput;
    }

    public static Int32 FooInt32(Int32 iInput)
    {
        iInput += 1;
        return iInput;
    }

    public static int FooIntByRef(ref int piInput)
    {
        piInput += 1;
        return piInput;
    }

    public static MyStruct SetStructure(MyStruct sInput)
    {
        sInput.x = 456;
        sInput.y = 123;

        return sInput;
    }

    public static Object SetObject(Object oInput)
    {
        // take it out of the box
        MyStruct sOOB = (MyStruct)oInput;
        sOOB.x = 456;
        sOOB.y = 123;

        oInput = sOOB;

        return oInput;
    }

    public static MyStruct SetStructureRef(ref MyStruct psInput)
    {
        psInput.x = 456;
        psInput.y = 123;

        return psInput;
    }

    public static Object SetObjectRef(ref Object poInput)
    {
        // take it out of the box
        MyStruct sOOB = (MyStruct)poInput;
        sOOB.x = 456;
        sOOB.y = 123;

        poInput = sOOB;

        return poInput;
    }
}
