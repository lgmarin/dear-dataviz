# Create the executable from our main.cpp
add_executable(dear_dataviz 
    main.cpp
    Application.cpp
    ui/MainWindow.cpp)

# --- Integrate Dear ImGui ---
# This is the correct way to add the ImGui source files to our executable.
target_sources(dear_dataviz PRIVATE
    ../libs/imgui/imgui.cpp
    ../libs/imgui/imgui_draw.cpp
    ../libs/imgui/imgui_tables.cpp
    ../libs/imgui/imgui_widgets.cpp
    ../libs/imgui/backends/imgui_impl_sdl2.cpp
    ../libs/imgui/backends/imgui_impl_sdlrenderer2.cpp
)

# Tell the compiler where to find the ImGui and SDL2 header files.
target_include_directories(dear_dataviz PRIVATE
    ../libs/imgui
    ../libs/imgui/backends
    .
    ${SDL2_INCLUDE_DIRS}
)

# Link our final executable against the SDL2 library.
target_link_libraries(dear_dataviz PRIVATE
    SDL2::SDL2
)