// C program for Quick Sort
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <chrono>
#include <iostream>
#include <utility>

int arr_size = 0;
void printArray(int A[], int size);
void printArrayBar(int A[], int size);
// print bar
void bar(int value);


struct perf {
    std::chrono::steady_clock::time_point start_;
    perf() : start_(std::chrono::steady_clock::now()) {}
    double elapsed() const {
        auto stop = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = stop - start_;
        return elapsed_seconds.count();
    }
};

// See: https://web.archive.org/web/20120219000149/http://www.sorting-algorithms.com/static/QuicksortIsOptimal.pdf
// Quicksort with 3-way partitioning
void quicksort(int a[], int l, int r)
{ 
    int i = l-1, j = r, p = l-1, q = r;
    int v = a[r];
    if (r <= l) return;
    for (;;) {
        while (a[++i] < v) ;
        while (v < a[--j]) if (j == l) break;
        if (i >= j) break;
        std::swap(a[i], a[j]);
        printArrayBar(a, arr_size);
        if (a[i] == v) { p++; std::swap(a[p], a[i]); printArrayBar(a, arr_size); }
        if (v == a[j]) { q--; std::swap(a[j], a[q]); printArrayBar(a, arr_size); }
    }
    std::swap(a[i], a[r]); 
    printArrayBar(a, arr_size);
    j = i-1; i = i+1;
    for (int k = l;   k < p; k++, j--) { std::swap(a[k], a[j]); printArrayBar(a, arr_size); }
    for (int k = r-1; k > q; k--, i++) { std::swap(a[i], a[k]); printArrayBar(a, arr_size); }
    quicksort(a, l, j);
    quicksort(a, i, r);
}

// Function to print an array
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void printArrayBar(int A[], int size)
{
    system("clear");
    for (int i = 0; i < size; i++) {
        bar(A[i]);
        printf("\n");
    }
    usleep(200000);
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
    int arr[] = { 43, 27, 100, 10, 67, 1, 90, 45, 87, 78, 74, 65, 13, 5, 77, 33 };
    arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);
    printArrayBar(arr, arr_size);
    printf("\n");

    perf p3;
    quicksort(arr, 0, arr_size - 1);
    std::cout << "Elapsed time: " << p3.elapsed() << "s" << std::endl;

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}

