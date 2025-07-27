#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex mtx;
int global_counter = 0;

void increment_with_origin_lock() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();
        // lock 对象的生命周期就是临界区
        global_counter++;
        mtx.unlock();
    }
}

void increment_with_lock_guard() {
    for (int i = 0; i < 100000; ++i) {
        // 构造函数获取锁
        lock_guard<mutex> lock(mtx);
        // lock 对象的生命周期就是临界区
        global_counter++;
        // 析构函数释放锁 (即使发生异常也会自动释放)
    }
}

void increment_with_unique_lock() 
{
    for (int i = 0; i < 100000; ++i) {
        // 构造函数获取锁
        unique_lock<mutex> lock(mtx, defer_lock);
        lock.lock();
        // lock 对象的生命周期就是临界区
        global_counter += 2;
        
        lock.unlock();
    }
}

int main() {
    thread t0(increment_with_origin_lock);
    thread t1(increment_with_lock_guard);
    thread t2(increment_with_unique_lock);

    t0.join();
    t1.join();
    t2.join();

    std::cout << "Final counter (with lock_guard): " << global_counter << std::endl; // 期望输出 200000
    return 0;
}