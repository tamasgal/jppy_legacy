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
        void getHits()
        int getNumberOfHits()


cdef class PyJDAQTimesliceReader:
    cdef JDAQTimesliceReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JDAQTimesliceReader(filename)

    def retrieve_next_timeslice(self):
        self.c_reader.retrieveNextTimeslice()

    def retrieve_next_superframe(self):
        self.c_reader.retrieveNextSuperframe()

    def get_hits(self):
        self.c_reader.getHits()

    @property
    def has_next(self):
        return self.c_reader.hasNext()

    @property
    def has_next_superframe(self):
        return self.c_reader.hasNextSuperframe()

    @property
    def number_of_hits(self):
        return self.c_reader.getNumberOfHits()
