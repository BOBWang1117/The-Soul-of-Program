#ifndef SORTMETHOD_H
#define SORTMETHOD_H

#include<vector>
using namespace std;

class Method
{
private:
	int sortID;

	vector<int> array;

	vector<int> bubbleArray;

	vector<int> quickArray;

	vector<int> mergeArray;
	vector<int> result;

	void Match();

	void BubbleSort();

	void QuickSort(int left, int right);

	void MergeSort(int arr[], int l, int r);

	vector<int>  HeapSort(vector<int> vSrc);
	vector<int> BucketSort(vector<int> vData);
	vector<int>  ShellSort(vector<int> vData);
public:
	Method(vector<int> array, int sortID);

	void doit();
};

#endif


