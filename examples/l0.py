#!/usr/bin/env python
import jppy
import numpy as np

r = jppy.PyJDAQTimesliceReader("/home/tgal/data/L0/KM3NeT_00000013_00000501.root")
i = 0
while r.has_next:
    r.retrieve_next_timeslice()
    j = 0
    while r.has_next_superframe:
        r.retrieve_next_superframe()
        n = r.number_of_hits
        channel_ids = np.zeros(n, dtype='i')
        dom_ids = np.zeros(n, dtype='i')
        times = np.zeros(n, dtype='i')
        tots = np.zeros(n, dtype='i')
        r.get_hits(channel_ids, dom_ids, times, tots)
        print(channel_ids)
        print(len(channel_ids))
        print(dom_ids)
        print(len(dom_ids))
        print(times)
        print(len(times))
        print(tots)
        print(len(tots))
        print("number of hits: {0}".format(n))
        raw_input()
        j += 1
    i += 1
print("{0} timeslices processed.".format(i))
