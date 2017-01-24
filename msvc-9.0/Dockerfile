FROM purplekarrot/base

ENV WINEARCH="win32"
ENV VSINSTALLDIR="C:\\Program Files\\Common Files\\Microsoft\\Visual C++ for Python\\9.0"
ENV CL_CMD="$VSINSTALLDIR\\VC\\bin\\cl.exe" \
    LINK_CMD="$VSINSTALLDIR\\VC\\bin\\link.exe" \
    RC_CMD="$VSINSTALLDIR\\WinSDK\\Bin\\rc.exe" \
    MT_CMD="$VSINSTALLDIR\\WinSDK\\Bin\\mt.exe"

RUN dpkg --add-architecture i386 \
    && apt-get -qq update \
    && apt-get -qq install -y --no-install-recommends \
        nsis \
        wine-development \
        wine32-development \
    && rm -rf /var/lib/apt/lists/*

RUN buildDeps='procps' \
    hostprefix='/home/builder/.wine/drive_c/Program\ Files/Common\ Files/Microsoft/Visual\ C++\ for\ Python/9.0' \
    && apt-get -qq update \
    && apt-get -qq install -y $buildDeps --no-install-recommends \
    && msiexec /i https://download.microsoft.com/download/7/9/6/796EF2E4-801B-4FC4-AB28-B59FBF6D907B/VCForPython27.msi /qn \
    && wine reg add HKEY_CURRENT_USER\\Environment /v PATH /t REG_EXPAND_SZ /d "$VSINSTALLDIR\\VS\\bin;$VSINSTALLDIR\\WinSDK\\Bin" /f \
    && wine reg add HKEY_CURRENT_USER\\Environment /v INCLUDE /t REG_EXPAND_SZ /d "$VSINSTALLDIR\\VS\\include;$VSINSTALLDIR\\WinSDK\\Include" /f \
    && wine reg add HKEY_CURRENT_USER\\Environment /v LIB /t REG_EXPAND_SZ /d "$VSINSTALLDIR\\VS\\lib;$VSINSTALLDIR\\WinSDK\\Lib" /f \
    && wine reg add HKEY_CURRENT_USER\\Environment /v LIBPATH /t REG_EXPAND_SZ /d "$VSINSTALLDIR\\VS\\lib;$VSINSTALLDIR\\WinSDK\\Lib" /f \
    && while pgrep wineserver > /dev/null; do sleep 1; done \
    && rm -rf \
        $hostprefix/VC/bin/amd64 \
        $hostprefix/VC/bin/x86_amd64 \
        $hostprefix/VC/lib/amd64 \
        $hostprefix/WinSDK/Bin/x64 \
        $hostprefix/WinSDK/Lib/x64 \
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

COPY ./toolchain.cmake /
