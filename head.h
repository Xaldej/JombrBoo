#pragma once
//ok

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;




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

const int name_lenght = 7;
char Name_P1[name_lenght] = " Jombr";
char Name_P2[name_lenght] = " Boo  ";



int Batle_field[n_fields][field_height][field_width];  //[0][*][*] - основное поле; [1][*][*] - копия поля для прорисовки поля во время установки обьектов
int Shop_field[field_height][field_width + panel_width + panel_width]; // главный экран магазина

//согласовать вычитание номера обьекта при перемещении данных  ????????????????????????????????????????????????????????????????
int element_number_l = -1; // -1 потому что сразу при входе в функцию делается ++ и для первого раза значение будет 0
int element_number_r = -1;

const int info_h = 6;
const int info_w = 20;

int Elements_Info_Player_Left[info_h][info_w];
int Elements_Info_Player_Right[info_h][info_w];

//параметры обьектов

//финансы_start
const int gun_1_price = 600;
const int gun_2_price = 400;
const int wall_1_price = 200;
const int wall_2_price = 100;

int total_money_left = 1200;
int total_money_right = 1200;

wint_t sec;
//end_финансы

//выстрелы
const int shots_1 = 20;
const int shots_2 = 10;
const int shots_3 = 0;
const int shots_4 = 0;
//направление выстрела
const int sh_route_l = 1;
const int sh_route_r = -1;
const int sh_route_3 = 0;
const int sh_route_4 = 0;

//количество 
const int HP_1 = 10;
const int HP_2 = 5;
const int HP_3 = 20;
const int HP_4 = 10;

//строки для info
const int b_type = 0;	// тип элемента
const int shots = 1;	// количество выстрелов
const int sh_route = 2; // направление выстрела
const int HP = 3;		// количество жизней
const int h_cor = 4;    // h координата центра обекта (высота  || Y)
const int w_cor = 5;     // w координата центра обекта (ширина || X)

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

void o_write_info_about_player_odject(char player, char building_type, int coordinate_h, int coordinate_w);  // записывает данные об обьектах игрока
void print_objects_info();

void o_fill_pannels();

int o_calculate_money(char player, char building_type);
int o_item_price(char building_type);
bool give_money();
void money_have();