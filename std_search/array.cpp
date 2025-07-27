#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>


using namespace std;

int main()
{
    array<int, 5> arr1;
    array<int, 5> arr2 = {1,2,4};
    array<double, 4> grades = {85.5, 92.0, 78.5, 95.0};
    array<char, 3> letters = {'A', 'B', 'C'};
    cout << "--- 初始数组内容 arr1---" << endl;
    for (size_t i = 0; i < arr1.size(); ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    cout << "--- {} initialize arr2---" << endl;
    for (size_t i = 0; i < arr2.size(); ++i) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    cout << "---- letters ----" << endl;
    for (size_t i = 0; i < letters.size(); ++i) {
        cout << letters[i] << " ";
    }
    cout << endl;
    cout << "---- Grades ----" << endl;
    for (size_t i = 0; i < grades.size(); ++i) {
        cout << grades[i] << " ";
    }
    cout << endl;
    double* data_ptr = grades.data();
    cout << "---- data_ptr ----" << endl;
    for (size_t i = 0; i < grades.size(); ++i) {
        cout << data_ptr[i] << " ";
    }
    cout << endl;

    // 2. 访问元素
    cout << "\n--- 元素访问 ---" << std::endl;
    cout << "First grade (operator[]): " << grades[0] << endl;
    cout << "Second grade (at()): " << grades.at(1) << endl;

    // // 边界检查示例：使用 at() 访问越界会抛出异常
    // try {
    //     cout << "Attempting to access out-of-bounds index (at()): ";
    //     cout << grades.at(10) << endl; // 会抛出 std::out_of_range
    // } catch (const std::out_of_range& e) {
    //     cerr << "Caught exception: " << e.what() << endl;
    // }

    // front() 和 back() 访问首尾元素
    cout << "Front element: " << grades.front() << endl;
    cout << "Back element: " << grades.back() << endl;

    

    // 5. 填充数组 (fill())
    std::array<int, 3> scores;
    scores.fill(100); // 将所有元素设置为 100
    scores.fill(20);
    std::cout << "Scores after fill(100): ";
    for (int s : scores) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}