#!/bin/bash
#SBATCH -o hw5.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=12
#SBATCH -p defq

module add openmpi/gcc/64/1.10.1
mpirun hw5

