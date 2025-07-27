#include <iostream>
#include <string>

// 函数模板：用于比较两个值并返回较大的那个
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    // 编译器会推断 T 为 int，生成 maximum(int, int)
    int max_int = maximum(10, 20);
    std::cout << "Max int: " << max_int << std::endl; // 输出: 20

    // 编译器会推断 T 为 double，生成 maximum(double, double)
    double max_double = maximum(3.14, 2.71);
    std::cout << "Max double: " << max_double << std::endl; // 输出: 3.14

    // 编译器会推断 T 为 std::string，生成 maximum(std::string, std::string)
    std::string s1 = "hello";
    std::string s2 = "world";
    std::string max_string = maximum(s1, s2);
    std::cout << "Max string: " << max_string << std::endl; // 输出: world (基于字典序)

    return 0;
}