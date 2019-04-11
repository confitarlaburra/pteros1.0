#include <fstream>
#include "pteros/core/grid.h"
#include "pteros/core/pteros_error.h"
#include "pteros/analysis/trajectory_reader.h"
#include "pteros/analysis/task_plugin.h"
#include "pteros/analysis/task_plugin.h"
#include  "../../src/MSD_task.h"
using namespace std;
using namespace pteros;
using namespace Eigen;


int main(int argc, char** argv){
    try {
        Options opt;
        parse_command_line(argc,argv,opt);

        Trajectory_reader proc(opt);
        proc.add_task( new MSD_cyl(opt) );

        proc.run();


    } catch(const Pteros_error& e){
        cout << e.what() << endl;
    }
}

