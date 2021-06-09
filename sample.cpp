// C++ program to find out execution time of
// of functions
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#ifdef PARALLEL
#include <mpi.h>
#endif

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv)
{

#ifdef PARALLEL
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    cout << processor_name << " ";
    cout << world_size << " ";
    cout << world_rank << endl;
#endif



    auto default_duration = 5000;

    if (argc >= 2) {
        default_duration = atoi(argv[1]);
    }

    vector<int> values(10000);

    auto f = []() -> int { return rand() % 10000; };

    auto start = high_resolution_clock::now();

    generate(values.begin(), values.end(), f);

    sort(values.begin(), values.end());

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    while (duration.count() <= default_duration) {

        generate(values.begin(), values.end(), f);

        sort(values.begin(), values.end());

        stop = high_resolution_clock::now();

        duration = duration_cast<milliseconds>(stop - start);

    }

#ifdef PARALLEL
    MPI_Finalize();
#endif

    return 0;
}