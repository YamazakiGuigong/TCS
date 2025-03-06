#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <conio.h>
#include <windows.h>



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

char map2[20][20] = { "#############",
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

void print()
{
	int i, j;
	COORD pos;
	CONSOLE_CURSOR_INFO curinfo;
	curinfo.dwSize = 1;
	curinfo.bVisible = FALSE;
	
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &curinfo);
	for (i = 0; i <= 12; i++)
		for (j = 0; j <= 12; j++)
		{
			pos.X = j;
			pos.Y = i;

			SetConsoleCursorPosition(handle, pos);
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
		for (j = 0; j <= 12; j++)
		{
			pos.X = j;
			pos.Y = i;
			SetConsoleCursorPosition(handle, pos);
			printf("%c", map[i][j]);
		}

	Sleep(10);



}

int main()
{
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

		if (_kbhit())
		{
			if (cache ==0)
			{
				key = _getch();
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



		if (t % 20 == 0)
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
				if (map[x][y] == '#' || map[x][y] == 'O')
					life = 0;
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
				if (map[x][y] == '#' || map[x][y] == 'O')
					life = 0;
			}

		}
		if (length == 121)
			break;
		if (t == 20)
			t = 0;
		print();

		frameTime = clock() - startTime + 10;
		if (frameTime > 0 && FPS > frameTime)
			Sleep(FPS - frameTime);


	}
	if (life == 0)
	{
		printf("you are lose!");
		return 0;
	}
	else
	{
		printf("you are win!");
			return 0;
	}
}