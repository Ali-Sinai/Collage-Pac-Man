#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include "color-console-master/include/color.hpp"
using namespace std;

//----------------------
int i=1, j=1;
char LastChar = ' ';
char PacMan = 16;
bool IsfirstRun = true;
//----------------------

void RandomBlocks(char Field[15][30]){
    int i, j;
    srand((unsigned) time(0));
    for (int t = 0; t < 50; t++){
        i = 1 + rand() % 14;
        j = 1 + rand() % 29;
        if ( (6 <= i && i <= 10) || (13 <= j && j <= 18)){
            t--;
            continue;
        }
        Field[i][j] = '#';
    }
}

//---------------------------------------
void InitField (char field[15][30]){
    if (IsfirstRun){
        IsfirstRun = false;
        for (int i = 0; i < 15; i++){
        for (int j = 0; j < 30; j++){
            if (i==0 || i==14 || j==0 || j==29 || (i==6 && (13<=j && j<=18)) || (i==10 && (13<=j && j<=18)) || (j==13 && (6<=i && i<=10)) || (j==18 && (6<=i && i<=10))){
                if ( i == 6 && (j == 15 || j==16)){
                    field[i][j] = '.';
                }else{
                    field[i][j] = '#';
                }
            }else{
                field[i][j] = '.';
            }
        }
    }
    RandomBlocks(field);
    }
}
//--------------------------------------

void PrintField(char field[15][30]){
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 30; j++){
            if (field[i][j] == PacMan){
                cout<<dye::blue(field[i][j])<<" ";
            }else{
            cout<<field[i][j]<<" ";
            }
        }
        cout<<endl;
    }
}

void GetKey(int &x, int &y, char k){
    switch (k){
        case 'w':
            if (x-1 > 0 && x-1<14){
                x -= 1;
                PacMan = 30;
            };
            break;
        case 's':
            if (x+1 > 0 && x+1<14){
                x += 1;
                PacMan = 31;
            };
            break;
        case 'a':
            if (y-1 > 0 && y-1<29){
                y -= 1;
                PacMan = 17;
            }
            break;
        case 'd':
            if (y+1 > 0 && y+1<29){
                y += 1;
                PacMan = 16;
            }
            break;
    }

}

void OrdinaryMove(char Field[15][30]){
    char k = getch();
    Field[i][j] = ' ';
    GetKey(i,j, k);
    Field[i][j] = PacMan;
    system("cls");
    PrintField(Field);
    OrdinaryMove(Field);
}

void InfinitiMove(char Field[15][30], char k){
    do{
        int LastI = i, LastJ = j;
        GetKey(i, j, k);
        if (Field[i][j] == '#'){
            i = LastI;
            j = LastJ;
            k = getch();
            InfinitiMove(Field, k);
        }
        Field[LastI][LastJ] = ' ';
        Field[i][j] = PacMan;
        if (i == LastI && j == LastJ){
            continue;
        }else{
            Sleep(30);
            system("cls");
            PrintField(Field);
        }
    }while(!kbhit());
    k = getch();
    InfinitiMove(Field, k);
    
}

int main(){
    // cout<<dye::aqua("hi there");
    char field[15][30];
    InitField(field);
    field[1][1] = PacMan;
    PrintField(field);
    // OrdinaryMove(field);
    char k = getch();
    InfinitiMove(field, k);
}