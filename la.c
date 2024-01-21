#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "la.h"

int add_ant(int x);
int add_quote1(void);
int show_ant_quote1(bool);
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
        if (add_ant(x) == ERR) break;
        if (add_quote1() == ERR) break;
        if (x == COLS / 2 - ANT1LENGTH / 2) {
            show_ant_quote1(true);
            getch();
            refresh();
            sleep(3);
            show_ant_quote1(false);
            getch();
            refresh();
        }
        getch();
        refresh();
        usleep(40000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();

    return 0;
}


int add_ant(int x)
{
    static char *d51[ANT1PATTERNS][ANT1HEIGHT + 1]
      = {
            {ANT1STR1, ANT1STR2, ANT1STR3, ANT1LGS1, ANT1DEL},
            {ANT1STR1, ANT1STR2, ANT1STR3, ANT1LGS2, ANT1DEL},
            {ANT1STR1, ANT1STR2, ANT1STR3, ANT1LGS3, ANT1DEL}
        };

    int y, i;

    if (x < - ANT1HEIGHT)  return ERR;
    y = LINES / 2 + 5;

    for (i = 0; i <= ANT1HEIGHT; ++i) {
        my_mvaddstr(y + i, x, d51[(ANT1LENGTH + x) % ANT1PATTERNS][i]);
    }

    return OK;
}

int add_quote1(void) {
    static char *quote1[QUOTE1_HEIGHT] = {
        QUOTE1_BORDER,
        QUOTE1_TEXT1,
        QUOTE1_TEXT2,
        QUOTE1_BORDER
    };
    
    int i;
    
    for (i = 0; i < QUOTE1_HEIGHT; ++i) {
        my_mvaddstr(LINES / 2 - 10 + i, COLS / 2 - 25, quote1[i]);
    }
    
    return OK;
}

int show_ant_quote1(bool show) {
    int y = LINES / 2;
    int x = COLS / 2 - 15;
    if (show) {
        static char *ant_quote1[ANT_QUOTE1_HEIGHT] = {
            ANT_QUOTE1_TOP,
            ANT_QUOTE1_TEXT,
            ANT_QUOTE1_BOT1,
            ANT_QUOTE1_BOT2,
            ANT_QUOTE1_BOT3
        };
        
        int i;
        
        for (i = 0; i < ANT_QUOTE1_HEIGHT; ++i) {
            my_mvaddstr(y + i, x, ant_quote1[i]);
        }
    } else {
        static char *ant_quote_del[ANT_QUOTE1_HEIGHT] = {
            ANT_QUOTE_DEL,
            ANT_QUOTE_DEL,
            ANT_QUOTE_DEL,
            ANT_QUOTE_DEL,
            ANT_QUOTE_DEL
        };
        
        int i;
        
        for (i = 0; i < ANT_QUOTE1_HEIGHT; ++i) {
            my_mvaddstr(y + i, x, ant_quote_del[i]);
        }
    }

    return OK;
}