// #include <vector>
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
            event_id = 0;
        }
        int get_next_frame_index() {
            event_id++;
            KM3NETDAQ::JDAQEvent* event = file_scanner.next();
            return event->getFrameIndex();
        };
        bool has_next() {
            return file_scanner.hasNext();
        }
        void hits_dummy() {
            /*
            for (KM3NETDAQ::JDAQEvent::const_iterator<JHit_t>
                    hit = event->begin<JHit_t>();
                 hit != event->end<JHit_t>();
                 ++hit)
            {
                struct Hit AHit;
                AHit.tot = (int)hit->getToT();
                AHit.time = (int)hit->getT();
            }
            */
        }
    private:
        int event_id;
        JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
};

extern "C" {
    JDAQEventReader* JDAQEventReader_new(char* filename){ return new JDAQEventReader(filename); }
    int JDAQEventReader_get_next_frame_index(JDAQEventReader* r){
        return r->get_next_frame_index();
    }
    bool JDAQEventReader_has_next(JDAQEventReader* r){
        return r->has_next();
    }
}



int main(int argc, char **argv)
{
    return 0;
}
