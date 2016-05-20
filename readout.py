from ctypes import cdll
lib = cdll.LoadLibrary('./libreadout.so')

class JDAQEventReader(object):
    def __init__(self):
        self.obj = lib.JDAQEventReader_new()

    def get_next_tot(self):
        return lib.JDAQEventReader_get_next_tot(self.obj)

    def bar(self):
        return lib.JDAQEventReader_bar(self.obj)


reader = JDAQEventReader()
print(reader.bar())
print(reader.get_next_tot())
print(reader.get_next_tot())

