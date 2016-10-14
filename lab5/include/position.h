#ifndef _position
#define _position
struct position_node
{
  int x, y;
  struct intrusive_node node;
};

void remove_position(struct intrusive_list *, int, int); 
void add_positon(struct intrusive_list *, int, int); 
void show_all_positions(struct intrusive_list *);  
void remove_all_positions(struct intrusive_list *); 
#endif
