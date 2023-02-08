#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <thread>
#include <thread>
#include "color-console-master/include/color.hpp"
using namespace std;
//----------------------
bool isreplayed = false;
int i = 1, j = 1;
char PacMan = 16;
char LastChar1 = '.';
char LastChar2 = '.';
char LastChar3 = '.';
bool IsfirstRun = true;
#define FieldI 15
#define FieldJ 30
int Dots = 0;
int Score = 0;
char Directions[4] = {'w', 's', 'a', 'd'};
char Field[FieldI][FieldJ];
int Life = 4;
bool GameEnded = false;
bool a = false;
bool IsFirstThread = true;
int run = 1;
int GhostisRunningTime = 0;
bool GhostisCaught = false;
int Difficulty;
//----------------------
int main();
void ghost(int Gi, int Gj, char LastChar);
void endGame(int Score, bool win);
//----------------------
bool sixtyChance()
{
    int RandNo = rand() % 10;
    return (RandNo < 6) ? true : false;
}
//----------------------
void gotoxy(char x, char y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}
//----------------------------------------------------
bool blockVlidation(int NewI, int NewJ)
{
    int PatternNo = 2;
    if (NewI == 0 || NewI == FieldI - 1 || NewJ == 0 || NewJ == FieldJ - 1 || (NewI == (FieldI / 2) - 1 && (FieldJ / 2) - 2 <= NewJ && NewJ <= (FieldJ / 2) + 2))
    {
        return false;
    }
    if (Difficulty == 4)
    {
        PatternNo = 2 + rand() % 3;
    }
    return NewI % PatternNo == 0 && NewJ % PatternNo == 0 ? true : false;
}
//------------------------------------
void randomBlocks()
{
    int BlockNo = 100, i, j, x[BlockNo] = {0};
    srand((unsigned)time(0));
    for (int t = 0; t < BlockNo; t++)
    {
        do
        {
            i = 1 + rand() % FieldI - 1;
            j = 1 + rand() % FieldJ - 1;
        } while (!blockVlidation(i, j));
        Field[i][j] = '#';
    }
    for (int t = 0; t < 5; t++)
    {
        do
        {
            i = 1 + rand() % FieldI - 1;
            j = 1 + rand() % FieldJ - 1;
        } while (!blockVlidation(i, j));
        Field[i][j] = '^';
    }
}
//---------------------------------------
void initField()
{
    int DotNumberForVeryHard;
    for (int i = 0; i < FieldI; i++)
    {
        for (int j = 0; j < FieldJ; j++)
        {
            if (i == 0 || i == FieldI - 1 || j == 0 || j == FieldJ - 1 || (i == (FieldI / 2) - 1 && j == (FieldJ / 2) - 2 && j == (FieldJ / 2) + 2) || (i == (FieldI / 2) + 1 && (((FieldJ / 2) - 2) <= j && j <= ((FieldJ / 2) + 2))) || ((j == (FieldJ / 2) - 2) && ((FieldI / 2) - 1 <= i && i <= (FieldI / 2) + 1)) || ((j == (FieldJ / 2) + 2) && ((FieldI / 2) - 1 <= i && i <= (FieldI / 2) + 1)))
            {
                Field[i][j] = '#';
            }
            else if ((i == (FieldI / 2) && (j == (FieldJ / 2) - 1 || j == (FieldJ / 2) || j == (FieldJ / 2) + 1)))
            {
                Field[i][j] = 233;
            }
            else
            {
                Field[i][j] = '.';
            }
        }
    }
    randomBlocks();
}
//--------------------------------------
void printField()
{
    if (run == -1)
    {
        cout << dye::red("DUMB Ghost activated!!\nTime remaining : " + to_string(GhostisRunningTime));
    }
    else if (run == 1)
    {
        cout << dye::red("Run from the ghosts NOW!!");
    }
    cout << dye::red("\nLIFE REMAINING : " + to_string(Life) + "  |  YOUR SCORE IS : " + to_string(Score) + "\n");
    for (int i = 0; i < FieldI; i++)
    {
        for (int j = 0; j < FieldJ; j++)
        {
            if (Field[i][j] == PacMan)
            {
                run == 1 ? cout << dye::yellow(Field[i][j]) << " " : cout << dye::red(Field[i][j]) << " ";
            }
            else if (Field[i][j] == (char)233)
            {
                run == 1 ? cout << dye::red(Field[i][j]) << " " : cout << dye::blue(Field[i][j]) << " ";
            }
            else
            {
                cout << Field[i][j] << " ";
            }
        }
        cout << endl;
    }
}
//------------------------------------
void getKey(int &x, int &y, char k, string C)
{
    switch (k)
    {
    case 'w':
        if (x - 1 > 0 && x - 1 < FieldI - 1)
        {
            // x -= run;
            if (run == -1)
            {
                C == "Pacman" ? x += run : x -= run;
            }
            else
            {
                x -= run;
            }
            PacMan = C == "Pacman" ? 30 : PacMan;
        };
        break;
    case 's':
        if (x + 1 > 0 && x + 1 < FieldI - 1)
        {
            // x += run;
            if (run == -1)
            {
                C == "Pacman" ? x -= run : x += run;
            }
            else
            {
                x += run;
            }
            PacMan = C == "Pacman" ? 31 : PacMan;
        };
        break;
    case 'a':
        if (y - 1 > 0 && y - 1 < FieldJ - 1)
        {
            // y -= run;
            if (run == -1)
            {
                C == "Pacman" ? y += run : x -= run;
            }
            else
            {
                y -= run;
            }
            PacMan = C == "Pacman" ? 17 : PacMan;
        }
        break;
    case 'd':
        if (y + 1 > 0 && y + 1 < FieldJ - 1)
        {
            // y += run;
            if (run == -1)
            {
                C == "Pacman" ? y -= run : x += run;
            }
            else
            {
                y += run;
            }
            PacMan = C == "Pacman" ? 16 : PacMan;
        }
        break;
    }
}
//--------------------------------------
// void OrdinaryMove(char Field[FieldI][FieldJ]){
//     char k = getch();
//     Field[i][j] = ' ';
//     GetKey(i,j, k);
//     Field[i][j] = PacMan;
//     system("cls");
//     printField(Field);
//     OrdinaryMove(Field);
// }
//---------------------------------------
// void InfinitiMove(char Field[FieldI][FieldJ], char k){
//     do{
//         int LastI = i, LastJ = j;
//         GetKey(i, j, k);
//         if (Field[i][j] == '#'){
//             i = LastI;
//             j = LastJ;
//             k = getch();
//             InfinitiMove(Field, k);
//         }
//         Field[LastI][LastJ] = ' ';
//         Field[i][j] = PacMan;
//         if (i == LastI && j == LastJ){
//             continue;
//         }else{
//             Sleep(30);
//             system("cls");
//             printField(Field);
//         }
//     }while(!kbhit());
//     k = getch();
//     InfinitiMove(Field, k);
// }
//------------------------------------------------------
void checkNumberOfDots()
{
    Dots = 0;
    for (int i = 0; i < FieldI; i++)
    {
        for (int j = 0; j < FieldJ; j++)
        {
            if (Field[i][j] == '.')
            {
                Dots++;
            }
        }
    }
    if (Dots == 0)
    {
        system("cls");
        endGame(Score, true);
    }
}
//------------------------------------------------------
void endGame(int Score, bool win)
{
    GameEnded = true;
    Sleep(200);
    system("cls");
    win ? cout << "YOU WIN!!" : cout << "YOU LOST!!";
    cout << "\nYour Score is " << Score << "!!\nPress any key to continue...";
    getch();
    abort();
}
//------------------------------------------------------
bool isCaugthByGhost(int Gi, int Gj)
{
    if (Field[Gi][Gj] == PacMan)
    {
        i = 1;
        j = 1;
        Life--;
        if (Life == 0)
        {
            endGame(Score, false);
        }
        return true;
    }
    return false;
}
//------------------------------------------------------
void changeGhostLoc(int RandDirection, int Gi, int Gj, char LastChar)
{
    int LastGI = Gi, LastGJ = Gj;
    getKey(Gi, Gj, Directions[RandDirection], "Ghost");
    if (Field[Gi][Gj] == '#' || Field[Gi][Gj] == (char)233)
    {
        Gi = LastGI;
        Gj = LastGJ;
        ghost(Gi, Gj, LastChar);
    }
    Field[LastGI][LastGJ] = LastChar;
    LastChar = Field[Gi][Gj];
    LastChar = isCaugthByGhost(Gi, Gj) ? ' ' : LastChar;
    Field[Gi][Gj] = (char)233;
    ghost(Gi, Gj, LastChar);
}
//------------------------------------------------------
int ranDirFunc(int Gi, int Gj)
{
    if (abs(i - Gi) == 1 || abs(j - Gj) == 1)
    {
        if (i > Gi)
        {
            return 1;
        }
        else if (i < Gi)
        {
            return 0;
        }
        else if (j > Gj)
        {
            return 3;
        }
        else if (j < Gj)
        {
            return 2;
        }
    }
    else if (i > Gi && j > Gj)
    {
        if (sixtyChance)
        {
            return rand() % 2 == 0 ? 1 : 3;
        }
        else
        {
            return 2;
        }
    }
    else if (i > Gi && j < Gj)
    {
        if (sixtyChance)
        {
            return 1 + rand() % 2;
        }
        else
        {
            return 3;
        }
    }
    else if (i < Gi && j > Gj)
    {
        if (sixtyChance)
        {
            return rand() % 2 == 0 ? 0 : 3;
        }
        else
        {
            return 2;
        }
    }
    else if (i < Gi && j < Gj)
    {
        if (sixtyChance)
        {
            return rand() % 2 == 0 ? 0 : 2;
        }
        else
        {
            return 3;
        }
    }
}
//------------------------------------------------------
int ghostDifficulty(int Gi, int Gj)
{
    switch (Difficulty)
    {
    case 1:
        return rand() % 4;
        break;
    case 2:
        if (abs(i - Gi) <= 5 && abs(j - Gj) <= 5)
        {
            return ranDirFunc(Gi, Gj);
        }
        else
        {
            return rand() % 4;
        }
        break;
    case 3:
    case 4:
        return ranDirFunc(Gi, Gj);
        break;
    }
}
//------------------------------------------------------
void ghost(int Gi, int Gj, char LastChar)
{
    srand((unsigned)time(0));
    int FirstGI, FirstGJ;
    if (IsFirstThread)
    {
        FirstGI = Gi;
        FirstGJ = Gj;
        IsFirstThread = false;
    }
    Sleep(100);
    int RandDirection = ghostDifficulty(Gi, Gj);
    if (i == Gi && j == Gj && GhostisCaught)
    {
        Gi = FirstGI + 1;
        Gj = FirstGJ;
        GhostisCaught = false;
        Sleep(500);
    }
    changeGhostLoc(RandDirection, Gi, Gj, LastChar);
}
//------------------------------------------------------
void moveWithCursorInfinity(char k)
{
    do
    {
        if (Difficulty == 4)
        {
            randomBlocks();
        }
        if (GameEnded)
        {
            system("cls");
            break;
        }
        checkNumberOfDots();
        if (GhostisRunningTime == 0 && run == -1)
        {
            run = 1;
            system("cls");
        }
        int LastI = i, LastJ = j;
        getKey(i, j, k, "Pacman");
        if (Field[i][j] == '#')
        {
            i = LastI;
            j = LastJ;
            gotoxy(0, 0);
            printField();
        }
        if (Field[i][j] == '.')
        {
            Score += 10;
            Dots--;
        }
        if (Field[i][j] == '^')
        {
            system("cls");
            GhostisRunningTime = 90;
            run = -1;
            Score += 50;
        }
        if (run == -1)
        {
            if (Field[i][j] == (char)233)
            {
                Score += 200;
                GhostisCaught = true;
            }
        }
        Field[LastI][LastJ] = ' ';
        Field[i][j] = PacMan;
        gotoxy(0, 0);
        Sleep(40);
        printField();
        if (run == -1)
        {
            GhostisRunningTime -= 1;
        }
    } while (!kbhit());
    k = getch();
    moveWithCursorInfinity(k);
    moveWithCursorInfinity(k);
}
//-----------------------------------------------
int main()
{
    system("cls");
    cout << "HI !\nMy name is Mr.PacMan. Choose your difficulty :";
    cout << "\n1. Pfff.. :)\n2. Hmm.. Ok\n3. Oh no...\n4. HOLY SH**!!\n>> ";
    cin >> Difficulty;
    initField();
    srand((unsigned)time(0));
    switch (Difficulty)
    {
    case 1:
    case 2:
        Field[1][1] = PacMan;
        printField();
        break;
    case 3:
    case 4:
        do
        {
            i = 1 + rand() % FieldI - 1;
            j = 1 + rand() % FieldI - 1;
        } while (Field[i][j] == '#' || Field[i][j] == char(233) || Field[i][j] == '^');
        Field[i][j] = PacMan;
        break;
    }
    char k = getch();
    thread pac(moveWithCursorInfinity, k);
    thread g1(ghost, (FieldI / 2), (FieldJ / 2) - 1, LastChar1);
    thread g2(ghost, (FieldI / 2), (FieldJ / 2), LastChar2);
    thread g3(ghost, (FieldI / 2), (FieldJ / 2) + 1, LastChar3);
    if (GameEnded)
    {
        Sleep(200);
        system("cls");
        pac.detach();
        system("cls");
    }
    pac.join();
    g1.join();
    g2.join();
    g3.join();
}