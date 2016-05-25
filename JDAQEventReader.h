#ifndef JDAQEVENTREADER_H
#define JDAQEVENTREADER_H

namespace jppy {
    class JDAQEventReader {
    public:
        JDAQEventReader();
        JDAQEventReader(char* filename);
        void retrieveNextEvent();
        int getFrameIndex();
        int getNumberOfSnapshotHits();
        void getHits(int* channel_ids, int* dom_ids, int* times, int* tots);
        bool hasNext();
//  private:
//      JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
//      KM3NETDAQ::JDAQEvent* event;
    };
}

#endif /* JDAQEVENTREADER_H */
