#include <iostream>

using namespace std;

template <typename T>
class Wrapper { // 这是一个模板类
public:
    T data;
    Wrapper(T val) : data(val) {}

    // 这是一个成员函数模板
    template <typename U>
    bool is_greater_than(U other_value) const {
        return data > other_value;
    }
};


int main()
{
  Wrapper<int> int_wrapper(10);
  int_wrapper.is_greater_than(5);      // 调用 1
  int_wrapper.is_greater_than(10.5);   // 调用 2
  
  Wrapper<int> int_wrapper0(10);
  int_wrapper0.is_greater_than(float(30.3));      // 调用 1
  
  Wrapper<double> int_wrapper1(10.0);
  int_wrapper1.is_greater_than(5);      // 调用 1
  int_wrapper1.is_greater_than(10.5);   // 调用 2

  cout << typeid(int_wrapper).name() << endl;
  cout << typeid(int_wrapper0).name() << endl;
  cout << typeid(int_wrapper1).name() << endl;
}