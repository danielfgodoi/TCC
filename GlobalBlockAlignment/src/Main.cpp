#include "BlockAlignment.h"

int main(int argc, char const *argv[])
{
	clock_t startTime = clock();
	string fileType;
	string originalBlockFileName;
	string blockFileName;
	vector<string> textFileNameList;

	if (argc < 5)
	{
		cout << "Missing arguments! Please try again...\n";
		cout << "To execute run bin/BlockAlignment -t <text files list> -b <block file>\n\n";
		exit(EXIT_FAILURE);
	}

	else
	{
		fileType = argv[1];

		if (fileType == "-t")
		{
			int i = 2;
			while (i < argc - 4)
			{
				textFileNameList.push_back(argv[i]);
				++i;
			}

			fileType = argv[i];

			if (fileType == "-b")
			{
				++i;
				blockFileName = argv[i];

				i += 2;
				originalBlockFileName = argv[i];
			}

			else if (fileType == "-o")
			{
				++i;
				originalBlockFileName = argv[i];

				i += 2;
				blockFileName = argv[i];
			}

			else
			{
				cout << "Missing argument \"-b\"! Please try again...\n\n";
				exit(EXIT_FAILURE);
			}
		}

		else if (fileType == "-b")
		{
			blockFileName = argv[2];
			
			int i = 3;
			fileType = argv[i];
			if (fileType == "-o")
			{
				++i;
				originalBlockFileName = argv[i];

				i += 2;
				while (i < argc)
				{
					textFileNameList.push_back(argv[i]);
					++i;
				}
			}

			else if (fileType == "-t")
			{
				++i;
				while (i < argc && fileType != "-o")
				{
					textFileNameList.push_back(argv[i]);

					++i;
					fileType = argv[i];
				}

				fileType = argv[i];
				if (fileType == "-o")
				{
					++i;
					originalBlockFileName = argv[i];
				}
			}

			else
			{
				cout << "Missing argument \"-t\"! Please try again...\n\n";
				exit(EXIT_FAILURE);
			}
		}

		else if (fileType == "-o")
		{
			originalBlockFileName = argv[2];

			int i = 3;
			fileType = argv[i];
			if (fileType == "-b")
			{
				++i;
				blockFileName = argv[i];

				i += 2;
				while (i < argc)
				{
					textFileNameList.push_back(argv[i]);
					++i;
				}
			}

			else if (fileType == "-t")
			{
				++i;
				while (i < argc && fileType != "-b")
				{
					textFileNameList.push_back(argv[i]);

					++i;
					fileType = argv[i];
				}

				fileType = argv[i];
				if (fileType == "-b")
				{
					++i;
					blockFileName = argv[i];
				}
			}

			else
			{
				cout << "Missing argument \"-t\"! Please try again...\n\n";
				exit(EXIT_FAILURE);
			}
		}
				
		else
		{
			cout << "Invalid argument " << argv[1] << "! Please try again...\n\n";
			exit(EXIT_FAILURE);			
		}

		BlockAlignment blockAlignment(textFileNameList, blockFileName, originalBlockFileName);
		blockAlignment.align();
	}

	// cout << "\n> The program executed successfully\n";

	// Calculate and print total time taken
	double totalTime = (double)(clock() - startTime)/CLOCKS_PER_SEC;
	
	if (totalTime >= 60)
	{
		int minutes = totalTime / 60;
		double seconds = totalTime - (minutes * 60);
		// printf("> Total time taken: %dm%.3fs\n", minutes, seconds);
	}

	// else printf("\n> Total time taken: 0m%.3fs\n\n", totalTime);

	return 0;
}
