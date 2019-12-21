void game_input(int in)
{
    do
    {
        if (in == 2 || in == 1)
        {
            //gettting dimension size!
            printf("\033[32mPlease Enter Environment Dimension Size:\033[0m(each between 0 to 25)\n");
            do
            {
                printf("Rows(Width):");
                scanf("%d", &m);getch();
                printf("Columns(Length):");
                scanf("%d", &n);getch();
                if ((m <= 0) || (m >= 25) || (n <= 0) || (n >= 25))
                    printf("\033[31mTry again in an accurate range!\033[0m\n");
            } while ((m <= 0) || (m >= 25) || (n <= 0) || (n >= 25));
        }

        if (in == 3 || in == 1)
        {
            //getting police station!
            printf("\n\033[32mPlease Enter Number of Police Stations!\033[0m(each between 0 to 10)\n");
            do
            {
                scanf("%d", &ps);getch();
                if (ps >= 10 || ps <= 0)
                    printf("\033[31mTry again;\033[0m Enter number in the given range!\n");
            } while (ps >= 10 || ps <= 0);
        }

        if (in == 3 || in == 4 || in == 1)
        {
            //getting cops in each station!
            printf("\n\033[32mPlease Enter Number of Cops in Each Police Station!\033[0m(each between 0 to 10)\n");
            for (int i = 0; i < ps; i++)
            {
                do
                {
                    printf("\033[36mStation %d:\033[0m", i + 1);
                    scanf("%d", &plc_stn[i][0]);getch();
                    if (plc_stn[i][0] >= 10 || plc_stn[i][0] <= 0)
                        printf("\033[31mTry again;\033[0m Enter number in the given range!\n");
                } while (plc_stn[i][0] >= 10 || plc_stn[i][0] <= 0);
            }
            total_cops = 0;
            for (int i = 0; i < ps; i++)
                total_cops += plc_stn[i][0];
        }
    } while (chk_input());
}
int chk_input()
{
    if (total_cops > n * m - 9 * 1)
    {
        printf("%60c\033[31mNot Enough Sapce!\033[34m\n%42cPlease Change Dimension Size or Number of Elements!\033[0m\n", '\0', '\0');
        sleep(2);
        return -1;
    }
    return 0;
}
int initialize_board()
{
    turn = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        //notice descartian coord is (j,i)! but i rows & j columns
        {
            board[i][j] = empty;
        }
    int ret = rand_position();
    board_design();
    // getch();
    return ret;
}
int rand_position()
{
    for (int i = 0; i < ps; i++)
    {
        plc_stn[i][1] = -1; //default value of report center!
        for (int j = 0; j < plc_stn[i][0]; j++)
        {
            int x, y;
            do
            {
                x = rand() % n;
                y = rand() % m;
            } while (board[y][x] != empty);
            cop_loc[i][j][0] = y;
            cop_loc[i][j][1] = x;
            board[y][x] = i + 1 + '0';
        }
    }
    int x, y, c = 0;
    do
    {
        if (++c >= m * n)
            break;
        x = rand() % n;
        y = rand() % m;
    } while (board[y][x] != empty || chk_neighbor(y, x, 1, 1) > 0);
    board[y][x] = 'R';
    rob_loc[0][0] = y;
    rob_loc[0][1] = x;
    if (chk_neighbor(y, x, 1, 1) > 0)
        return -1; //caught robbers number
    return 0;
}
