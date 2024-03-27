#!/bin/bash
#
#SBATCH --job-name=Gibbs-4
#SBATCH --output=res.txt
#
#SBATCH --mail-user=esteban.foncoux@student.unamur.be
#SBATCH --mail-type=ALL
#
#SBATCH --time=10:00:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem-per-cpu=3000
#
#SBATCH --array=0-99

cd $HOME/MMMI/build
module load GSL

srun ./main_classe_4 $SLURM_ARRAY_TASK_ID
