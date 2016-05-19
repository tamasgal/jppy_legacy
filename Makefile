JPP_DIR := $(JPP_DIR)

include $(JPP_DIR)/Makerules

CXXFLAGS  += -I$(ANTRS_INCLUDE)
LDFLAGS   += -L$(ANTRS_LIB)

#CXXFLAGS  += -pg
#LDFLAGS   += -pg

SRCS := $(wildcard *.cc)
OBJS := $(SRCS:.cc=.o)
BINS := $(OBJS:.o=)
#APPS := $(addprefix $(JPP_BIN), $(BINS))

include $(JPP_DIR)/Makedependencies

readout:	LOADLIBES+= $(ROOTLIBS) $(JDAQ_LIBS) $(JPPLIBS)
