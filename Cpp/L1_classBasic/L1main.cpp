#include <iostream>

using namespace std;
class Computer {
 public:
  void displayHelloMessage() const { cout << "Hello Test" << endl; }
};

int main(int argc, char const *argv[]) {
  Computer myComputer;
  myComputer.displayHelloMessage();
  return 0;
}
