#include <iostream>
#include <cmath> 
#include <math.h>

using namespace std;

int main() {
  // Declare your variables
	int degree;
	int value ;
	int mod_val;
	int store;
	int sum =0;

  // Read the input
	cin >> degree;
	cin >> value;
	cin >> mod_val;

	int arr[degree] = {};

	for (int i=0;i<degree+1; i++){
		cin >> arr[i];
	}
	cout << arr;
	for (int j=1; j< degree; j++){
		int cal = arr[j-1]*pow(value, j-1);
		sum += cal;
	}
	cout << sum;
  return 0;
}
