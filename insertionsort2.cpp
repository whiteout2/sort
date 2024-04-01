#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/ioctl.h>


// print bar
void bar(int value);

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


template <typename T>
void insertion_sort(std::vector<T> &v)
{
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::rotate(std::upper_bound(v.begin(), i, *i), i, std::next(i));
        // NOTE: lijkt snel maar dat komt omdat we niet elke stap kunnen printen
        // rotate() zet de waarde in een keer op de juiste plek
        // En kun je dit wel een insertion sort noemen? Eerder rotation sort.
        for (auto i: v)
            std::cout << i << ' ';
        std::cout << std::endl;
        //printArrayBar(&v[0], v.size());
    }
}

int main()
{
    std::vector<int> vec{ 43, 27, 100, 10, 67, 1, 90, 45, 87, 78, 74, 65, 13, 5, 77, 33 };
    insertion_sort(vec);
    for (auto i: vec)
        std::cout << i << ' ';
    std::cout << std::endl;
}