FROM purplekarrot/base:latest

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

COPY toolchain.cmake .
