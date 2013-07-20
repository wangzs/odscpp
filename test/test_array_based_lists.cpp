#include "../odscpp/lists/array_based.hpp"
#include <iostream>
#include <string>

using std::string;
using namespace wzs;

int main()
{
  ArrayStack<int> test_int;
  for (size_t i=0; i<20; ++i)
    test_int.Push(rand() % 40);

  for (size_t i=0; i<10; ++i)
    std::cout << test_int.Pop() << " " ;
  std::cout << std::endl;

  string a[10] = {"ha", "hehe", "hello world", "c++", "Linux", "test"};
  ArrayStack<string> test_string;
  FastArrayStack<string> test_fast_string;
  ArrayQueue<string> test_queue;

  std::cout << "\n====================================" << std::endl 
    << "@: fast array stack " << std::endl;
  for (size_t i=0; i<20; ++i) {
    test_fast_string.Push(a[rand() % 10]);
    std::cout << test_fast_string.Get(i) << " ";
  }
  std::cout << std::endl;
  for (size_t i=0; i<10; ++i)
    std::cout << test_fast_string.Pop() << " ";
  std::cout << "\n==================================" << std::endl
    << "@: array queue " << std::endl;
  for (size_t i=0; i<20; ++i) {
    test_queue.Add(a[rand() % 10]);
    std::cout << test_queue.Get(i) << " ";
  }
  std::cout << std::endl;
  for (size_t i=0; i<16; ++i)
    std::cout << test_queue.Remove() << " ";
  std::cout << std::endl;
  for (size_t i=0; i<10; ++i) {
    test_queue.Add(a[rand() % 10]);
    std::cout << test_queue.Get(i) << " ";
  }
  std::cout << std::endl;
  for (size_t i=0; i<7; ++i)
    std::cout << test_queue.Remove() << " ";
  std::cout << "\n==================================" << std::endl;

  for (size_t i=0; i<20; ++i) {
    test_string.Push(a[rand() % 10]);
    std::cout << test_string.Get(i) << " ";
  }
  std::cout << std::endl;
    
  for (size_t i=0; i<10; ++i)
    std::cout << test_string.Pop() << " ";

  return 0;
}