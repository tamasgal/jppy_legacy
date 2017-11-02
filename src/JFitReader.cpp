#include "common.h"

namespace jppy {

JSUPPORT::JFileScanner<JFIT::JEvt> fileScanner;
JFIT::JEvt* event;

JFitReader::JFitReader() {}

JFitReader::JFitReader(char* filename) {
    std::cout << "Filename in c++: " << filename << std::endl;
    fileScanner.open(filename);
}

void JFitReader::retrieveNextEvent() { event = fileScanner.next(); }
bool JFitReader::hasNext() { return fileScanner.hasNext(); }

int JFitReader::getNFits() { return event->size(); }

void JFitReader::getFits(double* pos_xs, double* pos_ys, double* pos_zs,
  double* dir_xs, double* dir_ys, double* dir_zs,
  int* ndfs, double* times, double* qualities, double* energies
) {
    // int nFits = event->size();
    // for (int i = 0; i < nFits; i++) {
    JFIT::JEvt::iterator __end = event->end();
    JFIT::JEvt::iterator __begin = event->begin();
    for (JFIT::JEvt::iterator track = event->begin(); track != __end; ++track) {
        int i = std::distance(__begin, track);
        double pos_x = static_cast<double>(track->getX());
        double pos_y = static_cast<double>(track->getY());
        double pos_z = static_cast<double>(track->getZ());
        double dir_x = static_cast<double>(track->getDX());
        double dir_y = static_cast<double>(track->getDY());
        double dir_z = static_cast<double>(track->getDZ());
        int ndf = static_cast<int>(track->getNDF());
        double time = static_cast<double>(track->getT());
        double quality = static_cast<double>(track->getQ());
        double energy = static_cast<double>(track->getE());
        pos_xs[i] = pos_x;
        pos_ys[i] = pos_y;
        pos_zs[i] = pos_z;
        dir_xs[i] = dir_x;
        dir_ys[i] = dir_y;
        dir_zs[i] = dir_z;
        ndfs[i] = ndf;
        times[i] = time;
        qualities[i] = quality;
        energies[i] = energy;
    }
}
}   // namespace jppy
