FROM purplekarrot/base

RUN apt-get update \
    && apt-get install -y --no-install-recommends qemu-user \
    && rm -rf /var/lib/apt/lists/*

RUN buildDeps='curl file python unzip' \
    revision='13b' \
    && apt-get update && apt-get install -y --no-install-recommends $buildDeps \
    && mkdir /tmp/android-ndk \
    && cd /tmp/android-ndk \
    && curl -SLO http://dl.google.com/android/repository/android-ndk-r${revision}-linux-x86_64.zip \
    && unzip android-ndk-r${revision}-linux-x86_64.zip \
    && /bin/bash ./android-ndk-r${revision}/build/tools/make-standalone-toolchain.sh \
        --arch=arm \
        --platform=android-24 \
        --install-dir=/opt/android-ndk \
    && cd / \
    && rm -rf /tmp/android-ndk \
    && apt-get purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

COPY toolchain.cmake .
