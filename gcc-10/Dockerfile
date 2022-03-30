FROM purplekarrot/base:latest

RUN apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends g++-10 \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/gcc-10" \
    CXX="/usr/bin/g++-10" \
    COVERAGE_COMMAND="/usr/bin/gcov-10" \
    COVERAGE_FLAGS="--coverage"
