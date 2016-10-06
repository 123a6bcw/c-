#include <stdlib.h>
#include <stdio.h>

int main()
{
    void *a = malloc(10);
    a = NULL;
    
    void *b = malloc(20);
    
    int *c = malloc(30);
    free(c);
    
    printf("%i\n", *c);
    
    printf("try valgrind\n");
    return 0;
}
