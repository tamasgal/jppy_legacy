import os

from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

import subprocess

ROOT_INC = subprocess.Popen(["root-config", "--incdir"],
                            stdout=subprocess.PIPE).communicate()[0].strip()
JPP_INC = os.environ['JPP_INC']

extensions = [
    Extension("jppp", ["jppp.pyx"],
              include_dirs=[JPP_INC, ROOT_INC, ],
              #libraries = [...],
              #library_dirs = [...]
             ),
]
setup(ext_modules = cythonize(extensions))
