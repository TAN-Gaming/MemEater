#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MEMSIZE_MB_MPLY 1048576UL // 1024 * 1024

int main(int argc, char *argv[])
{
    unsigned long memSizeMB = 0;
    unsigned long memSize;
    void *memPtr;

    printf("Memory allocation testing program\n");

    /* Input memory size in MB from user */
    printf("Enter size in MB: ");
    scanf("%lu", &memSizeMB);

    /* Prevent overflow */
    if (memSizeMB >= ULONG_MAX / MEMSIZE_MB_MPLY)
    {
        printf("ERROR: Invalid memory size.\n");
        return 1;
    }

    memSize = memSizeMB * MEMSIZE_MB_MPLY;

    /* Allocate memory (not used) */
    memPtr = malloc(memSize);
    if (!memPtr)
    {
        printf("ERROR: Memory allocation failed.\n");
        return 1;
    }

    /* Actually use the memory (write data) */
    memset(memPtr, 'A', memSize);
    printf("Allocated memory size=%luMB...\n", memSizeMB);

    /* Hold the memory until user press a key */
    system("pause");

    /* Free allocated memory */
    free(memPtr);
    printf("Memory freed.\n");

    return 0;
}
