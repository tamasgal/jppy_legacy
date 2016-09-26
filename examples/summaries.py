#!/usr/bin/env python

from jppy.daqsummaryslicereader import PyJDAQSummarysliceReader

r = PyJDAQSummarysliceReader("KM3NeT_00000013_00000501.root")

i = 0
while r.has_next:
    r.retrieve_next_summaryslice()
    print("Frame index: {0}".format(r.frame_index))
    print("Detector ID: {0}".format(r.det_id))
    print("Run Number:  {0}".format(r.run_number))
    print("UTC Seconds: {0}".format(r.utc_seconds))
    print("UTC NanoSeconds:  {0}".format(r.utc_nanoseconds))
    j = 0
    print("Number of Frames: {0}".format(r.number_of_frames))
    while r.has_next_frame:
        print(r.number_of_received_packets, r.max_sequence_number, r.module_id,
              r.has_udp_trailer, r.white_rabbit_status, r.high_rate_veto,
              r.fifo_status)
        r.retrieve_next_frame()
        j += 1
    i += 1


