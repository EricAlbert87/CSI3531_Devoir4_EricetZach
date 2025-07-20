#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

int simulate_fifo(int pages[], int n, int frames) {
    int mem[10], front = 0, count = 0, i, j, found;
    for (i = 0; i < frames; i++) mem[i] = -1;
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < frames; j++) {
            if (mem[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            mem[front] = pages[i];
            front = (front + 1) % frames;
            count++;
        }
    }
    return count;
}

int simulate_lru(int pages[], int n, int frames) {
    int mem[10], time[10], count = 0, i, j, t = 0, least, pos, found;
    for (i = 0; i < frames; i++) mem[i] = -1;
    for (i = 0; i < n; i++) {
        t++;
        found = 0;
        for (j = 0; j < frames; j++) {
            if (mem[j] == pages[i]) {
                time[j] = t;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (i < frames) {
                mem[i] = pages[i];
                time[i] = t;
            } else {
                least = time[0]; pos = 0;
                for (j = 1; j < frames; j++) {
                    if (time[j] < least) {
                        least = time[j];
                        pos = j;
                    }
                }
                mem[pos] = pages[i];
                time[pos] = t;
            }
            count++;
        }
    }
    return count;
}

int main() {
    int pages[N], i;
    srand(time(NULL));
    for (i = 0; i < N; i++) pages[i] = rand() % 10;

    for (int f = 1; f <= 7; f++) {
        int fifo_faults = simulate_fifo(pages, N, f);
        int lru_faults = simulate_lru(pages, N, f);
        printf("Frames: %d | FIFO: %d | LRU: %d\n", f, fifo_faults, lru_faults);
    }
    return 0;
}
