#include <iostream>
#include <vector>

using namespace std;

int get_value() {
    return 100;
}

class MyClass {
public:
    string name;
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


void process_my_class(const MyClass& obj) {
    cout << "left value transfer, process_my_class(const MyClass&): " << obj.name << endl;
}

void process_my_class(MyClass&& obj) {
    cout << "right value transfer,  process_my_class(MyClass&&): " << obj.name << endl;
    // process_my_class(obj);
    // process_my_class(std::forward<MyClass&>(obj));
}

// 转发器
template<typename T>
void my_forwarding_wrapper(T&& arg) { // T&& 是万能引用
    std::cout << "my_forwarding_wrapper received: " << arg.name << std::endl;
    // 使用 std::forward 来保留 arg 的原始值类别
    process_my_class(std::forward<T>(arg));
}

int main()
{
    //================  left value  ========================
    int a = 10; // a 是左值
    int b = a;  // a 在这里作为左值被读取

    int arr[5];
    arr[0] = 5; // arr[0] 是左值

    int& ref = a; // ref 是一个左值引用，绑定到左值 a

    //================  right value  ======================
    int x = 10 + 20; // (10 + 20) 的结果 30 是右值
    int y = get_value(); // get_value() 的返回值 100 是右值

    int&& ref1 = 20;
    int&& ref2 = 20;
    cout << "address of ref1 is : " << &ref1 << endl;
    cout << "address of ref2 is : " << &ref2 << endl;

    ref1 = 40;
    cout << ref1 << "      " << ref2 << endl;

    //================  move  =======================
    vector<int> ma = {2,3,4,6,7,8,0,10,1};
    vector<int> mb = move(ma);
    cout << mb.size() << "  " << ma.size() << endl;


    //================  left value calling  ==========================
    cout << endl << "--- Calling with an lvalue ---" << endl;
    MyClass obj1("Alice");
    process_my_class(obj1);


    //================  right value calling  ==========================
    cout << endl << "--- Calling with an rvalue ---" << endl;
    process_my_class(MyClass("Bob"));
    process_my_class(move(obj1));
    process_my_class(obj1);

    //================  forwarding wrapper  ==========================
    cout << endl << "--- forwarding wrapper use ---" << endl;
    process_my_class(MyClass("Bob"));
    process_my_class(move(obj1));
    process_my_class(obj1);
}