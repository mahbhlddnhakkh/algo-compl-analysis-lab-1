#include "experiment_util.hpp"
#ifdef EXPERIMENT_PRINT
#include <iostream>
#endif
#include <fstream>
#include <sstream>

int main(const int argc, const char* argv[])
{
  const char* input_path = (argc > 1) ? argv[1] : "input1.txt";
  const char* output_pathA = (argc > 2) ? argv[2] : "output1.A.txt";
  const char* output_pathB = (argc > 3) ? argv[3] : "output1.B.txt";
  const char sep = ' ';
  std::fstream f(input_path);
  Point<lab_point_type>* arr1 = nullptr, *arr2 = nullptr;
  size_t n = 0, i = 0, m;
  if (f.is_open())
  {
    std::stringstream sstream;
    std::string line;
    if (!std::getline(f, line))
    {
      f.close();
      throw std::string(input_path) + " cannot be empty";
    }
    sstream << line;
    sstream >> n;
    sstream.clear();
    if (n <= 0)
    {
      f.close();
      throw line + " cannot be 0 because it's a size";
    }
    arr1 = new Point<lab_point_type>[n];
    while(std::getline(f, line) && i < n)
    {
      size_t sz = line.length();
      if (sz != 0)
      {
        lab_point_type x, y;
        size_t j = 0;
        while (j < sz && line[j] != sep)
        {
          sstream << line[j];
          j++;
        }
        j++;
        sstream >> x;
        sstream.clear();
        while (j < sz)
        {
          sstream << line[j];
          j++;
        }
        sstream >> y;
        sstream.clear();
        arr1[i] = Point<lab_point_type>(x, y);
#ifdef EXPERIMENT_PRINT
        std::cout << arr1[i] << ' ';
#endif
        i++;
      }
    }
#ifdef EXPERIMENT_PRINT
    std::cout << '\n';
#endif
    f.close();
  }
  else
  {
    throw std::string(input_path) + " not found";
  }
  arr2 = new Point<lab_point_type>[n];
  std::copy(arr1, arr1+n, arr2);
  m = conv_sort_3_heap(arr1, n);
  write_arr_to_file(arr1, m, output_pathA);
  m = conv_sort_5_merge(arr2, n);
  write_arr_to_file(arr2, m, output_pathB);
  if (arr1 != nullptr)
    delete[] arr1;
  if (arr2 != nullptr)
    delete[] arr2;
  return 0;
}
