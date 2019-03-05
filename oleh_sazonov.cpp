#pragma once
#include "head.h"

//левая и правая панели;
char Left_panel[field_height][panel_width];
char Right_panel[field_height][panel_width];

char Name_P1[name_lenght] = " Jombr";
char Name_P2[name_lenght] = " Boo  ";
int total_money_left = 950;
int total_money_right = 950;

int Batle_field[n_fields][field_height][field_width];  //[0][*][*] - основное поле; [1][*][*] - копия поля для прорисовки поля во время установки обьектов
int Shop_field[field_height][field_width + panel_width + panel_width]; // главный экран магазина

//согласовать вычитание номера обьекта при перемещении данных  ????????????????????????????????????????????????????????????????
int element_number_l = -1; // -1 потому что сразу при входе в функцию делается ++ и для первого раза значение будет 0
int element_number_r = -1;


int Elements_Info_Player_Left[info_h][info_w];
int Elements_Info_Player_Right[info_h][info_w];

//параметры обьектов



char building_type = '1';  // тип здания. инициализируется при выборе в магазине // передается в функцию прорисовки/перемещении обьекта

char player; //('R' - правый игрок player2; 'L' - левый игрок player1)

int *arr = new int[(Building_height*Building_width)];
int Building[Building_height][Building_width];

int current_position_h;
int current_position_w;
int current_pos_extr_w;

int coordinate_h;
int coordinate_w;

void o_fill_batle_field_after_start()
{
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
void o_display_batle_field(int panel_width, int field_height, int field_width)
{
	money_have();
	int turn;
	player == 'L' ? turn = 1 : turn = 2;
	system("cls");
	for (int h = 0; h < field_height; h++) {
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
void o_get_main_screen_actions() // принимает клавиши действий на главном игровом поле
{
	char button;
	do
	{
		/*if (give_money() == true)
		{
			o_display_batle_field(panel_width, field_height, field_width);
		}*/
		button = _getwch();
		switch (button)
		{
		case 'P': case 'p':  o_fill_shop(); o_display_shop(); o_get_shop_actions(); return; break;
		case '-': return;
		case 'Y': case 'y':  o_display_h_coordinates_field();	break;
		case 'X': case 'x':  o_display_w_coordinates_field();	break;
		case 'I': case 'i':  print_objects_info();				break;
		default: break;
		}
	} while (button != 'p' || button != 'P' || button != 'x' || button != 'X' || button != 'Y' || button != 'y' || button != 'i' || button != 'I');

	return;
}
void o_print_copy_batle_field()   //action_in
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

void o_move_elements(char player, char building_type) //action_in
{

	int temp_value;

	if (player == 'L')
	{
		current_position_h = 9;
		current_position_w = 0;
	}
	else if (player == 'R')
	{
		current_position_h = 9;
		current_position_w = 56;
	}

	system("cls");

	o_print_copy_batle_field();


	char movement_to = 'X';
	while (movement_to != '9' || movement_to != '0')
	{
		/*
		if (give_money() == true)
		{
			money_have();
			current_position_h++;	o_move_up(player, building_type);
		}*/

		switch (movement_to)
		{
		case '>': o_move_elements('R', building_type);  break;
		case '<': o_move_elements('L', building_type);  break;
		case 'X': o_get_field_copy(); current_position_h++;	o_move_up(player, building_type); break;
		case 'w': case 'W': o_get_field_copy(); o_move_up(player, building_type);		break;
		case 's': case 'S': o_get_field_copy(); o_move_down(player, building_type); break;
		case 'a': case 'A': o_get_field_copy(); o_move_left(player, building_type);		break;
		case 'd': case 'D': o_get_field_copy(); o_move_right(player, building_type);	break;
		case '9':
			if (o_check_free_zone(current_position_h, current_position_w, building_type) == true)
			{
				temp_value = o_calculate_money(player, building_type);
				if (temp_value == -1)
				{
					o_get_field_copy();
					o_print_copy_batle_field();
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
			building_type++; building_type == '6' ? building_type = '1' : building_type;
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
	arr = o_building_select(player, building_type);

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
				coordinate_h = current_position_h;  //принимаем координаты для записи положения обьектов в координатый массив
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
	o_print_copy_batle_field();  //вызываем прорисовку временной копии основоного поля
	return;
}
void o_move_down(char player, char building_type)
{
	arr = o_building_select(player, building_type);

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
			if (current_position_h < field_height - 3)
			{
				current_position_h++;
				coordinate_h = current_position_h; //принимаем координаты для записи положения обьектов в координатый массив
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
	o_print_copy_batle_field();

	return;
}

void o_move_left(char player, char building_type)
{
	player == 'L' ? current_pos_extr_w = 1 : current_pos_extr_w = 30;
	arr = o_building_select(player, building_type);

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
			if (current_position_w > current_pos_extr_w)
			{
				current_position_w--;
				coordinate_w = current_position_w; //принимаем координаты для записи положения обьектов в координатый массив
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
	o_print_copy_batle_field();
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
				current_position_w--;
				o_move_right(player, building_type);
			}
		}
	}
	system("cls");
	o_print_copy_batle_field();

	return;
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

void o_buy_item(char player, char building_type)
{
	int *item = o_building_select(player, building_type);

	for (int h = 0, i = 0; h < Building_height; h++)
	{
		for (int w = 0; w < Building_width; w++, i++)
		{
			Batle_field[main_f][current_position_h+h][current_position_w+w] = *(item + i);
		}
	}
	o_put_coordinates(player, building_type, coordinate_h, coordinate_w);
	o_write_info_about_player_odject(player, building_type, coordinate_h, coordinate_w);
	return;
}

int *o_building_select(char player, char building_type) //переключает здание в заисимости от юзера и типа выбранного здания
{
	int *building = new int[(Building_height*Building_width)];

	switch (player)
	{
	case 'L':
		if (building_type == '1')
		{
			int Gun1[(Building_height*Building_width)] = { 178,178,178,178,204,205,178,178,178 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Gun1[i];
			}
			return building;
		}
		else if (building_type == '2')
		{
			int Gun_cheap1[(Building_height*Building_width)] = { 176,176,176,176,199,196,176,176,176 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Gun_cheap1[i];
			}
			return building;
		}
		else if (building_type == '3')
		{
			int Wall1[Building_height*Building_width] = { 32,178,32,32,178,32,32,178,32 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Wall1[i];
			}
			return building;
		}
		else if (building_type == '4')
		{
			int Wall_cheap1[Building_height*Building_width] = { 32,177,32,32,177,32,32,177,32 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Wall_cheap1[i];
			}
			return building;
		}
		else if (building_type == '5')
		{
			int Goldmine[Building_height*Building_width] = { 201, 205, 187, 186, 36, 186, 200, 205, 188 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Goldmine[i];
			}
			return building;
		}

	case 'R':
		if (building_type == '1')
		{
			int Gun2[Building_height*Building_width] = { 178,178,178,205,185,178,178,178,178 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Gun2[i];
			}
			return building;
		}
		else if (building_type == '2')
		{
			int Gun_cheap2[Building_height*Building_width] = { 176,176,176,196,182,176,176,176,176 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Gun_cheap2[i];
			}
			return building;
		}
		else if (building_type == '3')
		{
			int Wall2[Building_height*Building_width] = { 32,178,32,32,178,32,32,178,32 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Wall2[i];
			}
			return building;
		}
		else if (building_type == '4')
		{
			int Wall_cheap2[Building_height*Building_width] = { 32,177,32,32,177,32,32,177,32 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Wall_cheap2[i];
			}
			return building;
		}
		else if (building_type == '5')
		{
			int Goldmine[Building_height*Building_width] = { 201, 205, 187, 186, 36, 186, 200, 205, 188 };
			for (int i = 0; i < (Building_height*Building_width); i++)
			{
				building[i] = Goldmine[i];
			}
			return building;
		}
		break;

	default:
		break;
	}
	return 0;
}

void o_fill_shop()
{
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

int o_display_shop()
{
	o_display_marker_in_store(building_type);
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
	char item_5_money[] = "+150 ";

	char str_Items[] = "       ";
	char str_Select[] = "       ";
	char str_Price[] = "Price: ";
	char str_Health[] = "Health: ";
	char str_Shots[] = "Shots: ";
	char str_Money[] = "Money+:";


	int h0 = 7, w0 = 26, w1 = w0;  //стартовые позиции для отрисовки обьектов в магазине
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
	w0 = w0 + 7;
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
	w0 = w0 + 7;
	Shop_field[h0 + 0][w0 + 0] = 32; Shop_field[h0 + 0][w0 + 1] = 178; Shop_field[h0 + 0][w0 + 2] = 32;
	Shop_field[h0 + 1][w0 + 0] = 32; Shop_field[h0 + 1][w0 + 1] = 178; Shop_field[h0 + 1][w0 + 2] = 32;
	Shop_field[h0 + 2][w0 + 0] = 32; Shop_field[h0 + 2][w0 + 1] = 178; Shop_field[h0 + 2][w0 + 2] = 32;
	w0 = w0 + 7;
	Shop_field[h0 + 0][w0 + 0] = 32; Shop_field[h0 + 0][w0 + 1] = 177; Shop_field[h0 + 0][w0 + 2] = 32;
	Shop_field[h0 + 1][w0 + 0] = 32; Shop_field[h0 + 1][w0 + 1] = 177; Shop_field[h0 + 1][w0 + 2] = 32;
	Shop_field[h0 + 2][w0 + 0] = 32; Shop_field[h0 + 2][w0 + 1] = 177; Shop_field[h0 + 2][w0 + 2] = 32;
	w0 = w0 + 7;
	Shop_field[h0 + 0][w0 + 0] = 201; Shop_field[h0 + 0][w0 + 1] = 205; Shop_field[h0 + 0][w0 + 2] = 187;
	Shop_field[h0 + 1][w0 + 0] = 186; Shop_field[h0 + 1][w0 + 1] = 36; Shop_field[h0 + 1][w0 + 2] = 186;
	Shop_field[h0 + 2][w0 + 0] = 200; Shop_field[h0 + 2][w0 + 1] = 205; Shop_field[h0 + 2][w0 + 2] = 188;

	Shop_field[h0 + 4][w1 + 1] = 49;  Shop_field[h0 + 4][w1 + 8] = 50; Shop_field[h0 + 4][w1 + 15] = 51; Shop_field[h0 + 4][w1 + 22] = 52; Shop_field[h0 + 4][w1 + 29] = 53;
	int h_items = 1; int h_select = 4;
	int h_price = 6; int h_health = 8; int h_shots = 9; int h_money = 10;
	int w_item1 = 0; int w_item2 = 7; int w_item3 = 14; int w_item4 = 21; int w_item5 = 28;
	for (int i = 0; i < 4; i++)
	{
		Shop_field[h0 + h_price][w1 + w_item1 + i] = item_1_price[i];
		Shop_field[h0 + h_price][w1 + w_item2 + +i] = item_2_price[i];
		Shop_field[h0 + h_price][w1 + w_item3 + i] = item_3_price[i];
		Shop_field[h0 + h_price][w1 + w_item4 + i] = item_4_price[i];
		Shop_field[h0 + h_price][w1 + w_item5 + i] = item_5_price[i];
	}

	for (int i = 0; i < 4; i++)
	{
		Shop_field[h0 + h_health][w1 + w_item1 + i] = item_1_health[i];
		Shop_field[h0 + h_health][w1 + w_item2 + i] = item_2_health[i];
		Shop_field[h0 + h_health][w1 + w_item3 + i] = item_3_health[i];
		Shop_field[h0 + h_health][w1 + w_item4 + i] = item_4_health[i];
		Shop_field[h0 + h_health][w1 + w_item5 + i] = item_5_health[i];

	}
	for (int i = 0; i < 4; i++)
	{
		Shop_field[h0 + h_shots][w1 + w_item1 + i] = item_1_shots[i];
		Shop_field[h0 + h_shots][w1 + w_item2 + i] = item_2_shots[i];
		Shop_field[h0 + h_shots][w1 + w_item3 + i] = item_3_shots[i];
		Shop_field[h0 + h_shots][w1 + w_item4 + i] = item_4_shots[i];
		Shop_field[h0 + h_shots][w1 + w_item5 + i] = item_5_shots[i];

	}
	for (int i = 0; i < 4; i++)
	{
		Shop_field[h0 + h_money][w1 + w_item1 + i] = item_1_money[i];
		Shop_field[h0 + h_money][w1 + w_item2 + i] = item_2_money[i];
		Shop_field[h0 + h_money][w1 + w_item3 + i] = item_3_money[i];
		Shop_field[h0 + h_money][w1 + w_item4 + i] = item_4_money[i];
		Shop_field[h0 + h_money][w1 + w_item5 + i] = item_5_money[i];

	}

	int w0_inscr = 15;

	for (int i = 0; i < 7; i++)
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
		for (int w = 0; w < (field_width + (panel_width * 2)); w++)
		{
			printf("%c", (char)Shop_field[h][w]);
		}
		printf("\n");
	}
	printf("\t\t Select: [1-4]  [9] \t Next: [N]\tBack: [P] ");

	return 0;
}

void o_display_marker_in_store(char building_type)
{
	int h = 11; int w0 = 26;
	int w11 = w0 + 0; int w12 = w0 + 2;
	int w21 = w0 + 7; int w22 = w0 + 9;
	int w31 = w0 + 14; int w32 = w0 + 16;
	int w41 = w0 + 21; int w42 = w0 + 23;
	int w51 = w0 + 28; int w52 = w0 + 30;

	building_type == NULL ? building_type = '1' : building_type;

	Shop_field[h][w11] = ' '; Shop_field[h][w12] = ' ';
	Shop_field[h][w21] = ' '; Shop_field[h][w22] = ' ';
	Shop_field[h][w31] = ' '; Shop_field[h][w32] = ' ';
	Shop_field[h][w41] = ' '; Shop_field[h][w42] = ' ';
	Shop_field[h][w51] = ' '; Shop_field[h][w52] = ' ';
	if (building_type == '1')
	{
		Shop_field[h][w11] = '{'; Shop_field[h][w12] = '}';
	}
	else if (building_type == '2')
	{
		Shop_field[h][w21] = '{'; Shop_field[h][w22] = '}';
	}
	else if (building_type == '3')
	{
		Shop_field[h][w31] = '{'; Shop_field[h][w32] = '}';
	}
	else if (building_type == '4')
	{
		Shop_field[h][w41] = '{'; Shop_field[h][w42] = '}';
	}
	else if (building_type == '5')
	{
		Shop_field[h][w51] = '{'; Shop_field[h][w52] = '}';
	}
	return;
}

void o_display_h_coordinates_field()
{
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
		case '0': o_display_batle_field(panel_width, field_height, field_width);  break;
		case'x': case 'X':	o_display_w_coordinates_field(); break;
		default: break;
		}
	}
	return;
}

void o_display_w_coordinates_field()
{
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
		case 'P': case 'p': o_display_batle_field(panel_width, field_height, field_width); o_get_main_screen_actions(); break;
		case'y': case 'Y':	o_display_h_coordinates_field(); break;
		default: break;
		}
	} while (input_but != 'p' && input_but != 'P' && input_but != 'y' && input_but != 'Y');

	return;
}

void o_put_coordinates(char player, char building_type, int coordinate_h, int coordinate_w)
{

	if (building_type == '1' || building_type == '2' || building_type == '5')
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
	else if (building_type == '3' || building_type == '4')
	{
		for (int h = 0; h < Building_height; h++)
		{
			for (int w = 0; w < Building_width; w++)
			{
				if (w == 1)
				{
					Batle_field[h_cors_f][coordinate_h + h][coordinate_w + w] = coordinate_h + 1;
					Batle_field[w_cors_f][coordinate_h + h][coordinate_w + w] = coordinate_w + 1;
				}
			}
		}
	}

	return;
}

void o_write_info_about_player_odject(char player, char building_type, int coordinate_h, int coordinate_w)
{
	coordinate_h = coordinate_h + 1;
	coordinate_w = coordinate_w + 1;

	if (player == 'L')
	{
		element_number_l++;                // если убит обьект минусовать нужно
		Elements_Info_Player_Left[b_type][element_number_l] = building_type;

		if (building_type == '1')
		{
			Elements_Info_Player_Left[shots][element_number_l] = shots_1;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_l;
			Elements_Info_Player_Left[HP][element_number_l] = HP_1;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
		else if (building_type == '2')
		{
			Elements_Info_Player_Left[shots][element_number_l] = shots_2;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_l;
			Elements_Info_Player_Left[HP][element_number_l] = HP_2;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
		else if (building_type == '3')
		{
			Elements_Info_Player_Left[shots][element_number_l] = shots_3;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_3;
			Elements_Info_Player_Left[HP][element_number_l] = HP_3;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
		else if (building_type == '4')
		{
			Elements_Info_Player_Left[shots][element_number_l] = shots_4;
			Elements_Info_Player_Left[sh_route][element_number_l] = sh_route_4;
			Elements_Info_Player_Left[HP][element_number_l] = HP_4;
			Elements_Info_Player_Left[h_cor][element_number_l] = coordinate_h;
			Elements_Info_Player_Left[w_cor][element_number_l] = coordinate_w;
		}
		else if (building_type == '5')
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

		if (building_type == '1')
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_1;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_r;
			Elements_Info_Player_Right[HP][element_number_r] = HP_1;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
		else if (building_type == '2')
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_2;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_r;
			Elements_Info_Player_Right[HP][element_number_r] = HP_2;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
		else if (building_type == '3')
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_3;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_3;
			Elements_Info_Player_Right[HP][element_number_r] = HP_3;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
		else if (building_type == '4')
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_4;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_4;
			Elements_Info_Player_Right[HP][element_number_r] = HP_4;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
		else if (building_type == '5')
		{
			Elements_Info_Player_Right[shots][element_number_r] = shots_5;
			Elements_Info_Player_Right[sh_route][element_number_r] = sh_route_5;
			Elements_Info_Player_Right[HP][element_number_r] = HP_5;
			Elements_Info_Player_Right[h_cor][element_number_r] = coordinate_h;
			Elements_Info_Player_Right[w_cor][element_number_r] = coordinate_w;
		}
	}

	return;
}

void print_objects_info()
{
	/*    Cимволы в информационном поле обьектов для игрока
		Слева :						  Справа:
		  1	 - большая пушка за $600 -   1   (49)
		  2  -  малая пушка за $400  -   2   (50)
		  3  - большая стена за $200  -  3   (51)
		  4  -  малая  стена за $100  -  4   (52)
		  5  - золотая шахта - 5        (53)
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

void o_get_shop_actions() // принимает клавиши действий в магазине
{
	char action_in_shop;
	do
	{
		action_in_shop = _getwch();
		switch (action_in_shop)
		{
		case '<': player = 'L';  o_display_shop(); break;  //для переключения игрока в магазине  используй (Shift + <) меняет на левого   (фича для тестов)
		case '>': player = 'R';  o_display_shop(); break;  //для переключения игрока в магазине  используй (Shift + >) меняет на правого  (фича для тестов)
		case '1': building_type = '1'; o_move_elements(player, building_type);  break;
		case '2': building_type = '2'; o_move_elements(player, building_type);  break;
		case '3': building_type = '3'; o_move_elements(player, building_type);  break;
		case '4': building_type = '4'; o_move_elements(player, building_type);  break;
		case '5': building_type = '5'; o_move_elements(player, building_type);  break;
		case 'N': case'n':  building_type++; building_type == '6' ? building_type = '1' : building_type; o_display_shop();   break;
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
	} while (action_in_shop != '9' && action_in_shop != 'p' && action_in_shop != '4' && action_in_shop != '5' && action_in_shop != 'P' && action_in_shop != '1' && action_in_shop != '2' && action_in_shop != '3');

	return;
}

void o_fill_pannels()
{
	const int name_size = 8;
	char Player_1_name[name_size] = "Player1";
	char Player_2_name[name_size] = "Player2";

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
		Left_panel[3][w] = '-';
		Right_panel[3][w + 1] = '-';
		Left_panel[8][w] = '-';
		Right_panel[8][w + 1] = '-';
		Left_panel[23][w] = 196;
		Right_panel[23][w + 1] = 196;

	}
	Left_panel[23][9] = 217;
	Right_panel[23][0] = 192;

	Left_panel[6][2] = '$';
	Right_panel[6][3] = '$';

	const int money_lenght = 7;
	char coins[money_lenght] = "Money:";
	for (int w = 0; w < money_lenght; w++)
	{
		Left_panel[5][w + 1] = coins[w];
		Right_panel[5][w + 2] = coins[w];
	}
	money_have();
	return;
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

int o_item_price(char building_type)
{
	int item_price;

	if (building_type == '1')
	{
		item_price = gun_1_price;
	}
	else if (building_type == '2')
	{
		item_price = gun_2_price;
	}
	else if (building_type == '3')
	{
		item_price = wall_1_price;
	}
	else if (building_type == '4')
	{
		item_price = wall_2_price;
	}
	else if (building_type == '5')
	{
		item_price = goldmine_price;
	}

	return item_price;
}

void money_have()
{
	char L1; char L2; char L3; char L4;
	char R1; char R2; char R3; char R4;
	int n1 = 0; int n2 = 0; int n3 = 0; int n4 = 0;
	int r1 = 0; int r2 = 0; int r3 = 0; int r4 = 0;

	if (total_money_left < 9999)
	{
		n1 = (total_money_left / 1000);
		n2 = (total_money_left - n1 * 1000) / 100;
		n3 = (total_money_left - n1 * 1000 - n2 * 100) / 10;
		n4 = (total_money_left - n1 * 1000 - n2 * 100 - n3 * 10);
		Left_panel[6][7] = ' ';
		L1 = 48 + n4;	 L2 = 48 + n3;	L3 = 48 + n2;	L4 = 48 + n1;
	}
	else
	{
		L1 = '9'; L2 = '9'; L3 = '9'; L4 = '9';
		Left_panel[6][7] = '+';
	}

	if (total_money_right < 9999)
	{
		r1 = (total_money_right / 1000);
		r2 = (total_money_right - r1 * 1000) / 100;
		r3 = (total_money_right - r1 * 1000 - r2 * 100) / 10;
		r4 = (total_money_right - r1 * 1000 - r2 * 100 - r3 * 10);
		Right_panel[6][8] = ' ';
		R1 = 48 + r4; 	 R2 = 48 + r3;  R3 = 48 + r2; 	R4 = 48 + r1;

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

bool o_check_free_zone(int current_position_h, int current_position_w, char building_type)
{

	if (Batle_field[main_f][current_position_h + 0][current_position_w] != 32 || Batle_field[main_f][current_position_h + 0][current_position_w + 1] != 32 || Batle_field[main_f][current_position_h + 0][current_position_w + 2] != 32
		|| Batle_field[main_f][current_position_h + 1][current_position_w] != 32 || Batle_field[main_f][current_position_h + 1][current_position_w + 1] != 32 || Batle_field[main_f][current_position_h + 1][current_position_w + 2] != 32
		|| Batle_field[main_f][current_position_h + 2][current_position_w] != 32 || Batle_field[main_f][current_position_h + 2][current_position_w + 1] != 32 || Batle_field[main_f][current_position_h + 2][current_position_w + 2] != 32)
	{
		printf("\a\r                           Zone is already taken                           ");
		Sleep(1500);
		return false;
	}
	else if (building_type == '1' || building_type == '2' || building_type == '5')
	{
		if (
			Batle_field[main_f][current_position_h - 1][current_position_w] != 32 || Batle_field[main_f][current_position_h - 1][current_position_w + 1] != 32 || Batle_field[main_f][current_position_h - 1][current_position_w + 2] != 32         //top
			|| Batle_field[main_f][current_position_h + 3][current_position_w] != 32 || Batle_field[main_f][current_position_h + 3][current_position_w + 1] != 32 || Batle_field[main_f][current_position_h + 3][current_position_w + 2] != 32    //bottom
			|| Batle_field[main_f][current_position_h + 0][current_position_w - 1] != 32 || Batle_field[main_f][current_position_h + 1][current_position_w - 1] != 32 || Batle_field[main_f][current_position_h + 2][current_position_w - 1] != 32 //left
			|| Batle_field[main_f][current_position_h + 0][current_position_w + 3] != 32 || Batle_field[main_f][current_position_h + 1][current_position_w + 3] != 32 || Batle_field[main_f][current_position_h + 2][current_position_w + 3] != 32 //right
			)
		{
			printf("\a\r                      Too close. You can not build here                      ");
			Sleep(1500);
			return false;
		}

	}
	else if (building_type == '3' || building_type == '4')
	{
		if (
			Batle_field[main_f][current_position_h - 1][current_position_w + 1] != 32        //top
			|| Batle_field[main_f][current_position_h + 3][current_position_w + 1] != 32    //bottom
			)
		{
			printf("\a\r                      Too close. You can not build here                      ");
			Sleep(1500);
			return false;
		}

	}
	return true;
}

void give_item_on_start(char player, char building_type, int centre_h, int centre_w)
{
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

void start_items_list()
{
	//give_item_on_start(char player, char building_type, int centre_h, int centre_w)
	// границы полей; 
	// player 'L'     ↑  1                     // player 'R'     ↑  1         
	//            1 <   > 27                   //           31 <   > 57
	//                ↓  22                   //     		     ↓  22


	give_item_on_start('L', '5', 4, 2);
	give_item_on_start('L', '5', 18, 2);

	give_item_on_start('R', '5', 4, 56);
	give_item_on_start('R', '5', 18, 56);



	return;
}