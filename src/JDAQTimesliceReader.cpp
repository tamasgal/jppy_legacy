#include <string>
#include <vector>
#include "common.h"
#include "JLang/JObjectReader.hh"
#include "JLang/JSinglePointer.hh"
#include "JDAQ/JDAQTimeslice.hh"
#include "JDAQ/JDAQEvaluator.hh"
#include "JSupport/JTreeScanner.hh"
#include "JDAQTimesliceReader.h"

using namespace KM3NETDAQ ;     // for JDAQTimeSlice
using namespace JSUPPORT;       // for JFileScanner and JTreeScanner
using namespace JLANG;

namespace jppy {

    JSUPPORT::JFileScanner<KM3NETDAQ::JDAQTimeslice> fileScanner;
    typedef JTreeScanner<JDAQTimeslice, JDAQEvaluator>  JTreeScanner_t;
    JLANG::JSinglePointer< JTreeScanner_t > treeScanner;

    std::string _filename;
    KM3NETDAQ::JDAQTimeslice* timeslice;
    JDAQTimeslice::const_iterator superframe_it;
    int timeslice_idx = 0;
    int superframe_idx = 0;
    std::map<int, int> frame_index_map;

    JDAQTimesliceReader::JDAQTimesliceReader() {}

    JDAQTimesliceReader::JDAQTimesliceReader(char* filename) {
        _filename = std::string(filename);
        std::cout << "Filename in c++: " << filename << std::endl;
        fileScanner.open(filename);
    }

    void JDAQTimesliceReader::initTreeScanner() {
        std::cout << "Initialising JTreeScanner, this may take a few seconds." << std::endl;
        treeScanner.reset(new JTreeScanner_t(_filename));
        int n = treeScanner->GetEntries();
        for(int i = 0; i < n; i++) {
            JDAQTimeslice* timeslice = treeScanner->getEntry(i);
            frame_index_map[timeslice->getFrameIndex()] = i;
            // std::cout << i << " : " << timeslice->getFrameIndex() << std::endl;
        }
        std::cout << n << " timeslices indexed." << std::endl;
    }

    void JDAQTimesliceReader::retrieveTimeslice(int index) {
        timeslice = treeScanner->getEntry(index);
        superframe_it = timeslice->begin();
    }

    void JDAQTimesliceReader::retrieveTimesliceAtFrameIndex(int frame_index) {
        // std::cout << "Retrieving timeslice with frame index " << frame_index;
        int i = frame_index_map[frame_index];
        // std::cout << " (at index " << i << ")" << std::endl;
        timeslice = treeScanner->getEntry(i);
        superframe_it = timeslice->begin();
    }

    void JDAQTimesliceReader::retrieveNextTimeslice() {
        timeslice = fileScanner.next();
        superframe_it = timeslice->begin();
        timeslice_idx += 1;
        superframe_idx = 0;
        // std::cout << "Timeslice idx: " << superframe_idx << std::endl;
    }
    void JDAQTimesliceReader::retrieveNextSuperframe() {
        superframe_it++;
        // std::cout << "Superframe idx: " << superframe_idx << std::endl;
        superframe_idx += 1;
    }
    bool JDAQTimesliceReader::hasNext() { return fileScanner.hasNext(); }
    bool JDAQTimesliceReader::hasNextSuperframe() {
        return superframe_it != timeslice->end();
    }
    int JDAQTimesliceReader::getNumberOfFrames() {
        return timeslice->size();
    }
    int JDAQTimesliceReader::getNumberOfHits() {
        // std::cout << superframe_it->getModuleID() << std::endl;
        return superframe_it->size();
    }

    int JDAQTimesliceReader::getFrameIndex() {
        return superframe_it->getFrameIndex();
    }

    int JDAQTimesliceReader::getModuleID() {
        return superframe_it->getModuleID();
    }

    int JDAQTimesliceReader::getUTCSeconds() {
        return superframe_it->getTimesliceStart().getUTCseconds();
    }

    int JDAQTimesliceReader::getUTCNanoseconds() {
        return superframe_it->getTimesliceStart().getUTC16nanosecondcycles() * 16;
    }

    int JDAQTimesliceReader::getUDPNumberOfReceivedPackets() {
        return superframe_it->getUDPNumberOfReceivedPackets();
    }

    int JDAQTimesliceReader::getUDPMaximalSequenceNumber() {
        return superframe_it->getUDPMaximalSequenceNumber();
    }

    bool JDAQTimesliceReader::hasUDPTrailer() {
        return superframe_it->hasUDPTrailer();
    }

    bool JDAQTimesliceReader::testWhiteRabbitStatus() {
        return superframe_it->testWhiteRabbitStatus();
    }

    bool JDAQTimesliceReader::testHighRateVeto() {
        return superframe_it->testHighRateVeto();
    }

    bool JDAQTimesliceReader::testFIFOStatus() {
        return superframe_it->testFIFOStatus();
    }

    void JDAQTimesliceReader::getHits(int* channel_ids,
                                      int* dom_ids,
                                      int* times,
                                      int* tots,
                                      int start_index) {
        int i = start_index;
        for (JDAQSuperFrame::const_iterator hit = superframe_it->begin();
             hit != superframe_it->end(); ++hit ) {
            channel_ids[i] = static_cast<int>(hit->getPMT());
            dom_ids[i] = superframe_it->getModuleID();
            // std::cout << superframe_it->getModuleID() << std::endl;
            times[i] = hit->getT();
            tots[i] = static_cast<int>(hit->getToT());
            i++;
        }
    }
}
