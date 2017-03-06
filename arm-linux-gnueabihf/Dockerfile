FROM purplekarrot/base:latest

RUN dpkg --add-architecture armhf \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        g++-arm-linux-gnueabihf \
        libstdc++6:armhf \
        qemu-user \
    && rm -rf /var/lib/apt/lists/*

COPY ./toolchain.cmake /
