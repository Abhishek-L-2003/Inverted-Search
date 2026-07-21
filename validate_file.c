#include "main.h"

int validate_backup_file(FILE *fp)
{
    // Store hash index
    int index;

    // Store file count and word count
    int f_count, w_count;

    // Store word and filename
    char word[50], fname[50];

    // Store character while validating delimiters
    char ch;

    // Move file pointer to beginning
    rewind(fp);

    // Traverse backup file
    while(1)
    {
        // Read starting character
        if(fscanf(fp, "%c", &ch) != 1)
            break;   // Stop at EOF

        // Check whether record starts with '#'
        if(ch != '#')
        {
            printf("Missing starting #\n");
            return FAILURE;
        }

        // Read hash index
        if(fscanf(fp, "%d", &index) != 1)
        {
            printf("Index missing\n");
            return FAILURE;
        }

        // Validate semicolon after index
        if(fscanf(fp, "%c", &ch) != 1 || ch != ';')
        {
            printf("Missing ';' after index\n");
            return FAILURE;
        }

        // Validate index range
        if(index < 0 || index > 26)
            return FAILURE;

        // Read word from file
        if(fscanf(fp, "%49[^;]", word) != 1)
            return FAILURE;

        // Validate semicolon after word
        if(fscanf(fp, "%c", &ch) != 1 || ch != ';')
        {
            printf("Missing ';' after word\n");
            return FAILURE;
        }

        // Check whether word is empty
        if(strlen(word) == 0)
            return FAILURE;

        // Read file count
        if(fscanf(fp, "%d", &f_count) != 1)
            return FAILURE;

        // Validate semicolon after file count
        if(fscanf(fp, "%c", &ch) != 1 || ch != ';')
        {
            printf("Missing ';' after file count\n");
            return FAILURE;
        }

        // Validate file count
        if(f_count <= 0)
            return FAILURE;

        // Traverse all subnode entries
        for(int i = 0; i < f_count; i++)
        {
            // Read filename
            if(fscanf(fp, "%49[^;]", fname) != 1)
                return FAILURE;

            // Validate filename extension
            if(validate_txt(fname) == FAILURE)
                return FAILURE;

            // Validate semicolon after filename
            if(fscanf(fp, "%c", &ch) != 1 || ch != ';')
            {
                printf("Missing ';' after filename\n");
                return FAILURE;
            }

            // Read word count
            if(fscanf(fp, "%d", &w_count) != 1)
                return FAILURE;

            // Validate word count
            if(w_count <= 0)
                return FAILURE;

            // Validate semicolon after word count
            if(fscanf(fp, "%c", &ch) != 1 || ch != ';')
            {
                printf("Missing ';' after word count\n");
                return FAILURE;
            }
        }

        // Validate ending '#'
        if(fscanf(fp, "%c", &ch) != 1 || ch != '#')
        {
            printf("Missing ending #\n");
            return FAILURE;
        }

        // Skip optional newline character
        fscanf(fp, "\n");
    }

    // Move file pointer back to beginning
    rewind(fp);

    return SUCCESS;
}