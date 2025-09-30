#include <iostream>
#include "Heap/Heap.h"
using namespace std;

int main() {
    cout << "=== �����ʾ�� ===" << endl;
    MaxHeap maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);
    maxHeap.push(1);
    maxHeap.push(5);

    cout << "�����Ԫ��: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    cout << "=== С����ʾ�� ===" << endl;
    MinHeap minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(4);
    minHeap.push(1);
    minHeap.push(5);

    cout << "С����Ԫ��: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    cout << "=== ģ���ʾ�� ===" << endl;
    Heap<int, greater<int>> customMaxHeap;  // �����
    customMaxHeap.push(3);
    customMaxHeap.push(1);
    customMaxHeap.push(4);

    cout << "�Զ�������: ";
    while (!customMaxHeap.empty()) {
        cout << customMaxHeap.top() << " ";
        customMaxHeap.pop();
    }
    cout << endl;

    return 0;
}