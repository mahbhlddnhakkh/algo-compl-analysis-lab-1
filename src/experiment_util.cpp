#include "experiment_util.hpp"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <cstdlib>

double rand_range(const double& from, const double& to)
{
  return rand_range(std::rand(), from, to);
}

double rand_range(const int& num, const double& from, const double& to)
{
  // https://stackoverflow.com/a/2704552
  return ((static_cast<double>(num) / static_cast<double>(RAND_MAX)) * (to - from)) + from;
}

void write_arr_to_file(const Point<lab_point_type>* arr, const size_t& n, const char* path)
{
  size_t i;
  std::ofstream out(path);
  if (out.is_open())
  {
    out << n << '\n';
#ifdef EXPERIMENT_PRINT
    std::cout << n << '\n';
#endif
    for (i = 0; i < n; i++)
    {
      out << arr[i] << '\n';
#ifdef EXPERIMENT_PRINT
      std::cout << arr[i] << ' ';
#endif
    }
    out.close();
#ifdef EXPERIMENT_PRINT
    std::cout << '\n';
#endif
  }
  else
  {
    std::cout << path << " unable to write\n";
#ifdef EXPERIMENT_PRINT
    for (i = 0; i < n; i++)
    {
      std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
#endif
  }
}

void do_experiment(const size_t& q, const size_t& w, const size_t& n, std::ofstream& out)
{
  // q w n T1_A(n) T1_B(n) T2_A(n) T2_B(n)
  // A - 3-heap sort, B - 5-merge sort
  // T1_X(n) - random array type 1, T2_X(n) - random array type 2
  // time is in ms
  Point<lab_point_type>* arr1A = generate_array_type_1(q, w, n), *arr2A = generate_array_type_2(q, w, n);
  Point<lab_point_type>* arr1B = new Point<lab_point_type>[n], *arr2B = new Point<lab_point_type>[n];
  std::copy(arr1A, arr1A+n, arr1B);
  std::copy(arr2A, arr2A+n, arr2B);
  out << q << ' ' << w << ' ' << n;
#ifdef EXPERIMENT_PRINT
  std::cout << q << ' ' << w << ' ' << n;
#endif

  measure_conv_time(arr1A, n, out, conv_sort_3_heap);
  measure_conv_time(arr1B, n, out, conv_sort_5_merge);
  measure_conv_time(arr2A, n, out, conv_sort_3_heap);
  measure_conv_time(arr2B, n, out, conv_sort_5_merge);

  out << '\n';
#ifdef EXPERIMENT_PRINT
  std::cout << '\n';
#endif

  delete[] arr1A;
  delete[] arr1B;
  delete[] arr2A;
  delete[] arr2B;
}

Point<lab_point_type>* generate_array_type_1(const size_t& q, const size_t& w, const size_t& n)
{
  Point<lab_point_type>* arr = new Point<lab_point_type>[n];
  for (size_t i = 0; i < n; i++)
  {
    lab_point_type x, y;
    x = static_cast<lab_point_type>(rand_range(0.0, static_cast<double>(w)));
    y = static_cast<lab_point_type>(rand_range(0.0, static_cast<double>(q)));
    arr[i] = Point<lab_point_type>(x, y);
  }
  return arr;
}

Point<lab_point_type>* generate_array_type_2(const size_t& q, const size_t& w, const size_t& n)
{
  const int rand_max_half = RAND_MAX / 2;
  Point<lab_point_type>* arr = new Point<lab_point_type>[n];
  for (size_t i = 0; i < n; i++)
  {
    bool fix_y = std::rand() % 2 == 1;
    const int rand_x = std::rand();
    const int rand_y = std::rand();
    lab_point_type x, y;
    if (fix_y)
    {
      if (rand_y >= rand_max_half)
      {
        y = static_cast<lab_point_type>(q);
      }
      else
      {
        y = static_cast<lab_point_type>(0);
      }
      x = static_cast<lab_point_type>(rand_range(rand_x, 0.0, static_cast<double>(w)));
    }
    else
    {
      if (rand_x >= rand_max_half)
      {
        x = static_cast<lab_point_type>(w);
      }
      else
      {
        x = static_cast<lab_point_type>(0);
      }
      y = static_cast<lab_point_type>(rand_range(rand_y, 0.0, static_cast<double>(q)));
    }
    arr[i] = Point<lab_point_type>(x, y);
  }
  return arr;
}

void measure_conv_time(Point<lab_point_type>* arr, const size_t& n, std::ofstream& out, size_t (*conv_sort_func)(Point<lab_point_type>*, const size_t&))
{
  // https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
  auto start = std::chrono::high_resolution_clock::now();
  conv_sort_func(arr, n);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  out << ' ' << duration.count();
#ifdef EXPERIMENT_PRINT
  std::cout << ' ' << duration.count();
#endif
}
