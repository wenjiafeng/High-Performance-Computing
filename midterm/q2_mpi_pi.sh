#!/bin/bash
#SBATCH -o q2_mpi_pi.out
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=12
#SBATCH -p defq

module add openmpi/gcc/64/1.10.1
mpirun q2_mpi_pi

