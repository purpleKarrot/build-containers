set(CMAKE_C_COMPILER   "/usr/bin/clang-3.9")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-3.9")

set(CMAKE_C_FLAGS_DEBUG_INIT   "-fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fsanitize=address -fno-omit-frame-pointer")

if(EXISTS "/source/.clang-tidy")
  set(CMAKE_CXX_CLANG_TIDY "/usr/bin/clang-tidy-3.9" CACHE INTERNAL "" FORCE)
endif()

if(EXISTS "/source/.iwyu.imp")
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE
    "include-what-you-use;-Xiwyu;--mapping_file=/source/.iwyu.imp"
    CACHE INTERNAL "" FORCE)
endif()
