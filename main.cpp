#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

int i=1, j=1;
char PacMan = '>';


void InitField (char field[25][50]){
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 50; j++){
            if (i==0 || i==24 || j==0 || j==49){
                field[i][j] = '#';
            }else{
                field[i][j] = ' ';
            }
        }
    }
}

void PrintField(char field[25][50]){
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 50; j++){
            cout<<field[i][j]<<" ";
        }
        cout<<endl;
    }
}

void GetKey(int &x, int &y, char k){
    switch (k){
        case 'w':
            if (x-1 > 0 && x-1<24){
                x -= 1;
            };
            break;
        case 's':
            if (x+1 > 0 && x+1<24){
                x += 1;
            };
            break;
        case 'a':
            if (y-1 > 0 && y-1<49){
                y -= 1;
                PacMan = '<';
            }
            break;
        case 'd':
            if (y+1 > 0 && y+1<49){
                y += 1;
                PacMan = '>';
            }
            break;
    }

}

void OrdinaryMove(char Field[25][50]){
    char k = getch();
    GetKey(i,j, k);
    InitField(Field);
    for (int t = 1; t < 24; t++){
        for(int k = 1; k < 49; k++){
            if ( t == i && k == j){
                Field[t][k] = '>';
            }
        }
    }
    system("cls");
    PrintField(Field);
    OrdinaryMove(Field);
}

void InfinitiMove(char Field[25][50], char k){
    do{
        GetKey(i, j, k);
        InitField(Field);
        for (int t = 1; t < 24; t++){
            for(int k = 1; k < 49; k++){
                if ( t == i && k == j){
                    Field[t][k] = '>';
                }
            }
        }
        system("cls");
        PrintField(Field);
    }while(!kbhit());
    k = getch();
    InfinitiMove(Field, k);
}

int main(){
    char field[25][50];
    InitField(field);
    field[1][1] = '>';
    PrintField(field);
    char k = getch();
    InfinitiMove(field, k);
}