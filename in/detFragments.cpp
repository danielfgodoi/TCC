#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <cmath> 

using namespace std;

int main(int argc, char const *argv[]) 
{
	string fileName = argv[1];



	// 
	int deteriorationLevel;

	if (argv[2])
	{
		string level = argv[2];
		deteriorationLevel = atoi(level.c_str());
	}

	else
	{
		deteriorationLevel = 20;
	}



	// 
	ifstream file(fileName.c_str());
	ifstream::pos_type fileSize = file.tellg();
	file.seekg(0, ios::beg);

	string line;
	string data = "";

	while(getline(file, line))
	{
		data += line + "\n";
	}

	int size = data.size()-1;
	// cout << data;

	// for (int i = 0; i < size; ++i)
	// {
	// 	cout << data[i];
	// }



	// 
	int chars = size * deteriorationLevel / 100;
	int counter = 0;

	// cout << "deterioration level: " << deteriorationLevel << endl;
	// cout << "number of chars: " << size << endl;
	// cout << "1's: " << chars << endl;
	// cout << "0's: " << size - (chars) << endl;
	srand(time(NULL));
	
	int um = 0;
	int zero = 0;
	int r;

	// cout << data << endl << endl;
	int breakLine = 67;

	for (int i = 0; i < size; ++i)
	{
		if (deteriorationLevel == 5)
			r = rand() % 5;
		if (deteriorationLevel == 10)
			r = rand() % 5;
		if (deteriorationLevel == 20)
			r = rand() % 4;
		if (deteriorationLevel == 40)
			r = rand() % 2;
		if (deteriorationLevel == 80)
			r = rand() % 2;
		
		if (r == 1)
		{
			if (data[i] == '\n')
			{
				cout << data[i];
			}

			else
			{
				if (counter < chars)
				{
					cout << "?";
					++counter;
				}

				else
				{
					cout << data[i];
				}
			}
		}

		else
		{
			cout << data[i];
		}
	}

	// cout << endl;
	// cout << "number of ?'s: " << counter << endl;

	return 0;
}