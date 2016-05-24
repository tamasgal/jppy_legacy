#ifndef JDAQEVENTREADER_H
#define JDAQEVENTREADER_H
//#include "Python.h"
//#include <vector>
//#include "JDAQ/JDAQEvent.hh"
//#include "JSupport/JMultipleFileScanner.hh"

//using namespace KM3NETDAQ;

namespace jppp {
    class JDAQEventReader {
        public:
            JDAQEventReader();
            JDAQEventReader(char* filename);
            void retrieve_next_event();
            int get_frame_index();
            int get_number_of_snapshot_hits();
            void get_tots(int *out_array);
//            int* get_tots();
            bool has_next();
//        private:
 //           JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
  //          KM3NETDAQ::JDAQEvent* event;
    };
}

#endif /* JDAQEVENTREADER_H */
