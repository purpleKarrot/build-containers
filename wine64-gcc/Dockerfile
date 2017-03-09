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

RUN buildDeps='procps' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && wine64 hostname > /dev/null \
    && while pgrep wineserver > /dev/null; do sleep 1; done \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*
