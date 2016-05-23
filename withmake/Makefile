JPP_DIR := $(JPP_DIR)

include $(JPP_DIR)/Makerules

CXXFLAGS  += -I$(ANTRS_INCLUDE) -I/afs/in2p3.fr/throng/km3net/src/python/2.7.11/include
LDFLAGS   += -L$(ANTRS_LIB)

#CXXFLAGS  += -pg
#LDFLAGS   += -pg

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)
BINS := $(OBJS:.o=)

include $(JPP_DIR)/Makedependencies

readout: LOADLIBES+= $(ROOTLIBS) $(JDAQ_LIBS) $(JPPLIBS)

#libreadout.so : $(OBJS)
#	$(CXX) $(SOFLAGS) -o $@ $^
#	$(CXX) $(ROOTLIBS) $(JDAQ_LIBS) $(JPPLIBS) $(LDFLAGS) -O -shared -Wl -o $@ $^
