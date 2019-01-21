#include"head.h"
HANDLE toPaint = GetStdHandle(STD_OUTPUT_HANDLE);

/*
Get the map from the .txt file and write it to the Array "Map"
Arguments:
MapArray - the Array we are going to write the file to
mapFileName - name of the file we take info from
*/
void getTheMapFromTheFile(char MapArray[][H][W], string mapFileName)
{
	char TempMapRow[W + 1];
	ifstream fileMapIn(mapFileName);
	if (fileMapIn.is_open())
	{
		for (int h = 0; h < H && !fileMapIn.eof(); h++)
		{
			fileMapIn.getline(TempMapRow, (W + 1));
			for (int w = 0; w < W; w++)
			{
				MapArray[0][h][w] = TempMapRow[w];
			}
		}
		fileMapIn.close();
	}
	else
	{
		printf("Error\! The map file was not found\n");
		return;
	}
	return;
}
/*
Fill the map with the economy info
Arguments:
MapArray - the Array where we should add an economics
resourse1Amount1stp - amount of the first reosurse for the first player
resourse2Amount1stp - amount of the second resourse for the second player
resourse1Amount2ndp - amount of the first reosurse for the first player
resourse2Amouny2ndp - amount of the second resourse for the second player
*/
void addEconomics(char MapArray[][H][W], int resourse1Amount1stp, int resourse2Amount1stp, int resourse1Amount2ndp, int resourse2Amouny2ndp)
{
	int tempRes = 0;
	MapArray[0][1][res1IconP1W] = resourse1icon;
	MapArray[0][1][res2IconP1W] = resourse2icon;
	MapArray[0][1][res1IconP2W] = resourse1icon;
	MapArray[0][1][res2IconP2W] = resourse2icon;
	for (int i = 3; i > 0; i--) // 3 for three digit numbers of resources
	{
		tempRes = resourse1Amount1stp % 10;
		resourse1Amount1stp /= 10;
		MapArray[0][1][res1IconP1W + i] = char(tempRes + asciiZeroPosition);
	}
	for (int i = 3; i > 0; i--)
	{
		tempRes = resourse2Amount1stp % 10;
		resourse2Amount1stp /= 10;
		MapArray[0][1][res2IconP1W + i] = char(tempRes + asciiZeroPosition);
	}
	for (int i = 3; i > 0; i--)
	{
		tempRes = resourse1Amount2ndp % 10;
		resourse1Amount2ndp /= 10;
		MapArray[0][1][res1IconP2W + i] = char(tempRes + asciiZeroPosition);
	}
	for (int i = 3; i > 0; i--)
	{
		tempRes = resourse2Amouny2ndp % 10;
		resourse2Amouny2ndp /= 10;
		MapArray[0][1][res2IconP2W + i] = char(tempRes + asciiZeroPosition);
	}
	return;
}
/*
Add all guns to the gun list
Arguments:
MapArray - map to add guns in
gunSet - set of guns we should add
gunCost1 - cost of gun for 1st resource
gunCost2 - cost of gun for 2st resource
*/
void addGunsList(char MapArray[][H][W], int gunSet, int gunCost1, int gunCost2)
{
	int currentGunH = startGunShopH1stp;
	int gunCost1temp = gunCost1;
	int gunCost2temp = gunCost2;
	switch (gunSet)
	{
	case 1:
	{
		for (int j = 0, z = 0; j < 4; j++)
		{
			for (int i = 0; i < 3; i++, z++)
			{
				if (!(j == 3))
				{
					MapArray[0][startGunShopH1stp + j][startGunShopW1stp + i] = Gun1Array[z];
					MapArray[1][startGunShopH1stp + j][startGunShopW1stp + i] = gunIndex;
				}
				else
				{
					MapArray[0][startGunShopH1stp + j][startGunShopW1stp + i] = border;
				}
			}
		}
		for (int j = 0, z = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++, z++)
			{
				if (i == 0 && j == 0)
				{
					MapArray[0][startGunShopH1stp + j][startGunShopW1stp + i + 3] = resourse1icon;
					MapArray[1][startGunShopH1stp + j][startGunShopW1stp + i + 3] = economicIndex;
					MapArray[0][startGunShopH1stp + j + 3][startGunShopW1stp + i + 3] = border;
					MapArray[1][startGunShopH1stp + j + 3][startGunShopW1stp + i + 3] = borderIndex;
				}
				else if (j == 0)
				{
					MapArray[0][startGunShopH1stp + j][startGunShopW1stp + i + 3] = (gunCost1 % 10 + asciiZeroPosition);
					gunCost1 /= 10;
					MapArray[0][startGunShopH1stp + j + 3][startGunShopW1stp + i + 3] = border;
					MapArray[1][startGunShopH1stp + j + 3][startGunShopW1stp + i + 3] = borderIndex;
					MapArray[0][startGunShopH1stp + j + 3][startGunShopW1stp + i + 4] = border;
					MapArray[1][startGunShopH1stp + j + 3][startGunShopW1stp + i + 4] = borderIndex;
				}
				if (i == 0 && j == 1)
				{
					MapArray[0][startGunShopH1stp + j][startGunShopW1stp + i + 3] = resourse2icon;
					MapArray[1][startGunShopH1stp + j][startGunShopW1stp + i + 3] = economicIndex;
				}
				else if (j == 1)
				{
					MapArray[0][startGunShopH1stp + j][startGunShopW1stp + i + 3] = (gunCost2 % 10 + asciiZeroPosition);
					gunCost2 /= 10;
				}
			}
		}
		for (int j = 0, z = 0; j < 4; j++)
		{
			for (int i = 0; i < 3; i++, z++)
			{
				if (!(j == 3))
				{
					MapArray[0][startGunShopH2ndp + j][startGunShopW2ndp + i] = Gun1Array[z];
					MapArray[1][startGunShopH2ndp + j][startGunShopW2ndp + i] = gunIndex;
				}
				else
				{
					MapArray[0][startGunShopH2ndp + j][startGunShopW2ndp + i] = border;
				}
			}
		}
		for (int j = 0, z = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++, z++)
			{
				if (i == 0 && j == 0)
				{
					MapArray[0][startGunShopH2ndp + j][startGunShopW2ndp + i + 3] = resourse1icon;
					MapArray[1][startGunShopH2ndp + j][startGunShopW2ndp + i + 3] = economicIndex;
					MapArray[0][startGunShopH2ndp + j + 3][startGunShopW2ndp + i + 3] = border;
					MapArray[1][startGunShopH2ndp + j + 3][startGunShopW2ndp + i + 3] = borderIndex;
				}
				else if (j == 0)
				{
					MapArray[0][startGunShopH2ndp + j][startGunShopW2ndp + i + 3] = (gunCost1temp % 10 + asciiZeroPosition);
					gunCost1temp /= 10;
					MapArray[0][startGunShopH2ndp + j + 3][startGunShopW2ndp + i + 3] = border;
					MapArray[1][startGunShopH2ndp + j + 3][startGunShopW2ndp + i + 3] = borderIndex;
					MapArray[0][startGunShopH2ndp + j + 3][startGunShopW2ndp + i + 4] = border;
					MapArray[1][startGunShopH2ndp + j + 3][startGunShopW2ndp + i + 4] = borderIndex;
				}
				if (i == 0 && j == 1)
				{
					MapArray[0][startGunShopH2ndp + j][startGunShopW2ndp + i + 3] = resourse2icon;
					MapArray[1][startGunShopH2ndp + j][startGunShopW2ndp + i + 3] = economicIndex;
				}
				else if (j == 1)
				{
					MapArray[0][startGunShopH2ndp + j][startGunShopW2ndp + i + 3] = (gunCost2temp % 10 + asciiZeroPosition);
					gunCost2temp /= 10;
				}
			}
		}
		currentGunH += 4;
	};
	break;
	default: break;
	}
	return;
}
/*
Set indexes for the map
Arguments:
MapArray - the Array we are going to set indexes for
*/
void fillIndexesInTheMAp(char MapArray[][H][W])
{
	for (int h = 0; h < H; h++)
	{
		for (int w = 0; w < W; w++)
		{
			if (MapArray[0][h][w] == border)
			{
				MapArray[1][h][w] = borderIndex;
			}
			if (MapArray[0][h][w] == resourse1icon || MapArray[0][h][w] == resourse2icon)
			{
				MapArray[1][h][w] = economicIndex; //resource and 3 dijit number of resuorce amount
				MapArray[1][h][w + 1] = economicIndex;
				MapArray[1][h][w + 2] = economicIndex;
				MapArray[1][h][w + 3] = economicIndex;
			}
		}
	}
	return;
}
/*
Outputs the map to the user's screen
Arguments:
MapArray - the Array to output
*/
void drowTheMap(char MapArray[][H][W])
{
	for (int h = 0; h < H; h++)
	{
		for (int w = 0; w < W; w++)
		{
			if (MapArray[1][h][w] == borderIndex)
			{
				SetConsoleTextAttribute(toPaint, (RED << 4) + WHITE);
			}
			else if (MapArray[1][h][w] == economicIndex)
			{
				SetConsoleTextAttribute(toPaint, (YELLOW << 4) + BLACK);
			}
			else if (MapArray[1][h][w] == gunIndex)
			{
				SetConsoleTextAttribute(toPaint, (BLACK << 4) + RED);
			}
			else
			{
				SetConsoleTextAttribute(toPaint, (WHITE << 4) + GREEN);
			}
			printf("%c", MapArray[0][h][w]);
		}
	}
	return;
}
