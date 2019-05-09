#include "pfCyl_task.h"

void pf_cyl::pre_process()  {
  rad2=options("rad").as_float()*options("rad").as_float();
  window=options("win").as_int();
  minZ=options("minZmaxZ").as_floats()[0];
  maxZ=options("minZmaxZ").as_floats()[1];
  PoreLength= maxZ - minZ;
  pfsel.modify(system,options("sel").as_string());
  Vector3f dum(0,0,0);
  posListOld.resize(pfsel.size(),dum);
  if (options.has("selFit"))  
    selFit.modify(system,id);
  cout<<"pfcyl "<<id<<" pre process: "<<"pore "<<id<<endl;
  cout<<"Windows: "<<window<<endl;
  cout<<"Radius2: "<<rad2<<endl;
  cout<<"minZ: "<<minZ<<endl;
  cout<<"maxZ: "<<maxZ<<endl;
  cout<<"pfcyl selection: "<<options("sel").as_string()<<endl;
  cout<<"pfcyl selection size: "<<pfsel.size()<<endl;
  frames=0;
  if (selFit.size()) {
    cout<<"Reference selection: "<<id<<endl;
    cout<<"Reference selection size: "<<selFit.size()<<endl;
  } else {
    cout<<"Warning: reference selection empty,"
	<<"no RMSD fitting against initial reference!!!"<<endl;
  }
}

void pf_cyl::process_frame(const Frame_info& info) {
  if (selFit.size()) {
    Affine3f trans = fit_transform(selFit,selFitOld);
    Selection(system,"all").apply_transform(trans);
  }
  /*
  string A = to_string(frames);
  string name =A+"."+id+".pdb";
  Selection(system,"all").write(name);
  */
  collect_n();
  frames++;
}

void pf_cyl::post_process(const Frame_info& info) {
  calculate_MSD();
}


void pf_cyl::collect_n() {
  dzAll=0.0;
  for(int i = 0; i < pfsel.size(); i++) {
    if ( ( (pfsel.XYZ(i)[2] >= minZ) && (pfsel.XYZ(i)[2] <= maxZ ) )  &&  
  	 ( (pfsel.XYZ(i)[0]*pfsel.XYZ(i)[0] + pfsel.XYZ(i)[1]*pfsel.XYZ(i)[1] ) <=  rad2)) {
      if ( ( (posListOld[i][2] >= minZ) && (posListOld[i][2] <= maxZ ) )  &&  
	   ( (posListOld[i][0]*posListOld[i][0] + posListOld[i][1]*posListOld[i][1] ) <=  rad2)) {
	dz =pfsel.XYZ(i)[2]-posListOld[i][2];
	dzAll+=dz;
      }
    }
    posListOld[i]=pfsel.XYZ(i);
  }
  if (frames > 0)
    dn = dzAll/PoreLength; 
  dnList.push_back(dn);
  n += dn;
  nList.push_back(n);
}

void pf_cyl::calculate_MSD() {
  cout<<"#\tNow computing MSD(pf) for "<<id<<" for "<<frames<<" frames..."<<endl;
  string outName = "n(t)."+id+".dat";
  ofstream outputL(outName);
  outputL.precision(3);
  outputL<<"#Trajectory of collective  "<<options("sel").as_string()<<endl;
  outputL<<"#Frame          #n(t)"<<endl;
  for(int it = 0; it < frames; it++) {
    outputL<<setw(15)<<it<<setw(15)<<nList[it]<<endl;
  }
  outputL.close();

  vector<float> N2List(window,0.0);
  vector<int> averageCounter(window,0);
  float nLoop;
  float N2;
  int windowCounter;
  for(int it = 0; it < frames-window; it++) {
      windowCounter=0;
      nLoop=0;
      N2=0;
      for(int j = it; j < it+window; j++) {
	if (j>it) // first is always zero
	  nLoop+=dnList[j];
	//computes the msd of n, N2 and accumualtes for every time-window frame
	N2=nLoop*nLoop;
	N2List[windowCounter]+=N2;
	averageCounter[windowCounter]++;
        windowCounter++;
      }
  }
   
  outName = "N2_msd."+id+".dat";
  ofstream output(outName);
  output<<"#Frame   <N2>"<<std::endl;
  output.precision(3);
  for(int i = 0; i < N2List.size(); i++) {
    output<<setw(15)<<i<<setw(15)<<(N2List[i]/averageCounter[i])<<endl;
  }
  output.close();
}

