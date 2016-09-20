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
        void retrieveNextTimeslice()
        void retrieveNextSuperframe()
        bool hasNext()
        bool hasNextSuperframe()
        void getHits(int* channel_ids, int* dom_ids, int* times, int* tots)
        int getNumberOfHits()


cdef class PyJDAQTimesliceReader:
    cdef JDAQTimesliceReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JDAQTimesliceReader(filename)

    def retrieve_next_timeslice(self):
        self.c_reader.retrieveNextTimeslice()

    def retrieve_next_superframe(self):
        self.c_reader.retrieveNextSuperframe()

    def get_hits(self,
                 np.ndarray[int, ndim=1, mode="c"] channel_ids not None,
                 np.ndarray[int, ndim=1, mode="c"] dom_ids  not None,
                 np.ndarray[int, ndim=1, mode="c"] times not None,
                 np.ndarray[int, ndim=1, mode="c"] tots not None):
        self.c_reader.getHits(&channel_ids[0], &dom_ids[0], &times[0], &tots[0])

    @property
    def has_next(self):
        return self.c_reader.hasNext()

    @property
    def has_next_superframe(self):
        return self.c_reader.hasNextSuperframe()

    @property
    def number_of_hits(self):
        return self.c_reader.getNumberOfHits()
