#include <iostream>
#include <string>

// --- 1. 模板类的声明 ---
template <typename T> // 模板参数声明
class MyContainer {
public:
    T data;

    // 构造函数：可以在类内直接实现，也可以在类外实现
    MyContainer(T val) : data(val) {
        std::cout << "MyContainer<" << typeid(T).name() << "> created with data: " << data << std::endl;
    }

    // 成员函数的声明 (在类内部)
    void print_data() const; // 声明函数，但不在类内实现

    template <typename U>
    void process_data(U input) const;
};

// --- 2. 模板类成员函数在类外的实现 ---

// 关键语法：
// template <typename T>        // 1. 再次声明这是一个模板
// void MyContainer<T>::print_data() const { // 2. 指定所属的模板类及其模板参数
//     std::cout << "Data from outside implementation: " << data << std::endl;
// }

template <typename T>
void MyContainer<T>::print_data() const {
    std::cout << "Data from outside implementation for MyContainer<" << typeid(T).name() << ">: " << data << std::endl;
}

template <typename T>         // 这一层对应外层类模板 MyContainer<T> 的参数
template <typename U>         // 这一层对应内层成员函数模板 process_data<U> 的参数
void MyContainer<T>::process_data(U input) const {
    std::cout << "Inside MyContainer<" << typeid(T).name() << ">'s process_data<" << typeid(U).name() << ">:" << std::endl;
    std::cout << "  Container value: " << data << std::endl;
    std::cout << "  Input data: " << input << std::endl;
    std::cout << "  (Result of operation, e.g., value + input): " << data + input << std::endl;
}

// -----------------------------------------------------------
// 另一个例子：如果 MyContainer 有多个模板参数
template <typename T, typename U>
class PairContainer {
public:
    T first;
    U second;
    PairContainer(T f, U s) : first(f), second(s) {}
    void print_pair() const;
};

template <typename T, typename U> // 再次声明所有模板参数
void PairContainer<T, U>::print_pair() const { // 指定所属的模板类及其所有模板参数
    std::cout << "Pair: (" << first << ", " << second << ")" << std::endl;
}
// -----------------------------------------------------------

int main() {
    // 实例化 MyContainer<int>
    MyContainer<int> int_container(100);
    int_container.print_data(); // 调用在类外实现的函数
    int_container.process_data(300.65);
    std::cout << "---" << std::endl;

    // 实例化 MyContainer<std::string>
    MyContainer<std::string> string_container("Hello Templates!");
    string_container.print_data(); // 调用在类外实现的函数
    string_container.process_data("   hello world");
    std::cout << "---" << std::endl;

    // 实例化 PairContainer<double, char>
    PairContainer<double, char> my_pair(3.14, 'A');
    my_pair.print_pair();

    return 0;
}