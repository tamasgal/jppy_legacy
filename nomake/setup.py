from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize


extensions = [
    Extension("jppp", ["jppp.pyx"],
              include_dirs=["/opt/jpp/software"],
              #libraries = [...],
              #library_dirs = [...]
             ),
]
setup(ext_modules = cythonize(extensions))
