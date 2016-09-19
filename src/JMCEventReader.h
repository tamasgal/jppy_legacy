#ifndef JMCEVENTREADER_H
#define JMCEVENTREADER_H

namespace jppy {
    class JMCEventReader {
    public:
        JMCEventReader();
        JMCEventReader(char* filename);
        void retrieveNextEvent();
        int getNumberOfMCHits();
        int getNumberOfMCTracks();
        void getMCHits(int* types, float* lengths, int* pmt_ids,
                       float* pos_xs, float* pos_ys, float* pos_zs,
                       float* dir_xs, float* dir_ys, float* dir_zs,
                       float* energies, float* times);
        void getMCTracks(int* types, int* origins, float* pure_dts,
                         float* pure_npes, int* idents, int* pmt_ids,
                         float* dts, float* npes);
        void getWeights(float* w2s, float*w3s);
    };
}

#endif /* JMCEVENTREADER_H */
