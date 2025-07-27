#include <iostream>
#include <string>

// 类模板：一个简单的 Pair 类，可以存储两个不同或相同类型的值
template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair(T1 f, T2 s) : first(f), second(s) {}

    void print() const {
        std::cout << "(" << first << ", " << second << ")" << std::endl;
    }
};

int main() {
    // 创建一个 Pair<int, double> 实例
    Pair<int, double> p1(10, 20.5);
    std::cout << "Pair 1: ";
    p1.print(); // 输出: (10, 20.5)

    // 创建一个 Pair<std::string, int> 实例
    Pair<std::string, int> p2("Age", 30);
    std::cout << "Pair 2: ";
    p2.print(); // 输出: (Age, 30)

    // 创建一个 Pair<char, char> 实例
    Pair<char, char> p3('A', 'B');
    std::cout << "Pair 3: ";
    p3.print(); // 输出: (A, B)

    return 0;
}