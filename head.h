#pragma once
using namespace std;

#include <iostream>
#include <conio.h>
#include <Windows.h>



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
char Left_panel[field_height][panel_width];
char Right_panel[field_height][panel_width];

int Batle_field[n_fields][field_height][field_width];  //[0][*][*] - �������� ����; [1][*][*] - ����� ���� ��� ���������� ���� �� ����� ��������� ��������
int Shop_field[field_height][field_width + panel_width + panel_width]; // ������� ����� ��������




//������� ������
const int Building_width = 3;
const int Building_height = 3;

char building_type;  // ��� ������. ���������������� ��� ������ � �������� // ���������� � ������� ����������/����������� �������
char player; //('R' - ������ ����� player2; 'L' - ����� ����� player1)

int *arr = new int[(Building_height*Building_width)];
int Building[Building_height][Building_width];



int current_position_h;
int current_position_w;
int current_pos_extr_w;

int coordinate_h;
int coordinate_w;

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
