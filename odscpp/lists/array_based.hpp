/*
* @ File  : array_stack.hpp 
* @ Author：wangzs
* @ Date  ：2013/07/19 0:52 am
*/

#ifndef ARRAY_STACK_HPP
#define ARRAY_STACK_HPP

#include <algorithm>
#include <cmath>
#include <cassert>

#include "../common/core_parts.hpp"

namespace wzs {
  /*
  * @ Class    ：ArrayStack   [An ArrayStack implements the List interface.]
  * @ Interface：Get(i) / Set(i, val) / Add(i, val) / Push(val) / Remove(i) / Pop() / Size()
  */
  template <typename T>
  class ArrayStack {
  public:
    ArrayStack()
      :m_size(0), m_stackData(5) { }

    inline size_t Size() const{
      return m_size;
    }

    inline T& Get(size_t index) {
      assert(index <= m_size);
      return m_stackData[index];
    }
    inline const T& Get(size_t index) const {
      assert(index <= m_size);
      return m_stackData[index];
    }

    inline T Set(size_t index, const T& val) {     // 返回原有index位置处的值
      assert(index <= m_size);
      T tmp = m_stackData[index];
      m_stackData[index] = val;
      return tmp;
    }

    inline void Add(size_t index, const T& val) {
      assert(index <= m_size);
      if (m_size + 1 > m_stackData.m_length)
        resize();
      for (size_t i=m_size; i>index; --i)
        m_stackData[i] = m_stackData[i-1];
      m_stackData[index] = val;
      m_size++;
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

      if (m_stackData.m_length >= 3 * m_size)
        resize();
      return tmp;
    }
    
    T Pop() {
      return Remove(m_size-1);
    }

  private:
    void resize() {
      size_t new_size = 2 * m_size;
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

  /*
  * @ Class    ：FastArrayStack   [An FastArrayStack like ArrayStack, just used STL.]
  * @ Interface：Get(i) / Set(i, val) / Add(i, val) / Push(val) / Remove(i) / Pop() / Size()
  * @ Add-time ：2013/07/19 20:04
  */
  template <typename T> 
  class FastArrayStack {
  public:
    FastArrayStack()
      : m_stackData(5), m_size(0) { }

    inline size_t Size() const{
      return m_size;
    }

    inline T& Get(size_t index) {
      assert(index <= m_size);
      return m_stackData[index];
    }
    inline const T& Get(size_t index) const {
      assert(index <= m_size);
      return m_stackData[index];
    }

    inline T Set(size_t index, const T& val) {
      assert(index <= m_size);
      T tmp = m_stackData[index];     // 返回原有index位置处的值
      m_stackData[index] = val;
      return tmp;
    }

    inline void Add(size_t index, const T& val) {
      assert(index <= m_size);
      if (m_size + 1 > m_stackData.m_length)
        resize();
      m_size++;
      std::copy_backward(&m_stackData[index], &m_stackData[m_size-1], &m_stackData[m_size]);
      m_stackData[index] = val;
    }

    void Push(const T& val) {
      Add(m_size, val);
    }

    inline T Remove(size_t index) {
      assert(index < m_size);
      T tmp = m_stackData[index];
      std::copy(&m_stackData[index+1], &m_stackData[m_size], &m_stackData[index]);
      m_size--;

      if (m_stackData.m_length >= 3 * m_size)
        resize();
      return tmp;
    }

    T Pop() {
      return Remove(m_size-1);
    }

  private:
    void resize() {
      size_t new_size = 2 * m_size;
      new_size = (new_size > 1 ? new_size : 1);
      Array<T> tmp(new_size);     // tmp对象是在栈上，而其成员是在堆中产生
      std::copy(&m_stackData[0], &m_stackData[m_size], &tmp[0]);
      m_stackData = tmp;
    }


  private:
    Array<T> m_stackData;
    size_t   m_size;
  };

  /*
  * @ Class    ：ArrayQueue   
  *              [An ArrayQueue using modular arithmetic to implement circular array
  *               ArrayQueue is a FIFO queue.]
  * @ Interface：Get(i) / Set(i, val) / Add(i, val) / Push(val) / Remove(i) / Pop() / Size()
  * @ Add-time ：2013/07/19 20:04
  */
  template <typename T>
  class ArrayQueue {
  public:
    ArrayQueue() 
      :m_queueData(5), m_head(0), m_len(0) { }

    inline size_t Size() const {
      return m_len;
    }

    inline T& Get(size_t index) {
      assert(0 <= index && index < m_queueData.m_length);
      return m_queueData[(index + m_head) % m_queueData.m_length];
    }
    inline const T& Get(size_t index) const {
      assert(0 <= index && index < m_queueData.m_length);
      return m_queueData[(index + m_head) % m_queueData.m_length];
    }

    inline T Set(size_t index, const T& val) {     // 返回原有index位置处的值
      assert(0 <= index && index < m_queueData.m_length);
      T tmp = m_queueData[(index + m_head) % m_queueData.m_length];
      m_queueData[(index + m_head) % m_queueData.m_length] = val;
      return tmp;       // 若T非内置类型，会两次调用T的构造函数，会影响效率
    }

    inline void Add(const T& val) {
      if (m_len + 1 > m_queueData.m_length)
        resize();
      m_queueData[(m_head + m_len) % m_queueData.m_length] = val;
      m_len++;
    }

    inline T Remove() {
      assert(m_len > 0);
      T tmp = m_queueData[m_head];
      m_head = (m_head + 1) % m_queueData.m_length;
      m_len--;

      if (m_queueData.m_length > 3 * m_len)
        resize();
      return tmp;
    }

  private:
    void resize() {
      size_t new_size = 2 * m_len;
      new_size = new_size ? new_size : 1;
      Array<T> tmp(new_size);
      for (size_t i=0; i<m_len; ++i)
        tmp[i] = m_queueData[(i + m_head) % m_queueData.m_length];
      m_queueData = tmp;
      m_head = 0;
    }
  private:
    Array<T> m_queueData;
    size_t   m_head;      // 指向ArrayQueue的头
    size_t   m_len;       // ArrayQueue的元素个数
  };





}

#endif
