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
    std::cout << "是否进行排序性能测试?（Y/N）" << std::endl;
    std::cin >> test;
    if (test != 'Y' && test != 'y') return 0;

    std::cout << "输入测试数据规模（当数据规模到达500,000时，执行时间可能长达数十分钟，请酌情设计规模）" << std::endl;
    int total_number;
    std::cin >> total_number;
    std::cout << "等待脚本生成数据..." << std::endl;
    auto future = std::async(std::launch::async, runPythonScript, total_number);
    const int pythonResult = future.get();  // 阻塞直到 Python 完成
    if (pythonResult != 0) {
        std::cerr << "Python 脚本执行失败，退出码：" << pythonResult << std::endl;
        return -1;
    }
    std::cout << "Python 随机数文件生成完成，开始排序..." << std::endl;
    Sort::SortTest();
    return 0;
}
