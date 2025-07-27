#include <iostream>

using namespace std;

class MyClass {
    public:
        string name;
        MyClass() : name("default init") { // 使用移动构造函数优化
            cout << "MyClass(" << name << ") constructed" << endl;
        }
        MyClass(int id) : name(to_string(id) + "th val") { // 使用移动构造函数优化
            cout << "MyClass(" << name << ") constructed" << endl;
        }
        MyClass(string n) : name(move(n)) { // 使用移动构造函数优化
            cout << "MyClass(" << name << ") constructed" << endl;
        }
        MyClass(const MyClass& other) : name(other.name) {
            cout << "MyClass(" << name << ") copied" << endl;
        }
        MyClass(MyClass&& other) noexcept : name(move(other.name)) {
            cout << "MyClass(" << name << ") moved from " << other.name << endl;
            other.name = "[MOVED]"; // 标记源对象已被移动
        }
        ~MyClass() {
            cout << "MyClass(" << name << ") destructed" << endl;
        }
    };


int main()
{
    allocator<int> int_allocator;
    int* data = int_allocator.allocate(5);
    cout << "Allocated memory for 5 ints at: " << data << endl;

    // 2. 在分配的内存上构造对象
    for (int i = 0; i < 5; ++i) {
        cout << "data[" << i << "] = " << data[i] << endl;
        int_allocator.construct(&data[i], i * 10); // 在 data[i] 处构造 int，值为 i*10
        cout << "Constructed data[" << i << "] = " << data[i] << endl;
    }

    // 3. 使用数据 (像操作普通数组一样)
    cout << "Accessing constructed data: " << data[2] << endl;

    // 4. 销毁对象 (调用析构函数)
    // 必须先析构对象，再释放内存
    for (int i = 0; i < 5; ++i) {
        int_allocator.destroy(&data[i]); // 销毁 data[i] 处的 int 对象
        cout << "Destroyed data[" << i << "]" << endl;
    }

    // 5. 释放内存
    int_allocator.deallocate(data, 5);
    cout << "Deallocated memory." << endl;



    allocator<MyClass> MyClass_allocator;
    MyClass* MyClass_data = MyClass_allocator.allocate(5);
    cout << "Allocated memory for 5 ints at: " << MyClass_data << endl;

    // 2. 在分配的内存上构造对象
    for (int i = 0; i < 5; ++i) {
        cout << "MyClass_data[" << i << "] = " << MyClass_data[i].name << endl;
        MyClass_allocator.construct(&MyClass_data[i], i); // 在 data[i] 处构造 int，值为 i*10
        cout << "Constructed MyClass_data[" << i << "] = " << MyClass_data[i].name << endl;
    }

    // 3. 使用数据 (像操作普通数组一样)
    cout << "Accessing constructed data: " << MyClass_data[2].name << endl;

    // 4. 销毁对象 (调用析构函数)
    // 必须先析构对象，再释放内存
    for (int i = 0; i < 5; ++i) {
        MyClass_allocator.destroy(&MyClass_data[i]); // 销毁 data[i] 处的 int 对象
        cout << "Destroyed data[" << i << "]" << endl;
        cout << "MyClass_data[" << i << "] = " << MyClass_data[i].name << endl;
    }

    // 5. 释放内存
    MyClass_allocator.deallocate(MyClass_data, 5);
    cout << "Deallocated memory." << endl;
}