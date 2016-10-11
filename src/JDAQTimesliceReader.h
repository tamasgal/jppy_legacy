#ifndef JDAQTIMESLICEREADER_H
#define JDAQTIMESLICEREADER_H

namespace jppy {
    class JDAQTimesliceReader {
    public:
        JDAQTimesliceReader();
        JDAQTimesliceReader(char* filename);
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
        void getHits(int* channel_ids, int* dom_ids, int* times, int* tots);
    };
}

#endif /* JDAQTIMESLICEREADER_H */
