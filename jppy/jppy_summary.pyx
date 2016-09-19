# distutils: language = c++
# distutils: sources = JDAQSummarysliceReader.cpp
# vim:set ts=4 sts=4 sw=4 et:

from libcpp cimport bool

import numpy as np
cimport numpy as np
cimport cython

np.import_array()


cdef extern from "JDAQSummarysliceReader.h" namespace "jppy":
    cdef cppclass JDAQSummarysliceReader:
        JDAQSummarysliceReader() except +
        JDAQSummarysliceReader(char* filename) except +
        void retrieveNextSummaryslice()
        int getUDPNumberOfReceivedPackets()
        bool hasNext()


cdef class PyJDAQSummarysliceReader:
    cdef JDAQSummarysliceReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JDAQSummarysliceReader(filename)

    def retrieve_next_summary_slice(self):
        self.c_reader.retrieveNextSummaryslice()

    @property
    def number_of_received_packets(self):
        return self.c_reader.getUDPNumberOfReceivedPackets()

    @property
    def has_next(self):
        return self.c_reader.hasNext()
