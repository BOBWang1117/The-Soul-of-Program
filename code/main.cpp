/*
* This program is called 'The soul of the program'
* The aim is compute a table showing the effitive of some sort methods.
* The program used sorting method: BubbleSort(), QuickSort(), MergeSort()
* The finally sorting array is Ascending
*/

#include<iostream>
#include <stdlib.h>
#include <time.h>
#include"sortmethod.h"

using namespace std;

vector<int> DisorderSeeds()
{
	//Task 1: construct a disorder array
	long int length;
	long int div;
	vector<int> sortArray;

	printf("Please input a number you want to have a length in array: ");
	scanf_s("%d", &length);
	div = length*2 + 10;
	srand((unsigned)time(NULL));
	for (int i = 0; i < length; i++)
	{
		sortArray.push_back(rand() % div);
	}

	//Print the disorder array
	printf("Before sort: \n");
	for (int i = 0; i < length; i++)
	{
		//printf("%d ", sortArray[i]);
	}
	printf("\n");

	return sortArray;
}

int main()
{
	printf("The soul of the program\n");

	//Task 1: construct a disorder array
	vector<int> sortArray = DisorderSeeds();

	while (true)
	{
		int sortID;
		printf("Please input a number you want to sort ID: ");
		scanf_s("%d", &sortID);
		//Task 2: Using algorithm
		Method a(sortArray, sortID);
		a.doit();
	}

	return 0;
}