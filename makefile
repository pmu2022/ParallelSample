

CXX = icpc
MPICXX = mpiicpc

.PHONY: run serial parallel clean

default: serial mpi_sample

serial: sample

parallel: mpi_sample

sample: sample.o
	$(CXX) $^ -o $@

sample.o: sample.cpp
	$(CXX) -c $^ -o $@

mpi_sample: mpi_sample.o
	$(MPICXX) $^ -o $@

mpi_sample.o: sample.cpp
	$(MPICXX) -DPARALLEL -c $^ -o $@

clean:
	rm -rf *.o mpi_sample sample

run:
	time ./sample 10000
