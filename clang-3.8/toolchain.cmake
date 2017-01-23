if(EXISTS "/source/.clang-tidy")
  set(CMAKE_CXX_CLANG_TIDY "/usr/bin/clang-tidy-3.8" CACHE INTERNAL "" FORCE)
endif()
