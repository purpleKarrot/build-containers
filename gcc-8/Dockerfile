FROM purplekarrot/base:latest

RUN echo 'deb http://ftp.debian.org/debian experimental main' >> /etc/apt/sources.list \
    && apt-get -qq update \
    && apt-get -qq -t experimental install -y --no-install-recommends g++-8 \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/gcc-8" \
    CXX="/usr/bin/g++-8" \
    COVERAGE_COMMAND="/usr/bin/gcov-8" \
    COVERAGE_FLAGS="--coverage"
