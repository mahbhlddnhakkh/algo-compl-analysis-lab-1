#ifndef __LAB_K_MERGE_HPP__
#define __LAB_K_MERGE_HPP__

#include <cstddef>

template<class T>
void bubble_sort(T* arr, const size_t& n, const size_t& start);

template<class T>
class K_Merge
{
private:
  size_t k;
  T* arr;
  size_t n;
public:
  K_Merge(T* arr = nullptr, const size_t& n = 0, const size_t& k = 3);
  void sort();
  void sort_merge(const size_t& i, const size_t& j);
  void merge(const size_t& i, const size_t& m, const size_t& j);
  T* get_array(void) { return this->arr; }
  void set_array(T* arr, const size_t& n) { this->arr = arr; this->n = n; }
  void set_k(const size_t& k) { this->k = k; };
  size_t get_k(void) const { return this->k; }
};

template<class T>
inline K_Merge<T>::K_Merge(T* arr, const size_t& n, const size_t& k)
{
  this->set_k(k);
  this->set_array(arr, n);
}

template<class T>
inline void K_Merge<T>::sort()
{
  this->sort_merge(0, this->n-1);
}

template<class T>
inline void K_Merge<T>::sort_merge(const size_t &i, const size_t &j)
{
  if (j-i+1 <= this->k)
  {
    bubble_sort<T>(this->arr, j+1, i);
  }
  else
  {
    size_t step = (j-i+1) / this->k, numb;
    for (numb = 0; numb < this->k-1; numb++)
    {
      this->sort_merge(i+step*numb, i+step*(numb+1)-1);
    }
    this->sort_merge(i+numb*step, j);
    for (numb = 0; numb < this->k-2; numb++)
    {
      this->merge(i, i+step*(numb+1)-1, i+step*(numb+2)-1);
    }
    this->merge(i, i+step*(numb+1)-1, j);
  }
}

template<class T>
inline void K_Merge<T>::merge(const size_t &i, const size_t &m, const size_t &j)
{
  const size_t b_sz = j-i+1;
  T* b = new T[b_sz];
  size_t i1 = i, i2 = m+1, i3 = 0;
  while (i3 < b_sz)
  {
    if (i1 <= m && i2 <= j && this->arr[i1] <= this->arr[i2] || i2 == j+1)
    {
      b[i3++] = this->arr[i1++];
    }
    else
    {
      b[i3++] = this->arr[i2++];
    }
  }
  for (i3 = i; i3 < j+1; i3++)
  {
    this->arr[i3] = b[i3-i];
  }
  delete[] b;
}

#endif