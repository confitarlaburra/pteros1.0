#include "stdheader.h"

using namespace std;
using namespace pteros;
using namespace Eigen;

#ifndef INCLUDED_MSDHEADER_H
#define INCLUDED_MSDHEADER_H 


class MSD: public Consumer {
 public:
  //Constructor
 MSD( Trajectory_processor* pr, Options & _options ): Consumer(pr){
    options=_options;
  }
 protected:

  virtual void pre_process();
  virtual void process_frame(const Frame_info& info);
  virtual void post_process(const Frame_info& info);

  void collect_pos();
  void calculate_MSD();
  void set_dimensions();
  
  Selection MSDsel;
  Options options;
  int window;
  int ndim = 3;
  int frames =0;
  int dim[3] = {0, 1, 2};
  vector<vector<Vector3f> > position;
};
#endif 
