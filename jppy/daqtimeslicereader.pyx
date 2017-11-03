# distutils: language = c++
# distutils: sources = src/JDAQTimesliceReader.cpp
# vim:set ts=4 sts=4 sw=4 et:
from libcpp cimport bool

import numpy as np
cimport numpy as np
cimport cython

np.import_array()


cdef extern from "JDAQTimesliceReader.h" namespace "jppy":
    cdef cppclass JDAQTimesliceReader:
        JDAQTimesliceReader() except +
        JDAQTimesliceReader(char* filename) except +
        void initTreeScanner()
        void retrieveTimeslice(int index)
        void retrieveTimesliceAtFrameIndex(int frame_index)
        void retrieveNextTimeslice()
        void retrieveNextSuperframe()
        bool hasNext()
        bool hasNextSuperframe()
        int getNumberOfFrames()
        void getHits(int* channel_ids, int* dom_ids, int* times, int* tots, int start_index)
        int getNumberOfHits()
        int getModuleID()
        int getFrameIndex()
        int getUTCSeconds()
        int getUTCNanoseconds()
        int getUDPNumberOfReceivedPackets()
        int getUDPMaximalSequenceNumber()
        bool hasUDPTrailer()
        bool testWhiteRabbitStatus()
        bool testHighRateVeto()
        bool testFIFOStatus()


cdef class PyJDAQTimesliceReader:
    cdef JDAQTimesliceReader c_reader
    cdef public object slices

    def __cinit__(self, char* filename):
        self.c_reader = JDAQTimesliceReader(filename)
        self.slices = self.slice_generator()

    def init_tree_scanner(self):
        self.c_reader.initTreeScanner()

    def retrieve_timeslice(self, int index):
        self.c_reader.retrieveTimeslice(index)

    def retrieve_timeslice_at_frame_index(self, int frame_index):
        self.c_reader.retrieveTimesliceAtFrameIndex(frame_index)

    def retrieve_next_timeslice(self):
        self.c_reader.retrieveNextTimeslice()

    def retrieve_next_superframe(self):
        self.c_reader.retrieveNextSuperframe()

    @property
    def n_frames(self):
        return self.c_reader.getNumberOfFrames()

    def get_hits(self,
                 np.ndarray[int, ndim=1, mode="c"] channel_ids not None,
                 np.ndarray[int, ndim=1, mode="c"] dom_ids  not None,
                 np.ndarray[int, ndim=1, mode="c"] times not None,
                 np.ndarray[int, ndim=1, mode="c"] tots not None,
                 int start_index = 0):
        self.c_reader.getHits(&channel_ids[0],
                              &dom_ids[0],
                              &times[0],
                              &tots[0],
                              start_index)

    @property
    def has_next(self):
        return self.c_reader.hasNext()

    @property
    def has_next_superframe(self):
        return self.c_reader.hasNextSuperframe()

    # Frame
    @property
    def frame_index(self):
        return self.c_reader.getFrameIndex()

    @property
    def dom_id(self):
        return self.c_reader.getModuleID()

    @property
    def utc_seconds(self): return self.c_reader.getUTCSeconds()

    @property
    def utc_nanoseconds(self): return self.c_reader.getUTCNanoseconds()

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

    @property
    def number_of_hits(self):
        return self.c_reader.getNumberOfHits()

    def slice_generator(self):
        while self.has_next:
            self.retrieve_next_timeslice()
            yield self

    def frame_generator(self):
        while self.has_next_superframe:
            yield self
            self.retrieve_next_superframe()

    def __iter__(self):
        return self

    def next(self):
        """Python 2/3 compatibility for iterators"""
        return self.__next__()

    def __next__(self):
        return next(self.slices)
