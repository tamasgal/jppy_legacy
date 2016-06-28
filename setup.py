#!/usr/bin/env python
# coding=utf-8
# Filename: setup.py
"""
jppy setup script.

"""
from distutils.core import setup
from distutils.extension import Extension
import os
import subprocess as sp

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

ROOT_INC = sp.Popen(["root-config", "--incdir"],
                    stdout=sp.PIPE).communicate()[0].strip().decode()
ROOT_LIB = sp.Popen(["root-config", "--libdir"],
                    stdout=sp.PIPE).communicate()[0].strip().decode()
JPP_INC = os.environ['JPP_INC']
JPP_LIB = os.environ['JPP_LIB']


extensions = [
    Extension("jppy", ["jppy.pyx"],
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

setup(name='jppy',
      version='1.1.0',
      url='http://git.km3net.de/tgal/jppy.git',
      description='Python bindings for JPP',
      author='Tamas Gal',
      author_email='tgal@km3net.de',
      install_requires=['cython', 'numpy'],
      ext_modules=cythonize(extensions, language='c++', gdb_debug=True),
      classifiers=[
          'Development Status :: 3 - Alpha',
          'Intended Audience :: Developers',
          'Intended Audience :: Science/Research',
          'Programming Language :: Python',
      ],
      )
