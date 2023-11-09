// TODO: delete

#include <iostream>
#include <time.h>
#include "experiment_util.hpp"

static inline void separate()
{
  std::cout << "-----------------------------------------------\n";
}

void test1()
{
  Point<lab_point_type> arr[] = {Point<lab_point_type>(10, 20), Point<lab_point_type>(60, 160), Point<lab_point_type>(110, 20), Point<lab_point_type>(-60, 80), Point<lab_point_type>(70, 140), Point<lab_point_type>(50, 50), Point<lab_point_type>(-100, -30), Point<lab_point_type>(-45, 50), Point<lab_point_type>(80, 90), Point<lab_point_type>(180, 10), Point<lab_point_type>(-100, 100), Point<lab_point_type>(40, -150), Point<lab_point_type>(-10, -10), Point<lab_point_type>(20, -50), Point<lab_point_type>(-30, -50)};
  //std::cout << (sizeof(arr) / sizeof(Point<lab_point_type>)) << '\n'; // test just in case
  size_t m = conv_sort_3_heap(arr, sizeof(arr) / sizeof(Point<lab_point_type>));
  std::cout << "Expected: (-100, -30) (40, -150) (180, 10) (60, 160) (-100, 100) \n";
  std::cout << "Actual:   ";
  for (size_t i = 0; i < m; i++)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  separate();
}

void test2()
{
  int arr[] = { 108, 16, 23, 42, 4, 121, 8, 15 };
  size_t sz = sizeof(arr)/sizeof(int);
  D_Heap<int>(arr, sz, 3);
  for (size_t i = 0; i < sz; i++)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  separate();
}

void test3()
{
  int arr[] = { 108, 16, 23, 42, 4, 121, 8, 39, 21, 11, 50, 3, 43, 15 };
  size_t sz = sizeof(arr)/sizeof(int);
  d_heap_sort<3, int>(arr, sz);
  for (size_t i = 0; i < sz; i++)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  separate();
}

void test4()
{
  int arr[] = { 108, 16, 23, 42, 4, 121, 8, 39, 21, 11, 50, 3, 43, 15 };
  size_t sz = sizeof(arr)/sizeof(int);
  k_merge_sort<5, int>(arr, sz);
  for (size_t i = 0; i < sz; i++)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  separate();
}

void test5()
{
  std::srand(time(0));
  std::cout << "Rand from -100000 to +100000 -> " << rand_range(-100000.0, 100000.0) << '\n';
}

int main()
{
  test1();
  test2();
  test3();
  test4();
  test5();
  std::cout << "all tests done!\n";
  return 0;
}
