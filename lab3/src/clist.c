#include "../include/clist.h"

void init_list(struct intrusive_list *l)
{
    l -> head = NULL; 
}

void add_node(struct intrusive_list *l, struct intrusive_node *n)
{
    if (l -> head == NULL)
    {
        n -> next = n;
        n -> prev = n;
        l -> head = n;
        return;
    }
    
    n -> next = l -> head;
    n -> prev = l -> head -> prev;
    l -> head -> prev -> next = n;
    l -> head -> prev = n;
    
    l -> head = n;
    return;
}

struct intrusive_node *remove_node(struct intrusive_list *l, struct intrusive_node *n)
{
    if (n == l -> head)
    {
        if (l -> head -> next == l -> head)
        {
            free(l -> head);
            l -> head = NULL;
            return NULL;
        }
        
        struct intrusive_node *new_head = l -> head -> next;
        free(l -> head);
        l -> head = new_head;
        return new_head;
    }
    
    struct intrusive_node *return_value = n -> next;
    
    (n -> prev) -> next = n -> next;
    (n -> next) -> prev = n -> prev;
    free(n); 
    
    return return_value;
}

int get_length(struct intrusive_list *l)
{
    if (l -> head == NULL)
    {
        return 0;
    }
    
    int len = 0;
    struct intrusive_node *ptr = l -> head;
    do
    {
        len++;
        ptr = ptr -> next;
    } while (ptr != l -> head);
    
    return len;
}
