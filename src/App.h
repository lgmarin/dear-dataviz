#pragma once

#include "ui/WindowManager.h"

// Forward declare SDL types to avoid including SDL headers in our header.
struct SDL_Window;
struct SDL_Renderer;

class App final {
public:
    App() = default;
    ~App();

    // Non-copyable, movable
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = default;
    App& operator=(App&&) = default;

    // @brief Initializes the application, setting up SDL and ImGui.
    // @returns Returns 0 on success, non-zero on failure.
    int init();

    void shutdown();

    // @brief Runs the main application loop.
    void run();

private:
    void processEvents();
    void renderUI();
    void shutdownImGui();
    void shutdownSDL();
    void setupRendererBackend();
    void setContextConfig();

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_isRunning = true;

    UI::WindowManager m_windowManager;
};