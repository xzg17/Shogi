from distutils.core import setup, Extension
import os

os.environ['CC'] = 'gcc'

src_dir = 'src'

ext_modules = []
ext_modules.append(Extension('_board',[src_dir + '/debug.cpp']))
setup(
  name='Shogi',
  ext_modules = ext_modules,
  url="https://github.com/xzg17/Shogi"
)
