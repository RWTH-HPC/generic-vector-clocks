# Preparation Script

## Usage

Execute `./prep.sh` with the following options.

-`t` Tasks per node. Default: `24`.

-`n` Space-separated list of number of nodes. Default:  `1 2 4`

-`s` Choose between tool processes (`mpi`) or threads (`thread`). Default: `mpi thread`

-`c` Collective VC strategies. Choose from `naive`, `binomial` and `mpi`. Default: `naive binomial mpi`

GTI's communication strategies and protocols can be specified in the script.
