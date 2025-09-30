#include <memory>

#include "AStar/AStarMatrix.h"
#include "AStar/Matrix.h"


int main() {
    std::shared_ptr<AStarMatrix> p(new AStarMatrix(0, 0, {0, 0}, {0, 0}, true));
    p->ShowMatrix();
    p->FindWay();
    return 0;
}
