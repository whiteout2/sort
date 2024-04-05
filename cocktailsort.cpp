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


// See: https://www.geeksforgeeks.org/cocktail-sort/
void CocktailSort(int a[], int n)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;
 
    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;
 
        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
                printArrayBar(a, arr_size, 0, 0, i);
                swapped = true;
            }
        }
 
        // if nothing moved, then array is sorted.
        if (!swapped)
            break;
 
        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;
 
        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;
 
        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
                printArrayBar(a, arr_size, 0, 0, i);
                swapped = true;
            }
        }
 
        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
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
        //if (i > lt && i < nc) printf("\x1b[32m");  // green=greater
        //if (i >= nc && i < pi) printf("\x1b[31m"); // red=nc
        //if (i == pi) printf("\x1b[30m");           // black=pivot
        if (i == pi) printf("\x1b[31m");

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
    //int arr[] = { 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33 };
    //int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    //int arr[] = { 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);
    //printArrayBar(arr, arr_size);
    printf("\n");

    perf p3;
    CocktailSort(arr, arr_size);
    std::cout << "Elapsed time: " << p3.elapsed() << "s" << std::endl;

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}

