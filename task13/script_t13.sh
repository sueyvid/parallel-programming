#!/bin/bash 
#SBATCH --job-name=PP_t12
#SBATCH --partition=amd-512 
#SBATCH --time=0-0:10
#SBATCH --cpus-per-task=128
#SBATCH --exclusive
#SBATCH --mail-user=sueyvidr8@gmail.com
#SBATCH --mail-type=END

export OMP_PROC_BIND=master

pascalanalyzer ./t13 -g -i 100,200,400,800,1600,3200 -c 1,2,4,8,16,32,64,128 -o t13_master.json

