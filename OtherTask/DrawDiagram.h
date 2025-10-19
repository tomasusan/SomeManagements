#pragma once
#include <vector>


class DrawDiagram {
public:
    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 将一定规模内的数据转化未直方图输出，当数值过大或过小时将失效
     * @param v 要展示的数组
     * @param startLevel 归零起评等级，过大或过低时将自动分配
     * @param step 纵向方向梯度
     */
    static void DrawColumnDiagram(const std::vector<int> & v, int startLevel = 0);

};
