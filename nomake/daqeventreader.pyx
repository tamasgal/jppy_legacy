# distutils: language = c++
# distutils: sources = JDAQEventReader.cpp
# vim:set ts=4 sts=4 sw=4 et:

from libcpp cimport bool

import numpy as np
cimport numpy as np
cimport cython
import ctypes

np.import_array()

cdef extern from "JDAQEventReader.h" namespace "jppp":
    cdef cppclass JDAQEventReader:
        JDAQEventReader() except +
        JDAQEventReader(char* filename) except +
        void retrieve_next_event()
        int get_frame_index()
        bool has_next()
        int get_number_of_snapshot_hits()
        #get_tots(int* tots)
#        int* get_tots()
        void get_tots(int* tots)
        void test_get_tots()


# cdef JDAQEventReader *reader = new JDAQEventReader('../test.root')
# try:
#     print reader.has_next()
# finally:
#     del reader


cdef class PyJDAQEventReader:
    cdef JDAQEventReader c_reader
    def __cinit__(self, char* filename):
        self.c_reader = JDAQEventReader(filename)
    def retrieve_next_event(self):
        self.c_reader.retrieve_next_event()
    def get_frame_index(self):
        return self.c_reader.get_frame_index()
    def get_number_of_snapshot_hits(self):
        return self.c_reader.get_number_of_snapshot_hits()
    def get_tots(self, np.ndarray[int, ndim=1, mode="c"] input not None):
        n = self.get_number_of_snapshot_hits()
        self.c_reader.get_tots(&input[0])
    def test_get_tots(self):
        self.c_reader.test_get_tots()
