#include <ncurses.h>
#include <cstdlib>
#include <string>
#include <iostream>

int main()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	const char *labs[] = {"lab_01", "lab_02", "lab_03", "lab_04", "lab_05", "Exit"};
	int n = sizeof(labs) / sizeof(labs[0]);
	int choice = 0;

	while (true)
	{
		clear();
		for (int i = 0; i < n; i++)
		{
			if (i == choice)
				attron(A_REVERSE);
			mvprintw(2 + i, 2, "%s", labs[i]);
			if (i == choice)
				attroff(A_REVERSE);
		}

		int c = getch();
		switch (c)
		{
		case 'q':
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
				endwin();
				return 0;
			}

			endwin(); // close ncurses before starting

			// launch the selected laboratory via Makefile
			std::string cmd = "make run_app APP=" + std::string(labs[choice]);
			system(cmd.c_str());

			std::cout << "Press any key to continue..." << std::endl;
			getch();

			initscr(); // back to ncurses
			break;
		}
	}

	endwin();
	return 0;
}
