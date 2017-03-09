# Docker Images for C++ Toolchains

## Images

### purplekarrot/base <a href="https://microbadger.com/images/purplekarrot/base"><img alt="purplekarrot/base" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/base.svg"></a>

This is the base for other toolchain images. From Debian Sid with make, CMake,
and Ninja.

### purplekarrot/clang-3.8 <a href="https://microbadger.com/images/purplekarrot/clang-3.8"><img alt="purplekarrot/clang-3.8" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-3.8.svg"></a>

Contains Clang and Clang-Tidy in version 3.8.

### purplekarrot/clang-3.8-clazy <a href="https://microbadger.com/images/purplekarrot/clang-3.8-clazy"><img alt="purplekarrot/clang-3.8-clazy" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-3.8-clazy.svg"></a>

Same as purplekarrot/clang-3.8, but uses Clazy as the C++ compiler.

### purplekarrot/clang-3.9 <a href="https://microbadger.com/images/purplekarrot/clang-3.9"><img alt="purplekarrot/clang-3.9" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-3.9.svg"></a>

Contains Clang, Clang-Tidy, and Include-What-You-Use in version 3.9.

### purplekarrot/clang-3.9-clazy <a href="https://microbadger.com/images/purplekarrot/clang-3.9-clazy"><img alt="purplekarrot/clang-3.9-clazy" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/clang-3.9-clazy.svg"></a>

Same as purplekarrot/clang-3.9, but uses Clazy as the C++ compiler.

### purplekarrot/gcc-5 <a href="https://microbadger.com/images/purplekarrot/gcc-5"><img alt="purplekarrot/gcc-5" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/gcc-5.svg"></a>

Uses GCC version 5.

### purplekarrot/gcc-6 <a href="https://microbadger.com/images/purplekarrot/gcc-6"><img alt="purplekarrot/gcc-6" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/gcc-6.svg"></a>

Uses GCC version 6.

### purplekarrot/mingw-w64-i686 <a href="https://microbadger.com/images/purplekarrot/mingw-w64-i686"><img alt="purplekarrot/mingw-w64-i686" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/mingw-w64-i686.svg"></a>

Uses MinGW to target 32bit Windows. It uses Wine as crosscompiling emulator and
NSIS to create packages.

### purplekarrot/mingw-w64-x86-64 <a href="https://microbadger.com/images/purplekarrot/mingw-w64-x86-64"><img alt="purplekarrot/mingw-w64-x86-64" align="right" src="https://images.microbadger.com/badges/image/purplekarrot/mingw-w64-x86-64.svg"></a>

Uses MinGW to target 64bit Windows. It uses Wine as crosscompiling emulator and
NSIS to create packages.
