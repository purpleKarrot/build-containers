FROM debian:12-slim
MAINTAINER Daniel Pfeifer "daniel@pfeifer-mail.de"

RUN true \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        ca-certificates \
        cmake \
        make \
        ninja-build \
    && rm -rf /var/lib/apt/lists/*

COPY . /

ENTRYPOINT ["/usr/bin/ctest", "--script", "/entrypoint.cmake"]
