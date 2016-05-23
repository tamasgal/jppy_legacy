#!/bin/bash
make clean
rm libreadout.so
make

g++ -shared -Wl \
    -L${JPP_LIB} \
    -L${ANTRS_LIB} \
    `/usr/local/root/v5.34.23//bin/root-config --libs` \
    -lKM3NeTDAQROOT \
    -llang \
    -lpython \
    -o libreadout.so  readout.o
