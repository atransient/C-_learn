#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

atomic<int> shared_counter(0);


void increment_function() {
    for (int i = 0; i < 100000; ++i) {
        // 这行代码是原子操作。它等价于 shared_counter.fetch_add(1, std::memory_order_seq_cst);
        shared_counter.fetch_add(1, std::memory_order_seq_cst);
        // shared_counter++;
        // shared_counter += 2;
    }
}

int main()
{
    thread t1(increment_function);
    thread t2(increment_function);
    t1.join();
    t2.join();
    cout << "Final counter value (with atomic): " << shared_counter.load() << endl;
    cout << shared_counter << endl;
    // 检查是否是无锁的 (可选)
    if (shared_counter.is_lock_free()) {
        cout << "std::atomic<int> operations are lock-free on this platform." << endl;
    } else {
        cout << "std::atomic<int> operations are not lock-free on this platform (using mutex emulation)." << endl;
    }
}