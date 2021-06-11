import inspect
import subprocess
import sys
import psutil
import os

import joblib
from joblib import delayed

VERBOSITY = 100000

try:
    duration = int(sys.argv[1])
except IndexError:
    duration = 10000

try:
    jobs = int(sys.argv[2])
except IndexError:
    jobs = 8


def run_subprocess():
    name = inspect.stack()[0][3]
    print(f'START: {name}')
    subprocess.run(['./sample', str(duration)])
    print(f'END: {name}')


def run_parallel_subprocess(number):
    name = inspect.stack()[0][3]
    print(f'START: {name}')
    subprocess.run(['mpirun', '-n', str(number), './sample', str(duration)])
    print(f'END: {name}')


if __name__ == '__main__':
    nr_cpu_logical = psutil.cpu_count(logical=True)
    print(f'CPU (including logical): {nr_cpu_logical:4d}')

    nr_cpu_non_logical = psutil.cpu_count(logical=False)
    print(f'CPU (only physical):     '
          f'{nr_cpu_non_logical:4d}')

    sched_affinity = len(os.sched_getaffinity(0))
    print(f'CPU (affinity):         '
          f'{sched_affinity:4d}')

    jobs = jobs // 2

    print(f'Jobs (specified):       '
          f'{jobs:4d}')

    with joblib.Parallel(n_jobs=jobs, verbose=VERBOSITY) as parallel:
        parallel_jobs = [delayed(run_parallel_subprocess)(2) for i in range(
            jobs)]

        parallel(parallel_jobs)
