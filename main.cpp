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
int Dots = 0;
int Score = 0;
//----------------------

int main();

void blocksValidation(int x[]){
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < i; j++){
            if (abs(x[i] - x[j]) <= 3){
                int newx;
                do{
                    newx = 1 + rand() % 14;
                }while(6 <= newx && newx <= 10 && abs(x[i] - x[j]) <= 3);
                x[i] = newx;
            }
        }
    }
}

void randomBlocks(char Field[15][30]){
    int i, j, lasti, lastj;
    int x[50] = {0}, y[50] = {0};
    srand((unsigned) time(NULL));
    for (int t = 0; t < 50; t++){
        i = 1 + (rand() % 14);
        j = 1 + (rand() % 29);
        if ( (6 <= i && i <= 10) || (13 <= j && j <= 18)){
            t--;
            continue;
        }
        x[t] = i; y[t] = j;
    }
    blocksValidation(x);
    for (int e = 0; e < 50; e++){
        Field[x[e]][y[e]] = '#';
    }
}

//---------------------------------------
#define m 15
#define n 30
void initField (char field[m][30]){
    if (IsfirstRun){
        IsfirstRun = false;
        for (int i = 0; i < 15; i++){
            for (int j = 0; j < 30; j++){
                if (i==0 || i==14 || j==0 || j==29 || (i==6 && (13<=j && j<=18)) || (i==10 && (13<=j && j<=18)) || (j==13 && (6<=i && i<=10)) || (j==18 && (6<=i && i<=10))){
                    if ( i == 6 && (j == 15 || j==16)){
                        field[i][j] = '.';
                        Dots++;
                    }else{
                        field[i][j] = '#';
                    }
                }else{
                    field[i][j] = '.';
                    Dots++;
                }
            }
        }
        randomBlocks(field);
    }
}
//--------------------------------------

void printField(char field[15][30]){
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

void getKey(int &x, int &y, char k){
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

void ordinaryMove(char Field[15][30]){
    char k = getch();
    Field[i][j] = ' ';
    getKey(i,j, k);
    Field[i][j] = PacMan;
    system("cls");
    printField(Field);
    ordinaryMove(Field);
}

void endGame(int Score){
    cout<<"\n*** YOU WIN ***\nYour score is "<<Score;
    cout<<"Do you want to play one more time? (y,n)";
    char k = getch();
    if (k == 'y'){
        main();
    }
}

void infinitiMove(char Field[15][30], char k){
    do{
        int LastI = i, LastJ = j;
        getKey(i, j, k);
        if (Field[i][j] == '#'){
            i = LastI;
            j = LastJ;
            k = getch();
            infinitiMove(Field, k);
        }else if(Field[i][j] == '.'){
            Dots--;
            Score += 10;
        }
        Field[LastI][LastJ] = ' ';
        Field[i][j] = PacMan;
        if (i == LastI && j == LastJ){
            break;
        }else{
            Sleep(30);
            system("cls");
            printField(Field);
        }
        cout<<"Your Score : "<<Score<<endl;
        cout<<"Dots : "<<Dots<<endl;
    }while(!kbhit());
    if (Dots == 35){
        system("cls");
        endGame(Score);
    }else{
        k = getch();
        infinitiMove(Field, k);
    }
}

int main(){
    system("cls");
    Score = 0;
    char field[15][30];
    // randomBlocks(field);
    initField(field);
    field[1][1] = PacMan;
    printField(field);
    char k = getch();
    infinitiMove(field, k);
}