from ctypes import cdll, c_char_p, c_int, POINTER
import sys

lib = cdll.LoadLibrary('./libjppp.so')

lib.JDAQEventReader_new.argtypes = [c_char_p]
lib.JDAQEventReader_get_hits.restype = POINTER(c_int)

class JDAQEventReader(object):
    def __init__(self, filename):
        print("Filename: {0}".format(filename))
        self.obj = lib.JDAQEventReader_new(filename)

    def get_frame_index(self):
        return lib.JDAQEventReader_get_frame_index(self.obj)

    def retrieve_next_event(self):
        lib.JDAQEventReader_retrieve_next_event(self.obj)

    def get_hits(self):
        return lib.JDAQEventReader_get_hits(self.obj)

    @property
    def has_next(self):
        return lib.JDAQEventReader_has_next(self.obj)

    def __iter__(self):
        while self.has_next:
            self.retrieve_next_event()
            yield (self.get_frame_index(), self.get_hits())


for event in JDAQEventReader(sys.argv[1]):
    print(event[0])
    hits = event[1]
