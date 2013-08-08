#ifndef CHAPTER2_H
#define CHAPTER2_H

#include <iostream>
#include <cmath>
#include <cassert>
#include "../common/core_parts.hpp"
using wzs::Array;

namespace Exercise {
  const size_t initArraySize = 4;
  /*
  * @ Class    ：ArrayStack   [An ArrayStack implements the List interface.]
  * @ Interface：Get(i) / Set(i, val) / Add(i, val) / Push(val) / Remove(i) / Pop() / Size()
  */
  template <typename T>
  class ArrayStack {
  public:
    ArrayStack()
      :m_size(0), m_stackData(initArraySize) { }

    inline size_t Size() const{
      return m_size;
    }
    inline size_t Capacity() const {
      return m_stackData.m_length;
    }
    inline void SetSize(size_t size) {
      m_size = size;
    }

    inline Array<T>& GetElem() {
      return m_stackData;
    }

    inline T& Get(size_t index) {
      assert(index < m_size);
      return m_stackData[index];
    }
    inline const T& Get(size_t index) const {
      assert(index < m_size);
      return m_stackData[index];
    }

    inline T Set(size_t index, const T& val) {     // 返回原有index位置处的值
      assert(index < m_size);
      T tmp = m_stackData[index];
      m_stackData[index] = val;
      return tmp;
    }

    inline void Add(size_t index, const T& val) {
      assert(index <= m_size);
      if (m_size + 1 > m_stackData.m_length)
        resize();
      for (int i=m_size; i>index; --i)
        m_stackData[i] = m_stackData[i-1];
      m_stackData[index] = val;
      m_size++;
    }

    /*
    =======================================================
    *   @Exercise 2.1: AddAll(i,c) inserts all elements of 
    *       the collection(c) into the list at position i.
    =======================================================
    */
    template <int nSize>
    void AddAll(size_t index, const T (&arrVal)[nSize]) {
      assert(index <= m_size);
      size_t arrLen = nSize;
      if (m_size + arrLen > m_stackData.m_length)
        resize(arrLen-1);
      for (int i=m_size+arrLen-1; i>index+arrLen-1; --i)
        m_stackData[i] = m_stackData[i-arrLen];
      for (size_t i=index; i<index+arrLen; ++i)
        m_stackData[i] = arrVal[i-index];
      m_size += arrLen;
    }

    void Push(const T& val) {
      Add(m_size, val);
    }

    inline T Remove(size_t index) {
      assert(index < m_size);
      T tmp = m_stackData[index];
      for (size_t i=index; i<m_size-1; ++i)
        m_stackData[i] = m_stackData[i+1]; 
      m_size--;

      if (m_stackData.m_length >= 3 * m_size && m_stackData.m_length > initArraySize)
        resize();
      return tmp;
    }
    
    T Pop() {
      return Remove(m_size-1);
    }

    void TestPrint() {
      std::cout << "\nElements are: ";
      for (size_t i=0; i<m_size; ++i)
        std::cout << m_stackData[i] << " ";
      std::cout << std::endl;
    }

  private:
    void resize(size_t arr_len=0) {
      size_t new_size = 2 * (m_size+arr_len);
      new_size = (new_size > 1 ? new_size : 1);
      Array<T> tmp(new_size);     // tmp对象是在栈上，而其成员是在堆中产生
      for (size_t i=0; i<m_size; ++i)
        tmp[i] = m_stackData[i];
      m_stackData = tmp;
    }

  private:
    Array<T> m_stackData;
    size_t   m_size;        // 实际元素个数
  };




}

#endif