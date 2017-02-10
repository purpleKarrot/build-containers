set(CTEST_RUN_CURRENT_SCRIPT 0)

set(BUILD_MODEL "$ENV{BUILD_MODEL}")
set(CTEST_CHANGE_ID "$ENV{CHANGE_ID}")

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

set(prefix_arg ";-DCMAKE_INSTALL_PREFIX:PATH=/prefix")

foreach(config ${BUILD_CONFIGURATIONS})
  set(BUILD_CONFIG "${config}")
  set(config_arg "-DCMAKE_BUILD_TYPE:STRING=${config}")
  set(CONFIGURE_ARGS "OPTIONS \"${config_arg}${prefix_arg}${toolchain_arg}\"")
  configure_file("/build.cmake" "/binary/build-${config}.cmake" @ONLY)
  list(APPEND _run_scripts "/binary/build-${config}.cmake")
  list(APPEND _install_projects "/binary/${config};\${CPACK_PACKAGE_NAME};ALL;/")
endforeach()

ctest_run_script(${_run_scripts} RETURN_VALUE ret)
if(NOT ret EQUAL 0)
  message(FATAL_ERROR "Failed to run build script.")
endif()

if(BUILD_PACKAGES)
  list(GET BUILD_CONFIGURATIONS 0 _first_config)
  file(WRITE "/binary/CPackConfig.cmake"
    "include(\"/binary/${_first_config}/CPackConfig.cmake\")\n"
    "set(CPACK_INSTALL_CMAKE_PROJECTS \"${_install_projects}\")\n"
    )
  execute_process(COMMAND cpack --config ./CPackConfig.cmake
    WORKING_DIRECTORY "/binary"
    RESULT_VARIABLE ret
    )
  if(NOT ret EQUAL 0)
    message(FATAL_ERROR "Failed to create package.")
  endif()
endif()
