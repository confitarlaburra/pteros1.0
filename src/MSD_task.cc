#include "MSD_task.h"



void MSD_cyl::pre_process()  {
  /*
  set_dimensions();
  rad2=options("rad").as_float()*options("rad").as_float();
  window=options("win").as_int();
  minZ=options("minZmaxZ").as_floats()[0];
  maxZ=options("minZmaxZ").as_floats()[1];
  MSDsel.modify(system,options("sel").as_string());
  position.resize(MSDsel.size());
  in_out.resize(MSDsel.size());
  */
  if (options.has("selFit"))  
    selFit.modify(system,options("selFit").as_string());
  frames=0;
  /*
  cout<<"MSDcyl pre process: "<<"pore "<<refFrame<<endl;
  cout<<"Windows: "<<window<<endl;
  cout<<"Radius2: "<<rad2<<endl;
  cout<<"minZ: "<<minZ<<endl;
  cout<<"maxZ: "<<maxZ<<endl;
  cout<<"MSDcyl selection: "<<options("sel").as_string()<<endl;
  cout<<"MSDcyl selection size: "<<MSDsel.size()<<endl;
  */
  //cout<<"Number of frames "<<system.num_frames()<<endl;
  if (selFit.size()) {
    cout<<"Reference selection: "<<options("selFit").as_string()<<endl;
    cout<<"Reference selection size: "<<selFit.size()<<endl;
  } else {
    cout<<"Warning: reference selection empty,"
	<<"no RMSD fitting against initial reference!!!"<<endl;
  }
}

void MSD_cyl::process_frame(const Frame_info& info)  {
  if (selFit.size()) {
    Affine3f trans = fit_transform(selFit,selFitOld);
    Selection(system,"all").apply_transform(trans);
  }
  string A = to_string(frames);
  string name =A+".pdb";
  Selection(system,"all").write(name);
  frames++;
}

void MSD_cyl::post_process(const Frame_info& info)  {

  
  //calculate_MSD();
}


void MSD_cyl::collect_pos() {

}

void MSD_cyl::calculate_MSD() {

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

