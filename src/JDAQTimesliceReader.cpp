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
    int timeslice_idx = 0;
    int superframe_idx = 0;

    JDAQTimesliceReader::JDAQTimesliceReader() {}

    JDAQTimesliceReader::JDAQTimesliceReader(char* filename) {
        std::cout << "Filename in c++: " << filename << std::endl;
        fileScanner.open(filename);
    }

    void JDAQTimesliceReader::retrieveNextTimeslice() {
        timeslice = fileScanner.next();
        superframe_it = timeslice->begin();
        timeslice_idx += 1;
        superframe_idx = 0;
        //std::cout << "Timeslice idx: " << superframe_idx << std::endl;
    }
    void JDAQTimesliceReader::retrieveNextSuperframe() {
        superframe_it++;
        //std::cout << "Superframe idx: " << superframe_idx << std::endl;
        superframe_idx += 1;
    }
    bool JDAQTimesliceReader::hasNext() { return fileScanner.hasNext(); }
    bool JDAQTimesliceReader::hasNextSuperframe() {
        return superframe_it != timeslice->end();
    }
    int JDAQTimesliceReader::getNumberOfHits() {
        //std::cout << superframe_it->getModuleID() << std::endl;
        return superframe_it->size();
    }

    int JDAQSummarysliceReader::getModuleID() {
        return superframe_it->getModuleID();
    }

    int JDAQSummarysliceReader::getUDPNumberOfReceivedPackets() {
        return superframe_it->getUDPNumberOfReceivedPackets();
    }

    int JDAQSummarysliceReader::getUDPMaximalSequenceNumber() {
        return superframe_it->getUDPMaximalSequenceNumber();
    }

    bool JDAQSummarysliceReader::hasUDPTrailer() {
        return superframe_it->hasUDPTrailer();
    }

    bool JDAQSummarysliceReader::testWhiteRabbitStatus() {
        return superframe_it->testWhiteRabbitStatus();
    }

    bool JDAQSummarysliceReader::testHighRateVeto() {
        return superframe_it->testHighRateVeto();
    }

    bool JDAQSummarysliceReader::testFIFOStatus() {
        return superframe_it->testFIFOStatus();
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
            //std::cout << superframe_it->getModuleID() << std::endl;
            times[i] = hit->getT();
            tots[i] = int(hit->getToT());
            i++;
        }
    }
}
