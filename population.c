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
    while (n < 9);

    // TODO: Prompt for end size

    int end;
    do
    {
        end = get_int("What is the ending population size? ");
    }
    while (end < n);

    // TODO: Calculate number of years until we reach threshold

    int born = (n / 3);
    int death = (n / 4);

    int years;
    
    for (years = 1; n >= end; years++)
    {
         n = (n + (born - death) * years);
    }


    // TODO: Print number of years
   printf("Years: %i\n", years);

}