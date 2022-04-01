FROM purplekarrot/base:latest

RUN dpkg --add-architecture i386 \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        g++:i386 \
        wine \
        wine32 \
        wine32-tools \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/winegcc" \
    CXX="/usr/bin/wineg++" \
    WINEARCH=win32
