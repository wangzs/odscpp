/*
* @ File  : core_parts.hpp
* @ Author£ºwangzs
* @ Date  £º2013/07/19 0:40 am
*/
#include <cassert>
#include <cstddef>

#ifndef CORE_PARTS_HPP
#define CORE_PARTS_HPP

namespace wzs {
  template <typename T> 
  class Array {
  public:
    Array(size_t len) {
      m_length = len;
      m_data = new T[m_length];
    }

    ~Array() {
      if (m_data)
        delete [] m_data;
    }

    T& operator[](size_t index) {
      assert(0 <= index && index < m_length);
      return m_data[index];
    }
    const T& operator[](size_t index) const {
      assert(0 <= index && index <= m_length);
      return m_data[index];
    }
    
    Array<T>& operator=(Array<T>& b) {      // ×ªÒÆ¸³Öµ
      if (m_data != NULL) 
        delete [] m_data;
      m_data = b.m_data;
      b.m_data = NULL;
      m_length = b.m_length;

      return *this;
    }

  public:
    T*      m_data;
    size_t  m_length;
  };





}

#endif