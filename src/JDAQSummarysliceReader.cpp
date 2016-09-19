#include "common.h"


namespace jppy {
//    JSUPPORT::JFileScanner<KM3NETDAQ::JDAQSummaryslice> fileScanner;
    JSUPPORT::JMultipleFileScanner<KM3NETDAQ::JDAQSummaryslice> inputFiles;
    JSUPPORT::JTreeScanner<KM3NETDAQ::JDAQSummaryslice> treeScanner(inputFiles);
    KM3NETDAQ::JDAQSummaryslice summary;
    KM3NETDAQ::JDAQChronometer chronometer;

    JDAQSummarysliceReader::JDAQSummarysliceReader() {}

    JDAQSummarysliceReader::JDAQSummarysliceReader(char* filename) {
        std::cout << "Filename in c++: " << filename << std::endl;
        inputFiles.addFilename(filename);
        inputFiles.hasNext();  // this is needed! why??
        //std::cout << inputFiles.hasNext() << std::endl;
    }

    void JDAQSummarysliceReader::retrieveNextSummaryslice() {
        //summary = *treeScanner.next();
        if(!treeScanner.hasNext()) {
            std::cout << "No summary slices!" << std::endl;
            return;
        }

        std::cout << "New summary" << std::endl;
        summary = *treeScanner.next();
//        std::cout << summary->getUTCseconds() << std::endl;
        std::cout << dynamic_cast<const KM3NETDAQ::JDAQChronometer&> (summary) <<  std::endl;
        chronometer = dynamic_cast<const KM3NETDAQ::JDAQChronometer&> (summary);
    }

    int JDAQSummarysliceReader::getUDPNumberOfReceivedPackets() {
        std::cout << chronometer.getRunNumber() << std::endl;
        std::cout << chronometer.getDetectorID() << std::endl;
        std::cout << chronometer.getFrameIndex() << std::endl;
        std::cout << chronometer.getTimesliceStart() << std::endl;
        std::cout << "Number of received packets:" << std::endl;
        for (KM3NETDAQ::JDAQSummaryslice::const_iterator frame = summary.begin();
             frame != summary.end();
             ++frame) {
            std::cout << frame->getUDPNumberOfReceivedPackets() << " / "
                      << frame->getUDPMaximalSequenceNumber() << " from "
                      << frame->getModuleID()
                      << std::endl;
        }


        return 23;
        //return summary.getUDPNumberOfReceivedPackets();
    }

    bool JDAQSummarysliceReader::hasNext() { return treeScanner.hasNext(); }
}
