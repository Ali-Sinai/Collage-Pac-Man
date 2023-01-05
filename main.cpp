#include <iostream>
using namespace std;

void Field (char field[50][25]){
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 25; j++){
            if (i==0 || i==49 || j==0 || j==24){
                field[i][j] = '#';
            }
        }
    }
}

int main(){
    // i have no fucking idea.
}