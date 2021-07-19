#include <iostream>
#include <cstdlib>

using namespace std;

void merge(int arr[], int const left, int const middle, int const right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int *leftSubArray = new int[n1], *rightSubArray = new int[2];

    for(int index = 0; index < n1; index++)
        leftSubArray[index] = arr[left + index];
    
    for(int index = 0; index < n2; index++)
        rightSubArray[index] = arr[middle + 1 + index];

    int subArrayOneIndex = 0;
    int subArrayTwoIndex = 0;
    int subArrayMergeIndex = left;

    while(subArrayOneIndex < n1 && subArrayTwoIndex < n2)
    {
        if(leftSubArray[subArrayOneIndex] <= rightSubArray[subArrayTwoIndex])
        {
            arr[subArrayMergeIndex] = leftSubArray[subArrayOneIndex];
            subArrayOneIndex++;
        }
        else
        {
            arr[subArrayMergeIndex] = rightSubArray[subArrayTwoIndex];
            subArrayTwoIndex++;
        }
        subArrayMergeIndex++;
    }

    while(subArrayOneIndex < n1)
    {
        arr[subArrayMergeIndex] = leftSubArray[subArrayOneIndex];
        subArrayOneIndex++;
        subArrayMergeIndex++;
    }

    while(subArrayTwoIndex < n2)
    {
        arr[subArrayMergeIndex] = rightSubArray[subArrayTwoIndex];
        subArrayTwoIndex++;
        subArrayMergeIndex++;

    }

}

void mergeSort(int arr[], int left, int right)
{
    if(left < right)
    {
        int middle = (left + right)/2;
        mergeSort(arr, left, middle);
        mergeSort(arr,middle+1, right);
        merge(arr, left, middle, right);
    }
}

int main()
{
    int arr[10] = {0};

    int size = 10;

    for(int index=0; index < size; index++)
    {
        arr[index] = rand() % 10000;

       cout<< arr[index] << " ";
    }

    mergeSort(arr,0,9);
    cout<< "\nAfter Sort" <<endl;
    for(int index=0; index < 10; index++)
    {
        cout<<arr[index] << " ";
    }

    return 0;
}