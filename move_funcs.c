void board_swap(int fi, int fj, int li, int lj)
{
    char hold = board[fi][fj];
    board[fi][fj] = board[li][lj];
    board[li][lj] = hold;
}

void board_move(int i, int j, int who, int which, int x, int y)
//briefly "who" refers to cop no. or -1(robber)
//but "which" is station no. for cops or robber no. because robbers are isolated, not in connection
{
    board_swap(i, j, i + y, j + x);
    if (who != -1)
    {
        cop_loc[which][who][0] = i + y;
        cop_loc[which][who][1] = j + x;
    }
    else
    {
        rob_loc[which][0] = i + y;
        rob_loc[which][1] = j + x;
    }
}

void rand_move(int i, int j, int who, int which)
{
    int x, y;
    do
    {
        x = rand() % 3 - 1;
        y = rand() % 3 - 1;
        if (i + y >= m || j + x >= n || i + y < 0 || j + x < 0)
            continue;
    } while (board[i + y][j + x] != empty && (x != 0 || y != 0));
    if (x == 0 && y == 0)
        return; //we can ignore it :), actually means staying there
    board_move(i, j, who, which, x, y);
}

void aware_move(int who, int which, int ri, int rj)
{
    if (who != -1) //this part is sepecified for cops
    {
        for (int k = 0; k < plc_stn[which][0]; k++) //k is no. of each cop!!
        {
            int *i = &cop_loc[which][k][0], *j = &cop_loc[which][k][1], flag = 0;
            int y = (ri - *i), x = (rj - *j);
            if (y != 0)
                y = abs(y) / y;
            if (x != 0)
                x = abs(x) / x;
            for (int s = 1; s >= 0; s--)
            {
                if (!flag)
                    for (int r = 1; r >= 0; r--)
                    {
                        if (board[*i + (r * y)][*j + (s * x)] != empty || (s == 0 && r == 0))
                            continue;
                        x *= s;
                        y *= r;
                        board_move(*i, *j, k, which, x, y);
                        flag = 1; //shows that cop could move successfully!
                        break;
                    }
            }
        }
    }
    else //this part is specified for robbers
    {
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                if (chk_neighbor(ri + y, rj + x, 2, 1) <= 0 && board[ri + y][rj + x] == empty)
                {
                    if (ri + y >= m || rj + x >= n || ri + y < 0 || rj + x < 0)
                        continue;
                    board_move(ri, rj, -1, 0, x, y);
                    return;
                }
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                if (chk_neighbor(ri + y, rj + x, 1, 1) <= 0 && board[ri + y][rj + x] == empty)
                {
                    if (ri + y >= m || rj + x >= n || ri + y < 0 || rj + x < 0)
                        continue;
                    board_move(ri, rj, -1, 0, x, y);
                    return;
                }
        rand_move(ri, rj, -1, 0);
    }
}
int chk_neighbor(int i, int j, int r, int forwho)
{
    for (int x = (-1 * r); x <= r; x++)
    {
        for (int y = (-1 * r); y <= r; y++)
        {
            //ignoring outside the range and the element itself
            if ((x == 0 && y == 0) || i + y >= m || j + x >= n || i + y < 0 || j + x < 0)
                continue;
            if (board[i + y][j + x] != empty)
            {
                if (forwho == -1)
                {
                    if (board[i + y][j + x] == 'R')
                    {
                        neighbor[0] = i + y;
                        neighbor[1] = j + x;
                        return -1;
                    }
                }
                else if (board[i + y][j + x] != 'R')
                {
                    neighbor[2] = i + y;
                    neighbor[3] = j + x;
                    return (board[i + y][j + x] - '0'); //changing char to digit + 1!(because 0 means nothing found)
                }
            }
        }
    }
    return 0;
}
