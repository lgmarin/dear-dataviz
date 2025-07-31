add_library(dataviz_app STATIC
    Application.cpp
)

# Make the include directory public.
target_include_directories(dataviz_app PUBLIC
    . # Allows including "App.h"
)

# The application logic depends on the UI library.
target_link_libraries(dataviz_app PUBLIC
    dataviz_ui
)
