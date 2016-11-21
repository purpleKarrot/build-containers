#

find_package(PkgConfig QUIET)
include(CMakeFindDependencyMacro)

foreach(cmp ${Qt5_FIND_COMPONENTS})
  find_dependency(Qt5${cmp})
  pkg_check_modules(PC_Qt5_${cmp} QUIET Qt5${cmp})
  set_property(TARGET Qt5::${cmp}
    APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${PC_Qt5_${cmp}_STATIC_LDFLAGS})
  set(Qt5Core_QMAKE_EXECUTABLE "/usr/local/bin/qmake")
  set(Qt5Core_MOC_EXECUTABLE "/usr/local/bin/moc")
  set(Qt5Core_RCC_EXECUTABLE "/usr/local/bin/rcc")
  set(Qt5DBus_QDBUSCPP2XML_EXECUTABLE "/usr/local/bin/qdbuscpp2xml")
  set(Qt5DBus_QDBUSXML2CPP_EXECUTABLE "/usr/local/bin/qdbusxml2cpp")
endforeach()
