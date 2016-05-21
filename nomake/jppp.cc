#include "Python.h"
#include <vector>
// #include "numpy/arrayobject.h"
#include "JDAQ/JDAQEvent.hh"
//#include "JDAQ/JDAQKeyHit.hh"
#include "JSupport/JMultipleFileScanner.hh"

using namespace KM3NETDAQ;

/// A dummy struct for testing
struct Hit {
    int tot, time;
};


// Just some non-sense tests

class JDAQEventReader{
    public:
        JDAQEventReader(char* filename) {
            std::cout << "Filename in c++: " << filename << std::endl;
            file_scanner.open(filename);
        }
        void retrieve_next_event() {
            event = file_scanner.next();
        }
        int get_frame_index() {
            return event->getFrameIndex();
        };
        bool has_next() {
            return file_scanner.hasNext();
        }
        PyObject* get_hits() {
            PyObject* hits = PyList_New(0);

            typedef KM3NETDAQ::JDAQTriggeredHit JHit_t;

//            std::vector<JDAQSnapshotHit> snapshotHits=event.getHits<JDAQSnapshotHit>();

            for (KM3NETDAQ::JDAQEvent::const_iterator<JHit_t>
                    hit = event->begin<JHit_t>();
                 hit != event->end<JHit_t>();
                 ++hit)
            {
                int tot = (int)hit->getToT();
                PyList_Append(hits, PyInt_FromLong(tot));
            }


            return hits;
        }
    private:
        int event_id;
        JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
        KM3NETDAQ::JDAQEvent* event;
};

extern "C" {
    JDAQEventReader* JDAQEventReader_new(char* filename){
        return new JDAQEventReader(filename);
    }

    int JDAQEventReader_get_frame_index(JDAQEventReader* r){
        return r->get_frame_index();
    }

    void JDAQEventReader_retrieve_next_event(JDAQEventReader* r){
        r->retrieve_next_event();
    }

    PyObject* JDAQEventReader_get_hits(JDAQEventReader* r) {
        return r->get_hits();
    }

    bool JDAQEventReader_has_next(JDAQEventReader* r){
        return r->has_next();
    }
}



int main(int argc, char **argv)
{
    std::cout << "jojo" << std::endl;
    return 0;
}
