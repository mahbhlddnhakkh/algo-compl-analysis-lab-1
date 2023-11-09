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
  const char* output_path = (argc > 2) ? argv[2] : "output3.txt";
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
    throw std::runtime_error(std::string(input_path) + " not found");
  }

  std::ofstream out(output_path);
  if (out.is_open())
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

        do_experiment(q, w, n, out);
      }
    }
    out.close();
  }
  else
  {
    throw std::runtime_error(std::string(output_path) + " unable to write");
  }
  return 0;
}
