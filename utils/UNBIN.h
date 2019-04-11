#include <cassert>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>
//class declaration to unbin 1D and 2D histograms
class Unbin  {
 public:
  void unbin2D(std::ofstream & output);
  void unbin2D_rad(std::ofstream & output);
  void unbin1D(std::ofstream & output);
  void unbin1D_rad (std::ofstream & output);
  void setnorm (double norm);
 protected:
  std::vector<vector<int> > hist2D;
  std::vector<int> hist1D;
  double min_1D;
  double min_2D;
  double bin_size_1D;
  double bin_size_2D;
  double norm_factor;
};
// end  class

const double PI =  3.14159265359;

//function to check normalize options
void check_norm_argument(string normalization);
