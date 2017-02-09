#include "BlockAlignment.h"
#define breakLine 50

inline void
BlockAlignment::readFile(string fileName,  vector<vector<char> > &fileData)
{
	fileData.clear();
	// ifstream file(fileName, ios::in | ios::binary | ios::ate);
	ifstream file(fileName.c_str());

	if (file)
	{
		ifstream::pos_type fileSize = file.tellg();
		file.seekg(0, ios::beg);
		std::vector<char> data;

		int i = 1;
		string line;
		while(getline(file, line))
		{
			fileData.resize(i);
			copy(line.begin(), line.end(), back_inserter(fileData[i-1]));
			++i;
		}

		// // Preprossing text chaging whitespaces with '?' for blocks and '*' for texts
		// for (int i = 0; i < fileData.size(); ++i)
		// {
		// 	for (int j = 0; j < fileData[0].size(); ++j)
		// 	{
		// 		if (fileData[i][j] == ' ')
		// 		{
		// 			fileData[i][j] = c;
		// 		}
		// 	}
		// }

		// // Print fileData
		// for (int i = 0; i < fileData.size(); ++i)
		// {
		// 	for (int j = 0; j < fileData[0].size(); ++j)
		// 	{
		// 		cout << fileData[i][j];
		// 	}

		// 	cout << endl;
		// }

		// // Print fileData
		// for (int i = 0; i < fileData.size(); ++i)
		// {
		// 	for (int j = 0; j < fileData[i].size(); ++j)
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
BlockAlignment::setTextSize()
{
	textSizeN = textData.size();
	textSizeM = textData[0].size();
	// cout << "Text size is " << textSizeN << "x" << textSizeM << endl;
}

inline void
BlockAlignment::setBlockSize()
{
	blockSizeN = blockData.size();
	blockSizeM = blockData[0].size();
	// cout << "Block size is " << blockSizeN << "x" << blockSizeM << endl;
}

inline void
BlockAlignment::getSequence(int n, int m)
{
	textSequence.clear();

	for (int i = n; i < blockSizeN + n; ++i)
	{
		for (int j = m; j < blockSizeM + m; ++j)
		{
			textSequence += textData[i][j];
		}
	}

	// This print all sequences with same size as block's
	// cout << textSequence << endl;
}

void
BlockAlignment::align()
{
	// Original block
	readFile(originalBlockFileName, originalBlockData);

	// Block
	readFile(blockFileName, blockData);
	setBlockSize();
	for (int i = 0; i < blockSizeN; ++i)
		for (int j = 0; j < blockSizeM; ++j)
			blockSequence += blockData[i][j];

	int k = 0;
	while (k < textFileNameList.size())
	{
		// Text
		textFileName = textFileNameList[k];
		// cout << "\nStarting alignment for " << textFileName << " and " << blockFileName << endl;
		readFile(textFileName, textData);
		setTextSize();

		if (blockSizeN > textSizeN || blockSizeM > textSizeM)
		{
			cout << "Block \"" << blockFileName << "\" is bigger than text \"" << textFileName << "\". Please try again...\n\n";
			exit(EXIT_FAILURE);
		}

		alignment.clear();
		similarity.clear();

		// Resize alignment matrix
		int size = blockSequence.size() + 1;
		alignment.resize(size);
		for (int i = 0; i < size; ++i)
		{
			alignment[i].resize(size);
		}

		// Resize similarity matrix
		numberOfSequences = (textSizeN - blockSizeN + 1) * (textSizeM - blockSizeM + 1);
		similarity.resize(numberOfSequences);
		for (int i = 0; i < numberOfSequences; ++i)
		{
			similarity[i].resize(3);
		}

		// cout << "****************** alignment size: " << alignment.size() << "x" << alignment[0].size() << endl;
		// cout << "****************** similarity size: " << similarity.size() << "x" << similarity[0].size() << endl;

		// **************************************************************************************************** //

		int n = 0;
		int m = 0;
		sMax = INT_MIN;
		sIterator = 0;

		while (textSizeN - blockSizeN + 1 > n)
		{
			m = 0;
			while (textSizeM - blockSizeM + 1 > m)
			{
				getSequence(n, m);
				similarity[sIterator][1] = n;
				similarity[sIterator][2] = m;
				globalAlignment(textSequence, blockSequence);
				++m;
				++sIterator;
			}

			++n;
		}

		++k;
		print();
		verify();
	}	
}

inline void
BlockAlignment::globalAlignment(string textSequence, string blockSequence)
{
	textSequenceResult.clear();
	blockSequenceResult.clear();

	int i, j, k;
	int n = textSequence.size() + 1;
	int m = blockSequence.size() + 1;

	// Construct alignment matrix
	for (k = 0; k < m; ++k)
	{
		alignment[0][k] = k * score('-', blockSequence[k]);
	}

	for (k = 0; k < n; ++k)
	{
		alignment[k][0] = k * score(textSequence[k], '-');
	}

	for (i = 1; i < n; ++i)
	{
		for (j = 1; j < m; ++j)
		{
			alignment[i][j] = max(
				alignment[i-1][j] + score(textSequence[i-1], '-'),
				alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]),
				alignment[i][j-1] + score('-', blockSequence[j-1])
			);
		}
	}

	// Get similarity
	similarity[sIterator][0] = alignment[n-1][m-1];

	// Construct optimal alignment (result)
	i = textSequence.size();
	j = blockSequence.size();

	while (i != 0 && j != 0)
	{
		if (alignment[i][j] == alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]))
		{
			textSequenceResult += textSequence[i-1];
			blockSequenceResult += blockSequence[j-1];
			i--;
			j--;
		}

		else if (alignment[i][j] == alignment[i][j-1] + score('-', blockSequence[j-1]))
		{
			textSequenceResult += '-';
			blockSequenceResult += blockSequence[j-1];
			j--;
		}

		else if (alignment[i][j] == alignment[i-1][j] + score(textSequence[i-1], '-'))
		{
			textSequenceResult += textSequence[i-1];
			blockSequenceResult += '-';
			i--;
		}
	}

	while (i != 0)
	{
		textSequenceResult += textSequence[i-1];
		blockSequenceResult += '-';
		i--;
	}

	while (j != 0)
	{
		textSequenceResult += '-';
		blockSequenceResult += blockSequence[j-1];
		j--;
	}

	/**
	 * Revert results
	 * Here we use rbegin and rend to the string constructor to revert the string
	 */
	textSequenceResult = string(textSequenceResult.rbegin(), textSequenceResult.rend());
	blockSequenceResult = string(blockSequenceResult.rbegin(), blockSequenceResult.rend());

	// cout << "similarity: " << similarity[sIterator][0] << endl;

	if (similarity[sIterator][0] > sMax)
	{
		sMax = similarity[sIterator][0];
		iMax = sIterator;
		bestResult[0] = textSequenceResult;
		bestResult[1] = blockSequenceResult;
	}

	// for (int i = 0; i < textSequenceResult.size(); i += breakLine)
	// {
	// 	cout << string(bestResult[0].begin() + i, bestResult[0].begin() + i + breakLine) << endl;
	// 	cout << string(bestResult[1].begin() + i, bestResult[1].begin() + i + breakLine) << endl;
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
	cout << "\n> Best result and coordinate for files " << textFileName << " and " << blockFileName << endl;
	cout << "S\tN\tM\n-----------------\n";
	cout << similarity[iMax][0] << "\t" << similarity[iMax][1] << "\t" << similarity[iMax][2] << endl << endl;

	int sequenceSize = bestResult[0].size();
	
	#ifndef breakLine
	#define breakLine
	int breakLine = 150;
	#endif

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

	string original;

	// Concatenate originalBlockData
	for (int i = 0; i < originalBlockData.size(); ++i)
	{
		for (int j = 0; j < originalBlockData[i].size(); ++j)
		{
			original += originalBlockData[i][j];
		}
	}

	for (int i = 0; i < bestResult[1].size(); ++i)
	{
		if (bestResult[1][i] == '?')
		{
			++chars;

			if (bestResult[0][i] == original[i])
			{
				++hits;
			}
		}
	}


	// cout << endl;
	// cout << bestResult[0] << endl;
	// cout << bestResult[1] << endl;
	// cout << original << endl << endl;

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
