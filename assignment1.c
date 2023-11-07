#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int z = 0; z < n1; z++)
    {
        L[z] = arr[z + l];
    }
    for (int z = 0; z < n2; z++)
    {
        R[z] = arr[z + m + 1];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


void bubbleSort(int arr[],int n){
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j]>arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            
        }
        
    }
    
}


void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", arr[i]);
    }

    printf("\n");
}

int main()
{
    int n;
    int arr[1000];
    printf("Enter the no. of element : ");
    scanf("%d",&n);

    
    printf("Enter %d elements : \n",n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    
    int childPid = fork();

    if(childPid == 0){
        printf("\nChild Process: \nBubble Sort :");
        bubbleSort(arr,n);
        printf("\nChild Process End");
    }
    else if(childPid>0){
        printf("\nParent Process: \nMerge Sort : ");
        mergeSort(arr,0,n-1);
        printf("\nMerge Sort completed");
        

        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("\nChild process Exited %d",WEXITSTATUS(status));
        }
    }
    else{
        perror("\nerror fork");
        exit(1);
    }

    printf("\nSorted array \n ");
    printArray(arr,n);
    return 0;
}
