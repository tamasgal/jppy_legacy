from daqeventreader import PyJDAQEventReader

reader = PyJDAQEventReader('../test.root')

for i in range(4):
    print("Event #{0}".format(i))
    reader.retrieve_next_event()
    print("  Frame Index: {0}".format(reader.get_frame_index()))
    print("  Amount of Snapshot Hits: {0}".format(reader.get_number_of_snapshot_hits()))
    print("  Snapshot HIts: {0}".format(reader.get_tots()))

