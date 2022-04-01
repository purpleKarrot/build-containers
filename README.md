# Docker Images for C++ Toolchains

## Images

### purplekarrot/base <a href="https://hub.docker.com/r/purplekarrot/base"><img alt="purplekarrot/base" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/base"></a>

This is the base for other toolchain images. From [Debian 11](https://www.debian.org/releases/bullseye/) with [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/).

### purplekarrot/x86-64-linux-gnu <a href="https://hub.docker.com/r/purplekarrot/x86-64-linux-gnu"><img alt="purplekarrot/x86-64-linux-gnu" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/x86-64-linux-gnu"></a>

Uses the [GNU compiler](https://gcc.gnu.org/) and targets the amd64 architecture.

### purplekarrot/aarch64-linux-gnu <a href="https://hub.docker.com/r/purplekarrot/aarch64-linux-gnu"><img alt="purplekarrot/aarch64-linux-gnu" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/aarch64-linux-gnu"></a>

Uses the [GNU compiler](https://gcc.gnu.org/) and targets the arm64 architecture.

### purplekarrot/arm-linux-gnueabihf <a href="https://hub.docker.com/r/purplekarrot/arm-linux-gnueabihf"><img alt="purplekarrot/arm-linux-gnueabihf" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/arm-linux-gnueabihf"></a>

Uses the [GNU compiler](https://gcc.gnu.org/) and targets the armhf architecture.

### purplekarrot/android-ndk <a href="https://hub.docker.com/r/purplekarrot/android-ndk"><img alt="purplekarrot/android-ndk" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/android-ndk"></a>

Contains the [Android NDK](https://developer.android.com/ndk/index.html).

### purplekarrot/android-standalone <a href="https://hub.docker.com/r/purplekarrot/android-standalone"><img alt="purplekarrot/android-standalone" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/android-standalone"></a>

Contains a [standalone toolchain](https://developer.android.com/ndk/guides/standalone_toolchain.html).

### purplekarrot/clang-11 <a href="https://hub.docker.com/r/purplekarrot/clang-11"><img alt="purplekarrot/clang-11" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/clang-11"></a>

Contains [Clang](http://clang.llvm.org/), [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/), and [Include-What-You-Use](https://include-what-you-use.org/) in version 11.

### purplekarrot/clang-11-clazy <a href="https://hub.docker.com/r/purplekarrot/clang-11-clazy"><img alt="purplekarrot/clang-11-clazy" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/clang-11-clazy"></a>

Same as purplekarrot/clang-11, but uses [Clazy](https://github.com/KDE/clazy) as the C++ compiler.

### purplekarrot/mingw-w64-i686 <a href="https://hub.docker.com/r/purplekarrot/mingw-w64-i686"><img alt="purplekarrot/mingw-w64-i686" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/mingw-w64-i686"></a>

Uses MinGW to target 32bit Windows. It uses [Wine](https://www.winehq.org/) as crosscompiling emulator and [NSIS](http://nsis.sourceforge.net/) to create packages.

### purplekarrot/mingw-w64-x86-64 <a href="https://hub.docker.com/r/purplekarrot/mingw-w64-x86-64"><img alt="purplekarrot/mingw-w64-x86-64" align="right" src="https://img.shields.io/docker/image-size/purplekarrot/mingw-w64-x86-64"></a>

Uses MinGW to target 64bit Windows. It uses [Wine](https://www.winehq.org/) as crosscompiling emulator and [NSIS](http://nsis.sourceforge.net/) to create packages.
