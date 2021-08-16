#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)

{
    float dollars;

    // ask user for change

    do
    {
        dollars = get_float("How much change is owed? ");
    }
    while (dollars < 0.009);

    // obtain change in integer

    int cents = round(dollars * 100);

    // calculate minimum coins needed

    int q = cents / 25;

    int d = (cents - (q * 25)) / 10;

    int n = (cents - (q * 25) - (d * 10)) / 5;

    int p = (cents - (q * 25) - (d * 10) - (n * 5)) / 1;

    int coins = q + d + n + p;

    printf("Minimum coins needed: %i\n", coins);

}