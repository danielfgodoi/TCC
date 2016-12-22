#include "BlockAlignment.h"
#define breakLine 50

inline void
BlockAlignment::readFile(string fileName,  vector<vector<char> > &fileData)
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
			fileData.resize(i);
			copy(line.begin(), line.end(), back_inserter(fileData[i-1]));
			++i;
		}

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
BlockAlignment::prepareText()
{
	textSizeN = textData.size();
	textSequence.resize(textSizeN);

	textSizeM.resize(textSizeN);

	for (int i = 0; i < textSizeN; ++i)
	{
		textSizeM[i] = textData[i].size();
		textSequence[i].resize(textSizeM[i]);
	}
}

inline void
BlockAlignment::prepareBlock()
{
	blockSizeN = blockData.size();
	blockSequence.resize(blockSizeN);

	blockSizeM.resize(blockSizeN);

	bestResult.resize(blockSizeN);
	bestLine.resize(blockSizeN);

	for (int i = 0; i < blockSizeN; ++i)
	{
		blockSizeM[i] = blockData[i].size();
		blockSequence[i].resize(blockSizeM[i]);
		bestResult[i].resize(2);
		bestLine[i].resize(2);
	}
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

	// Prepare block sequence
	for (i = 0; i < blockSizeN; ++i)
		for (j = 0; j < blockSizeM[i]; ++j)
			blockSequence[i][j] = blockData[i][j];

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

		// Prepare text sequence
		for (i = 0; i < textSizeN; ++i)
			for (j = 0; j < textSizeM[i]; ++j)
				textSequence[i][j] = textData[i][j];

		// Align for each combination of lines (text and block)
		// So we'll have n_lines_text * n_lines_block
		similarity.resize(blockSizeN);

		for (b = 0; b < blockSizeN; ++b)
		{
			sIterator = b;
			similarity[sIterator] = INT_MIN;

			for (t = 0; t < textSizeN; ++t)
			{
				textSequenceResult.clear();
				blockSequenceResult.clear();
				alignment.clear();
				
				n = textSizeM[t] + 1;
				m = blockSizeM[b] + 1;

				// Resize alignment matrix (nxm)
				// n: block size, m: text size
				alignment.resize(n);
				for (j = 0; j < n; ++j)
				{
					alignment[j].resize(m);
				}

				// Call semiglobal aligment here
				int s = similarity[sIterator];
				semiglobalAlignment(textSequence[t], blockSequence[b]);
				if (similarity[sIterator] > s)
				{
					bestLine[sIterator][0] = t + 1;
					bestLine[sIterator][1] = b + 1;
				}
			}
		}

		// cout << "similarity: " << similarity << endl;
		// cout << bestResult[0] << endl;
		// cout << bestResult[1] << "\n\n";

		++k;
		print();
	}
}

inline void
BlockAlignment::semiglobalAlignment(string textSequence, string blockSequence)
{
	int maxLocal = INT_MIN,
		maxI = 0,
		maxJ = m-1,
		local_similarity;

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
			// cout << textSequence[i-1] << " " << blockSequence[j-1] << " \n";
			alignment[i][j] = max(
				alignment[i-1][j] + score(textSequence[i-1], '-'),
				alignment[i-1][j-1] + score(textSequence[i-1], blockSequence[j-1]),
				alignment[i][j-1] + score('-', blockSequence[j-1])
			);
		}
	}

	// Get maximum value of last raw or column (similarity)
	for (int i = 1; i < n; ++i)
	{
		if(alignment[i][m-1] > maxLocal)
		{
			maxLocal = alignment[i][m-1];
			maxI = i;
		}
	}

	for (int j = 0; j < m-1; ++j)
	{
		if(alignment[n-1][j] > maxLocal)
		{
			maxLocal = alignment[n-1][j];
			maxI = n-1;
			maxJ = j;
		}
	}

	// Get similarity
	local_similarity = maxLocal;
	// cout << "similarity: " << local_similarity << endl;

	// Construct optimal alignment (result)
	int i = maxI;
	int j = maxJ;

	for (int k = n-1; k > maxI; --k)
	{
		textSequenceResult += textSequence[k-1];
		blockSequenceResult += '-';
	}

	for (int k = m-1; k > maxJ; --k)
	{
		textSequenceResult += '-';
		blockSequenceResult += blockSequence[k-1];
	}

	while(i != 0 && j != 0)
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

	while(i != 0)
	{
		textSequenceResult += textSequence[i-1];
		blockSequenceResult += '-';
		i--;
	}

	while(j != 0)
	{
		textSequenceResult += '-';
		blockSequenceResult += blockSequence[j-1];
		j--;
	}

	// Revert results
	// Here we use rbegin and rend to the string constructor to revert the string
	textSequenceResult = string(textSequenceResult.rbegin(), textSequenceResult.rend());
	blockSequenceResult = string(blockSequenceResult.rbegin(), blockSequenceResult.rend());

	// cout << textSequenceResult << endl;
	// cout << blockSequenceResult << "\n\n\n\n";

	if (local_similarity > similarity[sIterator])
	{
		similarity[sIterator] = local_similarity;
		bestResult[sIterator][0] = textSequenceResult;
		bestResult[sIterator][1] = blockSequenceResult;
	}

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
	for (int r = 0; r <= sIterator; ++r)
	{
		// cout << "\nFinished alignment with " << numberOfSequences << " sequences" << endl;
		// cout << "S\tN\tM\n-----------------\n";
		// for (int i = 0; i < numberOfSequences; ++i)
		// cout << similarity[i][0] << "\t" << similarity[i][1] << "\t" << similarity[i][2] << endl;
		// cout << endl;

		cout << "\n> Best result and text-block best line " << textFileName << " and " << blockFileName << endl;
		cout << "S\tTL\tBL\n-----------------\n";
		// cout << similarity[iMax][0] << "\t" << similarity[iMax][1] << "\t" << similarity[iMax][2] << endl << endl;
		cout << similarity[r] << "\t" << bestLine[r][0] << "\t" << bestLine[r][1] << endl << endl;

		int sequenceSize = bestResult[r][0].size();

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

			// 	cout << bestResult[r][0].substr(i, breakLine) << endl;
			// }

			// else
			// 	cout << textFileName << " " << bestResult[r][0].substr(i, breakLine) << endl;


			// for (int j = 0; j < longerFileName + 1; ++j)
			// {
			// 	cout << " ";
			// }

			// for (int j = 0; j < (int)(bestResult[r][0].substr(i, breakLine)).length(); ++j)
			// {
			// 	if(bestResult[r][0][j+i] == bestResult[r][1][j+i])
			// 		cout << "|";

			// 	else if(bestResult[r][0][j+i] == '-' || bestResult[r][1][j+i] == '-')
			// 		cout << " ";

			// 	else
			// 		cout << "!";
			// }

			// cout << endl;

			// cout << blockFileName << " " << bestResult[r][1].substr(i, breakLine) << endl;
		}

	// Verify is going to be here because we go through the bestResults array
	int chars = 0;
	int hits = 0;

	string original;

	// Concatenate originalBlockData

	int i = bestLine[r-1][1];
	for (int j = 0; j < originalBlockData[i].size(); ++j)
	{
		original += originalBlockData[i][j];
	}

	// Calculate shift
	int shift = 0;
	while (bestResult[r][1][shift] == '-')
	{
		++shift;
	}

	for (int i = 0, j = shift; i < original.size(); ++i, ++j)
	{
		// cout << bestResult[r][0][j];
		// cout << original[i];

		if (bestResult[r][1][j] == '?')
		{
			++chars;

			if (bestResult[r][0][j] == original[i])
			{
				++hits;
			}
		}
	}

	// cout << bestResult[r][0] << endl;
	// cout << bestResult[r][1] << endl;
	// for (int i = 0; i < shift; ++i)
	// {
	// 	cout << " ";
	// }
	// cout << original << endl << endl;

	cout << "Number of chars ?: " << chars << endl;
	cout << "Numer of hits: " << hits << endl;
	cout << "Hits percentage: " << (double)hits*100/chars << "%" << endl << endl;

	cout << "\n\n\n";
	}
}
