/// Space Invaders

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <ctime>

using namespace std;

const int l = 15, b = 15;
int health, score;
int shipX, shipY;
int bullX, bullY;
int bullet[15];

int tmp, y, tmp2, y2;
bool urgent;

char board [l][b];

void init (){
    for (int i = 0; i < l; i++){
        for (int j = 0; j < b; j++){
            board[i][j] = ' ';
        }
    }

    health = 100;
    score = 0;
    shipX = l - 1;
    shipY = b - (l / 2) - 1;

    board[shipX][shipY] = 'U';
    urgent = 0;
}

void print (){
    cout << "\nScore -> " << score << "   ";
    cout << "   Your Health -> " << health << "\n\n";

    cout << "\\/";
    for (int i = 0; i < b; i++) cout << "\\/";
    cout << "\n";

    for (int i = 0; i < l; i++){
        cout << "|";
        for (int j = 0; j < b; j++){
            cout << board[i][j] << " ";
        }
        cout << "|\n";
    }

    cout << "--";
    for (int i = 0; i < b; i++) cout << "--";
    cout << "\n\n";

    cout << "* -> Bomb, Hit and Continue its path\n";
    cout << "I -> Bullet, Hit and will Suspend\n";
    cout << "U -> Spaceship, Save it, and Score more\n";
}

void fire(){
    if (shipX == tmp && shipY == y) board[tmp][y] = 'U';
    else board[tmp][y] = ' ';

    if (score % 15 == 0){
        tmp = 0;
        y = rand() % 15;
        urgent = 0;
    }
    else tmp += 1;

    board[tmp][y] = '*';

    if (shipX == tmp2 && shipY == y2) board[tmp2][y2] = 'U';
    else board[tmp2][y2] = ' ';

    if (urgent){
        tmp2 = 0;
        y2 = rand() % 15;
        urgent = 0;
    }
    else tmp2 += 1;

    board[tmp2][y2] = '|';
}

int main(){
    char move_;

    init ();
    float f1 = 0.00, f2 = 0.00;
//    print ();

    while (health){
        clock_t start = clock();

        while ( ! _kbhit() )
        {
            if (((clock() - start) / CLOCKS_PER_SEC) >= f1)
            {
                if (((clock () - start)/ CLOCKS_PER_SEC ) >= f2)
                {
                    system("cls");
                }

                start = clock();
                board[shipX][shipY] = 'U';
                score += 1;

                if (((shipX == tmp && shipY == y) ||
                    (shipX - 1 == tmp && shipY == y)) ||
                    ((shipX == tmp2 && shipY == y2) ||
                    (shipX - 1 == tmp2 && shipY == y2))){

                    health -= 10;
                    urgent = 1;

                    board[shipX][shipY] = 'U';
                }

                fire();
                print();
            }

            if (health <= 0) goto flag;
        }

        move_ = getch();

        system("cls");

        board[shipX][shipY] = ' ';

        switch(move_){
            case 'w': shipX -= 1; break;
            case 's': shipX += 1; break;
            case 'a': shipY -= 1; break;
            case 'd': shipY += 1; break;
        }

        board[shipX][shipY] = 'U';
        score += 1;

        if ((shipX == tmp && shipY == y) ||
            (shipX - 1 == tmp && shipY == y) ||
            ((shipX == tmp2 && shipY == y2) ||
            (shipX - 1 == tmp2 && shipY == y2))){

            health -= 10;
            urgent = 1;

            board[shipX][shipY] = 'U';
        }

        fire();
        print();

        if (health <= 0) break;
    }

    flag:
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n            GAME OVER\n\n\n\n\n\n\n\n";



    return 0;
}
