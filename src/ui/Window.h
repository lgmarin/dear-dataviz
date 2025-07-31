#pragma once

#include <imgui.h>
#include <string>

namespace UI {
    /// @brief Base class for all UI windows.
    /// Provides a framework for creating windows with ImGui, handling visibility, size, position,
    /// and rendering content.
    class Window {
    protected:
        std::string m_title;
        bool m_visible = true;
        bool m_firstFrame = true;
        ImGuiWindowFlags m_flags = ImGuiWindowFlags_None;
        ImVec2 m_size = {400, 300};
        ImVec2 m_position = {100, 100};
        ImVec2 m_lastSize = {0, 0};
        ImVec2 m_lastPosition = {0, 0};

    public:
        explicit Window(std::string title, ImGuiWindowFlags flags = ImGuiWindowFlags_None)
            : m_title(std::move(title)), m_flags(flags) {}
        
        virtual ~Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = default;
        Window& operator=(Window&&) = default;

        /// @brief Updates the window state. Called every frame.
        /// @param deltaTime Time since the last update in seconds.
        void update(float deltaTime) {
            if (!m_visible) return;
            
            // Pre-update hook (can be overridden)
            onPreUpdate(deltaTime);
            
            // Main update logic (can be overridden)
            onUpdate(deltaTime);
            
            // Post-update hook (can be overridden)
            onPostUpdate(deltaTime);
        }

        /// @brief Renders the window content. Called every frame.
        /// This method handles the ImGui Begin/End calls and checks for visibility changes.
        void render() {
            if (!m_visible) return;

            // Set initial window properties on first frame
            if (m_firstFrame) {
                ImGui::SetNextWindowSize(m_size, ImGuiCond_FirstUseEver);
                ImGui::SetNextWindowPos(m_position, ImGuiCond_FirstUseEver);
                m_firstFrame = false;
            }

            // Begin window
            bool wasVisible = m_visible;
            if (ImGui::Begin(m_title.c_str(), &m_visible, m_flags)) {
                // Check for size/position changes
                checkForChanges();
                
                // Pre-render hook (can be overridden)
                onPreRender();
                
                // Render content (must be implemented by derived classes)
                renderContent();
                
                // Post-render hook (can be overridden)
                onPostRender();
            }
            ImGui::End();

            // Handle visibility change
            if (wasVisible && !m_visible) {
                onHide();
            } else if (!wasVisible && m_visible) {
                onShow();
            }
        }

        virtual bool isVisible() const noexcept { return m_visible; }
        virtual const std::string& getTitle() const noexcept { return m_title; }
        virtual ImVec2 getSize() const noexcept { return m_size; }
        virtual ImVec2 getPosition() const noexcept { return m_position; }

        virtual void setVisible(bool visible) noexcept {
            if (m_visible != visible) {
                m_visible = visible;
                if (visible) onShow();
                else onHide();
            }
        }
        virtual void setTitle(const std::string_view title) { m_title = title; }
        virtual void setSize(const ImVec2& size) noexcept { m_size = size; }
        virtual void setPosition(const ImVec2& position) noexcept { m_position = position; }

    protected:
        // Virtual hooks that derived classes can override as needed
        virtual void onPreUpdate(float deltaTime) {}
        virtual void onUpdate(float deltaTime) {}
        virtual void onPostUpdate(float deltaTime) {}
        
        virtual void onPreRender() {}
        virtual void onPostRender() {}

        /// @brief Renders the content of the window.
        /// This method must be implemented by derived classes to define what content is displayed in the window
        virtual void renderContent() = 0;
        
        // Event hooks (can be overridden)
        virtual void onShow() {}
        virtual void onHide() {}
        virtual void onClose() {}
        virtual void onResize(const ImVec2& newSize) {}
        virtual void onMove(const ImVec2& newPosition) {}

    private:
        void checkForChanges() noexcept {
            ImVec2 currentSize = ImGui::GetWindowSize();
            ImVec2 currentPos = ImGui::GetWindowPos();
            
            if (currentSize.x != m_lastSize.x || currentSize.y != m_lastSize.y) {
                m_size = currentSize;
                onResize(currentSize);
                m_lastSize = currentSize;
            }
            
            if (currentPos.x != m_lastPosition.x || currentPos.y != m_lastPosition.y) {
                m_position = currentPos;
                onMove(currentPos);
                m_lastPosition = currentPos;
            }
        }
    };
}