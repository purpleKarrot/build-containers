FROM purplekarrot/base:latest

RUN apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends g++-6 \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/gcc-6" \
    CXX="/usr/bin/g++-6" \
    COVERAGE_COMMAND="/usr/bin/gcov-6" \
    COVERAGE_FLAGS="--coverage"
