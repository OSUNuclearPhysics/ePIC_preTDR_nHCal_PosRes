#!/bin/sh

export GUN_PHI=${3}
export GUN_THETA=${4}
export GUN_MOMENTUM=${5}
export GUN_PARTICLE=pi-
export NUMBER_OF_EVENTS=100000
export CLUSTER=${1}
export PROCESS=${2}

export FILENAME=${GUN_PARTICLE}_${NUMBER_OF_EVENTS}events_p${GUN_MOMENTUM}gev_phi${GUN_PHI}_theta${GUN_THETA}
##export DDSIM_FILE=sim_${FILENAME}_${CLUSTER}_${PROCESS}.edm4hep.root
export DDSIM_FILE=sim_${FILENAME}.edm4hep.root
##export EICRECON_FILE=eicrecon_${FILENAME}_${CLUSTER}_${PROCESS}.edm4eic.root
export EICRECON_FILE=eicrecon_${FILENAME}.edm4eic.root

echo "source step3_main.sh epic" | /eic/u/palspeic/eic-shell
