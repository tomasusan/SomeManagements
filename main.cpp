#include <iostream>

#include "CellDetect/CellDetect.h"
using namespace std;

int main() {
    auto cell = new CellDetect(true);
    cout << "Would you like to only see the root node? Y/N" <<endl;
    char ye;
    cin >>ye;
    bool seeOnlyRoot = false;
    seeOnlyRoot = ye == 'y' || ye == 'Y';
    cell->DetectCells(seeOnlyRoot);
}