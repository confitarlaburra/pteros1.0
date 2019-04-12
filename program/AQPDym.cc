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
    // init instances for pore A,B,C & D

    System systemA(options("refs").as_strings()[0]);
    Selection selFitA(systemA,options("selFit").as_string());

    
   //Selection fitA();
    
    MSD_cyl msdCylA(&proc,options,selFitA,string("A"));
    //MSD_cyl msdCylB(&proc,options,options("fitFrame").as_ints()[1]);
    //MSD_cyl msdCylC(&proc,options,options("fitFrame").as_ints()[2]);
    //MSD_cyl msdCylD(&proc,options,options("fitFrame").as_ints()[3]);
    proc.run();
  } catch(const Pteros_error& e) {
    cout<<e.what()<<endl;
  }
}





