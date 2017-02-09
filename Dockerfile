FROM debian:stretch
MAINTAINER Daniel Pfeifer "daniel@pfeifer-mail.de"

ENV HOME="/home/builder"
RUN mkdir -p $HOME

RUN true \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        ca-certificates \
        libarchive13 \
        libcurl3 \
        libexpat1 \
        libjsoncpp1 \
        librhash0 \
        libuv1 \
        make \
        runit \
        zlib1g \
    && rm -rf /var/lib/apt/lists/*

# Disable git warning about detached HEAD.
RUN buildDeps='git' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && git config --global advice.detachedHead false \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

# Build and install ninja from source.
RUN buildDeps='g++ git python' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && git clone -b v1.7.2 --depth 1 https://github.com/martine/ninja.git \
    && cd ninja \
    && python configure.py --bootstrap \
    && mv ninja /usr/local/bin/ \
    && cd / \
    && rm -rf ninja \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

# Build and install CMake from source.
RUN buildDeps=' \
        g++ \
        git \
        libarchive-dev \
        libcurl4-openssl-dev \
        libexpat1-dev \
        libjsoncpp-dev \
        librhash-dev \
        libuv1-dev \
        zlib1g-dev \
        ' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && git clone -b v3.8.0-rc1 --depth 1 git://cmake.org/cmake.git CMake \
    && cd CMake \
    && mkdir build \
    && cd build \
    && ../bootstrap \
        --parallel=$(nproc) \
        --prefix=/usr/local \
        --system-libs \
        --no-server \
    && make -j$(nproc) \
    && make install \
    && cd / \
    && rm -rf CMake \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

COPY ./build.cmake /
COPY ./entrypoint.cmake /
COPY ./entrypoint.sh /

ENTRYPOINT ["/entrypoint.sh"]
