// #include <vector>
//#include "Python.h"
#include "JDAQ/JDAQEvent.hh"
#include "JSupport/JMultipleFileScanner.hh"

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
        int* get_hits() {
            static int hits[5];
            int i = 0;

            typedef KM3NETDAQ::JDAQTriggeredHit JHit_t;

            for (KM3NETDAQ::JDAQEvent::const_iterator<JHit_t>
                    hit = event->begin<JHit_t>();
                 hit != event->end<JHit_t>();
                 ++hit)
            {
                if(i < 5) {
                    hits[i++] = (int)hit->getToT();
                }
//                struct Hit AHit;
//                AHit.tot = (int)hit->getToT();
//                AHit.time = (int)hit->getT();
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

    int* JDAQEventReader_get_hits(JDAQEventReader* r) {
        return r->get_hits();
    }

    bool JDAQEventReader_has_next(JDAQEventReader* r){
        return r->has_next();
    }
}



int main(int argc, char **argv)
{
    return 0;
}
