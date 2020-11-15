// Name: Al Hisham Anik
// ID: 1585385
// CMPUT274, Fall 2019
//
//Exercise 7: Euler's Phi Function

#include <iostream> 
#include <iomanip> 
using namespace std; 


// This function computes the value phi of n for all greater or equal than 1 and less or equa than 2^23-1
unsigned int phi(unsigned int n) {
  	int r[0] = a, r[1] = b ;
	int s[0] = 1, s[1] = 0 ;
	int t[0] = 0, t[1] = 1 ;


	int32_t i = 1;
	while r[i] > 0 {
		int32_t q = r[i-1]/r[i]
		r[i+1] = r[i-1] - q*r[i]
		s[i+1] = s[i-1] - q*s[i]
		t[i+1] = t[i-1] - q*t[i]
		i = i+1
  uint32_t m = n/2
  if (n == 1) {
    cout << "not prime" << endl;
  }
  else {
  	 for(i = 2; i <= m; i++) {
  	  if (n == 1){
  	  	cout<<"not prime"<<endl;
  	  } 
      if(n % i == 0) {  
          cout<<"not prime"<<endl;  
          flag=1;  
          break;  
      }  
     }  
  if (flag==0 && n!= 1) {
      cout << "prime"<<endl;  
  return 0;
  }
}


//Counting 15-bits integers k with gcd(n,k) = 1
uint32_t gcd_euclid_fast(uint32_t a, uint32_t b) {
  while (b > 0) {
    a %= b;

    // now swap them
    uint32_t tmp = a;
    a = b;
    b = tmp;s
  }
  return a; // b is 0
}

// Main function which reads the value entered from the bash terminal
int main() {
	int32_t n;    
    cin >> n;  
    
    uint32_t value = phi(unsigned n)
    double ratio  = value/n

    // returns the value of integer entered, phi of n and the ratio between phi of n and n
    cout<< value <<end;
    cout<< ratio <<endl;
    cout << n <<endl;

	}
} 
  
