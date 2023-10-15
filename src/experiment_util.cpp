#include "experiment_util.hpp"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <cstdlib>

void write_arr_to_file(const Point<lab_point_type>* arr, const size_t& n, const char* path)
{
  size_t i;
  std::ofstream out(path);
  if (out.is_open())
  {
    out << n << '\n';
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

void do_experiment(const size_t& q, const size_t& w, const size_t& n, std::ofstream& outA, std::ofstream& outB)
{
  // alg1 (A) to out1, alg2 (B) to out2
  // file1: q w n T_A1(n) T_A2(n)
  // file2: q w n T_B1(n) T_B2(n)
  // but std::cout : q w n T_A1(n) T_A2(n) T_B1(n) T_B2(n)
  Point<lab_point_type>* arrA1 = generate_array_type_1(q, w, n), *arrA2 = generate_array_type_2(q, w, n);
  Point<lab_point_type>* arrB1 = new Point<lab_point_type>[n], *arrB2 = new Point<lab_point_type>[n];
  std::copy(arrA1, arrA1+n, arrB1);
  std::copy(arrA2, arrA2+n, arrB2);
  outA << q << ' ' << w << ' ' << n;
  outB << q << ' ' << w << ' ' << n;
#ifdef EXPERIMENT_PRINT
  std::cout << q << ' ' << w << ' ' << n;
#endif

  measure_time(arrA1, n, outA, conv_sort_3_heap);
  measure_time(arrA2, n, outA, conv_sort_3_heap);
  measure_time(arrB1, n, outB, conv_sort_5_merge);
  measure_time(arrB2, n, outB, conv_sort_5_merge);

  outA << '\n';
  outB << '\n';
#ifdef EXPERIMENT_PRINT
  std::cout << '\n';
#endif

  delete[] arrA1;
  delete[] arrA2;
  delete[] arrB1;
  delete[] arrB2;
}

Point<lab_point_type>* generate_array_type_1(const size_t& q, const size_t& w, const size_t& n)
{
  const lab_point_type rand_max_lab = static_cast<lab_point_type>(RAND_MAX);
  Point<lab_point_type>* arr = new Point<lab_point_type>[n];
  for (size_t i = 0; i < n; i++)
  {
    lab_point_type x, y;
    x = static_cast<lab_point_type>(std::rand()) / rand_max_lab * w;
    y = static_cast<lab_point_type>(std::rand()) / rand_max_lab * q;
    arr[i] = Point<lab_point_type>(x, y);
  }
  return arr;
}

Point<lab_point_type>* generate_array_type_2(const size_t& q, const size_t& w, const size_t& n)
{
  const lab_point_type rand_max_lab = static_cast<lab_point_type>(RAND_MAX);
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
      x = static_cast<lab_point_type>(rand_x) / rand_max_lab * w;
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
      y = static_cast<lab_point_type>(rand_y) / rand_max_lab * q;
    }
  }
  return arr;
}

void measure_time(Point<lab_point_type>* arr, const size_t& n, std::ofstream& out, size_t (*conv_sort_func)(Point<lab_point_type>*, const size_t&))
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
