FROM purplekarrot/base

ENV WINEARCH="win32"

RUN dpkg --add-architecture i386 \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        nsis \
        wine-development \
        wine32-development \
    && rm -rf /var/lib/apt/lists/*

RUN buildDeps='curl p7zip-full procps' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && mkdir /msvc \
    && cd /msvc \
    && curl -SLO https://download.microsoft.com/download/f/e/6/fe6eb291-e187-4b06-ad78-bb45d066c30f/6.0.6001.18000.367-KRMSDK_EN.iso \
    && 7z x *.iso \
    && msiexec /i https://dl.winehq.org/wine/wine-mono/4.6.4/wine-mono-4.6.4.msi /qn \
    && msiexec /i Setup/vc_stdx86.msi /qn ADDEPLOY=1 \
    && msiexec /i Setup/WinSDKBuild-x86.msi /qn ADDEPLOY=1 \
    && msiexec /i Setup/WinSDKWin32Tools-x86.msi /qn ADDEPLOY=1 \
    && while pgrep wineserver > /dev/null; do sleep 1; done \
    && cd / \
    && rm -rf /msvc \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*

COPY wrapmsvc /wrapmsvc

RUN buildDeps='wine32-development-tools' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && cd /wrapmsvc \
    && winegcc -m32 $CFLAGS -o "/usr/bin/cl" wrapmsvc.c -DWRAP_CL -lmsvcrt \
    && winegcc -m32 $CFLAGS -o "/usr/bin/link" wrapmsvc.c -DWRAP_LINK -lmsvcrt \
    && winegcc -m32 $CFLAGS -o "/usr/bin/rc" wrapmsvc.c -DWRAP_RC -lmsvcrt \
    && winegcc -m32 $CFLAGS -o "/usr/bin/mt" wrapmsvc.c -DWRAP_MT -lmsvcrt \
    && cd / \
    && rm -rf /wrapmsvc \
    && apt-get -qq purge --auto-remove -y $buildDeps \
    && rm -rf /var/lib/apt/lists/*
