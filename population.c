#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int n;
    do
    {
        n = get_int("What is the starting population size? ");
    }
    while (n < 10);

    // TODO: Prompt for end size

    int end;
    do
    {
        end = get_int("What is the ending population size? ");
    }
    while (end < n);

    // TODO: Calculate number of years until we reach threshold

    int y;
    
    for (y = 1; n >= end; y++)
    {
         n = (n + ((n / 3) - (n / 4)) * y);
         printf("Years: %i\n", y);
    }


    // TODO: Print number of years
 

}