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

COPY toolchain.cmake .
