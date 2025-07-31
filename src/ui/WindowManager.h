#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "Window.h"

namespace UI {
    /// @brief Manages a collection of UI windows.
    /// Provides functionality to create, update, render, and manage visibility of windows.
    class WindowManager final {
    private:
        std::vector<std::unique_ptr<Window>> m_windows;

    public:
        // Non-copyable, movable
        WindowManager() = default;
        ~WindowManager() = default;
        WindowManager(const WindowManager&) = delete;
        WindowManager& operator=(const WindowManager&) = delete;
        WindowManager(WindowManager&&) = default;
        WindowManager& operator=(WindowManager&&) = default;

        template<typename T, typename... Args>
        T* createWindow(Args&&... args) {
            static_assert(std::is_base_of_v<Window, T>, "T must inherit from Window");
            static_assert(std::is_constructible_v<T, Args...>, "T must be constructible with given arguments");

            auto window = std::make_unique<T>(std::forward<Args>(args)...);
            T* ptr = window.get();
            m_windows.push_back(std::move(window));
            return ptr;
        }

        void removeWindow(Window* window) noexcept {
            m_windows.erase(
                std::remove_if(m_windows.begin(), m_windows.end(),
                    [window](const auto& ptr) { return ptr.get() == window; }),
                m_windows.end()
            );
        }

        void updateAll(float deltaTime) const {
            for (auto& window : m_windows) {
                window->update(deltaTime);
            }
        }

        void renderAll() const {
            for (auto& window : m_windows) {
                window->render();
            }
        }

        void setAllVisible(bool visible) const noexcept {
            for (auto& window : m_windows) {
                window->setVisible(visible);
            }
        }

        size_t getWindowCount() const noexcept { return m_windows.size(); }
        
        template<typename T>
        T* findWindow() const {
            for (const auto& window : m_windows) {
                if (auto* typed = dynamic_cast<T*>(window.get())) {
                    return typed;
                }
            }
            return nullptr;
        }
    };
} // namespace UI