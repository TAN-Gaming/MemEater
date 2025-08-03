/*
 * Author: Thamatip Chitpong, 2024-2025
 *
 * SPDX-License-Identifier: 0BSD
 * License-Filename: LICENSE.txt
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMSIZE_MB_MPLY ((size_t)1048576) // 1024 * 1024

void app_pause(const char *message)
{
    int key;

    printf("%s", message);
    getchar(); // Fix leftovers

    /* NOTE: Press ENTER key to continue */
    do
    {
        key = getchar();

    } while (key != EOF && key != '\r' && key != '\n');
}

int main(int argc, char *argv[])
{
    size_t memSizeMB = 0;
    size_t memSize;
    void *memPtr;

    printf("Memory allocation testing program\n");

    /* Input memory size in MB from user */
    printf("Enter size in MB: ");
#ifdef _WIN32
    scanf("%Iu", &memSizeMB);
#else
    scanf("%zu", &memSizeMB);
#endif

    /* Prevent overflow */
    if (memSizeMB >= SIZE_MAX / MEMSIZE_MB_MPLY)
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
#ifdef _WIN32
    printf("Allocated memory size=%IuMB.\n", memSizeMB);
#else
    printf("Allocated memory size=%zuMB.\n", memSizeMB);
#endif

    /* Hold the memory until user press ENTER key */
    app_pause("Press ENTER key to exit...");

    /* Free allocated memory */
    free(memPtr);
    printf("Memory freed.\n");

    return 0;
}
