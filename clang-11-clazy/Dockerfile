FROM purplekarrot/clang-11

RUN true \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends clazy \
    && rm -rf /var/lib/apt/lists/*

ENV CLANGXX=$CXX \
    CXX="/usr/bin/clazy"
