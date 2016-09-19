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

    JDAQTimesliceReader::JDAQTimesliceReader() {}

    JDAQTimesliceReader::JDAQTimesliceReader(char* filename) {
        std::cout << "Filename in c++: " << filename << std::endl;
        fileScanner.open(filename);
    }

    void JDAQTimesliceReader::retrieveNextTimeslice() { timeslice = fileScanner.next(); }
    bool JDAQTimesliceReader::hasNext() { return fileScanner.hasNext(); }

    void JDAQTimesliceReader::getHits() {
        for(JDAQTimeslice::const_iterator superframe = timeslice->begin();
            superframe != timeslice->end();
            superframe++) {
            for(JDAQSuperFrame::const_iterator hit=superframe->begin();
                hit!=superframe->end();
                ++hit ) {
                //std::cout << "Hit..." << std::endl;
            }
        }
    }
}
