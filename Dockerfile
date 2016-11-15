FROM debian:sid
MAINTAINER Daniel Pfeifer "daniel@pfeifer-mail.de"

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    make \
    ninja-build \
    runit \
 && rm -rf /var/lib/apt/lists/*

COPY ./build.cmake /
COPY ./entrypoint.sh /

ENTRYPOINT ["/entrypoint.sh"]
