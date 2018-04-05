#!/bin/bash
#SBATCH -o hw6.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH -p defq

module add openmpi/gcc/64/1.10.1
mpirun hw6 
