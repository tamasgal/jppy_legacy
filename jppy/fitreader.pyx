# distutils: language=c++
# distutils: sources = src/JFitReader.cpp
# vim:set ts=4 sts=4 sw=4 et:
from libcpp cimport bool

import numpy as np
cimport numpy as np
cimport cython

np.import_array()

#
# cdef extern from "JFit/JFitParameters.hh" namespace "jppy":
#     cdef enum JFitParameter:
#         JGANDALF_BETA0_RAD = 0
#         JGANDALF_BETA1_RAD = 1
#         JGANDALF_CHI2 = 2
#         JGANDALF_NUMBER_OF_HITS = 3
#         JENERGY_ENERGY = 4
#         JENERGY_CHI2 = 5
#         JGANDALF_LAMBDA = 6
#         JGANDALF_NUMBER_OF_ITERATIONS = 7
#         JSTART_NPE_MIP = 8
#         JSTART_NPE_MIP_TOTAL = 9
#         JSTART_LENGTH_METRES = 10
#         JVETO_NPE = 11
#         JVETO_NUMBER_OF_HITS = 12
#

cdef extern from "JFitReader.h" namespace "jppy":
    cdef cppclass JFitReader:
        JFitReader() except +
        JFitReader(char* filename) except +
        void retrieveNextEvent()
        int getNFits()
        bool hasNext()
        void getFits(
            double* pos_xs,
            double* pos_ys,
            double* pos_zs,
            double* dir_xs,
            double* dir_ys,
            double* dir_zs,
            int* ndfs,
            double* times,
            double* qualities,
            double* energies
        )


cdef class PyJFitReader:
    cdef JFitReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JFitReader(filename)

    def retrieve_next_event(self):
        self.c_reader.retrieveNextEvent()

    @property
    def n_fits(self):
        return self.c_reader.getNFits()

    @property
    def has_next(self):
        return self.c_reader.hasNext()

    def get_fits(self,
                 np.ndarray[double, ndim=1, mode="c"] pos_xs not None,
                 np.ndarray[double, ndim=1, mode="c"] pos_ys not None,
                 np.ndarray[double, ndim=1, mode="c"] pos_zs not None,
                 np.ndarray[double, ndim=1, mode="c"] dir_xs not None,
                 np.ndarray[double, ndim=1, mode="c"] dir_ys not None,
                 np.ndarray[double, ndim=1, mode="c"] dir_zs not None,
                 np.ndarray[int, ndim=1, mode="c"] ndfs not None,
                 np.ndarray[double, ndim=1, mode="c"] times not None,
                 np.ndarray[double, ndim=1, mode="c"] qualities not None,
                 np.ndarray[double, ndim=1, mode="c"] energies not None,
                 ):
        self.c_reader.getFits(
                &pos_xs[0],
                &pos_ys[0],
                &pos_zs[0],
                &dir_xs[0],
                &dir_ys[0],
                &dir_zs[0],
                &ndfs[0],
                &times[0],
                &qualities[0],
                &energies[0],
                )
