/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;
int i;
int j;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
int count;

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board                          //DO THIS FIRST
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int size = (d * d) - 1; // this will be the starting point (top left)
    
    for (int i = 0; i < d; i++) // iterate over the rows
    {
        for (int j = 0; j < d; j++) // iterate over the columns
        {
            board [i][j] = size;
            size--;//decrement counter
        }
    }
    

    
    if ((d) % 2 == 0) //if d is even, swap the 1 and the 2
    {
        board [d-1][d-3] = 1;
        board [d-1][d-2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        printf("\n");
        
        for (int j = 0; j < d; j++)
        {
            
            if (board[i][j] == 0)
            {
                printf(" 0 ");
            }
            else
            {
                printf("%2i|  ", board[i][j]);
            }
        }
    }
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    
int r;//row
int c;//column

    
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            //left side
            if (board[i][j] == tile) //increments board looking for location
            {
                r = i; //saves  it to array
                c =j;
            }
        }
    }
    //look for all locations of legal places the variable can be
    if (board[r - 1][c] == 0 && r - 1 >= 0)
    {
        board[r - 1][c] = board [r][c];
        board [r][c] = 0;
        return true;
    }
    else if (board[r + 1][c] == 0 && r + 1 < d)
    {
        board[r + 1][c] = board [r][c];
        board [r][c] = 0;
        return true;
    }
    else if (board [r][c +1] == 0 && d > c+1)
    {
        board[r][c+1] = board [r][c];
        board[r][c] = 0;
        return true;
    }
    else if (board[r][c -1] == 0 && c - 1 >=0)
    {
        board[r][c-1] = board[r][c];
        board[r][c] = 0;
        return true;
    }

return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
 
 int count = 0;
 
 if (board[d-1][d-1]!=0)
    { 
    return false;
    }
    
 for (int i = 0; i < d; i++)
 {
     for (int j = 0; j < d; j++)
     {
        count++;
        if (board [i][j] != count)
        {
            if (count < (d*d)){return false;}
         }
     }
 }
 return true;
}
