FROM purplekarrot/base:latest

RUN dpkg --add-architecture arm64 \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        g++-aarch64-linux-gnu \
        libstdc++6:arm64 \
        qemu-user \
    && rm -rf /var/lib/apt/lists/*

COPY ./toolchain.cmake /
