#!/bin/bash
rm *.o
rm *.so
g++ -c -fPIC jppp.cc -o jppp.o \
    -I$(root-config --incdir) \
    $(python-config --includes) \
    -I$JPP_INC
g++ -shared -Wl \
    $(root-config --libs) \
    $(python-config --libs) \
    -L${JPP_LIB} \
    -lKM3NeTDAQROOT \
    -o libjppp.so  jppp.o
