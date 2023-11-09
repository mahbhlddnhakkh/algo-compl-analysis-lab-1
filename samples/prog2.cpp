#include "experiment_util.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <chrono>

int main(const int argc, const char* argv[])
{
  std::srand(time(0));
  const char* output_path1 = (argc > 1) ? argv[1] : "output2.1.txt";
  const char* output_path2 = (argc > 2) ? argv[2] : "output2.2.txt";

  std::ofstream out1(output_path1);
  if (out1.is_open())
  {
    std::cout << "experiment 1\n";
    auto start = std::chrono::high_resolution_clock::now();
    const size_t q_w = 1000000;
    size_t n = 1;
    for (; n <= 1000001; n += 10000)
    {
      do_experiment(q_w, q_w, n, out1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Done in " << duration.count() << " ms\n";
    out1.close();
  }
  else
  {
    throw std::runtime_error(std::string(output_path1) + " unable to write");
  }

  std::cout << '\n';

  std::ofstream out2(output_path2);
  if (out2.is_open())
  {
    std::cout << "experiment 2\n";
    auto start = std::chrono::high_resolution_clock::now();
    size_t q_w = 0;
    const size_t n = 1000000;
    for (; q_w <= 1000000; q_w += 10000)
    {
      do_experiment(q_w, q_w, n, out2);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Done in " << duration.count() << " ms\n";
    out2.close();
  }
  else
  {
    throw std::runtime_error(std::string(output_path2) + " unable to write");
  }
  return 0;
}
