FROM purplekarrot/base:latest

RUN apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends g++ \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/gcc" \
    CXX="/usr/bin/g++" \
    COVERAGE_COMMAND="/usr/bin/gcov" \
    COVERAGE_FLAGS="--coverage"
