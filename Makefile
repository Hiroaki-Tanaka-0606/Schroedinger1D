option = -lblas -llapack

target = Schroedinger_main.o initialize.o loadInput.o lapack.o utils.o

target_well = Schroedinger_well_main.o initialize.o loadInput_well.o lapack.o utils.o

all: Schroedinger.o Schroedinger_well.o

Schroedinger.o: $(target)
	$(CXX) $^ $(option) -o $@

Schroedinger_well.o: $(target_well)
	$(CXX) $^ $(option) -o $@

.cpp.o:
	$(CXX) -c $<

Schroedinger_main.o: variables.hpp
initialize.o: variables_ext.hpp
loadInput.o: variables_ext.hpp
lapack.o: variables_ext.hpp
utils.o: variables_ext.hpp
