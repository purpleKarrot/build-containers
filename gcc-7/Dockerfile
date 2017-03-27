FROM purplekarrot/base:latest

RUN echo 'deb http://ftp.debian.org/debian experimental main' >> /etc/apt/sources.list \
    && apt-get -qq update \
    && apt-get -qq -t experimental install -y --no-install-recommends g++-7 \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/gcc-7" \
    CXX="/usr/bin/g++-7" \
    COVERAGE_COMMAND="/usr/bin/gcov-7" \
    COVERAGE_FLAGS="--coverage"
