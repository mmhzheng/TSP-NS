# TSP-NS : Time Slice based Parallized Network Simulator

This is a parallized discrete event simulator for network test. The implemented functions are very limited till now. But the core functions are all ready.

## Structure
<TSP-NS>
├── core-parallel    ## This is the parallel-core
├── example          ## How to use it is shown here
├── lib
└── network          ## Very simple network implementation using parallel-core

## Usage
Firstly, you need to clone the respority and init the submodules used in this project.
``` bash
git clone 
git submodule update --init --recursive
```
Then you need to setup the dependences.
```bash
bash setup.sh
```
Now you can take a look at example/simple_topo.cpp and run it!
```bash
cd example
./auto_build.sh
./test_simple_topo
```

## Reference Code
This project needs to thanks  [g3logger](https://github.com/KjellKod/g3log.git), [ThtreadPool](https://github.com/progschj/ThreadPool.git) and [skiplist](https://github.com/greensky00/skiplist).




