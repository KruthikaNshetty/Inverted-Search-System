#ifndef INVERTED_H
#define INVERTED_H


#include <stdio.h>      
#include <stdlib.h>   
#include <string.h>     
#include <ctype.h>      

/* Macro Definitions */
#define SUCCESS 0      
#define FAILURE -1      




typedef struct node
{
    char file_name[50]; 
    struct node *link; 
} Slist;




typedef struct node1
{
    int word_count;    // Number of times word appears in this file
    char file_name[25]; // File name where word is present
    struct node1 *sub_link;    
} sub_node;


typedef struct node2
{
    int file_count;   // Number of files containing this word
    char word[26]; // The word stored
    sub_node *sub_link; // Pointer to sub node list 
    struct node2 *main_link;// Pointer to next main node
} main_node;

typedef struct node3
{
    char index;         
    main_node *link;    
} hash_t;

/* Validate whether file exists and is not empty */
int validate_files(char *file);

/* Check whether file name already exists in file list */
int find_node(Slist *head, char *data);

/* Insert new file name at end of file list */
int insert_at_last(Slist **head, char *data);

/* Print all file names in file list */
void print_list(Slist *head);

/* Create inverted index database from given file list */
void create_database(Slist *head, hash_t arr[]);

/* Create a new main node for a word */
main_node *create_main_node(char *word, char *file_name);

/* Create a new sub node for a file */
sub_node *create_sub_node(char *file_name);

/* Display entire inverted index database */
void display(hash_t arr[]);

/* Save database into a file */
void save(hash_t arr[]);

/* Search for a word in database */
void search(hash_t arr[]);

/* Update database from saved file */
int update_database(hash_t arr[]);

/* Check if file already exists in database */
int file_exists(hash_t arr[], char *filename);

#endif