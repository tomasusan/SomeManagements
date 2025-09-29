#pragma once
#include "Matrix.h"
#include "LogManagement.h"
#include <queue>
using namespace std;

struct State {
    pair<int, int> CurPosition;
    pair<int, int> EndPosition;

    int ToDistance() const {
        return abs(CurPosition.first - EndPosition.first) + abs(CurPosition.second - EndPosition.second);
    }

    bool operator>(const State &Other) const {
        return Other.ToDistance() < ToDistance();
    }

    bool operator<(const State &Other) const {
        return ToDistance() < Other.ToDistance();
    }
};

enum NextDirection {
    Right = 1,
    Left = -1,
    Up = -1,
    Down = 1
};

class AStarMatrix : public Matrix<char> {
public:
    AStarMatrix(int InRow, int InCol, const std::pair<int, int> &InStart, const std::pair<int, int> &InEnd,
                bool LoadDefault);

    virtual void ShowMatrix() override;
    void FindWay();
private:
    std::pair<int, int> Start, End;

    priority_queue<State> StateQueue;
    void LoadDefaultMatrix();
    NextDirection NextVertical = Up;
    NextDirection NextHorizontal = Right;
};

inline AStarMatrix::AStarMatrix(int InRow, int InCol, const std::pair<int, int> &InStart,
                                const std::pair<int, int> &InEnd, bool LoadDefault): Matrix<char>(0, 0) {
    if (LoadDefault) {
        LoadDefaultMatrix();
    } else {
        ResizeMatrix(InRow, InCol);
        Start = InStart;
        End = InEnd;
    }
}

inline void AStarMatrix::LoadDefaultMatrix() {
    const char *DefaultMatrix[] = {
        "********",
        "*S**#***",
        "****#***",
        "****#***",
        "****#***",
        "**###*E*",
        "****#***",
        "********"
    };

    ResizeMatrix(8, 8);

    LogManagement::GetInstance()->Display("Init Default", "AStarMatrix");
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            SetAt(i, j, DefaultMatrix[i][j]);
            if (DefaultMatrix[i][j] == 'S') Start = {i, j};
            if (DefaultMatrix[i][j] == 'E') End = {i, j};
        }

    NextVertical = End.first - Start.first > 0 ? Down: Up;
    NextHorizontal = Start.second - End.second > 0 ? Right: Left;

}

inline void AStarMatrix::ShowMatrix() {
    Matrix<char>::ShowMatrix();
}

inline void AStarMatrix::FindWay() {
    State StartState{Start, End};
    StateQueue.push(StartState);
    while (!StateQueue.empty()) {
        const auto CurState = StateQueue.top();
        StateQueue.pop();

        auto StateVertical = CurState;
        StateVertical.CurPosition.first += NextVertical;

        auto StateHorizontal = CurState;
        StateHorizontal.CurPosition.second += NextHorizontal;

        auto StateSlating = CurState;
        StateSlating.CurPosition.first += NextVertical;
        StateSlating.CurPosition.second += NextHorizontal;

        if (*GetAt(StateVertical.CurPosition.first, StateVertical.CurPosition.second) != '#') StateQueue.push(StateVertical);
        if (*GetAt(StateHorizontal.CurPosition.first, StateHorizontal.CurPosition.second) != '#') StateQueue.push(StateHorizontal);
        if (*GetAt(StateSlating.CurPosition.first, StateSlating.CurPosition.second) != '#') StateQueue.push(StateSlating);

        

    }
}
