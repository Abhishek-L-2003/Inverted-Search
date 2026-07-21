#include "main.h"

int update_database(mainnode **arr, int *created, flist **uhead)
{
    // Initialize update file list
    *uhead = NULL;

    // Store backup filename
    char filename[50];

    // Prompt user for database filename
    printf("Enter the database name\n");

failure:

    // Read filename from user
    scanf("%s", filename);

    // Check whether file exists
    if(check_exist(filename) == FAILURE)
    {
        printf("%s does not exist\n", filename);
        goto failure;
    }

    // Open backup file in read mode
    FILE *fp = fopen(filename, "r");

    // Return failure if file opening fails
    if(fp == NULL)
        return FAILURE;

    // Check whether file is empty
    if(check_file_empty(fp) == 0)
    {
        printf("File is empty\n");

        fclose(fp);

        goto failure;
    }

    // Validate backup file format
    if(validate_backup_file(fp) == FAILURE)
    {
        printf("Updating database failed\n");
        return FAILURE;
    }

    // Move file pointer to beginning
    fseek(fp, 0, SEEK_SET);

    // Store hash index
    int index;

    // Read backup file data
    while(fscanf(fp, "#%d;", &index) == 1)
    {
        // Allocate memory for mainnode
        mainnode *new = malloc(sizeof(mainnode));

        // Initialize sublink
        new->sublink = NULL;

        // Initialize mainlink
        new->mainlink = NULL;

        // Read word and file count
        fscanf(fp, "%[^;];%d;",
               new->word,
               &new->f_count);

        // Check whether index is empty
        if(arr[index] == NULL)
        {
            // Insert node at hash index
            arr[index] = new;
        }
        else
        {
            // Traverse mainnode list
            mainnode *temp = arr[index];

            while(temp->mainlink != NULL)
                temp = temp->mainlink;

            // Insert node at end
            temp->mainlink = new;
        }

        // Create subnodes
        for(int i = 0; i < new->f_count; i++)
        {
            // Allocate memory for subnode
            subnode *newsub = malloc(sizeof(subnode));

            // Initialize next pointer
            newsub->nextsub = NULL;

            // Read filename and word count
            fscanf(fp, "%[^;];%d;",
                   newsub->f_name,
                   &newsub->w_count);

            // Insert filename into update file list
            insert_flist(uhead, newsub->f_name);

            // Check whether sublink is empty
            if(new->sublink == NULL)
            {
                // Insert first subnode
                new->sublink = newsub;
            }
            else
            {
                // Traverse subnode list
                subnode *temp = new->sublink;

                while(temp->nextsub != NULL)
                    temp = temp->nextsub;

                // Insert subnode at end
                temp->nextsub = newsub;
            }
        }

        // Skip ending delimiter
        fscanf(fp, "#\n");
    }

    fclose(fp);

    // Mark database as updated
    *created = 1;

    return SUCCESS;
}

void insert_flist(flist **head, char *name)
{
    // Check duplicate filename
    if(check_duplicate(name, *head) == FAILURE)
        return;

    // Allocate memory for file node
    flist *new = malloc(sizeof(flist));

    // Allocate memory for filename
    new->fname = malloc(strlen(name) + 1);

    // Copy filename
    strcpy(new->fname, name);

    // Initialize link pointer
    new->link = NULL;

    // Check whether list is empty
    if(*head == NULL)
    {
        // Insert first node
        *head = new;
    }
    else
    {
        // Traverse file list
        flist *temp = *head;

        while(temp->link)
            temp = temp->link;

        // Insert node at end
        temp->link = new;
    }
}