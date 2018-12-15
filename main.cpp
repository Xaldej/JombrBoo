/*JoombrBoo
authours:
alexey melentyev
mihail ignatenko
oleg sazonov
date: 10.12.18*/

#include"head.h"
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
const int M = 5;
const int N = 100;
int Database_user_1[M][N];
int Database_user_2[M][N];
/*each column contain information about element
0 line: type of element
	 1 - wall
	 2 - usual gun
	 3 - in progress =)
1st line: remaining hp
2nd line: remaining shots
3rd and 4th lines: position of element
*/

void main()
{
	testFunction();

	system("pause");
	return;
}
