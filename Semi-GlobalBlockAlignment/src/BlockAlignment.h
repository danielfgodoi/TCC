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
	BlockAlignment(vector<string> textFileNameList, string blockFileName, string originalBlockFileName)
	{
		this->textFileNameList = textFileNameList;
		this->blockFileName = blockFileName;
		this->originalBlockFileName = originalBlockFileName;
		// bestResult.resize(2);
	};

	// Default destructor
	~BlockAlignment(){};
	
	// Public methods
	void align();

private:
	// Variables
	// Block and text sizes
	int blockSizeN; // number of rows
	vector<int> blockSizeM; // number of columns
	int textSizeN; // number of rows
	vector<int> textSizeM; // number of columns
	
	int numberOfSequences;
	int sIterator;
	int sMax;
	int iMax;
	vector<string> textFileNameList;
	string textFileName;
	string blockFileName;
	string originalBlockFileName;
	vector<string> textSequence;
	vector<string> blockSequence;
	string textSequenceResult;
	string blockSequenceResult;
	vector<vector<string> > bestResult;
	vector<vector<char> > textData;
	vector<vector<char> > blockData;
	vector<vector<char> > originalBlockData;
	
	vector<int> similarity; // stores the similarities
	vector< vector<int> > bestLine; // stores the best text and block lines

	vector< vector<int> > alignment; // stores the alignments matrix

	int n; // Alignment matrix size (text width)
	int m; // Alignment matrix size (block width)

	// Methods
	void print();
	
	void readFile(string fileName,  vector<vector<char> > &fileData);
	void prepareBlock();
	void prepareText();

	void getSequence(int n, int m);
	
	// void globalAlignment(string textSequence, string blockSequence);
	void semiglobalAlignment(string textSequence, string blockSequence);
	
	int score(const char a, const char b);
	int max(int a, int b, int c);
};

#endif
