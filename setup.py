#!/usr/bin/env python
# coding=utf-8
# Filename: setup.py
"""
jppp setup script.

"""
from distutils.core import setup
from distutils.extension import Extension
import os
import subprocess

try:
    from Cython.Build import cythonize
    import numpy
except:
    raise SystemExit("Please install Cython and Numpy:\n\n"
                     "    pip install cython numpy")

try:
    os.environ['JPP_DIR']
except KeyError:
    raise SystemExit("\n$JPP_DIR is not set. "
                     "You need to activate the JPP environment!")

ROOT_INC = subprocess.Popen(["root-config", "--incdir"],
                            stdout=subprocess.PIPE).communicate()[0].strip()
ROOT_LIB = subprocess.Popen(["root-config", "--libdir"],
                            stdout=subprocess.PIPE).communicate()[0].strip()
JPP_INC = os.environ['JPP_INC']
JPP_LIB = os.environ['JPP_LIB']


extensions = [
    Extension("jppp", ["jppp.pyx"],
              include_dirs=[JPP_INC, ROOT_INC, numpy.get_include()],
              library_dirs=[ROOT_LIB, JPP_LIB],
              libraries=['KM3NeTDAQROOT',
                         'pthread', 'dl', 'util', 'm',
                         'Core', 'Cint', 'RIO', 'Net', 'Hist', 'Graf',
                         'Graf3d', 'Tree', 'Rint', 'Matrix', 'Physics',
                         'MathCore', 'Gpad', 'Thread'],
              # extra_link_args=[]
              ),
]

setup(ext_modules=cythonize(extensions, language='c++', gdb_debug=True))