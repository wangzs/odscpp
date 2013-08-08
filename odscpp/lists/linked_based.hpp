/*
============================================
* @ filename: linked_based.hpp
* @ author  : Wangzs
* @ date    : 2013/08/02
* @ describe: Open Data Structure - Chapter 3
*   SLList / DLList / SEList(not implement)
============================================
*/
#ifndef ODSCPP_LINKEDBASED_HPP
#define ODSCPP_LINKEDBASED_HPP

#include <cassert>
#include <cstddef>

#include "array_based.hpp"

#if _DEBUG
#include <iostream>
#endif


namespace wzs {
  /*
  =================================================
  * @ class Stack_LinkedList can add new val in 
  *     any location, and remove any location elem.
  *     It also implement 'LIFO'.
  =================================================
  */
  template <typename T>
  class Stack_LinkedList {
  public:
    Stack_LinkedList() {
      m_pHead = m_pTail = NULL;
      m_len = 0;
    }

    ~Stack_LinkedList() {
      while (m_pHead != m_pTail) {
        node* tmpHead = m_pHead;
        m_pHead = m_pHead->next;
        delete tmpHead;
      } 
      if (m_len != 0)
        delete m_pTail;
    }
    
    inline size_t Size() const {
      return m_len;
    }

    void Add(size_t index, const T& val) {
      assert(index <= m_len);
      node* addedNode = new node();
      addedNode->val = val;
      // the first add node
      if (0 == m_len) {
        m_pHead = m_pTail = addedNode;
        addedNode->next = NULL;
      }
      else if (index > 0 && index == m_len) {
        m_pTail->next = addedNode;
        addedNode->next = NULL;
        m_pTail = addedNode;
      }
      else {
        size_t beginIndex = 0;
        node* preNode = NULL;
        node* shiftNode = m_pHead;
        while (beginIndex < index) {
          beginIndex++;
          preNode = shiftNode;
          shiftNode = shiftNode->next;
        }
        preNode->next = addedNode;
        addedNode->next = shiftNode;
      }
      m_len++;
    }
    T push_back(const T& val) {
      node* addedNode = new node();
      addedNode->val = val;
      addedNode->next = NULL;
      if (0 == m_len)
        m_pHead = m_pTail = addedNode;
      else {
        m_pTail->next = addedNode;
        m_pTail = addedNode;
      }
      m_len++;
      return val;
    }

    T Remove(size_t index) {
      assert(index < m_len);
      T tmpVal;
      if (1 == m_len) {
        tmpVal = m_pHead->val;
        delete m_pHead;
        m_pHead = m_pTail = NULL;
      }
      else if (0 == index) {
        tmpVal = m_pHead->val;
        node* tmp = m_pHead;
        m_pHead = m_pHead->next;
        delete tmp;
      }
      else if (index > 0 && index == m_len) {
        node* preNode = m_pHead;
        while (preNode->next != m_pTail)
          preNode = preNode->next;
        preNode->next = NULL;
        tmpVal = m_pTail->val;
        delete m_pTail;
        m_pTail = preNode;
      }
      else {
        node* preNode = m_pHead;
        node* deleteNode = m_pHead;
        int beginIndex = 0;
        while (beginIndex < index) {
          beginIndex--;
          preNode = deleteNode;
          deleteNode = deleteNode->next; 
        }
        preNode->next = deleteNode->next;
        tmpVal = deleteNode->val;
        delete deleteNode;
      }
      return tmpVal;
    }
    T remove_back() {
      assert(m_len > 0);
      node* preNode = m_pHead;
      while (preNode->next != m_pTail)
        preNode = preNode->next;
      T tmpVal(m_pTail->val);
      preNode->next = NULL;
      delete m_pTail;
      m_pTail = preNode;
      return tmpVal;
    }

#if _DEBUG
    void TestPrint() {
      node* shiftNode = m_pHead;
      while (shiftNode != m_pTail) {
        std::cout << shiftNode->val << " ";
        shiftNode = shiftNode->next;
      }
      std::cout << m_pTail->val << std::endl;
    }
#endif

  private:
    struct node {
      T     val;
      node* next;
    };
    node*   m_pHead;  // point the SLList's head
    node*   m_pTail;  // point the SLList's tail
    size_t  m_len;    // the number of elements
  };  // end class SinglyLinkedList definition


  /*
  ============================================
  * @ class Deque_LinkedList push new val in 
  *   the front of the list, and pop the val
  *   in the front of the list too. 'FIFO'
  ============================================
  */
  template <typename T> 
  class Deque_LinkedList {
  public:
    Deque_LinkedList() {
      m_pHead = m_pTail = NULL;
      m_len = 0;
    }
    ~Deque_LinkedList() {
      while (m_pHead != m_pTail) {
        node* tmpHead = m_pHead;
        m_pHead = m_pHead->next;
        delete tmpHead;
      }
      if (m_len != 0)
        delete m_pTail;
    }

    inline size_t Size() const {
      return m_len;
    }

    T Push(const T& val) {
      node* newNode = new node();
      newNode->val = val;
      newNode->next = m_pHead;
      m_pHead = newNode;
      if (0 == m_len)
        m_pTail = m_pHead;
      m_len++;
      return val;
    }

    T Pop() {
      assert(m_len > 0);
      T tmp = m_pHead->val;
      node* secondNode = m_pHead;
      m_pHead = m_pHead->next;
      delete secondNode;
      if (1 == m_len)
        m_pTail = m_pHead;    // point to NULL
      m_len--;
      return tmp;
    }

#if _DEBUG
    void TestPrint() {
      node* shiftNode = m_pHead;
      while (shiftNode != m_pTail) {
        std::cout << shiftNode->val << " ";
        shiftNode = shiftNode->next;
      }
      std::cout << m_pTail->val << std::endl;
    }
#endif

  private:
    struct node {
      T     val;
      node* next;
    };
    node*   m_pHead;
    node*   m_pTail;
    size_t  m_len;
  };


  /*
  ===============================================
  * @ describe : a doubly-linked list, the member 
  *     m_nodeDummy acts as placeholder.
  * @ interface: get(i) / set(i, val) / 
  *     add(i, val) / remove(i)
  ===============================================
  */
  template <typename T>
  class DLList {
  private:
    struct node {
      T val;
      node* prev;
      node* next;
    };

    node    m_nodeDummy;   // 哨兵节点
    size_t  m_len;         // 元素个数

  public:
    DLList() {
      m_len = 0;
      m_nodeDummy.next = &m_nodeDummy;
      m_nodeDummy.prev = &m_nodeDummy;
    }

    inline size_t Size() const {
      return m_len;
    }

    T Get(size_t index) const {
      return getNode(index)->val;
    }

    T Set(size_t index, const T& val) {
      node* elem = getNode(index);
      T tmp_val = elem->val;
      elem->val = val;
      return tmp_val;
    }
    
    void Add(size_t index, const T& val) {
      addBefore(getNode(index), val);
    }

    T Remove(size_t index) {
      assert(index < m_len && m_len > 0);
      node* del_node = getNode(index);
      T tmp = del_node->val;
      removeNode(del_node);
      return tmp;
    }

#ifdef _DEBUG
    void TestPrint() {
      node* shift_node = m_nodeDummy.next;
      while (shift_node->next != &m_nodeDummy) {
        std::cout << shift_node->val << " ";
        shift_node = shift_node->next;
      }
       std::cout << shift_node->val << " ";
      std::cout << std::endl;
    }
#endif

  private:
    inline node* getNode(size_t index) {
      assert(index <= m_len);
      node* p;
      if (index < m_len / 2) {
        p = m_nodeDummy.next;
        for (size_t i=0; i<index; ++i)
          p = p->next;
      }
      else {
        p = &m_nodeDummy;
        for (int i=m_len; i>index; --i)
          p = p->prev;
      }
      return (p);
    }

    inline node* addBefore(node* loc_node, const T& val) {
      node* new_node = new node();
      new_node->val = val;
      new_node->prev = loc_node->prev;
      new_node->next = loc_node;
      loc_node->prev->next = new_node;
      loc_node->prev = new_node;
      m_len++;
      return new_node;
    }

    inline void removeNode(node* loc_node) {
      loc_node->prev->next = loc_node->next;
      loc_node->next->prev = loc_node->prev;
      delete loc_node;
      m_len--;
    }
  };


  /*
  =====================================================
  * @ describe: DDList requires an additional space for
  *   the next and previous nodes. SEList reduces this 
  *   wasted space, using a block containing several 
  *   items.
  * @ iterface: 
  =====================================================
  */
  template <typename T>
  class BDeque : public ArrayDeque<T> {
  public:
    BDeque(size_t blockSize = 8) {
      m_head = 0;
      m_len  = 0;
      Array<T> z(blockSize + 1);
      m_queueData = z;
    }

    ~BDeque() { }

    void Add(size_t index, const T& val) {
      ArrayDeque<T>::Add(index, val);
    }
  
    bool Add(const T& val) {
      ArrayDeque<T>::Add(Size(), val);
    }

    void resize() { }
  };

  template <typename T>
  class SEList {
  private:
    struct node {
      BDeque<T> data_block;
      node*     pre;
      node*     next;
    };
    node    m_nodeDummy;
    size_t  m_len;
  };
////// It's complicated, do not implement
///////////////////////////////////////////////


} // end namespace

#endif