#include "stdheader.h"

using namespace std;
using namespace pteros;
using namespace Eigen;

#ifndef INCLUDED_PFCYLHEADER_H
#define INCLUDED_PFCYLHEADER_H 


class pf_cyl: public Consumer {
 public:
  //Constructor
 pf_cyl( Trajectory_processor* pr, Options & _options, const Selection & _selFitOld, const string& _id ): Consumer(pr){
    options=_options;
    selFitOld=_selFitOld;
    id=_id; // same selection as selFitOld
  }

 pf_cyl( Trajectory_processor* pr, Options & _options, const Selection & _selFitOld ): Consumer(pr){
    options=_options;
    selFitOld=_selFitOld;
  }
  
 protected:

  virtual void pre_process();
  virtual void process_frame(const Frame_info& info);
  virtual void post_process(const Frame_info& info);

  void collect_n();
  void calculate_MSD();
  Selection pfsel;
  Selection selFit;
  Selection selFitOld;
  Options options;
  string id="0";
  int window;
  int frames =0;
  float rad2;
  float minZ;
  float maxZ;
  float PoreLength;
  float dzAll=0.0;
  float dz=0.0;
  float dn=0.0;
  float n =0.0;
  vector<Vector3f> posListOld;
  vector<float> dnList;
  vector<float> nList;
};
#endif 
