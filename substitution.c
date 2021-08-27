#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <strings.h>

#define _GNU_SOURCE
#include <string.h>

bool alpha_only(string command);
bool full_alpha(string command2);

int main(int argc, string argv[])
{

    // Check that user input only 1 command line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check that key is 26 characters only
    else if (strlen(argv[1]) != 26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check that key is alphabetical only
    else if (alpha_only(argv[1]) == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check that key has no duplicates in alphabet
    else if (full_alpha(argv[1]) != 0)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // Ask user for plain text
        string plain = get_string("plaintext: ");
        // Convert plaintext to cyphertext
        int n = strlen(plain);
        printf("ciphertext: ");
        for (int i = 0; i < n; i++)
        {
            // print uppercase letters
            if isupper(plain[i])
            {
                int up = plain[i] - 65;
                printf("%c", toupper(argv[1][up]));
            }
            // print lowercase letters
            else if islower(plain[i])
            {
                int lower = plain[i] - 97;
                printf("%c", tolower(argv[1][lower]));
            }
            // print non-alphabetical characters
            else
            {
                printf("%c", plain[i]);
            }
        }
        printf("\n");
        return 0;
    }

}

    // Formula: Check that command is alphabetical only
bool alpha_only(string command)
{
    int n = strlen(command);
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        if (isalpha(command[i]))
        {
            x += 0;
        }
        else
        {
            x++;
        }
    }
    if (x == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Formula: Check that string has no duplicates in alphabet
bool full_alpha(string command2)
{
    int x = 0;
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (command2[i] == command2[j])
            {
                x++;
            }
            else
            {
                x += 0;
            }
        }
    }
    if (x == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}