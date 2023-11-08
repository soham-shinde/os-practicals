#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shared_memory_key", 65); // Generate the same unique key

    int shmid = shmget(key, SHM_SIZE, 0666); // Get the shared memory segment
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    char *shmaddr = shmat(shmid, NULL, 0); // Attach to the shared memory
    if (shmaddr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Read the message from shared memory and display it
    printf("Message read from shared memory by the client: %s\n", shmaddr);

    shmdt(shmaddr); // Detach from the shared memory

    return 0;
}
