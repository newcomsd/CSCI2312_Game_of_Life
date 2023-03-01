/***********************************************************
Stephen Newcomb comments
March 1st, 2023

All new comment by Stephen Newcomb will start with "SN:"

***********************************************************/

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
/*SN:The above code is pulling all the needed library's for Conway's Game of life including:
iostream - for input/output functions
chrono - for time-type functions (clock, duration, etc.)
thread - for concurrent, running functions
string - string aka text functions
*/


// Info for Sleep function:
// https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
/*SN:The above code declares the related identifiers throughout the program below to assist with code
convenience and clarity.*/


const int WIDTH = 50;
const int HEIGHT = 20;
const float init_probability_alive = 0.5;
/*SN:The above code declares/initializes constants throughout the program that define the width of the game
(50 columns), height (20 rows), and the initial probability of each cell being 'alive' at the start (50%)*/


// W => Windows
// M => Mac
// L => Linux
const char SYSTEM = 'W';
//SN: Another constant declared/initialized for the whole program that defines a Windows user

struct Cell{
    int sum = 0;
    bool alive = false;
    bool will_switch = false;
};
/*SN: This structure defines the possibilities for each 'alive' cell, and whether it can
turn 'alive' or if it will switch*/


void clear_console(){
    //SN: A void statement clearing the console per the system user
    switch(SYSTEM){
        //SN: a switch statement determine the 'type' of system (Windows, Mac, Linux)
        case 'W':
            system("cls");
            break;
        case 'M':
        case 'L':
            std::cout << "\x1B[2J\x1B[H";
            break;
        default:
            break;
        /*SN: Based off the system type, these case statements determine the necessary actions on
        how to clear the console*/
    }
}

bool is_init_alive(){
    // Get a random value between 0 and 1
    //SN: AND is defined by a boolean function (true/false, 1/0)
    double r = ((double) rand() / (RAND_MAX));
    //SN: declaring r as the 'random' variable and uses the rand() function to pull the random number
    if (r < init_probability_alive){
        return true;
    }
    // There's no else statement here, will this still work?
        //SN: Yes, if statements still work with no 'else' statement
    //SN:Essentially, based off the bool r variable, this if statement determines which cells are alive
    return false;
    //SN:not much to say here, but that this is the proper way to close a boolean function
}

void init_game(Cell cell[HEIGHT][WIDTH]){
    //SN: This function is calling the height (rows) and width (columns) of the game
    for(int i = 0; i < HEIGHT; i++){
        //SN: This loop builds out the height of the program
        for(int j = 0; j < WIDTH; j++){
        //SN: This loop builds out the width of the program
            bool is_alive = false;
        //SN: This boolean statement turns all the cells 'dead'
            if(i > 0 && i < HEIGHT-1 && j > 0 && j < WIDTH-1){
                is_alive = is_init_alive();
            }
        //SN: This part is fun: it sets a 'dead' border around the perimeter of the box. None of these cells can 'live'
            cell[i][j].alive = is_alive;
        //SN: This turns the random cells 'alive' (50% per the is_init_alive random calculation)

        }
    }
}

int main() {
    //SN: The fun is about to begin; the main function for the game :-)
    std::cout << "game start, type a number" << std::endl;
    //SN: Asking the user for a number to seed the random function that determines the alive/dead cells
    int temp_seed;
    char temp;
    std::cin >> temp_seed;
    /*SN: The 3 lines above declare the temp seed as an in, collect the value from the user, and declare temp as a
    char date type*/
    srand(temp_seed);
    //SN: random function for the temp seed that was inputted by the user
    unsigned int round_count = 1;
    //SN: this unsigned integer initializes variable 'round_count' to 1
    Cell cell[HEIGHT][WIDTH];
    //SN: Calling the proper height and width for the grid
    init_game(cell);
    bool game_running = true;
    // Allow user to exit after x rounds
    //SN: nothing to add here; allows the user to exit after a given number a rounds
    int round_pause = 200;
    //SN: this int variable determines how many rounds will run before the came is paused... in this case, 200 rounds
    while(game_running){
    //SN: Here we go!  The while loop for the game to start and run!
        // Draw the grid
        bool all_dead = true;
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTH; j++){
                if(cell[i][j].alive){
                    all_dead = false;
                }
        //SN: This loop draws the grid and places the random alive & dead cells throughout the game
                if(i > 0 && i < HEIGHT-1 && j > 0 && j < WIDTH-1){
                    int sum = 0;
        //SN; This draws the outline of the grid so no cells can be 'alive' on the furthest perimeter
                    for(int k = -1; k <= 1; k++) {
                        for (int m = -1; m <= 1; m++) {
                            // Check to make sure [i][j] isn't self
                            //SN: Nothing to add here
                            if(k == 0 && m ==0){
                                continue;
                            /*SN: Properly continues the loop as long as k & m equal 0... thereby, making sure
                            if after [i][j] are not defined as themselves*/
                            }
                            if(cell[i+k][j+m].alive){
                                sum += 1;
                            //SN: if the cell is alive, it's returning a 'true' value (aka 1) to the boolean "sum"
                            }
                        }
                    }
                    cell[i][j].sum = sum;
                    //SN: Flipping 'on' the 'true' cells for each iteration
                    if(cell[i][j].alive){
                        if(sum > 3 || sum < 2){
                            cell[i][j].will_switch = true;
                        /*SN: Per the rules of the game, this if statement is examining cells to determine whether
                         or not they may flip on the next iteration (ie. if the sum around the
                         cell is greater than three or less than 2  if so, it'll flip) */
                        }
                    }else{
                        if(sum == 3){
                            cell[i][j].will_switch = true;
                        /* SN: This is another potential possibility to determine if a cell will flip based on the rules
                        of the game*/
                        }
                    }
                }
            }
        }

        std::string curr_line;
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTH; j++){
                if(cell[i][j].alive){
                    curr_line += "0 ";
                    //SN: As the program iterates/refreshes, this outputs a zero and space for the 'alive' cells
//                    std::cout << cell[i][j].sum << " ";
                }else{
                    curr_line += ". ";
                    //SN: As the program iterates/refreshes, this outputs a period and space for the 'dead' cells
                }
                if (cell[i][j].will_switch){
                    cell[i][j].alive = !cell[i][j].alive;
                    cell[i][j].will_switch = false;
                    /*SN: This if statement is examining whether or not a cell will turn 'dead' or 'alive' per the
                    above loops*/
                }
            }
            curr_line += '\n';
            //SN: Creates a new line for each row
        }

        clear_console();
//        sleep_until(system_clock::now() + 50ms);
        //SN: clears the console after the game has been run sets the current clock to be +50ms
        std::cout << curr_line << std::endl;
        //SN: draws the grid

        sleep_until(system_clock::now() + 50ms);
        //SN: After the game has been run, this 'sleep's' the console for 50ms past the current moment
        if(all_dead){
        //SN: If statement to determine the output after the game has been run
            std::cout << "All life has been exterminated. Good job, hero." << std::endl;
            printf("It survived for %d rounds. Continue? Y/N",round_count);
        /*SN: In a witty fashion, this tells the user how many iterations the game ran for BEFORE all cells died.  And
        allows the user to try again*/
            std::cin >> temp;
            if(temp == 'N' || temp == 'n'){
                printf("Good call. See ya.");
                game_running = false;
        //SN: If the user says N or n, the game terminates and closes
            }else{
                init_game(cell);
        //SN: If the user tries again, then the game will re-run
            }
        }
        if(round_count % round_pause == 0){
            printf("Paused at %d rounds. Enter n to escape, or anything else to continue.",round_count);
            std::cin >> temp;
        //SN: allows the user to pause the game, and chose to end the program, or continue with the simulation
            if(temp == 'N' || temp == 'n'){
                printf("Good call. See ya.\n");
                game_running = false;
        //SN:If the user chooses to end the game during a pause, this exits and closes the program
            }
            if(temp == 'R' || temp == 'r'){
                init_game(cell);
        //SN: Asks the user for a random seed to initiate the game again
            }
        }

        round_count++;
        /*SN: adds 1 to the 'round count' (this give an accurate count to the number of rounds because
        coding iterations always start at 0*/
//        std::cout << rand() << std::endl;
    }
    return 0;
    //SN: ENDS the main function!
}

//SN: Phew!  That was fun!
