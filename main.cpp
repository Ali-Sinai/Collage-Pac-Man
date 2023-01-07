#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
using namespace std;

//----------------------
int i=1, j=1;
char LastChar = ' ';
char PacMan = 16;
bool IsfirstRun = true;
//----------------------

void RandomBlocks(char Field[25][50]){
    int i, j;
    srand((unsigned) time(0));
    for (int t = 0; t < 100; t++){
        i = 1 + rand() % 24;
        j = 1 + rand() % 49;
        if ( (11 <= i && i <= 15) || (23 <= j && j <= 28)){
            t--;
            continue;
        }
        Field[i][j] = '#';
        // cout<<i<<","<<j<<"   ";
    }
}

//---------------------------------------
void InitField (char field[25][50]){
    if (IsfirstRun){
        IsfirstRun = false;
        for (int i = 0; i < 25; i++){
        for (int j = 0; j < 50; j++){
            if (i==0 || i==24 || j==0 || j==49 || (i==11 && (23<=j && j<=28)) || (i==15 && (23<=j && j<=28)) || (j==23 && (11<=i && i<=15)) || (j==28 && (11<=i && i<=15))){
                if ( i == 11 && (j == 25 || j==26)){
                    field[i][j] = ' ';
                }else{
                    field[i][j] = '#';
                }
            }else{
                field[i][j] = ' ';
            }
        }
    }
    RandomBlocks(field);
    }
}
//--------------------------------------

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
                PacMan = 30;
            };
            break;
        case 's':
            if (x+1 > 0 && x+1<24){
                x += 1;
                PacMan = 31;
            };
            break;
        case 'a':
            if (y-1 > 0 && y-1<49){
                y -= 1;
                PacMan = 17;
            }
            break;
        case 'd':
            if (y+1 > 0 && y+1<49){
                y += 1;
                PacMan = 16;
            }
            break;
    }

}

void OrdinaryMove(char Field[25][50]){
    char k = getch();
    Field[i][j] = ' ';
    GetKey(i,j, k);
    Field[i][j] = PacMan;
    system("cls");
    PrintField(Field);
    OrdinaryMove(Field);
}

void InfinitiMove(char Field[25][50], char k){
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
            system("cls");
            PrintField(Field);
        }
    }while(!kbhit());
    k = getch();
    InfinitiMove(Field, k);
    
}

int main(){
    char field[25][50];
    InitField(field);
    field[1][1] = PacMan;
    PrintField(field);
    // OrdinaryMove(field);
    char k = getch();
    InfinitiMove(field, k);
}