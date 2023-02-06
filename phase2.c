#include <stdio.h>
#include "curses.h"
#include <stdlib.h>
#include <string.h>
#define SIZE 100
int main()
{
    int coloum = 0;
    int numberoflines = 0;
    initscr();
    mvprintw(0, 0, "1");
    keypad(stdscr, TRUE);
    start_color();
    noecho();
    cbreak();
    int get;
    char GETCOMMAND[SIZE];
    refresh();
    while (strcmp(GETCOMMAND, "q") != 0)
    {
        mvprintw(LINES - 4, 1, "NORMAL");
        for (int i = LINES - numberoflines - 1; i > 4; i--)
        {
            mvprintw(LINES - i, 0, "~");
        }
        refresh();
        get = getch();
        if (get == 'i')
        {
            mvprintw(LINES - 4, 1, "INSERT");
            while (get != 27)
            {
                if (get != '\n' && get != KEY_UP && get != KEY_DOWN && get != KEY_RIGHT && get != KEY_LEFT)
                {
                    move(numberoflines, coloum);
                    printw("%c", get);
                    refresh();
                    coloum++;
                    get = getch();
                }
                if (get == '\n' && get != KEY_UP && get != KEY_DOWN && get != KEY_RIGHT && get != KEY_LEFT)
                {
                    coloum = 2; // baraye neveshtan char dar khat jadid
                    numberoflines++;
                    move(numberoflines, coloum);
                    mvprintw(numberoflines, 0, "%d ", numberoflines + 1);
                    get = getch();
                    printw("%c", get);
                    refresh();
                    coloum++;
                    get = getch();
                }
                else if (get == KEY_UP)
                {
                    move(numberoflines - 1, coloum);
                    get = getch();
                    numberoflines--;
                }
                else if (get == KEY_DOWN)
                {

                    move(numberoflines + 1, coloum);
                    get = getch();
                    numberoflines++;
                }
                else if (get == KEY_RIGHT)
                {

                    move(numberoflines, coloum + 1);
                    get = getch();
                    coloum++;
                }
                else if (get == KEY_LEFT)
                {

                    move(numberoflines, coloum - 1);
                    get = getch();
                    coloum--;
                }
            }
            refresh();
        }
        int row = 1;
        int col = 1;
        if (get == 'v')
        {
            move(0, 0);
            mvprintw(LINES - 4, 1, "VISUAl");
            refresh();
            get = getch();
            while (get != 27)
            {
                if (get == KEY_UP)
                {
                    move(row - 1, col);
                    row--;
                }
                else if (get == KEY_DOWN)
                {

                    move(row + 1, col);
                    row++;
                }
                else if (get == KEY_RIGHT)
                {

                    move(row, col + 1);
                    col++;
                }
                else if (get == KEY_LEFT)
                {

                    move(row, col - 1);
                    col--;
                }
                get = getch();
            }
        }
        if (get == 27)
        {
            mvprintw(LINES - 4, 1, "NORMAL");
            refresh();
        }
        if (get == ':')
        {
            move(LINES - 2, 0);
            mvprintw(LINES - 2, 0, ":");
            char get1;
            get1 = getch();
            while (get1 != '\n')
            {
                get1 = getch();
                printw("%c", get1);
            }
        }
    }
    refresh();
    endwin();
    return 0;
}