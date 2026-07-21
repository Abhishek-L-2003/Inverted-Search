#include "main.h"

int create_database(mainnode **arr, flist *fhead, int *created)
{
    // Traverse through all files
    while(fhead)
    {
        // Open file in read mode
        FILE *fp = fopen(fhead->fname, "r");

        // Return failure if file not opened
        if(fp == NULL)
            return FAILURE;

        char str[100];

        // Read words from file one by one
        while(fscanf(fp, "%s", str) == 1)
        {
            // Check if first character is alphabet
            if(isalpha(str[0]))
            {
                // Calculate hash index for alphabets
                int index = tolower(str[0]) - 'a';

                // Insert word into mainnode
                mainnode *node = insert_first_mainnode(&arr[index], str, fhead->fname);

                // Insert/update subnode if mainnode exists
                if(node != NULL)
                {
                    insert_first_subnode(node, fhead->fname);
                }
            }
            else
            {
                // Store special characters/numbers at index 26
                int index = 26;

                // Insert word into special index
                mainnode *node = insert_first_mainnode(&arr[index], str, fhead->fname);

                // Insert/update subnode
                if(node != NULL)
                {
                    insert_first_subnode(node, fhead->fname);
                }
            }
        }

        fclose(fp);

        // Move to next file
        fhead = fhead->link;
    }

    // Mark database as created
    *created = 1;

    return SUCCESS;
}

mainnode *insert_first_mainnode(mainnode **address, char word[], char fileaddress[])
{
    // Check if hash index is empty
    if(*address == NULL)
    {
        // Allocate memory for mainnode
        *address = (mainnode *)malloc(sizeof(mainnode));

        // Return NULL if allocation fails
        if(*address == NULL)
            return NULL;

        // Copy word into node
        strcpy((*address)->word, word);

        // Initialize file count
        (*address)->f_count = 0;

        // Initialize links
        (*address)->mainlink = NULL;
        (*address)->sublink = NULL;

        return *address;
    }
    else
    {
        // Traverse mainnode list
        mainnode *temp = *address;

        while(temp != NULL)
        {
            // Check if word already exists
            if(strcmp(temp->word, word) == 0)
            {
                return temp;
            }

            temp = temp->mainlink;
        }

        // Allocate memory for new node
        mainnode *new = (mainnode *)malloc(sizeof(mainnode));

        // Return NULL if allocation fails
        if(new == NULL)
            return NULL;

        // Copy word into node
        strcpy(new->word, word);

        // Initialize file count
        new->f_count = 0;

        // Initialize sublink
        new->sublink = NULL;

        // Insert node at beginning
        new->mainlink = *address;
        *address = new;

        return new;
    }
}

int insert_first_subnode(mainnode *node, char fileaddress[])
{
    // Check if mainnode exists
    if(node == NULL)
        return FAILURE;

    // Check if sublink is empty
    if(node->sublink == NULL)
    {
        // Allocate memory for subnode
        subnode *new = (subnode *)malloc(sizeof(subnode));

        // Return failure if allocation fails
        if(new == NULL)
            return FAILURE;

        // Copy filename
        strcpy(new->f_name, fileaddress);

        // Initialize word count
        new->w_count = 1;

        // Initialize next pointer
        new->nextsub = NULL;

        // Link subnode to mainnode
        node->sublink = new;

        // Increment file count
        node->f_count++;

        return SUCCESS;
    }
    else
    {
        // Traverse subnode list
        subnode *temp = node->sublink;

        while(temp != NULL)
        {
            // Check if filename already exists
            if(strcmp(temp->f_name, fileaddress) == 0)
            {
                // Increment word count
                temp->w_count++;

                return SUCCESS;
            }

            temp = temp->nextsub;
        }

        // Allocate memory for new subnode
        subnode *new = (subnode *)malloc(sizeof(subnode));

        // Return failure if allocation fails
        if(new == NULL)
        return FAILURE;

        strcpy(new->f_name, fileaddress);

        // Initialize word count
        new->w_count = 1;

        // Insert subnode at beginning
        new->nextsub = node->sublink;
        node->sublink = new;

        // Increment file count
        node->f_count++;

        return SUCCESS;
    }
}