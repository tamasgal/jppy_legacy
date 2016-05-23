#!/bin/bash
rm -f *.o
rm -f *.so
g++ -c -fPIC jppp.cc -o jppp.o \
    -I$(root-config --incdir) \
    $(python-config --includes) \
    -I$JPP_INC
g++ -shared \
    $(root-config --libs) \
    $(python-config --libs) \
    -L${JPP_LIB} \
    -lKM3NeTDAQROOT \
    -o libjppp.so  jppp.o
