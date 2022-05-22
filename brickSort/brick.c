// C Program to implement Odd-Even / Brick Sort
#include <stdio.h>
#include <stdlib.h>
#include<omp.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// A function to sort the algorithm using Odd Even sort
void oddEvenSort(int arr[], int arr_size)
{
	int isSorted = 0; // Initially array is unsorted

	while (!isSorted)
	{
		isSorted = 1;

		// Perform Bubble sort on odd indexed element
		for (int i=1; i<=arr_size-2; i=i+2)
		{
			if (arr[i] > arr[i+1])
			{
				swap(&arr[i], &arr[i+1]);
				isSorted = 0;
			}
		}

		// Perform Bubble sort on even indexed element
		for (int i=0; i<=arr_size-2; i=i+2)
		{
			if (arr[i] > arr[i+1])
			{
				swap(&arr[i], &arr[i+1]);
				isSorted = 0;
			}
		}
	}

}

// A utility function ot print an array 
void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

// Driver program to test above functions.
int main()
{
    double start, end;
    int arr_size;
    printf("Enter size of array : ");
    scanf("%d", &arr_size);

    int arr[arr_size];

    for(int i = 0; i < arr_size; i++)
    {
        arr[i] = rand()%100;
    }

    printf("\nRandom array is :\n");
	printArray(arr, arr_size);

	// int arr[] = {34, 2, 10, -9};
	// int arr_size = sizeof(arr)/sizeof(arr[0]);

    start = omp_get_wtime();

	oddEvenSort(arr, arr_size);

    end = omp_get_wtime();

    printf("\nSorted array is :\n");
	printArray(arr, arr_size);
    printf("\nExecution time in Brick sort is : %f seconds\n\n", end-start);


	return 0;
}
