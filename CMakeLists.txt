cmake_minimum_required(VERSION 3.5)

project(numbers_storage LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Sql REQUIRED)
find_package(Boost 1.65 COMPONENTS system unit_test_framework REQUIRED)

set(HEADERS
    inc/EntriesModel.h
    inc/Entry.h
    inc/Entries.h
    inc/EntriesRef.h
    inc/DBManager.h
    inc/ModelManager.h
    inc/generate.h
    inc/Validate.h
)
set(SOURCES
    src/EntriesModel.cpp
    src/Entry.cpp
    src/Entries.cpp
    src/EntriesRef.cpp
    src/DBManager.cpp
    src/ModelManager.cpp
    src/generate.cpp
    src/Validate.cpp
)

include_directories(inc)
include_directories ( ${Boost_INCLUDE_DIRS} )

add_executable(numbers_storage
        main.cpp
        qml.qrc
        ${HEADERS}
        ${SOURCES}
)

target_link_libraries(numbers_storage
  PRIVATE Qt5::Core Qt5::Quick Qt5::Sql)

enable_testing()

add_executable(entries_test
    test/all_unit_tests.cpp
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(entries_test
        Qt5::Core Qt5::Quick Qt5::Sql ${Boost_LIBRARIES})

add_test(NAME Entries_test COMMAND entries_test)
