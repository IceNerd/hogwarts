/*************************************************************************
* Author:					Alberto Martinez
* Date Created:				05.03.2004
* Last Modification Date:	05.03.2004
* Lab Number:				CST 211 Lab 3
* Filename:					main.cpp
*
* Overview:
*	This program will encode and decode morse code from a file.  The file
*		provided consists of morse code.  Each letter on each line.  A
*		space is identified by four '-' or "----".  The program will read
*		the data from the file to a Queue and then decode it.  The decoded
*		data will go into a String.  From that, then, the program will
*		encode the string.
*
* Input:
*	Morse Code from file.
*
* Output:
*	String and Morse Code
*	
*************************************************************************/


#include <iostream>
using std::cout;

#include <fstream>
using std::ifstream;

#include "String.h"
#include "Error.h"
#include "cMorse.h"

int main()
{
	try
	{
		cMorse MorseCode("Morse.DAT");
		ifstream infile;
		tQueue< String > CodeList;

		cout<<"Getting Data from File\n";

		infile.open("Message.DAT");
		if(infile.is_open())
		{
			String FromFile;
			while(!(infile.eof()))
			{
				infile>>FromFile;
				CodeList.Enqueue(FromFile);
			}
		}
		infile.close();
		
		cout<<"Decoding Data\n";
		String Decoded;
		int howmany(0);
		while(!(CodeList.isEmpty()))
		{
			howmany++;
			Decoded += MorseCode.Decode(CodeList.Front());
			CodeList.Dequeue();
		}
		cout<<Decoded<<"\n";

		cout<<"Re-Encoding Data\n";
		for(int i = 0; i < howmany; i++)
		{
			cout<<Decoded[i]<<": "<<MorseCode.Encode(Decoded[i])<<"\n";
		}
	}
	catch(EXCEPTION& uhoh)
	{
		cout<<uhoh;
	}

}