set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_ANDROID_NDK "/opt/ndk")

# if(EXISTS "/source/.clang-tidy")
#   set(CMAKE_CXX_CLANG_TIDY "/opt/android-ndk/bin/clang-tidy" CACHE INTERNAL "" FORCE)
# endif()

set(CMAKE_CROSSCOMPILING_EMULATOR /usr/bin/qemu-arm)
