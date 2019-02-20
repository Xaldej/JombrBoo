#pragma once
//ok

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;

//������� �����
const int field_height = 24;
const int field_width = 59;
const int panel_width = 10;
const int panel_height = 24;


const int n_fields = 4; //���������� �������(�����)
//������� ������� ������������ ��� ����� � ����������
const int main_f = 0;
const int copy_f = 1;
const int h_cors_f = 2;
const int w_cors_f = 3;


//����� � ������ ������;
extern char Left_panel[field_height][panel_width];
extern char Right_panel[field_height][panel_width];

const int name_lenght = 7;

extern char Name_P1[name_lenght];
extern char Name_P2[name_lenght];


extern int Batle_field[n_fields][field_height][field_width];  //[0][*][*] - �������� ����; [1][*][*] - ����� ���� ��� ���������� ���� �� ����� ��������� ��������
extern int Shop_field[field_height][field_width + panel_width + panel_width]; // ������� ����� ��������

//����������� ��������� ������ ������� ��� ����������� ������  ????????????????????????????????????????????????????????????????
extern int element_number_l; // -1 ������ ��� ����� ��� ����� � ������� �������� ++ � ��� ������� ���� �������� ����� 0
extern int element_number_r;

const int info_h = 6;
const int info_w = 20;

extern int Elements_Info_Player_Left[info_h][info_w];
extern int Elements_Info_Player_Right[info_h][info_w];

//��������� ��������

//�������_start
const int gun_1_price = 600;
const int gun_2_price = 400;
const int wall_1_price = 200;
const int wall_2_price = 100;
const int goldmine_price = 950;

extern int total_money_left;
extern int total_money_right;


//end_�������

//��������
const int shots_1 = 20;
const int shots_2 = 10;
const int shots_3 = 0;
const int shots_4 = 0;
const int shots_5 = 0;
//����������� ��������
const int sh_route_l = 1;
const int sh_route_r = -1;
const int sh_route_3 = 0;
const int sh_route_4 = 0;
const int sh_route_5 = 0;
//���������� 
const int HP_1 = 10;
const int HP_2 = 5;
const int HP_3 = 20;
const int HP_4 = 10;
const int HP_5 = 5;
//������ ��� info
const int b_type = 0;	// ��� ��������
const int shots = 1;	// ���������� ���������
const int sh_route = 2; // ����������� ��������
const int HP = 3;		// ���������� ������
const int h_cor = 4;    // h ���������� ������ ������ (������  || Y)
const int w_cor = 5;     // w ���������� ������ ������ (������ || X)

//������� ������
const int Building_width = 3;
const int Building_height = 3;

extern char building_type;  // ��� ������. ���������������� ��� ������ � �������� // ���������� � ������� ����������/����������� �������
extern char player; //('R' - ������ ����� player2; 'L' - ����� ����� player1)

extern int *arr;
extern int Building[Building_height][Building_width];

extern int current_position_h;
extern int current_position_w;
extern int current_pos_extr_w;

extern int coordinate_h;
extern int coordinate_w;

//�������
void o_get_field_copy();						//���������� ����� ��������� ������ � ������ ����������� ��������(�����)
void o_push_batle_field_from_copy();			// ��������� ���������� ���������� ������ �� ����� ��������� ����� � ������� ����
void o_display_batle_field(int panel_width, int field_height, int field_width); //���������� �������� (�������) ������� �����
int *o_building_select(char player, char building_type);			//������������ ��������� �� ����� �������� � �������� ������������� �������� ��� ������� ����������� ������
void o_fill_batle_field_after_start();			//��������� ������� ���� ����� ������

void o_print_copy_batle_field(); //���������� �� ������ ����� ��������� ���� 
void o_fill_shop();				 //��������� ���� �������� 
void o_display_marker_in_store(char building_type); // ���������� ���������(������) �� ����� ������ ����� � ��������
int	o_display_shop();  // ���������� ����� ��������

void o_get_shop_actions(); // ��������� ���� � ��������
void o_get_main_screen_actions(); //��������� ���� �� ������� ������

// ������� ����������� � ��������� ��������
void o_move_elements(char player, char building_type);
void o_move_up(char player, char building_type);    // ���������� ������ �����
void o_move_down(char player, char building_type);  // ���������� ������ ����
void o_move_left(char player, char building_type);  // ���������� ������ �����
void o_move_right(char player, char building_type); // ���������� ������ ������
void o_put_coordinates(char player, char building_type, int coordinate_h, int coordinate_w); // ������� ������ ���������� ��������� � ������ ���������;

void o_display_h_coordinates_field(); //���������� ������������ ���� �� ���������� �� ������ (� ����������)
void o_display_w_coordinates_field(); //���������� ������������ ���� �� ���������� �� ������ (x ����������)

void o_write_info_about_player_odject(char player, char building_type, int coordinate_h, int coordinate_w);  // ���������� ������ �� �������� ������
void print_objects_info();

void o_fill_pannels();

int o_calculate_money(char player, char building_type);
int o_item_price(char building_type);
void give_money();
void money_have();
void play();
bool o_check_free_zone(int current_position_h, int current_position_w, char building_type); //��������� �������� �� ���� ��� ��������� �������;



/***********alexey_melentyev****************/

//some code was written separatly from Oleg's code. Because of this I used define Not to rename elements
#define Player_1_Data Elements_Info_Player_Left
#define Player_2_Data Elements_Info_Player_Right
#define data_M info_h
#define data_N info_w
#define MainField Batle_field[0]


const int shots_M = 4, shots_N = 500;
extern int Player_1_Shots[shots_M][shots_N]; // {0} to make it empty
extern int Player_2_Shots[shots_M][shots_N]; // {0} to make it empty	
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

//functions alexey_melentyev

void MovementMechanichs(int Player_1_Data[data_M][data_N], int Player_2_Data[data_M][data_N], int Player_1_Shots[shots_M][shots_N], int Player_2_Shots[shots_M][shots_N]);
void MakeAShot(int Player_Data[data_M][data_N], int Player_Shots[shots_M][shots_N], int number_of_element);
int ShotMovement(int Player_1_Data[data_M][data_N], int Player_2_Data[data_M][data_N], int Player_Shots[shots_M][shots_N], int number, int player_number);
void MakeADamage(int Player_1_Data[data_M][data_N], int Player_2_Data[data_M][data_N], int Player_Shot[shots_M][shots_N], int number_of_shot, int player_number, int number_of_element_to_damage);
void DeleteInfoFromShots(int Array[shots_M][shots_N], int shot_number, int player_number);
int FindElementToDamage(int Player_Data[data_M][data_N], int m, int n);
int CheckElementDestroy(int Player_Data[data_M][data_N], int number_of_element);
void DeleteInfoFromField(int Player_Data[data_M][data_N], int number_of_element);
void DeleteInfoFromData(int Player_Data[data_M][data_N], int number_of_element, int player_number);
bool check_win();

