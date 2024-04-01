// C program for Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int arr_size = 0;
void printArray(int A[], int size);
// print bar
void bar(int value);

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
            //printArray(arr, arr_size);
		}
		else {
			arr[k] = R[j];
			j++;
            //printArray(arr, arr_size);
		}
		k++;
        //printArray(arr, arr_size);
	}
    //printArray(arr, arr_size);

	// Copy the remaining elements of L[],
	// if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
        //printArray(arr, arr_size);
        system("clear");
        for (int i = 0; i < arr_size; i++) {
            bar(arr[i]);
            printf("\n");
        }
        usleep(100000);
	}

	// Copy the remaining elements of R[],
	// if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
        //printArray(arr, arr_size);
        system("clear");
        for (int i = 0; i < arr_size; i++) {
            bar(arr[i]);
            printf("\n");
        }
        usleep(100000);
	}
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
	if (l < r) {
		int m = l + (r - l) / 2;

        // int arr_size = 6;//= sizeof(arr) / sizeof(arr[0]);
        //printArray(arr, 6);

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

// Function to print an array
void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

void bar (int value) {
    // Print progress bar
	//system("clear");
	
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
	int barWidth = w.ws_col - 10;

   	float progress = 0.0;
   	
	//while (progress < 1.0) {
    while (progress < value/100.0) {
	    //printf("\r%3d%% ", (int)(progress * 100.0));
        printf("\r%3d ", value);
	    int pos = barWidth * progress;
	    for (int i = 0; i < barWidth; i++) {
	        if (i <= pos) printf("\u2588");
	        else printf(" ");
	    }
	    fflush(stdout);
	
	    progress += 0.02; // test
	    
	    //usleep(100000);
	}
	//printf("\r100%%\n");
    //printf("\r%i", value);

}



// Driver code
int main()
{
	int arr[8] = { 43, 27, 99, 10, 67, 2, 45, 90 }; //, 87, 78, 65, 74 };
	arr_size = sizeof(arr) / sizeof(arr[0]);

	printf("Given array is \n");
	printArray(arr, arr_size);
    printf("\n");

	mergeSort(arr, 0, arr_size - 1);

	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	return 0;
}

