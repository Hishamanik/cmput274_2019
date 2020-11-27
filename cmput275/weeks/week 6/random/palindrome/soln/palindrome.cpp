#include <iostream>
#include <cstring>

using namespace std;

int main() {
  // input contains the input string
  // n is the length of the input string
  char input[20001];
  int n = 0;
  int number = 0;

  // read in line and determine out how long it is
  cin >> input;
  n = strlen(input);

  // now solve the problem!
  int k=0;
  for (int i=0; i<n; i++){
  	for (int j=n; j>0; j--){
  		if (input[i]==input[j]){
  			number ++;
  			break;
  		}
  		else if (n%2 == 0) {
  			number == 0;
  		} 
  	}
  }
  cout << number << endl;


  return 0;
}
