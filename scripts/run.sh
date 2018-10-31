#!/bin/bash

./radiobiology run.mac
octave-cli resave.m
root -q convert_ED.C
open edep.pdf
