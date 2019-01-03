#include<iostream>
#include<windows.h>
#include<ctime>
#include <fstream>
using namespace std;
const int I = 2, H = 25, W = 80; //map array parameters Index, Height, Width
const int gunsSize = 3 * 3;
const int asciiZeroPosition = 48;
const int res1IconP1W = 1, res2IconP1W = 5, res1IconP2W = 71, res2IconP2W = 75; // res1IconP1W - Width position for resource 1 icon Pleyer 1
const int startGunShopH1stp = 3, startGunShopW1stp = 1, startGunShopH2ndp = 3, startGunShopW2ndp = 71; // startGunShopH1stp - left top Heigth position for first player's gun shop menu
const char border = '.'; //list of border chars
const char borderIndex = 'b', economicIndex = 'e', gunIndex = 'g';
const char resourse1icon = '#', resourse2icon = '*';
const char Gun1Array[gunsSize] = { '/','-','\\','=','=','=','\\','-','/' };
const int Gun1ArrayCost1 = 10, Gun1ArrayCost2 = 101;
string firstMap = "map.txt";
HANDLE toPaint = GetStdHandle(STD_OUTPUT_HANDLE); //just need this thing to color symbols
enum color { BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5, BROWN = 6, LIGHTGRAY = 7, DARKGRAY = 8, LIGHTBLUE = 9, LIGHTGREEN = 10, LIGHTCYAN = 11, LIGHTRED = 12, LIGHTMAGENTA = 13, YELLOW = 14, WHITE = 15 };

void getTheMapFromTheFile(char MapMapArray[][H][W], string mapFileName);
void drowTheMap(char MapMapArray[][H][W]);
void addEconomics(char MapArray[][H][W], int resourse1Amount1stp = 111, int resourse2Amount1stp = 99, int resourse1Amount2ndp = 77, int resourse2Amouny2ndp = 4); // default values are spubs
void fillIndexesInTheMAp(char MapArray[][H][W]);
void addGunsList(char MapArray[][H][W], int gunSet = 1, int gunCost1 = 50, int gunCost2 = 10); // 1 is the stub

const int players_data_array_width = 6, players_data_array_long = 100;
int Player_1_Data[players_data_array_width][players_data_array_width] = { 0 }; // {0} to make it empty
int Player_2_Data[players_data_array_width][players_data_array_width] = { 0 }; // {0} to make it empty
/****************************************************************************************************************
all data about users' elements is stored in Player_1_Data and Player_2_Data arrays according to next rules:
each column is different info about the same element:
0 line: type of element
	1 - gun
	2 - wall
	3 - ...
1 line: amount of shots
2 line: shoots direction
	 1 - from left to right
	-1 - from right to left
3 line: amount of hp
4 line: horisontal position
5 line: vertical position
****************************************************************************************************************/

const int player_shots_array_width = 4, player_shots_array_long = 500;
int Player_1_Shots[player_shots_array_width][player_shots_array_long] = { 0 }; // {0} to make it empty
int Player_2_Shots[player_shots_array_width][player_shots_array_long] = { 0 }; // {0} to make it empty
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