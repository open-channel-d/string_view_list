set(SRC test.cpp)
set(TEST_NAME sv_list_test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(../include)

add_executable(${TEST_NAME} ${SRC})

set_target_properties(${TEST_NAME} PROPERTIES
   CXX_STANDARD 17
   CXX_EXTENSIONS OFF
)

target_link_libraries(${TEST_NAME} sv_list ${Boost_LIBRARIES})

add_test(${TEST_NAME} ${TEST_NAME})