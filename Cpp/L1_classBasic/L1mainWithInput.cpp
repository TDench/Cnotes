#include <iostream>
#include <string>

using namespace std;
class Computer {
 public:
  void displayHelloMessage(string s) const { cout << s << endl; }
};

int main(int argc, char const *argv[]) {
  Computer myComputer;
  string inputStr;
  inputStr = "Hello input";
  myComputer.displayHelloMessage(inputStr);
  return 0;
}
