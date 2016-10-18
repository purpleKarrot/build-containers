FROM purplekarrot/base

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++-6 \
 && rm -rf /var/lib/apt/lists/*

ENV CTEST_COVERAGE_COMMAND="/usr/bin/gcov-6"

COPY ./toolchain.cmake /
