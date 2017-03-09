FROM purplekarrot/base:stretch

RUN dpkg --add-architecture i386 \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        g++-mingw-w64-i686 \
        nsis \
        wine \
        wine32 \
    && rm -rf /var/lib/apt/lists/*

ENV WINEARCH=win32 \
    WINEPATH=/usr/lib/gcc/i686-w64-mingw32/6.2-win32/

RUN buildDeps='procps' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && wine hostname > /dev/null \
    && while pgrep wineserver > /dev/null; do sleep 1; done \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

RUN echo '\
set(CMAKE_SYSTEM_NAME Windows)\n\
\n\
set(CMAKE_C_COMPILER   \"/usr/bin/i686-w64-mingw32-gcc\")\n\
set(CMAKE_CXX_COMPILER \"/usr/bin/i686-w64-mingw32-g++\")\n\
set(CMAKE_RC_COMPILER  \"/usr/bin/i686-w64-mingw32-windres\")\n\
\n\
set(CMAKE_CROSSCOMPILING_EMULATOR \"/usr/bin/wine\")\n\
' >> /toolchain.cmake
