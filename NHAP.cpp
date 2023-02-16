#include<iostream>
#include <cstring>
using namespace std;
int chuyen(char c){
          return (int)c-48;
         }

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

int main(){

    system("pause");
    return 0;
}