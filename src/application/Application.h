#pragma once

#include "../ui/WindowManager.h"

// Forward declare SDL types to avoid including SDL headers in our header.
struct SDL_Window;
struct SDL_Renderer;

class Application final {
public:
    Application() = default;
    ~Application();

    // Non-copyable, movable
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = default;
    Application& operator=(Application&&) = default;

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