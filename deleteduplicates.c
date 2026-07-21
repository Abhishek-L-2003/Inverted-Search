#include "main.h"

int delete_duplicates(flist **fhead, flist *uhead)
{
    // Traverse update file list
    while(uhead != NULL)
    {
        // Start traversal from original file list
        flist *temp = *fhead;

        // Initialize previous pointer
        flist *prev = NULL;

        // Traverse original file list
        while(temp != NULL)
        {
            // Check if filenames are same
            if(strcmp(temp->fname, uhead->fname) == 0)
            {
                // Check if node is first node
                if(prev == NULL)
                {
                    // Move head to next node
                    *fhead = temp->link;

                    // Free duplicate node
                    free(temp);

                    // Reset temp to new head
                    temp = *fhead;
                }
                else
                {
                    // Skip duplicate node
                    prev->link = temp->link;

                    // Free duplicate node
                    free(temp);

                    // Move temp to next node
                    temp = prev->link;
                }
            }
            else
            {
                // Move prev pointer
                prev = temp;

                // Move temp pointer
                temp = temp->link;
            }
        }

        // Move to next update file node
        uhead = uhead->link;
    }

    // Return success status
    return SUCCESS;
}