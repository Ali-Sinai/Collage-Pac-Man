#include <iostream>
using namespace std;

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

int main(){
    char field[25][50];
    InitField(field);
    PrintField(field);
}