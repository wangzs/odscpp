#if 0

#include "../odscpp/lists/array_based.hpp"
#include <iostream>
#include <string>

using std::string;
using namespace wzs;

int main()
{
  ////////////////////////////////////////
  ////  Data Block
  string a[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

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


  ////////////////////////////////////////////////////////
  // DualArrayDeque Test
  DualArrayDeque<string> test_dual_deque;
  std::cout << "===================================\n@: array dual deque " << std::endl;
  for (size_t i=0; i<5; ++i)
    test_dual_deque.Add(i, a[rand() % 10]);
  test_dual_deque.TestPrint();
  std::cout << "\nadd: \"" << a[6] << "\" in [0].\n";
  test_dual_deque.Add(0, a[6]);
  test_dual_deque.TestPrint();
  std::cout << "\nadd: \"" << a[0] << "\" in [2].\n"; 
  test_dual_deque.Add(2, a[0]);
  test_dual_deque.TestPrint();
  std::cout << "Capacity: " << test_dual_deque.Capacity() << std::endl;
  std::cout << "\nRemove [0] element \"" << test_dual_deque.Remove(0) << "\".\n"; 
  std::cout << "Capacity: " << test_dual_deque.Capacity() << std::endl;
  test_dual_deque.TestPrint();
  std::cout << "\nRemove [0] element \"" << test_dual_deque.Remove(0) << "\".\n"; 
  test_dual_deque.TestPrint();
  std::cout << "\nRemove [0] element \"" << test_dual_deque.Remove(0) << "\".\n"; 
  test_dual_deque.TestPrint();

  ////////////////////////////////////////////////////////
  // RootishArrayStack Test
  RootishArrayStack<string> test_rootis_stack;
  std::cout << "===================================\n@: array rootish stack " << std::endl;
  for (size_t i=0; i<5; ++i)
    test_rootis_stack.Add(i, a[rand() % 10]);
  test_rootis_stack.TestPrint();
  std::cout << "\nadd: \"" << a[0] << "\" in [2].\n"; 
  test_rootis_stack.Add(2, a[0]);
  test_rootis_stack.TestPrint();
  std::cout << "\nadd: \"" << a[3] << "\" in [1].\n"; 
  test_rootis_stack.Add(1, a[3]);
  test_rootis_stack.TestPrint();
  std::cout << "\nRemove [1] element \"" << test_rootis_stack.Remove(1) << "\".\n"; 
  test_rootis_stack.TestPrint();


  return 0;
}

#endif