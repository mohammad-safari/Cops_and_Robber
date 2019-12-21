/*            list of functions and fields used in my game, classified and described briefly           */

/*                                             global fields                                           */
//actually nothing!
char empty = ' ';

//roles as time
int turn = 0;
//Dimensions
int m = 1, n = 1;
//number of stations
int ps = 0;
//number of cops
int total_cops = 0;

//Gang's Streets!;D
char board[25][25];
/*Station Parameters! ->
                        1. number of recruited cops
                        2. last reporting cop no. or -1(no report)
                        3, 4. i, j of last report*/
int plc_stn[10][4];
//Cops location classified by each station!
int cop_loc[10][10][2];
//Robber location
int rob_loc[10][2];
//used as a return of chk_neighbor when robber recognized
int neighbor[4];

/*                                            moving function!                                         */

//subsidary moving function!
void board_swap(int fi, int fj, int li, int lj);
//general move function!
void board_move(int i, int j, int who, int which, int x, int y);
//a general move function in random
void rand_move(int i, int j, int who, int which);
//a function for tracing and fleeing!!
void aware_move(int who, int which, int ri, int rj);

/*   looking arround in a given radius! for cops(inp: any num but -1 out: first founded police num + 1
     or 0->null) and robber(inp: -1 out: -1 and first founded robber loc in neighbor array or 0->null)   */
int chk_neighbor(int i, int j, int r, int who);

/*                                         intializing functions!                                        */

//getting values and authorizing them by chk_input help
void game_input(int in);
//helping to authorize input values
int chk_input();

//a function to perform new board!
int initialize_board();
//locating elements on board!
int rand_position();

/*                                        game UI & main functions                                       */

//a function for graphing the board
void board_design();
//a userfriendly behaviour at the end of game!:)
void game_menu();
//a function in which all other functions are called and where actually game flows!
int game_panel(int f);
//an input stream function for user to control time
int getch(void);
