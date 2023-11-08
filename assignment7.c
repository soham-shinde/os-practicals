#include <stdio.h>
#include <stdlib.h>

// Function to sort the array in ascending order
void sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Shortest Seek Time First (SSTF) Disk Scheduling Algorithm
void sstf(int requestQueue[], int size, int initialHead) {
    int seekSequence[size];
    int visited[size];

    for (int i = 0; i < size; i++) {
        seekSequence[i] = -1;
        visited[i] = 0;
    }

    int currentPosition = initialHead;
    int totalSeekTime = 0;

    for (int i = 0; i < size; i++) {
        int minSeek = 1000000;
        int nextIndex = -1;

        for (int j = 0; j < size; j++) {
            if (!visited[j]) {
                int seek = abs(currentPosition - requestQueue[j]);
                if (seek < minSeek) {
                    minSeek = seek;
                    nextIndex = j;
                }
            }
        }

        visited[nextIndex] = 1;
        seekSequence[i] = requestQueue[nextIndex];
        totalSeekTime += minSeek;
        currentPosition = requestQueue[nextIndex];
    }

    printf("SSTF Seek Sequence: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

// SCAN Disk Scheduling Algorithm
void scan(int requestQueue[], int size, int initialHead) {
    int seekSequence[size];
    int visited[size];

    for (int i = 0; i < size; i++) {
        seekSequence[i] = -1;
        visited[i] = 0;
    }

    int totalSeekTime = 0;
    int currentIndex = 0;

    sort(requestQueue, size);

    // Moving towards the end
    for (int i = 0; i < size; i++) {
        if (requestQueue[i] > initialHead) {
            currentIndex = i;
            break;
        }
    }

    int left = currentIndex - 1;
    int right = currentIndex;
    int i = 0;

    while (left >= 0 || right < size) {
        if (i % 2 == 0) {
            if (left >= 0) {
                seekSequence[i] = requestQueue[left];
                totalSeekTime += abs(initialHead - requestQueue[left]);
                initialHead = requestQueue[left];
                left--; 
            } else {
                seekSequence[i] = requestQueue[right];
                totalSeekTime += abs(initialHead - requestQueue[right]);
                initialHead = requestQueue[right];
                right++;
            }
        } else {
            if (right < size) {
                seekSequence[i] = requestQueue[right];
                totalSeekTime += abs(initialHead - requestQueue[right]);
                initialHead = requestQueue[right];
                right++;
            } else {
                seekSequence[i] = requestQueue[left];
                totalSeekTime += abs(initialHead - requestQueue[left]);
                initialHead = requestQueue[left];
                left--;
            }
        }
        i++;
    }

    printf("SCAN Seek Sequence: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

// C-Look Disk Scheduling Algorithm
void clook(int requestQueue[], int size, int initialHead) {
    int seekSequence[size];
    int visited[size];

    for (int i = 0; i < size; i++) {
        seekSequence[i] = -1;
        visited[i] = 0;
    }

    int totalSeekTime = 0;
    int currentIndex = 0;

    sort(requestQueue, size);

    // Moving towards the end
    for (int i = 0; i < size; i++) {
        if (requestQueue[i] > initialHead) {
            currentIndex = i;
            break;
        }
    }

    int right = currentIndex;
    int i = 0;

    while (right < size) {
        seekSequence[i] = requestQueue[right];
        totalSeekTime += abs(initialHead - requestQueue[right]);
        initialHead = requestQueue[right];
        right++;
        i++;
    }

    for (int j = 0; j < currentIndex; j++) {
        seekSequence[i] = requestQueue[j];
        totalSeekTime += abs(initialHead - requestQueue[j]);
        initialHead = requestQueue[j];
        i++;
    }

    printf("C-Look Seek Sequence: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

int main() {
    int requestQueue[] = {82,170,43,140,24,16,190};
    int size = sizeof(requestQueue) / sizeof(requestQueue[0]);
    int initialHead = 50;

    sstf(requestQueue, size, initialHead);
    scan(requestQueue, size, initialHead);
    clook(requestQueue, size, initialHead);

    return 0;
}
