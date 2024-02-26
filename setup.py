from distutils.core import setup, Extension
import os

os.environ['CC'] = 'gcc'

src_dir = 'src'

ext_modules.append(Extension('Board',[src_dir + '/Board.cpp']))
setup(
  name='Board',
  ext_modules = ext_modules,
  url="https://github.com/xzg17/cppTest"
)
