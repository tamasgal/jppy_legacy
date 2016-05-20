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
        int get_next_tot() { return 1; };
};

extern "C" {
    JDAQEventReader* JDAQEventReader_new(){ return new JDAQEventReader(); }
    int JDAQEventReader_get_next_tot(JDAQEventReader* r){ r->get_next_tot(); }
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
