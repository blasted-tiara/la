#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "la.h"

int add_D51(int x);
int my_mvaddstr(int y, int x, char *str);

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
        if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x)
        if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

int main(int argc, char *argv[])
{
    int x;

    initscr();
    signal(SIGINT, SIG_IGN);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    for (x = COLS - 1; ; --x) {
        if (add_D51(x) == ERR) break;
        if (x == COLS / 2 - ANT1LENGTH / 2) {
            sleep(2);
        }
        getch();
        refresh();
        usleep(40000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();

    return 0;
}


int add_D51(int x)
{
    static char *d51[ANT1PATTERNS][ANT1HEIGHT + 1]
      = {
            {ANT1STR1, ANT1STR2, ANT1STR3, ANT1LGS1, ANT1DEL},
            {ANT1STR1, ANT1STR2, ANT1STR3, ANT1LGS2, ANT1DEL},
            {ANT1STR1, ANT1STR2, ANT1STR3, ANT1LGS3, ANT1DEL}
        };

    int y, i;

    if (x < - ANT1HEIGHT)  return ERR;
    y = LINES / 2 - 2;

    for (i = 0; i <= ANT1HEIGHT; ++i) {
        my_mvaddstr(y + i, x, d51[(ANT1LENGTH + x) % ANT1PATTERNS][i]);
    }

    return OK;
}
