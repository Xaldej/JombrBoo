/*JoombrBoo
authours:
alexey melentyev
oleg sazonov
date: 10.12
*/
#include "head.h"

int main()
{
	//player = 'R';

	o_fill_batle_field_after_start();
	o_display_batle_field(panel_width, field_height, field_width);


	return 0;
}




void o_fill_batle_field_after_start()
{
	for (int h = 0; h < panel_height; h++)
	{
		for (int w = 0; w < panel_width; w++)
		{
			Left_panel[h][w] = char(177);
		}
	}

	for (int h = 0; h < field_height; h++)
	{
		for (int w = 0; w < field_width; w++)
		{
			if (w == 29)
			{
				Batle_field[main_f][h][w] = '|';
				Batle_field[copy_f][h][w] = '|';
			}
			else
				Batle_field[main_f][h][w] = ' ';
		}
	}

	for (int h = 0; h < panel_height; h++) {
		for (int w = 0; w < panel_width; w++)
		{
			Right_panel[h][w] = char(176);
		}

	}
	return;
}
void o_display_batle_field(int panel_width, int field_height, int field_width)
{
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
	printf("                                 Open Shop: [P];");
	o_get_main_screen_actions();
	return;
}
void o_get_main_screen_actions() // принимает клавиши действий на главном игровом поле
{
	char button;
	while (true)
	{
		button = _getwch();
		switch (button)
		{
		case 'P': case 'p':  case '«':  case 'з':  o_fill_shop(); o_display_shop();  break;
		case 'C': case 'c': case '—': case 'с': o_display_coordinates_field(); break;
		default: break;
		}
	}

	return;
}
void o_print_copy_batle_field()
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
	printf("       Move: [W, A, S, D]       Buy: [9];  Shop: [P];  Cancel [0]; ");
	return;
}

void o_move_elements(char player, char building_type)
{
	if (player == 'L')
	{
		current_position_h = 0;
		current_position_w = 1;
	}
	else if (player == 'R')
	{
		current_position_h = 0;
		current_position_w = 30;
	}

	system("cls");
	o_print_copy_batle_field();
	char movement_to = 'X';
	while (true)
	{

		switch (movement_to)
		{
		case 'w': case 'W': case 'ц': case '÷':			o_get_field_copy(); o_move_up(player, building_type);		break;
		case 's': case 'S': case 'ы': case 'џ': case 'X':		o_get_field_copy(); o_move_down(player, building_type);		break;
		case 'a': case 'A': case 'ф': case '‘':			o_get_field_copy(); o_move_left(player, building_type);		break;
		case 'd': case 'D': case 'в': case '¬':			o_get_field_copy(); o_move_right(player, building_type);	break;
		case 'p': case 'P': case 'з': case '«':			o_fill_shop(); o_display_shop(); break;
		case '9':		o_put_coordinates(player, building_type, coordinate_h, coordinate_w); o_push_batle_field_from_copy();  break;  //после нажати€ на 9 записываем данные с экрана в основной массив;
		case '0': o_display_batle_field(panel_width, field_height, field_width);		 break;
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
				coordinate_h = current_position_h;  //принимаем координаты дл€ записи положени€ обьектов в координатый массив
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
	o_print_copy_batle_field();  //вызываем прорисовку временной копии основоного пол€
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
				coordinate_h = current_position_h; //принимаем координаты дл€ записи положени€ обьектов в координатый массив
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
				coordinate_w = current_position_w; //принимаем координаты дл€ записи положени€ обьектов в координатый массив
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
				coordinate_w = current_position_w; //принимаем координаты дл€ записи положени€ обьектов в координатый массив
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

void o_push_batle_field_from_copy()
{
	for (int h = 0; h < field_height; h++)
	{
		for (int w = 0; w < field_width; w++)
		{
			Batle_field[main_f][h][w] = Batle_field[copy_f][h][w];
		}
	}
	return;
}


int *o_building_select(char player, char building_type) //переключает здание в заисимости от юзера и типа выбранного здани€
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
		break;

	default:
		break;
	}
	return 0;
}

int o_display_shop()
{
	system("cls");
	char item_1_price[] = "$600";
	char item_2_price[] = "$400";
	char item_3_price[] = "$200";
	char item_4_price[] = "$100";

	char str_Items[] = "Items: ";
	char str_Price[] = "Price: ";
	char str_Select[] = "Select:";

	int h0 = 8, w0 = 30, w1 = w0;  //стартовые позиции дл€ отрисовки обьектов в магазине
	Shop_field[h0 + 0][w0 + 0] = 178; Shop_field[h0 + 0][w0 + 1] = 178; Shop_field[h0 + 0][w0 + 2] = 178;
	Shop_field[h0 + 1][w0 + 0] = 178; Shop_field[h0 + 1][w0 + 1] = 204; Shop_field[h0 + 1][w0 + 2] = 205;
	Shop_field[h0 + 2][w0 + 0] = 178; Shop_field[h0 + 2][w0 + 1] = 178; Shop_field[h0 + 2][w0 + 2] = 178;
	w0 = w0 + 7;
	Shop_field[h0 + 0][w0 + 0] = 176; Shop_field[h0 + 0][w0 + 1] = 176; Shop_field[h0 + 0][w0 + 2] = 176;
	Shop_field[h0 + 1][w0 + 0] = 176; Shop_field[h0 + 1][w0 + 1] = 199; Shop_field[h0 + 1][w0 + 2] = 196;
	Shop_field[h0 + 2][w0 + 0] = 176; Shop_field[h0 + 2][w0 + 1] = 176; Shop_field[h0 + 2][w0 + 2] = 176;
	w0 = w0 + 7;
	Shop_field[h0 + 0][w0 + 0] = 32; Shop_field[h0 + 0][w0 + 1] = 178; Shop_field[h0 + 0][w0 + 2] = 32;
	Shop_field[h0 + 1][w0 + 0] = 32; Shop_field[h0 + 1][w0 + 1] = 178; Shop_field[h0 + 1][w0 + 2] = 32;
	Shop_field[h0 + 2][w0 + 0] = 32; Shop_field[h0 + 2][w0 + 1] = 178; Shop_field[h0 + 2][w0 + 2] = 32;
	w0 = w0 + 7;
	Shop_field[h0 + 0][w0 + 0] = 32; Shop_field[h0 + 0][w0 + 1] = 177; Shop_field[h0 + 0][w0 + 2] = 32;
	Shop_field[h0 + 1][w0 + 0] = 32; Shop_field[h0 + 1][w0 + 1] = 177; Shop_field[h0 + 1][w0 + 2] = 32;
	Shop_field[h0 + 2][w0 + 0] = 32; Shop_field[h0 + 2][w0 + 1] = 177; Shop_field[h0 + 2][w0 + 2] = 32;

	Shop_field[h0 + 4][w1 + 1] = 49;  Shop_field[h0 + 4][w1 + 8] = 50; Shop_field[h0 + 4][w1 + 15] = 51; Shop_field[h0 + 4][w1 + 22] = 52;

	for (int i = 0; i < 4; i++)
	{
		Shop_field[h0 + 6][w1 + i] = item_1_price[i];
		Shop_field[h0 + 6][w1 + 7 + i] = item_2_price[i];
		Shop_field[h0 + 6][w1 + 14 + i] = item_3_price[i];
		Shop_field[h0 + 6][w1 + 21 + i] = item_4_price[i];
	}


	int w0_inscr = 15;

	for (int i = 0; i < 7; i++)
	{
		Shop_field[h0 + 1][w0_inscr + i] = str_Items[i];
		Shop_field[h0 + 4][w0_inscr + i] = str_Select[i];
		Shop_field[h0 + 6][w0_inscr + i] = str_Price[i];
	}


	for (int h = 0; h < field_height; h++)
	{
		for (int w = 0; w < (field_width + (panel_width * 2)); w++)
		{
			printf("%c", (char)Shop_field[h][w]);
		}
		printf("\n");
	}
	printf("          Select building: [1-4];       Confirm: [9];    Cancel: [0]; ");
	o_get_shop_actions();
	return 0;
}

void o_get_shop_actions() // принимает клавиши действий в магазине
{
	char action_in_shop;
	while (true)
	{
		action_in_shop = _getwch();
		switch (action_in_shop)
		{
		case '<': player = 'L'; break;  //дл€ переключени€ игрока в магазине  используй (Shift + <) мен€ет на левого   (фича дл€ тестов)
		case '>': player = 'R'; break;  //дл€ переключени€ игрока в магазине  используй (Shift + >) мен€ет на правого  (фича дл€ тестов)
		case '1': building_type = '1'; o_display_marker_in_store(building_type); break;
		case '2': building_type = '2'; o_display_marker_in_store(building_type); break;
		case '3': building_type = '3'; o_display_marker_in_store(building_type); break;
		case '4': building_type = '4'; o_display_marker_in_store(building_type); break;
		case '9': o_move_elements(player, building_type); break;
		case '0': o_display_batle_field(panel_width, field_height, field_width);	break;
		default: break;
		}
	}

	return;
}

void o_display_marker_in_store(char building_type)
{
	if (building_type == '1')
	{
		Shop_field[12][30] = '{'; Shop_field[12][32] = '}';
		Shop_field[12][37] = ' '; Shop_field[12][39] = ' ';
		Shop_field[12][44] = ' '; Shop_field[12][46] = ' ';
		Shop_field[12][51] = ' '; Shop_field[12][53] = ' ';
	}
	else if (building_type == '2')
	{
		Shop_field[12][30] = ' '; Shop_field[12][32] = ' ';
		Shop_field[12][37] = '{'; Shop_field[12][39] = '}';
		Shop_field[12][44] = ' '; Shop_field[12][46] = ' ';
		Shop_field[12][51] = ' '; Shop_field[12][53] = ' ';
	}
	else if (building_type == '3')
	{
		Shop_field[12][30] = ' '; Shop_field[12][32] = ' ';
		Shop_field[12][37] = ' '; Shop_field[12][39] = ' ';
		Shop_field[12][44] = '{'; Shop_field[12][46] = '}';
		Shop_field[12][51] = ' '; Shop_field[12][53] = ' ';
	}
	else if (building_type == '4')
	{
		Shop_field[12][30] = ' '; Shop_field[12][32] = ' ';
		Shop_field[12][37] = ' '; Shop_field[12][39] = ' ';
		Shop_field[12][44] = ' '; Shop_field[12][46] = ' ';
		Shop_field[12][51] = '{'; Shop_field[12][53] = '}';
	}


	o_display_shop();
	return;
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
/*    Cимволы в координатном поле обьектов дл€ игрока
		—лева :						  —права:
		  G	 - больша€ пушка за $600 -   P
		  g  -  мала€ пушка за $400  -   p
		  W  - больша€ стена за $200  -  V
		  w  -  мала€  стена за $100  -  v
*/
void o_put_coordinates(char player, char building_type, int coordinate_h, int coordinate_w)
{
	if (player == 'L')
	{
		if (building_type == '1')
		{
			for (int h = 0; h < Building_height; h++)
			{
				for (int w = 0; w < Building_width; w++)
				{
					Batle_field[cors_f][coordinate_h + h][coordinate_w + w] = 'G';
				}
			}
		}
		else if (building_type == '2')
		{
			for (int h = 0; h < Building_height; h++)
			{
				for (int w = 0; w < Building_width; w++)
				{
					Batle_field[cors_f][coordinate_h + h][coordinate_w + w] = 'g';
				}
			}
		}
		else if (building_type == '3')
		{
			for (int h = 0; h < Building_height; h++)
			{
				for (int w = 0; w < Building_width; w++)
				{
					if (w == 1)
						Batle_field[cors_f][coordinate_h + h][coordinate_w + w] = 'W';
				}
			}
		}
		else if (building_type == '4')
		{
			for (int h = 0; h < Building_height; h++)
			{
				for (int w = 0; w < Building_width; w++)
				{
					if (w == 1)
						Batle_field[cors_f][coordinate_h + h][coordinate_w + w] = 'w';
				}
			}
		}
	}

	else if (player == 'R')
	{
		if (building_type == '1')
		{
			for (int h = 0; h < Building_height; h++)
			{
				for (int w = 0; w < Building_width; w++)
				{

					Batle_field[cors_f][coordinate_h + h][coordinate_w + w] = 'P';
				}
			}
		}
		else if (building_type == '2')
		{
			for (int h = 0; h < Building_height; h++)
			{
				for (int w = 0; w < Building_width; w++)
				{

					Batle_field[cors_f][coordinate_h + h][coordinate_w + w] = 'p';
				}
			}
		}
		else if (building_type == '3')
		{
			for (int h = 0; h < Building_height; h++)
			{
				for (int w = 0; w < Building_width; w++)
				{
					if (w == 1)
						Batle_field[cors_f][coordinate_h + h][coordinate_w + w] = 'S';
				}
			}
		}
		else if (building_type == '4')
		{
			for (int h = 0; h < Building_height; h++)
			{
				for (int w = 0; w < Building_width; w++)
				{
					if (w == 1)
						Batle_field[cors_f][coordinate_h + h][coordinate_w + w] = 's';
				}
			}
		}
	}

	return;
}

void o_display_coordinates_field()
{
	system("cls");
	for (int h = 0; h < field_height; h++) {
		for (int lp = 0; lp < panel_width; lp++)
		{
			printf("%c", Left_panel[h][lp]);
		}

		for (int w = 0; w < field_width; w++)
		{
			printf("%c", (char)Batle_field[cors_f][h][w]);
		}

		for (int rp = 0; rp < panel_width; rp++)
		{
			printf("%c", Right_panel[h][rp]);
		}
		printf("\n");
	}
	//123456789.123456789.123456789.123456789.123456789.123456789.123456789.123456789.
	printf("                     Back to main field:   [0]     ");


	char input_but;
	while (true)
	{
		input_but = _getwch();
		switch (input_but)
		{
		case '0': o_display_batle_field(panel_width, field_height, field_width);  break;

		default: break;
		}
	}

	return;
}


