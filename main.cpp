#include <memory>
#include "AStar/Matrix.h"

int main() {

    const std::shared_ptr<Matrix<int>> p(new Matrix<int>(4, 4));
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            p->SetAt(i, j, i*4+j);
        }
    }
    p->ShowMatrix();
    return 0;
}
