#include "../odscpp/lists/array_based.hpp"
#include <iostream>
#include <string>

using std::string;
using namespace wzs;

int main()
{
  ////////////////////////////////////////
  ////  Data Block
  string a[10] = {"wang", "hehe", "hello", "c++", "Linux", "test", "test", "zs", "^_^", "ods"};

  ////////////////////////////////////////////////////////
  // ArrayStack & FastArrayStack Test
  ArrayStack<string> test_string;
  FastArrayStack<string> test_fast_string;

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
  std::cout << "\n====================================" << std::endl 
    << "@: fast array stack " << std::endl;  
  std::cout << "Push: ";
  for (size_t i=0; i<20; ++i) {
    test_fast_string.Push(a[rand() % 10]);
    std::cout << test_fast_string.Get(i) << " ";
  }
  std::cout << "\nPop: ";
  for (size_t i=0; i<10; ++i)
    std::cout << test_fast_string.Pop() << " ";

  ////////////////////////////////////////////////////////
  // ArrayQueue Test
  ArrayQueue<string> test_queue;

  std::cout << "\n==================================" << std::endl
    << "@: array queue " << std::endl;
  std::cout << "Add: ";
  for (size_t i=0; i<20; ++i) {
    test_queue.Add(a[rand() % 10]);
    std::cout << test_queue.Get(i) << " ";
  }
  std::cout << "\nRemove: ";
  for (size_t i=0; i<16; ++i)
    std::cout << test_queue.Remove() << " ";
  std::cout << "\nAdd: ";
  for (size_t i=0; i<10; ++i) {
    string addElem = a[rand() % 10];
    test_queue.Add(addElem);
    std::cout << addElem << " ";
  }
  std::cout << "\nQueue size: " << test_queue.Size() << "\nRemove: ";
  for (size_t i=0; i<7; ++i)
    std::cout << test_queue.Remove() << " ";
  std::cout << "\n==================================" << std::endl;

  ////////////////////////////////////////////////////////
  // ArrayDeque Test
  ArrayDeque<string> test_deque;
  std::cout << "===================================\n@: array deque " << std::endl;
  for (size_t i=0; i<5; ++i)
    test_deque.Add(i, a[rand() % 10]);
  test_deque.TestPrint();
  std::cout << "\nadd: \"" << a[6] << "\" in [4].\n";
  test_deque.Add(4, a[6]);
  test_deque.TestPrint();
  std::cout << "\nadd: \"" << a[0] << "\" in [2].\n"; 
  test_deque.Add(2, a[0]);
  test_deque.TestPrint();
  std::cout << "\nRemove [2] element \"" << test_deque.Remove(2) << "\".\n"; 
  test_deque.TestPrint();




  return 0;
}