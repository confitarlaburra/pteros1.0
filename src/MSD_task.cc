#include "MSD_task.h"

void MSD::pre_process()  {
  window=options("win").as_int();
  MSDsel.modify(system,options("sel").as_string());
  position.resize(MSDsel.size());
  cout<<"MSD  pre process: "<<endl;
  cout<<"Windows: "<<window<<endl;
  cout<<"MSD selection: "<<options("sel").as_string()<<endl;
  cout<<"MSD selection size: "<<MSDsel.size()<<endl;
  cout<<"Remember to unwrap trajectories first as pteros does not read PBC from dcd's"<<endl;
  frames=0;
  set_dimensions();
}

void MSD::process_frame(const Frame_info& info) {
  collect_pos();
  frames++;
}

void MSD::post_process(const Frame_info& info) {
  calculate_MSD();
}


void MSD::collect_pos() {
  for(int i = 0; i < MSDsel.size(); i++) { 
    position[i].push_back(MSDsel.XYZ(i));
  }
}

void MSD::calculate_MSD() {
  cout<<"#\tNow computing MSD for "<<frames<<" frames..."<<endl;
  //1d vector to store msd
  vector<double> MSD_list(window,0.0);
  // 1d vector to count for averaging
  vector<int> average_counter(window,0);
  for(int it = 0; it < frames-window; it++) {
    int window_counter = 0;
    double square_d = 0;
    for(int j = it; j < it+window; j++) { //second loop through frames starting from it
      average_counter[window_counter]++;
      for (int i=0; i<MSDsel.size(); i++) {
	square_d = 0;
	for(int k = 0; k < ndim; k++) { // loop through selected dimensions  and get displacement
	  const double d = (position[i][j])[dim[k]]-(position[i][it])[dim[k]];
	  square_d += d * d;
	}
	MSD_list[window_counter]+=square_d;
      }
      window_counter++;
    }
  }
  ofstream output("msd.dat");
  output << "# Time series of the mean square displacement\n"
	 << "# Here the calculation uses a double loop scheme:" << endl
	 << "# <[r(t)-r(t+tau)]^2>/2*Nd*t\n";
  output<<"#MSD of atoms "<<options("sel").as_string()<<endl;
  output<<"#Window          <MSD>"<<endl;
  float t =0.0;
  output.precision(8);
  for(int i = 0; i < MSD_list.size(); i++) {
    output<<setw(15)<<i<<setw(15)<<(MSD_list[i]/average_counter[i]/MSDsel.size())<<endl;
  }
  output.close();       
}



void MSD::set_dimensions() {
  int i =0;  
  if( i != (options("dim").as_strings()).size() ){
    ndim = 0;
    string dum(options("dim").as_strings()[i]);
    cout<<"Considering "<<dum<<" dimension for MSD calculation"<<endl;
    if (dum == "x") {
      dim[ndim] = 0;
      ndim++;
    } else if (dum == "y") {
      dim[ndim] = 1;
      ndim++;
    } else if (dum == "z") {
      dim[ndim] = 2;
      ndim++;
    } else {
      throw Pteros_error("MSD ")<<
	"Wrong argument given for -dim !!\n"
	"  You can give x, y, and/or z\n"
	"  For example:\n"
	"    -dim  x\n"
	"  or:\n"
	"    -dim x y z\n";
    }
    i++;
  }
  if( i != (options("dim").as_strings()).size() ) {  
    string dum(options("dim").as_strings()[i]);
    cout<<"Considering "<<dum<<" dimension for MSD calculation"<<endl;
    if (dum == "x") {
      dim[ndim] = 0;
      ndim++;
    } else if (dum == "y") {
      dim[ndim] = 1;
      ndim++;
    } else if (dum == "z") {
      dim[ndim] = 2;
      ndim++;
    } else {
      throw Pteros_error("MSD ")<<
	"Wrong argument given for -dim !!\n"
	"  You can give x, y, and/or z\n"
	"  For example:\n"
	"    -dim  x\n"
	"  or:\n"
	"    -dim x y z\n";
    }
    i++;
  }
  if( i != (options("dim").as_strings()).size() ) {  
    string dum(options("dim").as_strings()[i]);
    cout<<"Considering "<<dum<<" dimension for MSD calculation"<<endl;
    if (dum == "x") {
      dim[ndim] = 0;
      ndim++;
    } else if (dum == "y") {
      dim[ndim] = 1;
      ndim++;
    } else if (dum == "z") {
      dim[ndim] = 2;
      ndim++;
    } else {
      throw Pteros_error("MSD ")<<
	"Wrong argument given for -dim !!\n"
	"  You can give x, y, and/or z\n"
	"  For example:\n"
	"    -dim  x\n"
	"  or:\n"
	"    -dim x y z\n";
    }
    i++;
  }
  cout<<"Total MSD dimensions to consider: "<<ndim<<endl;
}

