# distutils: language = c++
# distutils: sources = src/JDAQSummarysliceReader.cpp
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

        bool hasNext()
        void retrieveNextSummaryslice()
        int getNumberOfFrames()
        int getRunNumber()
        int getDetectorID()
        int getFrameIndex()
        int getUTCSeconds()
        int getUTCNanoseconds()

        bool hasNextFrame()
        void retrieveNextFrame()
        int getModuleID()
        int getUDPNumberOfReceivedPackets()
        int getUDPMaximalSequenceNumber()
        bool hasUDPTrailer();
        bool testWhiteRabbitStatus();
        bool testHighRateVeto();
        bool testFIFOStatus();
        void getRates(double* rates)
        void getHRVs(int* hrvs)
        void getFIFOs(int* fifos)

cdef class PyJDAQSummarysliceReader:
    cdef JDAQSummarysliceReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JDAQSummarysliceReader(filename)

    def retrieve_next_summaryslice(self):
        self.c_reader.retrieveNextSummaryslice()

    def retrieve_next_frame(self):
        self.c_reader.retrieveNextFrame()


    @property
    def has_next(self): return self.c_reader.hasNext()

    @property
    def has_next_frame(self): return self.c_reader.hasNextFrame()

    @property
    def n_frames(self): return self.c_reader.getNumberOfFrames()

    @property
    def run_number(self): return self.c_reader.getRunNumber()

    @property
    def det_id(self): return self.c_reader.getDetectorID()

    @property
    def frame_index(self): return self.c_reader.getFrameIndex()

    @property
    def utc_seconds(self): return self.c_reader.getUTCSeconds()

    @property
    def utc_nanoseconds(self): return self.c_reader.getUTCNanoseconds()

    # Frame
    @property
    def dom_id(self):
        return self.c_reader.getModuleID()

    @property
    def number_of_received_packets(self):
        return self.c_reader.getUDPNumberOfReceivedPackets()

    @property
    def max_sequence_number(self):
        return self.c_reader.getUDPMaximalSequenceNumber()

    @property
    def has_udp_trailer(self):
        return self.c_reader.hasUDPTrailer();

    @property
    def white_rabbit_status(self):
        return self.c_reader.testWhiteRabbitStatus();

    @property
    def high_rate_veto(self):
        return self.c_reader.testHighRateVeto();

    @property
    def fifo_status(self):
        return self.c_reader.testFIFOStatus();

    def get_rates(self, np.ndarray[double, ndim=1, mode="c"] rates not None):
        self.c_reader.getRates(&rates[0])

    def get_hrvs(self, np.ndarray[int, ndim=1, mode="c"] hrvs not None):
        self.c_reader.getHRVs(&hrvs[0])

    def get_fifos(self, np.ndarray[int, ndim=1, mode="c"] fifos not None):
        self.c_reader.getFIFOs(&fifos[0])
