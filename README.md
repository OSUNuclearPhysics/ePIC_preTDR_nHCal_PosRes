# ePIC_preTDR_nHCal_eh-ratio

## e/h response

### Run Simulation Jobs

```bash
cd simjobsubmission
```

use `./run.sh` on BNL-SDCC shell

It will run multiple jobs with particle gun type and momentum specified - `particle_p_all.txt`, the execution script is defined in `runSimBatch.sh`.

The analysis macro for filling hitograms with energy deposition is defined in `readHCalSimReader.C`. This macro is executed on Simulation output files.


### Run local analysis

After the jobs have finished one needs to merge the files.

```bash
cd /parent/to/desired/outputdirectory/withparticleandmomentum (Outputdir = /gpfs/mnt/gpfs02/eic/palspeic/simdir/ebyh_response/Steel/ in submitSim.job)
hadd -f output_e-_1GeV_hcal_only.root e-_1GeV_hcal_only/*
hadd -f output_pi-_1GeV_hcal_only.root pi-_1GeV_hcal_only/*
hadd -f output_e-_2GeV_hcal_only.root e-_2GeV_hcal_only/*
hadd -f output_pi-_2GeV_hcal_only.root pi-_2GeV_hcal_only/*
```
and so on..

change the names of the files in alphabetic order with increasing momentum (aoutput_e-_1GeV_hcal_only.root, boutput_e-_2GeV_hcal_only.root, aoutput_pi-_1GeV_hcal_only.root, boutput_pi-_2GeV_hcal_only.root, etc.)

copy `output*hcal_only.root`s (1,2,5,10,20) to a directory named `high_energy`. 
copy `ebyh_ana.C` to the parent directory of `high_energy`.
One can further analyze it and plot energy deposition distribution, sampling fraction, etc. using `ebyh_ana.C ("particle species (e.g. e-)", "high_energy")`

repeat the same procedure for pi-.

copy `ebyh_ratio.C` to the parent directory of `high_energy`.
run `ebyh_ratio.C` to get e/h ratio plot.
