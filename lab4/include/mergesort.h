#ifndef __mergesort
#define __mergesort 
int mergesort (void*, size_t, size_t, int (*compar)(const void*,const void*));
void copy(void*, size_t, size_t, void*, size_t);
void merge(void*, size_t, int (*compar)(const void*,const void*), size_t, size_t, size_t, size_t, void*);
#endif
