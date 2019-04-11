#include "UNBIN.h"
// Unbin class implementation
void Unbin::unbin2D(std::ofstream & output){
  double X,Y;
  for(int i = 0; i < hist2D.size(); i++) {
    X =(i)*bin_size_1D + min_1D + bin_size_1D*0.5;
    for(int j = 0; j < hist2D[0].size(); j++) {
      Y =(j)*bin_size_2D + min_2D + bin_size_2D*0.5;
      //cout<<hist2D[i][j]<<" "<<norm_factor<<endl;
      output<<setw(15)<<X<<setw(15)<<Y<<setw(15)<<(hist2D[i][j])/norm_factor<<endl;
    }
  }
}

// Cylindrical and axial histogram. Radial dimension is the second dimension of 2D array
void Unbin::unbin2D_rad(std::ofstream & output){
  double X,Y,radial_norm_fact;
  int shell;
  for(int i = 0; i < hist2D.size(); i++) {
    X =(i)*bin_size_1D + min_1D + bin_size_1D*0.5;
    for(int j = 0; j < hist2D[0].size(); j++) {
      Y =(j)*bin_size_2D +min_2D + bin_size_2D*0.5;
      shell =2*(j+1) - 1;
      radial_norm_fact=norm_factor*shell*bin_size_1D;
      //cout<<hist2D[i][j]<<" "<<norm_factor<<endl;
      output<<setw(15)<<X<<setw(15)<<Y<<setw(15)<<(hist2D[i][j])/norm_factor<<endl;
    }
  }
}


void Unbin::unbin1D(std::ofstream & output){
  double X;
  for(int i = 0; i < hist1D.size(); i++) {
    X =(i)*bin_size_1D + min_1D +bin_size_1D*0.5;
    output<<setw(15)<<X<<setw(15)<<(hist1D[i])/norm_factor<<endl;
  }
}

// Unbins cylindrical shells 
void Unbin::unbin1D_rad (std::ofstream & output) {
  double radial_norm_fact,X;
  int shell;
  for(int i = 0; i < hist1D.size(); i++) {
    X =(i)*bin_size_1D + min_1D + bin_size_1D*0.5;
    //extra factor  for cylindrical shell i.e. each shell is larger in volume
    shell =2*(i+1) - 1;
    radial_norm_fact=norm_factor*shell;
    output<<setw(15)<<X<<setw(15)<<(hist1D[i])/radial_norm_fact<<endl;
  }
}

void Unbin::setnorm(double norm) {
  norm_factor =norm;
}
