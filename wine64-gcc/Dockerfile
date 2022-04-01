FROM purplekarrot/base:latest

RUN true \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        g++ \
        wine \
        wine64 \
        wine64-tools \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/winegcc" \
    CXX="/usr/bin/wineg++" \
    WINEARCH=win64
