#pragma once
#include "Singleton.h"
#include <vector>

/**
 * @author tomasusan
 * @date  2025-10-19
 * @brief 指定排序模型
 */
enum class ESortType {
    BubbleSort,
    SelectionSort,
    InsertionSort,
    QuickSort,
    MergeSort,
    ShellSort,
    HeapSort,
};

/**
 * @author tomasusan
 * @date 2025-10-19
 * @brief 排序类
 */
class Sort {
public:
    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 排序总封装接口，默认冒泡排序
     * @param v 待排序数组
     * @param type 排序模型，默认冒泡
     */
    static void sort(std::vector<int> &v, ESortType type = BubbleSort);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 冒泡排序
     * @param v 待排序数组
     */
    static void bubbleSort(std::vector<int> &v);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 选择排序
     * @param v 待排序数组
     */
    static void selectionSort(std::vector<int> &v);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 插入排序
     * @param v 待排序数组
     */
    static void insertionSort(std::vector<int> &v);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 快速排序
     * @param v 待排序数组
     */
    static void quickSort(std::vector<int> &v);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 归并排序
     * @param v 待排序数组
     */
    static void mergeSort(std::vector<int> &v);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 希尔排序
     * @param v 待排序数组
     */
    static void shellSort(std::vector<int> &v);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 堆排序
     * @param v 待排序数组
     */
    static void heapSort(std::vector<int> &v);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 各类排序性能测试，默认规模50000
     */
    static void SortTest();

private:
    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 快速排序具体实现，递归调用
     * @param v 数组
     * @param left 左边界
     * @param right 右
     */
    static void quickSortImp(std::vector<int> &v, int left, int right);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 归并排序具体实现，递归调用
     * @param v 数组
     * @param left 左边界
     * @param right 右边界
     */
    static void mergeSortImp(std::vector<int> &v, int left, int right);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 合并两个子序列
     * @param v 数组
     * @param left 左边界
     * @param mid 中界
     * @param right 右边界
     */
    static void merge(std::vector<int> &v, int left, int mid, int right);

    /**
     * @author tomasusan
     * @date 2025-10-19
     * @brief 整理生成堆
     * @param v 数组
     * @param n 树节点数量
     * @param i 当前结点编号
     */
    static void heapify(std::vector<int> &v, int n, int i);
};
