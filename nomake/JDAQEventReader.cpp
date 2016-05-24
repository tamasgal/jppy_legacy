#include "JDAQEventReader.h"
#include <iostream>
#include "JDAQ/JDAQEvent.hh"
#include "JSupport/JMultipleFileScanner.hh"

// Just some non-sense tests

namespace jppp {

    JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
    KM3NETDAQ::JDAQEvent* event;

    JDAQEventReader::JDAQEventReader() {}
    JDAQEventReader::JDAQEventReader(char* filename) {
        std::cout << "Filename in c++: " << filename << std::endl;
        file_scanner.open(filename);
    }
  void JDAQEventReader::retrieve_next_event() { event = file_scanner.next(); }
  int JDAQEventReader::get_frame_index() { return event->getFrameIndex(); };
  bool JDAQEventReader::has_next() { return file_scanner.hasNext(); }

  int JDAQEventReader::get_number_of_snapshot_hits() {
      std::vector<KM3NETDAQ::JDAQSnapshotHit> snapshotHits = event->getHits<KM3NETDAQ::JDAQSnapshotHit>();
      return snapshotHits.size();
  }

  //int* JDAQEventReader::get_tots() {
  void JDAQEventReader::get_tots(int* tots) {

    typedef KM3NETDAQ::JDAQTriggeredHit JHit_t;
    std::vector<KM3NETDAQ::JDAQSnapshotHit> snapshotHits = event->getHits<KM3NETDAQ::JDAQSnapshotHit>();
    std::cout << "Snapshot hits: " << snapshotHits.size() << std::endl;

    int n_snapshot_hits = snapshotHits.size();
//    int tots[n_snapshot_hits];

    std::cout << "Hits (directly from readout): " << std::endl;
    for (int i = 0; i < n_snapshot_hits; i++) {
      std::cout << (int)snapshotHits[i].getToT() << " ";
      tots[i] = (int)snapshotHits[i].getToT();
    }
    std::cout << std::endl;
    std::cout << std::endl;
//    return tots;
  }

  void JDAQEventReader::test_get_tots() {
      // Testing the get_tots() function internally

      std::vector<KM3NETDAQ::JDAQSnapshotHit> snapshotHits = event->getHits<KM3NETDAQ::JDAQSnapshotHit>();
      int n = snapshotHits.size();
      std::cout << "Trying to fetch " << n << " hits" << std::endl;

      int* test_arr = (int*) malloc (n*(sizeof(int)));
      JDAQEventReader::get_tots(test_arr);

      std::cout << "Testing get_tots in c: " << std::endl;
      for(int i = 0; i < n; i++) {
          std::cout << test_arr[i] << " ";
      }
      std::cout << std::endl;

      free(test_arr);
  }

}


int main(int argc, char** argv) {
  std::cout << "jojo" << std::endl;
  return 0;
}

