
.PHONY: run serial parallel clean

default: serial mpi_sample

serial: sample

parallel: mpi_sample

sample: sample.o
	g++ $^ -o $@

sample.o: sample.cpp
	g++ -c $^ -o $@

mpi_sample: mpi_sample.o
	mpic++ $^ -o $@

mpi_sample.o: sample.cpp
	mpic++ -DPARALLEL -c $^ -o $@


clean:
	rm -rf *.o mpi_sample sample


run:
	time ./sample 10000
