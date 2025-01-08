#!/bin/bash
####source cleanup.sh
##gun_momenta=(0.5 1 2 5 10 20) #gun_momenta
gun_momenta=(1) #gun_momenta
for energy in ${gun_momenta[@]}; do
    ./step0_run.sh $energy
done

# ~/condor_control.sh # wait for all jobs to finish

# merge different output files (Phi*Theta*) into one
#for energy in ${gun_momenta[@]}; do
 #   workdir=/gpfs/mnt/gpfs02/eic/palspeic/twopartreso_v2/ePICRecoDataAnalysis/output
    ##echo "hadd -f -k $workdir/output_${energy}.edm4hep.root $workdir/Phi*Theta*/outputFill_${energy}_*.root" | /eic/u/palspeic/eic-shell
 # done
