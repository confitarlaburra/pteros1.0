#include "stdheader.h"

using namespace std;
using namespace pteros;
using namespace Eigen;

#ifndef INCLUDED_MSDCYLHEADER_H
#define INCLUDED_MSDCYLHEADER_H 


class MSD_cyl: public Consumer {
 public:
  //Constructor
 MSD_cyl( Trajectory_processor* pr, Options & _options, const Selection &  _selFitOld, const string& _id ): Consumer(pr){
    options=_options;
    selFitOld=_selFitOld;
    id=_id; // same selectio as selFitOld
  }

 MSD_cyl( Trajectory_processor* pr, Options & _options, const Selection  & _selFitOld  ): Consumer(pr){
    options=_options;
    selFitOld=_selFitOld;
  }

  
 protected:

  virtual void pre_process();
  virtual void process_frame(const Frame_info& info);
  virtual void post_process(const Frame_info& info);

  void collect_pos();
  void calculate_MSD();
  void set_dimensions();
  
  Selection MSDsel;
  Selection selFit;
  Selection selFitOld;
  Options options;
  string id="all";
  int window;
  int ndim = 3;
  int frames =0;
  int dim[3] = {0, 1, 2};
  float rad2;
  float minZ;
  float maxZ;
  vector<vector<Vector3f> > position;
  vector<vector <bool> > in_out;
  vector<vector<int > >loads_in_time;
};
#endif 
