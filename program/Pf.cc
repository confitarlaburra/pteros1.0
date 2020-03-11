#include "../src/stdheader.h"
#include "../src/pfCyl_task.h"

using namespace std;
using namespace pteros;
using namespace Eigen;
int main(int argc, char** argv){
  try {
    // Create container for command-line options
    Options options;
    // Parse command line
    parse_command_line(argc,argv, options);
    // Create Trajectory processor and pass options to it
    Trajectory_processor proc(options);
    //Create reference selection for pore aligned in z and centrered
    System systemRef(options("ref").as_string());
    Selection selFit(systemRef,options("selFit").as_strings()[0]);
    //init instances of pf and load calculation for pore A,B,C & D
    pf_cyl pfCylA(&proc,options,selFit,options("selFit").as_string());
    proc.run();
  } catch(const Pteros_error& e) {
    cout<<e.what()<<endl;
  }
}





