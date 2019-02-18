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

extern int total_money_left;
extern int total_money_right;


//end_�������

//��������
const int shots_1 = 20;
const int shots_2 = 10;
const int shots_3 = 0;
const int shots_4 = 0;
//����������� ��������
const int sh_route_l = 1;
const int sh_route_r = -1;
const int sh_route_3 = 0;
const int sh_route_4 = 0;

//���������� 
const int HP_1 = 10;
const int HP_2 = 5;
const int HP_3 = 20;
const int HP_4 = 10;

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
bool give_money();
void money_have();