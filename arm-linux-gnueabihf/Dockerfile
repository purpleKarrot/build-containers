FROM purplekarrot/base

RUN apt-get update
    && apt-get install -y --no-install-recommends qemu-user \
    && rm -rf /var/lib/apt/lists/*

ENV PKG_CONFIG_LIBDIR=/usr/lib/arm-linux-gnueabihf/pkgconfig:/opt/qt5/lib/pkgconfig \
    PKG_CONFIG_SYSROOT_DIR=/

RUN dpkg --add-architecture armhf \
    && apt-get update && apt-get install -y --no-install-recommends \
        g++-arm-linux-gnueabihf \
        libfontconfig1-dev:armhf \
        libfreetype6-dev:armhf \
        libx11-dev:armhf \
        libxext-dev:armhf \
        libxfixes-dev:armhf \
        libxi-dev:armhf \
        libxrender-dev:armhf \
        libxcb1-dev:armhf \
        libx11-xcb-dev:armhf \
        libxcb-glx0-dev:armhf \
    && rm -rf /var/lib/apt/lists/*

# TODO: (to save a little time and space)
#   * install qtbase5-dev-tools permanently
#   * install qt5-qmake during the build
#   * build qt with qmake without bootstrapping
#   * use system zlib jpeg pcre sqlite tiff ?

RUN buildDeps='g++ git python' \
    && apt-get update && apt-get install -y $buildDeps --no-install-recommends \
    && git clone --recursive --branch v5.6.2 git://code.qt.io/qt/qt5.git \
    && cd qt5 \
    && ./configure -opensource -confirm-license -release -static \
        -prefix /opt/qt5 \
        -hostprefix /usr/local \
        -device linux-arm-generic-g++ \
        -device-option CROSS_COMPILE=/usr/bin/arm-linux-gnueabihf- \
        -device-option DISTRO_OPTS=hard-float \
        -no-xcb \
        -nomake tests \
        -nomake examples \
        -skip qtactiveqt \
        -skip qtwebchannel \
        -skip qtwebengine \
        -skip qtwebkit \
        -skip qtwebsockets \
        -skip qtwebview \
        -skip qtxmlpatterns \
    && make -j $(nproc) \
    && make install \
    && cd - \
    && rm -rf qt5 \
    && apt-get purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

COPY ./toolchain.cmake /
