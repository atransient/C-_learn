#include <iostream>
#include <cstring> // For strlen

// 通用函数模板
template <typename T>
void print_value(T value) {
    std::cout << "通用版本: " << value << std::endl;
}

// char* 类型的特化版本
template <> // 注意这里 <> 是空的，因为所有类型参数都已特化
void print_value<const char*>(const char* value) {
    std::cout << "char* 特化版本 (长度为 " << strlen(value) << "): " << value << std::endl;
}

template <> // 注意这里 <> 是空的，因为所有类型参数都已特化
void print_value<char*>(char* value) {
    std::cout << "char* 特化版本  非const (长度为 " << strlen(value) << "): " << value << std::endl;
}

int main() {
    print_value(123);           // 调用通用版本
    print_value(3.14);          // 调用通用版本
    print_value("Hello Template"); // 调用 char* 特化版本

    std::string s = "C++";
    print_value(s); // 调用通用版本 (std::string 类型)

    char* char_set = "C++";
    print_value(char_set); // 调用通用版本 (std::string 类型)

    return 0;
}