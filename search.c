#include "main.h"

int search_database(mainnode **arr, char word[])
{
    // Initialize hash index
    int index = 0;

    // Check whether first character is alphabet
    if(isalpha(word[0]))
        // Calculate hash index for alphabets
        index = tolower(word[0]) - 'a';
    else
        // Store special characters/numbers at index 26
        index = 26;

    // Point to corresponding hash index
    mainnode *temp = arr[index];

    // Check whether index is empty
    if(temp == NULL)
    {
        return FAILURE;
    }

    // Traverse mainnode list
    while(temp != NULL)
    {
        // Check whether word matches
        if(strcmp(word, temp->word) == 0)
        {
            // Display word found message
            printf("%s is found in the database\n", word);

            // Display number of files containing word
            printf("%s is present in %d file(s)\n",
                   word,
                   temp->f_count);

            // Point to subnode list
            subnode *subtemp = temp->sublink;

            // Traverse subnode list
            while(subtemp != NULL)
            {
                // Display filename and word count
                printf("%s is present in %s in %d times\n",
                       temp->word,
                       subtemp->f_name,
                       subtemp->w_count);

                // Move to next subnode
                subtemp = subtemp->nextsub;
            }

            // Return success if word found
            return SUCCESS;
        }

        // Move to next mainnode
        temp = temp->mainlink;
    }

    // Return failure if word not found
    return FAILURE;
}