#!/bin/bash

source ~/geant4.sh
source ~/root528.sh

./injector run.mac
root -q analysis.C
