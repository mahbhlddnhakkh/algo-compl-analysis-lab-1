#ifndef __LAB_UTILITY_HPP__
#define __LAB_UTILITY_HPP__

#include "d_heap.hpp"
#include "k_merge.hpp"
#include <cstddef>
#include <limits>
#include <ostream>

template<class T>
class Point;

template<class T>
std::ostream& operator<<(std::ostream& out, const Point<T>& p);

template<class T>
inline T det(const Point<T>& p1, const Point<T>& p2)
{
  return (p1.x*p2.y - p1.y*p2.x);
}

template<class T>
inline bool is_zero(const T& x)
{
  return std::abs(x) <= std::numeric_limits<T>::epsilon();
}

template<class T>
inline bool points_le(const Point<T>& p1, const Point<T>& p2)
{
  T tmp = det<T>(p1, p2);
  return tmp > T(0) || (is_zero<T>(tmp) && p1.abs_sq() < p2.abs_sq());
}

template<class T>
inline void bubble_sort(T* arr, const size_t& n)
{
  for (size_t i = 0; i < n; i++)
  {
    bool swapped = false;
    for (size_t j = 0; j < n-i-1; j++)
    {
      if (arr[j] > arr[j+1])
      {
        std::swap<T>(arr[j], arr[j+1]);
        swapped = true;
      }
    }
    if (swapped == false)
      break;
  }
}

template<class T>
inline void bubble_sort(T* arr, const size_t& n, const size_t& start)
{
  bubble_sort<T>(arr+start, n-start);
}

template<size_t d, class T>
inline void d_heap_sort(T* arr, const size_t& n)
{
  D_Heap<T> heap(arr, n, d);
  size_t j = n;
  for (size_t i = 0; i < n-1; i++)
  {
    std::swap<T>(arr[0], arr[n-1-i]);
    j--;
    heap.bubble_down(0, j);
  }
}

template<size_t k, class T>
inline void k_merge_sort(T* arr, const size_t& n)
{
  K_Merge<T> merge(arr, n, k);
  merge.sort();
}

#endif
