from ctypes import cdll
lib = cdll.LoadLibrary('./libreadout.so')

class JDAQEventReader(object):
    def __init__(self):
        self.obj = lib.JDAQEventReader_new()

    def get_next_frame_index(self):
        return lib.JDAQEventReader_get_next_frame_index(self.obj)


reader = JDAQEventReader()
for i in range(4):
    idx = reader.get_next_frame_index()
    print("Getting event #{0}\n  FrameIndex: {1}".format(i, idx))
