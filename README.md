# ePIC_preTDR_nHCal_PosRes
Repository for reproducing position resolution plots for ePIC preTDR nHCal 
## Simulation and Reconstruction
 ```bash
cd sim_and_reco_jobsubmission
```
### Prepare geometry and EICrecon

This study was done with the nHCal only (without the magnet). The default ``` epic/configurations/backward_hcal_only.yml ```  has also magnet included so it needs to be modified (see ``` epic/configurations/backward_hcal_only_womagnet.yml ```).
In ``` eic-shell ```
```bash
git clone https://github.com/eic/epic.git
cp backward_hcal_onlywoMagnet.yml epic/configurations/
cd epic
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
cmake --build build -- install -j4
```
This particular study was done with ``` eicrecon ``` with the commit-hash ``` 0e1566c91b04605618c4571e72c3cfba18b2cb11 ``` where the ClusterMCParticleAssociation was a one-to-one mapping between the nHCal cluster and the MC particle (meaning there was one MC particle associated to a cluster).
```bash
cd ../
git clone https://github.com/eic/EICrecon.git
cd EICrecon
git checkout 0e1566c91b04605618c4571e72c3cfba18b2cb11
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
cmake --build build -- install -j4
```

### Submit simulation and reconstruction jobs
Outside ``` eic-shell ```  
```bash
cd ../
./run_all.sh
```
This will run simulation and reconstruction jobs with neutron gun pointed at ``` theta = 155 degree ``` and  ``` phi = 45 degree ``` and pion gun pointed at theta value (in degrees) taken from the 2nd column of ``` pionangles.txt ``` and phi value (in degrees) from the 1st column. The corresponding simulation and reconstruction outputfiles will be stored in the ```Phi*Theta*``` directories created during the jobsubmission.


## Analysis of the reconstruction data

Inside ``` eic-shell ``` 

```bash 
cd ../
git clone https://github.com/lkosarz/ePICRecoDataAnalysis.git
```
Replace the following files ``` HistogramsReco.h ```, ``` HistogramsRecoClusters ```, ``` readFrameRootRecoMain.C ``` in that cloned repository with the ones inside ``` ePIC_preTDR_nHCal_PosRes ``` .

Create seperate list files inside ``` ePICRecoDataAnalysis/data ``` that would have the list of files for the corresponding reconstruction output files.

```bash 
cd ePICRecoDataAnalysis/data
touch filesReco_155.list filesReco_156.list filesReco_157.list filesReco_158.list filesReco_159.list filesReco_160.list filesReco_161.list filesReco_164.list filesReco_167.list filesReco_170.list
```
Inside each of the list files write the paths of the reconstruction outputs corresponding to pion gun at the mentioned theta angle in degrees. File lists containing ancillary reconstruction data (accessible from BNL SDCC) are already included in this ``` ePICRecoDataAnalysis/data ```.

Perform the analysis for each of the list files seperately by changing the input list and output root file in the line no. 191 of ``` readFrameRootRecoMain.C ```. One needs to compile the repository ``` ePICRecoDataAnalysis ``` to perform analysis (see the README of ``` ePICRecoDataAnalysis ```)
Inside ``` eic-shell ```

```bash
cd ../ 
make
./readFrameRootRecoMain
```

All of the output root files would be stored inside ``` ePICRecoDataAnalysis/output ```.

```bash 
cd output
root -l clusterXYs.C
```
This will produce the Figure 8.173 (Position of the reconstructed clusters in x, y)

```bash
root -l neutronReco_from_chargedHadroncorrection.C
```

This will produce Figures 8.174 and 8.175.





