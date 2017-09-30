## Electric Sheep screensaver for Kodi
[![Build Status](https://travis-ci.org/notspiff/screensaver.electricsheep.svg?branch=master)](https://travis-ci.org/notspiff/screensaver.electricsheep)

This is a working screensaver for Kodi, however there is a big caveat;
Since both Kodi and electric sheep utilizes FFmpeg, it is imperative
that the add-on is built against the exactly same version of FFmpeg,
or you have a high risk of being bitten by ABI incompatibilities. 
The Kodi binaries typically embed FFmpeg statically, and the statically linked
symbols will be used independent of how you link the add-on.

Thus, you need to build this against a Kodi build-tree to get at the appropriate
headers and libraries.

**The easiest way to achieve this is**
1. If applicable for your platform, build the kodi dependencies in BUILDDEPS.
   This will hold the FFmpeg used.
2. Build kodi in BUILDDIR
3. Configure the add-on using 

  ```cmake -DCMAKE_PREFIX_PATH=BUILDDIR/build -DCMAKE_PREFIX_PATH=BUILDDEPS -DKODI_BUILD_DIR=BUILDDIR```.

Skip the BUILDDEPS setting if your platform builds FFmpeg in the Kodi build tree and not a dependency tree.

This will build the add-on and inject it into the Kodi build tree. You can then
access it by executing the kodi binary in BUILDDIR.

It should also be possible to package up in this form, either as a zip or using 'make install' on applicable platforms.

I have only tested this on Linux (Ubuntu), but the same procedure should in
principle work for OSX. Note that electric sheep comes with its own set of
dependencies, including
- Boost::Threads
- libgtop
- liblua51
- wxwidgets >= 2.9
- libGLee
- flam3

All of these can be found using apt-get on Ubuntu. You will possibly struggle
a bit more on platforms without proper software management (OSX, LibreELEC).
