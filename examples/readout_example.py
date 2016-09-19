from jppy import PyJDAQEventReader
import sys
import numpy as np


try:
    reader = PyJDAQEventReader(sys.argv[1])
except IndexError:
    raise SystemExit("Usage: {0} FILENAME".format(__file__))

for i in range(4):
    print(42*"=")
    print("Event #{0}".format(i))
    reader.retrieve_next_event()
    print("  Frame Index: {0}".format(reader.get_frame_index()))
    print("  Amount of Snapshot Hits: {0}".format(reader.get_number_of_snapshot_hits()))

    n = reader.get_number_of_snapshot_hits()
    channel_ids = np.zeros(n, dtype='i')
    dom_ids = np.zeros(n, dtype='i')
    times = np.zeros(n, dtype='i')
    tots = np.zeros(n, dtype='i')
    triggereds = np.zeros(n, dtype='i')
    reader.get_hits(channel_ids, dom_ids, times, tots, triggereds)
    print("  Snapshot Hits: \n"
          "    Channel IDs: {3}\n"
          "    DOM IDs:     {2}\n"
          "    Times:       {1}\n"
          "    ToTs:        {0}\n"
          "    Triggereds:  {4}"
          .format(tots, times, dom_ids, channel_ids, triggereds))

