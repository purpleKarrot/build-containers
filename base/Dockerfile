FROM debian:sid
MAINTAINER Daniel Pfeifer "daniel@pfeifer-mail.de"

ENV HOME="/home/builder"
RUN mkdir -p $HOME

RUN true \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        ca-certificates \
        cmake \
        make \
        ninja-build \
        runit \
    && rm -rf /var/lib/apt/lists/*

# Disable git warning about detached HEAD.
RUN buildDeps='git' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && git config --global advice.detachedHead false \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

COPY . /

ENTRYPOINT ["/entrypoint.sh"]
