#ifndef JDAQSUMMARYSLICEREADER_H
#define JDAQSUMMARYSLICEREADER_H

namespace jppy {
    class JDAQSummarysliceReader {
    public:
        JDAQSummarysliceReader();
        JDAQSummarysliceReader(char* filename);
        void retrieveNextSummaryslice();
        void retrieveNextFrame();
        int getModuleID();
        int getUDPNumberOfReceivedPackets();
        int getUDPMaximalSequenceNumber();
        int getRunNumber();
        int getDetectorID();
        int getFrameIndex();
        int getUTCSeconds();
        int getUTCNanoseconds();
        //int getTimesliceStart();
        bool hasNext();
        bool hasNextFrame();
        void debug();
    };

}

#endif /* JDAQSUMMARYSLICEREADER_H */
