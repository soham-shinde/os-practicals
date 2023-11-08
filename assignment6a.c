#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_PATH "myfifo"

int main() {
    char sentence[1024];
    int fifo_fd;
    int res;

    // Create the FIFO (if it doesn't exist)
    mkfifo(FIFO_PATH, 0666);

    // Open the FIFO for writing
    fifo_fd = open(FIFO_PATH, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(1);
    }

    printf("Enter sentences (type 'exit' to quit):\n");

    while (1) {
        printf(">> ");
        fgets(sentence, sizeof(sentence), stdin);

        if (strcmp(sentence, "exit\n") == 0) {
            break;
        }

        // Write the sentence to the FIFO
        res = write(fifo_fd, sentence, strlen(sentence) + 1);
        if (res == -1) {
            perror("Failed to write to FIFO");
            exit(1);
        }
    }

    close(fifo_fd);
    return 0;
}
