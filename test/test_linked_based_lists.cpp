#if 1

#include "../odscpp/lists/linked_based.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace wzs;


int main() {
  string a[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

  Stack_LinkedList<string> test1;
  for (size_t i=0; i<10; ++i) {
    string tmp = a[rand() % 10];
    test1.Add(i, tmp);
    cout << tmp << " ";
  }
  cout << endl;
  for (size_t i=0; i<5; ++i)
    cout << test1.remove_back() << " ";
  cout << endl;
  cout << "Push: " << test1.push_back(a[rand() % 10]) << endl;
  test1.TestPrint();
  cout << "Pop: " << test1.remove_back() << endl;

  Deque_LinkedList<string> test2;
  for (size_t i=0; i<10; ++i) {
    string tmp = a[rand() % 10];
    test2.Push(tmp);
    cout << tmp << " ";
  }
  cout << endl;
  for (size_t i=0; i<5; ++i)
    cout << test2.Pop() << " ";
  cout << endl;
  cout << "Push: " << test2.Push(a[rand() % 10]) << endl;
  test2.TestPrint();
  cout << "Pop: " << test2.Pop() << endl;

  DLList<string> test3;
  for (size_t i=0; i<10; ++i) {
    string tmp = a[rand() % 10];
    test3.Add(i, tmp);
    cout << tmp << " ";
  }
  cout << endl;
  for (size_t i=0; i<5; ++i) 
    cout << test3.Remove(1) << " ";
  cout << endl;
  test3.TestPrint();
  cout << "Add new val '" << a[5] << "' in [2] :" << endl;
  test3.Add(2, a[5]);
  test3.TestPrint();
  cout << "Remove node [4]: " << test3.Remove(4) << endl;
  test3.TestPrint();

  return 0;
}


#endif