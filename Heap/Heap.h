#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    // �ϸ�����
    void heapifyUp(int index) {
        if (index == 0) return;

        int parent = (index - 1) / 2;
        if (heap[parent] < heap[index]) {
            swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }

    // �³�����
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // ����Ԫ��
    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // ɾ���Ѷ�Ԫ��
    void pop() {
        if (heap.empty()) return;

        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }

    // ��ȡ�Ѷ�Ԫ��
    int top() {
        if (heap.empty()) return -1;
        return heap[0];
    }

    // ���Ƿ�Ϊ��
    bool empty() {
        return heap.empty();
    }

    // �Ѵ�С
    int size() {
        return heap.size();
    }

    // ��ӡ��
    void print() {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

class MinHeap {
private:
    vector<int> heap;

    // �ϸ�����
    void heapifyUp(int index) {
        if (index == 0) return;

        int parent = (index - 1) / 2;
        if (heap[parent] > heap[index]) {
            swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }

    // �³�����
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // ����Ԫ��
    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // ɾ���Ѷ�Ԫ��
    void pop() {
        if (heap.empty()) return;

        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }

    // ��ȡ�Ѷ�Ԫ��
    int top() {
        if (heap.empty()) return -1;
        return heap[0];
    }

    // ���Ƿ�Ϊ��
    bool empty() {
        return heap.empty();
    }

    // �Ѵ�С
    int size() {
        return heap.size();
    }

    // ��ӡ��
    void print() {
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

#include <functional>

template<typename T, typename Compare = less<T>>
class Heap {
private:
    vector<T> heap;
    Compare comp;

    void heapifyUp(int index) {
        if (index == 0) return;

        int parent = (index - 1) / 2;
        if (comp(heap[parent], heap[index])) {
            swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int target = index;

        if (left < heap.size() && comp(heap[target], heap[left])) {
            target = left;
        }
        if (right < heap.size() && comp(heap[target], heap[right])) {
            target = right;
        }

        if (target != index) {
            swap(heap[index], heap[target]);
            heapifyDown(target);
        }
    }

public:
    Heap() = default;

    explicit Heap(const Compare& compare) : comp(compare) {}

    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;

        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }

    T top() const {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

    int size() const {
        return heap.size();
    }
};