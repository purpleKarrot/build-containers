FROM purplekarrot/base

RUN VERSION=4.0 && \
    apt-get update && \
    apt-get install -y --no-install-recommends clang-${VERSION} && \
    mkdir /tmp/clang-tidy && \
    chown _apt /tmp/clang-tidy && \
    cd /tmp/clang-tidy && \
    apt-get download clang-tidy-${VERSION} && \
    dpkg -x clang-tidy-${VERSION}_*.deb . && \
    cp usr/bin/clang-tidy-${VERSION} /usr/bin && \
    cp usr/lib/llvm-${VERSION}/bin/clang-tidy /usr/lib/llvm-${VERSION}/bin/ && \
    cd / && \
    rm -rf /tmp/clang-tidy && \
    rm -rf /var/lib/apt/lists/*

ENV CTEST_MEMORYCHECK_TYPE="AddressSanitizer"

COPY ./toolchain.cmake /
