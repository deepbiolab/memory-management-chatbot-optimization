#include <iostream>

void myFunction(int &&val) { std::cout << "val = " << val << std::endl; }

int main() {
  int i = 42;
  myFunction(std::move(i));  // work
  myFunction(42);            // work
  // myFunction(i); // not work
  return 0;
}