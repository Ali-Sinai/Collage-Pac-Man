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
    return NewI % 3 == 0 ? true : false;
}
//------------------------------------
void RandomBlocks(char Field[FieldI][FieldJ]){
    int BlockNo = 80, i, j, x[BlockNo] = {0};
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
void InitField (char field[FieldI][FieldJ]){
    if (IsfirstRun){
        IsfirstRun = false;
        for (int i = 0; i < FieldI; i++){
            for (int j = 0; j < FieldJ; j++){
                if (i==0 || i==FieldI-1 || j==0 || j==FieldJ-1 || (i==(FieldI/2)-1 && j == (FieldJ/2)-2 && j == (FieldJ/2)+2) || (i==(FieldI/2)+1 && (((FieldJ/2)-2)<=j && j<=((FieldJ/2)+2))) || (j == (FieldJ/2)-2) && ((FieldI/2)-1 <= i && i <= (FieldI/2)+1)  || (j == (FieldJ/2)+2) && ((FieldI/2)-1 <= i && i <= (FieldI/2)+1)){
                    field[i][j] = '#';
                }else{
                    field[i][j] = '.';
                }
            }
        }
        RandomBlocks(field);
    }
}
//--------------------------------------
void PrintField(char field[FieldI][FieldJ]){
    for (int i = 0; i < FieldI; i++){
        for (int j = 0; j < FieldJ; j++){
            if (field[i][j] == PacMan){
                cout<<dye::blue(field[i][j])<<" ";
            }else{
            cout<<field[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}
//-------------------------------------------
void GetKey(int &x, int &y, char k){
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
//     PrintField(Field);
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
//             PrintField(Field);
//         }
//     }while(!kbhit());
//     k = getch();
//     InfinitiMove(Field, k);
    
// }
//------------------------------------------------------
void moveWithCursorInfinity(char Field[FieldI][FieldJ], char k){
    do{
        int LastI = i, LastJ = j;
        GetKey(i, j, k);
        if (Field[i][j] == '#'){
            i = LastI;
            j = LastJ;
            k = getch();
            moveWithCursorInfinity(Field, k);
        }
        Field[LastI][LastJ] = ' ';
        Field[i][j] = PacMan;
        if (i == LastI && j == LastJ){
            continue;
        }else{
            gotoxy(0,0);
            Sleep(30);
            PrintField(Field);
        }
    }while(!kbhit());
    k = getch();
    moveWithCursorInfinity(Field, k);
}
//-----------------------------------------------
int main(){
    // cout<<dye::aqua("hi there");
    system("cls");
    char field[FieldI][FieldJ];
    InitField(field);
    field[1][1] = PacMan;
    PrintField(field);
    // cursorPrintField(field);
    // OrdinaryMove(field);
    char k = getch();
    // InfinitiMove(field, k);
    moveWithCursorInfinity(field, k);
}