#include<iostream>
#include "math.h"
using namespace std;

// int add(int a, int b) {
//   return a+b;
// }

int main(int argc, char* argv[]) {
  if(argc != 3) {
    cout << "must pass two args" << endl;
    exit(1);
  }
  int a = stoi(argv[1]);
  int b = stoi(argv[2]);
  cout << add(a, b) << endl;
  return 1;
}