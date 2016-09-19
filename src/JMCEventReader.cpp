#include <iostream>
#include <map>

#include "JMC/JMCEvt.hh"
#include "JMC/JMCHead.hh"
#include "JMC/JMCToolkit.hh"
#include "JSupport/JMultipleFileScanner.hh"


namespace jppy {

    JSUPPORT::JFileScanner<JMC::JMCEvt> fileScanner;
    JMC::JMCEvt* event;

    JMCReader::JMCReader() {}

    JMCReader::JMCEventReader(char* filename) {
        std::cout << "Filename in c++: " << filename << std::endl;
        fileScanner.open(filename);
    }

    void JMCReader::retrieveNextEvent() { event = fileScanner.next(); }

    bool JMCEventReader::hasNext() { return fileScanner.hasNext(); }

    JMCEventReader();
    JMCEventReader(char* filename);
    void retrieveNextEvent();
    int getNumberOfMCHits();
    int getNumberOfMCTracks();
    void getMCHits(int* types, float* lengths, int* pmt_ids,
                   float* pos_xs, float* pos_ys, float* pos_zs,
                   float* dir_xs, float* dir_ys, float* dir_zs,
                   float* energies, float* times);
    void getMCTracks(int* types, int* origins, float* pure_dts,
                     float* pure_npes, int* idents, int* pmt_ids,
                     float* dts, float* npes);
    void getWeights(float* w2s, float*w3s);

    void JMCEventReader::getHits(int* channel_ids,
                                  int* dom_ids,
                                  int* times,
                                  int* tots,
                                  int* triggereds)
    {
        std::map <int, std::map <int, std::map <int, int> > >  triggered_map;

        std::vector<JMC::JDAQTriggeredHit> triggeredHits
            = event->getHits<JMC::JDAQTriggeredHit>();

        int nTriggeredHits = triggeredHits.size();

        for (int i = 0; i < nTriggeredHits; i++) {
            int channel_id = (int)triggeredHits[i].getPMT();
            int dom_id = (int)triggeredHits[i].getModuleID();
            int time = (int)triggeredHits[i].getT();
            triggered_map[channel_id][dom_id][time] = 1;
        }

        std::vector<JMC::JDAQSnapshotHit> snapshotHits
            = event->getHits<JMC::JDAQSnapshotHit>();

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
