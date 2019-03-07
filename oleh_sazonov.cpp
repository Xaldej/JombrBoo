#pragma once
#include "head.h"
HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
#define colorRESET SetConsoleTextAttribute  (col, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#define colorBLUE SetConsoleTextAttribute  (col, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#define colorGREEN SetConsoleTextAttribute  (col, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define NEXT_SLIDE  Sleep(300);system("cls");


// Left & Right info panels which not comtained in main field 
char Left_panel[field_height][panel_width];
char Right_panel[field_height][panel_width];

char Name_P1[name_lenght] = " Jombr";
char Name_P2[name_lenght] = " BooM ";
int total_money_left = 1200;
int total_money_right = 1200;

//[0][*][*] - main field;
//[1][*][*] -copy of field for displaying objects on installation of object 

int Batle_field[n_fields][field_height][field_width];
int Shop_field[field_height][field_width + panel_width + panel_width]; // main shop screen

//it defines index of cell for loging info about installed objects
// -1 because will be use ++ on activation of function. Then first value will bee equall 0
int element_number_l = -1;
int element_number_r = -1;

int Elements_Info_Player_Left[info_h][info_w];
int Elements_Info_Player_Right[info_h][info_w];

// Type of object for initialization on first opening of shop
//it uses in functions of movement and displaying 

char building_type = BIG_GUN;

char player; //('R' - player2; 'L' - player1)

int *arr = new int[(Building_height*Building_width)];
int Building[Building_height][Building_width];

//this variables contained position of objects on time of movement objects in shopping time 
int current_position_h;
int current_position_w;
int current_pos_extr_w;

int coordinate_h;
int coordinate_w;


void o_buy_item(char player, char building_type)
{
	//this function write data about obj type, position  and characteristic to the info arrays
	int *item = o_building_select(player, building_type);

	for (int h = 0, i = 0; h < Building_height; h++)
	{
		for (int w = 0; w < Building_width; w++, i++)
		{
			Batle_field[main_f][current_position_h + h][current_position_w + w] = *(item + i);
		}
	}

	o_put_coordinates(player, building_type, coordinate_h, coordinate_w);
	o_write_info_about_player_odject(player, building_type, coordinate_h, coordinate_w);

	return;
}

int *o_building_select(char player, char building_type) //switchs build according to user select (returns pointer to array of building symbols in int type)
{
	int *building = new int[(Building_height*Building_width)];  //pointer to array of characters vallues acordig to user select


	//here contains integer vallues of character on ASCII table for buildings visualisation
	int Wall1[Building_height*Building_width] = { 32,178,32,32,178,32,32,178,32 };
	int Wall_cheap1[Building_height*Building_width] = { 32,177,32,32,177,32,32,177,32 };
	int Goldmine[Building_height*Building_width] = { 201, 205, 187, 186, 36, 186, 200, 205, 188 };

	int Gun1[(Building_height*Building_width)] = { 178,178,178,178,204,205,178,178,178 };
	int Gun2[Building_height*Building_width] = { 178,178,178,205,185,178,178,178,178 };

	int Gun_cheap1[(Building_height*Building_width)] = { 176,176,176,176,199,196,176,176,176 };
	int Gun_cheap2[Building_height*Building_width] = { 176,176,176,196,182,176,176,176,176 };

	if (building_type == BIG_WALL) //bigg wall
	{

		for (int i = 0; i < (Building_height*Building_width); i++)
		{
			building[i] = Wall1[i];
		}
		return building;
	}
	else if (building_type == SMALL_WALL) //small wall
	{
		for (int i = 0; i < (Building_height*Building_width); i++)
		{
			building[i] = Wall_cheap1[i];
		}
		return building;
	}
	else if (building_type == GOLDMINE)  //goldmine building
	{
		for (int i = 0; i < (Building_height*Building_width); i++)
		{
			building[i] = Goldmine[i];
		}
		return building;
	}

	switch (player)
	{
	case 'L':
		if (building_type == BIG_GUN) //big gun
		{
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Gun1[i];
			}
			return building;
		}
		else if (building_type == SMALL_GUN) //small gun
		{
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Gun_cheap1[i];
			}
			return building;
		}


	case 'R':
		if (building_type == BIG_GUN)  //big gun
		{
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Gun2[i];
			}
			return building;
		}
		else if (building_type == SMALL_GUN) //small gun
		{
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Gun_cheap2[i];
			}
			return building;
		}
		break;

	default:
		break;
	}
	return 0;
}

bool o_check_free_zone(int current_position_h, int current_position_w, char building_type)
{
#define BTL_F_M  Batle_field[main_f]
#define CUR_POS_h current_position_h
#define CUR_POS_w current_position_w

	//This function cheks opportunity to install objects by current coordinates
	// Start point of calculation is central coors of item

	//checking of empty zone by current oblect coors for any object
	if (BTL_F_M[CUR_POS_h + 0][CUR_POS_w] != 32 || BTL_F_M[CUR_POS_h + 0][CUR_POS_w + 1] != 32 || BTL_F_M[CUR_POS_h + 0][CUR_POS_w + 2] != 32
		|| BTL_F_M[CUR_POS_h + 1][CUR_POS_w] != 32 || BTL_F_M[CUR_POS_h + 1][CUR_POS_w + 1] != 32 || BTL_F_M[CUR_POS_h + 1][CUR_POS_w + 2] != 32
		|| BTL_F_M[CUR_POS_h + 2][CUR_POS_w] != 32 || BTL_F_M[CUR_POS_h + 2][CUR_POS_w + 1] != 32 || BTL_F_M[CUR_POS_h + 2][CUR_POS_w + 2] != 32
		)
	{
		printf("\a\r                           Zone is already taken                           ");
		Sleep(1500);
		return false;
	}
	else if (building_type == BIG_GUN || building_type == SMALL_GUN || building_type == GOLDMINE)
	{
		//checking neighbor cells around obj 
		if (
			BTL_F_M[CUR_POS_h - 1][CUR_POS_w] != 32 || BTL_F_M[CUR_POS_h - 1][CUR_POS_w + 1] != 32 || BTL_F_M[CUR_POS_h - 1][CUR_POS_w + 2] != 32       //top
			|| BTL_F_M[CUR_POS_h + 3][CUR_POS_w] != 32 || BTL_F_M[CUR_POS_h + 3][CUR_POS_w + 1] != 32 || BTL_F_M[CUR_POS_h + 3][CUR_POS_w + 2] != 32		//bottom
			|| BTL_F_M[CUR_POS_h + 0][CUR_POS_w - 1] != 32 || BTL_F_M[CUR_POS_h + 1][CUR_POS_w - 1] != 32 || BTL_F_M[CUR_POS_h + 2][CUR_POS_w - 1] != 32       //left
			|| BTL_F_M[CUR_POS_h + 0][CUR_POS_w + 3] != 32 || BTL_F_M[CUR_POS_h + 1][CUR_POS_w + 3] != 32 || BTL_F_M[CUR_POS_h + 2][CUR_POS_w + 3] != 32	   //right
			)
		{
			printf("\a\r                      Too close. You can not build here                      ");
			Sleep(1500);
			return false;
		}

	}
	else if (building_type == BIG_WALL || building_type == SMALL_WALL)
	{
		//checking neighbor cells around obj  (only top and bottom because left and right chars of walls  it is char'32' which used like empty)

		if (
			BTL_F_M[CUR_POS_h - 1][CUR_POS_w + 1] != 32         //top
			|| BTL_F_M[CUR_POS_h + 3][CUR_POS_w + 1] != 32        //bottom
			)
		{
			printf("\a\r                      Too close. You can not build here                      ");
			Sleep(1500);
			return false;
		}

	}
	return true;
}

int o_calculate_money(char player, char building_type)
{

	if (player == 'L')
	{
		if (total_money_left < o_item_price(building_type))
		{
			printf("\r                                Not enough money                             ");
			Sleep(1500);
			return -1;
		}
		else
		{
			total_money_left = total_money_left - o_item_price(building_type);
			o_buy_item(player, building_type);
			return 0;

		}
	}
	else if (player == 'R')
	{
		if (total_money_right < o_item_price(building_type))
		{
			printf("\r                                Not enough money                             ");
			Sleep(1500);
			return -1;
		}
		else
		{
			total_money_right = total_money_right - o_item_price(building_type);
			o_buy_item(player, building_type);
			return 0;

		}
	}
	return 0;
}


void o_display_batle_field(int panel_width, int field_height, int field_width)
{
	int turn;

	money_have();   //calculation amout of money every time when repaints main field 

	player == 'L' ? turn = 1 : turn = 2;  //it for displaying inscription of player move

	system("cls");

	for (int h = 0; h < field_height; h++)
	{
		for (int lp = 0; lp < panel_width; lp++)
		{
			printf("%c", Left_panel[h][lp]);
		}

		for (int w = 0; w < field_width; w++)
		{
			printf("%c", (char)Batle_field[main_f][h][w]);
		}

		for (int rp = 0; rp < panel_width; rp++)
		{
			printf("%c", Right_panel[h][rp]);
		}
		printf("\n");
	}

	printf("    Open Shop:    [P] \t\tSkip the turn:\t[-]\t\tPlayer %d turn", turn);;

	return;
}
void o_display_copy_batle_field()   //action_in
{
	system("cls");
	for (int h = 0; h < field_height; h++) {
		for (int lp = 0; lp < panel_width; lp++)
		{
			printf("%c", Left_panel[h][lp]);
		}

		for (int w = 0; w < field_width; w++)
		{
			printf("%c", (char)Batle_field[copy_f][h][w]);
		}

		for (int rp = 0; rp < panel_width; rp++)
		{
			printf("%c", Right_panel[h][rp]);
		}
		printf("\n");
	}
	//123456789.123456789.123456789.123456789.123456789.123456789.123456789.123456789.
	printf("\tMove: [W, A, S, D]   Next: [N]     Buy: [9]    Battle: [P] ");
	return;
}

void o_display_marker_in_store(char building_type)
{
	//list of allowed marker positions
	int h = 11;
	int w0 = 26;

	int w11 = w0 + 0;
	int w12 = w0 + 2;
	int w21 = w0 + 7;
	int w22 = w0 + 9;
	int w31 = w0 + 14;
	int w32 = w0 + 16;
	int w41 = w0 + 21;
	int w42 = w0 + 23;
	int w51 = w0 + 28;
	int w52 = w0 + 30;

	building_type == NULL ? building_type = BIG_GUN : building_type;  //if bulding type not initialized BIG_GUN will be use by default 

	Shop_field[h][w11] = ' '; Shop_field[h][w12] = ' ';
	Shop_field[h][w21] = ' '; Shop_field[h][w22] = ' ';
	Shop_field[h][w31] = ' '; Shop_field[h][w32] = ' ';
	Shop_field[h][w41] = ' '; Shop_field[h][w42] = ' ';
	Shop_field[h][w51] = ' '; Shop_field[h][w52] = ' ';

	if (building_type == BIG_GUN)
	{
		Shop_field[h][w11] = '{'; Shop_field[h][w12] = '}';
	}
	else if (building_type == SMALL_GUN)
	{
		Shop_field[h][w21] = '{'; Shop_field[h][w22] = '}';
	}
	else if (building_type == BIG_WALL)
	{
		Shop_field[h][w31] = '{'; Shop_field[h][w32] = '}';
	}
	else if (building_type == SMALL_WALL)
	{
		Shop_field[h][w41] = '{'; Shop_field[h][w42] = '}';
	}
	else if (building_type == GOLDMINE)
	{
		Shop_field[h][w51] = '{'; Shop_field[h][w52] = '}';
	}
	return;
}
int o_display_shop()
{
	o_display_marker_in_store(building_type);  //every time when shop was opened this function move marker to point according to last object selection
	system("cls");

	char item_1_price[] = "$600";
	char item_2_price[] = "$400";
	char item_3_price[] = "$200";
	char item_4_price[] = "$100";
	char item_5_price[] = "$950";

	char item_1_health[] = " 10 ";
	char item_2_health[] = "  5 ";
	char item_3_health[] = " 20 ";
	char item_4_health[] = " 10 ";
	char item_5_health[] = "  5 ";

	char item_1_shots[] = " 20 ";
	char item_2_shots[] = " 10 ";
	char item_3_shots[] = "  0 ";
	char item_4_shots[] = "  0 ";
	char item_5_shots[] = "  0 ";

	char item_1_money[] = " +0 ";
	char item_2_money[] = " +0 ";
	char item_3_money[] = " +0 ";
	char item_4_money[] = " +0 ";
	char item_5_money[] = "+15 ";

	char str_Items[] = "       ";
	char str_Select[] = "       ";
	char str_Price[] = "Price: ";
	char str_Health[] = "Health: ";
	char str_Shots[] = "Shots: ";
	char str_Money[] = "Money+:";

	//anchor start points for displaying objects in shop 
	int h0 = 7;
	int w0 = 26;
	int w1 = w0;
	int next_point = 7;
	//

	Shop_field[h0 + 0][w0 + 0] = 178; Shop_field[h0 + 0][w0 + 1] = 178; Shop_field[h0 + 0][w0 + 2] = 178;

	if (player == 'L')
	{
		Shop_field[h0 + 1][w0 + 0] = 178; Shop_field[h0 + 1][w0 + 1] = 204; Shop_field[h0 + 1][w0 + 2] = 205;
	}
	else if (player == 'R')
	{
		Shop_field[h0 + 1][w0 + 0] = 205; Shop_field[h0 + 1][w0 + 1] = 185; Shop_field[h0 + 1][w0 + 2] = 178;
	}

	Shop_field[h0 + 2][w0 + 0] = 178; Shop_field[h0 + 2][w0 + 1] = 178; Shop_field[h0 + 2][w0 + 2] = 178;

	w0 = w0 + next_point;

	Shop_field[h0 + 0][w0 + 0] = 176; Shop_field[h0 + 0][w0 + 1] = 176; Shop_field[h0 + 0][w0 + 2] = 176;

	if (player == 'L')
	{
		Shop_field[h0 + 1][w0 + 0] = 176; Shop_field[h0 + 1][w0 + 1] = 199; Shop_field[h0 + 1][w0 + 2] = 196;
	}
	else if (player == 'R')
	{
		Shop_field[h0 + 1][w0 + 0] = 196; Shop_field[h0 + 1][w0 + 1] = 182; Shop_field[h0 + 1][w0 + 2] = 176;
	}

	Shop_field[h0 + 2][w0 + 0] = 176; Shop_field[h0 + 2][w0 + 1] = 176; Shop_field[h0 + 2][w0 + 2] = 176;

	w0 = w0 + next_point;

	Shop_field[h0 + 0][w0 + 0] = 32; Shop_field[h0 + 0][w0 + 1] = 178; Shop_field[h0 + 0][w0 + 2] = 32;
	Shop_field[h0 + 1][w0 + 0] = 32; Shop_field[h0 + 1][w0 + 1] = 178; Shop_field[h0 + 1][w0 + 2] = 32;
	Shop_field[h0 + 2][w0 + 0] = 32; Shop_field[h0 + 2][w0 + 1] = 178; Shop_field[h0 + 2][w0 + 2] = 32;

	w0 = w0 + next_point;

	Shop_field[h0 + 0][w0 + 0] = 32; Shop_field[h0 + 0][w0 + 1] = 177; Shop_field[h0 + 0][w0 + 2] = 32;
	Shop_field[h0 + 1][w0 + 0] = 32; Shop_field[h0 + 1][w0 + 1] = 177; Shop_field[h0 + 1][w0 + 2] = 32;
	Shop_field[h0 + 2][w0 + 0] = 32; Shop_field[h0 + 2][w0 + 1] = 177; Shop_field[h0 + 2][w0 + 2] = 32;

	w0 = w0 + next_point;

	Shop_field[h0 + 0][w0 + 0] = 201; Shop_field[h0 + 0][w0 + 1] = 205; Shop_field[h0 + 0][w0 + 2] = 187;
	Shop_field[h0 + 1][w0 + 0] = 186; Shop_field[h0 + 1][w0 + 1] = 36;  Shop_field[h0 + 1][w0 + 2] = 186;
	Shop_field[h0 + 2][w0 + 0] = 200; Shop_field[h0 + 2][w0 + 1] = 205; Shop_field[h0 + 2][w0 + 2] = 188;

	Shop_field[h0 + 4][w1 + 1] = 49;
	Shop_field[h0 + 4][w1 + 8] = 50;
	Shop_field[h0 + 4][w1 + 15] = 51;
	Shop_field[h0 + 4][w1 + 22] = 52;
	Shop_field[h0 + 4][w1 + 29] = 53;

	//this var-s used for stationing of obj-s in shop field
	int h_items = 1;
	int h_select = 4;
	int h_price = 6;
	int h_health = 8;
	int h_shots = 9;
	int h_money = 10;

	int w_item1 = 0;
	int w_item2 = 7;
	int w_item3 = 14;
	int w_item4 = 21;
	int w_item5 = 28;

	//start displaying of objects parameters in shop info
	for (int i = 0; i < 4; i++)  //4 - length of inscription
	{
		Shop_field[h0 + h_price][w1 + w_item1 + i] = item_1_price[i];
		Shop_field[h0 + h_price][w1 + w_item2 + +i] = item_2_price[i];
		Shop_field[h0 + h_price][w1 + w_item3 + i] = item_3_price[i];
		Shop_field[h0 + h_price][w1 + w_item4 + i] = item_4_price[i];
		Shop_field[h0 + h_price][w1 + w_item5 + i] = item_5_price[i];
	}

	for (int i = 0; i < 4; i++)  //4 - length of inscription
	{
		Shop_field[h0 + h_health][w1 + w_item1 + i] = item_1_health[i];
		Shop_field[h0 + h_health][w1 + w_item2 + i] = item_2_health[i];
		Shop_field[h0 + h_health][w1 + w_item3 + i] = item_3_health[i];
		Shop_field[h0 + h_health][w1 + w_item4 + i] = item_4_health[i];
		Shop_field[h0 + h_health][w1 + w_item5 + i] = item_5_health[i];

	}
	for (int i = 0; i < 4; i++)  //4 - length of inscription
	{
		Shop_field[h0 + h_shots][w1 + w_item1 + i] = item_1_shots[i];
		Shop_field[h0 + h_shots][w1 + w_item2 + i] = item_2_shots[i];
		Shop_field[h0 + h_shots][w1 + w_item3 + i] = item_3_shots[i];
		Shop_field[h0 + h_shots][w1 + w_item4 + i] = item_4_shots[i];
		Shop_field[h0 + h_shots][w1 + w_item5 + i] = item_5_shots[i];

	}
	for (int i = 0; i < 4; i++)  //4 - length of inscription
	{
		Shop_field[h0 + h_money][w1 + w_item1 + i] = item_1_money[i];
		Shop_field[h0 + h_money][w1 + w_item2 + i] = item_2_money[i];
		Shop_field[h0 + h_money][w1 + w_item3 + i] = item_3_money[i];
		Shop_field[h0 + h_money][w1 + w_item4 + i] = item_4_money[i];
		Shop_field[h0 + h_money][w1 + w_item5 + i] = item_5_money[i];

	}
	//end of  displaying of objects parameters in shop info


	int w0_inscr = 15; //init start position of obj parameters titles

	for (int i = 0; i < 7; i++)  // 7 - lenght of inscription
	{
		Shop_field[h0 + h_items][w0_inscr + i] = str_Items[i];
		Shop_field[h0 + h_select][w0_inscr + i] = str_Select[i];
		Shop_field[h0 + h_price][w0_inscr + i] = str_Price[i];
		Shop_field[h0 + h_health][w0_inscr + i] = str_Health[i];
		Shop_field[h0 + h_shots][w0_inscr + i] = str_Shots[i];
		Shop_field[h0 + h_money][w0_inscr + i] = str_Money[i];
	}


	for (int h = 0; h < field_height; h++)
	{
		for (int w = 0; w < (field_width + (panel_width * 2)); w++) // (field_width + (panel_width * 2)) because used all lenght of screen which include lenght of panels and field lenght
		{
			printf("%c", (char)Shop_field[h][w]);
		}
		printf("\n");
	}
	printf("\t\t Select: [1-4]  [9] \t Next: [N]\tBack: [P] ");

	return 0;
}

void o_fill_batle_field_after_start()
{
	//this function fills main field and pannels after start 
	//here you can set any characters to fiil main field
	//h - height  w - width
	for (int h = 0; h < panel_height; h++)
	{
		for (int w = 0; w < panel_width; w++)
		{
			if (w == panel_width - 1)
			{
				Left_panel[h][w] = '|';
			}
			else
			{
				Left_panel[h][w] = ' ';
			}
		}
	}

	for (int h = 0; h < field_height; h++)
	{
		for (int w = 0; w < field_width; w++)
		{
			if (w == (field_width / 2) + 1)
			{
				Batle_field[main_f][h][w] = '.';
				Batle_field[copy_f][h][w] = '.';
			}
			else
			{
				Batle_field[main_f][h][w] = ' ';
			}
		}
	}

	for (int h = 0; h < panel_height; h++) {
		for (int w = 0; w < panel_width; w++)
		{
			if (w == 0)
			{
				Right_panel[h][w] = '|';
			}
			else
			{
				Right_panel[h][w] = ' ';
			}
		}

	}
	return;
}
void o_fill_pannels()
{
	const int money_lenght = 7;
	const int name_size = 8;

	char Player_1_name[name_size] = "Player1";
	char Player_2_name[name_size] = "Player2";
	char coins[money_lenght] = "Money:";

	for (int w = 0; w < name_size; w++)
	{
		Left_panel[1][w + 1] = Player_1_name[w];
		Right_panel[1][w + 2] = Player_2_name[w];
	}
	for (int w = 0; w < name_lenght; w++)
	{
		Left_panel[2][w + 1] = Name_P1[w];
		Right_panel[2][w + 3] = Name_P2[w];
	}

	for (int w = 0; w < panel_width - 1; w++)
	{
		//this characters to make appereance(construction) of pannels
		Left_panel[3][w] = '-';
		Right_panel[3][w + 1] = '-';
		Left_panel[8][w] = '-';
		Right_panel[8][w + 1] = '-';
		Left_panel[23][w] = 196;
		Right_panel[23][w + 1] = 196;
	}

	//corners on pannels
	Left_panel[23][9] = 217;
	Right_panel[23][0] = 192;

	Left_panel[6][2] = '$';
	Right_panel[6][3] = '$';


	for (int w = 0; w < money_lenght; w++)
	{
		Left_panel[5][w + 1] = coins[w];
		Right_panel[5][w + 2] = coins[w];
	}

	money_have();

	return;
}
void o_fill_shop()
{
	//this function used for beginning filling of shop field 
	for (int h = 0; h < field_height; h++)
	{
		for (int lp = 0, w = 0; lp < panel_width; lp++, w++)
		{
			Shop_field[h][w] = (int)Left_panel[h][lp];
		}

		for (int w = panel_width; w < field_width + panel_width; w++)
		{
			Shop_field[h][w] = (int)' ';
		}
		for (int rp = 0, w = field_width + panel_width; rp < panel_width; rp++, w++)
		{
			Shop_field[h][w] = (int)Right_panel[h][rp];
		}
	}
	return;
}


int o_item_price(char building_type)
{
	// This function is used to determine the price of the purchase building.
	int item_price;

	(building_type == BIG_GUN) ? item_price = gun_1_price : 1;
	(building_type == SMALL_GUN) ? item_price = gun_2_price : 1;
	(building_type == BIG_WALL) ? item_price = wall_1_price : 1;
	(building_type == SMALL_WALL) ? item_price = wall_2_price : 1;
	(building_type == GOLDMINE) ? item_price = goldmine_price : 1;

	return item_price;
}

void o_get_field_copy()
{
	for (int h = 0; h < field_height; h++)
	{
		for (int w = 0; w < field_width; w++)
		{
			Batle_field[copy_f][h][w] = Batle_field[main_f][h][w];
		}
	}
	return;
}
void o_get_shop_actions() // this func to take user input(actions) in shop
{
	char action_in_shop;
	do
	{
		action_in_shop = _getwch();
		switch (action_in_shop)
		{

		case '<': player = 'L';  o_display_shop(); break;  // to switch players in the store, use (Shift + <) changes to the left (test feature)
		case '>': player = 'R';  o_display_shop(); break;  // to switch players in the store, use (Shift + >) changes to the right (test feature)

		case BIG_GUN: building_type = BIG_GUN; o_move_elements(player, building_type);  break;
		case SMALL_GUN: building_type = SMALL_GUN; o_move_elements(player, building_type);  break;
		case BIG_WALL: building_type = BIG_WALL; o_move_elements(player, building_type);  break;
		case SMALL_WALL: building_type = SMALL_WALL; o_move_elements(player, building_type);  break;
		case GOLDMINE: building_type = GOLDMINE; o_move_elements(player, building_type);  break;

		case 'N': case'n':  building_type++; building_type == GOLDMINE + 1 ? building_type = BIG_GUN : building_type; o_display_shop();   break; //switch to next item
		case '9':
			if (building_type == NULL)
			{
				break;
			}
			else
			{
				o_move_elements(player, building_type); break;
			}
		case 'P': case 'p': o_display_batle_field(panel_width, field_height, field_width); o_get_main_screen_actions(); return;	 break;

		default: break;
		}
	} while (action_in_shop != '9' && action_in_shop != 'p' && action_in_shop != SMALL_WALL && action_in_shop != GOLDMINE && action_in_shop != 'P' && action_in_shop != BIG_GUN && action_in_shop != SMALL_GUN && action_in_shop != BIG_WALL);

	return;
}
void o_get_main_screen_actions() // this funktion gets controll buttons of users action on main field
{
	char button;
	do
	{
		button = _getwch();
		switch (button)
		{
		case 'P': case 'p':  o_fill_shop(); o_display_shop(); o_get_shop_actions(); return; break;
		case '-': return;												//skip turn
		case 'Y': case 'y':  o_display_h_coordinates_field();	break;  //for dev
		case 'X': case 'x':  o_display_w_coordinates_field();	break;  //for dev
		case 'I': case 'i':  print_objects_info();				break;  //for dev
		default: break;
		}
	} while (button != 'p' || button != 'P' || button != 'x' || button != 'X' || button != 'Y' || button != 'y' || button != 'i' || button != 'I');

	return;
}

void give_item_on_start(char player, char building_type, int centre_h, int centre_w)
{
	//write info about player obj whihc gives on start
	int *item = o_building_select(player, building_type);

	o_put_coordinates(player, building_type, centre_h - 1, centre_w - 1);
	o_write_info_about_player_odject(player, building_type, centre_h - 1, centre_w - 1);

	for (int h = 0, i = 0; h < Building_height; h++)
	{
		for (int w = 0; w < Building_width; w++, i++)
		{
			Batle_field[main_f][centre_h - 1 + h][centre_w - 1 + w] = *(item + i);
		}
	}

	return;
}

//start_movement functions*******************************//
void o_move_elements(char player, char building_type) //action_in
{

	int temp_value;   //variable to get returned value of function o_calculate_money();
	char movement_to = 'X';  // 'X' used to display object on main field after select in shop

	if (player == 'L')
	{
		current_position_h = 9;    // 0 , 9, 9, 56 current positions of respawn objects point on main field after getting object in the shop
		current_position_w = 0;
	}
	else if (player == 'R')
	{
		current_position_h = 9;
		current_position_w = 56;
	}

	system("cls");

	o_display_copy_batle_field();

	while (movement_to != '9' || movement_to != '0')
	{

		switch (movement_to)
		{
		case '>': o_move_elements('R', building_type);  break;
		case '<': o_move_elements('L', building_type);  break;
		case 'X': o_get_field_copy(); current_position_h++;	o_move_up(player, building_type); break; //movement of object to start point(it used to displaying object)
		case 'w': case 'W': o_get_field_copy(); o_move_up(player, building_type);			  break;
		case 's': case 'S': o_get_field_copy(); o_move_down(player, building_type);			  break;
		case 'a': case 'A': o_get_field_copy(); o_move_left(player, building_type);			  break;
		case 'd': case 'D': o_get_field_copy(); o_move_right(player, building_type);		  break;
		case '9':
			if (o_check_free_zone(current_position_h, current_position_w, building_type) == true)
			{
				temp_value = o_calculate_money(player, building_type);
				if (temp_value == -1)
				{
					o_get_field_copy();
					o_display_copy_batle_field();
					current_position_h++; o_move_up(player, building_type);
				}
				else if (temp_value == 0)
				{
					o_display_batle_field(panel_width, field_height, field_width);
					return;
				}

			}
			break;
		case 'p': case 'P':		o_display_batle_field(panel_width, field_height, field_width); return; break;
		case'n': case'N':
			building_type++; building_type == '6' ? building_type = BIG_GUN : building_type;
			current_position_h++;	o_move_up(player, building_type);
			break;

		default: break;
		}
		movement_to = _getwch();
	}
	return;
}
void o_move_up(char player, char building_type)
{
	arr = o_building_select(player, building_type);  //arr - array which used like buffer to containing objects symbols after selecting in shop or movement

	for (int h = 0, i = 0; h < Building_height; h++)
	{
		for (int w = 0; w < Building_width; w++, i++)
		{
			Building[h][w] = arr[i];
		}
	}

	for (int h = 0; h > -1; h--)
	{
		for (int w = 0; w > -1; w--)
		{
			if (current_position_h > 0)
			{
				current_position_h--;
				coordinate_h = current_position_h;  //getting of object  corrs after instalation to write position of obj-s in array of coors 
				for (int shift = 0; shift < Building_height; shift++)
				{
					for (int row = 0; row < Building_height; )
					{
						Batle_field[copy_f][current_position_h + row][current_position_w + shift] = Building[h + row][w + shift];
						row++;
						Batle_field[copy_f][current_position_h + row][current_position_w + shift] = Batle_field[main_f][current_position_h + row][current_position_w + shift];
					}
				}
			}
			else
			{
				printf("\a");
				current_position_h++;
				o_move_up(player, building_type);
			}
		}
	}
	system("cls");
	o_display_copy_batle_field();  //activating of displaying copy of main field
	return;
}
void o_move_down(char player, char building_type)
{
	arr = o_building_select(player, building_type); //arr - array which used like buffer to containing objects symbols after selecting in shop or movement

	for (int h = 0, i = 0; h < Building_height; h++)
	{
		for (int w = 0; w < Building_width; w++, i++)
		{
			Building[h][w] = arr[i];
		}
	}

	for (int h = 0; h > -1; h--)
	{
		for (int w = 0; w > -1; w--)
		{
			if (current_position_h < field_height - Building_height) //- Building_height because we can't move obj out of field zone
			{
				current_position_h++;

				coordinate_h = current_position_h; //getting of object  corrs after instalation to write position of obj-s in array of coors 

				for (int shift = 0; shift < Building_height; shift++)
				{
					for (int row = 0; row < Building_height; )
					{
						Batle_field[copy_f][current_position_h + row][current_position_w + shift] = Building[h + row][w + shift];
						row++;
						Batle_field[copy_f][current_position_h + row][current_position_w + shift] = Batle_field[main_f][current_position_h + row][current_position_w + shift];
					}
				}
			}
			else
			{
				printf("\a");
				current_position_h--;
				o_move_down(player, building_type);
			}
		}
	}
	system("cls");
	o_display_copy_batle_field(); //activating of displaying copy of main field

	return;
}
void o_move_left(char player, char building_type)
{
	player == 'L' ? current_pos_extr_w = 1 : current_pos_extr_w = 31;  // 1 | 31 - left border vallues of players field zone

	arr = o_building_select(player, building_type);

	for (int h = 0, i = 0; h < Building_height; h++)
	{
		for (int w = 0; w < Building_width; w++, i++)
		{
			Building[h][w] = arr[i];
		}
	}

	for (int h = 0; h > -1; h--)  // h-- because movement to begin of field (to the side of zero coors)
	{
		for (int w = 0; w > -1; w--)
		{
			if (current_position_w > current_pos_extr_w)
			{
				current_position_w--;

				coordinate_w = current_position_w; //getting of object  corrs after instalation to write position of obj-s in array of coors 

				for (int shift = 0; shift < Building_width; shift++)
				{
					for (int coll = 0; coll < Building_width; )
					{
						Batle_field[copy_f][current_position_h + shift][current_position_w + coll] = Building[h + shift][w + coll];
						coll++;
						Batle_field[copy_f][current_position_h + shift][current_position_w + coll] = Batle_field[main_f][current_position_h + shift][current_position_w + coll];
					}
				}
			}
			else
			{
				printf("\a");
				current_position_w++;
				o_move_left(player, building_type);
			}
		}
	}
	system("cls");
	o_display_copy_batle_field();
}
void o_move_right(char player, char building_type)
{
	arr = o_building_select(player, building_type);

	player == 'L' ? current_pos_extr_w = 26 : current_pos_extr_w = field_width - Building_width - 1;

	for (int h = 0, i = 0; h < Building_height; h++)
	{
		for (int w = 0; w < Building_width; w++, i++)
		{
			Building[h][w] = arr[i];
		}
	}
	for (int h = 0; h > -1; h--)
	{
		for (int w = 0; w > -1; w--)
		{
			if (current_position_w < current_pos_extr_w)
			{
				current_position_w++;

				coordinate_w = current_position_w; //принимаем координаты для записи положения обьектов в координатый массив

				for (int shift = 0; shift < Building_width; shift++)  //shift - shifting by height ( y corrs)
				{
					for (int coll = 0; coll < Building_width; )       //shift - shifting by width ( y corrs)
					{
						Batle_field[copy_f][current_position_h + shift][current_position_w + coll] = Building[h + shift][w + coll];
						coll++;
						Batle_field[copy_f][current_position_h + shift][current_position_w + coll] = Batle_field[main_f][current_position_h + shift][current_position_w + coll];
					}
				}
			}
			else
			{
				printf("\a");

				current_position_w--;

				o_move_right(player, building_type);
			}
		}
	}
	system("cls");
	o_display_copy_batle_field();

	return;
}
/*end_movement_funktions*****************/


void money_have()
{
	char L1; char L2; char L3; char L4;
	char R1; char R2; char R3; char R4;

	int n1 = 0; int n2 = 0; int n3 = 0; int n4 = 0;
	int r1 = 0; int r2 = 0; int r3 = 0; int r4 = 0;

	//for player1
	if (total_money_left < 9999)  //9999 because selected leng = 4 symbols
	{
		n1 = (total_money_left / 1000);
		n2 = (total_money_left - n1 * 1000) / 100;
		n3 = (total_money_left - n1 * 1000 - n2 * 100) / 10;
		n4 = (total_money_left - n1 * 1000 - n2 * 100 - n3 * 10);

		L1 = 48 + n4;
		L2 = 48 + n3;
		L3 = 48 + n2;
		L4 = 48 + n1;

		Left_panel[6][7] = ' ';  //position of last  char of $ summ    +1
	}
	else
	{
		L1 = '9'; L2 = '9'; L3 = '9'; L4 = '9';
		Left_panel[6][7] = '+';
	}

	//for player2
	if (total_money_right < 9999)
	{
		r1 = (total_money_right / 1000);
		r2 = (total_money_right - r1 * 1000) / 100;
		r3 = (total_money_right - r1 * 1000 - r2 * 100) / 10;
		r4 = (total_money_right - r1 * 1000 - r2 * 100 - r3 * 10);

		Right_panel[6][8] = ' '; //position of last  char of $ summ    +1

		R1 = 48 + r4;
		R2 = 48 + r3;
		R3 = 48 + r2;
		R4 = 48 + r1;

	}
	else
	{
		Right_panel[6][8] = '+';
		R1 = '9'; R2 = '9'; R3 = '9'; R4 = '9';
	}

	Left_panel[6][6] = L1;		Left_panel[6][5] = L2;	 	Left_panel[6][4] = L3;		Left_panel[6][3] = L4;
	Right_panel[6][7] = R1;		Right_panel[6][6] = R2; 	Right_panel[6][5] = R3; 	Right_panel[6][4] = R4;

	return;
}

void o_put_coordinates(char player, char building_type, int coordinate_h, int coordinate_w)
{
	//this function push info to coordinate fields X  & Y . Only centrall coors of object need to write

	if (building_type == BIG_GUN || building_type == SMALL_GUN || building_type == GOLDMINE)
	{
		for (int h = 0; h < Building_height; h++)
		{
			for (int w = 0; w < Building_width; w++)
			{
				Batle_field[h_cors_f][coordinate_h + h][coordinate_w + w] = coordinate_h + 1;
				Batle_field[w_cors_f][coordinate_h + h][coordinate_w + w] = coordinate_w + 1;
			}
		}
	}
	else if (building_type == BIG_WALL || building_type == SMALL_WALL)
	{
		for (int h = 0; h < Building_height; h++)
		{
			for (int w = 0; w < Building_width; w++)
			{
				if (w == 1)  //becase walls has visible size 1x3 we are write only central line (on movement functions walls has size 3x3)
				{
					Batle_field[h_cors_f][coordinate_h + h][coordinate_w + w] = coordinate_h + 1;
					Batle_field[w_cors_f][coordinate_h + h][coordinate_w + w] = coordinate_w + 1;
				}
			}
		}
	}

	return;
}

void start_items_list()
{
	//heare you can give_item_on_start for player (don't mix up zones and players)

	// borders of players zones; 
	// player 'L'     ↑  1                     // player 'R'     ↑  1         
	//            1 <   > 27                   //           31 <   > 57
	//                ↓  22                    //    		     ↓  22


	give_item_on_start('L', GOLDMINE, 4, 2);
	give_item_on_start('L', GOLDMINE, 18, 2);

	give_item_on_start('R', GOLDMINE, 4, 56);
	give_item_on_start('R', GOLDMINE, 18, 56);



	return;
}

void o_write_info_about_player_odject(char player, char building_type, int coordinate_h, int coordinate_w)
{
	coordinate_h = coordinate_h + 1;  // +1 because bellow we need to know central position of obj
	coordinate_w = coordinate_w + 1;

	if (player == 'L')
	{
		element_number_l++;              // if the object is deleted, element_number_l need to reduce

		Elements_Info_Player_Left[b_type][element_number_l] = building_type;

		//start writing datas about obj-s parametrs to players info field acording user select after shopping
		if (building_type == BIG_GUN)
		{  //dest                   //n_field  //cell_index
			Elements_Info_Player_Left[shots][element_number_l] = shots_1;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_l;
			Elements_Info_Player_Left[HP][element_number_l] = HP_1;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
		else if (building_type == SMALL_GUN)
		{
			Elements_Info_Player_Left[shots][element_number_l] = shots_2;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_l;
			Elements_Info_Player_Left[HP][element_number_l] = HP_2;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
		else if (building_type == BIG_WALL)
		{
			Elements_Info_Player_Left[shots][element_number_l] = shots_3;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_3;
			Elements_Info_Player_Left[HP][element_number_l] = HP_3;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
		else if (building_type == SMALL_WALL)
		{
			Elements_Info_Player_Left[shots][element_number_l] = shots_4;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_4;
			Elements_Info_Player_Left[HP][element_number_l] = HP_4;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
		else if (building_type == GOLDMINE)
		{
			Elements_Info_Player_Left[shots][element_number_l] = shots_5;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_5;
			Elements_Info_Player_Left[HP][element_number_l] = HP_5;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
	}
	else if (player == 'R')
	{
		element_number_r++;
		Elements_Info_Player_Right[b_type][element_number_r] = building_type;

		if (building_type == BIG_GUN)
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_1;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_r;
			Elements_Info_Player_Right[HP][element_number_r] = HP_1;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
		else if (building_type == SMALL_GUN)
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_2;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_r;
			Elements_Info_Player_Right[HP][element_number_r] = HP_2;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
		else if (building_type == BIG_WALL)
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_3;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_3;
			Elements_Info_Player_Right[HP][element_number_r] = HP_3;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
		else if (building_type == SMALL_WALL)
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_4;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_4;
			Elements_Info_Player_Right[HP][element_number_r] = HP_4;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
		else if (building_type == GOLDMINE)
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_5;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_5;
			Elements_Info_Player_Right[HP][element_number_r] = HP_5;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
	}
	//end of writing datas about obj-s parametrs to players info field acording user select after shopping
	return;
}


//animation of start and victory screans
void Start_Screen_Animation()
{

	colorBLUE

		NEXT_SLIDE  cout << R"(




                                  
                                         _ 
                                        | |
                                        | |
                                    _   | |
                                   | |__| |
                                    \____/ 
    	)";


	NEXT_SLIDE  cout << R"(




 
                        _ 
                       | |  
                       | |                                          ___  
                   _   | |                                         / _ \ 
                  | |__| |                                        | (_) |
                   \____/                                          \___/
)";
	NEXT_SLIDE

		cout << R"(




 
       _  
      | |
      | |                                ___  
  _   | |                               / _ \ 
 | |__| |                              | (_) |
  \____/                                \___/ 
   )";

	NEXT_SLIDE  cout << R"( 





       _  
      | | 
      | |   ___                                            _ __ ___
  _   | |  / _ \                                          | '_ ` _ \
 | |__| | | (_) |                                         | | | | | |
  \____/   \___/                                          |_| |_| |_|
   )";

	NEXT_SLIDE  cout << R"(


   
 
     
       _                                         
      | |                                        
      | |   ___                        _ __ ___  
  _   | |  / _ \                      | '_ ` _ \ 
 | |__| | | (_) |                     | | | | | |
  \____/   \___/                      |_| |_| |_|                                         
      )";

	NEXT_SLIDE  cout << R"(   




     
       _                                                 _     
      | |                                               | |    
      | |   ___        _ __ ___                         | |__  
  _   | |  / _ \      | '_ ` _ \                        | '_ \ 
 | |__| | | (_) |     | | | | | |                       | |_) |
  \____/   \___/      |_| |_| |_|                       |_.__/                                                          
      )";

	NEXT_SLIDE  cout << R"(



 
        
       _                               _ 
      | |                             | |
      | |   ___      _ __ ___         | |__              _ __ 
  _   | |  / _ \    | '_ ` _ \        | '_ \            | '__|
 | |__| | | (_) |   | | | | | |       | |_) |           | |   
  \____/   \___/    |_| |_| |_|       |_.__/            |_|                                                 
 )";

	NEXT_SLIDE
		cout << R"( 





       _                           _  
      | |                         | |
      | |   ___      _ __ ___     | |__        _ __ 
  _   | |  / _ \    | '_ ` _ \    | '_ \      | '__|
 | |__| | | (_) |   | | | | | |   | |_) |     | |   
  \____/   \___/    |_| |_| |_|   |_.__/      |_|   
 )";




	NEXT_SLIDE
		cout << R"(





       _                         _                        ____ 
      | |                       | |                      |  _ \ 
      | |   ___    _ __ ___     | |__        _ __        | |_) |
  _   | |  / _ \  | '_ ` _ \    | '_ \      | '__|       |  _ < 
 | |__| | | (_) | | | | | | |   | |_) |     | |          | |_) |
  \____/   \___/  |_| |_| |_|   |_.__/      |_|          |____/ 
 )";

	NEXT_SLIDE  cout << R"(




   
       _                       _                ____           ____
      | |                     | |              |  _ \         / __ \
      | |   ___    _ __ ___   | |__    _ __    | |_) |       | |  | |
  _   | |  / _ \  | '_ ` _ \  | '_ \  | '__|   |  _ <        | |  | |
 | |__| | | (_) | | | | | | | | |_) | | |      | |_) |       | |__| |
  \____/   \___/  |_| |_| |_| |_.__/  |_|      |____/         \____/                                                           
 )";
	NEXT_SLIDE  cout << R"(





       _                       _              ____       ____        ____
      | |                     | |            |  _ \     / __ \      / __ \ 
      | |   ___    _ __ ___   | |__    _ __  | |_) |   | |  | |    | |  | |
  _   | |  / _ \  | '_ ` _ \  | '_ \  | '__| |  _ <    | |  | |    | |  | |
 | |__| | | (_) | | | | | | | | |_) | | |    | |_) |   | |__| |    | |__| |
  \____/   \___/  |_| |_| |_| |_.__/  |_|    |____/     \____/      \____/ 
 )";
	NEXT_SLIDE  cout << R"( 





       _                       _              ____     ____      ____     __  _
      | |                     | |            |  _ \   / __ \    / __ \   |  \/ 
      | |   ___    _ __ ___   | |__    _ __  | |_) | | |  | |  | |  | |  | \  /
  _   | |  / _ \  | '_ ` _ \  | '_ \  | '__| |  _ <  | |  | |  | |  | |  | |\/|
 | |__| | | (_) | | | | | | | | |_) | | |    | |_) | | |__| |  | |__| |  | |  |
  \____/   \___/  |_| |_| |_| |_.__/  |_|    |____/   \____/    \____/   |_|  |_                                                                           
 )";



	NEXT_SLIDE  cout << R"(





       _                       _              ____     ____     ____    __  __ 
      | |                     | |            |  _ \   / __ \   / __ \  |  \/  |
      | |   ___    _ __ ___   | |__    _ __  | |_) | | |  | | | |  | | | \  / |
  _   | |  / _ \  | '_ ` _ \  | '_ \  | '__| |  _ <  | |  | | | |  | | | |\/| |
 | |__| | | (_) | | | | | | | | |_) | | |    | |_) | | |__| | | |__| | | |  | |
  \____/   \___/  |_| |_| |_| |_.__/  |_|    |____/   \____/   \____/  |_|  |_|
)";


	NEXT_SLIDE  cout << R"(





       _                       _              ____     ____     ____    __  __ 
      | |                     | |            |  _ \   / __ \   / __ \  |  \/  |
      | |   ___    _ __ ___   | |__    _ __  | |_) | | |  | | | |  | | | \  / |
  _   | |  / _ \  | '_ ` _ \  | '_ \  | '__| |  _ <  | |  | | | |  | | | |\/| |
 | |__| | | (_) | | | | | | | | |_) | | |    | |_) | | |__| | | |__| | | |  | |
  \____/   \___/  |_| |_| |_| |_.__/  |_|    |____/   \____/   \____/  |_|  |_|
)";



	NEXT_SLIDE  cout << R"(





       _                       _              ____     ____     ____    __  __ 
      | |                     | |            |  _ \   / __ \   / __ \  |  \/  |
      | |   ___    _ __ ___   | |__    _ __  | |_) | | |  | | | |  | | | \  / |
  _   | |  / _ \  | '_ ` _ \  | '_ \  | '__| |  _ <  | |  | | | |  | | | |\/| |
 | |__| | | (_) | | | | | | | | |_) | | |    | |_) | | |__| | | |__| | | |  | |
  \____/   \___/  |_| |_| |_| |_.__/  |_|    |____/   \____/   \____/  |_|  |_|
)";

	colorRESET


		printf("\n\n\n\n\n\n\t\t\t Press [any] key to continue.");

	_getwch();

	return;
}

void Player1_WIN_Animation()
{

	colorBLUE


		for (int i = 0; i < 6; i++)
		{
			NEXT_SLIDE
				cout << R"(
   _______   __         ______   __      __  ________  _______           __ 
  /       \ /  |       /      \ /  \    /  |/        |/       \        _/  | 
  |||||||  ||| |      /||||||  |||  \  /||/ ||||||||/ |||||||  |      / || |
  || |__|| ||| |      || |__|| | ||  \/||/  || |__    || |__|| |      |||| |
  ||    ||/ || |      ||    || |  ||  ||/   ||    |   ||    ||<         || |
  |||||||/  || |      |||||||| |   ||||/    |||||/    |||||||  |        || |
  || |      || |_____ || |  || |    || |    || |_____ || |  || |       _|| |_ 
  || |      ||       ||| |  || |    || |    ||       ||| |  || |      / ||   |
  ||/       ||||||||/ ||/   ||/     ||/     ||||||||/ ||/   ||/       ||||||/
)";
			NEXT_SLIDE

				cout << R"(
   _______   __         ______   __      __  ________  _______           __   
  /       \ /  |       /      \ /  \    /  |/        |/       \        _/  |
  |||||||  ||| |      /||||||  |||  \  /||/ ||||||||/ |||||||  |      / || |
  || |__|| ||| |      || |__|| | ||  \/||/  || |__    || |__|| |      |||| |
  ||    ||/ || |      ||    || |  ||  ||/   ||    |   ||    ||<         || |
  |||||||/  || |      |||||||| |   ||||/    |||||/    |||||||  |        || |
  || |      || |_____ || |  || |    || |    || |_____ || |  || |       _|| |_
  || |      ||       ||| |  || |    || |    ||       ||| |  || |      / ||   |
  ||/       ||||||||/ ||/   ||/     ||/     ||||||||/ ||/   ||/       ||||||/
                                                                
                                                            
                                                           
                 __       __        ______        __    __ 
                /  |  _  /  |      /      |      /  \  /  |
                || | / \ || |      ||||||/       ||  \ || |
                || |/|  \|| |        || |        |||  \|| |
                || /|||  || |        || |        ||||  || |
                || ||/|| || |        || |        || || || |
                ||||/  |||| |       _|| |_       || ||||| |
                |||/    ||| |      / ||   |      || | ||| |
                ||/      ||/       ||||||/       ||/   ||/  )";

		}
	_getwch();
	colorRESET
		return;
}

void Player2_WIN_Animation()
{
	colorBLUE

		for (int i = 0; i < 6; i++)
		{

			NEXT_SLIDE
				cout << R"(
 _______   __         ______  __      __  ________  _______          ______  
|       \ |  \       /      \|  \    /  \|        \|       \        /      \ 
| |||||||\| ||      |  ||||||\\||\  /  ||| ||||||||| |||||||\      |  ||||||\
| ||__/ ||| ||      | ||__| || \||\/  || | ||__    | ||__| ||       \||__| ||
| ||    ||| ||      | ||    ||  \||  ||  | ||  \   | ||    ||       /      ||
| ||||||| | ||      | ||||||||   \||||   | |||||   | |||||||\      |  |||||| 
| ||      | ||_____ | ||  | ||   | ||    | ||_____ | ||  | ||      | ||_____ 
| ||      | ||     \| ||  | ||   | ||    | ||     \| ||  | ||      | ||     \
 \||       \|||||||| \||   \||    \||     \|||||||| \||   \||       \||||||||
)";


			NEXT_SLIDE

				cout << R"(
 _______   __         ______  __      __  ________  _______          ______  
|       \ |  \       /      \|  \    /  \|        \|       \        /      \ 
| |||||||\| ||      |  ||||||\\||\  /  ||| ||||||||| |||||||\      |  ||||||\
| ||__/ ||| ||      | ||__| || \||\/  || | ||__    | ||__| ||       \||__| ||
| ||    ||| ||      | ||    ||  \||  ||  | ||  \   | ||    ||       /      ||
| ||||||| | ||      | ||||||||   \||||   | |||||   | |||||||\      |  |||||| 
| ||      | ||_____ | ||  | ||   | ||    | ||_____ | ||  | ||      | ||_____ 
| ||      | ||     \| ||  | ||   | ||    | ||     \| ||  | ||      | ||     \
 \||       \|||||||| \||   \||    \||     \|||||||| \||   \||       \||||||||
                                                          
                                        
                             
               __       __        ______        __    __                       
              |  \  _  |  \      |      \      |  \  |  \                      
              | || / \ | ||       \||||||      | ||\ | ||                      
              | ||/  |\| ||        | ||        | |||\| ||                      
              | ||  |||\ ||        | ||        | ||||\ ||                      
              | || ||\||\||        | ||        | ||\|| ||                      
              | ||||  \||||       _| ||_       | || \||||                      
              | |||    \|||      |   || \      | ||  \|||                      
               \||      \||       \||||||       \||   \||
)";
		}
	colorRESET
		_getwch();
	return;

}

void TIE_Animation()
{
	for (short i = 0; i < 6; i++)
	{
		if (i % 2 == 0)
			colorBLUE
		else
			colorGREEN

			NEXT_SLIDE

			cout << R"(

	 .----------------.    .----------------.    .----------------. 
	| .--------------. |  | .--------------. |  | .--------------. |
	| |  _________   | |  | |     _____    | |  | |  _________   | |
	| | |  _   _  |  | |  | |    |_   _|   | |  | | |_   ___  |  | |
	| | |_/ | | \_|  | |  | |      | |     | |  | |   | |_  \_|  | |
	| |     | |      | |  | |      | |     | |  | |   |  _|  _   | |
	| |    _| |_     | |  | |     _| |_    | |  | |  _| |___/ |  | |
	| |   |_____|    | |  | |    |_____|   | |  | | |_________|  | |
	| |              | |  | |              | |  | |              | |
	| '--------------' |  | '--------------' |  | '--------------' |
	 '----------------'    '----------------'    '----------------' 
       	)";
	}
	colorRESET
}
//end animation of start and victory screans


// start functions for dev & debag mode***************************************
void o_display_h_coordinates_field()
{
	//this func used by devs. to make sure of correct instalation of objects to selected position on main field  //ALEXEY uses  that positions 
	system("cls");
	for (int h = 0; h < field_height; h++)
	{
		printf("         |");
		for (int w = 0; w < field_width; w++)
		{
			if (Batle_field[h_cors_f][h][w] == 0)
			{
				printf("%c", (char)32);
			}
			else
			{
				printf("%c", '+');
			}
		}
		printf("|         ");
		printf("\n");
	}
	//123456789.123456789.123456789.123456789|123456789.123456789.123456789.123456789.
	printf("                     Back - [P]    X_cors - [X]   ");
	char input_but;
	while (true)
	{
		input_but = _getwch();
		switch (input_but)
		{
		case 'p': case 'P': o_display_batle_field(panel_width, field_height, field_width); return; break;
		case'x': case 'X':	o_display_w_coordinates_field(); return; break;
		default: break;
		}
	}
	return;
}

void o_display_w_coordinates_field()
{
	//this func used by devs. to make sure of correct instalation of objects to selected position on main field  //ALEXEY uses  that positions 

	system("cls");

	for (int h = 0; h < field_height; h++)
	{
		printf("%3d", h);
		printf("      |");
		for (int w = 0; w < field_width; w++)
		{
			if (Batle_field[w_cors_f][h][w] == 0)
			{
				printf("%c", (char)32);
			}
			else if (h == 23)
			{
				printf("%d", w % 10);
			}
			else
			{
				printf("%c", '+');
			}

		}
		printf("|         ");
		printf("\n");
	}

	//123456789.123456789.123456789.123456789.123456789.123456789.123456789.123456789.
	printf("                     Back - [P]    Y_cors - [Y]   ");


	char input_but;
	do
	{
		input_but = _getwch();
		switch (input_but)
		{
		case 'P': case 'p': o_display_batle_field(panel_width, field_height, field_width); o_get_main_screen_actions(); return; break;
		case'y': case 'Y':	o_display_h_coordinates_field(); return;  break;
		default: break;
		}
	} while (input_but != 'p' && input_but != 'P' && input_but != 'y' && input_but != 'Y');

	return;
}

void print_objects_info()
{
	//it used for devs to monitoring of changes in datas of installed/removed objects

	/*    SYMBOLS in players info fields to distinguish objects
		left :			       cost   right:     char value
		  1	 -  Big gun        $600  -  1		   (49)
		  2  -  Small gun      $400  -  2		   (50)
		  3  -	big wall       $200  -  3		   (51)
		  4  -  small wall     $100  -  4		   (52)
		  5  -  gold mine -    $950  -  5		   (53)
		type                           type
	 */


	system("cls");
	printf("Player 1 left: \n");
	for (int h = 0; h < info_h; h++)
	{
		if (h == 0)
		{
			printf(" Type:   ");
		}
		else if (h == 1)
		{
			printf(" Shots:  ");
		}
		else if (h == 2)
		{
			printf(" Route:  ");
		}
		else if (h == 3)
		{
			printf(" Health: ");
		}
		else if (h == 4)
		{
			printf(" Cors Y: ");
		}
		else if (h == 5)
		{
			printf(" Cors X: ");
		}
		for (int w = 0; w < info_w; w++)
		{
			if (Elements_Info_Player_Left[b_type][w] == 0 && Elements_Info_Player_Left[h][w] == 0)
			{
				printf("%3c", '_');
			}
			else
			{
				printf("%3d", Elements_Info_Player_Left[h][w]);
			}
		}
		printf("\n");
	}

	printf("\n");

	printf("Player 2 right: \n");
	for (int h = 0; h < info_h; h++)
	{
		if (h == 0)
		{
			printf(" Type:   ");
		}
		else if (h == 1)
		{
			printf(" Shots:  ");
		}
		else if (h == 2)
		{
			printf(" Route:  ");
		}
		else if (h == 3)
		{
			printf(" Health: ");
		}
		else if (h == 4)
		{
			printf(" Cors Y: ");
		}
		else if (h == 5)
		{
			printf(" Cors X: ");
		}
		for (int w = 0; w < info_w; w++)

			if (Elements_Info_Player_Right[b_type][w] == 0 && Elements_Info_Player_Right[h][w] == 0)
			{
				printf("%3c", '_');
			}
			else
			{
				printf("%3d", Elements_Info_Player_Right[h][w]);
			}
		printf("\n");
	}
	printf("\n\n\n\n\n\n Press [i] to return");

	char movement_to;
	do
	{
		movement_to = _getwch();
		switch (movement_to)
		{
		case 'I':case'i': o_display_batle_field(panel_width, field_height, field_width); o_get_main_screen_actions(); break;

		default: break;
		}
	} while (movement_to != 'i' && movement_to != 'I');

	return;

}
// end functions for dev & debag mode***************************************