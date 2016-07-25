#ifndef JDAQSUMMARYSLICEREADER_H
#define JDAQSUMMARYSLICEREADER_H

namespace jppy {
    class JDAQSummarysliceReader {
    public:
        JDAQSummarysliceReader();
        JDAQSummarysliceReader(char* filename);
        void retrieveNextSummaryslice();
        int getUDPNumberOfReceivedPackets();
        bool hasNext();
    };

}

#endif /* JDAQSUMMARYSLICEREADER_H */
