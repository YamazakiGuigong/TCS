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
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (sequence[i][j] == -1)
				map[i][j] = '*';

			else if (sequence[i][j] == 0)
				map[i][j] = ' ';

			else if (sequence[i][j] == 1)
				map[i][j] = 'S';

			else if (sequence[i][j] > 1)
				map[i][j] = 'O';

		}
		//Sleep(5);
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			pos.X = j;
			pos.Y = i;
			SetConsoleCursorPosition(handle, pos);
			cout << map[i][j];
		}
	}
	pos.X = 0;
	pos.Y = rows;
	SetConsoleCursorPosition(handle, pos);
	cout << "Current length: " << length << "  High score: " << score << "  ";
}

void generateFood(int& foodx, int& foody)
{
	do {
		srand(unsigned(time(NULL)));
		foodx = 1 + rand() % (rows - 2);
		foody = 1 + rand() % (cols - 2);
	} while (sequence[foodx][foody] != 0);

	sequence[foodx][foody] = -1;
}

int main()
{
	int x, y, t,num,book,cache;
	float FPS = 1000 / 120.0f;
	int startTime = 0;
	int frameTime = 0;
	int endTime = 0;
	cout << "输入行数和列数：\n";
	cin >> rows >> cols;
	sequence.resize(rows, vector<int>(cols, 0));
	initMap();

	x = rows / 2, y = cols / 2, t = 0,num=0,book=0,cache=0;
	sequence[x][y] = 1;
	sequence[x][y + 1] = 2;

	int foodx, foody;
	generateFood(foodx, foody);

	char direction = 'a';
	bool alive = true;
	int i, j;
	while (alive)
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
			if (t % 15 == 0 || num > 0)
			{
				cache = 0;
				if (num > 0)
					num--;

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
					alive = false;
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
					endTime = clock() - startTime;
					book = book + endTime;
					while (book >= 8)
					{
						book /= 8;
						num++;
					}
				}
				else
				{
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
		if (t == 30)
			t = 0;
	}

	system("cls");
	cout << "Game Over! Final length: " << length << endl;
	cout << "Press R to restart, any other key to exit...";

	if (tolower(_getch()) == 'r')
	{
		system("cls");
		main();
	}
	return 0;
}