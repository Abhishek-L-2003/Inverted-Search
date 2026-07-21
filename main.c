/*
Project      : Inverted Search using Hashing
Name         : Abhishek L
Date         : 22/05/2026

Description  : Inverted Search is a technique used to efficiently store and search words from multiple text files.
               This project uses Hashing and Linked Lists to create a searchable database of words.

               validate_argv(); // Validates command line arguments and stores valid filenames into linked list.
               validate_txt(); // Checks whether the given file has .txt extension.
               check_exist(); // Verifies whether the file exists and is not empty.
               check_duplicate(); // Checks duplicate filenames in the linked list.

               create_database(); // Creates the complete inverted search database from input files.
               insert_first_mainnode(); // Creates and inserts a mainnode containing unique word information.
               insert_first_subnode(); // Creates and inserts subnodes containing filename and word count details.

               display_database(); // Displays the complete database in formatted tabular form.
               search_database(); // Searches a word in the database and displays file occurrence details.

               save_database(); // Saves the entire database into a backup text file.
               check_file_empty(); // Checks whether the file is empty or not.

               update_database(); // Restores database contents from a backup file.
               insert_flist(); // Inserts filenames into update linked list while avoiding duplicates.

               delete_duplicates(); // Removes duplicate filenames after updating database.

               validate_backup_file(); // Validates the backup file format before restoring database.

Sample input : ./a.out file1.txt file2.txt

Sample output: -------------------------------Menu------------------------------------
               1.Create Database
               2.Display Database
               3.Search Database
               4.Save Database
               5.Update Database
               6.Exit

               Enter option : 1
               Creating database successful

               Enter option : 2

               Index   Word            FileCount      FileName        WordCount
               -------------------------------------------------------------------
               7       hello           1              file1.txt       2
               22      world           2              file1.txt       1
                                                      file2.txt       1

               Enter option : 3
               Enter the word you have to search : hello

               hello is found in the database
               hello is present in 1 file(s)
               hello is present in file1.txt in 2 times
*/

#include "main.h"

int main(int argc, char *argv[])
{
    // Create hash table array
    mainnode *arr[27];

    // Initialize all hash indices to NULL
    for(int i = 0; i < 27; i++)
        arr[i] = NULL;

    // Initialize file list head
    flist *fhead = NULL;

    // Initialize update file list head
    flist *uhead = NULL;

    // Check minimum argument count
    if(argc < 2)
    {
        printf("Minimum 2 arguments are required\n");
        return FAILURE;
    }

    // Validate command line arguments
    if(validate_argv(argv, &fhead) == FAILURE)
    {
        return FAILURE;
    }

    // Display valid filenames
    flist *temp = fhead;

    while(temp != NULL)
    {
        printf("%s ", temp->fname);
        temp = temp->link;
    }

    // Initialize 
    int created = 0, updated = 0;

    while(1)
    {
        // Display menu options
        printf("\n-------------------------------Menu------------------------------------\n");
        printf("1.Create Database\n");
        printf("2.Display Database\n");
        printf("3.Search Database\n");
        printf("4.Save Database\n");
        printf("5.Update Database\n");
        printf("6.Exit\n");

        // Read user option
        int option;
        scanf("%d", &option);

        // Process menu option
        switch(option)
        {
            // Create database option
            case 1:
            {
                // Check if valid files exist
                if(fhead == NULL)
                {
                    printf("There are no valid files\n");
                    break;
                }

                // Check if database already created
                if(created == 1)
                {
                    printf("Database is already created\n");
                    break;
                }

                // Remove duplicate files after update
                if(updated == 1)
                {
                    delete_duplicates(&fhead, uhead);
                }

                // Create database
                if(create_database(arr, fhead, &created) == FAILURE)
                {
                    printf("Creating database failed\n");
                }
                else
                {
                    printf("Creating database successful\n");
                }

                break;
            }

            // Display database option
            case 2:
            {
                // Check database existence
                if(created == 0 && updated == 0)
                {
                    printf("Database is not created yet\n");
                    printf("First create or update database\n");
                    break;
                }

                // Display database contents
                display_database(arr);

                break;
            }

            // Search database option
            case 3:
            {
                // Check database existence
                if(created == 0 && updated == 0)
                {
                    printf("Database is not created yet\n");
                    printf("First create or update database\n");
                    break;
                }

                // Store search word
                char word[20];

                // Read search word
                printf("Enter the word you have to search: ");
                scanf("%s", word);

                // Search word in database
                if(search_database(arr, word) == FAILURE)
                {
                    printf("%s is not found in the database\n", word);
                }

                break;
            }

            // Save database option
            case 4:
            {
                // Check database existence
                if(created == 0 && updated == 0)
                {
                    printf("Database is not created yet\n");
                    printf("First create or update database\n");
                    break;
                }

                // Save database into backup file
                save_database(arr, fhead);

                break;
            }

            // Update database option
            case 5:
            {
                // Prevent update after database creation
                if(created == 1)
                {
                    printf("Database is already created\n");
                    break;
                }

                // Update database from backup file
                if(update_database(arr, &updated, &uhead) == FAILURE)
                {
                    updated = 0;
                }

                break;
            }

            // Exit option
            case 6:
            {
                return SUCCESS;
            }
        }
    }
}