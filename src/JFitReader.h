#ifndef JFITREADER_H
#define JFITREADER_H

namespace jppy {
    class JFitReader {
    public:
        JFitReader();
        JFitReader(char* filename);
        void retrieveNextEvent();
        int getNFits();
        void getFits(
            double* pos_xs,
            double* pos_ys,
            double* pos_zs,
            double* dir_xs,
            double* dir_ys,
            double* dir_zs,
            int* ndfs,
            double* times,
            double* qualities,
            double* energies);
        bool hasNext();
    };
}

#endif /* JFITREADER_H */
