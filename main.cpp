#include "head.h"



//ok
int main()
{
	system("mode CON: lines=25 cols=79"); //to make sure that console has right size
	Start_Screen_Animation();
	o_fill_batle_field_after_start();
	o_fill_pannels();
	start_items_list();
	play();

	return 0;
}

void play()
{
	do
	{

		//player 1 (L) turn

		player = 'L';
		o_display_batle_field(panel_width, field_height, field_width);
		o_get_main_screen_actions();

		//player 2 (R) turn


		player = 'R';
		o_display_batle_field(panel_width, field_height, field_width);
		o_get_main_screen_actions();

		//counting of shots movement, damage, etc
		MovementMechanichs(Player_1_Data, Player_2_Data, Player_1_Shots, Player_2_Shots);

		//give money to both players
		give_money();
	} while (check_win());



	return;
}