# cpp-Generator
A C program to generate a cpp file ready to be completed from a given hpp file.  
---------  
Some basic stuff I made out of a personal need.  
You give it a `.hpp` file, and it will read it to make a `.cpp` file ready to be completed.  

## Example  

Executing the program on the following `.hpp` file:  

```cpp
#include <string>

class A {
private:
    int n1;
    std::string s1;
public:
    A(int n1, std::string s1);

    int something(int number);
};

void somefunction(float num);
```

will give you the following cpp file :
```
#include "file.hpp"

 A::A(int n1, std::string s1) {
    // TODO
}

int A::something(int number) {
    // TODO
}

void somefunction(float num) {
    // TODO
}
```
Generate it with this command :
``` cppgen file.hpp file.cpp ```

------
## Installation

clone the repo and run
```
sudo make system
```
for a global installation (in /usr/bin) or 
```
make local 
```
for a user only installation (in ~/bin, expected to exist)
