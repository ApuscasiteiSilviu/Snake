#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

int gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY;
int tailX[100], tailY[100];
int ntail;
int score;
enum eDirection{ STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Initializare()
{
    gameOver = 0;
    dir = STOP; /// asezam capul in mijloc, deci de acolo va incepe jocul
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

}

void Map()
{
     int i;
     system("cls");
     for (i = 0; i < width ; i++)
        cout << "#";

     if (i == width)
        cout << "##";
     cout << endl;

     for (int i = 0; i < height; i++)
     {
         for (int j = 0; j < width; j++)
           {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                        cout << " ";
            }

            if (j == width - 1)
                cout << "#";
           }
          cout << endl;
     }

     for (int i = 0; i < width; i++)
        cout << "#";

     if (i == width)
        cout << "##";
     cout << endl;

     cout << "Your score: " << score;
}

void Directie()
{
       if (_kbhit())
     {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
     }
}

void Logica()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int pre2X, pre2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < ntail; i++)
    {
        pre2X = tailX[i];
        pre2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = pre2X;
        prevY = pre2Y;
    }

    switch (dir)
    {
   case LEFT:
       x--;
       break;
   case RIGHT:
       x++;
       break;
   case UP:
       y--;
       Sleep(50);
       break;
   case DOWN:
       y++;
       Sleep(50);
       break;
   default:
       break;
    }

    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;

    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    for (int i = 0; i < ntail; i++)
        if (tailX[i] == x && tailY[i] == y)
        gameOver = 1;

    if (x == fruitX && y == fruitY)
    {
        ntail++;
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }

}


int main()
{
    Initializare();
    while(!gameOver)
    {
       Map();
       Directie();
       Logica();
       Sleep(10);
    }
    cout << endl;
    cout << "Game over!";
    return 0;
}
