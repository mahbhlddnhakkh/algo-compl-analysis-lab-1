#include "experiment_util.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

int main(const int argc, const char* argv[])
{
  const char* input_path = (argc > 1) ? argv[1] : "input1.txt";
  const char* output_pathA = (argc > 2) ? argv[2] : "output1.A.txt";
  const char* output_pathB = (argc > 3) ? argv[3] : "output1.B.txt";
  const char sep = ' ';
  std::fstream f(input_path);
  Point<lab_point_type>* arrA = nullptr, *arrB = nullptr;
  size_t n = 0, i = 0, m;
  if (f.is_open())
  {
    std::stringstream sstream;
    std::string line;
    if (!std::getline(f, line))
    {
      f.close();
      throw std::runtime_error(std::string(input_path) + " cannot be empty");
    }
    sstream << line;
    sstream >> n;
    sstream.clear();
    if (n <= 0)
    {
      f.close();
      throw std::runtime_error(line + " cannot be 0 because it's a size");
    }
    arrA = new Point<lab_point_type>[n];
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
        arrA[i] = Point<lab_point_type>(x, y);
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
    throw std::runtime_error(std::string(input_path) + " not found");
  }
  arrB = new Point<lab_point_type>[n];
  std::copy(arrA, arrA+n, arrB);

  auto start = std::chrono::high_resolution_clock::now();
  m = conv_sort_3_heap(arrA, n);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "conv_sort_3_heap done in " << duration.count() << " ms\n";
  write_arr_to_file(arrA, m, output_pathA);

  start = std::chrono::high_resolution_clock::now();
  m = conv_sort_5_merge(arrB, n);
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "conv_sort_5_merge done in " << duration.count() << " ms\n";
  write_arr_to_file(arrB, m, output_pathB);

  if (arrA != nullptr)
    delete[] arrA;
  if (arrB != nullptr)
    delete[] arrB;
  return 0;
}
