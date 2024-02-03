
#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{

    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }


    for (int i = 0; i < voter_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);


        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
    {
  for(int i = 0; i < candidate_count; i++)
  {
        if(strcmp(name, candidates[i].name)==0)
        {

            preferences[voter][rank] = i;
            return true;
        }
  }
    return false;
    }



// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for(int voter = 0; voter<voter_count; voter++)
    {
        for(int ranks = 0; ranks < candidate_count; ranks++)
        {
            int c = preferences[voter][ranks];
            if(!candidates[c].eliminated)
            {
                candidates[c].votes++;

                break;
            }
        }
    }
}

// Print the winner of the election, if the winner exists
bool print_winner(void)
{
    for(int candidate = 0; candidate < candidate_count; candidate++)
    {
        if(candidates[candidate].votes > voter_count / 2)
        {
            printf("%s\n", candidates[candidate].name);
            return true;
        }
    }
    return false;
}

// Return the smallest number of votes any  candidate has
int find_min(void)
{
    int smallest[] = {voter_count,1};
    for(int i = 0; i < candidate_count; i++ )
    {

        // store smallest number of votes on <smallest[0]>, if smallest[0] > candidates[i].votes, replace smallest[0] with it.
        if(smallest[0] > candidates[i].votes && candidates[i].eliminated == false)
        {
            smallest[0] = candidates[i].votes;
        }
    }
    return smallest[0];


}

// Return true if the election is tied anything else is false
bool is_tie(int min)
{
    int tieCount = 0;
    int onRun = 0;
    for(int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].eliminated == false && candidates[c].votes == min)
        {
            tieCount++;
            onRun++;
        }
        else if(candidates[c].eliminated == false)
        {
            onRun++;
        }
    }
    if(tieCount == onRun)
    {
        return true;
    }
    return false;
}

// remove whoever is in last
void eliminate(int min)
{
    for(int c = 0; c < candidate_count; c++)
    {
        if(candidates[c].votes == min)
        {


            candidates[c].eliminated = true;
            // printf eliminated
        }
    }
}
