#ifndef clist
#define clist 
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))
#include <stdlib.h>
struct intrusive_node 
{
  struct intrusive_node *next;
  struct intrusive_node *prev;
};

struct intrusive_list 
{
  struct intrusive_node *head;
};

void init_list(struct intrusive_list*);
void add_node(struct intrusive_list*, struct intrusive_node*);
struct intrusive_node *remove_node(struct intrusive_list*, struct intrusive_node*);

int get_length(struct intrusive_list*);
#endif
