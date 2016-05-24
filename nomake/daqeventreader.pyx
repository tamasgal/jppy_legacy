# distutils: language = c++
# distutils: sources = JDAQEventReader.cpp

cdef extern from "JDAQEventReader.h" namespace "jppp":
    cdef cppclass JDAQEventReader:
        pass
