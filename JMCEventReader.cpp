#include <iostream>
#include <map>
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

    int JDAQEventReader::getFrameIndex() { return event->getFrameIndex(); }
    int JDAQEventReader::getRunNumber() { return event->getRunNumber(); }
    int JDAQEventReader::getDetectorID() { return event->getDetectorID(); }
    int JDAQEventReader::getTriggerCounter() { return event->getCounter(); }
    int JDAQEventReader::getTriggerMask() { return event->getTriggerMask(); }
    int JDAQEventReader::getSize() { return event->getSize(); }
    unsigned int JDAQEventReader::getOverlays() { return event->getOverlays(); }
    int JDAQEventReader::getUTCSeconds() {
        return event->getTimesliceStart().getUTCseconds();
    }
    int JDAQEventReader::getUTCNanoseconds() {
        return event->getTimesliceStart().getUTC16nanosecondcycles() * 16;
    }

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
                                  int* tots,
                                  int* triggereds)
    {
        std::map <int, std::map <int, std::map <int, int> > >  triggered_map;

        std::vector<KM3NETDAQ::JDAQTriggeredHit> triggeredHits
            = event->getHits<KM3NETDAQ::JDAQTriggeredHit>();

        int nTriggeredHits = triggeredHits.size();

        for (int i = 0; i < nTriggeredHits; i++) {
            int channel_id = (int)triggeredHits[i].getPMT();
            int dom_id = (int)triggeredHits[i].getModuleID();
            int time = (int)triggeredHits[i].getT();
            triggered_map[channel_id][dom_id][time] = 1;
        }

        std::vector<KM3NETDAQ::JDAQSnapshotHit> snapshotHits
            = event->getHits<KM3NETDAQ::JDAQSnapshotHit>();

        int nSnapshotHits = snapshotHits.size();

        for (int i = 0; i < nSnapshotHits; i++) {
            int channel_id = (int)snapshotHits[i].getPMT();
            int dom_id = (int)snapshotHits[i].getModuleID();
            int time = (int)snapshotHits[i].getT();
            int tot = (int)snapshotHits[i].getToT();
            channel_ids[i] = channel_id;
            dom_ids[i] = dom_id;
            times[i] = time;
            tots[i] = tot;
            triggereds[i] = triggered_map[channel_id][dom_id][time];
        }
    }
}
