/*
 * MemEater - A simple memory stress testing tool.
 *
 * Written in 2024-2025 by Thamatip Chitpong <tangaming123456@outlook.com>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software. If not, see
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
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
