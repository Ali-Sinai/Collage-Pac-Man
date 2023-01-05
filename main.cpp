#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

int i=0, j=0;

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
    field[1][1] = '>';
}

void PrintField(char field[25][50]){
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 50; j++){
            cout<<field[i][j]<<" ";
        }
        cout<<endl;
    }
}

void GetKey(int &x, int &y){
    char k = getch();
    switch (k){
        case 'w':
            x -= 1;
            break;
        case 's':
            x += 1;
            break;
        case 'a':
            y -= 1;
            break;
        case 'd':
            y += 1;
            break;
    }

}

void OrdinaryMove(char Field[25][50]){
    GetKey(i,j);
    if (i>1 && j>1 && i<24 && j<49){
        for (int t = 1; t < 24; t++){
            for(int k = 1; k < 49; k++){
                if ( t == i && k == j){
                    Field[t][k] = '>';
                }
            }
        }
    }
    system("cls");
    PrintField(Field);
    OrdinaryMove(Field);
}

int main(){
    char field[25][50];
    InitField(field);
    PrintField(field);
    OrdinaryMove(field);
}