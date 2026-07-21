#include "main.h"

int display_database(mainnode **arr)
{
    printf("-------------------------------------------------------------------------------\n");

    printf("%-8s %-20s %-12s %-20s %-10s\n",
           "Index", "Word", "FileCount", "FileName", "WordCount");
    printf("-------------------------------------------------------------------------------\n");

    // Traverse all hash indices
    for(int i = 0; i < 27; i++)
    {
        // Point to mainnode list
        mainnode *temp = arr[i];

        // Traverse mainnode list
        while(temp != NULL)
        {
            // Point to subnode list
            subnode *subtemp = temp->sublink;

            // Flag to print mainnode details only once
            int first = 1;

            // Traverse subnode list
            while(subtemp != NULL)
            {
                // Print full row for first subnode
                if(first)
                {
                    printf("%-8d %-20s %-12d %-20s %-10d\n",
                           i,
                           temp->word,
                           temp->f_count,
                           subtemp->f_name,
                           subtemp->w_count);

                    // Reset flag after first print
                    first = 0;
                }
                else
                {
                    // Print only subnode details for remaining rows
                    printf("%-8s %-20s %-12s %-20s %-10d\n",
                           "",
                           "",
                           "",
                           subtemp->f_name,
                           subtemp->w_count);
                }

                // Move to next subnode
                subtemp = subtemp->nextsub;
            }

            // Move to next mainnode
            temp = temp->mainlink;
        }
    }


    printf("-------------------------------------------------------------------------------\n");

    return SUCCESS;
}