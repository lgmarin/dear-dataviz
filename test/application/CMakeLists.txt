add_executable(app_tests
    application_tests.cpp
)

# Link against the App library and Catch2
target_link_libraries(app_tests PRIVATE
    dataviz_app
    Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(app_tests)