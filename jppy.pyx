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
        bool hasNext()
        int getNumberOfSnapshotHits()
        void getHits(int* channel_ids, int* dom_ids, int* times, int* tots)


cdef class PyJDAQEventReader:
    cdef JDAQEventReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JDAQEventReader(filename)

    def retrieve_next_event(self):
        self.c_reader.retrieveNextEvent()

    def get_frame_index(self):
        return self.c_reader.getFrameIndex()

    def get_number_of_snapshot_hits(self):
        return self.c_reader.getNumberOfSnapshotHits()

    def get_hits(self,
                 np.ndarray[int, ndim=1, mode="c"] channel_ids not None,
                 np.ndarray[int, ndim=1, mode="c"] dom_ids  not None,
                 np.ndarray[int, ndim=1, mode="c"] times not None,
                 np.ndarray[int, ndim=1, mode="c"] tots not None):
        self.c_reader.getHits(&channel_ids[0], &dom_ids[0], &times[0], &tots[0])
