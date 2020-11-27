#include <iostream>
using namespace std;


int fib (int n) {
	cout << "Hey" << endl;
    if(n <= 1) 
        return n; 
    return fib(n-1) + fib(n-2); 
}

int main() {
    int i;
    cin >> i;
    cout << fib(i);
return 0;
}