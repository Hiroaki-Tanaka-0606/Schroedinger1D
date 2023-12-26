#include <complex>
using namespace std;

// Constants
// The values are given in initialize()
int buffer_length; // length of buffer used when each line of the input file is read
char* input_default; // default name of the input file
int fileName_length; // max length of the input and output file names
char* realNumber_format; // format for a real number used in sprintf() and printf()

//Variables
int nn; // number of 'n's for potential description
int* nArray; // array of 'n's
double* a_n; // a_n (cosine coefficients)
double* b_n; // b_n (sine coefficients)
int N; // number of meshes
double k_start; // start value of k
double k_end; // end value of k
int k_splits; // how many times the range [k_start, k_end] is split
int Neigen; // number of eigenstates to be output
char* value_output; // output file name, in which eigenvalues are written
char* state_output; // output file format, in which eigenstates are written

//Variables for well potential
double well_start;
double well_end;
double well_depth;
double x_width;
double vacuum_level;
double cosine_length;
double cosine_amp;

//Variables for zheev
char JOBZ;
char UPLO;
complex<double>** matrix;
double* W;
complex<double>* WORK;
int LWORK;
double* RWORK;
int INFO;
