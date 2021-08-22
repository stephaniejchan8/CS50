#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
    printf("Player 1's score: %i\n", score1);
    printf("Player 2's score: %i\n", score2);
}

int compute_score(string word)
{
    // Convert word into uppercase
    int n = strlen(word);
    int character[n];
    int i;
    for (i = 0; i < n; i++)
    {
        character[i] = (int) toupper(word[i]);
    }
    // Obtain score for character, excluding non-letters.
    int x[n];
    for (i = 0; i < n; i++)
    {
        if (character[i] >= 65 && character[i] <= 90)
        {
            x[i] = POINTS[(character[i] - 65)];
        }
        else
        {
            x[i] = 0;
        }
    }
    // Compute and return score for string
    int score = 0;
    for (i = 0; i < n; i++)
    {
        score += x[i];
    }
    return score;
}
