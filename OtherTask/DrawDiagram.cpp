#include "DrawDiagram.h"
#include "LogManagement.h"
#include <iostream>
#include <set>

void DrawDiagram::DrawColumnDiagram(const std::vector<int> &v, int startLevel) {
    int max = INT_MIN;
    int min = INT_MAX;
    for (const auto e: v) {
        if (max < e) max = e;
        if (min > e) min = e;
    }
    const int range = max - min;

    int level = max + 1;

    if (startLevel - max > range) {
        LogManagement::GetInstance()->Error("起始值过大，已自动取合适值", "BuildDiagram");
        startLevel = (max + min) / 2;
    }
    else if (min - startLevel > range) {
        LogManagement::GetInstance()->Error("起始值过小，已自动取合适值", "BuildDiagram");
        startLevel = (max + min) / 2;
    }
    else if (startLevel > max) {
        level = startLevel;
    }

    std::set<int> drawnData;
    while (level > startLevel) {
        for (int i=0;i<v.size();i++) {
            const auto e = v[i];
            int spareSpace = 0;
            if (e == level - 1 && !drawnData.contains(i)) {
                std::cout << " " << e;
                drawnData.insert(i);
                if (e >= 10) {
                    auto x = e;
                    while (x >= 10) {
                        spareSpace++;
                        x /= 10;
                    }
                }
            } else if (e >= level) std::cout << " |";
            else std::cout << "  ";
            for (int j = 2; j > spareSpace; j--) std::cout << "  ";
            for (int j = 0; j < spareSpace; j++) std::cout << " ";
        }
        level--;
        std::cout << std::endl;
    }
    for (int i = 0; i < v.size(); i++) {
        std::cout << "-" << i;
        int x = i;
        int spareSpace = 0;
        while (x >= 10) {
            spareSpace++;
            x /= 10;
        }
        for (int j = 2; j > spareSpace; j--) std::cout << "--";
        for (int j = 0; j < spareSpace; j++) std::cout << "-";
    }
    std::cout << "> " << startLevel << std::endl;

    level--;
    while (level >= min - 1) {
        for (int i=0;i<v.size();i++) {
            const auto e = v[i];
            int spareSpace = 0;
            if (e == level + 1 && !drawnData.contains(i)) {
                std::cout << " " << e;
                drawnData.insert(i);
                if (e >= 10) {
                    auto x = e;
                    while (x >= 10) {
                        spareSpace++;
                        x /= 10;
                    }
                }
            } else if (e <= level) {
                std::cout << " |";
            } else {
                std::cout << "  ";
            }
            for (int j = 2; j > spareSpace; j--) std::cout << "  ";
            for (int j = 0; j < spareSpace; j++) std::cout << " ";
        }

        level--;
        std::cout << std::endl;
    }
}
