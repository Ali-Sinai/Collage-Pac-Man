#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include "color-console-master/include/color.hpp"
using namespace std;
//----------------------
int i=1, j=1;
char LastChar = ' ';
char PacMan = 16;
bool IsfirstRun = true;
#define FieldI 15
#define FieldJ 30
int Dots = 0;
int Score = 0;
//----------------------
int main();
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
void randomBlocks(char Field[FieldI][FieldJ]){
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
void initField (char field[FieldI][FieldJ]){
    if (IsfirstRun){
        IsfirstRun = false;
        for (int i = 0; i < FieldI; i++){
            for (int j = 0; j < FieldJ; j++){
                if (i==0 || i==FieldI-1 || j==0 || j==FieldJ-1 || (i==(FieldI/2)-1 && j == (FieldJ/2)-2 && j == (FieldJ/2)+2) || (i==(FieldI/2)+1 && (((FieldJ/2)-2)<=j && j<=((FieldJ/2)+2))) || ((j == (FieldJ/2)-2) && ((FieldI/2)-1 <= i && i <= (FieldI/2)+1))  || ((j == (FieldJ/2)+2) && ((FieldI/2)-1 <= i && i <= (FieldI/2)+1))){
                    field[i][j] = '#';
                }else{
                    field[i][j] = '.';
                }
            }
        }
        randomBlocks(field);
    }
}
//--------------------------------------
void printField(char field[FieldI][FieldJ]){
    for (int i = 0; i < FieldI; i++){
        for (int j = 0; j < FieldJ; j++){
            if (field[i][j] == PacMan){
                cout<<dye::yellow(field[i][j])<<" ";
            }else{
                cout<<field[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}
//------------------------------------
void getKey(int &x, int &y, char k){
    switch (k){
        case 'w':
            if (x-1 > 0 && x-1<FieldI-1){
                x -= 1;
                PacMan = 30;
            };
            break;
        case 's':
            if (x+1 > 0 && x+1<FieldI-1){
                x += 1;
                PacMan = 31;
            };
            break;
        case 'a':
            if (y-1 > 0 && y-1<FieldJ-1){
                y -= 1;
                PacMan = 17;
            }
            break;
        case 'd':
            if (y+1 > 0 && y+1<FieldJ-1){
                y += 1;
                PacMan = 16;
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
void endGame(int Score){
    cout<<"You Win!!\nYour Score is "<<Score<<"!!\nDo You Want to Play Again? (y,n)";
    char ans = getch();
    if (ans == 'y'){
        main();
    }else if (ans == 'n'){
        cout<<"GoodBye!";
        abort();
    }else{
        ;
    }
}
//------------------------------------------------------
void checkNumberOfDots(char field[FieldI][FieldJ]){
    Dots = 0;
    for (int i = 0; i < FieldI; i++){
        for (int j = 0; j < FieldJ; j++){
            if (field[i][j] == '.'){
                Dots++;
            }
        }
    }
    if (Dots == 0){
        endGame(Score);
    }
}
//------------------------------------------------------
void moveWithCursorInfinity(char Field[FieldI][FieldJ], char k){
    do{
        checkNumberOfDots(Field);
        int LastI = i, LastJ = j;
        getKey(i, j, k);
        if (Field[i][j] == '#'){
            i = LastI;
            j = LastJ;
            k = getch();
            moveWithCursorInfinity(Field, k);
        }
        if (Field[i][j] == '.'){
            Score += 10;
            Dots--;
        }
        Field[LastI][LastJ] = ' ';
        Field[i][j] = PacMan;
        if (i == LastI && j == LastJ){
            break;
        }else{
            gotoxy(0,0);
            Sleep(30);
            printField(Field);
        }
        cout<<dye::black_on_white("Your Score : ")<<dye::black_on_white(Score)<<endl;
    }while(!kbhit());
    k = getch();
    moveWithCursorInfinity(Field, k);
}
//-----------------------------------------------
int main(){
    i=1; 
    j=1;
    LastChar = ' ';
    PacMan = 16;
    IsfirstRun = true;
    Dots = 0;
    Score = 0;
    system("cls");
    char field[FieldI][FieldJ];
    initField(field);
    field[1][1] = PacMan;
    printField(field);
    char k = getch();
    moveWithCursorInfinity(field, k);
}