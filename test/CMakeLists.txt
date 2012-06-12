include_directories(
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${QT_QTCORE_INCLUDE_DIR} 
    ${QT_QTDBUS_INCLUDE_DIR} 
)

set(test_SRCS
    main.cpp
    test.cpp
)

set(test_HDRS 
    test.h
)

set(test_MOCS 
    test.h
)

QT4_WRAP_CPP(MOCS ${test_MOCS})

add_executable(test ${test_SRCS} ${MOCS})

target_link_libraries(test
    ${QT_QTCORE_LIBRARY} 
    ${QT_QTDBUS_LIBRARY} 
    urfkill-qt
)

#install(TARGETS test RUNTIME DESTINATION bin)
