#include <iostream>
#include <memory>
#include <string>

class MyClass {
 private:
  // Define a private string member to hold text
  std::string _text;

 public:
  // Default constructor
  MyClass() {};

  // Constructor that initializes the text
  MyClass(std::string text) { _text = text; };

  // Destructor that prints a message when the object is destroyed
  ~MyClass() { std::cout << _text << " is destroyed." << std::endl; };

  // Member function to set the text
  void setText(std::string text) { _text = text; };
};

int main() {
  // Create a unique pointer (myClass1) to an instance of MyClass using
  // the default constructor
  // Create another unique pointer (myClass2) to an instance of MyClass
  // using the parameterized constructor
  std::unique_ptr<MyClass> myClass1(new MyClass());
  std::unique_ptr<MyClass> myClass2(new MyClass("string2"));

  // Use the -> operator to call setText on myClass1 and set its text to
  // "String 1"
  myClass1->setText("string1");

  // Use the dereference operator * to copy the contents of myClass2 into
  // myClass1
  *myClass1 = *myClass2;

  // Use the .get() function to retrieve raw pointers to the objects
  // managed by myClass1 and myClass2
  // Print the raw pointer addresses to the console
  std::cout << "Objects have Heap addresses " << myClass1.get() << " and "
            << myClass2.get() << std::endl;
  return 0;
}