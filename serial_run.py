import inspect
import subprocess
import sys

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
    with joblib.Parallel(n_jobs=jobs, verbose=VERBOSITY) as parallel:
        parallel_jobs = [delayed(run_subprocess)() for i in range(jobs)]

    parallel(parallel_jobs)
