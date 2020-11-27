#include <iostream>

using namespace std;

struct something {
    char a;     // 1 byte, but 3 bytes are padding
    int b;      // 4 bytes
    char c;     // 1 byte, but 3 bytes are padding
    char *p;    // 2, 4 or 8 bytes (depending on your machine)
};

struct anotherthing {
    char a;     
    char pad1[3];
    int b;
    char c;
    char pad2[3];
    char *p;
};

int main() {
    something s;
    anotherthing a;

    cout << sizeof(s) << endl;
    cout << sizeof(a) << endl;

    return 0;
}