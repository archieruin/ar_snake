#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;

bool ar_gameOver;

const int map_width = 20;
const int map_height = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];
int nTail;

enum eDir {
    STOP=0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

eDir dir;

void Setup() {
    ar_gameOver = false;
    dir = STOP;

    x = map_width / 2 - 1;
    y = map_height / 2 - 1;

    fruitX = rand() % map_width;
    fruitY = rand() % map_height;

    score = 0;
}

void Draw() {
    system("cls");

    for (int i = 0; i < map_width + 1; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            if (j == 0 || j == map_width - 1)
                cout << "#";
            if (i == y && j == x)
                cout << "@";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        cout << "o";
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < map_width + 1; i++)
        cout << "#";
    cout << endl;
    cout << endl;

    cout << "Score = " << score;
}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                ar_gameOver = true;
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case LEFT:
            x -= 1;
            break;
        case RIGHT:
            x += 1;
            break;
        case UP:
            y -= 1;
            break;
        case DOWN:
            y += 1;
            break;
        case STOP:
            break;
    }

    if (x >= map_width -1)
        x = 0;
    else if (x < 0)
        x = map_width - 1;

    if (y >= map_height -1)
        y = 0;
    else if (y < 0)
        y = map_height - 1;


    for (int i = 0; i < nTail; ++i) {
        if (tailX[i] == x && tailY[i] == y)
            ar_gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        nTail++;
        score += 10;
        fruitX = rand() % map_width;
        fruitY = rand() % map_height;
    }
}

int main() {
    Setup();
    while (!ar_gameOver) {
        Draw();
        Input();
        Logic();
    }
    return 0;
}
