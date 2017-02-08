#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <cmath> 

#define breakLine 150

using namespace std;

int main(int argc, char const *argv[]) 
{
	string fileName = argv[1];

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

	int size = data.size();
	// for (int i = 0; i < size; ++i)
	// {
	// 	cout << data[i];
	// }
	// cout << data;



	// 
	int textWidth = 150;
	int textHeight = ceil((float)size / textWidth);

	int maxWidth = ceil((float)textWidth*0.5);
	int minWidth = ceil((float)textWidth*0.2);
	int maxHeight = ceil((float)textHeight*0.5);
	int minHeight = ceil((float)textHeight*0.2);

	// cout << "textWidth: " << textWidth << endl;
	// cout << "textHeight: " << textHeight << endl << endl;

	// cout << "maxWidth: " << maxWidth << endl;
	// cout << "minWidth: " << minWidth << endl;
	// cout << "maxHeight: " << maxHeight << endl;
	// cout << "minHeight: " << minHeight << endl << endl;

	srand(time(NULL));
	int fragmentWidth = rand() % (maxWidth - minWidth + 1) + minWidth;
	int fragmentHeight = rand() % (maxHeight - minHeight + 1) + minHeight;

	// cout << "fragmentWidth: " << fragmentWidth << endl;
	// cout << "fragmentHeight: " << fragmentHeight << endl << endl;

	srand(time(NULL));
	int xPosition = rand() % ((maxWidth - fragmentWidth) - 0 + 1) + 0;
	int yPosition = rand() % ((maxHeight - fragmentHeight) - 0 + 1) + 0;

	// cout << "xPosition: " << xPosition << endl;
	// cout << "yPosition: " << yPosition << endl << endl;

	int xTotal = xPosition + fragmentWidth;
	int yTotal = yPosition + fragmentHeight;

	// cout << "xTotal: " << xTotal << endl;
	// cout << "yTotal: " << yTotal << endl << endl;



	// 
	// cout << data.substr(xPosition + (yPosition * textWidth) + (textWidth * 0), xTotal);
	// cout << endl;

	// cout << data.substr(xPosition + (yPosition * textWidth) + (textWidth * 1) + 1, xTotal);
	// cout << endl;

	// cout << data.substr(xPosition + (yPosition * textWidth) + (textWidth * 2) + 2, xTotal);
	// cout << endl;

	string fragment = "";
	for (int i = 0; i < yTotal; ++i)
	{
		// cout << data.substr(xPosition + (yPosition * textWidth) + yPosition + (textWidth * i) + i, xTotal);
		// cout << endl;
		
		fragment += data.substr(xPosition + (yPosition * textWidth) + yPosition + (textWidth * i) + i, xTotal) + "\n";
	}

	fragment = fragment.substr(0, fragment.size()-1);
	cout << fragment << endl;
	
	return 0;
}