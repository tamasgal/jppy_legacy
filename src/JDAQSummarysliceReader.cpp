#include "common.h"

namespace jppy {
    JSUPPORT::JFileScanner<KM3NETDAQ::JDAQSummaryslice> fileScanner;
    KM3NETDAQ::JDAQSummaryslice* summary;
    KM3NETDAQ::JDAQSummaryslice::const_iterator frame_it;
    KM3NETDAQ::JDAQChronometer chronometer;
    int summary_idx = 0;
    int frame_idx = 0;

    JDAQSummarysliceReader::JDAQSummarysliceReader() {}

    JDAQSummarysliceReader::JDAQSummarysliceReader(char* filename) {
        // std::cout << "Filename in c++: " << filename << std::endl;
        fileScanner.open(filename);
    }

    bool JDAQSummarysliceReader::hasNext() { return fileScanner.hasNext(); }

    void JDAQSummarysliceReader::retrieveNextSummaryslice() {
        if (!fileScanner.hasNext()) {
            // std::cout << "No summary slices!" << std::endl;
            return;
        }

        // std::cout << "New summary" << std::endl;
        summary = fileScanner->next();
        chronometer = dynamic_cast<const KM3NETDAQ::JDAQChronometer&> (*summary);
        frame_it = summary->begin();
        summary_idx++;
        frame_idx = 0;
    }

    int JDAQSummarysliceReader::getNumberOfFrames() {
        return summary->size();
    }

    int JDAQSummarysliceReader::getRunNumber() {
        return chronometer.getRunNumber();
    }

    int JDAQSummarysliceReader::getDetectorID() {
        return chronometer.getDetectorID();
    }

    int JDAQSummarysliceReader::getFrameIndex() {
        return chronometer.getFrameIndex();
    }

    int JDAQSummarysliceReader::getUTCSeconds() {
        return chronometer.getTimesliceStart().getUTCseconds();
    }

    int JDAQSummarysliceReader::getUTCNanoseconds() {
        return chronometer.getTimesliceStart().getUTC16nanosecondcycles() * 16;
    }

    /* Frame */

    bool JDAQSummarysliceReader::hasNextFrame() {
        return frame_it != summary->end();
    }

    void JDAQSummarysliceReader::retrieveNextFrame() {
        frame_it++;
        frame_idx++;
    }

    int JDAQSummarysliceReader::getModuleID() {
        return frame_it->getModuleID();
    }

    int JDAQSummarysliceReader::getUDPNumberOfReceivedPackets() {
        return frame_it->getUDPNumberOfReceivedPackets();
    }

    int JDAQSummarysliceReader::getUDPMaximalSequenceNumber() {
        return frame_it->getUDPMaximalSequenceNumber();
    }

    bool JDAQSummarysliceReader::hasUDPTrailer() {
        return frame_it->hasUDPTrailer();
    }

    bool JDAQSummarysliceReader::testWhiteRabbitStatus() {
        return frame_it->testWhiteRabbitStatus();
    }

    bool JDAQSummarysliceReader::testHighRateVeto() {
        return frame_it->testHighRateVeto();
    }

    bool JDAQSummarysliceReader::testFIFOStatus() {
        return frame_it->testFIFOStatus();
    }

    void JDAQSummarysliceReader::getRates(double* rates) {
        for (int channel_id = 0; channel_id != 31; ++channel_id) {
            // std::cout << "Channel " << channel_id << " rate: ";
            // std::cout << frame_it->getRate(channel_id) << std::endl;
            rates[channel_id] = frame_it->getRate(channel_id);
        }
    }
    void JDAQSummarysliceReader::getHRVs(int* hrvs) {
        /*
        for (KM3NETDAQ::JDAQSummaryslice::const_iterator frame = summary.begin();
             frame != summary.end();
             ++frame) {
            std::cout << "White rabbit status: " << frame->testWhiteRabbitStatus() << std::endl;
                      << frame->getModuleID()
                      << std::endl; */
        for (int channel_id = 0; channel_id != 31; ++channel_id) {
            hrvs[channel_id] = int(frame_it->testHighRateVeto(channel_id));
        }
    }

    void JDAQSummarysliceReader::getFIFOs(int* fifos) {
        /*
        for (KM3NETDAQ::JDAQSummaryslice::const_iterator frame = summary.begin();
             frame != summary.end();
             ++frame) {
            std::cout << "White rabbit status: " << frame->testWhiteRabbitStatus() << std::endl;
                      << frame->getModuleID()
                      << std::endl; */
        for (int channel_id = 0; channel_id != 31; ++channel_id) {
            fifos[channel_id] = int(frame_it->getFIFOStatus(channel_id));
        }
    }
}  // namespace jppy
