#include <iostream>

using namespace std;

int main() {
  // Declare your variables
	int chairs;
	int number_of_friends;
	int first_knight_position ;
	int prizes[100000] = {};
	int friends_position[100000] = {};
	int sum=0;

  // Read the input
	cin >> chairs;
	cin >> number_of_friends;
	cin >> first_knight_position;

	int m=0;
	for (int i=0;i<chairs;i++){
		cin >> prizes[i];
		m++;
	}

	for (int i=0; i<number_of_friends;i++){
		cin >> friends_position[i];
	}
  // Solve the problem
	int k=0;
	int total = (first_knight_position+number_of_friends);
	for (int j=first_knight_position;j<m;j++){
			sum += prizes[friends_position[k]];
			k++;
			cout << sum << " ";
	}
	//cout << sum << endl;
  return 0;
}
