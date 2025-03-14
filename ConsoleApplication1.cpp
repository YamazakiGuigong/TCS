#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

int length = 2, score = 0;
int rows, cols;
vector<vector<int>> sequence;
vector<vector<char>> map;

void initMap()
{
	system("cls");
	map.resize(rows, vector<char>(cols, ' '));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
				map[i][j] = '#';
		}
	}

}

void print()
{
	COORD pos;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.dwSize = 1;
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &curInfo);

	for (int i = 1; i < rows - 1; i++)
		for (int j = 1; j < cols - 1; j++)
		{
			switch (sequence[i][j])
			{
			case -1 : map[i][j] = '*';; break;
			case 0: map[i][j] = ' '; break;	
			case 1: map[i][j] = 'S'; break;
			default:if(sequence[i][j] > 1 ) map[i][j] = 'O'; break;
			}

		}

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			pos.X = j;
			pos.Y = i;
			SetConsoleCursorPosition(handle, pos);
			cout << map[i][j];
		}

	pos.X = 0;
	pos.Y = rows;
	SetConsoleCursorPosition(handle, pos);
	cout << "Current length: " << length << "  High score: " << score << "  ";
}

void generateFood(int& foodx, int& foody)
{
	do {
		foodx = 1 + rand() % (rows - 2);
		foody = 1 + rand() % (cols - 2);
	} while (sequence[foodx][foody] != 0);

	sequence[foodx][foody] = -1;
}

int main()
{
	srand(unsigned(time(NULL)));

	int x, y, t,book,cache,i, j, life;;
	float FPS = 1000 / 120.0f;
	int startTime = 0;
	int frameTime = 0;
	int endTime = 0;
	char direction = 'a';

	cout << "输入行数和列数：\n";
	cin >> rows >> cols;
	sequence.resize(rows, vector<int>(cols, 0));
	initMap();

	x = rows / 2, y = cols / 2, t = 0, cache = 0, life=1;
	sequence[x][y] = 1;
	sequence[x][y + 1] = 2;

	int foodx, foody;
	generateFood(foodx, foody);

	
	while (life)
	{
		startTime = clock();
		t++;
		
		if (_kbhit())
		{
			if (cache == 0)
			{
				char key = _getch();
				cache++;
				switch (tolower(key))
				{
				case 'w': if (direction != 's') direction = 'w'; break;
				case 's': if (direction != 'w') direction = 's'; break;
				case 'a': if (direction != 'd') direction = 'a'; break;
				case 'd': if (direction != 'a') direction = 'd'; break;
				}
			}
		}
			if (t % 15 == 0)
			{
				cache = 0;

				int newX = x, newY = y;
				switch (direction)
				{
				case 'w': newX--; break;
				case 's': newX++; break;
				case 'a': newY--; break;
				case 'd': newY++; break;
				}

				if (newX <= 0 || newX >= rows - 1 || newY <= 0 || newY >= cols - 1 || sequence[newX][newY] > 0)
				{
					life = 0;
					break;
				}

				if (sequence[newX][newY] == -1)
				{
					length++;
					for (i = 1; i < rows - 1; i++)
						for (j = 1; j < cols - 1; j++)
						{
							if (sequence[i][j] > 0)
								sequence[i][j]++;
						}
					if (length > score)
						score = length;

					generateFood(foodx, foody);
					endTime = clock() - startTime;//计算单次食物生成时间
					while (endTime >= 8)//如果食物生成时间大于8ms，执行t+1.
					{
						endTime /= 8;
						t++;
						if (t % 15 == 0)
							t = 14;
						if (t % 30 == 0)
							t = 14;
					}
				}
				else{
					for (i = 1; i < rows - 1; i++)
						for (j = 1; j < cols - 1; j++)
						{
							if (sequence[i][j] == length)
								sequence[i][j] = 0;
						}
					for (i = 1; i < rows - 1; i++)
						for (j = 1; j < cols - 1; j++)
						{
							if (sequence[i][j] > 0)
								sequence[i][j]++;
						}


				}
				sequence[newX][newY] = 1;
				x = newX;
				y = newY;
			}
		
		print();
		frameTime = clock() - startTime;
		if (frameTime > 0 && FPS > frameTime)
			Sleep(FPS - frameTime);
		if (t == 31)
			t = 0;
		if (length == (rows - 2) * (cols - 2))
			break;
	}

	system("cls");
	if(life==0)
	cout << "Game Over! Final length: " << length << endl;
	else
		cout << "You win! Final length: " << length << endl;
	cout << "Press R to restart, any other key to exit...";

	if (tolower(_getch()) == 'r')
	{
		system("cls");
		main();
	}
	return 0;
}