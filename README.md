# TSP-NS : Time Slice based Parallelized Network Simulator

This is a parallelized discrete event simulator for network test. The implemented functions are very limited till now. But the core functions are all ready.

## Structure
``` txt
<TSP-NS>
├── core-parallel     ## This is the parallel-core  
├── network           ## Very simple network implementation using parallel-core  
├── lib               ## dependences
└── example           ## How to use it is shown here  
```
 

## Dependences
1. git
2. cmake
3. pthread library

## Usage
Firstly, you need to clone the respority and init the submodules used in this project.
``` bash
git clone https://github.com/mmhzheng/TSP-NS.git
```
Then you need to setup the dependences.
```bash
sudo ./setup.sh
```
Now you can take a look at example/simple_topo.cpp and run it! You can check log file to see the running process.
```bash
cd example
./auto_build.sh
./test_simple_topo
```

## Reference Code
This project needs to thanks  [g3logger](https://github.com/KjellKod/g3log.git), [ThtreadPool](https://github.com/progschj/ThreadPool.git) and [skiplist](https://github.com/greensky00/skiplist).