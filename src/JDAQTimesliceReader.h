#ifndef JDAQTIMESLICEREADER_H
#define JDAQTIMESLICEREADER_H

namespace jppy {
    class JDAQTimesliceReader {
    public:
        JDAQTimesliceReader();
        JDAQTimesliceReader(char* filename);
        void retrieveNextTimeslice();
        void retrieveNextSuperframe();
        bool hasNext();
        bool hasNextSuperframe();
        int getNumberOfHits();
        void getHits();
    };
}

#endif /* JDAQTIMESLICEREADER_H */