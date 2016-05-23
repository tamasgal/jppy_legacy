#include "jppp.h"

// Just some non-sense tests

namespace jppp {

  JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
  KM3NETDAQ::JDAQEvent* event;

JDAQEventReader::JDAQEventReader(char* filename) {
    std::cout << "Filename in c++: " << filename << std::endl;
    file_scanner.open(filename);
  }
  void JDAQEventReader::retrieve_next_event() { event = file_scanner.next(); }
  int JDAQEventReader::get_frame_index() { return event->getFrameIndex(); };
  bool JDAQEventReader::has_next() { return file_scanner.hasNext(); }

  int* JDAQEventReader::get_tots() {

    typedef KM3NETDAQ::JDAQTriggeredHit JHit_t;
    std::vector<JDAQSnapshotHit> snapshotHits = event->getHits<JDAQSnapshotHit>();
    std::cout << "Snapshot hits: " << snapshotHits.size() << std::endl;

    int n_snapshot_hits = snapshotHits.size();
    int tots[n_snapshot_hits];

    std::cout << "Hits (from jppp.cc): ";
    for (int i = 0; i < n_snapshot_hits; i++) {
      std::cout << (int)snapshotHits[i].getToT() << " ";
      tots[i] = (int)snapshotHits[i].getToT();
    }
    std::cout << std::endl;

    return tots;
  }

}


int main(int argc, char** argv) {
  std::cout << "jojo" << std::endl;
  return 0;
}

