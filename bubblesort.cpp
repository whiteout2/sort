#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int arr_size = 0;
void printArray(int A[], int size);
void printArrayBar(int A[], int size);
// print bar
void bar(int value);


void bubblesort(int invoer[], int lengte) 
 {
    int i, j, tijdelijk;
    for (j = 0; j < lengte; j++) 
    {
       for (i = 1; i < lengte - j; i++) 
       {
          if(invoer[i-1] > invoer[i]) 
          {
             tijdelijk = invoer[i];
             invoer[i] = invoer[i-1];
             invoer[i-1] = tijdelijk;
             printArrayBar(invoer, lengte);
          }
       }
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

    bubblesort(arr, arr_size);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
