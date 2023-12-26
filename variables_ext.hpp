#include <complex>
using namespace std;

// Description of the following variables are in variables.hpp

// Constants
extern int buffer_length;
extern char* input_default;
extern int fileName_length;
extern char* realNumber_format;

// Variables
extern int nn;
extern int* nArray;
extern double* a_n;
extern double* b_n;
extern int N;
extern double k_start;
extern double k_end;
extern int k_splits;
extern int Neigen;
extern char* value_output;
extern char* state_output;

//Variables for well potential
extern double well_start;
extern double well_end;
extern double well_depth;
extern double x_width;
extern double vacuum_level;
extern double cosine_length;
extern double cosine_amp;

// Variables for zheev
extern char JOBZ;
extern char UPLO;
extern complex<double>** matrix;
extern double* W;
extern complex<double>* WORK;
extern int LWORK;
extern double* RWORK;
extern int INFO;
