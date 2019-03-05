#pragma once
#include "head.h"

int Player_1_Shots[shots_M][shots_N] = { 0 }; // {0} to make it empty
int Player_2_Shots[shots_M][shots_N] = { 0 }; // {0} to make it empty	


void MovementMechanichs(int Player_1_Data[data_M][data_N], int Player_2_Data[data_M][data_N], int Player_1_Shots[shots_M][shots_N], int Player_2_Shots[shots_M][shots_N])
{

	/**********************************
	Movement mechanics contain several steps:
	1. Shots movement
	2. Elements (from data arrays) actions
	3. ...
	**********************************/
	enum element_types { big_gun = 49, gun = 50,  big_wall = 51, wall = 52 };

	//Shots movement Player 1
	for (int i = 0; Player_1_Shots[0][i] != 0;)
	{
		i += ShotMovement(Player_1_Data, Player_2_Data, Player_1_Shots, i, 1);
	}

	//Shots movement Player 2
	for (int i = 0; Player_2_Shots[0][i] != 0;)
	{
		i += ShotMovement(Player_1_Data, Player_2_Data, Player_2_Shots, i, 2);
	}

	//Elements actions Player 1;
	for (int i = 0; Player_1_Data[0][i] != 0; i++)
	{
		switch (Player_1_Data[0][i]) //switch is used because in future there can be more then 2 type of elements
		{
		case gun:
			if (Player_1_Data[1][i] > 0)
			{
				MakeAShot(Player_1_Data, Player_1_Shots, i);
				Player_1_Data[1][i]--;
				if (Player_1_Data[1][i] == 0)
				{
					DeleteInfoFromField(Player_1_Data, i);
					DeleteInfoFromData(Player_1_Data, i, 1);
					i--;
				}
			}
			break;
		case big_gun:
			if (Player_1_Data[1][i] > 0)
			{
				MakeAShot(Player_1_Data, Player_1_Shots, i);
				Player_1_Data[1][i]--;
				if (Player_1_Data[1][i] == 0)
				{
					DeleteInfoFromField(Player_1_Data, i);
					DeleteInfoFromData(Player_1_Data, i, 1);
					i--;
				}
			}
			break;
		case wall:
			break;
		case big_wall:
			break;
		default:
			/*printf("MovementMechanichs error 1")*/;
			break;
		}
	}

	//Elements actions Player 2;
	for (int i = 0; Player_2_Data[0][i] != 0; i++)
	{
		switch (Player_2_Data[0][i]) //switch is used because in future there can be more then 2 type of elements
		{
		case gun:
			if (Player_2_Data[1][i] > 0)
			{
				MakeAShot(Player_2_Data, Player_2_Shots, i);
				Player_2_Data[1][i]--;
				if (Player_2_Data[1][i] == 0)
				{
					DeleteInfoFromField(Player_2_Data, i);
					DeleteInfoFromData(Player_2_Data, i, 2);
					i--;
				}
			}
			break;
		case big_gun:
			if (Player_2_Data[1][i] > 0)
			{
				MakeAShot(Player_2_Data, Player_2_Shots, i);
				Player_2_Data[1][i]--;
				if (Player_2_Data[1][i] == 0)
				{
					DeleteInfoFromField(Player_2_Data, i);
					DeleteInfoFromData(Player_2_Data, i, 2);
					i--;
				}
			}
			break;
		case wall:
			break;
		case big_wall:
			break;
		default:
			/*printf("MovementMechanichs error 1")*/;
			break;
		}
	}

}

void MakeAShot(int Player_Data[data_M][data_N], int Player_Shots[shots_M][shots_N], int number_of_element)
{
	enum shot_direction { left = -1, right = 1 };
	int m, n; //coordinates	
	int m_to_damage, n_to_damage;
	m = Player_Data[4][number_of_element];
	n = Player_Data[5][number_of_element];
	switch (Player_Data[2][number_of_element])
	{
	case right:
		if (MainField[m][n + 2] = ' ' || MainField[m][n + 2] == '.')
		{
			MainField[m][n + 2] = '-';
			for (int i = 0;; i++)
			{
				if (Player_Shots[0][i] == 0)
				{
					Player_Shots[0][i] = 1;
					Player_Shots[1][i] = 1;
					Player_Shots[2][i] = m;
					Player_Shots[3][i] = n + 2;
					break;
				}
			}
		}
		else if ((MainField[m][n + 2] = 'x') || (MainField[m][n + 2] = 'H'))
		{
			/*printf("Temp MakeAShot error 1")*/;
			//MakeADamage(Player_Shots, number_of_shot, 1)
		}
		else/* printf("MakeAShot error 1")*/;
		break;
	case left:
		if (MainField[m][n - 2] = ' ' || MainField[m][n - 2] == '.')
		{
			MainField[m][n - 2] = '-';
			for (int i = 0;; i++)
			{
				if (Player_Shots[0][i] == 0)
				{
					Player_Shots[0][i] = 1;
					Player_Shots[1][i] = -1;
					Player_Shots[2][i] = m;
					Player_Shots[3][i] = n - 2;
					break;
				}
			}
		}
		else if ((MainField[m][n - 2] = 'x') || (MainField[m][n - 2] = 'H'))
		{
			/*printf("Temp MakeAShot error 2");*/
			//MakeADamage(Player_Shots, number_of_shot, 1)
		}
		else /*printf("MakeAShot error 2")*/;
		break;
	default:
		/*printf("MakeAShot error 3")*/;
		break;
	}
	return;
}

int ShotMovement(int Player_1_Data[data_M][data_N], int Player_2_Data[data_M][data_N], int Player_Shots[shots_M][shots_N], int number_of_shot, int player_number)
{
	enum shot_direction { left = -1, right = 1 };
	int m, n; //coordinates
	int m_to_damage, n_to_damage;
	int shot_direction;
	int number_of_element_to_damage;

	shot_direction = Player_Shots[1][number_of_shot];
	m = Player_Shots[2][number_of_shot];
	n = Player_Shots[3][number_of_shot];
	switch (shot_direction) //switch for feature cases (there can be up and down)
	{
	case left:
		if (n == 0) //for cases when it is an edge of game zone
		{
		DeleteInfoFromShots(Player_Shots, number_of_shot, player_number);
		MainField[m][n] = ' ';
		return 0;
		}
		else if (MainField[m][n - 1] == ' ' || MainField[m][n - 1] == '.')
		{
			MainField[m][n - 1] = '-';
			Player_Shots[3][number_of_shot]--;
			//if (MainField[m][n] == '-') MainField[m][n] = ' ';
			if (MainField[m][n] == '=') MainField[m][n] = '-';
			else MainField[m][n] = Batle_field[1][m][n];
			return 1;
		}
		else if ((MainField[m][n - 1] == '-') || (MainField[m][n - 1] == '=')) // need to end this case after having copy of main fild
		{
			MainField[m][n - 1] = '=';
			Player_Shots[3][number_of_shot]--;
			//if (MainField[m][n] == '-') MainField[m][n] = ' ';			
			if (MainField[m][n] == '=') MainField[m][n] = '-';
			else MainField[m][n] = Batle_field[1][m][n];
			return 1;
		}
		else if ((MainField[m][n - 1] == 36) ||(MainField[m][n - 1] == 176) || (MainField[m][n - 1] == 177) || (MainField[m][n - 1] == 178) || (MainField[m][n - 1] == 186) 
			|| (MainField[m][n - 1] == 187) || (MainField[m][n - 1] == 188)	|| (MainField[m][n - 1] == 196)	|| (MainField[m][n - 1] == 200) || (MainField[m][n - 1] == 201) 
			|| (MainField[m][n - 1] == 199) || (MainField[m][n - 1] == 204) || (MainField[m][n - 1] == 205))
		{
			m_to_damage = Batle_field[2][m][n - 1];
			n_to_damage = Batle_field[3][m][n - 1];		
			if (player_number == 1) number_of_element_to_damage = FindElementToDamage(Player_2_Data, m_to_damage, n_to_damage);
			else if (player_number == 2) number_of_element_to_damage = FindElementToDamage(Player_1_Data, m_to_damage, n_to_damage);
			else /*printf("ShotMovement error 4.1")*/;
			if (number_of_element_to_damage == -1)
			{
				//MainField[m][n - 1] = '-'; or we can change visualisation for cases when shots is under user's own element
				Player_Shots[3][number_of_shot]--;
				//if (MainField[m][n] == '-') MainField[m][n] = ' '; 
				if (MainField[m][n] == '=') MainField[m][n] = '-';
				else MainField[m][n] = Batle_field[1][m][n];
				return 1;
			}
			else if (number_of_element_to_damage >= 0)
			{
				MakeADamage(Player_1_Data, Player_2_Data, Player_Shots, number_of_shot, player_number, number_of_element_to_damage);
				DeleteInfoFromShots(Player_Shots, number_of_shot, player_number);
				MainField[m][n] = ' '; //need to check copy of MainField to know element to return
				return 0; //if there was a damage Player_Shots array is moved to left for 1 position, because of this return 0
			}
			else /*printf("ShotMovement error 2.1")*/;
		}	
		else /*printf("ShotMovement error 1")*/;
		break;
	case right:
		if (n == 58) //for cases when it is an edge of game zone
		{
		DeleteInfoFromShots(Player_Shots, number_of_shot, player_number);
		MainField[m][n] = ' ';
		return 0;
		}
		else if (MainField[m][n + 1] == ' ' || MainField[m][n + 1] == '.')
		{
			MainField[m][n + 1] = '-';
			Player_Shots[3][number_of_shot]++;
			//if (MainField[m][n] == '-') MainField[m][n] = ' ';
			if (MainField[m][n] == '=') MainField[m][n] = '-';
			else MainField[m][n] = Batle_field[1][m][n];
			return 1;
		}		
		else if ((MainField[m][n + 1] == '-') || (MainField[m][n + 1] == '=')) //need to end this case after having copy of main fild
		{
			MainField[m][n + 1] = '=';
			Player_Shots[3][number_of_shot]++;
			//if (MainField[m][n] == '-') MainField[m][n] = ' ';
			if (MainField[m][n] == '=') MainField[m][n] = '-';
			else MainField[m][n] = Batle_field[1][m][n];
			return 1;
		}
		else if ((MainField[m][n + 1] == 36) ||(MainField[m][n + 1] == 176) || (MainField[m][n + 1] == 177) || (MainField[m][n + 1] == 178) || (MainField[m][n + 1] == 186) 
			|| (MainField[m][n + 1] == 187) || (MainField[m][n + 1] == 188) || (MainField[m][n + 1] == 196)	|| (MainField[m][n + 1] == 200) || (MainField[m][n + 1] == 201)
			|| (MainField[m][n + 1] == 199) || (MainField[m][n + 1] == 204) || (MainField[m][n + 1] == 205))
		{
			m_to_damage = Batle_field[2][m][n + 1];
			n_to_damage = Batle_field[3][m][n + 1];
			if (player_number == 1) number_of_element_to_damage = FindElementToDamage(Player_2_Data, m_to_damage, n_to_damage);
			else if (player_number == 2) number_of_element_to_damage = FindElementToDamage(Player_1_Data, m_to_damage, n_to_damage);
			else /*printf("ShotMovement error 4.1")*/;
			if (number_of_element_to_damage == -1)
			{
				//MainField[m][n + 1] = '-';
				Player_Shots[3][number_of_shot]++;
				//if (MainField[m][n] == '-') MainField[m][n] = ' '; 
				if (MainField[m][n] == '=') MainField[m][n] = '-';
				else MainField[m][n] = Batle_field[1][m][n];
				return 1;
			}
			else if (number_of_element_to_damage >= 0)
			{
				MakeADamage(Player_1_Data, Player_2_Data, Player_Shots, number_of_shot, player_number, number_of_element_to_damage);
				DeleteInfoFromShots(Player_Shots, number_of_shot, player_number);
				//if (MainField[m][n] == '-') MainField[m][n] = ' '; 
				if (MainField[m][n] == '=') MainField[m][n] = '-';	
				else MainField[m][n] = Batle_field[1][m][n];
				return 0;
			}
			else /*printf("ShotMovement error 2.2")*/;
		}
		
		else /*printf("ShotMovement error 2")*/;
		break;
	default:
		/*printf("ShotMovement error 3")*/;
		break;
	}
	/*printf("ShotMovement error 4")*/;
	return 999;
}

void DeleteInfoFromShots(int Array[shots_M][shots_N], int shot_number, int player_number)
{
	//this funtcion delete info about disappeared shot from array and move all info in array to left side (not to have empty spaces in array)
	int i;
	for (i = shot_number; Array[0][i] != 0; i++)
	{
		Array[0][i] = Array[0][i + 1];
		Array[1][i] = Array[1][i + 1];
		Array[2][i] = Array[2][i + 1];
		Array[3][i] = Array[3][i + 1];
	}
	i--;
	Array[0][i] = 0;
	Array[1][i] = 0;
	Array[2][i] = 0;
	Array[3][i] = 0;
	/*if (player_number == 1) amount_of_shots_player_1--;		for debugging
	else if (player_number == 2) amount_of_shots_player_2--;
	else printf("DeleteInfoFromShots error 1");*/

	return;
}

void MakeADamage(int Player_1_Data[data_M][data_N], int Player_2_Data[data_M][data_N], int Player_Shot[shots_M][shots_N], int number_of_shot, int player_number, int number_of_element_to_damage)
{
	int m, n; //coordinates
	//int m_centner_of_element, n_centner_of_element;
	enum shot_direction { left = -1, right = 1 };
	int shot_direction;
	shot_direction = Player_Shot[1][number_of_shot];
	m = Player_Shot[2][number_of_shot];
	n = Player_Shot[3][number_of_shot];

	if (player_number == 1)
	{
		Player_2_Data[3][number_of_element_to_damage]--;
		if (CheckElementDestroy(Player_2_Data, number_of_element_to_damage))
		{
			/*m_centner_of_element = (Player_2_Data[4][number_of_element_to_damage]);
			n_centner_of_element = (Player_2_Data[5][number_of_element_to_damage]);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					MainField[m_centner_of_element - 1 + i][n_centner_of_element - 1 + j] = ' ';
				}
			}*/
			DeleteInfoFromField(Player_2_Data, number_of_element_to_damage);
			DeleteInfoFromData(Player_2_Data, number_of_element_to_damage, 2);			
		}
	}
	else if (player_number == 2)
	{
		Player_1_Data[3][number_of_element_to_damage]--;
		if (CheckElementDestroy(Player_1_Data, number_of_element_to_damage))
		{			
			/*m_centner_of_element = (Player_1_Data[4][number_of_element_to_damage]);
			n_centner_of_element = (Player_1_Data[5][number_of_element_to_damage]);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					MainField[m_centner_of_element - 1 + i][n_centner_of_element - 1 + j] = ' ';
				}
			}*/
			DeleteInfoFromField(Player_1_Data, number_of_element_to_damage);
			DeleteInfoFromData(Player_1_Data, number_of_element_to_damage, 1);			
		}
	}
	else /*printf("MakeADamage error 1")*/;
	return;
}

int FindElementToDamage(int Player_Data[data_M][data_N], int m, int n)
{
	for (int i = 0; Player_Data[0][i] != 0; i++)
	{
		if (Player_Data[4][i] == m)
		{
			if (Player_Data[5][i] == n)
			{
				return i;
			}
		}
	}
	return -1;
}

int CheckElementDestroy(int Player_Data[data_M][data_N], int number_of_element)
{
	if (Player_Data[3][number_of_element] > 0) return 0;
	else if (Player_Data[3][number_of_element] == 0) return 1;
	else /*printf("CheckElementDestroy error 1")*/;
	return-1;
}

void DeleteInfoFromField(int Player_Data[data_M][data_N], int number_of_element)
{
	int m_centner_of_element, n_centner_of_element;

	m_centner_of_element = (Player_Data[4][number_of_element]);
	n_centner_of_element = (Player_Data[5][number_of_element]);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Batle_field[0][m_centner_of_element - 1 + i][n_centner_of_element - 1 + j] = ' ';
			Batle_field[1][m_centner_of_element - 1 + i][n_centner_of_element - 1 + j] = ' ';
			Batle_field[2][m_centner_of_element - 1 + i][n_centner_of_element - 1 + j] = 0;
			Batle_field[3][m_centner_of_element - 1 + i][n_centner_of_element - 1 + j] = 0;
		}
	}
}

void DeleteInfoFromData(int Player_Data[data_M][data_N], int number_of_element, int player_number)
{
	//this funtcion delete info about disappeared shot from array and move all info in array to left side (not to have empty spaces in array)
	int i;
	for (i = number_of_element; Player_Data[0][i] != 0; i++)
	{
		Player_Data[0][i] = Player_Data[0][i + 1];
		Player_Data[1][i] = Player_Data[1][i + 1];
		Player_Data[2][i] = Player_Data[2][i + 1];
		Player_Data[3][i] = Player_Data[3][i + 1];
		Player_Data[4][i] = Player_Data[4][i + 1];
		Player_Data[5][i] = Player_Data[5][i + 1];
	}
	i--;
	Player_Data[0][i] = 0;
	Player_Data[1][i] = 0;
	Player_Data[2][i] = 0;
	Player_Data[3][i] = 0;
	Player_Data[4][i] = 0;
	Player_Data[5][i] = 0;

	if (player_number == 1)
	{
		element_number_l--;
	}
	else if (player_number == 2)
	{
		element_number_r--;
	}
	else
	{
		//printf("DeleteInfoFromData error 1\n");
	}

	return;
}

bool check_win()
{
	int amount_of_building_player_1 = 0;
	int amount_of_building_player_2 = 0;
	int min_amount_to_lose = 1; //we can change this value to any we want
	for (int i = 0; Elements_Info_Player_Left[0][i] != 0; i++)
	{
		amount_of_building_player_1++;
	}
	for (int i = 0; Elements_Info_Player_Right[0][i] != 0; i++)
	{
		amount_of_building_player_2++;
	}
	if (amount_of_building_player_1 < min_amount_to_lose || amount_of_building_player_2 < min_amount_to_lose)
	{
		if (amount_of_building_player_1 < amount_of_building_player_2)
		{
			system("cls");
			Player2_WIN();
			printf("Amoun of building for player 1 = %d\n", amount_of_building_player_1);
			printf("Amoun of building for player 2 = %d\n\n", amount_of_building_player_2);
			return 0;
		}	
		else if (amount_of_building_player_1 == amount_of_building_player_2)
		{
			system("cls");
			printf("\n\nNo one win!\n\n");
			printf("Amoun of building for player 1 = %d\n", amount_of_building_player_1);
			printf("Amoun of building for player 2 = %d\n\n", amount_of_building_player_2);
			return 0;
		}
		else if (amount_of_building_player_1 > amount_of_building_player_2)
		{
			system("cls");
			Player1_WIN();  
			printf("Amoun of building for player 1 = %d\n", amount_of_building_player_1);
			printf("Amoun of building for player 2 = %d\n\n", amount_of_building_player_2);
			return 0;
		}
		else
		{
			printf("check_win error 1");
			return 0;
		}
	}
	else return 1;
}

void give_money()
{
	int add_money_per_one_building = 15
;
	//type=53
	int amount_building_player_1 = 0;
	int amount_building_player_2 = 0;	
	for (int i = 0; Elements_Info_Player_Left[0][i] != 0; i++)
	{
		if (Elements_Info_Player_Left[0][i] == 53)
		{
			amount_building_player_1++;
		}
			
	}
	for (int i = 0; Elements_Info_Player_Right[0][i] != 0; i++)
	{
		if (Elements_Info_Player_Right[0][i] == 53)
		{
			amount_building_player_2++;
		}

	}
	total_money_left += add_money_per_one_building * amount_building_player_1;
	total_money_right += add_money_per_one_building * amount_building_player_2;
	return;
}