// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LetsMakeADeal.h"
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;


int main(int argc, char *argv[])
{
	//variable defaults
	auto numbOfGames{1000};			// -g
	auto totalDoors{ 3 };			// -d
	auto openDoors{ 1 };			// -o
	bool switchStrategy{ false };	// -s t/f

	if (argc < 3)  //if less than 3 arguments, send out the correct syntax
	{
		cout << "Argument syntax: '-g' = number of games\n" <<
			"                 '-d' = total number of doors\n" <<
			"                 '-o' = number of opened doors\n" <<
			"                 '-s' = door switch strategy (either true or false)\n" <<
			" Usage Example: -g 1000 -d 3 -o 1 -s true\n";
	}
	else
	{
		for (int i = 1; i < argc; i++, i++) //cycle through the CLI to take in the flags and variables
		{
			auto option = string(argv[i]);
			if (option == "-g")  //# of games
			{
				numbOfGames = atoi(argv[i + 1]);
			}
			else if (option == "-d")  //# of total doors
			{
				totalDoors = atoi(argv[i + 1]);
			}
			else if (option == "-o")  //# of open doors
			{
				openDoors = atoi(argv[i + 1]);
			}
			else if (option == "-s") //switch strategy
			{

				if (argv[i + 1][0] == 't' || argv[i + 1][0] == 'T') //reads first letter of arg to allow for t vs. true
				{
					switchStrategy = true;
				}
			}
			else //all bad syntax kicks out of program
			{
				cout << "Incorrect syntax.\n";
				system("pause");
				return 0;
			}
		}

		//create a seed for the random generator
		auto seed = chrono::system_clock::now().time_since_epoch().count(); 

		uniform_int_distribution<long long> distribution(1, totalDoors);
		default_random_engine generator(seed);

		uniform_int_distribution<long long> distribution2(1, (totalDoors*(totalDoors - openDoors - 1)));
		default_random_engine generator2(seed);

		//create teh container for a series of games
		vector<LetsMakeADeal> games;

		//load the games into the container
		for (auto i = 0; i < numbOfGames; i++)
		{
			LetsMakeADeal g1(totalDoors, openDoors, switchStrategy);
			games.push_back(g1);
		}

		auto countWins{ 0 };

		//find the number of winnign games
		for (auto i = 0; i < games.size(); i++)
		{
			if (games[i].predictWin(distribution(generator), distribution2(generator2)))
			{
				countWins++;
			}
		}

		auto totalProbability = float(countWins) / numbOfGames;

		cout << "Total Probability: " << totalProbability << endl;
	}
	system("pause");
    return 0;
}

