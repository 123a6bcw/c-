#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mergesort.h"

int compare_int(const void *a, const void *b)
{
    return *((int*)(a)) < *((int*)(b));
}

int compare_char(const void *a, const void *b)
{
    return *((char*)(a)) < *((char*)(b));
}

int compare_string(const void *a, const void *b)
{
    return strcmp((char*)(a), (char*)(b)) < 0;
}

int main(int argc, char* argv[])
{ 
    int (*compar)(const void*,const void*);
    size_t size = 0;
    
    if (strcmp(argv[1], "int") == 0)
    {
        compar = compare_int;
        size = sizeof(int);
    } else
    if (strcmp(argv[1], "char") == 0)
    {
        compar = compare_char;
        size = sizeof(char);
    } else
    if (strcmp(argv[1], "str") == 0)
    {
        compar = compare_string;
        
        for (size_t i = 2; i < argc; i++)
        {
            size_t calc;
            for (calc = 0; argv[i][calc] != '\0'; calc++);
            
            if (calc + 1 > size)
            {
                size = calc + 1;
            }
        }
        
        size *= sizeof(char);
    }

    size_t num = argc - 2;
    void *a = malloc(num * size);
    for (size_t i = 0; i < num; i++)
    {
        if (strcmp(argv[1], "int") == 0)
        {
             *((int*)((char*)a + i * size)) = atoi(argv[i + 2]);     
        } else
        if (strcmp(argv[1], "char") == 0)
        {
            *((char*)a + i * size) = *(argv[i + 2]);
        } else
        if (strcmp(argv[1], "str") == 0)
        {
            for (size_t j = 0; j < size; j++)
            {
                *((char*)a + i * size + j) = argv[i + 2][j];
            }
        }
    }
    
    mergesort(a, num, size, compar);
    for (size_t i = 0; i < num; i++)
    {
        if (strcmp(argv[1], "int") == 0)
        {
            printf("%i ", *((int*)((char*)a + i * size)));
        } else
        if (strcmp(argv[1], "char") == 0)
        {
            printf("%c ", *((char*)a + i * size));
        } else
        if (strcmp(argv[1], "str") == 0)
        {
            printf("%s ", (char*)a + i * size);
        }
    }
    
    printf("\n");
    free(a);
    return 0;
}
