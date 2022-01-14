#include"sortmethod.h"
#include <chrono>   
using namespace std;
using namespace chrono;

//Test function
void testFuction(vector<int> vectorArray)
{
	printf("\n");
	printf("The result is \n");
	for (int i = 0; i < vectorArray.size(); i++)
	{
		//printf("%d ", vectorArray[i]);
	}
	printf("\n");
	printf("Done\n");
}

Method::Method(vector<int> passArray, int passSortID)
{
	array = passArray;
	sortID = passSortID;
}

void Method::Match()
{
	switch (sortID)
	{
	case 1:
		bubbleArray = array;
		BubbleSort();
		result = bubbleArray;
		break;

	case 2:
		quickArray = array;
		QuickSort(0, quickArray.size() - 1);
		result = quickArray;
		break;

	case 3:
	{
		mergeArray = array;
		result = mergeArray;
		MergeSort(result.data(), 0, mergeArray.size() - 1);
		mergeArray = result;
		
		break;
	}
	case 4:
	{
		result = HeapSort(array);
	}
		break;
	case 5:
	{
		result = ShellSort(array);
	}
	break;
	case 6:
	{
		result = BucketSort(array);
	}
	break;
	default:
		printf("ERROR: Please input an interge number 1 or 2 or 3!\n");
		exit(-1);

	}
}

void Method::BubbleSort()
{
	int temp;
	for (int i = 0; i < bubbleArray.size(); i++)
	{
		for (int j = 0; j < bubbleArray.size() - 1; j++)
		{
			if (bubbleArray[j] > bubbleArray[j + 1])
			{
				temp = bubbleArray[j];
				bubbleArray[j] = bubbleArray[j + 1];
				bubbleArray[j + 1] = temp;
			}
		}
	}

	testFuction(bubbleArray);
	printf("BubbleSort Done!\n");
}

void Method::QuickSort(int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int i, j, base, temp;
	i = left, j = right;
	base = quickArray[left];
	while (i < j)
	{
		while (quickArray[j] >= base && i < j)
			j--;
		while (quickArray[i] <= base && i < j)
			i++;
		if (i < j)
		{
			temp = quickArray[i];
			quickArray[i] = quickArray[j];
			quickArray[j] = temp;
		}
	}
	quickArray[left] = quickArray[i];
	quickArray[i] = base;

	QuickSort(left, i - 1);
	QuickSort(i + 1, right);
}

void merge(int arr[], int l, int q, int r)
{
	int n = r - l + 1;
	int* tmp = new int[n];
	int i = 0;
	int left = l;
	int right = q + 1;
	while (left <= q && right <= r)
		tmp[i++] = arr[left] <= arr[right] ? arr[left++] : arr[right++];
	while (left <= q)
		tmp[i++] = arr[left++];
	while (right <= r)
		tmp[i++] = arr[right++];
	for (int j = 0; j < n; ++j)
		arr[l + j] = tmp[j];
	delete[] tmp;
}

void Method::MergeSort(int arr[], int l, int r)
{
	if (l == r)
		return;
	int q = (l + r) / 2;
	MergeSort(arr, l, q);
	MergeSort(arr, q + 1, r);
	merge(arr, l, q, r);

}

void max_heapify(int arr[], int start, int end) {
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { 
		if (son + 1 <= end && arr[son] < arr[son + 1]) 
			son++;
		if (arr[dad] > arr[son])

			return;
		else { 
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

vector<int>  Method::HeapSort(vector<int> vSrc)
{
	int len = vSrc.size();
	for (int i = len / 2 - 1; i >= 0; i--)
		max_heapify(vSrc.data(), i, len - 1);

	for (int i = len - 1; i > 0; i--) {
		swap(vSrc[0], vSrc[i]);
		max_heapify(vSrc.data(), 0, i - 1);
	}
	return vSrc;
}

const int BUCKET_NUM = 10;

struct ListNode {
	explicit ListNode(int i = 0) :mData(i), mNext(NULL) {}
	ListNode* mNext;
	int mData;
};
ListNode* InsertList(ListNode* head, int val) {
	ListNode dummyNode;
	ListNode* newNode = new ListNode(val);
	ListNode* pre, * curr;
	dummyNode.mNext = head;
	pre = &dummyNode;
	curr = head;
	while (NULL != curr && curr->mData <= val) {
		pre = curr;
		curr = curr->mNext;
	}
	newNode->mNext = curr;
	pre->mNext = newNode;
	return dummyNode.mNext;
}
ListNode* MergeList(ListNode* head1, ListNode* head2) {
	ListNode dummyNode;
	ListNode* dummy = &dummyNode;
	while (NULL != head1 && NULL != head2) {
		if (head1->mData <= head2->mData) {
			dummy->mNext = head1;
			head1 = head1->mNext;
		}
		else {
			dummy->mNext = head2;
			head2 = head2->mNext;
		}
		dummy = dummy->mNext;
	}
	if (NULL != head1) dummy->mNext = head1;
	if (NULL != head2) dummy->mNext = head2;

	return dummyNode.mNext;
}

vector<int> Method::BucketSort(vector<int> vData) {
	int n = vData.size();
	vector<ListNode*> buckets(BUCKET_NUM, (ListNode*)(0));
	for (int i = 0; i < n; ++i) {
		int index = vData[i] % BUCKET_NUM;
		ListNode* head = buckets.at(index);
		buckets.at(index) = InsertList(head, vData[i]);
	}
	ListNode* head = buckets.at(0);
	for (int i = 1; i < BUCKET_NUM; ++i) {
		head = MergeList(head, buckets.at(i));
	}
	for (int i = 0; i < n; ++i) {
		vData[i] = head->mData;
		head = head->mNext;
	}

	return vData;
}

vector<int> Method::ShellSort(vector<int> vData) {
	int len = vData.size();
	int gap, i, j;
	int temp;
	for (gap = len >> 1; gap > 0; gap >>= 1)
		for (i = gap; i < len; i++) {
			temp = vData[i];
			for (j = i - gap; j >= 0 && vData[j] > temp; j -= gap)
				vData[j + gap] = vData[j];
			vData[j + gap] = temp;
		}
	return vData;
}

void Method::doit()
{
	auto start = system_clock::now();
	Match();
	auto end = system_clock::now();

	switch (sortID)
	{
	case 1:
		printf("bubblesort:\n");
		break;

	case 2:
		printf("quickArray:\n");
		break;

	case 3:
	{
		printf("mergeArray:\n");
		break;
	}
	case 4:
	{
		printf("HeapSort:\n");
	}
	break;
	case 5:
	{
		printf("ShellSort:\n");
	}
	break;
	case 6:
	{
		printf("BucketSort:\n");
	}
	break;
	default:
		printf("ERROR: Please input an interge number 1 or 2 or 3!\n");
		exit(-1);

	}

	testFuction(result);
	printf("\ncost:%0.3fms\n",1000.0f* duration_cast<microseconds>(end - start) * microseconds::period::num / double(microseconds::period::den));
}