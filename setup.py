# -*- coding: utf-8 -*-
from __future__ import print_function
from os import sys

try:
    from skbuild import setup
except ImportError:
    print('scikit-build is required to build from source.', file=sys.stderr)
    print('Please run:', file=sys.stderr)
    print('', file=sys.stderr)
    print('  python -m pip install scikit-build')
    sys.exit(1)

setup(
    name='itk-subdivisionquadedgemeshfilter',
    version='1.1.0',
    author='Wanlin Zhu',
    author_email='wanlin.zhu@unsw.edu.au',
    packages=['itk'],
    package_dir={'itk': 'itk'},
    download_url=r'https://github.com/InsightSoftwareConsortium/ITKSubdivisionQuadEdgeMeshFilter',
    description=r'ITK classes for triangle mesh subdivision',
    long_description='itk-subdivisionquadedgemeshfilter provides classes for '
                     'triangle mesh subdivision.\n'
                     'Please refer to:\n'
                     'W. Zhu, "Triangle Mesh Subdivision.", '
                     'Insight Journal, July-December 2011, http://hdl.handle.net/10380/3307.',
    classifiers=[
        "License :: OSI Approved :: Apache Software License",
        "Programming Language :: Python",
        "Programming Language :: C++",
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Intended Audience :: Education",
        "Intended Audience :: Healthcare Industry",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Medical Science Apps.",
        "Topic :: Scientific/Engineering :: Information Analysis",
        "Topic :: Software Development :: Libraries",
        "Operating System :: Android",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: POSIX",
        "Operating System :: Unix",
        "Operating System :: MacOS"
        ],
    license='Apache',
    keywords='ITK InsightToolkit Geometry Mesh',
    url=r'https://github.com/InsightSoftwareConsortium/ITKSubdivisionQuadEdgeMeshFilter',
    install_requires=[
        r'itk>=5.1.1'
    ]
    )
