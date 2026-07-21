#include "main.h"

int save_database(mainnode **arr, flist *fhead)
{
    // Prompt user for filename
    printf("Enter the filename:");

    // Store backup filename
    char filename[50];

failure:

    // Read filename from user
    scanf("%s", filename);

    // Validate .txt extension
    if(validate_txt(filename) == FAILURE)
    {
        printf("Please enter valid .txt filename\n");
        goto failure;
    }

    // Check whether filename already exists in database
    if(check_duplicate(filename, fhead) == FAILURE)
    {
        printf("This file is present in the database.\n");
        printf("So please enter new filename\n");

        goto failure;
    }

    // Open file in read mode
    FILE *fp = fopen(filename, "r");

    // Check whether file exists and is not empty
    if(fp != NULL && check_file_empty(fp) != 0)
    {
        printf("File is not empty\n");
        printf("1. Create new file\n");
        printf("2. Overwrite\n");

        // Store user option
        int option;

        // Read user choice
        scanf("%d", &option);

        fclose(fp);

        // Ask for another filename if option is 1
        if(option == 1)
            goto failure;
    }
    else if(fp != NULL)
    {
        // Close file if opened successfully
        fclose(fp);
    }

    // Open file in write mode
    fp = fopen(filename, "w");

    // Return failure if file opening fails
    if(fp == NULL)
        return FAILURE;

    // Traverse all hash indices
    for(int i = 0; i < 27; i++)
    {
        // Point to mainnode list
        mainnode *temp = arr[i];

        // Traverse mainnode list
        while(temp != NULL)
        {
            // Write mainnode details into file
            fprintf(fp, "#%d;%s;%d;",
                    i,
                    temp->word,
                    temp->f_count);

            // Point to subnode list
            subnode *subtemp = temp->sublink;

            // Traverse subnode list
            while(subtemp != NULL)
            {
                // Write subnode details into file
                fprintf(fp, "%s;%d;",
                        subtemp->f_name,
                        subtemp->w_count);

                // Move to next subnode
                subtemp = subtemp->nextsub;
            }

            // Write ending delimiter
            fprintf(fp, "#\n");

            // Move to next mainnode
            temp = temp->mainlink;
        }
    }

    fclose(fp);

    // Return success status
    return SUCCESS;
}

int check_file_empty(FILE *fp)
{
    // Move file pointer to end
    fseek(fp, 0, SEEK_END);

    // Get file size
    long size = ftell(fp);

    // Display file size
    printf("%ld", size);

    // Return file size
    return size;
}