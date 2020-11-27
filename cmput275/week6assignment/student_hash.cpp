/*Name: Al Hisham Anik
ID: 1585385
CMPUT275, Winter 2020

Reference: template code from eclass for student_hash.cpp file and https://www.techiedelight.com/use-struct-key-std-unordered_map-cpp/
to learn how to use struct hash program

Exercise 6: STL Concepts 
Part 1: Hashing a Custom Struct
*/

struct StudentRecord {
	string name;
	int id, grade;
};

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

template<typename T1, typename T2>
struct StudentRecord{
	string name;
	int id;
	int grade;

	// constructor
	Struct(string name, int id, int grade){
		this->name = name;
		this->id =id;
		this->grade= grade;
	}

// operator== is required to compare keys in case of hash collision
	bool operator==(const StudentRecord &p) const{
		return name == p.name && id == p.id && grade = p.grade;
	}
};
struct hash_function{
	template <class T1, class T2>
	size_t operator() (const StudentRecord<T1, T2> &studentrecord) const{
		size_t h1 = hash<string>()(studentrecord.name);
		size_t h2 = hash<int>()(studentrecord.id);
		size_t h3 = hash<int>()(studentrecord.grade);

		return h1 ^ h2;
	}
};

int main(){
	unordered_map<StudentRecord<string,string>, int, hash_functionn> u_map ={
	};
	for (const auto &entry: u_map){
		cout << entry.first.x << " " << entry.first.y << entry.second << endl;
	}
	return 0;
}