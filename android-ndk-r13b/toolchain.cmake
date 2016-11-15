include("/opt/android-ndk/build/cmake/android.toolchain.cmake")

if(EXISTS "/source/.clang-tidy")
  set(CMAKE_CXX_CLANG_TIDY
    "${ANDROID_LLVM_TOOLCHAIN_PREFIX}clang-tidy${ANDROID_TOOLCHAIN_SUFFIX}"
    CACHE INTERNAL "" FORCE)
endif()

set(CMAKE_CROSSCOMPILING_EMULATOR /usr/bin/qemu-arm)
