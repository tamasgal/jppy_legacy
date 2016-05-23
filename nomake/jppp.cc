#include "Python.h"
#include <vector>
// #include "numpy/arrayobject.h"
#include "JDAQ/JDAQEvent.hh"
//#include "JDAQ/JDAQKeyHit.hh"
#include "JSupport/JMultipleFileScanner.hh"

using namespace KM3NETDAQ;

// Just some non-sense tests

class JDAQEventReader {
 public:
  JDAQEventReader(char* filename) {
    std::cout << "Filename in c++: " << filename << std::endl;
    file_scanner.open(filename);
  }
  void retrieve_next_event() { event = file_scanner.next(); }
  int get_frame_index() { return event->getFrameIndex(); };
  bool has_next() { return file_scanner.hasNext(); }

  int* get_tots() {

    typedef KM3NETDAQ::JDAQTriggeredHit JHit_t;
    std::vector<JDAQSnapshotHit> snapshotHits = event->getHits<JDAQSnapshotHit>();
    std::cout << "Snapshot hits: " << snapshotHits.size() << std::endl;

    int n_snapshot_hits = snapshotHits.size();
    int tots[n_snapshot_hits];

    for (int i = 0; i < n_snapshot_hits; i++) {
      tots[i] = (int)snapshotHits[i].getToT();
    }

    return tots;
  }

 private:
  JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
  KM3NETDAQ::JDAQEvent* event;
};

extern "C" {
JDAQEventReader* JDAQEventReader_new(char* filename) {
  return new JDAQEventReader(filename);
}

int JDAQEventReader_get_frame_index(JDAQEventReader* r) {
  return r->get_frame_index();
}

void JDAQEventReader_retrieve_next_event(JDAQEventReader* r) {
  r->retrieve_next_event();
}

int* JDAQEventReader_get_tots(JDAQEventReader* r) { return r->get_tots(); }

bool JDAQEventReader_has_next(JDAQEventReader* r) { return r->has_next(); }
}

int main(int argc, char** argv) {
  std::cout << "jojo" << std::endl;
  return 0;
}
