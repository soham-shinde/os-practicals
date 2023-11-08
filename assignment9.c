#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES];
int work[MAX_RESOURCES];
int safeSequence[MAX_PROCESSES];
int processes, resources;

// Function to check if the process can be allocated or not
int canBeAllocated(int process) {
    for (int j = 0; j < resources; j++) {
        if (need[process][j] > work[j]) {
            return 0;
        }
    }
    return 1;
}

// Function to perform Banker's Algorithm
int bankersAlgorithm() {
    int index = 0;
    for (int i = 0; i < processes; i++) {
        finish[i] = 0;
    }

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    while (index < processes) {
        int found = 0;
        for (int i = 0; i < processes; i++) {
            if (finish[i] == 0 && canBeAllocated(i)) {
                for (int j = 0; j < resources; j++) {
                    work[j] += allocation[i][j];
                }
                safeSequence[index++] = i;
                finish[i] = 1;
                found = 1;
            }
        }
        if (found == 0) {
            return 0;  // System is in an unsafe state
        }
    }

    return 1;  // System is in a safe state
}

// Function to display the current state
void displayState() {
    printf("\nAvailable resources: ");
    for (int i = 0; i < resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Max demand:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("Current allocation:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Need:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int requestResources(int processRequest) {
    int request[MAX_RESOURCES];

    printf("Enter the resource request for Process %d:\n", processRequest);
    for (int i = 0; i < resources; i++) {
        scanf("%d", &request[i]);
    }

    if (processRequest < 0 || processRequest >= processes) {
        printf("Invalid process number.\n");
        return 1;
    }

    // Check if the request is within the need and available limits
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[processRequest][i] || request[i] > available[i]) {
            printf("Resource request exceeds need or available resources. Request denied.\n");
            return 1;
        }
    }

    // Attempt to allocate the resources temporarily
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[processRequest][i] += request[i];
        need[processRequest][i] -= request[i];
    }

    // Check if the system remains in a safe state
    if (bankersAlgorithm()) {
        printf("Resource request granted. System is in a safe state.\n");
    } else {
        printf("Resource request denied. System would be in an unsafe state. Request denied.\n");

        // Rollback the allocation and need values
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[processRequest][i] -= request[i];
            need[processRequest][i] += request[i];
        }
        return 1;
    }

    return 0;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the available instances of each resource:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum demand of each process:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the current allocation of each process:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int choice;
    do {
        printf("\nBanker's Algorithm Menu:\n");
        printf("1. Request additional resources\n");
        printf("2. Display current state\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int processRequest;
        switch (choice) {
            case 1:
                
                printf("Enter the process number requesting resources: ");
                scanf("%d", &processRequest);
                if (requestResources(processRequest) == 0) {
                    displayState();
                }
                break;
            case 2:
                displayState();
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
/*
5 3
ava 3 3 2
max
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

all
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

*/