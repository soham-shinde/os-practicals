#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_PATH "myfifo"
#define OUTPUT_FILE "output.txt"

int main() {
    char sentence[1024];
    int fifo_fd;
    int output_fd;
    int res;
    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;

    // Create the FIFO (if it doesn't exist)
    mkfifo(FIFO_PATH, 0666);

    // Open the FIFO for reading
    fifo_fd = open(FIFO_PATH, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for reading");
        exit(1);
    }

    // Open the output file for writing
    output_fd = open(OUTPUT_FILE, O_WRONLY | O_CREAT, 0644);
    if (output_fd == -1) {
        perror("Failed to open output file");
        exit(1);
    }

    while (1) {
        // Read a sentence from the FIFO
        res = read(fifo_fd, sentence, sizeof(sentence));

        if (res == 0) {
            break;
        }

        // Process the sentence
        charCount += strlen(sentence);
        wordCount++;

        for (int i = 0; sentence[i] != '\0'; i++) {
            if (sentence[i] == '\n') {
                lineCount++;
            }
        }

        // Write the sentence to the output file
        write(output_fd, sentence, strlen(sentence));
    }

    printf("Character Count: %d\n", charCount);
    printf("Word Count: %d\n", wordCount);
    printf("Line Count: %d\n", lineCount);

    close(fifo_fd);
    close(output_fd);

    return 0;
}
