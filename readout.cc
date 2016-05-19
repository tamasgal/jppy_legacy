#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

#include "JDAQ/JDAQEvent.hh"

#include "JSupport/JMultipleFileScanner.hh"

#include "Jeep/JParser.hh"
#include "Jeep/JMessage.hh"


/**
 * \file
 * Auxiliary program to analyse KM3NETDAQ::JDAQEvent.
 */
int main(int argc, char **argv)
{
  using namespace std;
  using namespace JSUPPORT;
  using namespace KM3NETDAQ;

  JFileScanner<JDAQEvent> scan;
  scan.open(argv[1]);

  while (scan.hasNext()) {

    JDAQEvent* event = scan.next();
    {
      typedef JDAQTriggeredHit JHit_t;

      for (JDAQEvent::const_iterator<JHit_t> hit = event->begin<JHit_t>(); hit != event->end<JHit_t>(); ++hit) {
         std::cout << "Hit  tot:" << (int)hit->getToT() << "ns   time: " << hit->getT() << std::endl;
      }
    }
  }
}
