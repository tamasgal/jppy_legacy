#include "common.h"
/*
#include <iostream>
#include <map>
#include "JFitReader.h"
#include "JDAQ/JEvt.hh"
#include "JSupport/JMultipleFileScanner.hh"
*/


namespace jppy {

    JSUPPORT::JFileScanner<JFIT::JEvt> fileScanner;
    JFIT::JEvt* event;

    JFitReader::JFitReader() {}

    JFitReader::JFitReader(char* filename) {
        std::cout << "Filename in c++: " << filename << std::endl;
        fileScanner.open(filename);
    }

    void JFitReader::retrieveNextEvent() { event = fileScanner.next(); }
    bool JFitReader::hasNext() { return fileScanner.hasNext(); }

    int JFitReader::getFrameIndex() { return event->getFrameIndex(); }
    double JFitReader::getX() { return event->getX(); }
    double JFitReader::getY() { return event->getY(); }
    double JFitReader::getZ() { return event->getZ(); }
    double JFitReader::getDX() { return event->getDX(); }
    double JFitReader::getDY() { return event->getDY(); }
    double JFitReader::getDZ() { return event->getDZ(); }
    int JFitReader::getNDF() { return event->getNDF(); }
    double JFitReader::getT() { return event->getT(); }
    double JFitReader::getQ() { return event->getQ(); }
    double JFitReader::getE() { return event->getE(); }

    void JFitReader::getFits(
        double* pos_xs,
        double* pos_ys,
        double* pos_zs,
        double* dir_xs,
        double* dir_ys,
        double* dir_zs,
        int* ndfs,
        double* times,
        double* qualities,
        double* energies,
                                  ){
        std::map <int, std::map <int, std::map <int, int> > >  triggered_map;

        std::vector<JFIT::JDAQTriggeredHit> triggeredHits
            = event->getHits<JFIT::JDAQTriggeredHit>();

        int nTriggeredHits = triggeredHits.size();

        for (int i = 0; i < nTriggeredHits; i++) {
            int channel_id = (int)triggeredHits[i].getPMT();
            int dom_id = (int)triggeredHits[i].getModuleID();
            int time = (int)triggeredHits[i].getT();
            triggered_map[channel_id][dom_id][time] = 1;
        }

        std::vector<JFIT::JDAQSnapshotHit> snapshotHits
            = event->getHits<JFIT::JDAQSnapshotHit>();

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
