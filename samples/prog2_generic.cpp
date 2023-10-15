#include "experiment_util.hpp"
#ifdef EXPERIMENT_PRINT
#include <iostream>
#endif
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <time.h>

int main(const int argc, const char* argv[])
{
  std::srand(time(0));
  const char* input_path = (argc > 1) ? argv[1] : "input3.txt";
  const char* output_pathA = (argc > 2) ? argv[2] : "output3.A.txt";
  const char* output_pathB = (argc > 3) ? argv[3] : "output3.B.txt";
  const char sep = ' ';
  std::stringstream sstream;
  
  std::fstream f(input_path);
  std::vector<std::string> coms;
  
  if (f.is_open())
  {
    std::string line;
    while(std::getline(f, line))
    {
      coms.push_back(line);
    }
    f.close();
  }
  else
  {
    throw std::string(input_path) + " not found";
  }

  std::ofstream outA(output_pathA), outB(output_pathB);
  if (outA.is_open() && outA.is_open())
  {
    for (const auto& e : coms)
    {
      size_t sz = e.length();
      if (sz != 0)
      {
        size_t q, w, n, j = 0;
        while (j < sz && e[j] != sep)
        {
          sstream << e[j];
          j++;
        }
        j++;
        sstream >> q;
        sstream.clear();
        
        while (j < sz && e[j] != sep)
        {
          sstream << e[j];
          j++;
        }
        j++;
        sstream >> w;
        sstream.clear();

        while (j < sz)
        {
          sstream << e[j];
          j++;
        }
        sstream >> n;
        sstream.clear();

        do_experiment(q, w, n, outA, outB);
      }
    }
    outA.close();
    outB.close();
  }
  else
  {
    if (!outA.is_open())
    {
      if (outB.is_open())
      {
        outB.close();
      }
      throw std::string(output_pathA) + " unable to write";
    }
    else
    {
      outA.close();
    }
    if (!outB.is_open())
    {
      throw std::string(output_pathB) + " unable to write";
    }
  }
  return 0;
}
