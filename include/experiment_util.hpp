#ifndef __LAB_EXPERIMENT_UTILITY_HPP__
#define __LAB_EXPERIMENT_UTILITY_HPP__

#include "conv.hpp"
#include <fstream>

//#define EXPERIMENT_PRINT

typedef double lab_point_type;

inline size_t conv_sort_bubble(Point<lab_point_type>* a, const size_t& n)
{
  return conv_sort<lab_point_type>(a, n, bubble_sort<Point<lab_point_type>>);
}

inline size_t conv_sort_3_heap(Point<lab_point_type>* a, const size_t& n)
{
  return conv_sort<lab_point_type>(a, n, d_heap_sort<3, Point<lab_point_type>>);
}

inline size_t conv_sort_5_merge(Point<lab_point_type>* a, const size_t& n)
{
  return conv_sort<lab_point_type>(a, n, k_merge_sort<5, Point<lab_point_type>>);
}

double rand_range(const double& from, const double& to);

double rand_range(const int& num, const double& from, const double& to);

void write_arr_to_file(const Point<lab_point_type>* arr, const size_t& n, const char* path);

void do_experiment(const size_t& q, const size_t& w, const size_t& n, std::ofstream& out);

Point<lab_point_type>* generate_array_type_1(const size_t& q, const size_t& w, const size_t& n);

Point<lab_point_type>* generate_array_type_2(const size_t& q, const size_t& w, const size_t& n);

void measure_conv_time(Point<lab_point_type>* arr, const size_t& n, std::ofstream& out, size_t (*conv_sort_func)(Point<lab_point_type>*, const size_t&));

#endif
