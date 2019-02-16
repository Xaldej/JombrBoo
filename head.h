#pragma once
using namespace std;

#include <iostream>
#include <conio.h>
#include <Windows.h>



//размеры полей
const int field_height = 24;
const int field_width = 59;
const int panel_width = 10;
const int panel_height = 24;


const int n_fields = 4; //количество масивов(полей)
//индексы масивов определяющие его номер и назначение
const int main_f = 0;
const int copy_f = 1;
const int h_cors_f = 2;
const int w_cors_f = 3;


//левая и правая панели;
char Left_panel[field_height][panel_width];
char Right_panel[field_height][panel_width];

int Batle_field[n_fields][field_height][field_width];  //[0][*][*] - основное поле; [1][*][*] - копия поля для прорисовки поля во время установки обьектов
int Shop_field[field_height][field_width + panel_width + panel_width]; // главный экран магазина




//размеры зданий
const int Building_width = 3;
const int Building_height = 3;

char building_type;  // тип здания. инициализируется при выборе в магазине // передается в функцию прорисовки/перемещении обьекта
char player; //('R' - правый игрок player2; 'L' - левый игрок player1)

int *arr = new int[(Building_height*Building_width)];
int Building[Building_height][Building_width];



int current_position_h;
int current_position_w;
int current_pos_extr_w;

int coordinate_h;
int coordinate_w;

//функции
void o_get_field_copy();						//отображает копию основного екрана в момент перемещения обьектов(пушек)
void o_push_batle_field_from_copy();			// переносит содержание временного масива во время установки пушек в главное поле
void o_display_batle_field(int panel_width, int field_height, int field_width); //отображает основной (главный) игровой екран
int *o_building_select(char player, char building_type);			//используется указатель на масив символов в качестве возвращаемого значения для функции перемещения орудий
void o_fill_batle_field_after_start();			//заполняет игровое поле после старта

void o_print_copy_batle_field(); //отображает на екране копию основного поля 
void o_fill_shop();				 //заполняет поле магазина 
void o_display_marker_in_store(char building_type); // отображает индикатор(скобки) во время выбора пушек в магазине
int	o_display_shop();  // отображает екран магазина

void o_get_shop_actions(); // принимает ввод в магазине
void o_get_main_screen_actions(); //принимает ввод на главном екране

// функции перемещения и установки обьектов
void o_move_elements(char player, char building_type);
void o_move_up(char player, char building_type);    // перемещает обьект вверх
void o_move_down(char player, char building_type);  // перемещает обьект вниз
void o_move_left(char player, char building_type);  // перемещает обьект влево
void o_move_right(char player, char building_type); // перемещает обьект вправо
void o_put_coordinates(char player, char building_type, int coordinate_h, int coordinate_w); // создает обьект указанными символами в масиве координат;

void o_display_h_coordinates_field(); //отображает координатное поле со значениями по высоте (у координаты)
void o_display_w_coordinates_field(); //отображает координатное поле со значениями по ширине (x координаты)
