#include "OtherTask/DrawDiagram.h"
using namespace std;

int main() {
    const vector<int> v = {40, 58, 54, 56, 38, 39, 48, 41, 40, 49, 58, 60, 61};
    DrawDiagram::DrawColumnDiagram(v, 100);
    return 0;
}
