FROM purplekarrot/clang-3.9

# Build and install clazy from source.
RUN buildDeps='git libclang-3.9-dev llvm-3.9-dev zlib1g-dev' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && git clone -b 1.1 --depth 1 https://github.com/KDE/clazy.git \
    && mkdir clazy/build \
    && cd clazy/build \
    && cmake -GNinja .. \
        -DCMAKE_INSTALL_PREFIX=/usr \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_LIBDIR=lib \
        -DLLVM_CONFIG_EXECUTABLE:FILEPATH=/usr/bin/llvm-config-3.9 \
    && ninja \
    && ninja install \
    && cd / \
    && rm -rf clazy \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

ENV CLANGXX=$CXX \
    CXX="/usr/bin/clazy"
