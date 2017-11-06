#ifndef PKG_JPPY_SRC_JDAQSUMMARYSLICEREADER_H_
#define PKG_JPPY_SRC_JDAQSUMMARYSLICEREADER_H_

namespace jppy {
class JDAQSummarysliceReader {
    public:
        JDAQSummarysliceReader();
        JDAQSummarysliceReader(char* filename);

        // Summaryslice
        void retrieveNextSummaryslice();
        bool hasNext();
        int getNumberOfFrames();
        int getRunNumber();
        int getDetectorID();
        int getFrameIndex();
        int getUTCSeconds();
        int getUTCNanoseconds();
        // int getTimesliceStart();
        bool hasUDPTrailer();
        bool testWhiteRabbitStatus();
        bool testHighRateVeto();
        bool testFIFOStatus();

        // Frame
        bool hasNextFrame();
        void retrieveNextFrame();
        int getModuleID();
        int getUDPNumberOfReceivedPackets();
        int getUDPMaximalSequenceNumber();
        void getRates(double* rates);
        void getHRVs(int* hrvs);
        void getFIFOs(int* fifos);
};
}

#endif  // PKG_JPPY_SRC_JDAQSUMMARYSLICEREADER_H_
