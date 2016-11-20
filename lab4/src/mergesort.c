#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

void copy(void *source, size_t size, size_t i, void *destination, size_t dest_i)
{
    for (size_t sz = 0; sz < size; sz++)
    {
        *((char*)destination + dest_i * size + sz) = *((char*)source + i * size + sz);
    }

    return;
}

void merge(void *source, size_t size, int (*compar)(const void*,const void*), size_t l1, size_t r1, size_t l2, size_t r2, void *destination)
{
    size_t i = l1;
    size_t j = l2;
    size_t dest_i = l1;
    while (i <= r1 && j <= r2)
    {
        size_t min;
        if ((*compar)((void*)((char*)source + i * size), (void*)((char*)source + j * size)))
        {
            min = i;
            i++;
        } else
        {
            min = j;
            j++;
        }

        copy(source, size, min, destination, dest_i);
        dest_i++;
    }

    if (j <= r2)
    {
        i = j;
        r1 = r2;
    }

    for (; i <= r1; i++)
    {
        copy(source, size, i, destination, dest_i);
        dest_i++;
    }

    return;
}

int mergesort (void *base, size_t num, size_t size, int (*compar)(const void*,const void*))
{
    void *auxiliary = malloc(num * size);
    
    size_t k;
    for (k = 1; (1 << (k - 1)) <= num; k++)
    {
        for (size_t i = 0; i < num; i += (1 << k))
        {
            size_t right = i + (1 << k) - 1;
            size_t middle = (i + right) / 2;
            if (right >= num)
            {
                right = num - 1;
                middle = i + (1 << (k - 1)) - 1;
            }
            
            if (middle < right)
            {
                merge(base, size, compar, i, middle, middle + 1, right, auxiliary);
            } else
            {
                for (size_t j = i; j < num; j++)
                {
                    copy(base, size, j, auxiliary, j);
                }
            }
        }

        void *swap = auxiliary;
        auxiliary = base;
        base = swap;
    }
    
    if (k % 2 == 0)
    {
        for (int i = 0; i < num; i++)
        {
            copy(base, size, i, auxiliary, i);
        }
        
        void *swap = auxiliary;
        auxiliary = base;
        base = swap;
    } 

    free(auxiliary);
    return 0;
}
