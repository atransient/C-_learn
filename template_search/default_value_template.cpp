#include <iostream>
#include <vector>
#include <string>

// 定义一个简单的容器类模板
// T 默认是 int
// Allocator 默认是 std::allocator<T>
template <typename T = int, typename Allocator = std::allocator<T>>
class MyContainer {
private:
    std::vector<T, Allocator> data;

public:
    MyContainer() {
        std::cout << "MyContainer 使用类型: " << typeid(T).name()
                  << " 和分配器: " << typeid(Allocator).name() << std::endl;
    }

    void add(const T& value) {
        data.push_back(value);
    }

    void print() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};


// 类模板：定长数组，N 默认值为 10
template <typename T, std::size_t N = 10>
class MyFixedArray {
public:
    T arr[N]; // 数组大小由非类型模板参数 N 决定

    MyFixedArray() {
        std::cout << "创建 MyFixedArray，大小为: " << N << std::endl;
    }

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
    // 1. 使用所有默认模板参数
    // T 会是 int，Allocator 会是 std::allocator<int>
    MyContainer<> c1;
    c1.add(10);
    c1.add(20);
    std::cout << "c1 data: ";
    c1.print(); // 输出: 10 20

    std::cout << std::endl;

    // 2. 显式指定第一个模板参数 (T)，第二个使用默认值
    // T 会是 double，Allocator 会是 std::allocator<double>
    MyContainer<double> c2;
    c2.add(3.14);
    c2.add(6.28);
    std::cout << "c2 data: ";
    c2.print(); // 输出: 3.14 6.28

    std::cout << std::endl;

    // 3. 显式指定所有模板参数
    // T 会是 std::string，Allocator 会是 std::allocator<std::string>
    MyContainer<std::string, std::allocator<std::string>> c3;
    c3.add("Hello");
    c3.add("World");
    std::cout << "c3 data: ";
    c3.print(); // 输出: Hello World

    std::cout << std::endl;
    // 4. 使用默认大小 (N = 10)
    MyFixedArray<int> arr1; // 相当于 MyFixedArray<int, 10>
    arr1.fill(5);
    std::cout << "arr1[0]: " << arr1[0] << std::endl; // 输出: 5

    std::cout << std::endl;

    // 5. 显式指定大小 (N = 5)
    MyFixedArray<double, 5> arr2;
    arr2.fill(3.14);
    std::cout << "arr2[2]: " << arr2[2] << std::endl; // 输出: 3.14

    return 0;
}