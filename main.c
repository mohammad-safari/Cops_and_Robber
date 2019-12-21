#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game_header.h"
#include "move_funcs.c"
#include "init_funcs.c"
#include "getch.c"

//if running on windows uncomment the line below
//#define clear cls
//if you decide to use getchar instead of getch uncomment the line below
//#define getch getchar
//note: everywhere i,j shows matrix element(for arr!:) and x, y is descartian element

void board_design()
{
    //Clear terminal
    system("clear");
    //Control Size
    printf("\033[8;35;130t");
    //Title!
    printf("%57c\033[34mCops\033[0m and \033[31mRobber\033[0m!\n\n\n", '\0');

    //Rows!
    printf("  ");
    for (int j = 0; j < n; j++)
        printf(" %0*d ", 2, j + 1);
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        //SubColumns? or some decorations!
        printf("  ");
        for (int k = 0; k < n; k++)
            printf("*---");
        printf("*\n%0*d", 2, i + 1);

        //Columns!
        for (int j = 0; j < n; j++)
        {
            printf("|");
            if (board[i][j] == 'R')
                printf(" \033[41;34m%c\033[0m ", 'R');
            else if (board[i][j] == empty)
                if (chk_neighbor(i, j, 2, 1))
                    printf(" \033[42m%c\033[0m ", board[i][j]);
                else
                    printf(" \033[47m%c\033[0m ", board[i][j]);
            else
                printf(" \033[44;31m%c\033[0m ", board[i][j]);
        }
        printf("|\n");
    }

    //Bottom Line!
    printf("  ");
    for (int k = 0; k < n; k++)
        printf("*---");
    printf("*\n\n");

    //Some info for user!
    // chk_neighbor(rob_loc[0][0], rob_loc[0][1], 1, 1);
    printf("%55cStatus: %c Move %dth\n%50cPress Any Key for Next Move\n\n", '\0', '\0', turn++, '\0');
    // usleep(3000);
    fflush(stdin);
    getch();
}

void game_menu()
{
    int flag = 1;
    while (flag)
    {
        int in;
        system("clear");
        printf("%60c\033[34mCops\033[0m and \033[31mRobber\033[0m:\n\n%63c\033[33mBY M_Safari\033[0m\n\n", '\0', '\0');
        printf("%67c\033[35mMenu\033[0m\n\n", '\0');
        printf("%62c\033[35m0 - Exit Game\033[0m\n", '\0');
        printf("%59c\033[35m1 - Continue to Game!\033[0m\n", '\0');
        printf("%59c\033[35m2 - Change Dimension!\033[0m\n", '\0');
        printf("%50c\033[35m3 - Change Police Stations and Cops number!\033[0m\n", '\0');
        printf("%50c\033[35m4 - Change Each Police Station Cops number!\033[0m\n", '\0');
        printf("%69c\n", '\0');
        // scanf("%d", &in);
        fflush(stdin);
        in = getch();
        switch (in)
        {
        case '0':
            flag = 0;
            break;
        case '1':
            game_panel(initialize_board());
            break;
        default:
            game_input(in - '0');
        }
        if (!flag)
            break;
    }
}

int game_panel(int f)
{
    int rob = 1 + f; //value (not variable) will be robbers number!
    while (rob > 0)
    {
        //Cops move first
        //first of all gathering street report
        for (int i = 0; i < ps; i++) //each station
        {
            plc_stn[i][1] = -1;                     //default is that there is no report of robbery in each station!!
            for (int j = 0; j < plc_stn[i][0]; j++) //each cop
            {
                if (chk_neighbor(cop_loc[i][j][0], cop_loc[i][j][1], 2, -1) == -1) //check if there is any robber
                {
                    plc_stn[i][1] = j; //report scouting a robber
                    //report content(location of robber in last seen)
                    plc_stn[i][2] = neighbor[0];
                    plc_stn[i][3] = neighbor[1];
                }
                else if (plc_stn[i][1] == j)
                {
                    plc_stn[i][1] = -1; //if the reporting cop has lost the track of robber or robber has been caught
                }
            }
            //check if there is any available report for this station
            if (plc_stn[i][1] > -1)
            {
                aware_move(1, i, neighbor[0], neighbor[1]); //after gathered from one station all recruited cops of the station
                //start to trace according to "last" report(may be a bug and lacking something!)
                continue; //visiting another station
            }
            //start moving random if there is not any report!
            for (int j = 0; j < plc_stn[i][0]; j++)
                rand_move(cop_loc[i][j][0], cop_loc[i][j][1], j, i);
        }

        //robber start moving!
        if (chk_neighbor(rob_loc[0][0], rob_loc[0][1], 2, 1) > 0)
            aware_move(-1, 0, rob_loc[0][0], rob_loc[0][1]);
        else
            rand_move(rob_loc[0][0], rob_loc[0][1], -1, 0);

        board_design();
        if (chk_neighbor(rob_loc[0][0], rob_loc[0][1], 1, 1) > 0) //check if a cop is near to robber
        {
            rob--; //the robber caught!
            board[rob_loc[0][0]][rob_loc[0][1]] = empty;
            board_swap(neighbor[2], neighbor[3], rob_loc[0][0], rob_loc[0][1]);
            board_design();
            printf("\n%47c\033[41mRobber Caught On Move %dth on %d %d\033[0m\n", '\0', --turn, rob_loc[0][0] + 1, rob_loc[0][1] + 1);
        }
        
    }
    printf("%53c\033[33mStreets are Safe now!\n%50cPress Any Key to Go to Menu!\033[0m\n", '\0', '\0');
    // usleep(1000);
    getch();
}

int main()
{
    //Control Size

    printf("\033[8;35;140t");
    time_t t = time(NULL);
    srand(t);
    printf("%60c\033[34mCops\033[0m and \033[31mRobber\033[0m:\n\n%63c\033[33mBY M_Safari\033[0m\n\n", '\0', '\0');
    game_input(1);
    game_panel(initialize_board());
    game_menu();
}
