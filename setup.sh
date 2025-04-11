#!/bin/bash

export TERM=screen

#source /grid/fermiapp/products/uboone/setup_uboone_mcc9.sh
source /cvmfs/uboone.opensciencegrid.org/products/setup_uboone_mcc9.sh
setup uboonecode v10_04_07_04 -q e26:prof

kx509
htgettoken -a htvaultprod.fnal.gov -i uboone
#httokensh -a htvaultprod.fnal.gov -i uboone -- /bin/bash