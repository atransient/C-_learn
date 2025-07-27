#include <iostream>
#include <array> // C++11 引入的定长数组，就是类模板和非类型模板参数的典型应用

// 类模板：定长数组
template <typename T, std::size_t N> // N 是一个非类型模板参数
class StaticArray {
public:
    T arr[N]; // 数组大小由 N 决定

    void fill(const T& val) {
        for (std::size_t i = 0; i < N; ++i) {
            arr[i] = val;
        }
    }

    T& operator[](std::size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }
};

int main() {
    // 创建一个包含 5 个 int 的 StaticArray
    StaticArray<int, 5> intArray;
    intArray.fill(10);
    std::cout << "intArray[0]: " << intArray[0] << std::endl; // 输出: 10
    std::cout << "intArray[4]: " << intArray[4] << std::endl; // 输出: 10

    // 创建一个包含 3 个 double 的 StaticArray
    StaticArray<double, 3> doubleArray;
    doubleArray.fill(3.14);
    std::cout << "doubleArray[1]: " << doubleArray[1] << std::endl; // 输出: 3.14

    return 0;
}