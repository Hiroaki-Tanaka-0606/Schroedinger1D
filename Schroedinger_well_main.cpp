#include "variables.hpp"
#include "initialize.hpp"
#include "loadInput_well.hpp"
#include "utils.hpp"
#include "lapack.hpp"
#include <iostream>
#include <cstring>

using namespace std;

// Schroedinger_main.cpp: main calclulation


int main(int argc, char** argv){
	// initial message
	cout << "Solver of one-dimensional Schroedinger equation with the well potential" << endl;
	initialize();

	// load input file name
	char inputName[fileName_length];
	if(argc==1){
		// only command -> input file name is default
		strcpy(inputName, input_default);
	}else{
		// input file name is given
		strcpy(inputName, argv[1]);
	}
	cout << "Input file: " << inputName << endl;
	FILE* input=fopen(inputName, "r");
	if(input==NULL){
		// error in opening the input file
		cout << "Error: can't open the input file" << endl;
		return -1;
	}
	
	// load input
	int loadInput_status=loadInput_well(input);
	if(loadInput_status==1){
		// ok
		cout << "Finished loading input" << endl;
	}else{
		cout << "Failed in loading input" << endl;
		return -1;
	}

	// close input
	fclose(input);

	// initialization of zheev, determine WORK size
	cout << "zheev initialization" << endl;
	zheevInit();
	if(INFO!=0){
		cout << "zheevInit failed" << endl;
		return -1;
	}

	// solve eigenvalue equation for each k point
	cout << "Solve eigenvalue equation" << endl;
	int i,j,l;
	double k;
	double delta_k=0.0;
	FILE* value_file=fopen(value_output, "w");
	char* state_fileName=new char[fileName_length];
	FILE* state_file;
	int sprintf_status;

	// write header rows
	fprintf(value_file, "# Eigenvalues\n");
	fprintf(value_file, "# k/2pi ");
	for(i=0;i<Neigen;i++){
		fprintf(value_file, "E_%d ",i+1);
	}
	fprintf(value_file, "\n");
	if(k_splits!=0){
		delta_k=(k_end-k_start)/k_splits;
	}
	for(i=0;i<=k_splits;i++){
		sprintf_status=sprintf(state_fileName, state_output, i);
		if(sprintf_status<0){
			cout << "Error: name of state output file" << endl;
			return -1;
		}
		state_file=fopen(state_fileName,"w");
		k=k_start+delta_k*i;
		// write header rows
		fprintf(state_file, "# Eigenstates\n");
		fprintf(state_file, "# k = ");
		fprintf(state_file, realNumber_format, k);
		fprintf(state_file, "\n");
		fprintf(state_file, "# x ");
		for(j=0;j<Neigen;j++){
			fprintf(state_file, "Re(psi_%d) Im(psi_%d) ",j+1,j+1);
		}
		fprintf(state_file, "\n");

		compositeMatrix_well(k);
	  zheev();
		if(INFO!=0){
			cout << "zheev failed" << endl;
			return -1;
		}
		
		// write the result to files
		// eigenvalues to value_file
		fprintf(value_file, realNumber_format, k);
		fprintf(value_file, " ");
		for(j=0;j<Neigen;j++){
			fprintf(value_file, realNumber_format, W[j]);
			fprintf(value_file, " ");
		}
		fprintf(value_file, "\n");
		//eigenstates to state_file
		for(j=0;j<N;j++){
			double x=j*1.0/N*x_width;
			fprintf(state_file, realNumber_format, x);
			fprintf(state_file, " ");
			for(l=0;l<Neigen;l++){
				fprintf(state_file, realNumber_format, matrix[l][j].real());
				fprintf(state_file, " ");
				fprintf(state_file, realNumber_format, matrix[l][j].imag());
				fprintf(state_file, " ");
			}
			fprintf(state_file, "\n");
		}
		fclose(state_file);
	}
	
	// test: matrix output
	/*
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("(%9.2e, %9.2e) ", matrix[i][j].real(), matrix[i][j].imag());
		}
		printf("\n");
	}
	*/
	
	fclose(value_file);
}
