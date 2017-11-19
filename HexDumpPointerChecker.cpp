#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <ctime>


using namespace std;

string ToHex(long long int Val);
string GetNibble(int Nibble);
long long int ToDec(string Val);
char GetValHex(char input);
bool InvalidTargetPointer(string Trg);

bool FollowPointer(string Pntr, string &Val, string &Adr);

int PointerDepthASDF;
string clearstringasdf;
string frstAdr;
string StartAdrASDF;
ifstream InFileASDF;
ifstream PointerFile;
int main()
{


B:

	

	cout << "Made by: Skoolzout1\n======================================================================\n\n";
	cout << "Make sure your dump file is located in this program's same directory,\n and is a .bin\n\n\n";
	cout << "Enter Name of .bin file to open within this directory\nYOU DO NOT NEED TO ADD '.bin' TO THE NAME \n\n File name is NOT case sensitive\n\n";
	string InPath;
	cin >> InPath;
	InPath += ".bin";
	

	


	InFileASDF.open(InPath.c_str(), ios::binary);



	while (!InFileASDF.is_open())
	{
		perror("File Open Error: \n");
		cout << "\nEnter Name of .bin file to open within this directory: \n";
		cin >> InPath;
		InPath += ".bin";
		InFileASDF.open(InPath.c_str());
	}

	cout << "Enter Dump Start address: ";
	cin >> StartAdrASDF;
	while (StartAdrASDF.size() != 8)
	{
		cout << "Starting Address is not 32bits in length. Please Re-enter:\n";
		cin >> StartAdrASDF;
	}
	StartAdrASDF = ToHex(ToDec(StartAdrASDF)); //Convert to Upper case
A:

	getline(cin, clearstringasdf);

	cout << "Enter 1 to follow a pointer, Or Enter 2 to Burst Read a list of Pointers from a file.\n";
	string SearchType;

	cin >> SearchType;

	while (SearchType != "1" && SearchType != "2")
	{
		cout << "Invalid entry for Search type.";
		cout << "Enter 1 to follow a pointer, Or Enter 2 to Burst Read a list of Pointers from a file.\n";
		cin >> SearchType;
	}

	if (SearchType == "1")
	{
		cout << "Type 'showme' to see example pointer equation\n";
		cout << "Enter Pointer equation: ";
		string TargetPointer;
		string Value;
		string Address;
		getline(cin, clearstringasdf);
		getline(cin, TargetPointer);
		while (TargetPointer == "showme")
		{
			cout << "Example 1 Stage pointer: [0x101C1D40] + 0x2580\n";
			cout << "Example 4 Stage pointer: [[[[0x101C1D40] + 0x2580] + 0xB24] + 0x40] + 0x980\n";
			cout << "Enter Pointer equation: ";
			getline(cin, TargetPointer);
		}
		while (!InvalidTargetPointer(TargetPointer))
		{
			cout << "\n\nInvalid Pointer equation\n";
			cout << "Type 'showme' to see example pointer equation\n";
			cout << "Enter Pointer equation: ";
			getline(cin, TargetPointer);
			while (TargetPointer == "showme")
			{
				cout << "Example 1 Stage pointer: [0x101C1D40] + 0x2580\n";
				cout << "Example 4 Stage pointer: [[[[0x101C1D40] + 0x2580] + 0xB24] + 0x40] + 0x980\n";
				cout << "Enter Pointer equation: ";
				getline(cin, TargetPointer);
			}
		}
		if (FollowPointer(TargetPointer, Value, Address))
		{
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPoints to the address of: " << Address << endl;
			cout << "Value inside of " << Address << ": " << Value << endl << endl;
			int AsDec = ToDec(Value);
			char CharArray[4];
			string AsString;
			for (int i = 0; i < 4; i++)
			{
				CharArray[3-i] = (AsDec >> (8 * i)) & 0xFF;
			}
			for (int i = 0; i < 4; i++)
			{
				AsString += CharArray[i];
			}
			
			float AsFloat = *(float*)&AsDec;
			cout << "Value in Decimal: " << AsDec;
			cout << "\nValue as String: " << AsString;
			cout << "\nValue as Float: " << AsFloat << endl << endl;
		}
		else
		{
			cout << "Pointer Reaches invalid location. Potentially outside of Dump Region.\n";
		}

		string response;
		cout << "\nWould you like to enter another pointer to follow?\n type Y for yes, and N for no:\n";
		cin >> response;
		while (response != "Y" && response != "y" && response != "N" && response != "n")
		{
			cout << "Invalid response, please re-enter:\n";
			cout << "\nWould you like to enter another pointer to follow?\n type Y for yes, and N for no:\n";
			cin >> response;
		}

		if (response == "Y" || response == "y")
		{
			response = "";
			cout << "\nUse the same Dump file? (Y/N): ";
			cin >> response;
			while (response != "Y" && response != "y" && response != "N" && response != "n")
			{
				cout << "Invalid response, please re-enter:\n";
				cout << "\nUse the same Dump file? (Y/N): ";
				cin >> response;
			}
			if (response == "Y" || response == "y")
			{
				goto A;
			}
			else if (response == "N" || response == "n")
			{
				getline(cin, clearstringasdf);
				goto B;
			}

		}
	}
	else
	{
		string PntrFileName;
		cout << "Ensure the file containing the pointers is in the same directory as this EXE.\n";
		cout << "Pointers should be seperated by a return (Enter).\n";
		cout << "This program will output a text file with the pointers that successfully reach\na specified target address. It will be located in this directory with\n its name being the current Epoch time in Hex\n";
		cout << "If you are Burst Reading a list of Pointers from a file\nENSURE THERE ISNT A SPACE AT THE BOTTOM OF THE TEXT FILE.\n";
		cout << "\n\nEnter the name of the file containing the Pointers, WITHOUT the .txt\n";
		cin >> PntrFileName;
		PntrFileName += ".txt";
		PointerFile.open(PntrFileName.c_str(), ios::binary);
		while (!PointerFile.is_open())
		{
			perror("File Open Error: \n");
			cout << "\n\nEnter the name of the file containing the Pointers, WITHOUT the .txt\n";
			cin >> PntrFileName;
			PntrFileName += ".txt";
			PointerFile.open(PntrFileName.c_str());
		}
		unsigned int LineNum = 1;
		string X;
		vector<string>Pointerz;
		vector<string>GoodPointerz;
		string Target;
		string Value;
		string Address;
		string response;
		cout << "\nEnter 1 to Filter out pointers that do not point to an address\n Or Enter 2 to Filter Pointers out that do not Point to a certain Value\n Or Enter 3 to just keep Pointers that point to valid addresses\n";
		cin >> response;
		while (response != "1" && response != "2" && response != "3")
		{
			cout << "Invalid entry for Filter type.";
			cout << "\nEnter 1 to Filter out pointers that do not point to an address\n Or Enter 2 to Filter Pointers out that do not Point to a certain Value\n Or Enter 3 to just keep Pointers that point to valid addresses\n";
			cin >> response;
		}

		if (response == "1")
		{
			cout << "Enter Target Address\n";
			cin >> Target;
			while (Target.size() != 8 || !Target.size())
			{
				cout << "Address is not 32 bits in length.. Please Re-enter\n";
				cout << "\nEnter Target Address\n";
				cin >> Target;
			}
			Target = ToHex(ToDec(Target)); //Lazy expensive way to convert to upper case.
		}
		else if (response == "2")
		{
			cout << "Enter Target Value\n";
			cin >> Target;
			while (Target.size() > 8 || !Target.size())
			{
				cout << "Value can't be greater than 32bits or equal 0.. Please Re-enter\n";
				cout << "\nEnter Target Value\n";
				cin >> Target;
			}
			Target = ToHex(ToDec(Target)); //Lazy expensive way to convert to upper case.
		}
		
		

		//Get Pointers from file
		while (!PointerFile.fail())
		{
			X = "";
			while (PointerFile.peek() != '\n' && !PointerFile.eof())
			{
				X += PointerFile.get();
			}
			if (InvalidTargetPointer(X))
			{
				Pointerz.push_back(X);
			}
			else
			{
				cout << "\nError is on line: " << LineNum << endl;
				cout << "Pointer in Question: " << X << endl;
				cout << "Please fix the pointer and reopen the program\n";
				cin >> clearstringasdf;
				exit(1);
			}
			while (PointerFile.peek() == '\n')
			{
				clearstringasdf = PointerFile.get();
			}
			LineNum++;
		}

		if (PointerFile.eof())
		{
			cout << "All Pointers are formatted correctly!\n";
			cout << "Counted " << Pointerz.size() << " Pointers\n\nNow Following Pointers...\n";

			if (response == "1")
			{
				for (int i = 0; i < Pointerz.size(); i++)
				{
					if (FollowPointer(Pointerz[i], Value, Address))
					{

						if (Address == Target)
						{
							GoodPointerz.push_back(Pointerz[i]);
						}
					}
				}
			}
			else if (response == "2")
			{
				for (int i = 0; i < Pointerz.size(); i++)
				{
					if (FollowPointer(Pointerz[i], Value, Address))
					{

						if (Value == Target)
						{
							GoodPointerz.push_back(Pointerz[i]);
						}
					}
				}
				
			}
			else
			{
				for (int i = 0; i < Pointerz.size(); i++)
				{
					if (FollowPointer(Pointerz[i], Value, Address))
					{
							GoodPointerz.push_back(Pointerz[i]);
					}
				}
			}
			

			cout << "Done!\n Eliminated " << Pointerz.size() - GoodPointerz.size() << " bad pointers.\n";
			cout << "Now outputting remaining pointers to text file...\n";
			ofstream OutFile;
			string OutPath = ToHex(time(NULL));
			OutPath += ".txt";
			OutFile.open(OutPath.c_str());

			if (OutFile.is_open())
			{
				for (int i = 0; i < GoodPointerz.size(); i++)
				{
					OutFile << GoodPointerz[i];
					if (i != (GoodPointerz.size() - 1))
					{
						OutFile << endl;
					}
				}
				
				cout << "Done Writing! Check " << OutPath << " for valid pointers.\n";
				OutFile.close();
			}
			else
			{
				cout << "Error creating Output file.. Aborting.\n";
				cin >> clearstringasdf;
				OutFile.close();
				exit(1);
			}
			
			cout << "\nWould you like to enter another pointer to follow?\n type Y for yes, and N for no:\n";
			cin >> response;
			while (response != "Y" && response != "y" && response != "N" && response != "n")
			{
				cout << "Invalid response, please re-enter:\n";
				cout << "\nWould you like to enter another pointer to follow?\n type Y for yes, and N for no:\n";
				cin >> response;
			}

			if (response == "Y" || response == "y")
			{
				response = "";
				cout << "\nUse the same Dump file? (Y/N): ";
				cin >> response;
				while (response != "Y" && response != "y" && response != "N" && response != "n")
				{
					cout << "Invalid response, please re-enter:\n";
					cout << "\nUse the same Dump file? (Y/N): ";
					cin >> response;
				}
				if (response == "Y" || response == "y")
				{
					PointerFile.close();
					goto A;
				}
				else if (response == "N" || response == "n")
				{
					getline(cin, clearstringasdf);
					PointerFile.close();
					InFileASDF.close();
					goto B;
				}

			}

		}
		else
		{
			cout << "Error Reading Data, Aborting..";
			cin >> clearstringasdf;
			exit(1);
		}
	}

	


	

	
	
	PointerFile.close();
	InFileASDF.close();




	return 0;
}

string ToHex(long long int Val)
{
	long long int Input = Val;
	string Output;
	bool Done = 0;
	double Blah = 0;
	long long int Blah2 = 0;
	double Blah3 = 0;
	long long int Blah4 = 0;
	string Letter;
	while (!Done)
	{
		if (Input < 0)
		{
			Input = 0x100000000 + Input;
		}
		if (Input / 16.0 > 0)
		{
			Blah = Input / 16.0;
			Blah4 = Blah;
			Blah3 = Blah4;
			Blah -= Blah4;
			Blah2 = Blah * 16;
			Letter = GetNibble(Blah2);
			Output += Letter;
			Input = Blah3;
		}
		else
		{
			Done = 1;
		}

	}

	string dummeh = Output;

	for (int i = Output.length() - 1; i >= 0; i--)
	{
		char fml = dummeh[Output.length() - 1 - i];
		Output[i] = fml;
	}

	return Output;
}

string GetNibble(int Nibble)
{
	if (Nibble == 0)
	{
		return "0";
	}
	else if (Nibble == 1)
	{
		return "1";
	}
	else if (Nibble == 2)
	{
		return "2";
	}
	else if (Nibble == 3)
	{
		return "3";
	}
	else if (Nibble == 4)
	{
		return "4";
	}
	else if (Nibble == 5)
	{
		return "5";
	}
	else if (Nibble == 6)
	{
		return "6";
	}
	else if (Nibble == 7)
	{
		return "7";
	}
	else if (Nibble == 8)
	{
		return "8";
	}
	else if (Nibble == 9)
	{
		return "9";
	}
	else if (Nibble == 10)
	{
		return "A";
	}
	else if (Nibble == 11)
	{
		return "B";
	}
	else if (Nibble == 12)
	{
		return "C";
	}
	else if (Nibble == 13)
	{
		return "D";
	}
	else if (Nibble == 14)
	{
		return "E";
	}
	else if (Nibble == 15)
	{
		return "F";
	}

}

long long int ToDec(string Val)
{
	string Input = Val;

	int i = Input.length() - 1;
	long long int Output = 0;
	int BS = 0;
	for (; i >= 0; i--)
	{
		BS = GetValHex(Input[i]);
		Output += pow(16, Input.length() - 1 - i) * BS;
	}


	return Output;


}

char GetValHex(char input)
{
	if (input == '0')
	{
		return 0;
	}
	else if (input == '1')
	{
		return 1;
	}
	else if (input == '2')
	{
		return 2;
	}
	else if (input == '3')
	{
		return 3;
	}
	else if (input == '4')
	{
		return 4;
	}
	else if (input == '5')
	{
		return 5;
	}
	else if (input == '6')
	{
		return 6;
	}
	else if (input == '7')
	{
		return 7;
	}
	else if (input == '8')
	{
		return 8;
	}
	else if (input == '9')
	{
		return 9;
	}
	else if (input == 'A' || input == 'a')
	{
		return 10;
	}
	else if (input == 'B' || input == 'b')
	{
		return 11;
	}
	else if (input == 'C' || input == 'c')
	{
		return 12;
	}
	else if (input == 'D' || input == 'd')
	{
		return 13;
	}
	else if (input == 'E' || input == 'e')
	{
		return 14;
	}
	else if (input == 'F' || input == 'f')
	{
		return 15;
	}
	else
	{
		return 99;
	}
}

bool InvalidTargetPointer(string Trg)
{

	int leftcount = 0;
	int rightcount = 0;

	for (int i = 0; i < Trg.size(); i++)
	{
		if (Trg[i] == '[')
		{
			leftcount++;
		}
		if (Trg[i] == ']')
		{
			rightcount++;
		}
	}
	PointerDepthASDF = leftcount;
	if (leftcount != rightcount)
	{
		cout << "uneven amount of brackets\n";
		return false;
	}
	else if (!leftcount || !rightcount)
	{
		cout << "\n\nThat wasn't even close to the correct format.. You're good!\n";
		return false;
	}
	frstAdr = "";
	int i = PointerDepthASDF + 2;
	while (Trg[i] != ']')
	{
		frstAdr += Trg[i];
		i++;
	}

	if (frstAdr < StartAdrASDF)
	{
		cout << "\nInitial address of " << frstAdr << " is less than the start address of " << StartAdrASDF;
		return false;
	}

	for (int i = PointerDepthASDF - 1; i < Trg.size(); i++)
	{
		if (Trg[i] == '[')
		{
			if (Trg[i + 1] != '0')
			{
				cout << "Missing the '0x' in front of an address\n";
				return false;
			}
			else if (Trg[i + 2] != 'x' && Trg[i + 2] != 'X')
			{
				cout << "Missing the '0x' in front of an address\n";
				return false;
			}
		}
		if (Trg[i] == ']')
		{
			if (Trg[i + 4] != '0')
			{
				cout << "Improper spacing between adresses and offsets in written equation,\n or missing 0x in front of offset\n";
				return false;
			}
			else if (Trg[i + 5] != 'x' && Trg[i + 5] != 'X')
			{
				cout << "Missing the 'x' between the offset\n";
				return false;
			}
		}

	}


	return true;
}

bool FollowPointer(string Pntr, string &Val, string &Adr)
{
	bool PntrIsValid = true;
	InFileASDF.clear();
	vector<long long int> Offsets;
	const int DATASIZE = 4;

	for (int i = 0; i < Pntr.size(); i++)
	{
		if (Pntr[i] == ']')
		{
			string dummy;
			if (Pntr[i + 2] == '+')
			{
				for (int count = i + 6; GetValHex(Pntr[count]) != 99; count++)
				{
					dummy += Pntr[count];
				}
				Offsets.push_back(ToDec(dummy));
			}
			else if (Pntr[i + 2] == '-')
			{
				for (int count = i + 6; GetValHex(Pntr[count]) != 99; count++)
				{
					dummy += Pntr[count];
				}
				Offsets.push_back(0 - ToDec(dummy));
			}
			else
			{
				cout << "Error!";
				exit(1);
			}
		}
	}

	int leftcount = 0;

	for (int i = 0; i < Pntr.size(); i++)
	{
		if (Pntr[i] == '[')
		{
			leftcount++;
		}

	}
	PointerDepthASDF = leftcount;

	frstAdr = "";
	int i = PointerDepthASDF + 2;
	while (Pntr[i] != ']')
	{
		frstAdr += Pntr[i];
		i++;
	}

	//Pointer Following

	InFileASDF.seekg(ToDec(frstAdr) - ToDec(StartAdrASDF));



	for (int count = 0; count < PointerDepthASDF; count++)
	{
		int x = 0;
		for (int i = 0; i < DATASIZE; i++)
		{
			//x |= (InFileASDF.get() << 8 * (DATASIZE - 1 - i));
			int y = InFileASDF.get();
			y <<= 8 * (DATASIZE - 1 - i);
			x |= y;
		}
		if (x < ToDec(StartAdrASDF))
		{
			PntrIsValid = false;
			break;
		}
		else
		{
			InFileASDF.seekg(x - ToDec(StartAdrASDF) + Offsets[count]);
		}

	}

	Adr = ToHex((InFileASDF.tellg()) + ToDec(StartAdrASDF));
	InFileASDF.seekg(ToDec(Adr) - ToDec(StartAdrASDF));
	int dummy = 0;
	for (int i = 0; i < DATASIZE; i++)
	{
		dummy |= (InFileASDF.get() << 8 * (DATASIZE - 1 - i));

	}

	Val = ToHex(dummy);


	if (Val.size() < 8)
	{
		string dummystr;
		for (int i = 8 - Val.size(); i > 0; i--)
		{
			dummystr += "0";
		}
		Val = dummystr + Val;
	}

	


	/*if (Stream.fail())
	{
		if (Stream.eof())
		{
			cout << "End of file reached..... this shouldn't have happened?\n";
		}
		else
		{
			cout << "Error occured, Invald Data Received.. please close and retry\n";
			getline(cin, Pntr);
			exit(1);
		}
	}*/

	return PntrIsValid;
}