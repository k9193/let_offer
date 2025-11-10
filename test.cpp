#include <iostream>
using namespace std;
struct Example1
{
    char a;   // 1字节
    short b;  // 2字节
    int c;    // 4字节
    double d; // 8字节
};

struct Example2
{
    char a;
    int b[3]; // int数组，每个4字节
    short c;
    char d[5]; // char数组，每个1字节
};
// Example1: 1 +1(padding) + 2 + 4 + 8 = 16字节
// Example2: 1 +3(padding) + 12 + 2 +5 +3(padding) = 24字节
int main(int argc, char const *argv[])
{
    cout << sizeof(Example1) << " \n";
    cout << sizeof(Example2) << " \n";
    return 0;
}
