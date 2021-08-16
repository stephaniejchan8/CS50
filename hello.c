#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Obtain user's name
    string answer = get_string("What is your name?\n");
    printf("hello, %s\n", answer);

}