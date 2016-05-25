#include <iostream>
#include "JDAQEventReader.h"
#include "JDAQ/JDAQEvent.hh"
#include "JSupport/JMultipleFileScanner.hh"


namespace jppy {

    JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> fileScanner;
    KM3NETDAQ::JDAQEvent* event;

    JDAQEventReader::JDAQEventReader() {}

    JDAQEventReader::JDAQEventReader(char* filename) {
        std::cout << "Filename in c++: " << filename << std::endl;
        fileScanner.open(filename);
    }

    void JDAQEventReader::retrieveNextEvent() { event = fileScanner.next(); }

    int JDAQEventReader::getFrameIndex() { return event->getFrameIndex(); };

    bool JDAQEventReader::hasNext() { return fileScanner.hasNext(); }

    int JDAQEventReader::getNumberOfSnapshotHits()
    {
        std::vector<KM3NETDAQ::JDAQSnapshotHit> snapshotHits
            = event->getHits<KM3NETDAQ::JDAQSnapshotHit>();
        return snapshotHits.size();
    }

    void JDAQEventReader::getHits(int* channel_ids,
                                  int* dom_ids,
                                  int* times,
                                  int* tots)
    {
        std::vector<KM3NETDAQ::JDAQSnapshotHit> snapshotHits
            = event->getHits<KM3NETDAQ::JDAQSnapshotHit>();

        int n = snapshotHits.size();

        for (int i = 0; i < n; i++) {
            channel_ids[i] = (int)snapshotHits[i].getPMT();
            dom_ids[i] = (int)snapshotHits[i].getModuleID();
            times[i] = (int)snapshotHits[i].getT();
            tots[i] = (int)snapshotHits[i].getToT();
        }
    }
}
