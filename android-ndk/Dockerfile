FROM purplekarrot/base:latest

RUN true \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends qemu-user \
    && rm -rf /var/lib/apt/lists/*

RUN buildDeps='curl unzip' revision='14b' \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends $buildDeps \
    && curl -SLO http://dl.google.com/android/repository/android-ndk-r${revision}-linux-x86_64.zip \
    && unzip android-ndk-r${revision}-linux-x86_64.zip \
    && mv ./android-ndk-r${revision} /opt/ndk \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

COPY toolchain.cmake .
