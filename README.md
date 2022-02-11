# An On-the-Fly Method to Exchange Vector Clocks in Distributed-Memory Programs - Supplemental Material
Authors: Simon Schwitanski, Felix Tomski, Joachim Protze, Christian Terboven, and Matthias S. Müller

This is supplemental material for the HIPS 2022 workshop paper "An On-the-Fly Method to Exchange Vector Clocks in Distributed-Memory Programs".


## Repository Structure
- [source](source/): Generic vector clock implementation with support for MPI and OpenSHMEM based on GTI
- [eval_results](eval_results/): Measurements results shown in the paper
- [eval_suite](eval_suite/): Custom-implemented benchmark suite to reproduce the SPEC MPI 2007 measurements
- [layout_samples](layout_samples/): Layout examples that can be used to run MUST with own applications
- [patches](patches/): UCX patch to support OpenSHMEM + MUST (experimental)


## Supported Programming Models
The current implementation supports all in the paper mentioned MPI functions and includes experimental support for most OpenSHMEM functions (see below for details).


## Source Code
The sources of our vector clock implementation is available in the subfolder `source`. Note that the folder contains a bunch of files unrelated to the paper.
The contributions can be found in the following folders and files:
- Generic vector clock module in GTI
    - [source/externals/GTI/modules/gti-internal/I_VectorClock.h](source/externals/GTI/modules/gti-internal/I_VectorClock.h)
    - [source/externals/GTI/modules/gti-internal/VectorClock.h](source/externals/GTI/modules/gti-internal/VectorClock.h)
    - [source/externals/GTI/modules/gti-internal/VectorClock.cpp](source/externals/GTI/modules/gti-internal/VectorClock.cpp)
    - [source/externals/GTI/system-builder/specifications/gti-implicit-analysis-spec.xml](source/externals/GTI/system-builder/specifications/gti-implicit-analysis-spec.xml)
    - [source/externals/GTI/system-builder/specifications/gti-vectorclock-api-spec.xml](source/externals/GTI/system-builder/specifications/gti-vectorclock-api-spec.xml)
- Annotation API
    - [source/specifications/must_annotation_api_spec.xml](source/specifications/must_annotation_api_spec.xml)
- Collective vector-clock exchange strategy
    - [source/externals/GTI/modules/coll-strategy](source/externals/GTI/modules/coll-strategy)
- MPI-specific + SHMEM-specific vector clock wrappers
    - [source/modules/VectorClockWrapper](source/modules/VectorClockWrapper)
- Vector clock tests (MPI + OpenSHMEM)
    - [source/tests/VectorClock](source/tests/VectorClock)


## Building
The vector clock analysis module is part of GTI / MUST. MUST is built with CMake. The build script will detect your installed MPI library.
To enable vector clock output (i.e., printing vector clock values to standard output) and to make the tests work, you should build in `Debug` mode. Alternatively, you can set `VC_DEBUG` to a debug level in [source/externals/GTI/modules/gti-internal/VectorClock.cpp](source/externals/GTI/modules/gti-internal/VectorClock.cpp). If you want to reproduce our measurements, you should use the `Release` mode which will turn off any debug output.

A typical build command (enabled tests will require LLVM lit and FileCheck) looks as follows:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/your/installdir -DENABLE_TESTS=ON -DMPI_C_COMPILER=mpicc -DMPI_CXX_COMPILER=mpicxx -DLLVM_FILECHECK_PATH=/your/path/to/FileCheck -DLLVM_LIT_PATH=/your/path/to/lit ..
make -j8 install
```

Details on how to build MUST can also be found on our webpage of production-ready releases: https://itc.rwth-aachen.de/must/.


### OpenSHMEM Support (experimental)
Note that OpenSHMEM support is only *experimental*. It works with the OpenSHMEM implementation included with OpenMPI (tested with version 4.1.1) and requires adaption of UCX (see next paragraph). You should pass `oshcc` and `oshcxx` as `MPI_C_COMPILER` and `MPI_CXX_COMPILER` to CMake. The OpenSHMEM module and tests will only be built if an OpenSHMEM (liboshmem) installation is detected.

The way how OpenMPI internally uses UCX to implement OpenSHMEM breaks with the multithreading that MUST internally requires to exchange data. UCX will throw assertions that will prevent to run OpenSHMEM programs with MUST at all. A workaround to avoid that is to remove the corresponding assertions in UCX. We provided a patch for that in the `patches` directory (tested with UCX 1.11.2).

For details on the supported OpenSHMEM functions, see the [source/tests/VectorClock/OpenSHMEM](source/tests/VectorClock/OpenSHMEM) directory and test cases on OpenSHMEM support.


## Testing
The vector clock implementation comes with LLVM `lit` tests included in [source/tests/VectorClock](source/tests/VectorClock). In order to run them, you have to enable tests in CMake with `-DENABLE-TESTS=ON` and ensure that you have LLVM `lit` installed. To run the vector clock tests, you should run in your build directory

```
lit tests/VectorClock
```

## Running Own Applications
If you want to test the implementation on your own programs, you can run MUST using the layouts provided in the [layout_samples](layout_samples) folder. We provided 3 example layouts:

- [layout_mpi_tool_procs.xml](layout_samples/layout_mpi_tool_procs.xml): Vector clock analysis on MPI using tool processes (default, this is how we also measured the SPEC 2007 benchmarks)
- [layout_mpi_tool_threads.xml](layout_samples/layout_mpi_tool_threads.xml): Vector clock analysis on MPI using tool threads, no additional MPI processes required
- [layout_shmem_tool_threads.xml](layout_samples/layout_shmem_tool_threads.xml): OpenSHMEM using tool threads to do the vector clock analysis (tool processes for OpenSHMEM are currently not supported)

Modify the layout XML file and replace `#NUM_PROCS#` with the desired number of processes your MPI program should be run with. Then, run the following command:

```
/your/installdir/bin/mustrun --must:layout $(pwd)/layout_sample.xml ./my_application
```

This will invoke MUST together with `mpiexec` and run your application. In case you built MUST in `Debug` mode or you set `VC_DEBUG` in the vector clock module, you will see output of the vector clock module.


## Evaluation
### Results
The `eval_results` folder contains the measurements of *all* SPEC MPI 2007 benchmarks. In addition to the data in the paper, it also contains evaluation results for the benchmarks that only have an *mref* data set.

The results for the different setups *split nodes* and *shared nodes* are available in the respective subfolders.

The evaluation results are stored
- per benchmark (see bench-*.csv)
- per node configuration (see node-*.csv)

### Suite
We provide our Slurm-based measurement suite that we used on RWTH CLAIX. It serves as a starter to reproduce the SPEC MPI 2007 measurements on other systems / setups. Access to the SPEC MPI 2007 benchmarks is required. Details are provided in the README of the subfolder.

### Setup
We did the SPEC MPI 2007 measurements on RWTH CLAIX18 with the following MPI + compiler configuration:
- Intel MPI 2018.5
- Intel C/C++ and Fortran compiler 19.0