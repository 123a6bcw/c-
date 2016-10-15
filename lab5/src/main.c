#include "../include/clist.h"
#include "../include/position.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int readtext(int *points, int *n, FILE *f)
{
    return fscanf(f, "%d%d", points + (*n), points + (*n) + 1);
}

int readbin(int *points, int *n, FILE *f)
{
    for (int times = 0; times <= 1; times++)
    {
        if (fread((char*)(points + (*n) + times), sizeof(char), 3, f) == 0)
        {
            return 0;
        }
        
        *((char*)(points + (*n) + times) + 3) = 0;
    }
    
    return 1;
}

int *load(char *open_type, char *file_name, int *n, int(*readfunc)(int *, int *, FILE *))
{
    FILE *f = fopen(file_name, open_type);  
    size_t np = 2;
    int *points = malloc(np * sizeof(int));
    while (1)
    {
        if ((*n) >= np)
        {
            points = realloc(points, 2 * np * sizeof(int)); 
            np *= 2;
        }
        
        if (readfunc(points, n, f) <= 0)
        {
            break;
        }
          
        (*n) += 2;
    }    
    
    fclose(f);    
    return points;
}

void savebin(char *file_name, int *points, int n)
{
	FILE *f = fopen(file_name, "wb");
	for (int i = 0; i < n; i++)
	{
	    fwrite((char*)(points + i), sizeof(char), 3, f);
	}
	fclose(f);
}

void savetext(char *file_name, int *points, int n)
{
	FILE *f = fopen(file_name, "wt");
	for (int i = 0; i < n; i += 2)
	{
	    fprintf(f, "%d %d\n", *(points + i), *(points + i + 1));
	}
	fclose(f);
}

void count(struct position_node *p, void *calc)
{
	(*(int*)calc)++;
}

void print(struct position_node *p, void *format_string)
{
	printf((char*)format_string, p -> x, p -> y);
}

void apply(struct intrusive_list *l, void (*op)(struct position_node *, void *), void *data)
{
	if (l -> head == NULL)
	{
	    return;
	}
		
	struct intrusive_node *ptr = l -> head -> prev;
	
	while (ptr != l -> head)
	{
		op(container_of(ptr, struct position_node, node), data);
		ptr = ptr -> prev;
	}
	
	op(container_of(l -> head, struct position_node, node), data);
}

int main(int argc, char* argv[]) 
{
    if (argc <= 3)
    {
        return 0;
    }
    
    struct intrusive_list l;
    init_list(&l);
    
    int n = 0;
    int *points;  
    if (strcmp(argv[1], "loadtext") == 0)
    {
        points = load("rt", argv[2], &n, readtext);
    } else
    if (strcmp(argv[1], "loadbin") == 0)
    {
        points = load("rb", argv[2], &n, readbin);
    }
    
    for (int i = 0; i < n; i += 2)
    {
        add_positon(&l, *(points + i), *(points + i + 1));
    }
    
    if (strcmp(argv[3], "savetext") == 0)
    {
		savetext(argv[4], points, n);
	} else
	if (strcmp(argv[3], "savebin") == 0)
	{
		savebin(argv[4], points, n);
	} else
	if (strcmp(argv[3], "print") == 0)
	{
		apply(&l, print, argv[4]);
		printf("\n");
	} else
    if (strcmp(argv[3], "count") == 0)
    {
		int ans = 0;
		apply(&l, count, &ans);
		printf("%d\n", ans);
	}

	free(points);
	remove_all_positions(&l);  
    return 0;
}
