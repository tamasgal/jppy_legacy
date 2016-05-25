#ifndef JDAQEVENTREADER_H
#define JDAQEVENTREADER_H

namespace jppp {
    class JDAQEventReader {
        public:
            JDAQEventReader();
            JDAQEventReader(char* filename);
            void retrieve_next_event();
            int get_frame_index();
            int get_number_of_snapshot_hits();
            void get_hits(int* channel_ids, int* dom_ids, int* times, int* tots);
            void get_tots(int* tots);
            void test_get_tots();
            bool has_next();
//      private:
//          JSUPPORT::JFileScanner<KM3NETDAQ::JDAQEvent> file_scanner;
//          KM3NETDAQ::JDAQEvent* event;
    };
}

#endif /* JDAQEVENTREADER_H */
