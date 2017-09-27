# Docker Images for C++ Toolchains

## Images

### purplekarrot/base <a href="https://microbadger.com/images/purplekarrot/base"><img alt="purplekarrot/base" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/base.svg"></a>

This is the base for other toolchain images. From [Debian Sid](https://www.debian.org/releases/sid/) with [CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/).

### purplekarrot/android-ndk <a href="https://microbadger.com/images/purplekarrot/android-ndk"><img alt="purplekarrot/android-ndk" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/android-ndk.svg"></a>

Contains the [Android NDK](https://developer.android.com/ndk/index.html).

### purplekarrot/android-standalone <a href="https://microbadger.com/images/purplekarrot/android-standalone"><img alt="purplekarrot/android-standalone" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/android-standalone.svg"></a>

Contains a [standalone toolchain](https://developer.android.com/ndk/guides/standalone_toolchain.html).

### purplekarrot/clang-3.9 <a href="https://microbadger.com/images/purplekarrot/clang-3.9"><img alt="purplekarrot/clang-3.9" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-3.9.svg"></a>

Contains [Clang](http://clang.llvm.org/), [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/), and [Include-What-You-Use](https://include-what-you-use.org/) in version 3.9.

### purplekarrot/clang-3.9-clazy <a href="https://microbadger.com/images/purplekarrot/clang-3.9-clazy"><img alt="purplekarrot/clang-3.9-clazy" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-3.9-clazy.svg"></a>

Same as purplekarrot/clang-3.9, but uses [Clazy](https://github.com/KDE/clazy) as the C++ compiler.

### purplekarrot/clang-4.0 <a href="https://microbadger.com/images/purplekarrot/clang-4.0"><img alt="purplekarrot/clang-4.0" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-4.0.svg"></a>

Contains [Clang](http://clang.llvm.org/) and [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/) in version 4.0.

### purplekarrot/clang-4.0-clazy <a href="https://microbadger.com/images/purplekarrot/clang-4.0-clazy"><img alt="purplekarrot/clang-4.0-clazy" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-4.0-clazy.svg"></a>

Same as purplekarrot/clang-4.0, but uses [Clazy](https://github.com/KDE/clazy) as the C++ compiler.

### purplekarrot/clang-5.0 <a href="https://microbadger.com/images/purplekarrot/clang-5.0"><img alt="purplekarrot/clang-5.0" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-5.0.svg"></a>

Contains [Clang](http://clang.llvm.org/) and [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/) in version 5.0.

### purplekarrot/clang-6.0 <a href="https://microbadger.com/images/purplekarrot/clang-6.0"><img alt="purplekarrot/clang-6.0" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-6.0.svg"></a>

Contains [Clang](http://clang.llvm.org/) and [Clang-Tidy](http://clang.llvm.org/extra/clang-tidy/) in version 6.0.

### purplekarrot/gcc-5 <a href="https://microbadger.com/images/purplekarrot/gcc-5"><img alt="purplekarrot/gcc-5" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/gcc-5.svg"></a>

Uses [GCC](https://gcc.gnu.org/) version 5.

### purplekarrot/gcc-6 <a href="https://microbadger.com/images/purplekarrot/gcc-6"><img alt="purplekarrot/gcc-6" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/gcc-6.svg"></a>

Uses [GCC](https://gcc.gnu.org/) version 6.

### purplekarrot/gcc-7 <a href="https://microbadger.com/images/purplekarrot/gcc-7"><img alt="purplekarrot/gcc-7" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/gcc-7.svg"></a>

Uses [GCC](https://gcc.gnu.org/) version 7.

### purplekarrot/mingw-w64-i686 <a href="https://microbadger.com/images/purplekarrot/mingw-w64-i686"><img alt="purplekarrot/mingw-w64-i686" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/mingw-w64-i686.svg"></a>

Uses MinGW to target 32bit Windows. It uses [Wine](https://www.winehq.org/) as crosscompiling emulator and [NSIS](http://nsis.sourceforge.net/) to create packages.

### purplekarrot/mingw-w64-x86-64 <a href="https://microbadger.com/images/purplekarrot/mingw-w64-x86-64"><img alt="purplekarrot/mingw-w64-x86-64" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/mingw-w64-x86-64.svg"></a>

Uses MinGW to target 64bit Windows. It uses [Wine](https://www.winehq.org/) as crosscompiling emulator and [NSIS](http://nsis.sourceforge.net/) to create packages.
