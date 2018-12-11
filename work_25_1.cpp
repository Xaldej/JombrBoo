/*work_25_1
autor: alexey melentyev
date: 06.12.18*/

#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;

void getArray(int *pointer, int A);
int getNumberFromUser(int from_number, int to_number);
void printArray(int *pointer, int A);
void copyArray(int *pointer_from, int *pointer_to, int A);

void main()
{
	int *pointer_1, *pointer_2;
	int N;

	cout << "What size of array do you want? " << endl;
	N = getNumberFromUser(10, 15);
	pointer_1 = new int[N];
	pointer_2 = new int[N];
	getArray(pointer_1, N);
	copyArray(pointer_1, pointer_2, N);
	cout << "Array 1:" << endl;
	printArray(pointer_1, N);
	cout << endl << "Array 2:" << endl;
	printArray(pointer_2, N);

	if (pointer_1)
	{
		delete[]pointer_1;
		pointer_1 = nullptr;
	}
	if (pointer_2)
	{
		delete[]pointer_2;
		pointer_2 = nullptr;
	}

	return;
}

void getArray(int *pointer, int A)
{
	srand(time(NULL));
	cout << "Waiting";
	for (int i = 0; i < A; i++)
	{
		*(pointer+i) = rand() % 100;
		Sleep(100);
		cout << ".";
	}
	return;
}

int getNumberFromUser(int from_number, int to_number)
{
	int input_number;
	while (1)
	{
		cout << "Enter number from " << from_number << " to " << to_number << " ";
		cin >> input_number;
		if ((input_number >= from_number) && (input_number <= to_number)) return input_number;
		else
		{
			cout << "Incorrect number" << endl;
			continue;
		}
	}
}

void copyArray(int *pointer_from, int *pointer_to, int A)
{
	for (int i = 0; i < A; i++)
	{
		*(pointer_to + i) = *(pointer_from + i);
	}
	return;
}

void printArray(int *pointer, int A)
{
	for (int i = 0; i < A; i++)
	{
		cout << *(pointer + i) << " ";
	}
	return;
}