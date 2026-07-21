#include "main.h"

int validate_argv(char *argv[], flist **fhead)
{
    // Start checking arguments from index 1
    int i = 1;

    // Traverse command line arguments
    while(argv[i])
    {
        // Validate .txt extension
        if(validate_txt(argv[i]) == SUCCESS)
        {
            // Check whether file exists and is not empty
            if(check_exist(argv[i]) == SUCCESS)
            {
                // Check duplicate filenames
                if(check_duplicate(argv[i], *fhead) == SUCCESS)
                {
                    // Allocate memory for file node
                    flist *new = (flist *)malloc(sizeof(flist));

                    // Return failure if allocation fails
                    if(new == NULL)
                        return FAILURE;

                    // Store filename
                    new->fname = argv[i];

                    // Initialize link pointer
                    new->link = NULL;

                    // Check whether list is empty
                    if(*fhead == NULL)
                    {
                        // Insert first node
                        *fhead = new;
                    }
                    else
                    {
                        // Insert node at beginning
                        new->link = *fhead;
                        *fhead = new;
                    }
                }
            }
        }

        // Move to next argument
        i++;
    }

    // Return success status
    return SUCCESS;
}

int validate_txt(char arr[])
{
    // Find '.' in filename
    char *p = strstr(arr, ".");

    // Validate .txt extension
    if(p == NULL || strcmp(p, ".txt") != 0)
    {
        printf("%s is not in correct file format\n", arr);

        return FAILURE;
    }

    // Return success status
    return SUCCESS;
}

int check_exist(char arr[])
{
    // Open file in read mode
    FILE *fp = fopen(arr, "r");

    // Check whether file exists
    if(fp == NULL)
    {
        printf("%s does not exist\n", arr);

        return FAILURE;
    }

    // Move file pointer to end
    fseek(fp, 0, SEEK_END);

    // Check whether file is empty
    if(ftell(fp) == 0)
    {
        printf("%s is empty\n", arr);

        fclose(fp);

        return FAILURE;
    }

    fclose(fp);

    return SUCCESS;
}

int check_duplicate(char arr[], flist *fdd)
{
    // Check whether file list is empty
    if(fdd == NULL)
        return SUCCESS;

    // Traverse file list
    while(fdd)
    {
        // Compare filenames
        if(strcmp(fdd->fname, arr) == 0)
        {
            return FAILURE;
        }

        // Move to next node
        fdd = fdd->link;
    }

    // Return success if no duplicates found
    return SUCCESS;
}