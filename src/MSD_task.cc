#include "MSD_task.h"



void MSD_cyl::pre_process()  {
  rad2=options("rad").as_float()*options("rad").as_float();
  window=options("win").as_int();
  minZ=options("minZmaxZ").as_floats()[0];
  maxZ=options("minZmaxZ").as_floats()[1];
  MSDsel.modify(system,options("sel").as_string());
  position.resize(MSDsel.size());
  in_out.resize(MSDsel.size());
  if (options.has("selFit"))  
    selFit.modify(system,id);
  cout<<"MSDcyl "<<id<<" pre process: "<<"pore "<<id<<endl;
  cout<<"Windows: "<<window<<endl;
  cout<<"Radius2: "<<rad2<<endl;
  cout<<"minZ: "<<minZ<<endl;
  cout<<"maxZ: "<<maxZ<<endl;
  cout<<"MSDcyl selection: "<<options("sel").as_string()<<endl;
  cout<<"MSDcyl selection size: "<<MSDsel.size()<<endl;
  frames=0;
  set_dimensions();
  if (selFit.size()) {
    cout<<"Reference selection: "<<id<<endl;
    cout<<"Reference selection size: "<<selFit.size()<<endl;
  } else {
    cout<<"Warning: reference selection empty,"
	<<"no RMSD fitting against initial reference!!!"<<endl;
  }
}

void MSD_cyl::process_frame(const Frame_info& info) {
  if (selFit.size()) {
    Affine3f trans = fit_transform(selFit,selFitOld);
    Selection(system,"all").apply_transform(trans);
  }
  /*
  string A = to_string(frames);
  string name =A+"."+id+".pdb";
  Selection(system,"all").write(name);
  */
  collect_pos();
  frames++;
}

void MSD_cyl::post_process(const Frame_info& info) {
  calculate_MSD();
}


void MSD_cyl::collect_pos() {
  vector<int> load_indexes;
  for(int i = 0; i < MSDsel.size(); i++) {
    position[i].push_back(MSDsel.XYZ(i));
    if ( ( (MSDsel.XYZ(i)[2] >= minZ) && (MSDsel.XYZ(i)[2] <= maxZ ) )  &&  
	 ( (MSDsel.XYZ(i)[0]*MSDsel.XYZ(i)[0] + MSDsel.XYZ(i)[1]*MSDsel.XYZ(i)[1] ) <=  rad2)) {
      load_indexes.push_back(i);
      in_out[i].push_back(true);
    } else
      in_out[i].push_back(false);
  }
  loads_in_time.push_back(load_indexes);
  //cout<<load_indexes.size()<<endl;
}

void MSD_cyl::calculate_MSD() {
  cout<<"#\tNow computing MSD for "<<id<<" for "<<frames<<" frames..."<<endl;
  //1d vector to store msd
  vector<double> MSD_list(window,0.0);
  //1d vector to count for averaging
  vector<int> average_counter(window,0);
  string outName = "Loads"+id+".dat";
  ofstream outputL(outName);
  outputL.precision(3);
  outputL<<"#Numer of loaded "<<options("sel").as_string()<<endl;
  outputL<<"#Frame          #N"<<endl;
  for(int it = 0; it < frames; it++) {
    outputL<<setw(15)<<it<<setw(15)<<loads_in_time[it].size()<<endl;
  }
  outputL.close();
  for(int it = 0; it < frames-window; it++) {
    int window_counter = 0;
    double square_d = 0;
    for(int j = it; j < it+window; j++) { //second loop through frames starting from origin "it"  
      for (int h =0; h < loads_in_time[it].size(); h++) { // loop through loaded atoms at origin frame it 
	int i=loads_in_time[it][h]; // index of a loaded atom at origin frame it
	square_d = 0;
	if (in_out[i][j]) { // check if atom i was loaded in time j 
	  for(int k = 0; k < ndim; k++) { // loop through selected dimensions  and get displacement 
	    const double d = (position[i][j])[dim[k]]-(position[i][it])[dim[k]];
	    square_d += d * d;
	  }
	  MSD_list[window_counter]+=square_d;
	  average_counter[window_counter]++;
	}
      }
      window_counter++;
    }
  }
  outName = "msd"+id+".dat";
  ofstream output(outName);
  output << "# Time series of the mean square displacement\n"
	 << "# Here the calculation uses a double loop scheme:" << endl
	 << "# <[r(t)-r(t+tau)]^2>/2*Nd*t\n";
  output<<"#MSD of atoms "<<options("sel").as_string()<<endl;
  output<<"#Frame          <MSD>"<<endl;
  float t =0.0;
  output.precision(3);
  for(int i = 0; i < MSD_list.size(); i++) { 
    output<<setw(15)<<i<<setw(15)<<(MSD_list[i]/average_counter[i])<<endl;
  }
  output.close(); 
}



void MSD_cyl::set_dimensions() {
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
      throw Pteros_error("MSDcyl ")<<
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
    cout<<"Considering "<<dum<<" dimension for MSDcyl calculation"<<endl;
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
      throw Pteros_error("MSDcyl ")<<
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
    cout<<"Considering "<<dum<<" dimension for MSDcyl calculation"<<endl;
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
      throw Pteros_error("MSDcyl ")<<
	"Wrong argument given for -dim !!\n"
	"  You can give x, y, and/or z\n"
	"  For example:\n"
	"    -dim  x\n"
	"  or:\n"
	"    -dim x y z\n";
    }
    i++;
  }
  cout<<"Total MSDcyl dimensions to consider: "<<ndim<<endl;
}

