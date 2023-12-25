#include "variables_ext.hpp"

void initialize(){
	buffer_length=1024;
	input_default=(char*)"input.dat";
	fileName_length=256;
	realNumber_format=(char*)"%12.5e";

	// array initialization
	value_output=new char[fileName_length];
	state_output=new char[fileName_length];
}
