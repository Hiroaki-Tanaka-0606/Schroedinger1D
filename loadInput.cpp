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

int loadInput(FILE* input){
	char buffer[buffer_length];
	char* fgets_status;
	int sscanf_status;
	int line=1;
	int i;

	// line 1: nn (number of 'n's)
	fgets_status=fgets(buffer, buffer_length, input);
	if(fgets_status==NULL){
		loadError(line); return -1;
	}
	sscanf_status=sscanf(buffer, "%d", &nn);
	if(sscanf_status!=1){
		parseError(line); return -1;
	}
	line++;
	cout << "Number of 'n's: " << nn << endl;
	
	// lines 2-(nn+1): n, a_n (cosine coefficient), and b_n (sine coefficient)
	nArray=new int[nn];
	a_n=new double[nn];
	b_n=new double[nn];
	for(i=0;i<nn;i++){
		fgets_status=fgets(buffer, buffer_length, input);
		if(fgets_status==NULL){
			loadError(line); return -1;
		}
		sscanf_status=sscanf(buffer, "%d%lf%lf", &nArray[i], &a_n[i], &b_n[i]);
		if(sscanf_status!=3){
			parseError(line); return -1;
		}
		line++;
	}
	// output V(x)
	cout << "V(x) =" << endl;
	for(i=0;i<nn;i++){
		if(i!=0){
			cout << "+ ";
		}else{
			cout << "  ";
		}
		printf(realNumber_format,a_n[i]);
		printf(" * cos(%d*pi*x) + ", nArray[i]*2);
		printf(realNumber_format,b_n[i]);
		printf(" * sin(%d*pi*x)\n", nArray[i]*2);
	}

	// line (nn+2): N (nubmer of meshes)
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

	// line (nn+3): k points specification
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

	// line (nn+4): Neigen (number of eigenstates to be output)
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

	// line (nn+5): eigenvalue file
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
	
	// line (nn+5): eigenstates file
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
