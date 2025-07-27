#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    // 方式一：直接初始化（C++11 之后推荐）
    pair<string, int> p1 = {"Alice", 30};

    // 方式二：使用构造函数
    pair<string, int> p2("Bob", 25);

    // 方式三：使用 std::make_pair (C++98/03 常用，C++11 后可省略类型推导)
    auto p3 = make_pair("Charlie", 35); // 类型自动推导为 std::pair<const char*, int>
                                            // 注意：这里 "Charlie" 是 const char* 而非 std::string

    // 如果想让 make_pair 推导出 std::string：
    auto p4 = make_pair(string("David"), 40); // 或者 std::string s("David"); auto p4 = std::make_pair(s, 40);

    // 访问成员
    cout << "p1: " << p1.first << ", " << p1.second << endl;
    cout << "p2: " << p2.first << ", " << p2.second << endl;
    cout << "p3: " << p3.first << ", " << p3.second << endl;
    cout << "p4: " << p4.first << ", " << p4.second << endl;


    pair<int, int> p_a = {1, 5};
    pair<int, int> p_b = {1, 3};
    pair<int, int> p_c = {2, 0};

    cout << "(1,5) == (1,3)? " << boolalpha << (p_a == p_b) << endl; // false
    cout << "(1,5) > (1,3)?  " << boolalpha << (p_a > p_b) << endl;  // true (5 > 3)
    cout << "(1,5) < (2,0)?  " << boolalpha << (p_a < p_c) << endl;  // true (1 < 2)
}