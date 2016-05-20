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
        JDAQEventReader() {
            file_scanner.open("test.root");
            event_id = 0;
        }
        int get_next_frame_index() {
            event_id++;
            KM3NETDAQ::JDAQEvent* event = file_scanner.next();
            return event->getFrameIndex();
        };
    private:
        int event_id;
        JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
};

extern "C" {
    JDAQEventReader* JDAQEventReader_new(){ return new JDAQEventReader(); }
    int JDAQEventReader_get_next_frame_index(JDAQEventReader* r){
        return r->get_next_frame_index();
    }
}



int main(int argc, char **argv)
{
    typedef KM3NETDAQ::JDAQTriggeredHit JHit_t;

    JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> scan;
    scan.open(argv[1]);

    int event_id = 0;

    while (scan.hasNext())
    {

        KM3NETDAQ::JDAQEvent* event = scan.next();
        {
            std::cout << "Run: " << event->getRunNumber()
                      << "  Event: " << event_id++
                      << "  Frame Index: " << event->getFrameIndex()
                      << std::endl;

            for (KM3NETDAQ::JDAQEvent::const_iterator<JHit_t>
                    hit = event->begin<JHit_t>();
                 hit != event->end<JHit_t>();
                 ++hit)
            {
                struct Hit AHit;
                AHit.tot = (int)hit->getToT();
                AHit.time = (int)hit->getT();
            }
        }
    }
}
