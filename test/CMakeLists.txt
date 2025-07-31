# Create the test executable
add_executable(unit_tests main.cpp simple_test.cpp)

# Link against Catch2's main library
target_link_libraries(unit_tests PRIVATE
    Catch2::Catch2WithMain
)

# Add the tests to CTest for easy running
include(Catch)
catch_discover_tests(unit_tests)