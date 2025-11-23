#!/bin/bash

# execute commands:
# chmod +x run.sh
# ./run.sh


# =========================================
# INSTALLATION STEPS FOR REQUIRED LIBRARIES
# =========================================

echo "=== Installing Required Libraries (Ubuntu) ==="
echo ""

# Update packages
sudo apt update

# 1. GCC
sudo apt install -y build-essential

# 2. Clang
sudo apt install -y clang

# 3. CUDA (NVCC)
# Requires NVIDIA drivers and toolkit
# Make sure to follow NVIDIA instructions: https://developer.nvidia.com/cuda-downloads
# Example for Ubuntu 24.04 + CUDA 12.2:
# sudo apt install -y nvidia-cuda-toolkit
sudo apt install -y nvidia-cuda-toolkit

# 4. MPICC / MPI / OpenMPI
sudo apt install -y mpich libmpich-dev openmpi-bin openmpi-common

# 5. Pthreads and OpenMP (part of GCC build-essential)
# Already installed with build-essential and libomp-dev
sudo apt install -y libomp-dev

# 6. Python + Dask + NumPy
sudo apt install -y python3 python3-pip
pip3 install --upgrade pip
pip3 install numpy dask

echo ""
echo "=== All required libraries installed ==="
echo ""

# =========================================
# COMPILING & RUNNING MULTICORE PROGRAMS
# =========================================

echo "=== COMPILING & RUNNING ALL MULTICORE PROGRAMS (NO CUDA) ==="

echo ""
echo "---- Program 1: MPI ----"
echo "mpicc p1.c -o p1"
mpicc p1.c -o p1
echo "mpirun -np 4 -host localhost:4 ./p1"
mpirun -np 4 -host localhost:4 ./p1

echo ""
echo "---- Program 2a: OpenMP ----"
echo "gcc -fopenmp p2a.c -o p2a"
gcc -fopenmp p2a.c -o p2a
echo "./p2a"
./p2a

echo ""
echo "---- Program 2b: Pthreads ----"
echo "gcc -pthread p2b.c -o p2b"
gcc -pthread p2b.c -o p2b
echo "./p2b"
./p2b

echo ""
echo "---- Program 2c: CUDA ----"
echo "nvcc p2c.cu -o p2c"
nvcc p2c.cu -o p2c
echo "./p2c"
./p2c

echo ""
echo "---- Program 2d: MPI ----"
echo "mpicc p2d.c -o p2d"
mpicc p2d.c -o p2d
echo "mpirun -np 4 -host localhost:4 ./p2d"
mpirun -np 4 -host localhost:4 ./p2d

echo ""
echo "---- Program 3: Parallel Matrix Sum (pthread) ----"
echo "gcc -pthread p3.c -o p3"
gcc -pthread p3.c -o p3
echo "./p3"
./p3

echo ""
echo "---- Program 4: Concurrent Merge Sort ----"
echo "gcc -pthread p4.c -o p4"
gcc -pthread p4.c -o p4
echo "./p4"
./p4

echo ""
echo "---- Program 5: Threaded Bank Transaction ----"
echo "gcc -pthread p5.c -o p5"
gcc -pthread p5.c -o p5
echo "./p5"
./p5

echo ""
echo "---- Program 6: Producer-Consumer (pthread + condvar) ----"
echo "gcc -pthread p6.c -o p6"
gcc -pthread p6.c -o p6
echo "timeout 2s ./p6"
timeout 2s ./p6

echo ""
echo "---- Program 7: Mutex Sync Banking ----"
echo "gcc -pthread p7.c -o p7"
gcc -pthread p7.c -o p7
echo "./p7"
./p7

echo ""
echo "---- Program 8: Condition Variables ----"
echo "gcc -pthread p8.c -o p8"
gcc -pthread p8.c -o p8
echo "timeout 2s ./p8"
timeout 2s ./p8

echo ""
echo "---- Program 9: OpenMP Parallel Summation ----"
echo "gcc -fopenmp p9.c -o p9"
gcc -fopenmp p9.c -o p9
echo "./p9"
./p9

echo ""
echo "---- Program 10: OpenMP Task Parallelism ----"
echo "gcc -fopenmp p10.c -o p10"
gcc -fopenmp p10.c -o p10
echo "./p10"
./p10

echo ""
echo "---- Program 11: Timeout Deadlock Handling ----"
echo "gcc -pthread p11.c -o p11"
gcc -pthread p11.c -o p11
echo "./p11"
./p11

echo ""
echo "---- Program 12: Work-Stealing Simulation ----"
echo "gcc -pthread p12.c -o p12"
gcc -pthread p12.c -o p12
echo "./p12"
./p12

echo ""
echo "=== ALL PROGRAMS COMPLETED SUCCESSFULLY ==="
