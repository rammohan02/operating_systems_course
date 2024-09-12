// Ram Mohan - COE19B055
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a=10, *p;
    p = &a;

    printf("Address of integer variable: %d\n", p);        //printing address of an integer variable

    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    p = b;
    for(int i=0; i<10; i++)
    {
        //p = &b[i];
        printf("Address of %d element in array: %d \n", i+1, p++);      //printing address of an array elements
    }
}
