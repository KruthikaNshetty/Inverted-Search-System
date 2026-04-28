/*Name:Kruthika N Shetty

Project descriptin: This project implements an Inverted Index using a Hash Table in C, which is used to efficiently map
 words to the files in which they appear. The program accepts multiple valid .txt files, reads their contents, and builds 
 a database where each word is stored in a hash table based on its first character. Each word (main node) maintains a list
 of files (sub nodes) along with the number of times the word appears in each file. The system supports operations such as
creating the database, searching for a word, displaying the entire database, saving it to a file, and updating it from a
saved file. This project demonstrates the use of file handling, dynamic memory allocation, linked lists, hashing techniques,
 and structured data organization in C.
 
*/


#include<stdio.h>      
#include<ctype.h>      
#include<string.h>     
#include "inverted.h" 

int main(int argc, char *argv[])
{
    
    if(argc < 2)//Check if minimum 1 file argument is given
    {
        printf("ERROR: Invalid arguments\n");
        return FAILURE; 
    }

    int db_created = 0; // Flag to check if database is created
    int db_updated = 0;// Flag to check if database is updated

    Slist *head = NULL; //Head pointer for storing file names

    hash_t arr[27];

  
    for(int i = 0; i < 27; i++)  // Initialize hash table
    {
        arr[i].index = i;    // Store index value
        arr[i].link = NULL;  // Initialize link as NULL
    }

    for (int i = 1; i < argc; i++)
    {
      
        if(validate_files(argv[i]) == SUCCESS)  //Validate each file
        {
            
            if(find_node(head, argv[i]) == SUCCESS)//Check if file already exists in list
            {
                printf("ERROR: %s duplicate found\n", argv[i]);
            }
            else
            {

                insert_at_last(&head, argv[i]);
            }
        }
    }

    printf("INFO: Valid files are: ");
    print_list(head); // Print all valid files

    while(1)         
    {
        int input;
        printf("<----------MENU---------->\n");
        printf("\n1.Create database\n2.Display database\n3.Search database\n4.update database\n5.Save\n6.Exit\n\n");
        printf("Select the operation you want to perform : ");
        scanf("%d",&input);   // Read choice from the user

        switch(input)
        {
            case 1:
              
                if(db_created == 1)  // Check if already created
                {
                    printf("INFO: Database already created\n");
                    break;
                }

                create_database(head, arr);   // Create inverted index
                db_created = 1; // Set flag
                printf("INFO: Database created successfully\n");
                break;

            case 2:
                
                if(db_created==0 && db_updated==0)//If DB not created or updated
                    printf("INFO: Database is empty\n");
                else
                    display(arr);// Display database
                break;

            case 3:
                search(arr);// Search word in database
                break;

            case 4:
               
                if(db_updated==1) //Check if already updated
                {
                    printf("INFO: Database already updated\n");
                    break;
                }

               
                if(update_database(arr)==SUCCESS) //Update database from backup file
                    db_updated=1;
                else
                    printf("ERROR: Update database failed\n");
                break;

            case 5:
                save(arr);// Save database to file
                break;

            case 6:
                return 0;// Exit program

            default:
                printf("ERROR : Invalid option\n"); //Invalid option
        }
    }
}

int validate_files(char *file)
{
    /* Check extension */
    char *dot = strrchr(file, '.');
    if(dot == NULL || strcmp(dot, ".txt") != 0)
    {
        printf("ERROR: %s has invalid extension\n", file);
        return FAILURE;
    }

   
    FILE *fptr = fopen(file, "r"); // Check file exists 
    if(fptr == NULL)
    {
        printf("ERROR: %s file does not exist\n", file);
        return FAILURE;
    }

    /* Check file is empty */
    fseek(fptr, 0, SEEK_END);
    if(ftell(fptr) == 0)
    {
        printf("ERROR: %s file is empty\n", file);
        fclose(fptr);
        return FAILURE;
    }

    fclose(fptr);
    return SUCCESS;
}