#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

// executes in-place bogo sort on a given array
static void bogo_sort(int* a, int size);
// returns 1 if given array is sorted and 0 otherwise
static int is_sorted(int* a, int size);
// shuffles the given array into a random order
static void shuffle(int* a, int size);
// print bar
void bar(int value);

int count = 0;

void bogo_sort(int* a, int size) {
    while (!is_sorted(a, size)) {
        
        shuffle(a, size);

        system("clear");
        for (int i = 0; i < size; i++) {
            //printf("%i ", a[i]);
            bar(a[i]);
            //printf(" %i\n", a[i]);
            printf("\n");
        }
        printf("shuffle: %i\n", count++);
        usleep(100000);
        //printf("\n");
        // TODO:
        // clear terminal and print array as bar chart
        // TEST:
        //bar();
    }
}

int is_sorted(int* a, int size) {
    for (int i = 0; i < size-1; i++) {
        if (a[i] > a[i+1]) {
            return 0;
        }
    }
    return 1;
}

void shuffle(int* a, int size) {
    int temp, random;
    for (int i = 0; i < size; i++) {
        random = (int) ((double) rand() / ((double) RAND_MAX + 1) * size);
        temp = a[random];
        a[random] = a[i];
        a[i] = temp;
    }
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

int main() {
    // example usage
    int input[] = { 68, 14, 78, 100, 67, 2 }; //, 45, 90, 87, 78, 65, 74 };
    int size = sizeof(input) / sizeof(*input);

    bogo_sort(input, size);

    // sorted result: 14 45 65 67 68 74 78 78 87 89 90 98
    printf("sorted result:");
    for (int i = 0; i < size; i++) {
        printf(" %d", input[i]);
    }
    printf("\n");

    return 0;
}