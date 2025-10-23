#pragma once
#include "../GlobalUtils/Matrix.h"
#include "LogManagement.h"
#include <queue>
#include <unordered_set>
#include <functional>
#include <vector>
#include <windows.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include <future>
#include <set>
using namespace std;
using namespace std::chrono;

/**
 * @author tomasusan
 * @date 2025-09-29
 * @brief 寻路状态结点
 * @details 该结点存储寻路状态节点，同时为应用优先队列重写了比较和哈希函数。启发值由已走的实际代价、距离上一步的当前代价和距离终点的预期代价构成
 */
struct State {
    pair<int, int> CurPosition;
    pair<int, int> PrevPosition;
    pair<int, int> StartPosition;
    pair<int, int> EndPosition;
    float MaxDist = 0.f;

    vector<pair<int, int> > VisitedPoint;

    float ActualCost = .0f;

    /**
     * @author tomasusan
     * @date 2025-09-30
     * @brief 计算两点的欧几里得距离
     * @param s 起点
     * @param e 终点
     * @return 两点欧几里得距离
     */
    float Distance(const pair<int, int> &s, const pair<int, int> &e) const {
        return sqrt(pow(s.first - e.first, 2) + pow(s.second - e.second, 2));
    }

    /**
     * @author tomasusan
     * @date 2025-09-30
     * @brief 动态权重，防止最开始和靠近终点时固定权重失效
     * @return 获取当前启发值权重
     */
    float DynamicWeight() const {
        float totalDist = Distance(StartPosition, EndPosition);
        float progress = Distance(StartPosition, CurPosition) / totalDist;
        return 0.3f + 0.4f * progress; // 权重在0.3到0.7之间动态变化
    }

    /**
     * @author tomasusan
     * @date 2025-09-30
     * @brief 根据启发值和未来值计算代价
     * @return 排序依据代价值
     */
    float TotalCost() const {
        auto g = ActualCost; //已走的实际路程代价
        auto h = Distance(StartPosition, EndPosition); //将要走的路程代价
        auto p = Distance(PrevPosition, CurPosition); //上一步的局部最优代价
        auto h_weight = DynamicWeight();
        return g * h_weight + h * (1 - h_weight) + p;
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


/**
 * @author tomasusan
 * @date 2025-09-30
 * @brief 重写的状态节点辅助哈希结构
 */
struct StateHash {
    size_t operator()(const State &s) const {
        size_t h1 = hash<int>{}(s.CurPosition.first);
        size_t h2 = hash<int>{}(s.CurPosition.second);
        return h1 ^ (h2 << 1);
    }
};


/**
 * @author tomasusan
 * @date 2025-09-29
 * @brief A*算法实现类
 */
class AStarMatrix : public Matrix<char> {
public:
    AStarMatrix(int InRow, int InCol, const std::pair<int, int> &InStart, const std::pair<int, int> &InEnd,
                bool LoadDefault);

    void ShowMatrix() override;

    void FindWay();

private:
    std::vector<vector<pair<int, int>>> Paths;
    std::pair<int, int> Start = {-1, -1}, End = {-1, -1};
    vector<pair<int, int> > Starts;
    bool Initialized = false;

    void LoadDefaultMatrix();
    void ToFile();
};

/**
 * @author tomasusan
 * @date 2025-09-25
 * @brief 寻路实现类构造函数
 * @param InRow 创建的矩阵行数
 * @param InCol 创建的矩阵列数
 * @param InStart 设定起点
 * @param InEnd 设定终点
 * @param LoadDefault 加载默认矩阵迷宫，当为真时前序参数失效
 */
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

/**
 * @author tomasusan
 * @date 2025-09-25
 * @brief 加载硬编码默认矩阵迷宫，并进行合法化
 */
inline void AStarMatrix::LoadDefaultMatrix() {
    /** 硬编码32*32 迷宫矩阵*/
    const char *DefaultMatrix[] = {
        "S***************#########*******",
        "###*###########****####E#######*",
        "###*#*********#*##*####*###***#*",
        "###*#*#####*#*#*##*####***#*#*#*",
        "###*#*#***#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#***#*#*",
        "###*#*#*#*#*#*#*##*####*#####*#*",
        "###*#*#*#*#*#*#*##*####*#***#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##*####*#*#*#*#*",
        "###*#*#*#*#*#*#*##******#*#*###*",
        "###*#*#*#*#*#*#*#######*#*#*###*",
        "###*#*#S#*#*#*#*********#*#*###*",
        "###*#*###*#*#*#############*#*#*",
        "S******************************S"
    };

    ResizeMatrix(32, 32);

    LogManagement::GetInstance()->Display("Init Default", "AStarMatrix");
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++) {
            SetAt(i, j, DefaultMatrix[i][j]);
            if (DefaultMatrix[i][j] == 'S') {
                Starts.emplace_back(i, j);
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

inline void AStarMatrix::ToFile() {
    std::string filePath = R"(..\AStar\CacheFile.txt)";
    std::ofstream outfile(filePath);
    if (!outfile.is_open()) {
        LogManagement::GetInstance()->Error("Could not open file", "AStarMatrix");
    }

    for (int i=-1;i<=Row;i++) {
        for (int j=-1;j<=Col;j++) {
            const auto cur = GetAt(i, j);
            if (!cur) outfile << '#';
            else outfile << *cur;
        }
        outfile << std::endl;
    }

    outfile.close();

    filePath = R"(..\AStar\Path.txt)";
    outfile = std::ofstream(filePath);

    for (const auto& e:Paths) {
        for (auto path:e)
            outfile << path.first + 1 << " " << path.second + 1 << " ";

        outfile << endl;
    }

#ifdef _WIN32
    auto future = std::async(std::launch::async, []()->int {
        return std::system("python ..\\AStar\\Draw.py");
    });
    std::cout<<"生成迷宫图像中>>>"<<std::endl;
    int pyResult = future.get();
    if (pyResult != 0) {
        LogManagement::GetInstance()->Error("Python脚本执行错误", "AStarMatrix");
    }
    std::cout<<"迷宫图像生成完毕:"<<std::endl;
#endif


    outfile.close();
}

/**
 * @author tomasusan
 * @date 2025-09-30
 * @brief 设置控制台输出颜色
 * @param color 期望颜色，具体参照枚举值
 */
inline void setColor(const int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/**
 * @author tomasusan
 * @date 205-09-29
 * @brief 重写的展示类，添加输出样式
 */
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
            setColor(BLUE);
            cout << Element << " ";
            setColor(WHITE);
        }
        if ((i + 1) % Col == 0) std::cout << std::endl;
    }
}

/**
 * @author tomasusan
 * @date 2025-09-29
 * @brief 寻路具体实现
 * @details 单点寻路采用混合权重启发，权重根据寻路进度动态分配，多点寻路则通过提前合并进行剪枝
 */
inline void AStarMatrix::FindWay() {
    if (!Initialized) {
        LogManagement::GetInstance()->Error("not initialized, will not perform the way finding", "AStarMatrix");
        return;
    }
    const auto StartTime = high_resolution_clock::now();
    cout << "Finding Way ..." << endl;

    int StartIndex = 0;
    for (auto CurStart: Starts) {
        cout << "Now Process: " << StartIndex << endl;
        priority_queue<State, vector<State>, std::greater<> > StateQueue;
        unordered_set<State, StateHash> VisitedStates;
        const State StartState{CurStart, CurStart, CurStart, End, static_cast<float>(sqrt(Row * Row + Col * Col)), {CurStart}, 0};
        StateQueue.push(StartState);
        VisitedStates.insert(StartState);

        while (!StateQueue.empty()) {
            const auto CurState = StateQueue.top();
            StateQueue.pop();

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (abs(i * j) == 1) {
                        auto neighbour_1 = GetAt(CurState.CurPosition.first + i, CurState.CurPosition.second);
                        auto neighbour_2 = GetAt(CurState.CurPosition.first, CurState.CurPosition.second + j);
                        if (!(neighbour_1 && neighbour_2 && (*neighbour_1 != '#' || *neighbour_2 != '#'))) continue;
                    }
                    auto NewState = CurState;
                    NewState.ActualCost += 1;
                    NewState.PrevPosition = CurState.CurPosition;
                    NewState.CurPosition.first += i;
                    NewState.CurPosition.second += j;
                    NewState.VisitedPoint.push_back({NewState.CurPosition});
                    const auto NextElement = GetAt(NewState.CurPosition.first, NewState.CurPosition.second);
                    if (NewState.CurPosition == End) {
                        cout << "Find Way! Current Start Index: " << StartIndex << endl;
                            Paths.push_back(NewState.VisitedPoint);
                        for (auto Point: NewState.VisitedPoint) {
                            if (Point == CurStart || Point == End || *NextElement == 'S') continue;
                            SetAt(Point.first, Point.second, 'O');
                        }
                        goto LoopEnd;
                    } else if (NextElement && *NextElement == 'O') {
                        cout << "Find Internal Way! Current Start Index: " << StartIndex << endl;
                            Paths.push_back(NewState.VisitedPoint);
                        for (auto Point: NewState.VisitedPoint) {
                            if (Point == CurStart || Point == End || *NextElement == 'S') continue;
                            SetAt(Point.first, Point.second, 'O');
                        }
                        goto LoopEnd;
                    }
                    if (NextElement && *NextElement != '#' && !VisitedStates.contains(NewState)) {
                        StateQueue.push(NewState);
                        VisitedStates.insert(NewState);
                    }
                }
            }
        }
        LoopEnd:
        StartIndex++;
    }
    // ShowMatrix();
    const auto EndTime = high_resolution_clock::now();
    const auto duration = duration_cast<milliseconds>(EndTime - StartTime);
    cout << "Using Time: " << duration.count() << " ms" << endl;

    ToFile();
}
