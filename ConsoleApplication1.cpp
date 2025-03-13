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
char map1[20][20] = { "#############",
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
int length = 2,score=0;
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
	printf("\nYour size%d,history high size%d", length,score);
	Sleep(10);
}

int main()
{
	const clock_t FPS = 40;
	int startTime = 0;
	int frameTime = 0;
	int endTime = 0;
	int x, y, i, j, life, key, t, cache, num,book;
	int food, foodx, foody;
	char direction,ch;
	
	for (i = 0; i <= 12; i++)
		for (j = 0; j <= 12; j++)
	{
		sequence[i][j] = 0;
	}
	for (i = 0; i <= 12; i++)
		for (j = 0; j <= 12; j++)
		{
			map[i][j] = map1[i][j];
		}
	life = 1, food = 0, t = 0, cache = 0, num = 0,book=0;
	x = 6, y = 6, direction = 'a';
	sequence[x][y] = 1, sequence[x][y + 1] = 2;
	length = 2;
	system("cls");

	while (life)
	{

		startTime = clock();
		t++;
		if (food == 0)
		{
			srand((unsigned)time(NULL));
			foodx = 1 + rand() % 11;
			foody = 1 + rand() % 11;
			while (map[foodx][foody] != ' ')
			{
				foodx = 1 + rand() % 11;
				foody = 1 + rand() % 11;
			}
			map[foodx][foody] = '*';
			sequence[foodx][foody] = -1;
			food = 1;
		}

		if (_kbhit())
		{
			if (cache == 0)
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
		endTime = clock();
		num = endTime - startTime;
		book = book + num;
		if(book>= 10 && t!=0 && t!=10 && t!=20 && t!=30)
		{
			
			book = book - 10;
			t++;
		}
		
		if (t % 10 == 0)
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
						if (map[x + 1][y] == '#' || map[x + 1][y] == 'O')
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
						if (map[x][y + 1] == '#' || map[x][y + 1] == 'O')
						{
							life = 0;
							break;
						}
			}

		}
		if (length > score)
			score = length;
		if (length == 121)
			break;
		if (t == 30)
			t = 0;

		print();
		frameTime = clock() - startTime + 10;
		if (frameTime > 0 && FPS > frameTime)
			Sleep(FPS - frameTime);

	}
	if (life == 0)
	{
		
		printf("\nyou are lose!\n");
		printf("Press R again\n");
		ch = _getch();
		if (ch == 'r' || ch == 'R')
			main();
		else
			return 0;
	}
	else
	{
		printf("\nyou are win!\n");
		return 0;
	}
}