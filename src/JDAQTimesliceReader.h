#ifndef PKG_JPPY_SRC_JDAQTIMESLICEREADER_H_
#define PKG_JPPY_SRC_JDAQTIMESLICEREADER_H_

namespace jppy {
class JDAQTimesliceReader {
    public:
        JDAQTimesliceReader();
        JDAQTimesliceReader(char* filename);
        void initTreeScanner();
        void retrieveTimeslice(int index);
        void retrieveTimesliceAtFrameIndex(int frame_index);
        void retrieveNextTimeslice();
        void retrieveNextSuperframe();
        bool hasNext();
        bool hasNextSuperframe();
        int getNumberOfFrames();

        // Frame
        int getModuleID();
        int getFrameIndex();
        int getUTCSeconds();
        int getUTCNanoseconds();
        int getUDPNumberOfReceivedPackets();
        int getUDPMaximalSequenceNumber();
        bool hasUDPTrailer();
        bool testWhiteRabbitStatus();
        bool testHighRateVeto();
        bool testFIFOStatus();
        int getNumberOfHits();
        void getHits(int* channel_ids, int* dom_ids, int* times, int* tots,
            int start_index);
};
}   // namespace jppy

#endif  // PKG_JPPY_SRC_JDAQTIMESLICEREADER_H_
