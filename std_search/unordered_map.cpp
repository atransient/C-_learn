#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
    unordered_map<string, int> ages;
    ages["Alice"] = 30;
    ages["Bob"] = 25;
    ages.insert({"Charlie", 35});
    cout << "Alice's age: " << ages["Alice"] << endl;

    // 检查元素是否存在
    if (ages.count("Bob")) {
        std::cout << "Bob is in the map." << std::endl;
    }

    // 遍历元素 (顺序不确定)
    std::cout << "\nAll ages:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 删除元素
    ages.erase("Bob");
    std::cout << "\nAfter deleting Bob:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 更新元素
    ages["Alice"] = 31;
    std::cout << "\nAlice's new age: " << ages["Alice"] << std::endl;

    // 查看大小
    std::cout << "\nsize : " << ages.size() << std::endl;

    return 0;
}