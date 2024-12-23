#include <iostream>
#include <memory>

class MyClass {
 private:
  int _member;

 public:
  MyClass(int val) : _member(val) {}
  void printVal() {
    std::cout << ", managed object " << this << " with val = " << _member
              << std::endl;
  }
};

void f(std::shared_ptr<MyClass> ptr) {
  std::cout << "shared_ptr (ref count = " << ptr.use_count() << ") " << &ptr;
  ptr->printVal();
}

int main() {
  std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>(23);
  std::cout << "shared_ptr (ref count = " << sharedPtr.use_count() << ") "
            << &sharedPtr;
  sharedPtr->printVal();

  f(sharedPtr);
  std::cout << "shared_ptr (ref count = " << sharedPtr.use_count() << ") "
            << &sharedPtr;
  sharedPtr->printVal();
}