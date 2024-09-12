//Ram Mohan - COE19B055
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main()
{
    FILE *file1, *file2;
    char content;

    file1 = fopen("sample_2.txt", "r");

    if(file1 == NULL)                               //checking whether file1 is created or not
    {
        printf( "File1 failed to open." );
    }
    else
    {
        file2 = fopen("sample_5.txt", "w");         //opening file2

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
            fclose(file1);
            fclose(file2);
        }
    }


    //Now removing vowels and moving it to original file from temporary file
    file1 = fopen("sample_5.txt", "r");
    if(file1 == NULL)
    {
        printf("File failed to open");
    }
    else
    {
        file2 = fopen("sample_2.txt", "w");

        content = fgetc(file1);
        while(content!=EOF)
        {
            if(!(content=='A' || content=='E' || content=='I' || content=='O' || content=='U' ||
               content=='a' || content=='e' || content=='i' || content=='o' || content=='u'))
            {
                fputc(content, file2);
            }
            content = fgetc(file1);
        }
        fclose(file1);
        fclose(file2);

        remove("sample_5.txt");             //removing the temporary file

        printf("Removed vowels from sample_2.txt successfully");
    }
}
