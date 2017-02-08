#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#define breakLine 150

using namespace std;

int main(int argc, char const *argv[]) 
{
	string fileName = argv[1];

	ifstream file(fileName.c_str());

	ifstream::pos_type fileSize = file.tellg();
	file.seekg(0, ios::beg);

	string line, data = "";

	while(getline(file, line))
	{
		data += line + " ";
	}

	int size = data.size()-1;

	data = data.substr(0, size);

	int control = 0;
	for (int i = 0; i < size; ++i)
	{

		if (isprint(data[i]))
		{
			if (control % (breakLine) == 0 && control != 0)
			{
				cout << endl;
			}
			
			cout << data[i];
			++control;
		}
	}

	return 0;
}