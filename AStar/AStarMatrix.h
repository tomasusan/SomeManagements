#pragma once
#include "Matrix.h"
#include "LogManagement.h"
#include <queue>
#include <unordered_set>
#include <functional>
#include <vector>
#include <windows.h>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;

struct State {
    pair<int, int> CurPosition;
    pair<int, int> PrevPosition;
    pair<int, int> StartPosition;
    pair<int, int> EndPosition;
    float MaxDist = 0.f;

    vector<pair<int, int> > VisitedPoint;

    float ActualCost = .0f;

    float Distance(const pair<int, int> &s, const pair<int, int> &e) const {
        return sqrt(pow(s.first - e.first, 2) + pow(s.second - e.second, 2));
    }

    // 动态权重，防止过于靠近起点或终点时固定权重失效
    float DynamicWeight() const {
        float totalDist = Distance(StartPosition, EndPosition);
        float progress = Distance(StartPosition, CurPosition) / totalDist;
        return 0.3f + 0.4f * progress; // 权重在0.3到0.7之间动态变化
    }

    float StartCostWeight = 0.5;

    float TotalCost() const {
        auto g = ActualCost; //已走的实际路程代价
        auto h = Distance(StartPosition, EndPosition); //将要走的路程代价
        auto p = Distance(PrevPosition, CurPosition); //上一步的局部最优代价
        auto h_weight = DynamicWeight();
        return g * h_weight + h *(1 -  h_weight) + p;
    }

    void PrintCur() const {
        cout << '(' << CurPosition.first << ", " << CurPosition.second << ")";
    }

    bool operator>(const State &Other) const {
        return Other.TotalCost() < TotalCost();
    }

    bool operator<(const State &Other) const {
        return TotalCost() < Other.TotalCost();
    }

    bool operator==(const State &Other) const {
        return CurPosition == Other.CurPosition;
    }
};

struct StateHash {
    size_t operator()(const State &s) const {
        size_t h1 = hash<int>{}(s.CurPosition.first);
        size_t h2 = hash<int>{}(s.CurPosition.second);
        return h1 ^ (h2 << 1);
    }
};

class AStarMatrix : public Matrix<char> {
public:
    AStarMatrix(int InRow, int InCol, const std::pair<int, int> &InStart, const std::pair<int, int> &InEnd,
                bool LoadDefault);

    void ShowMatrix() override;

    void FindWay();

private:
    std::pair<int, int> Start = {-1, -1}, End = {-1, -1};
    bool Initialized = false;

    void LoadDefaultMatrix();
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
        "S***###*****####*****###*****###",
        "#*#*#*#*###*#**#*###*#*#*###*#**",
        "#*#*#*#*#***#**#*#***#*#*#***#**",
        "#*#*#*#*#########*#####*#*#####*",
        "#*#*#*#*#*****#*#*****#*#*****#*",
        "#*#*#*#*####*#*#*####*#*#*####*#",
        "#*#*#*#*****#*#*#*****#*#*#*****",
        "#*#*#*####*#*#*#*#*####*#*#*####",
        "#*#*#*****#*#*#*#*#*****#*#*#***",
        "#*#*#####*#*#*#*#*#*#####*#*#*##",
        "#*#*****#*#*#*#*#*#*#*****#*#*#*",
        "#*#####*#*#*#*#*#*#*#*#*###*#*#*",
        "#*****#*#*#*#*#*#*#*#*#*#***#*#*",
        "####*#*#*#*#*#**#*##*#*#*#####*#",
        "#***#*#*#*#*#*#*#*#*#*#*#*****#*",
        "#*###*#*#*#*#*#*#*#*#*#*#*####*#",
        "#*#***#*#*#*#*#*#*#*#*#*#*****#*",
        "#*#*###*#*#*#*#*#*#*#*#*####*#*#",
        "#*#*#***#*#*#*#*#*#*#*#*****#*#*",
        "#*#*#*###*#*#*#*#*#*#*####*#*#*#",
        "#*#*#*#***#*#*#*#*#*#*****#*#*#*",
        "#*#*#*#*###*#*#*#*#*####*#*#*#*#",
        "#*#*#*#*#***#*#*#*#*****#*#*#*#*",
        "#*#*#*#*#*###*#*#*######*#*#*#*#",
        "#*#*#*#*#*#***#*#*****#*#*#*#*#*",
        "#*#*#*#*#*#*###*#######*#*#*#*#*",
        "#*#*#*#*#*#*#********#*#*#*#*#*#",
        "#*#*#*#*#*############*#*#*#*#*#",
        "#*#*#*#*#*#************#*#*#*#*#",
        "#*#*#*#*#*##############*#*#*#*#",
        "#*#*#*#*#****************#*#*#E#",
        "################################"
    };

    ResizeMatrix(32, 32);

    LogManagement::GetInstance()->Display("Init Default", "AStarMatrix");
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++) {
            SetAt(i, j, DefaultMatrix[i][j]);
            if (DefaultMatrix[i][j] == 'S') {
                if (Start != pair(-1, -1)) {
                    LogManagement::GetInstance()->Error("multiple starts detected, already abort", "AStarMatrix");
                    return;
                }
                Start = {i, j};
            }
            if (DefaultMatrix[i][j] == 'E') {
                if (End != pair(-1, -1)) {
                    LogManagement::GetInstance()->Error("multiple ends detected, already abort", "AStarMatrix");
                    return;
                }
                End = {i, j};
            }
        }

    if (Start == pair(-1, -1) || End == pair(-1, -1)) {
        LogManagement::GetInstance()->Error("start or end were initialized correctly, exit", "AStarMatrix");
        return;
    }

    Initialized = true;
}


inline void setColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void AStarMatrix::ShowMatrix() {
    if (!Initialized) {
        LogManagement::GetInstance()->Error("not initialized, will not show the Matrix", "AStarMatrix");
        return;
    }
    for (int i = 0; i < Size; i++) {
        const auto Element = *GetAt(i / Col, i % Col);
        if (Element == '*') {
            setColor(WHITE);
            cout << Element << " ";
            setColor(WHITE);
        } else if (Element == '#') {
            setColor(BLACK);
            cout << Element << " ";
            setColor(WHITE);
        } else if (Element == 'O') {
            setColor(GREEN);
            cout << Element << " ";
            setColor(WHITE);
        } else {
            setColor(GREEN);
            cout << Element << " ";
        }
        if ((i + 1) % Col == 0) std::cout << std::endl;
    }
}

inline void AStarMatrix::FindWay() {
    if (!Initialized) {
        LogManagement::GetInstance()->Error("not initialized, will not perform the way finding", "AStarMatrix");
        return;
    }
    const auto StartTime = high_resolution_clock::now();
    cout << "Finding Way ..." << endl;
    priority_queue<State, vector<State>, std::greater<> > StateQueue;
    unordered_set<State, StateHash> VisitedStates;
    const State StartState{Start, Start, Start, End, static_cast<float>(sqrt(Row * Row + Col * Col)), {Start}, 0};
    StateQueue.push(StartState);
    VisitedStates.insert(StartState);

    while (!StateQueue.empty()) {
        const auto CurState = StateQueue.top();
        StateQueue.pop();

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                auto NewState = CurState;
                NewState.ActualCost += 1;
                NewState.PrevPosition = CurState.CurPosition;
                NewState.CurPosition.first += i;
                NewState.CurPosition.second += j;
                NewState.VisitedPoint.push_back({NewState.CurPosition});
                if (NewState.CurPosition == End) {
                    const auto EndTime = high_resolution_clock::now();
                    const auto duration = duration_cast<milliseconds>(EndTime - StartTime);
                    cout << "Find Way! Using Time: " << duration.count() << "ms" << endl;
                    for (auto Point: NewState.VisitedPoint) {
                        if (Point == Start || Point == End) continue;

                        SetAt(Point.first, Point.second, 'O');
                    }
                    ShowMatrix();
                    return;
                }
                const auto NextElement = GetAt(NewState.CurPosition.first, NewState.CurPosition.second);
                if (NextElement && *NextElement != '#' && !VisitedStates.contains(NewState)) {
                    StateQueue.push(NewState);
                    VisitedStates.insert(NewState);
                }
            }
        }
    }

    cout << "Dead End :(" << endl;
}
