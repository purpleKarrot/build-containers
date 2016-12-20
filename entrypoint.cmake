set(CTEST_RUN_CURRENT_SCRIPT 0)

set(BUILD_MODEL "Experimental")

if(EXISTS "/toolchain.cmake")
  set(toolchain_arg ";-DCMAKE_TOOLCHAIN_FILE:FILEPATH=/toolchain.cmake")
endif()

include(ProcessorCount)
ProcessorCount(nproc)
if(NOT nproc EQUAL 0)
  set(TEST_ARGS "PARALLEL_LEVEL ${nproc}")
endif()

if(NOT BUILD_CONFIGURATIONS)
  message(FATAL_ERROR "Nothing to build!")
endif()

foreach(config ${BUILD_CONFIGURATIONS})
  set(BUILD_CONFIG "${config}")
  set(CONFIGURE_ARGS "OPTIONS \"-DCMAKE_BUILD_TYPE:STRING=${config}${toolchain_arg}\"")
  configure_file("/build.cmake" "/binary/build-${config}.cmake" @ONLY)
  list(APPEND _run_scripts "/binary/build-${config}.cmake")
  list(APPEND _install_projects "/binary/${config};\${CPACK_PACKAGE_NAME};ALL;/")
endforeach()

list(GET BUILD_CONFIGURATIONS 0 _first_config)
file(WRITE "/binary/CPackConfig.cmake"
  "include(\"/binary/${_first_config}/CPackConfig.cmake\")\n"
  "set(CPACK_INSTALL_CMAKE_PROJECTS \"${_install_projects}\")\n"
  )

ctest_run_script(${_run_scripts})

execute_process(COMMAND cpack --config ./CPackConfig.cmake
  WORKING_DIRECTORY "/binary"
  )
