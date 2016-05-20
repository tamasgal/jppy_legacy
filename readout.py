from ctypes import cdll, c_char_p
import sys

lib = cdll.LoadLibrary('./libreadout.so')

lib.JDAQEventReader_new.argtypes = [c_char_p]

class JDAQEventReader(object):
    def __init__(self, filename):
        print("Filename: {0}".format(filename))
        self.obj = lib.JDAQEventReader_new(filename)

    def get_next_frame_index(self):
        return lib.JDAQEventReader_get_next_frame_index(self.obj)

    def has_next(self):
        return lib.JDAQEventReader_has_next(self.obj)

    def event_generator(self):
        while self.has_next():
            yield self.get_next_frame_index()


reader = JDAQEventReader(sys.argv[1])

event_generator = reader.event_generator()
for event in event_generator:
    print(event)
