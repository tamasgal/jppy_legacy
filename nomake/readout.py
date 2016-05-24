from daqeventreader import PyJDAQEventReader
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

    tots = np.zeros(reader.get_number_of_snapshot_hits(), dtype='i')
    reader.get_tots(tots)
    print("  Snapshot Hits (actual python interface): {0}".format(tots))
    reader.test_get_tots()

