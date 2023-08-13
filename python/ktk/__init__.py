# pyright: reportMissingImports=false
try:
    # note: _ktk will be available once scikit-build compiles the wheels
    from ._ktk import *
except ImportError:
    print('Internal _ktk module not found - did you install the compiled wheel?')
    raise
