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
git checkout 0e1566c91b04605618c4571e72c3cfba18b2cb11
cd EICrecon
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=install
cmake --build build -- install -j4
```

### Submit simulation and reconstruction jobs
```bash
cd ../
./run_all.sh
```
This will run simulation and reconstruction jobs with neutron gun pointed at ``` theta = 155 degree ``` and  ``` phi = 45 degree ``` and pion gun pointed at theta value (in degrees) taken from the 2nd column of ``` pionangles.txt ``` and phi value (in degrees) from the 1st column. The corresponding outputfiles will be stored in the ```Phi*Theta*``` directories created during the jobsubmission.


