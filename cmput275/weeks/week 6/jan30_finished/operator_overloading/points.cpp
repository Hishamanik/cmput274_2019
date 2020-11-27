#include <iostream>

using namespace std;

struct Point {
  double x, y;
  Point operator+(const Point& rhs) const;
};

// The first "Point" is the return type of the function.
// The Point::operator+ means we are overloading the + operator
//  for the Point struct.
// The argument const Point& rhs is the right side of an expression.
//  and it must be "const" because we won't change it.
// Finally, the last const assures we won't change "this" struct.
Point Point::operator+(const Point& rhs) const {
  Point result;
  result.x = x + rhs.x; // same as this->x + rhs.x
  result.y = y + rhs.y;

  return result;
}

// To overload the << operator, you have to return a reference to
// the ostream object you are using to print after you print things.
ostream& operator<<(ostream& out, const Point& p) {
  out << '(' << p.x << ", " << p.y << ')';
  return out;
}

int main() {
  Point p, q;

  p.x = 1.0;
  p.y = 2.0;

  q.x = 5.5;
  q.y = 10.1;

  // This will call the operator+ method of p, with the point q being
  // passed as "rhs".
  Point r = p+q;

  cout << r.x << ' ' << r.y << endl;

  // Can also output using cout
  cout << r << endl;

  // Quick Note: << is a binary operator. We overloaded it above
  // so that if the first argument is an output stream and the second a point,
  // it will print the point and return the output stream by reference
  // again so it can be chained with another output.

  // Think, each (...) evaluates an expression and returns the output stream
  // object so it can be used with the next one. That is why the return type
  // of the operator is ostream& (gg. return a reference to, not a copy of, cout)

  // cout << p is called (the function above), which outputs the point
  // and returns a reference to the original cout object. The next call
  // is equivalent to cout << " + ", which again returns cout, and so on...
  (((((cout << p) << " + ") << q) << " = ") << (p+q)) << endl;


  // The above is equivalent to:
  // cout << p << " + " << q << " = " << (p+q) << endl;

  // We can also call the operator like it was a function, but that's
  // sort of defeating the point of using operator overloading because
  // we like shorter expressions like p+q.
  cout << p.operator+(q) << endl;

  return 0;
}
