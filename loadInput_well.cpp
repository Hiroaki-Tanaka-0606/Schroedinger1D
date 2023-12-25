#include <cstdio>
#include <iostream>
#include "variables_ext.hpp"
using namespace std;

void loadError(int line){
	cout << "Error in loading line " << line << endl;
}

void parseError(int line){
	cout << "Error in parsing line " << line << endl;
}

int loadInput_well(FILE* input){
	char buffer[buffer_length];
	char* fgets_status;
	int sscanf_status;
	int line=1;
	int i;

	// line 1: x width, well start, end, depth
	fgets_status=fgets(buffer, buffer_length, input);
	if(fgets_status==NULL){
		loadError(line); return -1;
	}
	sscanf_status=sscanf(buffer, "%lf %lf %lf %lf", &x_width, &well_start, &well_end, &well_depth);
	if(sscanf_status!=4){
		parseError(line); return -1;
	}
	line++;
	cout << "Well potential: from ";
	printf(realNumber_format, well_start);
	cout << " to ";
	printf(realNumber_format, well_end);
	cout << ", depth ";
	printf(realNumber_format, well_depth);
	cout << endl;

	// line 2: N (nubmer of meshes)
	fgets_status=fgets(buffer, buffer_length, input);
	if(fgets_status==NULL){
		loadError(line); return -1;
	}
	sscanf_status=sscanf(buffer, "%d", &N);
	if(sscanf_status!=1){
		parseError(line); return -1;
	}
	line++;
	cout << "Number of meshes: " << N << endl;

	// line 3: k points specification
	fgets_status=fgets(buffer, buffer_length, input);
	if(fgets_status==NULL){
		loadError(line); return -1;
	}
	sscanf_status=sscanf(buffer, "%lf%lf%d", &k_start, &k_end, &k_splits);
	if(sscanf_status!=3){
		parseError(line); return -1;
	}
	line++;
	cout << "k points: from ";
	printf(realNumber_format, k_start);
	cout << " to ";
	printf(realNumber_format, k_end);
	cout << ", " << k_splits+1 << " point(s)" << endl;

	// line 4: Neigen (number of eigenstates to be output)
	fgets_status=fgets(buffer, buffer_length, input);
	if(fgets_status==NULL){
		loadError(line); return -1;
	}
	sscanf_status=sscanf(buffer, "%d", &Neigen);
	if(sscanf_status!=1){
		parseError(line); return -1;
	}
	line++;
	cout << "Number of eigenstates to be output: " << Neigen << endl;

	// line 5: eigenvalue file
	fgets_status=fgets(buffer, buffer_length, input);
	if(fgets_status==NULL){
		loadError(line); return -1;
	}
	sscanf_status=sscanf(buffer, "%s", value_output);
	if(sscanf_status!=1){
		parseError(line); return -1;
	}
	line++;
	cout << "Eigenvalue output file: " << value_output << endl;
	
	// line 5: eigenstates file
	fgets_status=fgets(buffer, buffer_length, input);
	if(fgets_status==NULL){
		loadError(line); return -1;
	}
	sscanf_status=sscanf(buffer, "%s", state_output);
	if(sscanf_status!=1){
		parseError(line); return -1;
	}
	line++;
	cout << "Format of eigenstates output files: " << state_output << endl;


	return 1;
}
