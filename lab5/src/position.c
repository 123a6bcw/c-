#include "../include/clist.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct position_node
{
  int x, y;
  struct intrusive_node node;
};

void remove_position(struct intrusive_list *l, int x, int y)    
{ 
    if (l -> head == NULL)
    {
        return;
    }
    
    int head_steps = 0;
    struct intrusive_node *ptr = l -> head -> next;
    do
    {
        if (ptr == l -> head)
        {
            head_steps++;
        }
        
        struct position_node *item = container_of(ptr, struct position_node, node);
        
        if (item -> x == x && item -> y == y)
        {
            ptr = remove_node(l, ptr);
            free(item);
        } else
        {
            ptr = ptr -> next;
        }
    } while (ptr != NULL && head_steps < 1);
    
    return;
}

void add_positon(struct intrusive_list *l, int x, int y) 
{
     struct position_node *new_point = malloc(sizeof(*new_point));  
     add_node(l, &(new_point -> node));
          
     new_point -> x = x;
     new_point -> y = y;
     return;
}

void show_all_positions(struct intrusive_list *l) 
{
    if (l -> head == NULL)
    {
        printf("\n");
        return;
    }
    
    struct intrusive_node *ptr = l -> head;
    do
    {
        struct position_node *item = container_of(ptr, struct position_node, node);
        
        printf("(%i %i)", item -> x, item -> y);
        if (ptr -> next != l -> head)
        {
            printf(" ");
        }
        
        ptr = ptr -> next;
    } while (ptr != l -> head);
    
    printf("\n");
    return;
}

void remove_all_positions(struct intrusive_list *l) 
{
    if (l -> head == NULL)
    {
        return;
    }
    
    struct intrusive_node *ptr = l -> head;
    do
    {
        struct position_node *item = container_of(ptr, struct position_node, node);    
        ptr = remove_node(l, ptr);
        free(item);       
    } while (ptr != NULL);
}
