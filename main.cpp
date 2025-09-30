#include <iostream>
#include "Heap/Heap.h"
using namespace std;

int main() {
    cout << "=== 大根堆示例 ===" << endl;
    MaxHeap maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);
    maxHeap.push(1);
    maxHeap.push(5);

    cout << "大根堆元素: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    cout << "=== 小根堆示例 ===" << endl;
    MinHeap minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(4);
    minHeap.push(1);
    minHeap.push(5);

    cout << "小根堆元素: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    cout << "=== 模板堆示例 ===" << endl;
    Heap<int, greater<int>> customMaxHeap;  // 大根堆
    customMaxHeap.push(3);
    customMaxHeap.push(1);
    customMaxHeap.push(4);

    cout << "自定义大根堆: ";
    while (!customMaxHeap.empty()) {
        cout << customMaxHeap.top() << " ";
        customMaxHeap.pop();
    }
    cout << endl;

    return 0;
}