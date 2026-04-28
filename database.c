#include "inverted.h"  


void create_database(Slist *head, hash_t arr[])  // Function to create database
{
    char word[50];   
    int ind;       
    Slist *temp=head; 
    int word_found=0;

    while(temp!=NULL)  // traverse untill temp reaches null
    {
         if(file_exists(arr,temp->file_name)==1) // Check if file already exists in database
        {
            temp=temp->link; // Move to temp to temp link
            continue;       
        }

       FILE *fptr= fopen(temp->file_name,"r"); // Open file in read mode

       while(fscanf(fptr,"%s",word)!=EOF) // Read words one by one till end of file
       {
        word_found = 0;
        if(word[0]>='a' && word[0]<='z')   //check if first character is lowercase
        ind=word[0]-'a';                 
        else if(word[0]>='A' && word[0]<='Z') //check if first character is uppercase
        ind=word[0]-'A';                     
        else
        ind=26;   //Special index for non-alphabet characters

        if(arr[ind].link==NULL) 
        {
             arr[ind].link=create_main_node(word, temp->file_name); //Create new main node
        }
        else
        {
            main_node *main_temp=arr[ind].link; // Traverse main node list
             main_node *main_prev=NULL;   //update previous pointer to null

             while(main_temp!=NULL)   // traverse till temp reaches null
             {
                if(strcmp(main_temp->word,word)==0) //if word already exists
                {
                    word_found=1;
                     sub_node *sub_temp=main_temp->sub_link; 
                     sub_node *sub_prev=NULL;                

                     while(sub_temp!=NULL)  
                     {
                        if(strcmp(sub_temp->file_name,temp->file_name)==0)   // check if file already exists
                        {
                            (sub_temp->word_count)++; // Increment word count
                            break;       
                        }
                        
                        
                            sub_prev=sub_temp; // Move previous
                            sub_temp=sub_temp->sub_link;// Move sub temp to next
                        
                     }

                     if(sub_temp==NULL) 
                     {
                         sub_prev->sub_link=create_sub_node(temp->file_name); 
                         (main_temp->file_count)++;
                     }
                     else
                     break;  
                }

                main_prev=main_temp;          
                main_temp=main_temp->main_link; 
             }

             if(word_found==0)  //check  if word not found in main list
              main_prev->main_link=create_main_node(word,temp->file_name); 

        }        
    
       }

        fclose(fptr);// Close file
        temp = temp->link;//Move to next file
    }
        
}


 main_node *create_main_node(char *word, char *file_name)  
 {
     main_node *main_new=malloc(sizeof(main_node)); // Allocate memory for main node
    
     if(main_new == NULL)   // Check if memory is allocated or not
        return NULL;
     
            main_new->file_count=1;// Initialize file count to 1
            strcpy(main_new->word,word); // Copy word
            main_new->main_link=NULL; // Set main link to NULL
            main_new->sub_link = create_sub_node(file_name);// Create first sub node

        if(main_new->sub_link==NULL)   // If sub node creation fails
        {
            free(main_new);// Free  the allocated memory
            return NULL;
        }

               return  main_new;   
 }     


sub_node *create_sub_node(char *file_name) 
{
     sub_node *sub_new=malloc(sizeof( sub_node));   

     if(sub_new == NULL)   // Check if memory is allocated or not
        return NULL;

        sub_new->word_count=1;   // Initialize word count as 1
            strcpy(sub_new->file_name,file_name);   // Copy file name
            sub_new->sub_link = NULL;  // Set next pointer NULL

            return sub_new;   
}


void display(hash_t arr[])   // Function to display
{
    printf("-----------------------------------------------------------------------------\n");
    printf("%-10s %-12s %-15s %-12s %-20s\n","Index", "File_Count", "Word", "Word_Count", "File_Names");
    printf("-----------------------------------------------------------------------------\n");
    for(int i = 0; i < 27; i++)
    {
        if(arr[i].link != NULL)   // If index has data
        {
            main_node *mtemp = arr[i].link;

            while(mtemp != NULL)   // Loop through main nodes
            {
                printf("%-10d ", i);   // Print index
                printf("%-12d %-15s ", mtemp->file_count, mtemp->word);  
                // Print file count and word

                sub_node *stemp = mtemp->sub_link;

                while(stemp != NULL)
                {
                    printf("%-12d %-20s ", stemp->word_count, stemp->file_name);
                    // Print word count and file name

                    stemp = stemp->sub_link;   // Move to next sub node
                }

                printf("\n");

                mtemp = mtemp->main_link;   // Move to next main node
            }
        }
    }
    printf("-----------------------------------------------------------------------------\n");
}

void save(hash_t arr[]) // Function to save database into the  file
{
    char file[50]; 

    printf("Enter the file name to store the data "); 
    scanf(" %s",file);   // Read file name from user

    char *dot = strchr(file, '.'); 

    if(dot==NULL || strcmp(dot,".txt")!=0) // Check  the extension
    {
        printf("ERROR : %s has invalid extension!\n ", file);  
        return;
    }

    FILE *fptr = fopen(file, "w"); // Open file in write mode

    if(fptr == NULL) // Check if file opened or not
    {
        printf("ERROR : %s file does not exist !\n", file);
        return;  
    }

    for(int i=0;i<27;i++)   
    {
        if(arr[i].link!= NULL)// If index has data
        {
              main_node *mtemp=arr[i].link;

              while(mtemp!=NULL)
              {
                  fprintf(fptr,"#%d;",i);// Write index

                  fprintf(fptr,"%d;%s;",mtemp->file_count,mtemp->word);// Write file count & word

                  sub_node *stemp=mtemp->sub_link;  

                  while(stemp!=NULL) 
                  {
                    fprintf(fptr,"%d;%s;",stemp->word_count,stemp->file_name); 
                       stemp = stemp->sub_link;   // Move next
                  } 

                    fprintf(fptr,"#\n"); 
                    mtemp=mtemp->main_link;// Move next main node           
              }  
            }     
    }

    fclose(fptr);// Close file
}


void search(hash_t arr[]) // Function to search word
{
    int ind;  
    char word[50];  

    printf("Enter the word\n");  
    scanf(" %s",word);// Read word from the user

    if(word[0]>='a' && word[0]<='z')
        ind=word[0]-'a';
        else if(word[0]>='A' && word[0]<='Z')  
        ind=word[0]-'A';
        else
        ind=26;  

        if(arr[ind].link!=NULL) 
        {
            main_node *main_temp=arr[ind].link; 

            while(main_temp!=NULL)
            {
            if(strcmp(main_temp->word,word)==0) // check if word found
            {
                printf("\nWord \"%s\" found in %d file(s)\n",word, main_temp->file_count);

                 sub_node *sub_temp=main_temp->sub_link; 

                 while(sub_temp!=NULL) // Traverse sub nodes
                 {
                     printf("-> %s : %d time\n", sub_temp->file_name,sub_temp->word_count);

                       sub_temp=sub_temp->sub_link;
                 }
                   return;   
            }

            main_temp=main_temp->main_link; // Move next
        }
        }

        printf("ERROR: %s is not present in database \n",word); 
}


int file_exists(hash_t arr[], char *filename)  
{
    for(int i = 0; i < 27; i++)   // Loop till hash indexs
    {
        main_node *main = arr[i].link; 

        while(main != NULL)  // Traverse main node 
        {
            sub_node *sub = main->sub_link;// Get sub node list of that word

            while(sub != NULL) // Traverse sub node list
            {
                if(strcmp(sub->file_name, filename) == 0) // check if file name matches
                    return 1;   

                sub = sub->sub_link; // Move to next sub node
            }

            main = main->main_link; // Move to next main node
        }
    }

    return 0;  
}


int update_database(hash_t *arr)   
{
    char filename[25], line[50];   

    printf("Enter the saved file name: ");  
    scanf("%s", filename);   // Read file name from the user

    if (validate_files(filename) == FAILURE)   // Validate file name
        return FAILURE;  

    FILE *fptr = fopen(filename, "r"); // Open file in read mode

    while (fscanf(fptr, "%s", line) != EOF) // Read each line until EOF
    {
        int len = strlen(line); // find length of line

        if (line[0] != '#' || line[len - 1] != '#') 
        {
            printf("ERROR: Invalid %s file format\n", filename); 
            fclose(fptr); 
            return FAILURE; 
        }

        main_node *main_new = malloc(sizeof(main_node));
        if(main_new==NULL)  
        {
            printf("ERROR : Memory allocation failed\n");
             fclose(fptr); 
           return FAILURE;
        }
        char *token = strtok(&line[1], ";"); 
        int index = atoi(token);   

        main_new->file_count = atoi(strtok(NULL, ";"));   // Extract file count
        strcpy(main_new->word, strtok(NULL, ";"));   // copy word
        main_new->sub_link = NULL;   // Initialize sub link to null
        main_new->main_link = NULL;   // Initialize main link to null

        for (int i = 0; i < main_new->file_count; i++)   
        {
            sub_node *sub_new = malloc(sizeof(sub_node));  

            sub_new->word_count = atoi(strtok(NULL, ";"));
            strcpy(sub_new->file_name, strtok(NULL, ";"));  
            sub_new->sub_link = NULL;  // Initialize sub link to null

            if (main_new->sub_link == NULL) 
                main_new->sub_link = sub_new;  
            else
            {
                sub_node *sub_temp = main_new->sub_link;  

                while (sub_temp->sub_link != NULL)  
                    sub_temp = sub_temp->sub_link;

                sub_temp->sub_link = sub_new;  
            }
        }

        main_node *main = arr[index].link;  
        main_node *prev_main = NULL;   // Previous main pointer to null
        int w_found = 0;   // Flag to check if word exists or not

        while (main != NULL) //Traverse main node 
        {
            if (strcmp(main->word, main_new->word) == 0)  
            {
                w_found = 1; 

                sub_node *sub = main_new->sub_link;

                while (sub != NULL)  
                {
                    int f_found = 0;   

                    sub_node *temp = main->sub_link;// Traverse existing sub list
                    sub_node *prev_temp = NULL;  

                    while (temp != NULL) // Loop untill temp reaches null
                    {
                        if (strcmp(sub->file_name, temp->file_name) == 0)  
                        {
                            f_found = 1; 
                            break;  
                        }

                        prev_temp = temp;   // Update previous
                        temp = temp->sub_link;  // Move temp to temp sublink
                    }

                    if (f_found == 0)
                    {
                        sub_node *copy = malloc(sizeof(sub_node));  

                        copy->word_count = sub->word_count;// Copy word count
                        strcpy(copy->file_name, sub->file_name); // Copy file name
                        copy->sub_link = NULL; // Initialize link to null

                        if (prev_temp == NULL)  
                            main->sub_link = copy;
                        else
                            prev_temp->sub_link = copy;

                        main->file_count++;// Increment file count
                    }

                    sub = sub->sub_link;// Move to next new sub node
                }

                break;  
            }

            prev_main = main; // Update previous main 
            main = main->main_link; // Move to next main node
        }

        if (w_found == 0) //check if word not found in database
        {
            if (arr[index].link == NULL) // If index empty
                arr[index].link = main_new; // Insert directly
            else
            {
                main_node *main_temp = arr[index].link;  

                while (main_temp->main_link != NULL)
                    main_temp = main_temp->main_link;

                main_temp->main_link = main_new;  
            }
        }
        else // If word already existed
        {
            sub_node *tmp = main_new->sub_link;   

            while (tmp != NULL)
            {
                sub_node *next = tmp->sub_link;   // Store next
                free(tmp);  
                tmp = next;   // update tmp to next;
            }

            free(main_new);
        }
    }

    fclose(fptr); // Close file
    printf("INFO: Updated database successfully\n\n");  
    return SUCCESS;  
}