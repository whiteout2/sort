#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <utility>
#include <chrono>
#include <iostream>

void printArray(int arr[], int size);
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



// https://en.wikipedia.org/wiki/Insertion_sort
// Simple implementation: Jon Bentley shows a three-line C/C++ version that is five lines
// when optimized.[1]

/* Simplest insertion sort */
void isort1(int x[], int n)
{       
    int i, j;
    for (i = 1; i < n; i++)
        for (j = i; j > 0 && x[j-1] > x[j]; j--) {
            //std::swap(j-1, j); // NOTE: there is an error in the Programming Pearls book
            std::swap(x[j-1], x[j]);
            //printArray(arr, size);
            printArrayBar(x, n);
        }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
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

int main()
{
    int arr[] = { 43, 27, 100, 10, 67, 1, 90, 45, 87, 78, 74, 65, 13, 5, 77, 33 };
    int size = sizeof(arr) / sizeof(arr[0]);
    perf p3;
    isort1(arr, size);
    std::cout << "Elapsed time: " << p3.elapsed() << "s" << std::endl;
    printArray(arr, size);
}
