#ifndef JDAQTIMESLICEREADER_H
#define JDAQTIMESLICEREADER_H

namespace jppy {
    class JDAQTimesliceReader {
    public:
        JDAQTimesliceReader();
        JDAQTimesliceReader(char* filename);
        void retrieveNextTimeslice();
        bool hasNext();
        void getHits();
    };
}

#endif /* JDAQTIMESLICEREADER_H */
