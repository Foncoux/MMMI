#!/bin/bash
#
#SBATCH --job-name=NOMAD-MADS
#SBATCH --output=res.txt
#
#SBATCH --mail-user=esteban.foncoux@student.unamur.be
#SBATCH --mail-type=ALL
#
#SBATCH --time=04:00:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=2000
#
#SBATCH --array=0-99

cd $HOME/MMMI/build
module load GSL

srun ./main $SLURM_ARRAY_TASK_ID

