#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "../include/phonebook.h"

int main(int argc, char* argv[]){
    srand(time(NULL));
    phonebook_t book;
    init_phonebook(&book);  
    int result = load_phonebook_xml(argv[1], &book);
    if (result)
    {
        printf("Failed to load phonebook\n");
    }
    print_phonebook(&book);
    gen_phonebook(&book, rand() % 10);
    result = save_phonebook_xml(argv[2], &book);
    if (result)
    {
        printf("Failed to save phonebook\n");
    }
    clear_phonebook(&book);
    return 0;
}
