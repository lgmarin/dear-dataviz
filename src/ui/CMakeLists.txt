add_library(dataviz_ui STATIC
    MainWindow.cpp
)

# Add the ImGui source files to our UI library.
target_sources(dataviz_ui PRIVATE
    ../../libs/imgui/imgui.cpp
    ../../libs/imgui/imgui_draw.cpp
    ../../libs/imgui/imgui_tables.cpp
    ../../libs/imgui/imgui_widgets.cpp
    ../../libs/imgui/backends/imgui_impl_sdl2.cpp
    ../../libs/imgui/backends/imgui_impl_sdlrenderer2.cpp
)

# Make the include directories public so any library linking against
# dataviz_ui gets them automatically.
target_include_directories(dataviz_ui PUBLIC
    . # Allows including "Window.h"
    ../../libs/imgui
    ../../libs/imgui/backends
    ${SDL2_INCLUDE_DIRS}
)

# The UI library needs to link against SDL2
target_link_libraries(dataviz_ui PUBLIC
    SDL2::SDL2
)