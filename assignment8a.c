#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shared_memory_key", 65); // Generate a unique key

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666); // Create a shared memory segment
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    char *shmaddr = shmat(shmid, NULL, 0); // Attach to the shared memory
    if (shmaddr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Write a message to the shared memory
    char message[] = "Hello, shared memory!";
    strcpy(shmaddr, message);

    printf("Message written to shared memory by the server: %s\n", shmaddr);

    shmdt(shmaddr); // Detach from the shared memory

    return 0;
}
