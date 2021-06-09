
.PHONY: run

sample: sample.o
	g++-10 sample.o -o sample

sample.o: sample.cpp
	g++-10 -c $^ -o $@

run:
	time ./sample 10000
