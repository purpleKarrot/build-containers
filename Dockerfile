FROM debian:stretch
MAINTAINER Daniel Pfeifer "daniel@pfeifer-mail.de"

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    make \
    runit \
 && rm -rf /var/lib/apt/lists/*

# Build and install ninja from source.
RUN buildDeps='g++ git python' \
    && apt-get update && apt-get install -y $buildDeps --no-install-recommends \
    && git clone -b v1.7.2 --depth 1 https://github.com/martine/ninja.git \
    && cd ninja \
    && python configure.py --bootstrap \
    && mv ninja /usr/bin/ \
    && cd .. \
    && rm -rf ninja \
    && apt-get purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

# Build and install CMake from source.
RUN buildDeps='g++ git' \
    && apt-get update && apt-get install -y $buildDeps --no-install-recommends \
    && git clone -b v3.7.0 --depth 1 git://cmake.org/cmake.git CMake \
    && cd CMake \
    && mkdir build \
    && cd build \
    && ../bootstrap \
        --parallel=$(nproc) \
        --prefix=/usr \
        --no-server \
    && make -j$(nproc) \
    && make install \
    && cd / \
    && rm -rf CMake \
    && apt-get purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

COPY ./build.cmake /
COPY ./entrypoint.sh /

ENTRYPOINT ["/entrypoint.sh"]
