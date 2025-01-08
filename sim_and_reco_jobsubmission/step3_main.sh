#!/bin/sh

angleDir=Phi${GUN_PHI}Theta${GUN_THETA}
mkdir -p $angleDir
cd $angleDir
cp -r ../generate_hepmc3.py .

export GUN_THETA_MIN=$(echo "$GUN_THETA - 0.0001" | bc)
export GUN_THETA_MAX=$(echo "$GUN_THETA + 0.0001" | bc)
export GUN_PHI_MIN=$(echo "$GUN_PHI - 0.0001" | bc)
export GUN_PHI_MAX=$(echo "$GUN_PHI + 0.0001" | bc)
export GUN_MOMENTUM_MIN=$(echo "$GUN_MOMENTUM - 0.00001" | bc)
export GUN_MOMENTUM_MAX=$(echo "$GUN_MOMENTUM + 0.00001" | bc)

source ../epic/install/bin/thisepic.sh
if [ -f "$DDSIM_FILE" ] && [ "$(stat -c %s "$DDSIM_FILE")" -gt 10000 ]; then
   echo "$DDSIM_FILE exists."
else
##   sed -i '34d' generate_hepmc3.py
##   sed -i '34i\    theta = (float(os.environ.get("GUN_THETA"))/180.0)*np.pi' generate_hepmc3.py

   python generate_hepmc3.py $NUMBER_OF_EVENTS $GUN_MOMENTUM $GUN_THETA $CLUSTER $PROCESS
   echo "starting ddsim"   

    ##ddsim --compactFile $DETECTOR_PATH/epic_hcal_only.xml --numberOfEvents ${NUMBER_OF_EVENTS} --random.seed $(date +%N) --enableGun --gun.particle ${GUN_PARTICLE} --gun.thetaMin ${GUN_THETA_MIN}*degree --gun.thetaMax ${GUN_THETA_MAX}*degree --gun.phiMin ${GUN_PHI_MIN}*degree --gun.phiMax ${GUN_PHI_MAX}*degree --gun.distribution uniform --gun.momentumMin ${GUN_MOMENTUM_MIN}*GeV --gun.momentumMax ${GUN_MOMENTUM_MAX}*GeV --outputFile ${DDSIM_FILE}
    ddsim --runType run --compactFile $DETECTOR_PATH/epic_backward_hcal_only_womagnet.xml --numberOfEvents ${NUMBER_OF_EVENTS} --outputFile ${DDSIM_FILE} --inputFiles "output_${GUN_MOMENTUM}_${CLUSTER}_${PROCESS}.hepmc3" 
fi
echo "starting eicrecon"

source ../EICrecon/install/bin/eicrecon-this.sh
if [ -f "$EICRECON_FILE" ] && [ "$(stat -c %s "$EICRECON_FILE")" -gt 10000 ]; then
    echo "$EICRECON_FILE exists."
else
    eicrecon $DDSIM_FILE -Ppodio:output_file=${EICRECON_FILE} -Pjana:nevents=${NUMBER_OF_EVENTS} -Ppodio:output_collections="MCParticles,MCParticleAssociations,HcalEndcapNHitsContributions,HcalEndcapNHitsContributionAssociations,HcalEndcapNHits,HcalEndcapNHitAssociations,HcalEndcapNRawHits,HcalEndcapNRawHitAssociations,HcalEndcapNRecHits,HcalEndcapNRecHitAssociations,HcalEndcapNMergedHits,HcalEndcapNMergedHitHitAssociations,HcalEndcapNIslandProtoClusters,HcalEndcapNIslandProtoClusterAssociations,HcalEndcapNClusters,HcalEndcapNClusterAssociations,HcalEndcapNTruthProtoClusters,HcalEndcapNTruthProtoClusterAssociations,HcalEndcapNTruthClusters,HcalEndcapNTruthClusterAssociations"
    rm -r fieldmaps
fi

###echo "starting analysis"
###root -l '/gpfs/mnt/gpfs02/eic/palspeic/neotwoparticlereso/readHCalRecoReader.C("'${EICRECON_FILE}'" , "outputFill_'${GUN_MOMENTUM}_${CLUSTER}_${PROCESS}'.root")'
