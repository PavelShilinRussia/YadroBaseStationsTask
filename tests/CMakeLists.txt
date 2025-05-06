include(FetchContent)

FetchContent_Declare( googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.12.1 )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(ClubTimeTests
        ClubTimeTests.cpp
        ../src/ClubTime.cpp
)

target_include_directories(ClubTimeTests PRIVATE ../include)

target_link_libraries(ClubTimeTests PRIVATE gtest gtest_main)

add_test(NAME ClubTimeTests COMMAND ClubTimeTests)