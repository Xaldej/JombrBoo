#include<iostream>
#include<windows.h>
#include<ctime>
#include <fstream>

void getTheMapFromTheFile(char MapMapArray[][H][W], string mapFileName);
void drowTheMap(char MapMapArray[][H][W]);
void addEconomics(char MapArray[][H][W], int resourse1Amount1stp = 111, int resourse2Amount1stp = 99, int resourse1Amount2ndp = 77, int resourse2Amouny2ndp = 4); // default values are spubs
void fillIndexesInTheMAp(char MapArray[][H][W]);
void addGunsList(char MapArray[][H][W], int gunSet = 1, int gunCost1 = 50, int gunCost2 = 10); // 1 is the stub
