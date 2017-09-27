FROM purplekarrot/base:latest

RUN VERSION=6.0 \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends clang-${VERSION} \
    && mkdir /tmp/clang-tidy \
    && chown _apt /tmp/clang-tidy \
    && cd /tmp/clang-tidy \
    && apt-get -qq download clang-tidy-${VERSION} \
    && dpkg -x clang-tidy-${VERSION}_*.deb . \
    && cp usr/bin/clang-tidy-${VERSION} /usr/bin \
    && cp usr/lib/llvm-${VERSION}/bin/clang-tidy /usr/lib/llvm-${VERSION}/bin/ \
    && cd / \
    && rm -rf /tmp/clang-tidy \
    && rm -rf /var/lib/apt/lists/*

ENV CC="/usr/bin/clang-6.0" \
    CXX="/usr/bin/clang++-6.0"

RUN echo '\
if(EXISTS \"/source/.clang-tidy\")\n\
  set(CMAKE_CXX_CLANG_TIDY \"/usr/bin/clang-tidy-6.0\" CACHE INTERNAL \"\" FORCE)\n\
endif()\n\
' >> /toolchain.cmake
