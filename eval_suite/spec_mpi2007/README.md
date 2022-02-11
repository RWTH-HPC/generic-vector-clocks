# Runner Script

## Usage

Execute `./run_mpi2007.sh` with the following options.

-`t` Space-separated list of SPEC MPI2007 benchmark kernels. Default: `104`

-`n` Space-separated list of number of nodes. Default:  `1 2 4`

-`s` Choose between tool processes (`mpi`) or threads (`thread`). Default: `mpi`

-`c` Collective VC strategies. Choose from `raw`, `plain`, `naive`, `binomial` and `mpi`. Default: `raw plain naive binomial mpi`

-`i` Number of iterations performed by runspec. Default: `3`

-`d` SPEC MPI2007 dataset size: `test` or `ref`. Default: `ref`

-`b` Tasks per node. Default: `24`

-`m` Flag to choose medium data set over the large one for benchmarks which accept both. Default: `large`

-`p` Flag to disable task binding. Default: `bound`

## Output

- Slurm output goes into `outputs`.

- Measured data can be found in `eval_results`. Results for each run are in a timestamped directory.
