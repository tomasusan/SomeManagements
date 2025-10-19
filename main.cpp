#include <iostream>

#include "CellDetect/CellDetect.h"
using namespace std;

int main() {
    auto cell = new CellDetect(true);
    cell->DetectCells();
}