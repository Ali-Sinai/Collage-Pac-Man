#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <thread>
#include "color-console-master/include/color.hpp"
using namespace std;
//----------------------
int i=1, j=1;
char LastChar = '.';
char PacMan = 16;
bool IsfirstRun = true;
#define FieldI 15
#define FieldJ 30
int Dots = 0;
int Score = 0;
char Directions[4] = {'w', 's', 'a', 'd'};
int LastGI, LastGJ;
char Field[FieldI][FieldJ];
//----------------------
int main();
void ghost(int Gi, int Gj);
//----------------------
bool sixtyChance(){
    int RandNo = rand() % 10;
    return (RandNo < 6) ? true : false;
}
//----------------------
void gotoxy(char x, char y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}
//----------------------------------------------------
bool blockVlidation(int NewI, int NewJ){
    if (NewI == 0 || NewI == FieldI-1 || NewJ == 0 || NewJ == FieldJ-1 || (NewI==(FieldI/2)-1 && (FieldJ/2)-2 <= NewJ && NewJ <= (FieldJ/2)+2)){
        return false;
    }
    return NewI % 2 == 0 && NewJ % 2 == 0 ? true : false;
}
//------------------------------------
void randomBlocks(){
    int BlockNo = 100, i, j, x[BlockNo] = {0};
    srand((unsigned) time(0));
    for (int t = 0; t < BlockNo; t++){
        do{
            i = 1 + rand() % FieldI-1;
            j = 1 + rand() % FieldJ-1;
        }while (!blockVlidation(i, j));
        Field[i][j] = '#';
    }
}
//---------------------------------------
void initField (){
    if (IsfirstRun){
        IsfirstRun = false;
        for (int i = 0; i < FieldI; i++){
            for (int j = 0; j < FieldJ; j++){
                if (i==0 || i==FieldI-1 || j==0 || j==FieldJ-1 || (i==(FieldI/2)-1 && j == (FieldJ/2)-2 && j == (FieldJ/2)+2) || (i==(FieldI/2)+1 && (((FieldJ/2)-2)<=j && j<=((FieldJ/2)+2))) || ((j == (FieldJ/2)-2) && ((FieldI/2)-1 <= i && i <= (FieldI/2)+1))  || ((j == (FieldJ/2)+2) && ((FieldI/2)-1 <= i && i <= (FieldI/2)+1))){
                    Field[i][j] = '#';
                }else if ((i == (FieldI/2) && (j == (FieldJ/2)-1 || j == (FieldJ/2) || j == (FieldJ/2)+1))){
                    Field[i][j] = 233;
                }else{
                    Field[i][j] = '.';
                }
            }
        }
        randomBlocks();
    }
}
//--------------------------------------
void printField(){
    for (int i = 0; i < FieldI; i++){
        for (int j = 0; j < FieldJ; j++){
            if (Field[i][j] == PacMan){
                cout<<dye::yellow(Field[i][j])<<" ";
            }else if (Field[i][j] == (char)233){
                   cout<<dye::red(Field[i][j])<<" "; 
            }else{
                cout<<Field[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}
//------------------------------------
void getKey(int &x, int &y, char k, string C){
    switch (k){
        case 'w':
            if (x-1 > 0 && x-1<FieldI-1){
                x -= 1;
                PacMan = C == "Pacman" ? 30 : PacMan;
            };
            break;
        case 's':
            if (x+1 > 0 && x+1<FieldI-1){
                x += 1;
                PacMan = C == "Pacman" ? 31 : PacMan;
            };
            break;
        case 'a':
            if (y-1 > 0 && y-1<FieldJ-1){
                y -= 1;
                PacMan = C == "Pacman" ? 17 : PacMan;
            }
            break;
        case 'd':
            if (y+1 > 0 && y+1<FieldJ-1){
                y += 1;
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
void endGame(int Score, bool win){
    // gotoxy(160,0);
    win ? cout<<"YOU WIN!!" : cout<<"YOU LOST!!";
    cout<<"\nYour Score is "<<Score<<"!!\nDo You Want to Play Again? (y,n)";
    char ans = getch();
    if (ans == 'y'){
        gotoxy(0,0);
        i=1; j=1;
        LastChar = '.';
        PacMan = 16;
        IsfirstRun = true;
        Dots = 0; Score = 0;
        main();
    }else{
        cout<<"GoodBye!";
        abort();
    }
}
//------------------------------------------------------
void checkNumberOfDots(){
    Dots = 0;
    for (int i = 0; i < FieldI; i++){
        for (int j = 0; j < FieldJ; j++){
            if (Field[i][j] == '.'){
                Dots++;
            }
        }
    }
    if (Dots == 0){
        endGame(Score, true);
    }
}
//------------------------------------------------------
void changeGhostLoc(int RandDirection, int Gi, int Gj){
    getKey(Gi, Gj, Directions[RandDirection], "Ghost");
    if ( Field[Gi][Gj] == (char)233 ){
        getKey(Gi, Gj, Directions[RandDirection], "Ghost");
    }
    if ( Field[Gi][Gj] == '#' ){
        Gi = LastGI;
        Gj = LastGJ;
        ghost(Gi, Gj);
    }
    Field[LastGI][LastGJ] = LastChar;
    LastChar = Field[Gi][Gj];
    if (Field[Gi][Gj] == PacMan){
        Field[Gi][Gj] = (char)233;
        Sleep(500);
        endGame(Score, false);
    }
    Field[Gi][Gj] = (char)233;
    ghost(Gi, Gj);
}
//------------------------------------------------------
int ranDirFunc(int Gi, int Gj){
    if (abs(i - Gi) == 1 && abs(j - Gj) == 1){
        if (i > Gi){
            return 1;
        }else if (i < Gi){
            return 0;
        }else if (j > Gj){
            return 3;
        }else if (j < Gj){
            return 2;
        }
    }
    else if ( i > Gi && j > Gj){
        if (sixtyChance){
            return rand() % 2 == 0 ? 1 : 3;
        }else{
            return 2;
        }
    }else if (i > Gi && j < Gj){
        if (sixtyChance){
            return 1 + rand() % 2;
        }else{
            return 3;
        }
    }else if (i < Gi && j > Gj){
        if (sixtyChance){
            return rand() % 2 == 0 ? 0 : 3;
        }else{
            return 2;
        }
    }else if (i < Gi && j < Gj){
        if (sixtyChance){
            return rand() % 2 == 0 ? 0 : 2;
        }else{
            return 3;
        }
    }
}
//------------------------------------------------------
void ghost(int Gi, int Gj){
    Sleep(100);
    LastGI = Gi; LastGJ = Gj;
    int RandDirection;
    if (abs(i - Gi) <= 5 && abs(j - Gj) <= 5){
        RandDirection = ranDirFunc(Gi, Gj);
    }else{
        RandDirection = rand() % 4;
    }
    changeGhostLoc(RandDirection, Gi, Gj);
}
//------------------------------------------------------
void moveWithCursorInfinity(char k){
    do{
        checkNumberOfDots();
        int LastI = i, LastJ = j;
        getKey(i, j, k, "Pacman");
        if (Field[i][j] == '#'){
            i = LastI;
            j = LastJ;
            gotoxy(0,0);
            printField();
        }
        if (Field[i][j] == '.'){
            Score += 10;
            Dots--;
        }
        Field[LastI][LastJ] = ' ';
        Field[i][j] = PacMan;
        gotoxy(0,0);
        Sleep(30);
        printField();
        cout<<dye::black_on_white("Your Score : ")<<dye::black_on_white(Score)<<endl;
    }while(!kbhit());
    k = getch();
    moveWithCursorInfinity(k);
}
//-----------------------------------------------
int main(){
    system("cls");
    initField();
    Field[1][1] = PacMan;
    printField();
    char k = getch();
    thread g1(ghost, (FieldI/2), (FieldJ/2)-1);
    thread g2(ghost, (FieldI/2), (FieldJ/2));
    thread g3(ghost, (FieldI/2), (FieldJ/2)+1);
    thread t2(moveWithCursorInfinity, k);
    t2.join();
    g1.join();
    g2.join();
    g3.join();
}