
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

// Function prototypes

void avoidCycle(int count[]);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // count for invalid usage
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
int updateRanks = 0;
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            rank = i;
            ranks[updateRanks] = rank;
            updateRanks = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
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
    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by margin of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {

            int pair1_margin = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];

            int pair2_margin = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (pair1_margin < pair2_margin)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    int count[MAX] = {0};


    avoidCycle(count);

    for (int k = 0; k < pair_count; k++)
    {
        if (count[k] != 1)
        {
            locked[pairs[k].winner][pairs[k].loser] = true;
        }
    }
}
//Remove cycle
void avoidCycle(int count[])
{
    int record, cycle;

    int temp1, temp2, temp3, temp4, temp5;

    int j = pair_count - 1;

    for (; true; j--)
    {
        if (j < 0)
        {
            break;
        }

        if (count[j] != 1)
        {
            cycle = 0;
            record = j - 1;

            temp2 = pairs[j].winner;
            temp1 = pairs[j].loser;


            for (; true; record--)
            {
                if (record < 0)
                {
                    break;
                }
                if (temp2 == pairs[record].loser)
                {
                    temp2 = pairs[record].winner;
                    cycle++;
                }
                if (cycle == 1)
                {
                    temp3 = pairs[record].winner;
                }
                else if (cycle == 2)
                {
                    temp4 = pairs[record].winner;
                }
                else if (cycle == 3)
                {
                    temp5 = pairs[record].winner;
                }
                // arrange edges in decreasing strength
                if (cycle == 2 && temp1 == pairs[record].winner && temp3 == pairs[record].loser)
                {
                    count[j] = 1;
                    j = pair_count;
                    break;
                }
                else if (cycle == 3 && temp1 == pairs[record].winner && temp4 == pairs[record].loser)
                {
                    count[j] = 1;
                    j = pair_count;
                    break;
                }
                else if (cycle == 4 && temp1 == pairs[record].winner && temp5 == pairs[record].loser)
                {
                    count[j] = 1;
                    j = pair_count;
                    break;
                }
            }
        }
    }

}
// Print the winner of the election
void print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        bool buff = false;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true) // move to next candidate and check if ith (looser == true)
            {
                buff = true;
                break;
                //break jth loop, ith loop continues iterating
            }
        }

        if (buff == true)
        {
            continue;
        }
        //candidate with the source
        else if (buff == false)
        {
            printf("%s\n", candidates[i]);
            return;
        }

    }

    return;
}
// {
//     for (int i = 0; i < pair_count; i++)
//     {
//         lock(i);
//     }
//     return;
// }
// void lock(int i)
// {
//     if (i == 0)
//     {
//         locked[pairs[i].winner][pairs[i].loser] = true;
//     }
//     lock(i - 1);
//     for (int j = 0; j < i; j ++)
//     {
//         if (locked[pairs[i].loser][pairs[i - j].winner] == false)
//         {
//             locked[pairs[i].winner][pairs[i].loser] = true;
//         }
//         else
//         {
//             locked[pairs[i].winner][pairs[i].loser] = false;
    
//         }
//     }
// }