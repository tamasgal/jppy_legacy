#ifndef JDAQSUMMARYSLICEREADER_H
#define JDAQSUMMARYSLICEREADER_H

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
        //int getTimesliceStart();
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
    };

}

#endif /* JDAQSUMMARYSLICEREADER_H */
