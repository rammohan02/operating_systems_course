//Ram Mohan - COE19B055
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
    FILE *file1, *file2, *file3, *file4;
    char content, content1;
    file1 = fopen("sample_1.txt", "r");             //Opening file1

    if(file1 == NULL)                               //checking whether file1 is created or not
    {
        printf( "File1 failed to open." );
    }
    else
    {
        file2 = fopen("sample_2.txt", "w");         //opening file2

        if(file2==NULL)
        {
            printf("File2 failed to open");
        }
        else
        {
            content = fgetc(file1);                 //getting first character of file1
            while(content!=EOF)
            {
                fputc(content, file2);              //copying content from file1 to file2
                content = fgetc(file1);             //getting the next content
            }

            printf("File copied Successfully\n");

            fclose(file1);
            fclose(file2);
        }
    }

    file1 = fopen("sample_1.txt", "r");
    file3 = fopen("sample_3.txt", "w");

    if(file1 == NULL)
    {
        printf( "File1 failed to open." );
    }
    else
    {
        content = fgetc(file1);
        while(content!=EOF)
        {
            if(content>='A' && content<='Z')                //condition to change upper to lower
            {
                content = tolower(content);
                fputc(content, file3);
                content = fgetc(file1);
            }
            else                                            //condition to change lower to upper
            {
                content = toupper(content);
                fputc(content, file3);
                content = fgetc(file1);
            }
        }
        printf("Content modified successfully");
    }

    /*file1 = fopen("sample_1.txt", "r");
    file3 = fopen("sample_3.txt", "w");


    if(file1 == NULL)                               //checking whether file1 is created or not
    {
        printf( "File1 failed to open." );
    }
    else
    {
        content = fgetc(file1);
        while(content!=EOF)
        {
            content = toupper(content);             //converting to upper case
            fputc(content, file3);
            content = fgetc(file1);
        }
        fclose(file1);
        fclose(file3);

        printf("File Modified to UPPER CASE and saved in sample3 Successfully\n");
    }


    file1 = fopen("sample_1.txt", "r");
    file4 = fopen("sample_4.txt", "w");


    if(file1 == NULL)                               //checking whether file1 is created or not
    {
        printf( "File1 failed to open." );
    }
    else
    {
        content = fgetc(file1);
        while(content!=EOF)
        {
            content = tolower(content);             //converting to lower case
            fputc(content, file4);
            content = fgetc(file1);
        }
        fclose(file1);
        fclose(file4);

        printf("File Modified to lowercase and saved in sample_4.txt Successfully\n");
    }*/

}
