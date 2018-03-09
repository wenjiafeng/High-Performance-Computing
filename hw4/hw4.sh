#!/bin/bash
#SBATCH -o hw4.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH -p defq

module add openmpi/gcc/64/1.10.1
mpirun hw4

