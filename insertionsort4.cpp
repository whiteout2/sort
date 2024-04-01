#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
//#include <utility>
#include <iostream>
#include <vector>

void printArray(int arr[], int size);
void printArrayBar(int A[], int size);
// print bar
void bar(int value);


/* 
void insertionSort(int arr[], int size)
{
    int i, j, key;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            //printArray(arr, size);
            printArrayBar(arr, size);
            j = j - 1;
        }
        arr[j + 1] = key;
        //printArray(arr, size);
        printArrayBar(arr, size);
    }
}
*/


// https://en.wikipedia.org/wiki/Insertion_sort
// Simple implementation: Jon Bentley shows a three-line C/C++ version that is five lines
// when optimized.[1]

/* Simplest insertion sort */
/*
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
*/

template <typename T>
void insertion_sort(std::vector<T> &v)
{
	for (int i=1; i<v.size(); i++) {
		// de i eerste elementen staan reeds in volgorde
		T hulp = v[i]; // we halen het i-de element er uit.
		int j=i-1;
		while (j>=0 && hulp<v[j]) {
			// alle elementen groter dan het i-de element worden 1 plaats naar rechts opgeschoven
			v[j+1] = v[j];
			j--;
            printArrayBar(&v[0], v.size());
		}
		v[j+1] = hulp; // we voegen het uitgehaalde in op zijn juiste plaats.
        printArrayBar(&v[0], v.size());
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
    //int arr[] = { 43, 27, 100, 10, 67, 1, 90, 45, 87, 78, 74, 65, 13, 5, 77, 33 };
    //int size = sizeof(arr) / sizeof(arr[0]);
    std::vector<int> vec{ 43, 27, 100, 10, 67, 1, 90, 45, 87, 78, 74, 65, 13, 5, 77, 33 }; 
    //insertionSort(arr, size);
    //isort1(arr, size);
    insertion_sort(vec);
    //printArray(arr, size);
    for (auto i: vec)
        std::cout << i << ' ';
    std::cout << std::endl;
}
