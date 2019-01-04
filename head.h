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

const int data_M = 6, data_N = 100;
const int shots_M = 4, shots_N = 500;
extern int Player_1_Data[data_M][data_N];
extern int Player_2_Data[data_M][data_N];
extern int Player_1_Shots[shots_M][shots_N];
extern int Player_2_Shots[shots_M][shots_N];
