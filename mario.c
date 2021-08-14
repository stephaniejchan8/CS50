#include <cs50.h>
#include <stdio.h>

int main(void)

{
    // ask user for pyramid height
    int p;
    do
    {
        p = get_int("Pyramid height: ");
    }
    while (p < 1 || p > 8);

    // acknowledge accepted pyramid height

    printf("Stored: %i\n", p);

    // create pyramid

    for (int h = 0; h < p; h++)
    {
        for (int d = (p - 1); d > h; d--)
        {
            printf(" ");
        }
        for (int w = 0; w < h; w++)
        {
            printf("#");
        }
        printf("#\n");
    }
}