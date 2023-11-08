#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Page
{
    int page;
    int lastUsed;
};

bool isPagePresent(struct Page memory[], int page, int frameSize)
{
    for (int i = 0; i < frameSize; i++)
    {
        if (memory[i].page == page)
        {
            return true;
        }
    }

    return false;
}

void displayFrame(struct Page memory[], int frameSize)
{
    for (int i = 0; i < frameSize; i++)
    {
        if (memory[i].page != -1)
        {
            printf(" %d", memory[i].page);
        }
        else
        {
            printf(" -");
        }
    }
    printf("\n");
}

void fcfs(int pages[], int numPage, int frameSize)
{
    struct Page memory[frameSize];

    int pageFalut = 0, index = 0; // index for which page from memory is replace

    // init with empty
    for (int i = 0; i < frameSize; i++)
    {
        memory[i].page = -1;
    }

    for (int i = 0; i < numPage; i++)
    {
        if (!isPagePresent(memory, pages[i], frameSize))
        {
            memory[index].page = pages[i];
            index = (index + 1) % frameSize;
            pageFalut++;
        }
        printf("Page: %d\tMemory: ", pages[i]);
        displayFrame(memory, frameSize);
    }
    printf("\nTotal Page Faults %d, Total Page Hits: %d\n\n", pageFalut, (numPage - pageFalut));
}
void lru(int pages[], int numPage, int frameSize)
{
    struct Page memory[frameSize];
    int pageFault = 0, time = 0; // time variable denote at which index the page is used

    // init empty
    for (int i = 0; i < frameSize; i++)
    {
        memory[i].page = -1;
        memory[i].lastUsed = -1;
    }

    for (int i = 0; i < numPage; i++)
    {
        int j;
        for (j = 0; j < frameSize; j++)
        {
            if (memory[j].page == pages[i])
            {
                memory[j].lastUsed = time++;
                break;
            }
        }
        if (j == frameSize)
        {
            // for decied which page to replace
            int least = 0;
            for (int k = 1; k < frameSize; k++)
            {
                if (memory[k].lastUsed < memory[least].lastUsed)
                {
                    least = k;
                }
            }
            memory[least].page = pages[i];
            memory[least].lastUsed = time++;
            pageFault++;
        }
        printf("Page: %d\tMemory: ", pages[i]);
        displayFrame(memory, frameSize);
    }

    printf("\nTotal Page Faults %d, Total Page Hits: %d\n\n", pageFault, (numPage - pageFault));
}
void optimal(int pages[], int numPage, int frameSize)
{
    struct Page memory[frameSize];
    int pageFault = 0;

    for (int i = 0; i < frameSize; i++)
    {
        memory[i].page = -1;
    }

    for (int i = 0; i < numPage; i++)
    {
        if (!isPagePresent(memory, pages[i], frameSize))
        {
            int farthest = 0;
            int replace = -1;
            
            for (int j = 0; j < frameSize; j++)
            {
                int k;
                for ( k = i+1; k < numPage; k++)
                {
                    if(pages[k]==memory[j].page){
                        if(k>farthest){
                            farthest = k;
                            replace = j;
                        }
                        break;
                    }
                }
                if (k==numPage)
                {
                    replace = j;
                    break;
                }            
            }
            memory[replace].page = pages[i];
            pageFault++;
        }
        printf("Page: %d\tMemory: ", pages[i]);
        displayFrame(memory, frameSize);
    }

    printf("\nTotal Page Faults %d, Total Page Hits: %d\n\n", pageFault, (numPage - pageFault));

}

int main(int argc, char const *argv[])
{
    int pageCount, frameSize;
    printf("\nenter the No. of Pages : ");
    scanf("%d", &pageCount);

    int pages[pageCount];
    printf("\nenter %d Page Numbers : \n",pageCount);
    for (int i = 0; i < pageCount; i++)
        scanf("%d", &pages[i]);

    printf("\nenter Frame Size ");
    scanf("%d", &frameSize);
    optimal(pages, pageCount, frameSize);
    return 0;
}
