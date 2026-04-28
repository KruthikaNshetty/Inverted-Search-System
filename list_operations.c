#include "inverted.h"  


int find_node(Slist *head, char *data) //Function to find a node with given data
{
    while(head != NULL) // Traverse until head reaches null
    {
        if(strcmp(head->file_name, data) == 0) // Compare current node file_name with data
            return SUCCESS;   //return SUCCESS if found

        head = head->link;// Move head to head link
    }

    return FAILURE; 
}


int insert_at_last(Slist **head, char *data) // Function to insert a new node at the end
{
    Slist *new = malloc(sizeof(Slist));   
    if(new == NULL)   // Check if memory is allocated or not
        return FAILURE; 

    strcpy(new->file_name, data); // Copy data 
    new->link = NULL;  // Initialize lin new link to NULL

    if(*head == NULL) //check  if head is null or not
    {
        *head = new; // Make head to new
        return SUCCESS; 
    }

    Slist *temp = *head;   
    while(temp->link != NULL)  // Traverse untill tem reaches null
    {
        temp = temp->link;   // update temp to temp link
    }

    temp->link = new;  
    return SUCCESS;   
}


void print_list(Slist *head) // Function to print 
{
    if (head == NULL) // If list is empty
    {
        printf("INFO : List is empty\n");  
    }
    else
    {
        while (head)  
        {
            printf("%s ->", head -> file_name);  // Print current node's file_name
            head = head -> link;  // Move to next node
        }

        printf("NULL\n\n"); 
    }
}