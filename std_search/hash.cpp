#include <iostream>
#include <string>

using namespace std;

int main()
{
    hash<int> int_hasher;
    hash<std::string> string_hasher;

    int num = 123;
    string text = "hello world";

    size_t num_hash = int_hasher(num);
    size_t text_hash = string_hasher(text);

    cout << "Hash of int (" << num << "): " << num_hash << std::endl;
    cout << "Hash of string (\"" << text << "\"): " << text_hash << std::endl;

    // 相同的输入会产生相同的哈希值
    cout << "Hash of 123 again: " << int_hasher(123) << endl;
    cout << "Hash of \"hello world\" again: " << string_hasher("hello world") << endl;

    // 不同的输入通常产生不同的哈希值 (但可能冲突)
    cout << "Hash of 124: " << int_hasher(124) << endl;
    cout << "Hash of \"world hello\": " << string_hasher("world hello") << endl;
}