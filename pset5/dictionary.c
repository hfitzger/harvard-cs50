/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"


typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;


node* hashtable[HASHTABLE_SIZE];


unsigned int word_amt = 0;


bool loaded = false;

int hash_word(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}


bool check(const char* word)
{

    int leng = strlen(word);
    char copy_word[leng + 1];
    

    for (int i = 0; i < leng; i++)
    {
       copy_word[i] = tolower(word[i]);
    }
    

    copy_word[leng] = '\0';
    

    int h = hash_word(copy_word);
    

    node* cursor = hashtable[h];
    

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, copy_word) == 0)
        {

            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

bool load(const char* dictionary)
{

    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }
    

    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    while (true)
    {
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Could not malloc a new node.\n");
            return false;
        }
        
        fscanf(fp, "%s", new_node->word);
        new_node->next = NULL;
        
        if (feof(fp))
        {
            free(new_node);
            break;
        }

        word_amt++;
        
        int h = hash_word(new_node->word);
        node* head = hashtable[h];
        
        if (head == NULL)
        {
            hashtable[h] = new_node;
        }
        else
        {
            new_node->next = hashtable[h];
            hashtable[h] = new_node;
        }
    }
    fclose(fp);
    loaded = true;
    return true;
}


unsigned int size(void)
{
    if (loaded)
    {
        return word_amt;
    }
    else
    {
        return 0;
    }
}


bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node* cursor = hashtable[i];
        while (cursor != NULL)
        {
            // maintain connection to linked list using temp
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    loaded = false;
    return true;
}
