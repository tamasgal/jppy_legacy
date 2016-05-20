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

    @property
    def has_next(self):
        return lib.JDAQEventReader_has_next(self.obj)

    def __iter__(self):
        return self

    def next(self):
        """Python 2/3 compatibility for iterators"""
        return self.__next__()

    def __next__(self):
        if self.has_next:
            return self.get_next_frame_index()
        else:
            raise StopIteration


for event in JDAQEventReader(sys.argv[1]):
    print(event)
