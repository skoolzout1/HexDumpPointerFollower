#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

string ToHex(long long int Val);
string GetNibble(int Nibble);
long long int ToDec(string Val);
char GetValHex(char input);
bool InvalidTarget(string Trg);

int PointerDepthASDF;
string clearstringasdf;
string frstAdr;
string StartAdrASDF;
int main()
{

	
B:

	ifstream InFile;
  
	cout << "Made by: Skoolzout1\n======================================================================\n\n";
	cout << "Make sure your dump file is located in this program's same directory,\n and is a .bin\n\n\n";
	string InPath;
	cout << "Enter Name of .bin file to open within this directory\nYOU DO NOT NEED TO ADD '.bin' TO THE NAME \n\n File name is NOT case sensitive\n\n";
	cin >> InPath;
	InPath += ".bin";



	InFile.open(InPath.c_str());



	while (!InFile.is_open())
	{
		perror("File Open Error: \n");
		cout << "\nEnter Name of .bin file to open within this directory: \n";
		cin >> InPath;
		InPath += ".bin";
		InFile.open(InPath.c_str());
	}
	
	cout << "Enter Dump Start address: ";
	cin >> StartAdrASDF;
	while (StartAdrASDF.size() != 8)
	{
		cout << "Starting Address is not 32bits in length. Please Re-enter:\n";
		cin >> StartAdrASDF;
	}
	A:

	getline(cin, clearstringasdf);

	cout << "Type 'showme' to see example pointer equation\n";
	cout << "Enter Pointer equation: ";
	string Target;
	

	getline(cin, Target);
	while (Target == "showme")
	{
		cout << "Example 1 Stage pointer: [0x101C1D40] + 0x2580\n";
		cout << "Example 4 Stage pointer: [[[[0x101C1D40] + 0x2580] + 0xB24] + 0x40] + 0x980\n";
		cout << "Enter Pointer equation: ";
		getline(cin, Target);
	}
	while (!InvalidTarget(Target))
	{
		cout << "\n\nInvalid Pointer equation\n";
		cout << "Type 'showme' to see example pointer equation\n";
		cout << "Enter Pointer equation: ";
		getline(cin, Target);
		while (Target == "showme")
		{
			cout << "Example 1 Stage pointer: [0x101C1D40] + 0x2580\n";
			cout << "Example 4 Stage pointer: [[[[0x101C1D40] + 0x2580] + 0xB24] + 0x40] + 0x980\n";
			cout << "Enter Pointer equation: ";
			getline(cin, Target);
		}
	}
	
	
	string Value;
	string Address;


	vector<long long int> Offsets;




	const int DATASIZE = 4;
	

	
	for (int i = 0; i < Target.size(); i++)
	{
		if (Target[i] == ']')
		{
			string dummy;
			if (Target[i + 2] == '+')
			{
				for (int count = i + 6; GetValHex(Target[count]) != 99; count++)
				{
					dummy += Target[count];
				}
				Offsets.push_back(ToDec(dummy));
			}
			else if (Target[i + 2] == '-')
			{
				for (int count = i + 6; GetValHex(Target[count]) != 99; count++)
				{
					dummy += Target[count];
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

	InFile.seekg(ToDec(frstAdr) - ToDec(StartAdrASDF));
	for (int count = 0; count < PointerDepthASDF; count++)
	{
		int x = 0;
		for (int i = 0; i < DATASIZE; i++)
		{
			x |= (InFile.get() << 8 * (DATASIZE - 1 - i));

		}
		InFile.seekg(x - ToDec(StartAdrASDF) + Offsets[count]);
	}

	Address = ToHex((InFile.tellg()) + ToDec(StartAdrASDF));
	InFile.seekg(ToDec(Address) - ToDec(StartAdrASDF));
	int dummy = 0;
	for (int i = 0; i < DATASIZE; i++)
	{
		dummy |= (InFile.get() << 8 * (DATASIZE - 1 - i));

	}

	Value = ToHex(dummy);
	//char Val[8];
	//itoa(dummy,Val,16);
	
	if (Value.size() < 8)
	{
		string dummystr;
		for (int i = 8 - Value.size(); i > 0; i--)
		{
			dummystr += "0";
		}
		Value = dummystr + Value;
	}

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPoints to the address of: " << Address << endl;
	cout << "Value inside of " << Address << ": " << Value << endl << endl;


	if (InFile.fail())
	{
		if (InFile.eof())
		{
			cout << "End of file reached..... this shouldn't have happened?\n";
		}
		else
		{
			cout << "Error occured, no idea what.. please close and retry\n";
			getline(cin, Target);
			exit(1);
		}
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


	InFile.close();




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

bool InvalidTarget(string Trg)
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
	for (int i = PointerDepthASDF + 2; i < (8 + PointerDepthASDF + 2); i++)
	{
		frstAdr += Trg[i];
	}

	if (frstAdr < StartAdrASDF)
	{
		cout << "\nInitial address of " << frstAdr << " is less than the start address of " << StartAdrASDF;
		return false;
	}

	for (int i = PointerDepthASDF -1; i < Trg.size(); i++)
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

