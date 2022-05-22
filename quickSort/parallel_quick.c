/* C implementation of QuickSort */
#include <stdio.h>
#include <stdlib.h>
#include<omp.h>

// A utility function to swap two elements
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than the pivot
		if (arr[j] < pivot)
		{
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void parallelQuickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition

        #pragma omp parallel sections
        { 
            #pragma omp section
            {
                // recursive call on the left of pivot
                quickSort(arr, low, pi - 1);
            }

            #pragma omp section
            {
                // recursive call on the right of pivot
                quickSort(arr, pi + 1, high);
            }  
        }
		
	}
}

/* Function to print an array */
void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

// Driver Code
int main()
{
    double start, end, start1, end1;
    int arr_size;
    printf("Enter size of array : ");
    scanf("%d", &arr_size);

    int arr[arr_size], B[arr_size];

    for(int i = 0; i < arr_size; i++)
    {
        arr[i] = rand()%100;
        B[i] = arr[i];
    }

    printf("\nRandom generated array is :\n");
	printArray(arr, arr_size);

    start = omp_get_wtime();
	quickSort(arr, 0, arr_size - 1);
    end = omp_get_wtime();

    start1 = omp_get_wtime();
    parallelQuickSort(B, 0, arr_size - 1);
    end1 = omp_get_wtime();

    printf("\nSorted array is :\n");
	printArray(arr, arr_size);
    printf("\n\nExecution time in serial Quick sort is : %f seconds\n\n", end-start);
    printf("\nExecution time in parallel Quick sort is : %f seconds\n\n", end1-start1);


	return 0;
}
