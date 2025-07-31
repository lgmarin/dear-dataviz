add_executable(ui_tests
    window_test.cpp
)

# Link against the UI library and Catch2
target_link_libraries(ui_tests PRIVATE
    dataviz_ui
    Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(ui_tests)