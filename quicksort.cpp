// C program for Quick Sort
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <chrono>
#include <iostream>

int arr_size = 0;
void printArray(int A[], int size);
void printArrayBar(int A[], int size, int lt, int nc, int pi);
// print bar
void bar(int value);

int usecs, tfnd;


struct perf {
    std::chrono::steady_clock::time_point start_;
    perf() : start_(std::chrono::steady_clock::now()) {}
    double elapsed() const {
        auto stop = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = stop - start_;
        return elapsed_seconds.count();
    }
};


// See: https://www.geeksforgeeks.org/quick-sort/
// Lomuto partition scheme

// Utility function to swap tp integers
void swap(int* p1, int* p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int arr[], int low, int high)
{
    // choose the pivot
    int pivot = arr[high];

    // Index of smaller element and Indicate
    // the right position of pivot found so far
    int i = (low - 1);

    for (int j = low; j <= high; j++) {
        printArrayBar(arr, arr_size, i, j, high);
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            // Increment index of smaller element
            i++;
            swap(&arr[i], &arr[j]);
            //printArray(arr, arr_size);
            //printArrayBar(arr, arr_size, i, j, high);
        }
    }
    i++;
    //swap(&arr[i + 1], &arr[high]);
    swap(&arr[i], &arr[high]); // swap pivot
    //printArray(arr, arr_size);
    printArrayBar(arr, arr_size, i-1, i+1, i);
    
    //return (i + 1);
    return (i);
}

// The Quicksort function Implement
void quickSort(int arr[], int low, int high)
{
    // when low is less than high
    if (low < high) {
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion Call
        // smaller element than pivot goes left and
        // higher element goes right
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

void printArrayBar(int A[], int size, int lt, int nc, int pi)
{
    system("clear");
    for (int i = 0; i < size; i++) {
        // TODO: print colors to indicate: lesser, greater, not compared, pivot
        // See: https://nl.wikipedia.org/wiki/Quicksort
        // TEST: color
        // TODO: check boundaries for off-by-one, especially for pivot swap
        if (i <= lt) printf("\x1b[37m");           // white=lesser
        if (i > lt && i < nc) printf("\x1b[32m");  // green=greater
        if (i >= nc && i < pi) printf("\x1b[31m"); // red=nc
        if (i == pi) printf("\x1b[30m");           // black=pivot

        bar(A[i]);
        printf("\n");
        printf("\x1b[37m"); // white
    }
    //usleep(200000);
    usleep(usecs);
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
int main(int argc, char *argv[])
{
    int flags, opt;
    //int nsecs, tfnd;

    usecs = 200000;
    tfnd = 0;
    flags = 0;

    while ((opt = getopt(argc, argv, "nt:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            flags = 1;
            break;
        case 't':
            if (!isdigit(optarg[0]))
            {
                printf("Entered input is not a number\n");
                exit(EXIT_FAILURE);
            }
            usecs = atoi(optarg);
            tfnd = 1;
            break;
        default: /* '?' */
            //fprintf(stderr, "Usage: %s [-t usecs] [-n] name\n",
            fprintf(stderr, "Usage: %s [-t usecs]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    printf("flags=%d; tfnd=%d; usecs=%d; optind=%d\n",
           flags, tfnd, usecs, optind);

    if (optind >= argc)
    {
        fprintf(stderr, "Expected argument after options\n");
        //exit(EXIT_FAILURE);
    }

    printf("name argument = %s\n", argv[optind]);

    //exit(EXIT_SUCCESS);


    int arr[] = { 43, 27, 100, 10, 67, 1, 90, 45, 87, 78, 74, 65, 13, 5, 77, 33 };
    arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);
    //printArrayBar(arr, arr_size);
    printf("\n");

    perf p3;
    quickSort(arr, 0, arr_size - 1);
    std::cout << "Elapsed time: " << p3.elapsed() << "s" << std::endl;

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}

