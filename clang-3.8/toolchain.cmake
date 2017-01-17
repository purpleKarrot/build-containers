set(CMAKE_C_COMPILER   "/usr/bin/clang-3.8")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-3.8")

set(CMAKE_C_FLAGS_DEBUG_INIT   "-fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fsanitize=address -fno-omit-frame-pointer")

if(EXISTS "/source/.clang-tidy")
  set(CMAKE_CXX_CLANG_TIDY "/usr/bin/clang-tidy-3.8" CACHE INTERNAL "" FORCE)
endif()
