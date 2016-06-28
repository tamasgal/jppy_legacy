# distutils: language = c++
# distutils: sources = JDAQEventReader.cpp
# vim:set ts=4 sts=4 sw=4 et:

from libcpp cimport bool

import numpy as np
cimport numpy as np
cimport cython

np.import_array()


cdef extern from "JDAQEventReader.h" namespace "jppy":
    cdef cppclass JDAQEventReader:
        JDAQEventReader() except +
        JDAQEventReader(char* filename) except +
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


cdef class PyJDAQEventReader:
    cdef JDAQEventReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JDAQEventReader(filename)

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
    def trigger_counter(self):
        return self.c_reader.getTriggerCounter()

    @property
    def trigger_mask(self):
        return self.c_reader.getTriggerMask()

    @property
    def size(self):
        return self.c_reader.getSize()

    @property
    def overlays(self):
        return self.c_reader.getOverlays()

    @property
    def utc_seconds(self):
        return self.c_reader.getUTCSeconds()

    @property
    def utc_nanoseconds(self):
        return self.c_reader.getUTCNanoseconds()

    @property
    def number_of_snapshot_hits(self):
        return self.c_reader.getNumberOfSnapshotHits()

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
