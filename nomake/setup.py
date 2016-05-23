from distutils.core import setup
from Cython.Build import cythonize

setup(ext_modules = cythonize(
           "jppp.pyx",                 # our Cython source
           sources=["readout.cpp"],  # additional source file(s)
           language="c++",             # generate C++ code
           extra_compile_args=["-c", "-fPIC", "-I$(root-config --incdir)",
                               "$(python-config --includes)", "-I/sps/km3net/users/tgal/apps/jpp/trunk/software"],
      ))
