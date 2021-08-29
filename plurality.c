#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Array of sorted candidates
    candidate sorted[MAX];
    for (int i = 0; i < candidate_count; i++)
    {
        sorted[i].name = candidates[i].name;
        sorted[i].votes = candidates[i].votes;
    }
    // Determine candidate with highest count
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes > sorted[0].votes)
            {
                sorted[0].name = candidates[i].name;
                sorted[0].votes = candidates[i].votes;
            }
    // If there is a tie, include tied winners
        if (candidates[i].votes == sorted[0].votes && strcmp(candidates[i].name, sorted[0].name) != 0)
        {
            for (int j = 1; j < candidate_count; j++)
            {
                if (candidates[i].votes > sorted[j].votes)
                {
                    sorted[j].name = candidates[i].name;
                    sorted[j].votes = candidates[i].votes;
                    j = candidate_count;
                }
                if (candidates[i].votes < sorted[j].votes)
                {
                    j = candidate_count;
                }
            }
        }
    }
    if (sorted[0].votes > sorted[1].votes)
    {
        printf("%s\n", sorted[0].name);
    }
    else if (sorted[0].votes == sorted[1].votes)
    {
        printf("%s\n", sorted[0].name);
        for (int i = 0; sorted[i].votes == sorted[i + 1].votes; i++)
        {
            if (strcmp(sorted[i].name, sorted[i + 1].name) != 0)
            {
                printf("%s\n", sorted[i + 1].name);
            }
        }
    }
}

