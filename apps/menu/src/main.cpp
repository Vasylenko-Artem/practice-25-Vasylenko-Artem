#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>

void clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int main()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0); // hide cursor

	const char *labs[] = {"lab_01", "lab_02", "lab_03", "lab_04", "lab_05", "Exit"};
	int n = sizeof(labs) / sizeof(labs[0]);
	int choice = 0;

	int h = n + 4; // window height
	int w = 30;	   // window width
	int starty = (LINES - h) / 2;
	int startx = (COLS - w) / 2;

	WINDOW *menu_win = newwin(h, w, starty, startx);
	keypad(menu_win, TRUE);

	while (true)
	{
		werase(menu_win);
		box(menu_win, 0, 0);

		// centered title
		const char *title = " MENU ";
		int title_x = (w - strlen(title)) / 2;
		mvwprintw(menu_win, 0, title_x, "%s", title);

		for (int i = 0; i < n; i++)
		{
			int y = 2 + i;
			int len = strlen(labs[i]);
			int x = (w - len) / 2;

			if (i == choice)
			{
				wattron(menu_win, A_REVERSE);
				mvwhline(menu_win, y, 1, ' ', w - 2); // highlight full width
			}

			mvwprintw(menu_win, y, x, "%s", labs[i]);

			if (i == choice)
				wattroff(menu_win, A_REVERSE);
		}

		wrefresh(menu_win);

		int c = wgetch(menu_win);

		switch (c)
		{
		case 'q':
			delwin(menu_win);
			endwin();
			return 0;

		case KEY_UP:
			choice = (choice - 1 + n) % n;
			break;

		case KEY_DOWN:
			choice = (choice + 1) % n;
			break;

		case 10: // Enter
		case ' ':
			if (choice == n - 1) // Exit
			{
				delwin(menu_win);
				endwin();
				return 0;
			}

			// close ncurses
			delwin(menu_win);
			endwin();

			clearScreen();

			std::string cmd = "make run_app APP=" + std::string(labs[choice]);
			system(cmd.c_str());

			std::cout << "Press ENTER to continue...";
			std::cin.ignore();
			std::cin.get();

			// return ncurses
			initscr();
			cbreak();
			noecho();
			curs_set(0);

			starty = (LINES - h) / 2;
			startx = (COLS - w) / 2;

			menu_win = newwin(h, w, starty, startx);
			keypad(menu_win, TRUE);
			break;
		}
	}

	delwin(menu_win);
	endwin();
	return 0;
}
