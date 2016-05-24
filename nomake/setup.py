import os

from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import subprocess

ROOT_INC = subprocess.Popen(["root-config", "--incdir"],
                            stdout=subprocess.PIPE).communicate()[0].strip()
ROOT_LIB = subprocess.Popen(["root-config", "--libdir"],
                            stdout=subprocess.PIPE).communicate()[0].strip()
JPP_INC = os.environ['JPP_INC']
JPP_LIB = os.environ['JPP_LIB']
print(JPP_LIB)

extensions = [
    Extension("daqeventreader", ["daqeventreader.pyx"],
              include_dirs=[JPP_INC, ROOT_INC],
              library_dirs = [ROOT_LIB, JPP_LIB],
              libraries = ['KM3NeTDAQROOT',
                           'pthread', 'dl', 'util', 'm', 'Core', 'Cint', 'RIO',
                           'Net', 'Hist', 'Graf', 'Graf3d', 'Tree', 'Rint',
                           'Matrix', 'Physics', 'MathCore', 'Gpad', 'Thread',
                          ],
              #extra_link_args=[]
             ),
]
setup(ext_modules = cythonize(extensions, language='c++'))
