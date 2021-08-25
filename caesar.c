#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int key_format(string cla);
int key_number(string key_string);

int main(int argc, string argv[])
{
    // Ask user for correct key
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (key_format(argv[1]) == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // Ask user for message that needs to be encrypted
        string plaintext = get_string("plaintext: ");

        // Convert key (string) in command line argument to key (integer)
        int key = key_number(argv[1]);

        // Convert and print ciphertext
        printf("ciphertext: ");
        int n = strlen(plaintext);
        int c[n];
        for (int i = 0; i < n; i++)
        {
            if (isupper(plaintext[i]))
            {
                c[i] = ((plaintext[i] - 65 + key) % 26) + 65;
                printf("%c", (char) c[i]);
            }
            else if (islower(plaintext[i]))
            {
                c[i] = ((plaintext[i] - 97 + key) % 26) + 97;
                printf("%c", (char) c[i]);
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;
    }
}

// Function: check if string is an integer.

int key_format(string cla)
{
    int n = strlen(cla);
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        if (ispunct(cla[i]) || isalpha(cla[i]))
        {
            x++;
        }
    }
    if (x > 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Function: convert type (string) to type (integer)
int key_number(string key_string)
{
    int n = strlen(key_string);
    int digit = 0;
    for (int i = 0; i < n; i++)
    {
        digit += ((int) key_string[i] - 48) * (pow(10, (n - i - 1)));
    }
    return digit;
}
