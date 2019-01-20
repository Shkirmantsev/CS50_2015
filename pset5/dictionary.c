/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"
#define TABLESIZE 27
#define LENGTH_ 45



/**
 * Returns true if word is in dictionary else false.
 */
 
 // number of loaded words
unsigned int words_=0;

 
 // marker of load function
bool loaded_=false;

 // create structure
        typedef struct node
    {
        bool is_word;
        //char data;
        int level;
        struct node* children[TABLESIZE];
    } node;

// create tree's root
   
    
    node* createNode(void)
    {
        return (node*) calloc(1, sizeof(node));
    }
    node* root=NULL;

bool check(const char* word)
{
    // create cursor(crawler)
    
    node *crawler=root;
    unsigned int cw=0;
    unsigned int i=0;
    cw=word[i];
    while(cw!='\0')
    {
        
        if(isalpha(cw) )
        {
          cw=toupper(cw);
        }
        
        if ((cw>=65 && cw<=90) || cw=='\'')
        {
            if (cw=='\'')
            {
                cw=65+TABLESIZE-1;
            }
            
            if (crawler->children[cw-65]==NULL)
            {
                return false;
            }
            else
            {
                 crawler=crawler->children[cw-65];
            }
        }
       i++;
       cw=word[i]; 
    }
    return crawler->is_word;
}



    
/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    
    
     
    // !!!!!! feeling the tree !!!!!
    
    // step 1 - open dictionary fore reading
    
    
    
    
    FILE* fpd=fopen(dictionary, "r");
    if (fpd==NULL)
    {
        printf("culd not open %s.\n",dictionary);
        fclose(fpd);
        return false;
    }
    //feel the root
    root=createNode();
    int tmpc=0;
    int c=0;
    node* cursor=root;
    while(tmpc != EOF)
    {
        tmpc = fgetc(fpd);
        c=toupper(tmpc);
        if(c != '\n' && c != EOF)
        {
            if(c == '\'')
                c = TABLESIZE-1 + 65;
                
            if(cursor->children[c - 65] == NULL)
            {
                cursor->children[c - 65] = createNode();
            }
            cursor = cursor->children[c - 65];
        }
        // newline: set this node to an 'existing' word and move
        // back to the first node
        else if(c == '\n')
        {
            cursor->is_word = true;
            words_++;
            cursor = root;
        }
    }
  loaded_=true;
  return loaded_;      
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // return words;
    if (loaded_)
    return words_;
    else return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

// create function clean tree 
void clean (node* root)
{
 //if (root!=NULL)
 //{      
        int i;
        for( i = 0; i < (TABLESIZE); i++)
        {
            if(root->children[i] != NULL)
            {
                //char l=i+65;
               // printf("%c", l);
                clean(root->children[i]);
                
            }
            
        }
       // printf("\n"); 
        free(root);
  //}
}

bool unload(void)
{
    clean(root);
    return true;
}
