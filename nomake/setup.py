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

extensions = [
    Extension("jppp", ["jppp.pyx"],
              include_dirs=[JPP_INC, ROOT_INC, ],
              library_dirs = [JPP_LIB, ROOT_LIB],
              libraries = ['pthread', 'dl', 'util', 'm', 'Core', 'Cint', 'RIO',
                           'Net', 'Hist', 'Graf', 'Graf3d', 'Tree', 'Rint',
                           'Matrix', 'Physics', 'MathCore', ],
             ),
]
setup(ext_modules = cythonize(extensions))
