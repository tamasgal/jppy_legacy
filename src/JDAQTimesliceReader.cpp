#include <string>
#include <vector>
#include "common.h"
#include "JLang/JObjectReader.hh"
#include "JDAQ/JDAQTimeslice.hh"
#include "JDAQTimesliceReader.h"

using namespace KM3NETDAQ ; // for JDAQTimeSlice
using namespace JSUPPORT;   // for JFileScanner
using namespace JLANG;  

namespace jppy {

    JSUPPORT::JFileScanner<KM3NETDAQ::JDAQTimeslice> fileScanner;
    KM3NETDAQ::JDAQTimeslice* timeslice;
    JDAQTimeslice::const_iterator superframe_it;

    JDAQTimesliceReader::JDAQTimesliceReader() {}

    JDAQTimesliceReader::JDAQTimesliceReader(char* filename) {
        std::cout << "Filename in c++: " << filename << std::endl;
        fileScanner.open(filename);
    }

    void JDAQTimesliceReader::retrieveNextTimeslice() {
        timeslice = fileScanner.next();
        superframe_it = timeslice->begin();
    }
    void JDAQTimesliceReader::retrieveNextSuperframe() {
        ++superframe_it;
    }
    bool JDAQTimesliceReader::hasNext() { return fileScanner.hasNext(); }
    bool JDAQTimesliceReader::hasNextSuperframe() {
        return superframe_it != timeslice->end();
    }
    int JDAQTimesliceReader::getNumberOfHits() {
        return superframe_it->size();
    }

    void JDAQTimesliceReader::getHits(int* channel_ids,
                                      int* dom_ids,
                                      int* times,
                                      int* tots) {
        int i = 0;
        for( JDAQSuperFrame::const_iterator hit=superframe_it->begin();
             hit!=superframe_it->end();
             ++hit ) {
            channel_ids[i] = int(hit->getPMT());
            dom_ids[i] = superframe_it->getModuleID();
            times[i] = hit->getT();
            tots[i] = int(hit->getToT());
            i++;
        }
    }
}
