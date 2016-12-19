#ifndef _BlockAlignment_h
#define _BlockAlignment_h

#include <fstream>
#include <iostream>
#include <vector>

#include <cstdlib>
#include <climits>
#include <ctime>

#include <iomanip>

using namespace std;

class BlockAlignment
{
public:
	// Class constructor
	BlockAlignment(vector<string> textFileNameList, string blockFileName)
	{
		this->textFileNameList = textFileNameList;
		this->blockFileName = blockFileName;
		bestResult.resize(2);
	};

	// Default destructor
	~BlockAlignment(){};
	
	// Public methods
	void align();

private:
	// Variables
	// Block and text sizes
	// int blockSizeN; // number of rows
	// vector<int> blockSizeM; // number of columns
	// int textSizeN; // number of rows
	// vector<int> textSizeM; // number of columns
	int textSize;
	int blockSize;
	
	int numberOfSequences;
	int sIterator;
	int sMax;
	int iMax;
	vector<string> textFileNameList;
	string textFileName;
	string blockFileName;
	// vector<string> textSequence;
	// vector<string> blockSequence;
	string textSequence;
	string blockSequence;
	string textSequenceResult;
	string blockSequenceResult;
	vector<string> bestResult;

	// vector<vector<char> > textData;
	// vector<vector<char> > blockData;
	string textData;
	string blockData;
	
	int similarity; // stores the similarities

	vector< vector<int> > alignment; // stores the alignments matrix

	int n; // Alignment matrix size (text width)
	int m; // Alignment matrix size (block width)

	// Methods
	void print();
	
	void readFile(string fileName, string &fileData);
	void prepareBlock();
	void prepareText();

	void getSequence(int n, int m);
	
	void globalAlignment(string textSequence, string blockSequence);
	void localAlignment(string textSequence, string blockSequence);
	
	int score(const char a, const char b);
	int max(int a, int b, int c);
};

#endif