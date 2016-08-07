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


cdef extern from "JMCEventReader.h" namespace "jppy":
    cdef cppclass JMCEventReader:
        JMCEventReader() except +
        JMCEventReader(char* filename) except +
        void retrieveNextEvent()
        int getNumberOfMCHits()
        int getNumberOfMCTracks()
        void getMCHits()
        void getMCTracks()


#cdef extern from "JDAQSummarysliceReader.h" namespace "jppy":
#    cdef cppclass JDAQSummarysliceReader:
#        pass
#        JDAQSummarysliceReader() except +
#        JDAQSummarysliceReader(char* filename) except +
#        void retrieveNextSummaryslice()
#        int getUDPNumberOfReceivedPackets()
#        bool hasNext()


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


cdef class PyJMCEventReader:
    cdef JMCEventReader c_reader

    def __cinit__(self, char* filename):
        self.c_reader = JMCEventReader(filename)

    @property
    def has_next(self):
        return self.c_reader.hasNext()

    def retrieve_next_event(self):
        self.c_reader.retrieveNextEvent()

    @property
    def number_of_mc_hits(self):
        return self.c_reader.getNumberOfMCHits()

    @property
    def number_of_mc_tracks(self):
        return self.c_reader.getNumberOfMCTracks()

    def get_mc_tracks(self,
                      np.ndarray[int, ndim=1, mode="c"] types not None,
                      np.ndarray[int, ndim=1, mode="c"] origins  not None,
                      np.ndarray[float, ndim=1, mode="c"] pure_dts not None,
                      np.ndarray[float, ndim=1, mode="c"] pure_npes not None,
                      np.ndarray[int, ndim=1, mode="c"] idents not None,
                      np.ndarray[int, ndim=1, mode="c"] pmt_ids not None
                      np.ndarray[float, ndim=1, mode="c"] dts not None,
                      np.ndarray[float, ndim=1, mode="c"] npes not None,
                     ):
        self.c_reader.getMCTracks(
            &types[0], 
            &origins[0],
            &pure_dts[0],
            &pure_npes[0],
            &idents[0],
            &pmt_ids[0],
            &dts[0],
            &npes[0],
        )

    def get_mc_hits(self,
                    np.ndarray[int, ndim=1, mode="c"] types not None,
                    np.ndarray[float, ndim=1, mode="c"] lengths not None,
                    np.ndarray[int, ndim=1, mode="c"] pmt_ids  not None,
                    np.ndarray[float, ndim=1, mode="c"] pos_xs not None,
                    np.ndarray[float, ndim=1, mode="c"] pos_ys not None,
                    np.ndarray[float, ndim=1, mode="c"] pos_zs not None,
                    np.ndarray[float, ndim=1, mode="c"] dir_xs not None,
                    np.ndarray[float, ndim=1, mode="c"] dir_ys not None,
                    np.ndarray[float, ndim=1, mode="c"] dir_zs not None,
                    np.ndarray[float, ndim=1, mode="c"] energies not None,
                    np.ndarray[float, ndim=1, mode="c"] times not None,
                   ):
        self.c_reader.getMCHits(
            &types[0], 
            &lengths[0], 
            &pmt_ids[0], 
            &energies[0],
            &pos_xs[0],
            &pos_ys[0],
            &pos_zs[0],
            &dir_xs[0],
            &dir_ys[0],
            &dir_zs[0],
            &times[0],
        )


#cdef class PyJDAQSummarysliceReader:
#    cdef JDAQSummarysliceReader c_reader
#
#    def __cinit__(self, char* filename):
#        self.c_reader = JDAQSummarysliceReader(filename)
#
#    def retrieve_next_summary_slice(self):
#        self.c_reader.retrieveNextSummaryslice()
#
#    @property
#    def number_of_received_packets(self):
#        return self.c_reader.getUDPNumberOfReceivedPackets()
#
#    @property
#    def has_next(self):
#        return self.c_reader.hasNext()
