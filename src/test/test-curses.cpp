#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
	initscr();
	// box(stdscr, ACS_VLINE, ACS_HLINE);
	move(LINES/2, COLS/2);
	waddstr(stdscr, "hello, world!h\nello, world!hello, world!hello, world!hello, world!hello, world!");

	char buff[256];
	sprintf(buff, "%d %d %d %d\n", LINES, COLS, ACS_VLINE, ACS_HLINE);
	waddstr(stdscr, buff);
	refresh();
	while(true)
		getch();
	endwin();
	return 0;
}