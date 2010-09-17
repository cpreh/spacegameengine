Installation instructions:

This readme file contains some information on how to compile and install sge.
sge's architecture uses plugins to abstract specific libraries and such. Most
of the sge functionality will not be available if you lack plugins such as
image loader, renderer, input or font, and thus the test programs won't run.
Please follow the instructions below.

1. Common requirements
  To compile sge you need:
  - cmake (see cmake.org)
  - probably pkgconfig (if you are not on Windows)
  - boost (see boost.org)

  The boost version used is currently required to be 1.36 or later.

2. How to install
  If you are using Windows you might be interested in chapter 3.
  First, create a directory where the build files will go and cd into
  that directory.
  For example:
    mkdir build && cd build
  Now you can type 'cmake ..' and see which generators
  are available. For example a generator can be UNIX makefiles, VC++ project
  files and such.
  Type 'cmake -G "Unix Makefiles" ..' for example to build Unix makefiles that can
  later be used by make to compile sge.
  If there is only one meaningful generator available on your system,
  cmake will default to that.

  Now you have to choose which plugins you want cmake to build.
  This step is very important and I recommend users of a POSIX system to at
  least enable DEVIL, FREETYPE, OPENGL and X11INPUT.
  This can be done in the following way:
  'cmake -DENABLE_DEVIL:=1 -DENABLE_FREETYPE:=1
  -DENABLE_OPENGL:=1-DENABLE_X11INPUT:=1 ..'

  At the moment the following options are available:
  - BULLET (build the bullet collision plugin)
  - DEVIL (build the devil image loader plugin)
  - DINPUT (build the direct input plugin - Windows only)
  - FREETYPE (build the freetype font plugin)
  - GUI (build the gui)
  - OPENAL (build the openal audio plugin)
  - OPENGL (build the opengl plugin)
  - TEST (build the tests)
  - VORBIS (build the vorbis loader plugin)
  - WAVE (build the wave loader plugin)
  - X11INPUT (build the x11 input plugin - X11 only)

  Last you have to specify where sge will install into.
  The default is /usr/local on UNIX. You can change the behaviour if you type
  'cmake -D CMAKE_INSTALL_PREFIX="prefix" ..'.
  For example, if you want to have a local install, type
  'cmake -D CMAKE_INSTALL_PREFIX="/home/me/local" ..'
  If you don't want to install sge, type 'cmake -D DONT_INSTALL:=1 ..'.
  sge will then run out of the source directory only.

  If you think you have enabled enough, run 'cmake ..' again and use the build
  system you have specified the generator for, usually 'make'.

  Last run make install with an optional DESTDIR argument to install sge.


3. Installing on Windows
  If you want to install sge on windows, you can use the above mentioned
  procedure as well, but there is also a batch file available that can do more
  stuff for you: win32_install.bat.
  Call it from the command prompt and see which options it offers.
  For example. if you want to generate VC++ 2008 project files just type
  'win32install.bat vc9'.
  The script will enable most of the plugins as sge packs their needed libraries
  for windows.
  mingw has spurious concept checks on by default.
  Please turn them off by editing c++config.h.

4. Troubleshooting
  - sge won't compile because I installed boost in $some_random_directory!

    cmake tries to find boost itself. If it fails, read 'cmake --help-full' and
    search for Boost in there. For example you can specify BOOST_ROOT to point
    to your boost installation. 

5. Contact
  - If you have any problems please visit #sge-sanguis on freenode or drop me
    a mail to sefi <at> s-e-f-i.de.
