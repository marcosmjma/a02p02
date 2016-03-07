#PBS -l select=2:ncpus=1:mem=4gb:interconnect=mx
#PBS -j oe
#PBS -o a02p02-1.out

cd $PBS_O_WORKDIR
module load inter/15.0 openmpi/1.8.4
mpirun ./a02p02 10 10 > measures.dat

module load anaconda/2.5.0
./plot.py measures.dat
