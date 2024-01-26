#include<stdio.h>

#define NUMBERS {4, 6, 2, 11, 3, 7}

#define SWAP(x,y) { int t = *x; *x = *y; *y = t; }

#define PRINTINT(x) printf("%d", x);

#define TAB "\t"

#define NEWLINE "\n"

#define FOR(a,b,c,d) for(int a = b; a <= c; d)
#define QUICK(x,y,z) quickSort(x,y,z)

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    FOR (j, low, high-1, j++){
        if (arr[j] <= pivot)
        {
            i++;
            SWAP(&arr[i], &arr[j]);
        }
    }
    SWAP(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        QUICK(arr, low, pi - 1);
        QUICK(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size)
{
    int i;
    FOR(i,0,size-1,i++){
        PRINTINT(arr[i]);
        printf(TAB);
    }
    printf(NEWLINE);
}

int main()
{
    int arr[] = NUMBERS;
    int n = sizeof(arr)/sizeof(arr[0]);
    QUICK(arr, 0, n-1);
    printf(NEWLINE);
    printArray(arr, n);
    printf(NEWLINE);
    return 0;
}
