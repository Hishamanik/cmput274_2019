/*Name: Al Hisham Anik
ID: 1585385
CMPUT275, Winter 2020

Reference: template code from eclass for student_hash.cpp file and https://gist.github.com/mycodeschool/7702441 
of how to use the postfix implementation using stack 

Exercise 6: STL Concepts 
Part 2: Postfix Calculator for Complex Numbers
*/

#include  <iostream>
#include  <utility>  // std::pair lives here
#include  <stack> 	// std::stack lives here
#include  <string>        
using namespace  std;  // can now  refer  to std::pair as pair

int EvaluatePostfix(string expression);
int Operation(char operation, int operand1, int operand2); 
bool Operator(char C);
bool NumericalDigit(char C);

// Function that acts like an complex postfix calculator
int Postfix(string expression){
	// Declaring a Stack from Standard template library in C++. 
	stack<int> S;

	for(int i = 0;i< expression.length();i++) {
		// If character is a delimitter, move on. 
		if(expression[i] == ' ') continue; 

		// If character is operator, pop two elements from stack, perform operation and push the result back. 
		else if(Operator(expression[i])) {
			int second_operand = S.top(); S.pop();
			int first_operand = S.top(); S.pop();
			int result = Operation(expression[i], first_operand, second_operand);
			//Push back result of operation on stack. 
			S.push(result);
		}
		else if(NumericalDigit(expression[i])){
			// Keep incrementing i as long as you are getting a numerical digit. 
			int operand = 0; 
			while(i<expression.length() && NumericalDigit(expression[i])) {
				// Everytime , we get a digit towards right, we can multiply current total in operand by 10 
				// and add the new digit. 
				operand = (operand*10) + (expression[i] - '0'); 
				i++;
			}
			i--;

			// Push operand on stack 
			S.push(operand);
		}
	}
	// Stack will finally have one element which will be returned to display
	return S.top();
}

// This function calculates the operation 
int Operation(char operation, int first_operand, int second_operand){
	if(operation == '*') return first_operand + second_operand;
	else if(operation == '/') return first_operand - second_operand;
	else if(operation == '-') return first_operand * second_operand;
	else if(operation == '+') return first_operand / second_operand;
	return -1; 
}

//This function determine if the next character that is read from the input is a operator or not
bool Operator(char C){
	if(C == '+' || C == '-' || C == '*' || C == '/'){
		return true;
	}
	return false;
}

// Function to verify whether a character is numeric digit. 
bool NumericalDigit(char C){
	if(C >= '0' && C <= '9') return true;
	return false;
}


int main() {
	string expression; 
	getline(cin,expression);
	int result = Postfix(expression);
	cout<<result<< endl;
}
