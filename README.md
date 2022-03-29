# Docker Images for C++ Toolchains

## Images

### purplekarrot/base <a href="https://hub.docker.com/r/purplekarrot/base"><img alt="purplekarrot/base" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/base"></a>

This is the base for other toolchain images. From [Debian Sid](https://www.debian.org/releases/sid/) with [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/).

### purplekarrot/android-ndk <a href="https://hub.docker.com/r/purplekarrot/android-ndk"><img alt="purplekarrot/android-ndk" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/android-ndk"></a>

Contains the [Android NDK](https://developer.android.com/ndk/index.html).

### purplekarrot/android-standalone <a href="https://hub.docker.com/r/purplekarrot/android-standalone"><img alt="purplekarrot/android-standalone" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/android-standalone"></a>

Contains a [standalone toolchain](https://developer.android.com/ndk/guides/standalone_toolchain.html).

### purplekarrot/clang-3.9 <a href="https://hub.docker.com/r/purplekarrot/clang-3.9"><img alt="purplekarrot/clang-3.9" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/clang-3.9"></a>

Contains [Clang](http://clang.llvm.org/), [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/), and [Include-What-You-Use](https://include-what-you-use.org/) in version 3.9.

### purplekarrot/clang-3.9-clazy <a href="https://hub.docker.com/r/purplekarrot/clang-3.9-clazy"><img alt="purplekarrot/clang-3.9-clazy" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/clang-3.9-clazy"></a>

Same as purplekarrot/clang-3.9, but uses [Clazy](https://github.com/KDE/clazy) as the C++ compiler.

### purplekarrot/clang-4.0 <a href="https://hub.docker.com/r/purplekarrot/clang-4.0"><img alt="purplekarrot/clang-4.0" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/clang-4.0"></a>

Contains [Clang](http://clang.llvm.org/) and [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/) in version 4.0.

### purplekarrot/clang-4.0-clazy <a href="https://hub.docker.com/r/purplekarrot/clang-4.0-clazy"><img alt="purplekarrot/clang-4.0-clazy" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/clang-4.0-clazy"></a>

Same as purplekarrot/clang-4.0, but uses [Clazy](https://github.com/KDE/clazy) as the C++ compiler.

### purplekarrot/clang-5.0 <a href="https://hub.docker.com/r/purplekarrot/clang-5.0"><img alt="purplekarrot/clang-5.0" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/clang-5.0"></a>

Contains [Clang](http://clang.llvm.org/) and [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/) in version 5.0.

### purplekarrot/clang-6.0 <a href="https://hub.docker.com/r/purplekarrot/clang-6.0"><img alt="purplekarrot/clang-6.0" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/clang-6.0"></a>

Contains [Clang](http://clang.llvm.org/) and [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/) in version 6.0.

### purplekarrot/gcc-5 <a href="https://hub.docker.com/r/purplekarrot/gcc-5"><img alt="purplekarrot/gcc-5" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/gcc-5"></a>

Uses [GCC](https://gcc.gnu.org/) version 5.

### purplekarrot/gcc-6 <a href="https://hub.docker.com/r/purplekarrot/gcc-6"><img alt="purplekarrot/gcc-6" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/gcc-6"></a>

Uses [GCC](https://gcc.gnu.org/) version 6.

### purplekarrot/gcc-7 <a href="https://hub.docker.com/r/purplekarrot/gcc-7"><img alt="purplekarrot/gcc-7" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/gcc-7"></a>

Uses [GCC](https://gcc.gnu.org/) version 7.

### purplekarrot/gcc-8 <a href="https://hub.docker.com/r/purplekarrot/gcc-8"><img alt="purplekarrot/gcc-8" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/gcc-8"></a>

Uses [GCC](https://gcc.gnu.org/) version 8.

### purplekarrot/mingw-w64-i686 <a href="https://hub.docker.com/r/purplekarrot/mingw-w64-i686"><img alt="purplekarrot/mingw-w64-i686" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/mingw-w64-i686"></a>

Uses MinGW to target 32bit Windows. It uses [Wine](https://www.winehq.org/) as crosscompiling emulator and [NSIS](http://nsis.sourceforge.net/) to create packages.

### purplekarrot/mingw-w64-x86-64 <a href="https://hub.docker.com/r/purplekarrot/mingw-w64-x86-64"><img alt="purplekarrot/mingw-w64-x86-64" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/mingw-w64-x86-64"></a>

Uses MinGW to target 64bit Windows. It uses [Wine](https://www.winehq.org/) as crosscompiling emulator and [NSIS](http://nsis.sourceforge.net/) to create packages.
