#include "../src/stdheader.h"
#include "../src/MSD_task.h"
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
    //init instances of MSD
    MSD msd(&proc,options);
    proc.run();
  } catch(const Pteros_error& e) {
    cout<<e.what()<<endl;
  }
}





