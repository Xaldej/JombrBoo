#include "head.h"



//ok
int main()
{
	system("mode CON: lines=25 cols=80"); //to make sure that console has right size
	
	o_fill_batle_field_after_start();
	o_fill_pannels();
	
	do
	{
		//player 1 (L) turn
		player = 'L';		
		o_display_batle_field(panel_width, field_height, field_width);
		printf("\t\tPlayer 1 turn");
		o_get_main_screen_actions();

		//player 2 (R) turn
		player = 'R';		
		o_display_batle_field(panel_width, field_height, field_width);
		printf("\t\tPlayer 2 turn");
		o_get_main_screen_actions();

		//counting of shots movement, damage, etc
		MovementMechanichs(Player_1_Data, Player_2_Data, Player_1_Shots, Player_2_Shots);

		//give money to both players
		give_money();
	} while (1); //1 will be changet to function check win

	return 0;
}
