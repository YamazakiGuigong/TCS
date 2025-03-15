#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

map<string, int> highScores;

void readHighScores() {
    ifstream file("highscores.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string key;
        int value;
        if (iss >> key >> value) {
            highScores[key] = value;
        }
    }
    file.close();
}

void saveHighScores() {
    ofstream file("highscores.txt");
    for (const auto& pair : highScores) {
        file << pair.first << " " << pair.second << endl;
    }
    file.close();
}

void initMap(int rows, int cols, vector<vector<char>>& map, vector<vector<int>>& sequence) {
    system("cls");
    map.resize(rows, vector<char>(cols, ' '));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                map[i][j] = '#';
                sequence[i][j] = -2;
            }
        }
    }
}

void print(int rows, int cols, vector<vector<int>>& sequence, vector<vector<char>>& map,
    int length, int score) {
    COORD pos;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1;
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &curInfo);

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            switch (sequence[i][j]) {
            case -1: map[i][j] = '*'; break;
            case 0:  map[i][j] = ' '; break;
            case 1:  map[i][j] = 'S'; break;
            default: if (sequence[i][j] > 1) map[i][j] = 'O'; break;
            }
        }
    }

    pos.X = 0;
    for (int i = 0; i < rows; i++) {
        string row(map[i].begin(), map[i].end());
        pos.Y = i;
        SetConsoleCursorPosition(handle, pos);
        cout << row;
    }

    string mapKey = to_string(rows) + "x" + to_string(cols);
    int historyHigh = highScores.count(mapKey) ? highScores[mapKey] : 0;

    pos.X = 0;
    pos.Y = rows;
    SetConsoleCursorPosition(handle, pos);
    cout << "Current length: " << length
        << "  High score: " << score
        << "  History High: " << historyHigh
        << "  ";
}

void generateFood(int rows, int cols, vector<vector<int>>& sequence,
    int& foodx, int& foody, int remain) {
    vector<vector<int>> position(rows, vector<int>(cols, 0));
    int sum = 0, temp = 1;

    if (remain <= 0) return;

    sum = 1 + rand() % remain;
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            if (sequence[i][j] == 0) {
                position[i][j] = temp++;
            }
        }
    }

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            if (position[i][j] == sum) {
                foodx = i;
                foody = j;
                sequence[foodx][foody] = -1;
                return;
            }
        }
    }
}

bool playGame(int rows, int cols) {
    string mapKey = to_string(rows) + "x" + to_string(cols);
    int historyHigh = highScores.count(mapKey) ? highScores[mapKey] : 0;
    int length = 2, score = 0;
    vector<vector<int>> sequence(rows, vector<int>(cols, 0));
    vector<vector<char>> map;

    int x = rows / 2, y = cols / 2;
    sequence[x][y] = 1;
    sequence[x][y + 1] = 2;

    int foodx = 1, foody = 1;
    int remain = (rows - 2) * (cols - 2) - 2;
    generateFood(rows, cols, sequence, foodx, foody, remain);

    char direction = 'a';
    int t = 0, cache = 0, life = 1;
    const float FPS = 1000 / 60.0f;
    initMap(rows, cols, map, sequence);

    while (life) {
        int startTime = clock();
        t++;

        if (_kbhit()) {
            if (cache == 0) {
                char key = _getch();
                cache++;
                switch (tolower(key)) {
                case 'w': if (direction != 's') direction = 'w'; break;
                case 's': if (direction != 'w') direction = 's'; break;
                case 'a': if (direction != 'd') direction = 'a'; break;
                case 'd': if (direction != 'a') direction = 'd'; break;
                }
            }
        }

        if (t % 15 == 0) {
            cache = 0;
            int newX = x, newY = y;
            switch (direction) {
            case 'w': newX--; break;
            case 's': newX++; break;
            case 'a': newY--; break;
            case 'd': newY++; break;
            }

            if (newX <= 0 || newX >= rows - 1 || newY <= 0 || newY >= cols - 1 || sequence[newX][newY] > 0) {
                life = 0;
                break;
            }

            if (sequence[newX][newY] == -1) {
                length++;
                for (auto& row : sequence) {
                    for (auto& val : row) {
                        if (val > 0) val++;
                    }
                }
                if (length > score) score = length;
                remain = (rows - 2) * (cols - 2) - length;
                generateFood(rows, cols, sequence, foodx, foody, remain);
            }
            else {
                for (auto& row : sequence) {
                    for (auto& val : row) {
                        if (val == length) val = 0;
                    }
                }
                for (auto& row : sequence) {
                    for (auto& val : row) {
                        if (val > 0) val++;
                    }
                }
            }

            sequence[newX][newY] = 1;
            x = newX;
            y = newY;
        }

        print(rows, cols, sequence, map, length, score);

        int frameTime = clock() - startTime;
        if (FPS > frameTime) {
            Sleep(FPS - frameTime);
        }

        if (t == 31) t = 0;
        if (length == (rows - 2) * (cols - 2)) {
			break;
        }
    }

    if (score > historyHigh) {
        highScores[mapKey] = score;
        saveHighScores();
    }

    system("cls");
    cout << (life == 0 ? "Game Over!" : "You win!") << endl
        << " Final length: " << length << endl
        << "Press R to restart, any other key to exit...\n";

    return tolower(getchar()) == 'r';
}

int main() {
    readHighScores();
    srand(static_cast<unsigned>(time(nullptr)));
    system("cls");
    int rows, cols;

    do {
        bool validInput = false;
        while (!validInput) {
            cout << "输入行数和列数（5-55）：\n";
            cin >> rows >> cols;

            if (cin.fail()) {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cout << "输入必须为整数！请重新输入。\n";
                continue;
            }

            if (rows < 5 || rows > 55 || cols < 5 || cols > 55) {
                cout << "行数和列数必须在5到55之间！请重新输入。\n";
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                continue;
            }
            validInput = true;
        }
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    } while (playGame(rows, cols));

    return 0;
}