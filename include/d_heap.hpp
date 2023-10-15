#ifndef __LAB_D_HEAP_OLD_HPP__
#define __LAB_D_HEAP_OLD_HPP__

#include <cstddef>
#include <algorithm>

template<class T>
class D_Heap
{
private:
  size_t d;
  T* heap;
  size_t n;
public:
  D_Heap(T* arr = nullptr, const size_t& n = 0, const size_t& d = 3);
  void bubble_up(const size_t& i);
  void bubble_down(const size_t& i);
  void bubble_down(const size_t& i, const size_t& n);
  size_t get_max_child_index(const size_t& i) const;
  T* get_heap(void) const { return this->heap; }
  void set_array(T* arr, const size_t& n) { this->heap = arr; this->n = n; this->init(); }
  void set_d(const size_t& d) { this->d = d; this->init(); };
  size_t get_d(void) const { return this->d; }
  void init(void);
};

template<class T>
inline D_Heap<T>::D_Heap(T* arr, const size_t& n, const size_t& d)
{
  this->d = d;
  this->set_array(arr, n);
}

template<class T>
inline void D_Heap<T>::bubble_up(const size_t& i)
{
  size_t parent_i = (i - 1) / this->d, tmp = i;
  while (tmp > 0 && this->heap[tmp] > this->heap[parent_i])
  {
    std::swap<T>(this->heap[tmp], this->heap[parent_i]);
    tmp = parent_i;
    parent_i = (tmp - 1) / this->d;
  }
}

template<class T>
inline void D_Heap<T>::bubble_down(const size_t& i)
{
  size_t child_i = this->get_max_child_index(i), tmp = i;
  bool cond = tmp*this->d+1 < this->n;
  while (cond && this->heap[tmp] < this->heap[child_i])
  {
    std::swap<T>(this->heap[child_i], this->heap[tmp]);
    tmp = child_i;
    cond = tmp*this->d+1 < this->n;
    if (cond)
      child_i = this->get_max_child_index(tmp);
  }
}

template<class T>
inline void D_Heap<T>::bubble_down(const size_t& i, const size_t& n)
{
  size_t tmp = this->n;
  this->n = n;
  this->bubble_down(i);
  this->n = tmp;
}

template<class T>
inline size_t D_Heap<T>::get_max_child_index(const size_t &i) const
{
  size_t start_child_i = i * this->d + 1;
  size_t child_e_count = this->n - start_child_i, max_child_i = start_child_i;
  if (child_e_count > this->d)
    child_e_count = this->d;
  child_e_count += start_child_i;
  for (size_t j = start_child_i; j < child_e_count; j++)
  {
    if (this->heap[j] > this->heap[max_child_i])
      max_child_i = j;
  }
  return max_child_i;
}

template<class T>
inline void D_Heap<T>::init()
{
  size_t to = (n-1) / this->d;
  for (size_t i = 0; i < to; i++)
  {
    this->bubble_down(to-i-1);
  }
}

#endif
