#include "../src/stdheader.h"
#include "../src/MSDCyl_task.h"
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
    //init instances of MSD and load calculation for pore A,B,C & D
    MSD_cyl msdCylA(&proc,options,selFit,options("selFit").as_strings()[0]);
    MSD_cyl msdCylB(&proc,options,selFit,options("selFit").as_strings()[1]);
    MSD_cyl msdCylC(&proc,options,selFit,options("selFit").as_strings()[2]);
    MSD_cyl msdCylD(&proc,options,selFit,options("selFit").as_strings()[3]);
    proc.run();
  } catch(const Pteros_error& e) {
    cout<<e.what()<<endl;
  }
}





