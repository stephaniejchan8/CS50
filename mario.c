#include <cs50.h>
#include <stdio.h>

int main(void)

{
    // obtain height from user
    int p;
    do
    {
        p = get_int("Height: ");
    }
    while (p < 1 || p > 8);

    // create pyramid

    for (int h = 0; h < p; h++)
    {
        for (int s = (p - 1); s > h; s--)
        {
            printf(" ");
        }
        for (int r = 0; r < h; r++)
        {
            printf("#");
        }
        printf("#  #");
        for (int row = 0; row < h; row++)
        {
            printf("#");
        }
        printf("\n");
    }
}