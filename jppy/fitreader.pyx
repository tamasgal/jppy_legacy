# distutils: language = c++
# distutils: sources = src/JEvtReader.cpp
# vim:set ts=4 sts=4 sw=4 et:
from libcpp cimport bool

import numpy as np
cimport numpy as np
cimport cython

np.import_array()


cdef extern from "JFit/JFitParameters.hh" namespace "jppy":
    cdef enum JFitParameter:
        JGANDALF_BETA0_RAD = 0
        JGANDALF_BETA1_RAD = 1
        JGANDALF_CHI2 = 2
        JGANDALF_NUMBER_OF_HITS = 3
        JENERGY_ENERGY = 4
        JENERGY_CHI2 = 5
        JGANDALF_LAMBDA = 6
        JGANDALF_NUMBER_OF_ITERATIONS = 7
        JSTART_NPE_MIP = 8
        JSTART_NPE_MIP_TOTAL = 9
        JSTART_LENGTH_METRES = 10
        JVETO_NPE = 11
        JVETO_NUMBER_OF_HITS = 12


cdef extern from "JEvtReader.h" namespace "jppy":
    cdef cppclass JEvtReader:
        JEvtReader() except +
        JEvtReader(char* filename) except +
        void retrieveNextEvent()
        int getFrameIndex()
        int getRunNumber()
        int getDetectorID()
        int getTriggerCounter()
        int getTriggerMask()
        int getSize()
        unsigned int getOverlays()
        int getUTCSeconds()
        int getUTCNanoseconds()
        bool hasNext()
        int getNumberOfSnapshotHits()
        void getHits(int* channel_ids, int* dom_ids, int* times, int* tots,
                     int* triggereds)


cdef class PyJEvtReader:
    cdef JEvtReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JEvtReader(filename)

    def retrieve_next_event(self):
        self.c_reader.retrieveNextEvent()

    @property
    def frame_index(self):
        return self.c_reader.getFrameIndex()

    @property
    def run_id(self):
        return self.c_reader.getRunNumber()

    @property
    def det_id(self):
        return self.c_reader.getDetectorID()

    @property
    def has_next(self):
        return self.c_reader.hasNext()

    def get_hits(self,
                 np.ndarray[int, ndim=1, mode="c"] channel_ids not None,
                 np.ndarray[int, ndim=1, mode="c"] dom_ids  not None,
                 np.ndarray[int, ndim=1, mode="c"] times not None,
                 np.ndarray[int, ndim=1, mode="c"] tots not None,
                 np.ndarray[int, ndim=1, mode="c"] triggereds not None):
        self.c_reader.getHits(&channel_ids[0], &dom_ids[0], &times[0], &tots[0],
                              &triggereds[0])
