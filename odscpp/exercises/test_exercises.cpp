#if 0

#include <iostream>
#include <string>

#include "chapter2_arrayLists.h"

using std::string;
using namespace Exercise;

int main()
{
  ////////////////////////////////////////
  ////  Data Block
  string a[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
  string b[6] = {"a", "b", "c", "d", "e", "f"};
  ////////////////////////////////////////////////////////
  // ArrayStack & FastArrayStack Test
  ArrayStack<string> test_string;

  std::cout << "\n====================================" << std::endl 
    << "@: array stack " << std::endl;  
  std::cout << "Push: ";
  for (size_t i=0; i<20; ++i) {
    test_string.Push(a[rand() % 10]);
    std::cout << test_string.Get(i) << " ";
  }
  std::cout << "\nPop: ";
  for (size_t i=0; i<10; ++i)
    std::cout << test_string.Pop() << " ";
  std::cout << "\n=====================================" << std::endl
    << "@: add all array from index [3]." << std::endl;
  std::cout << "Origin state: ";
  test_string.TestPrint();
  test_string.AddAll(3, a);
  test_string.TestPrint();
  test_string.AddAll(7,b);
  test_string.TestPrint();

  return 0;
}



#endif