#!/bin/bash
#SBATCH --nodes  2            # number of nodes (2)
#SBATCH --ntasks 2            # number of tasks (2, default one task per node)
#SBATCH --time=0:01:00        # run time of the job (5 min)
#SBATCH --job-name="hostname" # name of the job (hostname)

# run (srun: run job on cluster with provided resources/allocation)
srun hostname
