#Set the correct compiler options
IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
   # 32 bit
   MESSAGE(STATUS "Detected that you use a 32 bit processor.")
ELSE(CMAKE_SIZEOF_VOID_P EQUAL 4)
   # 64 bit (well, anything else than 32 bit, but someone use something else than 32 or 64 bit ?)
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
   MESSAGE(STATUS "Detected that you use a 64 bit processor. Added -fPIC to the CXX_FLAGS.")
ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)

include_directories(
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${QT_QTCORE_INCLUDE_DIR} 
    ${QT_QTDBUS_INCLUDE_DIR}
)

set(liburfkill_qt_SRCS
    client.cpp
    device.cpp
    killswitch.cpp
)

set(liburfkill_qt_HDRS 
    urfkill.h 
    enum.h 
    client.h 
    device.h 
    killswitch.h
)

set(liburfkill_qt_MOCS 
    client.h 
    device.h 
    killswitch.h
)

set(GENERIC_LIB_VERSION "0.4.0")
set(GENERIC_LIB_SOVERSION "0")
set(VERSION ${GENERIC_LIB_VERSION})

QT4_WRAP_CPP(MOCS ${liburfkill_qt_MOCS})

add_library(urfkill-qt SHARED ${liburfkill_qt_SRCS} ${MOCS})

target_link_libraries(urfkill-qt ${QT_QTCORE_LIBRARY} ${QT_QTDBUS_LIBRARY})

set_target_properties(urfkill-qt PROPERTIES
    VERSION ${GENERIC_LIB_VERSION}
    SOVERSION ${GENERIC_LIB_SOVERSION}
)

install(TARGETS urfkill-qt DESTINATION ${LIB_INSTALL_DIR})

install(FILES ${liburfkill_qt_HDRS} DESTINATION include/liburfkill-qt)

# install pkgconfig file
if(NOT WIN32)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/urfkill-qt.pc.in ${CMAKE_CURRENT_BINARY_DIR}/urfkill-qt.pc @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/urfkill-qt.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)
endif(NOT WIN32)
