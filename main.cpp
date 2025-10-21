#include <iostream>
#include <future>
#include <sstream>

#include "Sort/Sort.h"

int runPythonScript(int totalNumber) {
    std::ostringstream cmd;
#ifdef _WIN32
    cmd << "python ..\\Sort\\generate_random.py " << totalNumber;   // Windows
#else
    cmd << "python3 ..\\Sort\\generate_random.py " << totalNumber;  // Linux / macOS
#endif
    return std::system(cmd.str().c_str());
}

int main() {
    std::vector<int> arr = {4,1,5,6,1,5,7,12,5124,1241,-1,2342,11411,1212315,121,123124531,1312};
    Sort::sort(arr, ESortType::QuickSort);
    for (const int & it : arr) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    char test;
    std::cout << "�Ƿ�����������ܲ���?��Y/N��" << std::endl;
    std::cin >> test;
    if (test != 'Y' && test != 'y') return 0;

    std::cout << "����������ݹ�ģ�������ݹ�ģ����500,000ʱ��ִ��ʱ����ܳ�����ʮ���ӣ���������ƹ�ģ��" << std::endl;
    int total_number;
    std::cin >> total_number;
    std::cout << "�ȴ��ű���������..." << std::endl;
    auto future = std::async(std::launch::async, runPythonScript, total_number);
    const int pythonResult = future.get();  // ����ֱ�� Python ���
    if (pythonResult != 0) {
        std::cerr << "Python �ű�ִ��ʧ�ܣ��˳��룺" << pythonResult << std::endl;
        return -1;
    }
    std::cout << "Python ������ļ�������ɣ���ʼ����..." << std::endl;
    Sort::SortTest();
    return 0;
}
