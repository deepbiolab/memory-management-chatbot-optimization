#include <stdlib.h>

#include <iostream>

class MyMovableClass {
 private:
  int _size;
<<<<<<< HEAD
  int* _data;

 public:
  MyMovableClass(size_t size) {  // constructor
=======
  int *_data;

 public:
  MyMovableClass(size_t size)  // constructor
  {
>>>>>>> 7f29e547e19f9a2d1d37e9bdf49cebf1134bf5db
    _size = size;
    _data = new int[_size];
    std::cout << "CREATING instance of MyMovableClass at " << this
              << " allocated with size = " << _size * sizeof(int) << " bytes"
              << std::endl;
  }

<<<<<<< HEAD
  ~MyMovableClass() {  // 1 : destructor
=======
  ~MyMovableClass()  // 1 : destructor
  {
>>>>>>> 7f29e547e19f9a2d1d37e9bdf49cebf1134bf5db
    std::cout << "DELETING instance of MyMovableClass at " << this << std::endl;
    delete[] _data;
  }

<<<<<<< HEAD
  MyMovableClass(const MyMovableClass& source)  // 2 : copy constructor
=======
  MyMovableClass(const MyMovableClass &source)  // 2 : copy constructor
>>>>>>> 7f29e547e19f9a2d1d37e9bdf49cebf1134bf5db
  {
    _size = source._size;
    _data = new int[_size];
    *_data = *source._data;
    std::cout << "COPYING content of instance " << &source << " to instance "
              << this << std::endl;
  }
<<<<<<< HEAD

  MyMovableClass& operator=(
      const MyMovableClass& source)  // 3 : copy assignment operator
=======
  MyMovableClass &operator=(
      const MyMovableClass &source)  // 3 : copy assignment operator
>>>>>>> 7f29e547e19f9a2d1d37e9bdf49cebf1134bf5db
  {
    std::cout << "ASSIGNING content of instance " << &source << " to instance "
              << this << std::endl;
    if (this == &source) return *this;
    delete[] _data;
    _data = new int[source._size];
    *_data = *source._data;
    _size = source._size;
    return *this;
  }
<<<<<<< HEAD
};
=======
};

MyMovableClass createObject(int size) {
  MyMovableClass obj(size);  // regular constructor
  return obj;                // return MyMovableClass object by value
}

int main() {
  MyMovableClass obj1(10);
  MyMovableClass obj2(obj1);
  obj2 = obj1;

  // Here, we are instantiating obj3 in the same statement; hence the
  // copy assignment operator would not be called.
  MyMovableClass obj3 = obj1;
  // createObject(10) returns a temporary copy of the object as an rvalue, which
  // is passed to the copy constructor.
  // MyMovableClass obj4 = createObject(10);

  MyMovableClass obj4(createObject(10));

  return 0;
}
>>>>>>> 7f29e547e19f9a2d1d37e9bdf49cebf1134bf5db
