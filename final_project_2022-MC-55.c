/*The following is the code for the Semester Project of CP-1
Written by Muhammad Rayan 2022-MC-55 (Section B)

//////////////////////////////////////////////////////////////////////////

The task for the project was to design a Genetic Algorithm that would arrange the the knights
in such a way on the chess board such that the knights are doing the maximum attacks a.k.a covering
the most boxes

/////////////////////////////////////////////////////////////////////////

Following is the code for how I approached the problem!
this approach of mine is done in such a way that the program a.k.a the Algorithm will
takes the no. of knights from the user as well as the no.of generations that the user wants
and evaluates through the algorithm and gives the output generation where the knights do maximum attacks
as to try to cover the whole board

/////////////////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h> //standard library
#include <time.h>   //time library to provide seed and enhance the randomizing of the functions

#define MAX_KNIGHTS 30    // Maximum number of knights
#define BOARD_SIZE 8      // Board size (assuming an 8x8 board)
#define MUTATION_RATE 0.1 // Mutation rate

typedef struct // this is a position struct to store the position of knights on the board
{
    int x; // row
    int y; // column
} Position;

/*the following function is to generate the random initial population of knights
from the user input*/

void initialize_population(int num_knights, Position population[])
{
    srand(time(NULL)); // Seed for random number generation

    for (int i = 0; i < num_knights; i++) // the for loop assigns a random position to the knights for the value of i
    {
        population[i].x = rand() % BOARD_SIZE; // Random x-coordinate
        population[i].y = rand() % BOARD_SIZE; // Random y-coordinate
    }
}

/*The following display_board function is responsible for visually
 representing the current positions of the knights on the 8x8 chessboard grid*/

void display_board(Position population[], int num_knights)
{
    char chessboard[BOARD_SIZE][BOARD_SIZE]; // this is to assign the chessboard a two dimensional array of 64 elements a.k.a chessboard

    for (int i = 0; i < BOARD_SIZE; i++) // this loop will assign all the characters in the board the '.' character which can be changed later on
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            chessboard[i][j] = '.';
        }
    }

    for (int k = 0; k < num_knights; k++) // this loop is to represent the position of knights on the board '.' is replaced with 'k'
    {
        int x = population[k].x; // for the x coordinate of k
        int y = population[k].y; // for the y coordinate of k
        chessboard[x][y] = 'K';
    }

    printf("\nChessboard with %d knights:\n\n", num_knights); // this will be our heading showing how many knights are present in the current chess board

    for (int i = 0; i < BOARD_SIZE; i++) // this loop will generate the board with the characters previously stored in the array
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf("%c ", chessboard[i][j]);
        }
        printf("\n");
    }
    printf("\n"); // starting a new line for neatness
}

/*the following function calculates the number of squares attacked by knights
this function also aids in calculating the fitness of our solution*/

int count_attacked_squares(Position population[], int num_knights)
{
    int attacked[BOARD_SIZE][BOARD_SIZE] = {{0}};
    int total_attacked = 0;

    // the following arrays store the 8 possiblemoves for the knight in rows and columns

    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2}; // for columns moves  in the x coordinate
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1}; // for rows moves     in the y coordinate

    for (int k = 0; k < num_knights; k++) // this loop esenially checks which of the block have been attacked by the knghts
    {
        int x = population[k].x;
        int y = population[k].y;

        for (int move = 0; move < 8; move++)
        {
            int new_x = x + dx[move]; // attacked box x coordinate
            int new_y = y + dy[move]; // attacked box y coordinate

            if (new_x >= 0 && new_x < BOARD_SIZE && new_y >= 0 && new_y < BOARD_SIZE) // this condition needs to be satisfied so that the bound of the board is not exceeded
            {
                attacked[new_x][new_y] = 1; // the attacked boxes are stored in this array as 1 and un attacked as 0    
            }
        }
    }

    /*this loop calculates the no. of squares that have remained unattacked on the chessboard*/

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            total_attacked += !attacked[i][j]; // this logic stores the elements in the attacked array mentioned as 0 and the not operator allows us to save the zeros as 1 and that gives us the unattacked squares or the fitness of our board
        }
    }

    return total_attacked; // the integer value of unattacked squares is returned
}

/*this function creates new offsprings for the next genertion
this is an integra part of the Genetic Algorithm*/

void crossover(Position parent1[], Position parent2[], Position offspring[], int num_knights) // two array from the position are taken and a new array of offspring is the output essesntially
{
    int crossover_point = rand() % num_knights; // a random cross over point is taken which is the modulus of the number of knights entered so that we get a valid crossover point

    for (int i = 0; i < crossover_point; i++) // implementing the cross over from parent 1 for the first part of the offspring array
    {
        offspring[i] = parent1[i];
    }

    for (int i = crossover_point; i < num_knights; i++) // implementing cross over from the second parent for the second part of the offspring array
    {
        offspring[i] = parent2[i];
    }
}
/*the following function generates mutation in the offspring based on the
mutation rate defined earlier its can be changed to get even more variations
Mutation helps introduce diversity into the population by slightly altering some individuals*/

void mutation(Position population[], int num_knights) // the population array is again initiated
{
    for (int i = 0; i < num_knights; i++)
    {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) // if the answer of the fraction is less than te mutation rate then mutation will occur
        {
            population[i].x = rand() % BOARD_SIZE; // the mutation occurs at x coordinate for the i cell in population array
            population[i].y = rand() % BOARD_SIZE; // the mutation occurs at y coordinate for the i cell in population array
        }
    }
}

/*following is the main function where are evaluating the output by implementing
the functions mentioned above to generate the output via Genetic Algorithm*/

int main()
{
    Position initial_population[MAX_KNIGHTS];          //this will prevent the initial population from incraesing from the max value
    Position offspring[MAX_KNIGHTS];                   //this will prevent the initial offspring number from increasing than te=he max value
    int num_knights, generation_limit;

    printf("Enter the number of knights: ");       //user inputs for the number of knights
    scanf("%d", &num_knights);
    printf("Enter the number of generations: ");    //user inputs for the no. of generation 
    scanf("%d", &generation_limit);

    if (num_knights <= 0 || num_knights > MAX_KNIGHTS)
    {
        printf("Invalid number of knights.\n");
        return 1;
    }

    initialize_population(num_knights, initial_population);   //applying functions for getting the initial population 
    display_board(initial_population, num_knights);           // applying function for the display of the chess board

    int initial_fitness = count_attacked_squares(initial_population, num_knights);
    printf("Initial fitness: %d\n", initial_fitness);

    //following lies the the genetic algorithm arranged in such a way to estalish evoloution //

    int current_generation = 0;                 //this is to keep track of current generation
    int best_fitness = initial_fitness;

    while (current_generation < generation_limit)                                 //the loop of the algorithm will continue till all the generations are solved
    {
        printf("Generation %d - Best fitness: %d\n", current_generation + 1, best_fitness);    //this prints the current generation and the best fitness found so far
        display_board(initial_population, num_knights);                                        //displays the number of knights for the current generation 

        for (int i = 0; i < num_knights; i += 2)       //the loop iterates through the knights in pairs for crossover and mutation as pairs are needed for that
        {
            crossover(initial_population, initial_population + i, offspring, num_knights);      //the functions Perform crossover between pairs of knights from the initial population, producing offspring
            mutation(offspring, num_knights);                                                   //the function Mutates the offspring, altering their positions randomly based on the mutation rate

            int offspring_fitness = count_attacked_squares(offspring, num_knights);             //fitness is calculated as the squares not being attacked 

            if (offspring_fitness < best_fitness)              //this condition ensures that the fitness value will change if the fitness of the offspring is less than the parent 
            {
                best_fitness = offspring_fitness;
                for (int j = 0; j < num_knights; j++)            //this loop will update the initial population to the offspring value so that the new population a.k.a the new generation can be used for the nect itteration
                {
                    initial_population[j] = offspring[j];
                }
            }
        }

        current_generation++;             //incrementing the generation number
    }

    printf("Final best fitness after %d generations: %d\n", generation_limit, best_fitness);      //printing the final value of generation and the fitness 

    return 0;
}
// End of Program!
// FINALLY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!