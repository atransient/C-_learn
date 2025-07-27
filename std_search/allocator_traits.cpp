// #include <iostream>
// #include <memory> // For allocator and allocator_traits
// #include <string>

// using namespace std;

// // 假设我们有一个自定义的简单分配器 (没有实现 construct/destroy)
// template<typename T>
// struct MySimpleAllocator {
//     using value_type = T;

//     // 简单地使用 operator new/delete 来分配/释放内存
//     T* allocate(size_t n) {
//         cout << "MySimpleAllocator::allocate(" << n << " elements)" << endl;
//         return static_cast<T*>(::operator new(n * sizeof(T)));
//     }

//     void deallocate(T* p, size_t n) {
//         cout << "MySimpleAllocator::deallocate(" << n << " elements)" << endl;
//         ::operator delete(p);
//     }
//     // 注意：这个分配器没有提供自己的 construct 或 destroy 方法
//     // 因此 allocator_traits 会使用默认的 placement new 和直接析构
// };

// // 比较自定义分配器实例的相等性 (对于 STL 容器很重要)
// template<typename T, typename U>
// bool operator==(const MySimpleAllocator<T>&, const MySimpleAllocator<U>&) {
//     return true; // 简单的分配器实例认为是相等的
// }
// template<typename T, typename U>
// bool operator!=(const MySimpleAllocator<T>&, const MySimpleAllocator<U>&) {
//     return false;
// }

// class MyObject {
// public:
//     int id;
//     MyObject(int i) : id(i) {
//         cout << "  MyObject(int) constructor called for ID: " << id << endl;
//     }
//     ~MyObject() {
//         cout << "  MyObject destructor called for ID: " << id << endl;
//     }
// };

// int main() {
//     // 1. 实例化我们的自定义分配器
//     MySimpleAllocator<MyObject> my_alloc;

//     // 2. 通过 allocator_traits 来操作这个分配器
//     // 这是标准库容器在内部会做的事情
//     using AllocTraits = allocator_traits<MySimpleAllocator<MyObject>>;

//     // --- 分配内存 ---
//     cout << "--- Using AllocTraits::allocate ---" << endl;
//     MyObject* obj_ptr = AllocTraits::allocate(my_alloc, 1); // 调用 my_alloc.allocate(1)
//     cout << "Allocated memory at: " << obj_ptr << endl;

//     // --- 构造对象 ---
//     cout << "\n--- Using AllocTraits::construct ---" << endl;
//     // 尽管 MySimpleAllocator 没有自己的 construct 方法，
//     // allocator_traits 依然能正确地在 obj_ptr 处构造 MyObject
//     AllocTraits::construct(my_alloc, obj_ptr, 123); // 内部使用 placement new

//     obj_ptr->id = 456; // 访问已构造的对象
//     cout << "Object's ID after modification: " << obj_ptr->id << endl;

//     // --- 销毁对象 ---
//     cout << "\n--- Using AllocTraits::destroy ---" << endl;
//     // 同样，尽管 MySimpleAllocator 没有自己的 destroy 方法，
//     // allocator_traits 依然能正确地析构 MyObject
//     AllocTraits::destroy(my_alloc, obj_ptr); // 内部直接调用 ~MyObject()

//     // --- 释放内存 ---
//     cout << "\n--- Using AllocTraits::deallocate ---" << endl;
//     AllocTraits::deallocate(my_alloc, obj_ptr, 1); // 调用 my_alloc.deallocate(obj_ptr, 1)

//     cout << "\n--- Demonstrating type aliases ---" << endl;
//     AllocTraits::pointer p_type = nullptr;
//     cout << "AllocTraits::pointer type is: " << typeid(p_type).name() << endl;
//     // 预期输出 MyObject*

//     AllocTraits::size_type s_type = 0;
//     cout << "AllocTraits::size_type type is: " << typeid(s_type).name() << endl;
//     // 预期输出 size_t

//     return 0;
// }


#include <iostream>
#include <memory> // 包含 std::allocator_traits

// --- 示例1: 使用标准分配器 (std::allocator) ---
// std::allocator<int> 默认的 pointer 类型是 int*
void testStandardAllocator() {
    std::cout << "--- 测试标准分配器 (std::allocator) ---" << std::endl;

    // 获取 std::allocator<int> 的 pointer 类型
    using Alloc = std::allocator<int>;
    using PointerType = std::allocator_traits<Alloc>::pointer;

    // 打印指针类型，对于 std::allocator<int>，这通常是 int*
    // 注意：typeid().name() 的输出可能因编译器而异
    std::cout << "std::allocator<int>::pointer 的类型是: "
              << typeid(PointerType).name() << std::endl;

    Alloc alloc;
    // 分配一个 int
    PointerType p = alloc.allocate(1);
    *p = 42;
    std::cout << "分配的值: " << *p << std::endl;
    alloc.deallocate(p, 1);
    std::cout << "内存已释放。" << std::endl;
    std::cout << std::endl;
}

// --- 示例2: 自定义分配器，返回 std::shared_ptr ---
template <typename T>
struct SmartPointerAllocator {
    using value_type = T;
    // 自定义分配器定义了 pointer 类型为 std::shared_ptr<T>
    using pointer = std::shared_ptr<T>;

    SmartPointerAllocator() = default;

    template <typename U>
    SmartPointerAllocator(const SmartPointerAllocator<U>&) {}

    // 分配内存并返回一个 std::shared_ptr
    pointer allocate(std::size_t n) {
        std::cout << "SmartPointerAllocator::allocate 被调用, 分配 " << n
                  << " 个元素。" << std::endl;
        // 模拟分配并返回一个 shared_ptr
        // 注意：实际应用中，这里需要更复杂的内存管理
        if (n == 0) return nullptr;
        // 为简单起见，我们直接构造一个 shared_ptr，不真正管理原始内存
        // 实际场景中，可能会从内存池中获取原始指针，然后包装成shared_ptr
        return std::make_shared<T>();
    }

    void deallocate(pointer p, std::size_t n) {
        std::cout << "SmartPointerAllocator::deallocate 被调用, 释放 " << n
                  << " 个元素。" << std::endl;
        // 对于 shared_ptr，当引用计数变为0时会自动释放内存
        // 这里只是打印信息
        (void)p; // 避免未使用的变量警告
        (void)n; // 避免未使用的变量警告
    }
};

void testSmartPointerAllocator() {
    std::cout << "--- 测试自定义智能指针分配器 (SmartPointerAllocator) ---" << std::endl;

    // 获取 SmartPointerAllocator<double> 的 pointer 类型
    using Alloc = SmartPointerAllocator<double>;
    using PointerType = std::allocator_traits<Alloc>::pointer;

    // 打印指针类型，对于 SmartPointerAllocator<double>，这将是 std::shared_ptr<double>
    std::cout << "SmartPointerAllocator<double>::pointer 的类型是: "
              << typeid(PointerType).name() << std::endl;

    Alloc alloc;
    // 分配一个 double
    PointerType p = alloc.allocate(1);
    *p = 123.45;
    std::cout << "分配的值: " << *p << std::endl;

    // shared_ptr 会在超出作用域时自动调用 deallocate
    // 在这里，我们手动调用deallocate只是为了演示，实际shared_ptr会自动管理
    alloc.deallocate(p, 1);
    std::cout << "内存已释放 (shared_ptr 自动管理)。" << std::endl;
    std::cout << std::endl;
}


int main() {
    testStandardAllocator();
    testSmartPointerAllocator();

    return 0;
}