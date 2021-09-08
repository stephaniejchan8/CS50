#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int cycle_size;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_locked(int first_pair, int unlocked_pair);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if name matches a candidate's name.
        if (strcmp(name, candidates[i]) == 0)
        {
            // If matches, record voter's preference.
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If candidate i is preferred over j
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // If candidate j is preferred over i
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                // Create temporary winner and loser value to sort data without data getting lost/replaced
                int temp_winner = pairs[i].winner;
                int temp_loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = temp_winner;
                pairs[j].loser = temp_loser;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    locked[pairs[0].winner][pairs[0].loser] = true;
    locked[pairs[1].winner][pairs[1].loser] = true;
    for (int i = 2; i < pair_count; i++)
    {
        // Use recursive function to check for cycles
        int unlocked_pair = i;
        if (check_locked(i, unlocked_pair) == true)
        {
            // If pair will not cause cycle, then lock this pair.
            locked[pairs[unlocked_pair].winner][pairs[unlocked_pair].loser] = true;
        }
    }
    return;
}


// Print the winner of the election
void print_winner(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        int x = 0;
        for (int j = 0; j < pair_count; j++)
        {
            // Check locked matrix to see which candidate is never locked in as a loser
            if (locked[j][i] == false)
            {
                x++;
                if (x == pair_count)
                {
                    // Print winner
                    printf("%s\n", candidates[i]);
                    return;
                }
            }
        }
    }
    return;
}


// RECURSION function to check for cycles in locking pairs
bool check_locked(int first_pair, int unlocked_pair)
{
    for (int second_pair = 0; second_pair < unlocked_pair; second_pair++)
    {
        // Check if the loser of last pair in cycle is the winner of another locked pair
        if (pairs[first_pair].loser == pairs[second_pair].winner && locked[pairs[second_pair].winner][pairs[second_pair].loser] == true)
        {
            // Check if this cycle returns to subject pair
            if (pairs[second_pair].loser == pairs[unlocked_pair].winner)
            {
                return false;
            }
            else
            {
                // Recursion to keep checking if cycle created with subject pair
                if (check_locked(second_pair, unlocked_pair) == false)
                {
                    // Cycle created if pair is locked
                    return false;
                }

            }
        }
    }
    // no cycle created if pair is locked
    return true;
}
