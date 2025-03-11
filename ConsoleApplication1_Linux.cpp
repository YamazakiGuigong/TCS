#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<termios.h>
#include<fcntl.h>
#include<iostream>
#include<sys/select.h>




char map[20][20] = { "#############",
						 "#           #",
						 "#           #",
						 "#           #",
						 "#           #",
						 "#           #",
						 "#     SO    #",
						 "#           #",
						 "#           #",
						 "#           #",
						 "#           #",
						 "#           #",
						 "#############" };
int sequence[20][20];

const char* HIDE_CURSOR = "\033[?25l";

void set_cursor_position(int x, int y){
	printf("\033[%d;%dH", y, x);
}

void set_nonblocking_mode(){
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate);
	ttystate.c_lflag &= ~(ICANON | ECHO);
	ttystate.c_cc[VMIN] = 0;
	ttystate.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

void reset_terminal(){
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate);
	ttystate.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int kbhit(){
	set_nonblocking_mode();
	struct timeval tv = { .tv_sec = 0, .tv_usec = 0 };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	reset_terminal();
	return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

void set_terminal_mode(){
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate);
	ttystate.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

char getch(){
	char ch;
	set_terminal_mode();
	read(STDIN_FILENO, &ch, 1);
	reset_terminal();
	return ch;
}

void print()
{
	std::cout << HIDE_CURSOR;
	int i, j;
	for (i = 1; i <= 11; i++)
		for (j = 1; j <= 11; j++)
		{
			set_cursor_position(j+1,i+1);
			printf(" ");
		}
	for (i = 1; i <= 11; i++)
		for (j = 1; j <= 11; j++)
		{
			if (sequence[i][j] == -1)
				map[i][j] = '*';
			if (sequence[i][j] == 0)
				map[i][j] = ' ';
			if (sequence[i][j] == 1)
				map[i][j] = 'S';
			if (sequence[i][j] > 1)
				map[i][j] = 'O';
		}

	for (i = 0; i <= 12; i++)
	{
		for (j = 0; j <= 12; j++)
		{
			set_cursor_position(j+1,i+1);
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
sleep(0.01);


}

int main()
{
	system("clear");
	const clock_t FPS = 40;
	int startTime = 0;
	int frameTime = 0;



	int x, y, i, j, life, key, length, t, cache;
	int food, foodx, foody;

	char direction;

	life = 1, food = 0, length = 2, t = 0, cache = 0;
	x = 6, y = 6, direction = 'a';
	sequence[x][y] = 1, sequence[x][y + 1] = 2;

	while (life)
	{

		startTime = clock();
		t++;
		while (food == 0)
		{
			srand((unsigned)time(NULL));
			foodx = 1 + rand() % 11;
			foody = 1 + rand() % 11;
			while (map[foodx][foody] != ' ')
			{
				srand((unsigned)time(NULL));
				foodx = 1 + rand() % 11;
				foody = 1 + rand() % 11;
			}
			map[foodx][foody] = '*';
			sequence[foodx][foody] = -1;
			food = 1;
		}
		if (kbhit())
		{
			if (cache == 0)
			{
				key = getch();
				if (key == 'w' && direction != 's')
					direction = 'w';
				if (key == 's' && direction != 'w')
					direction = 's';
				if (key == 'a' && direction != 'd')
					direction = 'a';
				if (key == 'd' && direction != 'a')
					direction = 'd';
				cache++;
			}
			
		}

		if (t % 2000 == 0)
		{
			if (direction == 'a')
			{
				if (map[x][y - 1] == ' ')
				{
					for (i = 1; i <= 11; i++)
						for (j = 1; j <= 11; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i <= 11; i++)
						for (j = 1; j <= 11; j++)
						{
							if (sequence[i][j] > 0)
								sequence[i][j]++;
						}
					y--;
					sequence[x][y] = 1;
					cache = 0;
				}
				else
					if (map[x][y - 1] == '*')
					{
						for (i = 1; i <= 11; i++)
							for (j = 1; j <= 11; j++)
							{
								if (sequence[i][j] > 0)
									sequence[i][j]++;
							}
						length++;
						y--;
						sequence[x][y] = 1;
						food = 0;
						cache = 0;
					}
					else
						if (map[x][y - 1] == '#' || map[x][y - 1] == 'O')
						{
							life = 0;
							break;
						}
				

			}

			if (direction == 'w')
			{
				if (map[x - 1][y] == ' ')
				{
					for (i = 1; i <= 11; i++)
						for (j = 1; j <= 11; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i <= 11; i++)
						for (j = 1; j <= 11; j++)
						{
							if (sequence[i][j] > 0)
								sequence[i][j]++;
						}
					x--;
					sequence[x][y] = 1;
					cache = 0;
				}
				else
					if (map[x - 1][y] == '*')
					{
						for (i = 1; i <= 11; i++)
							for (j = 1; j <= 11; j++)
							{
								if (sequence[i][j] > 0)
									sequence[i][j]++;
							}
						length++;
						x--;
						sequence[x][y] = 1;
						food = 0;
						cache = 0;
					}
					else
						if (map[x - 1][y] == '#' || map[x - 1][y] == 'O')
						{
							life = 0;
							break;
						}
			}

			if (direction == 's')
			{
				if (map[x + 1][y] == ' ')
				{
					for (i = 1; i <= 11; i++)
						for (j = 1; j <= 11; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i <= 11; i++)
						for (j = 1; j <= 11; j++)
						{
							if (sequence[i][j] > 0)
								sequence[i][j]++;
						}
					x++;
					sequence[x][y] = 1;
					cache = 0;
				}
				else
					if (map[x + 1][y] == '*')
					{
						for (i = 1; i <= 11; i++)
							for (j = 1; j <= 11; j++)
							{
								if (sequence[i][j] > 0)
									sequence[i][j]++;
							}
						length++;
						x++;
						sequence[x][y] = 1;
						food = 0;
						cache = 0;
					}
					else
						if (map[x+1][y] == '#' || map[x+1][y] == 'O')
						{
							life = 0;
							break;
						}
			}

			if (direction == 'd')
			{
				if (map[x][y + 1] == ' ')
				{

					for (i = 1; i <= 11; i++)
						for (j = 1; j <= 11; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i <= 11; i++)
						for (j = 1; j <= 11; j++)
						{
							if (sequence[i][j] > 0)
								sequence[i][j]++;
						}
					y++;
					sequence[x][y] = 1;
					cache = 0;

				}
				else
					if (map[x][y + 1] == '*')
					{
						for (i = 1; i <= 11; i++)
							for (j = 1; j <= 11; j++)
							{
								if (sequence[i][j] > 0)
									sequence[i][j]++;
							}
						length++;
						y++;
						sequence[x][y] = 1;
						food = 0;
						cache = 0;
					}
					else
						if (map[x][y+1] == '#' || map[x][y+1] == 'O')
						{
							life = 0;
							break;
						}
			}

		}
		if (length == 121)
			break;
		if (t == 10000)
			t = 0;
		print();

		frameTime = clock() - startTime + 10;
		if (frameTime > 0 && FPS > frameTime)
			sleep((FPS - frameTime) / 1000);


	}
	if (life == 0)
	{
		printf("you are lose!\n");
		return 0;
	}
	else
	{
		printf("you are win!");
			return 0;
	}
	reset_terminal();
	return 0;
}