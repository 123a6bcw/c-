#include <stdio.h>
#include <string.h>
#include <expat.h>
#include <time.h>
#include <ctype.h>
#include "../include/names.h"
#include "../include/phonebook.h"

#define BUFFER_SIZE 1000

void push_back_human(phonebook_t *book, human_t *human)
{
    if (book->size == book->capacity)
    {
        book->capacity *= 2;
        book->humans = realloc(book->humans, book->capacity * sizeof(human_t));
    }
    book->humans[book->size] = *human;
    book->size++;
}

static int new_phone = 0;

void start_element(void *data, const char *element, const char **attribute) 
{
    if (strcmp(element, "human") == 0)
    {
        human_t human;
	    size_t len = strlen((char *)attribute[1]);
	    char *name_copy = malloc((len + 1) * sizeof(char));
	    strcpy(name_copy, (char *)attribute[1]);
	    name_copy[len] = '\0';
	    strcpy(human.name, strtok(name_copy, " "));
	    strcpy(human.middle_name, strtok(NULL, " "));
	    strcpy(human.family_name, strtok(NULL, " "));
	    for (size_t i = 0; i < 10; i++)
	    {
	        human.phones[i][0] = '\0';
	    }
	    push_back_human(data, &human);
	    free(name_copy);
    } else
    if (strcmp(element, "phone") == 0)
    {
        new_phone = 1;
    }
}

void end_element(void *data, const char *element)
{
}

void handle_data(void *data, const char *content, int length)
{
    if (length > 0 && new_phone) 
    {
		char *phone = malloc((length + 1) * sizeof(char));
		memcpy(phone, content, length * sizeof(char));		
		phone[length] = '\0';
		human_t *human = &(((phonebook_t *)data)->humans[((phonebook_t *)data)->size - 1]);
	    for (size_t j = 0; j < 10; j++)
	    {
	        if (human->phones[j][0] == '\0')
	        {
	            strcpy(human->phones[j], phone);
	            break;
	        }
		}
		new_phone = 0;
		free(phone);
	}
}

int human_cmp(const void *a, const void *b)
{
    return strcmp(((human_t*) a)->family_name, ((human_t*) b)->family_name);
}

int load_phonebook_xml(const char *filename, phonebook_t *book)
{
    char buff[BUFFER_SIZE];
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        printf("Failed to open file\n");
        return 1;
    }

    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
    XML_SetUserData(parser, book);

    memset(buff, 0, BUFFER_SIZE);

    size_t len = 0;
    int done = 0;
    do 
    {
        len = fread(buff, sizeof(char), BUFFER_SIZE, fp);
        done = len < BUFFER_SIZE;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) 
        {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            XML_ParserFree(parser);
            fclose(fp);
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);
    
    qsort(book->humans, book->size, sizeof(human_t), human_cmp);
    return 0;
}

int save_phonebook_xml(const char *filename, phonebook_t *book)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) 
    {
        printf("Failed to open file\n");
        return 1;
    }
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp, "<phonebook>\n");
    for (size_t i = 0; i < book->size; i++)
    {
        fprintf(fp, "\t<human name=\"%s %s %s\">\n", book -> humans[i].name, book -> humans[i].middle_name, book -> humans[i].family_name);
        for (size_t j = 0; j < 10 && book->humans[i].phones[j][0] != '\0'; j++)
        {    
            fprintf(fp, "\t\t<phone>%s</phone>\n", book->humans[i].phones[j]);
        }
        fprintf(fp, "\t</human>\n");
    }
    fprintf(fp, "</phonebook>");
    fclose(fp);
    return 0;
}

void print_phonebook(phonebook_t *book)
{
    printf("%lu\n", book->size);
    for (size_t i = 0; i < book->size; i++)
    {
        printf("name: %s\n", book->humans[i].name);
        printf("middle name: %s\n", book->humans[i].middle_name);
        printf("family name: %s\n", book->humans[i].family_name);
        for (size_t j = 0; j < 10 && book->humans[i].phones[j][0] != '\0'; j++)
        {
            printf("phone: %s\n", book->humans[i].phones[j]);
	    }
	    
	    if (i < book->size - 1)
	    {
	        printf("\n");
	    }
    }
}

void clear_phonebook(phonebook_t *book)
{
    free(book->humans);
    book->capacity = 1;
    book->size = 0;
}

void init_phonebook(phonebook_t *book)
{
	book->size = 0;
	book->capacity = 1;
	book->humans = malloc(sizeof(human_t));
}

void gen_phonebook(phonebook_t *book, size_t sz)
{
	clear_phonebook(book);
	init_phonebook(book);
    for (size_t i = 0; i < sz; i++)
    {
        human_t human;
        size_t phone_num = 1 + rand() % 9;
        for (size_t j = 0; j < phone_num; j++)
        {
            size_t phone_len = 1 + rand() % 20;
            for (size_t k = 0; k < phone_len; k++)
            {
                human.phones[j][k] = '0' + rand() % 10;
            }
            human.phones[j][phone_len] = '\0';
        }
        human.phones[phone_num][0] = '\0';
        strcpy(human.name, kNames[rand() % NAMES_CNT]);
        strcpy(human.family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
        strcpy(human.middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
        push_back_human(book, &human);
    }
}
