SRC = readout.cc
OBJ = ${SRC:.cc=.o}
BIN = ${SRC:.cc=}

#SOFLAGS += -soname
CXX = g++ -Wall -llang ${SOFLAGS}

ROOTFLAGS += $(/usr/local/root/v5.34.23/bin/root-config --libs)
DAQ += -lKM3NeTDAQROOT 
JPPLIBS = -L${JPP_DIR}/out/Linux/lib/ 
JPPLIBS +=-L${JPP_DIR}/externals/antares-daq/out/Linux/lib/ 

CXXFLAGS  += -I$(ANTRS_INCLUDE)
LDFLAGS   += -L$(ANTRS_LIB)

#g++ -shared -Wl,-soname,libreadout.so $(JPPLIBS) `/usr/local/root/v5.34.23//bin/root-config --libs` -lKM3NeTDAQROOT -llang -o libreadout.so  readout.o

all: options libreadout.so

.c.o:
	@echo CXX $<
	@${CXX} -c ${CXXFLAGS}  $<

options:
	@echo st build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CXX       = ${CXX}"

libreadout.so: ${OBJ}
	@echo CXX -o $@
	@${CXX} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	rm -f readout ${OBJ}

.PHONY: options all clean
