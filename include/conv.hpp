#ifndef __LAB_CONV_HPP__
#define __LAB_CONV_HPP__

#include "point.hpp"
#include "utility.hpp"
#include <cstddef>

template<class T>
inline size_t conv_sort(Point<T>* a, const size_t& n, void (*sort_func)(Point<T>*, const size_t&))
{
  Point<T> c = a[0];
  size_t m = 0, i;
  for (i = 1; i < n; i++)
  {
    if (a[i].x < c.x || (is_zero(a[i].x - c.x) && a[i].y < c.y))
    {
      c = a[i];
      m = i;
    }
  }
  std::swap<Point<T>>(a[0], a[m]);
  m = 0;
  for (i = 0; i < n; i++)
    a[i] = a[i] - c;
  sort_func(a, n);
  for (i = 1; i < n; i++)
  {
  	if (a[i] != a[m])
  	{
		  while (m > 0 && det<T>(a[m] - a[m-1], a[i] - a[m]) < 0)
		    m--;
		  m++;
		  std::swap<Point<T>>(a[m], a[i]);
   	}
  }
  m++; // because it's the array size now
  for (i = 0; i < m; i++)
    a[i] = a[i] + c;
  return m;
}

#endif
