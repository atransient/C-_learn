// #include <iostream>
// #include <string>

// // 1. 基本情况 (Base Case): 处理最后一个或零个参数
// // 当参数包为空时，这个重载函数会被调用，用于终止递归。
// void print() {
//     std::cout << " (end)" << std::endl; // 打印一个结束标记
// }

// // 2. 递归情况 (Recursive Case): 处理一个参数和剩余的参数包
// template <typename T, typename... Args>
// void print(T head, Args... tail) {
//     std::cout << head; // 打印当前参数 (head)

//     // 如果还有剩余参数，则打印分隔符
//     if constexpr (sizeof...(tail) > 0) { // C++17 的 if constexpr，编译时判断
//         std::cout << ", ";
//     }
//     print(tail...); // 递归调用自身，处理剩余的参数包 (tail)
// }

// int main() {
//     std::cout << "--- 打印不同类型的参数 ---" << std::endl;
//     print(10);                             // T=int, Args=空
//     print(10, 3.14);                       // T=int, Args={double}
//     print("hello", 20, true, 'X');         // T=const char*, Args={int, bool, char}
//     print(std::string("World"), 42.5f);    // T=std::string, Args={float}

//     std::cout << "\n--- 单独调用基本情况 ---" << std::endl;
//     print(); // 调用基本情况

//     return 0;
// }


#include <iostream>
#include <string>

// 1. 基本情况：空 Tuple
template <typename...>
class Tuple {};

// 2. 递归情况：带一个头类型和剩余参数包的 Tuple
template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : public Tuple<Tail...> { // 继承自剩余参数的 Tuple
public:
    Head head_value; // 当前 Tuple 的头元素

    // 构造函数
    Tuple(Head h, Tail... t) : head_value(h), Tuple<Tail...>(t...) {
        // ...
    }

    // 辅助函数：打印 Tuple 内容
    void print() const {
        // std::cout << head_value << " ";
        // 递归调用基类的 print (如果基类有的话，这里只是为了演示)
        // 实际的 Tuple 访问通常通过 get<N>() 实现
        // static_cast<const Tuple<Tail...>&>(*this).print();
        print_impl();
        std::cout << std::endl;
    }
    void print_impl() const {
        std::cout << head_value << " ";
        static_cast<const Tuple<Tail...>&>(*this).print_impl();
        // Base case for print_impl: do nothing when Tail is empty
    }
};

// 为 print_impl 的基类情况添加特化
template <>
class Tuple<> {
public:
    void print() const {};
    void print_impl() const {};
};
// void Tuple<>::print_impl() const {
//     // Do nothing (base case for printing recursion)
// }


int main() {
    std::cout << "--- 变参类模板 Tuple ---" << std::endl;

    // 实例化一个 Tuple，包含 int, double, std::string
    Tuple<int, double, std::string> my_tuple(10, 3.14, "hello");

    // 访问元素 (这是一个简化的 Tuple 访问方式，实际 std::tuple 使用 get<N> )
    std::cout << "Tuple content (head): " << my_tuple.head_value << std::endl; // 输出 10

    // 访问第二个元素 (通过继承，有点复杂，实际 Tuple 通常使用索引访问)
    std::cout << "Tuple content (next head): "
              << static_cast<Tuple<double, std::string>&>(my_tuple).head_value << std::endl; // 输出 3.14

    // 使用我们简化的 print 函数
    std::cout << "Full Tuple print: ";
    my_tuple.print(); // 理论上应该打印所有元素，但我们这里实现简陋
    // my_tuple.print_impl();
    // std::cout << std::endl;

    return 0;
}


// #include <iostream>

// // 基本情况: 用于终止递归，或者处理零个参数的情况
// long long sum_all() {
//     return 0;
// }

// // 递归情况: 计算所有参数的和
// template <typename T, typename... Args>
// long long sum_all(T head, Args... tail) {
//     return static_cast<long long>(head) + sum_all(tail...);
// }

// // C++17 折叠表达式 (Fold Expressions) 简化版本
// // 这是最简洁和推荐的方式，C++17 及以后版本可用
// template <typename... Args>
// long long sum_all_fold(Args... args) {
//     // ((args + ...) + 0) 表示右折叠：(arg1 + (arg2 + (... + (argN + 0))))
//     // 或者 (0 + (... + args)) 表示左折叠：(((0 + arg1) + arg2) + ...) + argN)
//     return (args + ... + 0); // 对所有参数执行加法运算，默认初始值为0 (如果包为空)
// }

// int main() {
//     std::cout << "--- 递归求和 ---" << std::endl;
//     std::cout << "Sum (1, 2, 3): " << sum_all(1, 2, 3) << std::endl;
//     std::cout << "Sum (10.5, 20, 30L): " << sum_all(10.5, 20, 30L) << std::endl;
//     std::cout << "Sum (): " << sum_all() << std::endl;
//     std::cout << std::endl;

//     std::cout << "--- 折叠表达式求和 (C++17+) ---" << std::endl;
//     std::cout << "Sum (1, 2, 3, 4): " << sum_all_fold(1, 2, 3, 4) << std::endl;
//     std::cout << "Sum (1.1, 2.2f, 3): " << sum_all_fold(1.1, 2.2f, 3) << std::endl;
//     std::cout << "Sum (): " << sum_all_fold() << std::endl; // 对于空包，折叠表达式有默认行为
//                                                             // 对于二元操作符 (+)，空包通常计算为0 (对于 +, |等)

//     return 0;
// }