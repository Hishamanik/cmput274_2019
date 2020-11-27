// Name: Al Hisham Anik
// ID: 1585385
// CMPUT275, Winter 2020
// Refrence: https://www.geeksforgeeks.org/selection-sort/ : I used this website
// and CMPUT274,275 lecture slides pseduocode to implement my flipflop function
// Exercise 3: Pseudocode to Code Task 1:

//C++ libraries to carry out different syntax
#include <iostream>
#include <algorithm>
using namespace std;

// This function is an in place sorting algorithm that takes in input array pointer and the size of array
// and returns the sorted array to the main function
void flipFlopSort(int *arr, int n) {
  int i, j, min; 

   for(i = 0; i<n-1; i++) {
      min = i;   //get index of minimum data
      for(j = i+1; j<n; j++)
         if(arr[j] < arr[min])
            min = j;
         //placing in correct position
         swap(arr[i], arr[min]);
   }
}


int main() {
	int number;
	//reading input by the user
	cin >> number;

	//declaring variables and setting the length of array
	int x =0;
	int container[number] = {};
	int container1[number] ={};
	int container2[number] = {};
	int container3[number] = {};


	//inputing the numbers entered b the user as an element in an array
	for(int i=0;i<number;i++) {
		cin >> container[i];
	}
	int i=0;
	

	//if user entered two number only and if the former one is bigger than the later one 
	//then the elements swap positions
	if (number==2){
		if (container[i] > container[i+1]){
		swap(container[i], container[i+1]);
		cout << container[i] << ' ' << container[i+1] <<endl;
		}
		else {
			cout << container[i] << ' ' << container[i+1] <<endl;	
		}
	}

	//if the number of elements entered is greater than 2
	else { 
		//First (2*n)/3 of farray is used and sent to flipfFlopSort to get sorted and then inserted back to the original array
		for (i=0; i<((2*number)/3); i++){ 
			container1[i] = container[i];
		}
		flipFlopSort(container1,(2*number)/3);
		for (i=0;i<number/3; i++) {
   			container[i] = container1[i];
		}


		int j=0;
		// Last (2*n)/3 of array is used and sent to flipfFlopSort to get sorted and then inserted back to the original array
		for (i=(number -(2*number)/3); i<number; i++){ 
			container2[j] = container[i];
			j++;			
		}
		flipFlopSort(container2,(2*number)/3);
		int k=0;
		for (i=(number -(2*number)/3); i<number; i++){ 
			container[i] = container2[k];
			k++;			
		}			


		//First (2*n)/3 of array is used and sent to flipfFlopSort to get sorted and then inserted back to the original array
		for (i=0; i<((2*number)/3); i++){ 
			container3[i] = container[i];
		}
		flipFlopSort(container3,(2*number)/3);
		for (i = 0; i < ((2*number)/3); i++) {
   			container[i] = container3[i];
		}

		//Now the sorted array is printed in the terminal
		for (i=0;i<number;i++){
			cout<<container[i]<<" ";
		}
		cout << endl;
	}

	return 0;
}
