FROM purplekarrot/base

RUN apt-get update \
    && apt-get install -y --no-install-recommends qtbase5-dev \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update \
    && apt-get install -y --no-install-recommends g++-5 \
    && rm -rf /var/lib/apt/lists/*

ENV CTEST_COVERAGE_COMMAND="/usr/bin/gcov-5"

COPY ./toolchain.cmake /
