/* C program for Merge Sort using parallel programming */
#include <stdio.h>
#include <stdlib.h>
#include<omp.h>

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void parallelMergeSort(int arr[], int l, int r)
{
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr, l, m);
            }
            #pragma omp section
            {
                mergeSort(arr, m + 1, r);
            }
        }

		merge(arr, l, m, r);
	}
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

/* Driver code */
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
	mergeSort(arr, 0, arr_size - 1);
    end = omp_get_wtime();

    start1 = omp_get_wtime();
    parallelMergeSort(B, 0, arr_size - 1);
    end1 = omp_get_wtime();

	printf("\nSorted array is :\n");
	printArray(arr, arr_size);
    printf("\n\nExecution time in serial merge sort is : %f seconds\n\n", end-start);
    printf("\nExecution time in parallel merge sort is : %f seconds\n\n", end1-start1);

	return 0;
}