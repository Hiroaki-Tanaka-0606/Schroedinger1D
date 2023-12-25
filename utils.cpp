#define _USE_MATH_DEFINES
#include "variables_ext.hpp"
#include <iostream>
#include <complex>
using namespace std;

complex<double>** alloc_zmatrix(int n, int m){
  int i;
	complex<double>** mat;
  mat = (complex<double>**)malloc((size_t)(m * sizeof(complex<double>*)));
  if (mat == NULL) {
    cout << "Error: allocation failed in alloc_zmatrix" << endl;
		exit(1);
  }
  mat[0] = (complex<double>*)malloc((size_t)(m * n * sizeof(complex<double>)));
  if (mat[0] == NULL) {
    cout << "Error: allocation failed in alloc_zmatrix" << endl;
    exit(1);
  }
  for (i=1;i<m;i++){
		mat[i] = mat[i-1] + n;
	}
  return mat;
}

double* alloc_dvector(int n){
  double *vec;
  vec = (double*)malloc((size_t)(n * sizeof(double)));
  if (vec == NULL) {
    cout << "Error: allocation failed in alloc_dvector" << endl;
    exit(1);
  }
  return vec;
}

complex<double>* alloc_zvector(int n){
  complex<double> *vec;
  vec = (complex<double>*)malloc((size_t)(n * sizeof(complex<double>)));
  if (vec == NULL) {
    cout << "Error: allocation failed in alloc_zvector" << endl;
    exit(1);
  }
  return vec;
}

// H(k) is defined in README.md
void compositeMatrix(double k){
	int i,j,l;
	double x;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(i==j){
				// diagonal element, N^2+V_i
				x=i*1.0/N;
				matrix[i][i]=N*N;
				for(l=0;l<nn;l++){
					matrix[i][i]+=a_n[l]*cos(2*M_PI*nArray[l]*x);
					matrix[i][i]+=b_n[l]*sin(2*M_PI*nArray[l]*x);
				}
			}else if(abs(i-j)==1){
				// tri-diagonal, -N^2/2
				matrix[i][j]=-N*N*1.0/2;
			}else{
				// off-diagonal
				matrix[i][j]=0;
			}
		}
	}

	complex<double> I(0.0,1.0);
	// off-diagonal corners
	// right-top corner ((0,N-1) element))
	// matrix element = -N^2exp(-ik)/2
	// at matrix[N-1][0]
	// indicies are exchanged because of difference between C-style and fortran-style arrays
	matrix[N-1][0]=-N*N*1.0*exp(-I*2.0*M_PI*k)/2.0;

	//left-bottom corner ((N-1,0) element)
	// matrix element = -N^2exp(ik)/2
	// at matrix[0,N-1]
	matrix[0][N-1]=-N*N*1.0*exp(I*2.0*M_PI*k)/2.0;
		
	
		
}

// H(k) is defined in README.md
void compositeMatrix_well(double k){
	double dx=x_width/N;
	int i,j,l;
	double x;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(i==j){
				// diagonal element, N^2+V_i
				x=i*dx;
				matrix[i][i]=1.0/dx/dx;
				if(well_start < x && x < well_end){
					matrix[i][i]+=well_depth;
				}
			}else if(abs(i-j)==1){
				// tri-diagonal, -N^2/2
				matrix[i][j]=-0.5/dx/dx;
			}else{
				// off-diagonal
				matrix[i][j]=0;
			}
		}
	}

	complex<double> I(0.0,1.0);
	// off-diagonal corners
	// right-top corner ((0,N-1) element))
	// matrix element = -N^2exp(-ik)/2
	// at matrix[N-1][0]
	// indicies are exchanged because of difference between C-style and fortran-style arrays
	matrix[N-1][0]=-exp(-I*2.0*M_PI*k)/2.0/dx/dx;

	//left-bottom corner ((N-1,0) element)
	// matrix element = -N^2exp(ik)/2
	// at matrix[0,N-1]
	matrix[0][N-1]=-exp(I*2.0*M_PI*k)/2.0/dx/dx;
		
	
		
}
