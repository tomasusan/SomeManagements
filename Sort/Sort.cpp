#include "Sort.h"

#include <fstream>
#include <string>
#include <chrono>
#include <filesystem>
#include <iostream>

#include "LogManagement.h"

void Sort::sort(std::vector<int> &v, const ESortType type) {
    switch (type) {
        case BubbleSort:
            bubbleSort(v);
            break;
        case SelectionSort:
            selectionSort(v);
            break;
        case InsertionSort:
            insertionSort(v);
            break;
        case QuickSort:
            quickSort(v);
            break;
        case MergeSort:
            mergeSort(v);
            break;
        case ShellSort:
            shellSort(v);
            break;
        case HeapSort:
            heapSort(v);
            break;
        default:
            bubbleSort(v);
            break;
    }
}

void Sort::bubbleSort(std::vector<int> &v) {
    for (auto i = v.end(); i != v.begin(); --i) {
        for (auto j = v.begin(); j + 1 != i; ++j) {
            if (*j > *(j + 1)) {
                std::iter_swap(j, j + 1);
            }
        }
    }
}

void Sort::selectionSort(std::vector<int> &v) {
    for (auto i = v.begin(); i != v.end() - 1; ++i) {
        auto minPos = i; // 假设当前位置最小
        for (auto j = i + 1; j != v.end(); ++j) {
            if (*j < *minPos) {
                minPos = j;
            }
        }
        if (minPos != i) {
            std::iter_swap(i, minPos); // 交换最小值到当前位置
        }
    }
}

void Sort::insertionSort(std::vector<int> &v) {
    for (auto i = v.begin() + 1; i != v.end(); ++i) {
        const auto key = *i; // 当前要插入的元素
        auto j = i; // 从当前位置往前查找插入点

        // 向左移动比 key 大的元素
        while (j > v.begin() && *(j - 1) > key) {
            *j = *(j - 1);
            --j;
        }

        *j = key; // 插入 key
    }
}

void Sort::quickSort(std::vector<int> &v) {
    if (!v.empty()) quickSortImp(v, 0, static_cast<int>(v.size()) - 1);
}

void Sort::mergeSort(std::vector<int> &v) {
    if (!v.empty()) mergeSortImp(v, 0, static_cast<int>(v.size()) - 1);
}

void Sort::shellSort(std::vector<int> &v) {
    const int n = static_cast<int>(v.size());
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            const int temp = v[i];
            int j = i;
            while (j >= gap && v[j - gap] > temp) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = temp;
        }
    }
}

void Sort::heapSort(std::vector<int> &v) {
    const int n = static_cast<int>(v.size());

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(v, n, i);

    for (int i = n - 1; i > 0; --i) {
        std::swap(v[0], v[i]); // 将当前最大值移到末尾
        heapify(v, i, 0); // 重新调整堆（堆大小减1）
    }
}

void Sort::SortTest() {
    std::vector<int> numbers;
    const auto filename = R"(..\Sort\random_numbers.txt)";
    std::ifstream file(filename); // 打开文件（默认以文本模式读取）

    if (!file.is_open()) {
        LogManagement::GetInstance()->Error("找不到文件, 当前工作目录: " + std::filesystem::current_path().string(), "SortTest");
        return;
    }

    int value;
    while (file >> value) {
        // 逐个读取整数
        numbers.push_back(value);
    }

    file.close(); // 关闭文件

    std::cout << "开始排序性能测试..." << std::endl;
    std::cout << "数据规模：" << numbers.size() << std::endl;
    std::cout << "测试数据地址：" << filename << std::endl;

    for (int i = 0; i <= 6; i++) {
        const auto curType = static_cast<ESortType>(i);
        std::vector<int> tempArr;
        for (const auto e: numbers) tempArr.push_back(e);
        auto start = std::chrono::high_resolution_clock::now();
        switch (curType) {
            case BubbleSort:
                std::cout << "执行冒泡排序..." << std::endl;
                bubbleSort(tempArr);
                break;
            case SelectionSort:
                std::cout << "执行选择排序..." << std::endl;
                selectionSort(tempArr);
                break;
            case InsertionSort:
                std::cout << "执行插入排序..." << std::endl;
                insertionSort(tempArr);
                break;
            case QuickSort:
                std::cout << "执行快速排序..." << std::endl;
                quickSort(tempArr);
                break;
            case MergeSort:
                std::cout << "执行归并排序..." << std::endl;
                mergeSort(tempArr);
                break;
            case ShellSort:
                std::cout << "执行希尔排序..." << std::endl;
                shellSort(tempArr);
                break;
            case HeapSort:
                std::cout << "执行堆排序..." << std::endl;
                heapSort(tempArr);
                break;
            default:
                bubbleSort(tempArr);
                break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "执行耗时: " << duration.count() << " 毫秒" << std::endl;
    }
    const auto start = std::chrono::high_resolution_clock::now();
    std::cout << "执行STL默认排序..." << std::endl;
    std::sort(numbers.begin(), numbers.end());
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "执行耗时: " << duration.count() << " 毫秒" << std::endl;
}

void Sort::quickSortImp(std::vector<int> &v, int left, int right) {
    if (left >= right) return;

    int i = left;
    int j = right;
    const int pivot = v[(left + right) / 2]; // 选取中间元素为基准

    while (i <= j) {
        while (v[i] < pivot) ++i;
        while (v[j] > pivot) --j;

        if (i <= j) {
            std::swap(v[i], v[j]);
            ++i;
            --j;
        }
    }

    // 递归处理左右子区间
    if (left < j) quickSortImp(v, left, j);
    if (i < right) quickSortImp(v, i, right);
}

void Sort::mergeSortImp(std::vector<int> &v, const int left, const int right) {
    if (left >= right) return;
    const int mid = (left + right) / 2;
    mergeSortImp(v, left, mid);
    mergeSortImp(v, mid + 1, right);
    merge(v, left, mid, right);
}

void Sort::merge(std::vector<int> &v, const int left, const int mid, const int right) {
    std::vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (v[i] < v[j]) temp.push_back(v[i++]);
        else temp.push_back(v[j++]);
    }

    while (i <= mid) temp.push_back(v[i++]);
    while (j <= right) temp.push_back(v[j++]);

    for (int k = 0; k < temp.size(); k++) v[left + k] = temp[k];
}

void Sort::heapify(std::vector<int> &v, const int n, const int i) {
    int largest = i; // 当前节点作为最大值
    const int left = 2 * i + 1; // 左子节点
    const int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根大
    if (left < n && v[left] > v[largest])
        largest = left;

    // 如果右子节点比当前最大值还大
    if (right < n && v[right] > v[largest])
        largest = right;

    // 如果最大值不是根，则交换并递归调整子树
    if (largest != i) {
        std::swap(v[i], v[largest]);
        heapify(v, n, largest);
    }
}
