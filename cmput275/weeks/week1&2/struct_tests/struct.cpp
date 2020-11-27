#include <iostream> 
using namespace std; 
   
struct test1 { 
    short s;    // 2 bytes + 2 bytes padding
    int i;      // 4 bytes
    char c;     // 1 byte + 3 bytes padding
} t1; 
   
struct test2 { 
    int i;      // 4 bytes
    char c;     // 1 byte + 1 byte padding
    short s;    // 2 bytes 
} t2; 

struct test3 {
    char c;     // 1 byte + 3 bytes padding
    int i;      // 4 bytes
    short s;    // 2 bytes + 2 bytes padding
} t3[5];

// Nesting structures
struct test4 {
    char c;     // 1 byte + 3 bytes padding
    test3 t;    // 12 bytes
} t4;

struct Point3D {
    float x;    // 4 bytes
    float y;    // 4 bytes
    float z;    // 4 bytes
};

void size_test() {
    cout << "size of double is " << sizeof(double) << "\n";
    cout << "size of float is " << sizeof(float) << "\n";
    cout << "size of int is " << sizeof(int) << "\n";
    cout << "size of short is " << sizeof(short) << "\n";
    cout << "size of char is " << sizeof(char) << "\n";
}

Point3D create_struct(float x, float y, float z) {
    Point3D p = {x, y, z};
    return p;
}

void print_struct(Point3D point) {
    cout << "x: " << point.x << ", y: " << point.y << ", z: " << point.z << "\n";
}

// driver program 
int main() { 
    size_test();

    cout << "size of struct test1 is " << sizeof(t1) << "\n"; 
    cout << "size of struct test2 is " << sizeof(t2) << "\n";

    cout << "size of array of structs test3 is " << sizeof(t3) << "\n"; 
    cout << "size of struct test3 is " << sizeof(t3[0]) << "\n"; 

    cout << "size of struct test4 is " << sizeof(t4) << "\n";
    t4.t.i = 0;

    test3 t = {'a', 2, 1};
    
    Point3D p = create_struct(1.5, 0, -1);
    print_struct(p);
    
    test3 *pt3 = &t3[1];

    cout << "size of int member of struct test3 is " << sizeof(t3[0].i) << "\n";

    // using -> dereferencing operator
    cout << "size of short member of struct test3 is " << sizeof(pt3->s) << "\n";

    // using * dereferencing operator
    cout << "size of char member of struct test3 is " << sizeof((*pt3).c) << "\n";

    return 0; 
} 