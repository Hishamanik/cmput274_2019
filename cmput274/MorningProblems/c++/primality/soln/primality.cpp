#include <iostream>  
using namespace std;  
int main()  
{  
  int n, i, m=0, flag=0;  
  cout << "";  
  cin >> n;  
  m=n/2;

  if (n == 1) {
    cout << "not prime" << endl;
  }
  else {
  	 for(i = 2; i <= m; i++)  
  {
  	  if (n == 1)
  	  {
  	  	cout<<"not prime"<<endl;
  	  } 
      if(n % i == 0)  
      {  
          cout<<"not prime"<<endl;  
          flag=1;  
          break;  
      }  
  }  
  if (flag==0 && n!= 1)  
      cout << "prime"<<endl;  
  return 0;  
} 
    
 