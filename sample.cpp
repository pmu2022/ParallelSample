// C++ program to find out execution time of
// of functions
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv)
{
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

    return 0;
}