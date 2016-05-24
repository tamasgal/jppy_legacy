# distutils: language = c++
# distutils: sources = jppp.cc

cdef extern from "jppp.h" namespace "jppp":
    cdef cppclass JDAQEventReadout:
        pass
