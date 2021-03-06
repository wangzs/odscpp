/*
================================================
* @ filename : array_stack.hpp 
* @ author   ：wangzs
* @ date     ：2013/07/19 0:52 am
* @ describe : Open Data Structure - Chapter 2
*      ArrayStack / ArrayQueue / ArrayDeque / 
*      DualArrayDeque / RootishArrayStack
================================================
*/

#ifndef OSDCPP_ARRAYSTACK_HPP
#define OSDCPP_ARRAYSTACK_HPP

#include <algorithm>
#include <cmath>
#include <cassert>

#ifdef _DEBUG
#include <iostream>
#endif

#include "../common/core_parts.hpp"

namespace wzs {
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

      if (m_stackData.m_length >= 3 * m_size && m_stackData.m_length > initArraySize)
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
      : m_stackData(initArraySize), m_size(0) { }

    inline size_t Size() const{
      return m_size;
    }
    inline size_t Capacity() const {
      return m_stackData.m_length;
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

    inline T Set(size_t index, const T& val) {
      assert(index < m_size);
      T tmp = m_stackData[index];     // 返回原有index位置处的值
      m_stackData[index] = val;
      return tmp;
    }

    inline void Add(size_t index, const T& val) {
      assert(index <= m_size);
      if (m_size + 1 > m_stackData.m_length)
        resize();
      if (index != m_size)
        std::copy_backward(&m_stackData[index], &m_stackData[m_size-1], &m_stackData[m_size]);
      m_stackData[index] = val;
      m_size++;
    }

    void Push(const T& val) {
      Add(m_size, val);
    }

    inline T Remove(size_t index) {
      assert(index < m_size);
      T tmp = m_stackData[index];
      std::copy(&m_stackData[index+1], &m_stackData[m_size], &m_stackData[index]);
      m_size--;

      if (m_stackData.m_length >= 3 * m_size && m_stackData.m_length > initArraySize)
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
      std::copy(&m_stackData[0], &m_stackData[m_size-1], &tmp[0]);
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
      :m_queueData(initArraySize), m_head(0), m_len(0) { }

    inline size_t Size() const {
      return m_len;
    }
    inline size_t Capacity() const {
      return m_queueData.m_length;
    }

    inline Array<T>& GetElem() {
      return m_queueData;
    }

    inline T& Get(size_t index) {
      assert(index < m_len);
      return m_queueData[(index + m_head) % m_queueData.m_length];
    }
    inline const T& Get(size_t index) const {
      assert(index < m_len);
      return m_queueData[(index + m_head) % m_queueData.m_length];
    }

    inline T Set(size_t index, const T& val) {     // 返回原有index位置处的值
      assert(index < m_len);
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

      if (m_queueData.m_length > 3 * m_len && m_queueData.m_length > initArraySize)
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

  protected:
    Array<T> m_queueData;
    size_t   m_head;      // 指向ArrayQueue的头
    size_t   m_len;       // ArrayQueue的元素个数
  };


    /*
  * @ Class    ：ArrayDeque   
  *              [An ArrayDeque allows for efficient addition and remove at both ends.
  *               添加元素的位置在已有数组长度的前半段，则添加位置的前面元素前移；否则后移]
  * @ Interface：Get(i) / Set(i, val) / Add(i, val) / Remove(i) / Size()
  * @ Add-time ：2013/07/24 23:04
  */
  template <typename T>
  class ArrayDeque {
  public:
    ArrayDeque()
      :m_dequeData(initArraySize), m_head(0), m_len(0) { }

    inline size_t Size() const {
      return m_len;
    }
    inline size_t Capacity() const {
      return m_dequeData.m_length;
    }

    inline Array<T>& GetElem() {
      return m_dequeData;
    }

    inline T& Get(size_t index) {
      assert(index < m_len);
      return m_dequeData[(index + m_head) % m_dequeData.m_length];
    }
    inline const T& Get(size_t index) const {
      assert(index < m_len);
      return m_dequeData[(index + m_head) % m_dequeData.m_length];
    }

    inline T Set(size_t index, const T& val) {
      assert(index < m_len);
      size_t actureIndex = (m_head + index) % m_dequeData.m_length;
      T tmp = m_dequeData[actureIndex];
      m_dequeData[actureIndex] = val;
      return tmp;
    }

    inline void Add(size_t index, const T& val) {     // index 代表插入到已有数组中的的位置
      assert(index <= m_len);
      if (m_len + 1 > m_dequeData.m_length)
        resize();

      size_t halfDequeLen = m_len >> 1;
      size_t arrLen = m_dequeData.m_length;
      if (index <= halfDequeLen) { // 插入元素在数组前半段
        m_head = (m_head == 0) ? (m_dequeData.m_length-1) : (m_head-1);
        for (size_t i=0; i<=index; ++i)
          m_dequeData[(m_head + i + arrLen - 1) % arrLen] = m_dequeData[(m_head + i) % arrLen];
      }
      else {
        for (size_t i=m_len-index; i>0; --i)
          m_dequeData[(m_head + index + i) % arrLen] = m_dequeData[((m_head + index + i - 1) % arrLen)];
      }
      m_dequeData[(m_head + index) % arrLen] = val;
      m_len++;
    }

    inline T Remove(size_t index) {
      assert(index < m_len);
      T tmp = m_dequeData[(m_head + index) % m_dequeData.m_length];
      size_t halfDequeLen = m_len >> 1;
      if (index <= halfDequeLen) {    // 删除的元素在前半段
        for (size_t i=index; i>0; --i)
          m_dequeData[(m_head + i) % m_dequeData.m_length] = m_dequeData[(m_head + i - 1) % m_dequeData.m_length];
        m_head = (m_head+1) % m_dequeData.m_length;
      }
      else {
        for (size_t i=0; i<m_len-index; ++i)
          m_dequeData[(m_head + index + i) % m_dequeData.m_length] = 
                m_dequeData[(m_head + index + i + 1) % m_dequeData.m_length];
      }
      m_len--;
      if (3*m_len < m_dequeData.m_length && m_dequeData.m_length > initArraySize)
        resize();

      return tmp;
    }

#ifdef _DEBUG
    void TestPrint() {
      std::cout << "memory loction: \n";
      for (size_t i=0; i<m_dequeData.m_length; ++i) {
        if ( (i >= m_head && i<(m_head+m_len)) || ((m_head > (m_head+m_len)%m_dequeData.m_length) && (i>=m_head || i <(m_head+m_len)%m_dequeData.m_length)) )
          std::cout << m_dequeData[i] << " ";
        else
          std::cout << "* ";
      }
      std::cout << std::endl;
    }
#endif


  private:
    void resize() {
      size_t new_size = 2 * m_len;
      new_size = new_size ? new_size : 1;
      Array<T> tmp(new_size);
      for (size_t i=0; i<m_len; ++i)
        tmp[i] = m_dequeData[(i + m_head) % m_dequeData.m_length];
      m_dequeData = tmp;
      m_head = 0;
    }

  private:
    Array<T> m_dequeData;
    size_t m_head;      // ArrayDeque的头
    size_t m_len;       // ArrayDeque的元素个数
  };

  /*
  * @ Class    ：DualArrayDeque   
  *              [An DualArrayDeque using two ArrayStacks achieves the same performance bounds as ArrayDeque.]
  * @ Interface：Get(i) / Set(i, val) / Add(i, val) / Remove(i) / Size()
  * @ Add-time ：2013/07/27 18:47
  */
  template <typename T>
  class DualArrayDeque {
  public:
    DualArrayDeque() 
      : m_frontDeque(), m_backDeque(){ }
    
    inline size_t Size() const {
      return m_frontDeque.Size() + m_backDeque.Size();
    }
    inline size_t Capacity() const {
      return m_frontDeque.Capacity() + m_backDeque.Capacity();
    }

    T& Get(size_t index) {
      assert(index < m_frontDeque.Size() + m_backDeque.Size());
      if (index < m_frontDeque.Size())
        return m_frontDeque.Get(m_frontDeque.Size() - index - 1);
      else
        return m_backDeque.Get(index - m_frontDeque.Size());
    }

    const T& Get(size_t index) const {
      assert(index < m_frontDeque.Size() + m_backDeque.Size());
      if (index < m_frontDeque.Size())
        return m_frontDeque.Get(m_frontDeque.Size - index - 1);
      else
        return m_backDeque.Get(index - m_frontDeque.Size());
    }

    T Set(size_t index, const T& val) {
      assert(index < m_frontDeque.Size() + m_backDeque.Size());
      if (index < m_frontDeque.Size()) 
        return m_frontDeque.Set(m_frontDeque.Size() - index - 1, val);
      else 
        return m_backDeque.Set(index - m_frontDeque.Size(), val);
    }

    void Add(size_t index, const T& val) {
      assert(index <= m_frontDeque.Size() + m_backDeque.Size());
      if (m_frontDeque.Size() == 0)
        m_frontDeque.Add(0, val);
      else if (m_backDeque.Size() == 0)
        m_backDeque.Add(0, val);
      else if (index < m_frontDeque.Size()) 
        m_frontDeque.Add(m_frontDeque.Size() - index - 1, val);
      else
        m_backDeque.Add(index - m_frontDeque.Size(), val);
      balance();
    }

    T Remove(size_t index) {
      assert(index < m_frontDeque.Size() + m_backDeque.Size());
      T tmp;
      if (index < m_frontDeque.Size())
        tmp = m_frontDeque.Remove(m_frontDeque.Size() - index - 1);
      else
        tmp = m_backDeque.Remove(index - m_frontDeque.Size());
      balance();
      return tmp;
    }

#ifdef _DEBUG
    void TestPrint() {
      std::cout << "memory loction: \n";
      for (int i=m_frontDeque.Capacity()-1; i>=0; --i) {
        if (i < m_frontDeque.Size())
          std::cout << m_frontDeque.GetElem()[i] << " ";
        else
          std::cout << "* ";
      }
      for (size_t i=0; i<m_backDeque.Capacity(); ++i) {
        if (i < m_backDeque.Size())
          std::cout << m_backDeque.GetElem()[i] << " ";
        else
          std::cout << "* ";
      }
      std::cout << std::endl;
    }
#endif

  private:
    void balance() {
      if ((3 * m_frontDeque.Size() < m_backDeque.Size() && m_frontDeque.Size() > 0)||
        (3 * m_backDeque.Size() < m_frontDeque.Size() && m_backDeque.Size() > 0) ) {
        size_t len = m_frontDeque.Size() + m_backDeque.Size();   // 总元素数目
        size_t len_half = len >> 1;
        size_t front_size = 2*len_half > 1 ? 2*len_half : 1;
        Array<T> front_tmp(front_size);
        for (size_t i=0; i<len_half; ++i)         // 复制Deque前半段的值
          front_tmp[len_half - i - 1] = Get(i);
            
        size_t len_other = len - len_half; 
        size_t back_size = 2*len_other > 1 ? 2*len_other : 1;
        Array<T> back_tmp(back_size);
        for (size_t i=0; i<len_other; ++i)
          back_tmp[i] = Get(len_half + i);

        m_frontDeque.GetElem() = front_tmp;
        m_frontDeque.SetSize(front_size);
        m_backDeque.GetElem() = back_tmp;
        m_backDeque.SetSize(back_size); 
      }
    }

  private:
    ArrayStack<T> m_frontDeque ;    // 以两个ArrayStack实现Deque，tail<-----head(front) | (back)head---->tail
    ArrayStack<T> m_backDeque; 
  };

  /*
  * @ Class    ：RootishArrayStack   
  *              [An RootishArrayStack addresses the problem of wasted space, it stores n elements using O(n^1/2).]
  * @ Interface：Get(i) / Set(i, val) / Add(i, val) / Remove(i) / Size()
  * @ Add-time ：2013/07/29 10:15
  */
  template <typename T>
  class RootishArrayStack {
  public:
    RootishArrayStack()
      : m_len(0), m_rootishBlocks() { }
    ~RootishArrayStack() {
      for (size_t i=0; i<m_rootishBlocks.Size(); ++i)
        delete [] m_rootishBlocks.Get(i);
    }

    inline T& Get(size_t index) {
      assert(index < m_len);
      size_t b = index2block(index);
      size_t j = index - b * (b + 1)/2;
      return m_rootishBlocks.Get(b)[j];
    }

    inline const T& Get(size_t index) const {
      assert(index < m_len);
      size_t b = index2block(index);
      size_t j = index - b * (b + 1)/2;
      return m_rootishBlocks.Get(b)[j];
    }

    inline T& Set(size_t index, const T& val) {
      assert(index < m_len);
      size_t b = index2block(index);
      size_t j = index - b * (b + 1)/2;
      T tmp = m_rootishBlocks.Get(b)[j];
      m_rootishBlocks.Get(b)[j] = val;
      return tmp;
    }
    
    void Add(size_t index, const T& val) {
      assert(index <= m_len);
      size_t r = m_rootishBlocks.Size();
      if (r*(r+1)/2 < m_len+1)
        grow();
      m_len++;
      for (int j=m_len-1; j>index; --j)
        Set(j, Get(j-1));
      Set(index, val);
    }

    T Remove(size_t index) {
      assert(index < m_len);
      T tmp = Get(index);
      for (size_t j = index; j<m_len-1; ++j) 
        Set(j, Get(j+1));
      m_len--;
      size_t r = m_rootishBlocks.Size();
      if ((r-1)*(r-2)/2 >= m_len) 
        shrink();
      return tmp;
    }

#ifdef _DEBUG
    void TestPrint() {
      std::cout << "memory loction: \n";
      for (size_t i=0; i<m_len; ++i)
        std::cout << Get(i) << " ";
      std::cout << std::endl;
    }
#endif

  private:
    size_t index2block(size_t index) {
      double db = (-3.0 + sqrt(9.0 + (index << 3))) / 2.0;    // b = -3 + (9 + 8i)^1/2
      size_t b = static_cast<size_t>(ceil(db));
      return b;
    }

    void grow() {
      m_rootishBlocks.Add(m_rootishBlocks.Size(), new T[m_rootishBlocks.Size() + 1]);
    }

    void shrink() {
      size_t r = m_rootishBlocks.Size();
      while (r>0 && (r-2)*(r-1)/2 >= m_len) {
        delete [] m_rootishBlocks.Remove(m_rootishBlocks.Size() - 1);
        r--;
      }
    }

  private:
    ArrayStack<T*> m_rootishBlocks;
    size_t         m_len;
  };


}

#endif
