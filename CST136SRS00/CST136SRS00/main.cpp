// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LetsMakeADeal.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
using namespace std;


int main(int argc, char *argv[])
{

	//const int total_doors, const int open_doors, const bool switch_strategy
	auto numbOfGames{1000};   // -g
	int totalDoors = 3;       // -d
	int openDoors = 1;        // -o
	bool switchStrategy = false;  // -s t/f

	for (int i = 1; i< argc; i++,i++)
	{
		//cout << argv[i+1] << endl; 
		string option = string(argv[i]);
		if(option == "-g")
		{
			numbOfGames = atoi(argv[i + 1]);
		}
		else if (option == "-d")
		{
			totalDoors = atoi(argv[i + 1]);
		}
		else if (option == "-o")
		{
			openDoors = atoi(argv[i + 1]);
		}
		else if (option == "-s")
		{
			//cout << argv[i + 1] << endl; 
			if (argv[i + 1][0] == 't' || argv[i + 1][0] == 'T')
			{
				switchStrategy = true;
			}
		}
		//cout << "SwitchStrat is: " << switchStrategy << endl; 

	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	 std::uniform_int_distribution<int> distribution(1, totalDoors);
	 std::default_random_engine generator(seed);

	 std::uniform_int_distribution<int> distribution2(1, (totalDoors*(totalDoors - openDoors - 1)));
	 std::default_random_engine generator2(seed);

	vector<LetsMakeADeal> games; 

	for (int i = 0;i<numbOfGames;i++)
	{
		LetsMakeADeal g1(totalDoors,openDoors,switchStrategy); 
		games.push_back(g1);

	}

	//auto totalProbaility = 0.0f;
	int countWins = 0;

	for(int i = 0; i<games.size();i++)
	{
		if(games[i].predictWin(distribution(generator),distribution2(generator2)))
		{
			countWins++;
		}
	}

	auto totalProbaility = float(countWins) / numbOfGames; 
	
	cout << "Total Probability: " << totalProbaility << endl; 

	system("pause");
    return 0;
}

