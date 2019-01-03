/*JoombrBoo
authours:
alexey melentyev
mihail ignatenko
oleg sazonov
date: 10.12.18*/

#include"head.h"


void main()
{	
	int Player_1_Data[players_data_array_width][players_data_array_width] = { 0 }; // {0} to make it empty
	int Player_2_Data[players_data_array_width][players_data_array_width] = { 0 }; // {0} to make it empty
	/****************************************************************************************************************
	all data about users' elements is stored in Player_1_Data and Player_2_Data arrays according to next rules:
	each column is different info about the same element:
	0 line: type of element
		1 - gun
		2 - wall
		3 - ...
	1 line: amount of shots
	2 line: shoots direction
		 1 - from left to right
		-1 - from right to left
	3 line: amount of hp
	4 line: horisontal position
	5 line: vertical position
	****************************************************************************************************************/	
	int Player_1_Shots[player_shots_array_width][player_shots_array_long] = { 0 }; // {0} to make it empty
	int Player_2_Shots[player_shots_array_width][player_shots_array_long] = { 0 }; // {0} to make it empty
	/****************************************************************************************************************
	all data about active shots stored in Player_1_Shots and Player_2_Shots arrays with the samw logic as for users' elements
	0 line: type of shot
		1 - usual
		2 - maybe other types in future
	1 line: direction
		 1 - from left to right
		-1 - from right to left
	2 line: horisontal position
	3 line: vertical position
	****************************************************************************************************************/
	
	
	char Map[I][H][W];
	bool doContinue = true;
	getTheMapFromTheFile(Map, firstMap);
	addEconomics(Map);
	addGunsList(Map);
	fillIndexesInTheMAp(Map);
	drowTheMap(Map);
	while (doContinue)
	{

	}
	return;
}
