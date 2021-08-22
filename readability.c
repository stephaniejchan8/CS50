#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Obtain text from user.
    string text = get_string("Text: ");
    // Calculate number of letters in text.
    int n = strlen(text);
    int letters = 0;
    for (int i = 0; i < n; i++)
    {
        if isalpha(text[i])
        {
            letters++;
        }
    }
    // Calculate number of words in text.
    int words = 0;
    for (int i = 0; i < n; i++)
    {
        if isspace(text[i])
        {
            words++;
        }
    }
    if (letters > 0)
    {
        words++;
    }

    // Calculate number of sentences in text.
    int sentences = 0;
    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Calculate average number of letters per 100 words.
    double avletters = letters / (double) words * 100;

    // Calculate average number of sentences per 100 words.
    double avsentences = sentences / (double) words * 100;

    // Input averages into index.
    double index = 0.0588 * avletters - 0.296 * avsentences - 15.8;

    // Calculate and print out reading level.
    int level = (int) round(index);
    if (level >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }
}