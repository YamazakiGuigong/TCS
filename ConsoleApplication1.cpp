#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>


int sequence[20][20];
int length = 2,score=0;
int rows, cols;
std::vector<std::vector<char>> map;
void print()
{
	int i, j;
	COORD pos;
	CONSOLE_CURSOR_INFO curinfo;
	curinfo.dwSize = 1;
	curinfo.bVisible = FALSE;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &curinfo);
	system("cls");
	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			pos.X = j;
			pos.Y = i;
			SetConsoleCursorPosition(handle, pos);
			printf(" ");
			
		}
	}*/
	std::vector<std::vector<char>> map(rows, std::vector<char>(cols, ' '));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				map[i][j] = '#';
			}
		}
	}
	
	for (int i = 1; i < rows - 1; i++)
		for (int j = 1; j < cols-1; j++)
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
	//system("pause");
	for (const auto& row : map)
	{
		for (char c : row)
		{
			std::cout << c;
		}
		std::cout << std::endl;
	}
	printf("\nYour size%d,history high size%d", length, score);
	Sleep(10);
	//system("pause");	
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
	

	std::cout << "输入行数和列数:";
	std::cin >> rows >> cols;
	std::vector<std::vector<char>> map(rows, std::vector<char>(cols, ' ')); 
	system("cls");
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++) 
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
				map[i][j] = '#';
			}
		}
	}

	for (const auto& row : map)
	{
		for (char c : row) 
		{
			std::cout << c;
		}
		std::cout << std::endl;
	}
	for (i = 0; i <= rows; i++)
		for (j = 0; j <= cols; j++)
	{
		sequence[i][j] = 0;
	}

	x=rows/2, y = cols / 2;
	life = 1, food = 0, t = 0, cache = 0, num = 0,book=0, direction = 'a';
	sequence[x][y] = 1, sequence[x][y + 1] = 2;
	length = 2;
	//system("pause");
	system("cls");
	while (life)
	{

		startTime = clock();
		t++;
		if (food == 0)
		{
			srand((unsigned)time(NULL));
			foodx = 1 + rand() % (rows - 1);
			foody = 1 + rand() % (cols - 1);
			while (map[foodx][foody] != ' ')
			{
				foodx = 1 + rand() % (rows - 1);
				foody = 1 + rand() % (cols - 1);
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
					for (i = 1; i <rows - 1; i++)
						for (j = 1; j <cols - 1; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i<rows - 1; i++)
						for (j = 1; j <cols - 1; j++)
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
						for (i = 1; i < rows - 1; i++)
							for (j = 1; j <cols - 1; j++)
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
					for (i = 1; i <cols - 1; i++)
						for (j = 1; j <rows - 1; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i <cols - 1; i++)
						for (j = 1; j <rows - 1; j++)
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
						for (i = 1; i <cols - 1; i++)
							for (j = 1; j <rows - 1; j++)
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
					for (i = 1; i <cols - 1; i++)
						for (j = 1; j <rows - 1; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i <cols - 1; i++)
						for (j = 1; j <rows - 1; j++)
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
						for (i = 1; i <cols - 1; i++)
							for (j = 1; j <rows - 1; j++)
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

					for (i = 1; i <cols - 1; i++)
						for (j = 1; j <rows - 1; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i <cols - 1; i++)
						for (j = 1; j <rows - 1; j++)
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
						for (i = 1; i <cols - 1; i++)
							for (j = 1; j <rows - 1; j++)
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
		if (length == rows*cols)
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

