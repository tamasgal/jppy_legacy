from ctypes import cdll
lib = cdll.LoadLibrary('./libreadout.so')

class JDAQEventReader(object):
    def __init__(self):
        self.obj = lib.JDAQEventReader_new()

    def get_next_tot(self):
        lib.JDAQEventReader_get_next_tot(self.obj)


