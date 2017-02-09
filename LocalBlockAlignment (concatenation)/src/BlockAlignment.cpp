#include "BlockAlignment.h"
#define breakLine 50

inline void
BlockAlignment::readFile(string fileName, string &fileData)
{
	fileData.clear();
	ifstream file(fileName.c_str());

	if (file)
	{
		ifstream::pos_type fileSize = file.tellg();
		file.seekg(0, ios::beg);
		std::vector<char> data;
		char c;

		int i = 1;
		string line;

		while(getline(file, line))
		{
			fileData += line + " ";

			// fileData.resize(i);
			// copy(line.begin(), line.end(), back_inserter(fileData[i-1]));
			// ++i;
		}

		int size = fileData.size()-1;
		fileData = fileData.substr(0, size);

		// cout << fileData << endl << endl;

		// cout << "0: ";
		// for (int i = 0; i < fileData.size(); ++i)
		// {
		// 	cout << fileData[i];
		// }
		// cout << endl;

		// // Print fileData
		// for (int i = 0; i < fileData.size(); ++i)
		// {
		// 	cout << i << " ";
		// 	for (int j = 0; j < fileData[0].size(); ++j)
		// 	{
		// 		cout << fileData[i][j];
		// 	}

		// 	cout << endl;
		// }

		// cout << "File " << fileName << " was read successfully\n";
	}

	else
	{
		cout << "Failed to read file \"" << fileName << "\". The file doesn't exists! Please try again...\n\n";
		exit(EXIT_FAILURE);
	}
}

inline void
BlockAlignment::prepareText()
{
	textSize = textData.size();
	textSequence = textData;
}

inline void
BlockAlignment::prepareBlock()
{
	blockSize = blockData.size();
	blockSequence = blockData;
}

void
BlockAlignment::align()
{
	readFile(originalBlockFileName, originalBlockData);

	int i, j, k; // loop iterators
	int t, b; // text and block iterators

	// Read block file
	readFile(blockFileName, blockData);
	
	// Set block lines width
	prepareBlock();

	// // Print for debugging
	// cout << blockSizeN << endl;
	// for (i = 0; i < blockSizeN; ++i)
	// {
	// 	cout << blockSizeM[i] << "\t";
	// 	cout << blockSequence[i] << endl;
	// }

	// Read text files (one by one) and call align function
	k = 0;
	while (k < textFileNameList.size())
	{
		// Read text file
		textFileName = textFileNameList[k];
		readFile(textFileName, textData);

		// Set test lines width
		prepareText();

		textSequenceResult.clear();
		blockSequenceResult.clear();

		alignment.clear();
		
		n = textSize + 1;
		m = blockSize + 1;

		// Resize alignment matrix (nxm)
		// n: block size, m: text size
		alignment.resize(n);
		for (j = 0; j < n; ++j)
		{
			alignment[j].resize(m);
		}

		// Call semiglobal aligment here
		localAlignment(textSequence, blockSequence);

		++k;

		print();
		verify();
	}
}

inline void
BlockAlignment::localAlignment(string textSequence, string blockSequence)
{
	int maxLocal = INT_MIN, 
		maxI = 0, 
		maxJ = 0;

	for (int k = 0; k < m; ++k)
	{
		alignment[0][k] = 0;
	}

	for (int k = 0; k < n; ++k)
	{
		alignment[k][0] = 0;
	}

	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < m; ++j)
		{
			alignment[i][j] = max(
				alignment[i-1][j] + score(textSequence[i-1], '-'),
				alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]),
				alignment[i][j-1] + score('-', blockSequence[j-1])
			);

			if(alignment[i][j] < 0)
			{
				alignment[i][j] = 0;
			}

			// This condition is used to get the maximum value of the matrix
			if(alignment[i][j] > maxLocal)
			{
				maxLocal = alignment[i][j];
				maxI = i;
				maxJ = j;
			}
		}
	}

	// Get similarity
	similarity = maxLocal;
	// cout << "similarity: " << similarity << endl;

	// Construct optimal alignment (result)
	int i = maxI;
	int j = maxJ;

	while(alignment[i][j] != 0)
	{
		if(alignment[i][j] == alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]))
		{
			textSequenceResult += textSequence[i-1];
			blockSequenceResult += blockSequence[j-1];
			i--;
			j--;
		}

		else if(alignment[i][j] == alignment[i][j-1] + score('-', blockSequence[j-1]))
		{
			textSequenceResult += '-';
			blockSequenceResult += blockSequence[j-1];
			j--;
		}

		else if(alignment[i][j] == alignment[i-1][j] + score(textSequence[i-1], '-'))
		{
			textSequenceResult += textSequence[i-1];
			blockSequenceResult += '-';
			i--;
		}
	}

	// cout << "i: " << i << ", j: " << j << endl << endl;
	flag = j;
	
	textSequenceResult = string(textSequenceResult.rbegin(), textSequenceResult.rend());
	blockSequenceResult = string(blockSequenceResult.rbegin(), blockSequenceResult.rend());

	// start = j;
	// end = maxJ;

	// cout << similarity << endl;
	// cout << textSequenceResult << endl;
	// cout << blockSequenceResult << endl << endl;

	// for (int i = 0; i < textSequenceResult.size(); i += breakLine)
	// {
	// 	cout << string(textSequenceResult.begin() + i, textSequenceResult.begin() + i + breakLine) << endl;
	// 	cout << string(blockSequenceResult.begin() + i, blockSequenceResult.begin() + i + breakLine) << endl;
	// }
	
	// cout << endl;
}

inline int
BlockAlignment::score(const char a, const char b)
{
	if 		(a == b)				return  1;
	else if (a != '-' && b != '-') 	return -1;
	else 							return -2;
}

inline int
BlockAlignment::max(int a, int b, int c)
{
	int max = a;
	(max < b) && (max = b);
	(max < c) && (max = c);
	return max;
}

inline void
BlockAlignment::print()
{
	bestResult[0] = textSequenceResult;
	bestResult[1] = blockSequenceResult;

	// cout << "\nFinished alignment with " << numberOfSequences << " sequences" << endl;
	// cout << "S\tN\tM\n-----------------\n";
	// for (int i = 0; i < numberOfSequences; ++i)
	// cout << similarity[i][0] << "\t" << similarity[i][1] << "\t" << similarity[i][2] << endl;
	// cout << endl;

	cout << "\n> Best result and text-block best line " << textFileName << " and " << blockFileName << endl;
	cout << "Similarity\n-----------------\n";
	// cout << similarity[iMax][0] << "\t" << similarity[iMax][1] << "\t" << similarity[iMax][2] << endl << endl;
	cout << similarity << endl << endl;

	// Hits for ? chars
	int hits = 0;
	int j = 0;
	
	// Earn
	// char chars[] = "rost loss of setderricuriondi so of t notesilpoo wneton raostri ro si-";
	
	// Trade
	// char chars[] = "aprn erly ly un int t haablxibanctt jes ra ily ";

	int sequenceSize = bestResult[0].size();

	// for (int i = 0; i < sequenceSize; ++i)
	// {
	// 	if (bestResult[1][i] == '?')
	// 	{
	// 		if (bestResult[0][i] == chars[j])
	// 		{
	// 			++hits;
	// 		}

	// 		++j;
	// 	}
	// }

	// double percent = ((double)hits / 47) * 100;

	// cout << "Hits for ? chars: " << hits << " of 47" << endl;
	// cout << "Hits percentage: ";
	// cout << setprecision(3) << percent;
	// cout << "%" << endl << endl;

	// cout << "> Text (best window)\n";
	// for (int i = similarity[iMax][1]; i < similarity[iMax][1] + blockSizeN; ++i)
	// {
	// 	for (int j = similarity[iMax][2]; j < similarity[iMax][2] + blockSizeM; ++j)
	// 	{
	// 		cout << textData[i][j];
	// 	}
	// 	cout << endl;
	// }
	
	// cout << "\n> Block (best window)\n";
	// for (int i = 0; i < blockSizeN; ++i)
	// {
	// 	for (int j = 0; j < blockSizeM; ++j)
	// 	{	
	// 		cout << blockData[i][j];
	// 	}
	// 	cout << endl;
	// }

	// Print best alignment
	// cout << "\n> Text (best alignment)" << endl << bestResult[0] << endl;
	// cout << "\n> Block (best alignment)" << endl << bestResult[1] << endl;


	// cout << "> Best alignment for files " << textFileName << " and " << blockFileName << endl;
	
	#ifndef breakLine
	#define breakLine
	int breakLine = 150;
	#endif
	
	// for (int i = 0; i < sequenceSize; ++i)
	// {
		// Text sequence best result
		// cout << bestResult[0][i];
		// Block sequence best result
		// cout << bestResult[1][i];
	// }

	for (int i = 0; i < sequenceSize; i += breakLine)
	{
		// int longerFileName = (int)textFileName.length();

		// if ((int)blockFileName.length() > longerFileName)
		// {
		// 	longerFileName = (int)blockFileName.length();
		// 	cout << textFileName << " ";
		// 	for (int i = 0; i < (int)blockFileName.length() - (int)textFileName.length(); ++i)
		// 	{
		// 		cout << " ";
		// 	}

		// 	cout << bestResult[0].substr(i, breakLine) << endl;
		// }

		// else
		// 	cout << textFileName << " " << bestResult[0].substr(i, breakLine) << endl;


		// for (int j = 0; j < longerFileName + 1; ++j)
		// {
		// 	cout << " ";
		// }

		// for (int j = 0; j < (int)(bestResult[0].substr(i, breakLine)).length(); ++j)
		// {
		// 	if(bestResult[0][j+i] == bestResult[1][j+i])
		// 		cout << "|";

		// 	else if(bestResult[0][j+i] == '-' || bestResult[1][j+i] == '-')
		// 		cout << " ";

		// 	else
		// 		cout << "!";
		// }

		// cout << endl;

		// cout << blockFileName << " " << bestResult[1].substr(i, breakLine) << endl;
	}

	// cout << endl;
}

inline void
BlockAlignment::verify()
{
	int chars = 0;
	int hits = 0;

	for (int i = 0; i < bestResult[1].size(); ++i)
	{
		if (bestResult[1][i] == '?')
		{
			// ++chars;

			if (bestResult[0][i] == originalBlockData[i+flag])
			{
				++hits;
			}
		}
	}

	// Go through all block and count the number of '?' chars
	for (int i = 0; i < blockSize; ++i)
		if (blockSequence[i] == '?')
			++chars;

	// cout << endl;
	// cout << "flag: " << flag << endl;
	// cout << bestResult[0] << endl;
	// cout << bestResult[1] << endl;
	// for (int i = flag; i < bestResult[1].size() + flag; ++i)
	// {
	// 	cout << originalBlockData[i];
	// }
	// cout << endl << endl;

	double percent;
	if ((double)hits*100/chars > 0)
		percent = (double)hits*100/chars;
	else
		percent = 0;

	cout << "Number of chars ?: " << chars << endl;
	cout << "Numer of hits: " << hits << endl;
	cout << "Hits percentage: " << percent << "%" << endl << endl;
	cout << "\n\n\n";
}
