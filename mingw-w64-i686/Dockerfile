FROM purplekarrot/base:latest

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

COPY toolchain.cmake .
