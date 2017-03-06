FROM purplekarrot/base:latest

RUN apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends g++-5 \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/gcc-5" \
    CXX="/usr/bin/g++-5" \
    COVERAGE_COMMAND="/usr/bin/gcov-5" \
    COVERAGE_FLAGS="--coverage"
