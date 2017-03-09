FROM purplekarrot/base:stretch

RUN true \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        g++-mingw-w64-x86-64 \
        nsis \
        wine \
        wine64 \
    && rm -rf /var/lib/apt/lists/*

ENV WINEARCH=win64 \
    WINEPATH=/usr/lib/gcc/x86_64-w64-mingw32/6.2-win32/

RUN buildDeps='procps' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && wine64 hostname > /dev/null \
    && while pgrep wineserver > /dev/null; do sleep 1; done \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

RUN echo '\
set(CMAKE_SYSTEM_NAME Windows)\n\
\n\
set(CMAKE_C_COMPILER   \"/usr/bin/x86_64-w64-mingw32-gcc\")\n\
set(CMAKE_CXX_COMPILER \"/usr/bin/x86_64-w64-mingw32-g++\")\n\
set(CMAKE_RC_COMPILER  \"/usr/bin/x86_64-w64-mingw32-windres\")\n\
\n\
set(CMAKE_CROSSCOMPILING_EMULATOR \"/usr/bin/wine64\")\n\
' >> /toolchain.cmake
