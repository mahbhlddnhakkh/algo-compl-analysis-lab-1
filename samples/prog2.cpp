#include "experiment_util.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

int main(const int argc, const char* argv[])
{
  std::srand(time(0));
  const char* output_path1A = (argc > 1) ? argv[1] : "output2.1.A.txt";
  const char* output_path1B = (argc > 2) ? argv[2] : "output2.1.B.txt";
  const char* output_path2A = (argc > 3) ? argv[3] : "output2.2.A.txt";
  const char* output_path2B = (argc > 4) ? argv[4] : "output2.2.B.txt";

  std::ofstream out1A(output_path1A), out1B(output_path1B);
  if (out1A.is_open() && out1B.is_open())
  {
    std::cout << "experiment 1\n";
    size_t q = 1000000, w = 1000000, n = 1;
    for (; n <= 1000001; n += 10000)
    {
      do_experiment(q, w, n, out1A, out1B);
    }
    out1A.close();
    out1B.close();
  }
  else
  {
    if (!out1A.is_open())
    {
      if (out1B.is_open())
      {
        out1B.close();
      }
      throw std::string(output_path1A) + " unable to write";
    }
    else
    {
      out1A.close();
    }
    if (!out1B.is_open())
    {
      throw std::string(output_path1B) + " unable to write";
    }
  }

  std::cout << '\n';

  std::ofstream out2A(output_path2A), out2B(output_path2B);
  if (out2A.is_open() && out2B.is_open())
  {
    std::cout << "experiment 2\n";
    size_t q_w = 0, n = 1000000;
    for (; q_w <= 1000000; q_w += 10000)
    {
      do_experiment(q_w, q_w, n, out2A, out2B);
    }
    out2A.close();
    out2B.close();
  }
  else
  {
    if (!out2A.is_open())
    {
      if (out2B.is_open())
      {
        out2B.close();
      }
      throw std::string(output_path2A) + " unable to write";
    }
    else
    {
      out2A.close();
    }
    if (!out2B.is_open())
    {
      throw std::string(output_path2B) + " unable to write";
    }
  }
  return 0;
}
