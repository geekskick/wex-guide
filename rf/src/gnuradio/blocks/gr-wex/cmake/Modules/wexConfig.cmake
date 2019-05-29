INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_WEX wex)

FIND_PATH(
    WEX_INCLUDE_DIRS
    NAMES wex/api.h
    HINTS $ENV{WEX_DIR}/include
        ${PC_WEX_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    WEX_LIBRARIES
    NAMES gnuradio-wex
    HINTS $ENV{WEX_DIR}/lib
        ${PC_WEX_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(WEX DEFAULT_MSG WEX_LIBRARIES WEX_INCLUDE_DIRS)
MARK_AS_ADVANCED(WEX_LIBRARIES WEX_INCLUDE_DIRS)

