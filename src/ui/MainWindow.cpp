#include "MainWindow.h"
#include "imgui.h"

namespace UI
{
    MainWindow::MainWindow()
        : Window("Main Window") {}

    void MainWindow::onUpdate(float deltaTime) noexcept
    {
        m_frameTime = deltaTime;
    }

    void MainWindow::renderContent()
    {
        ImGui::Text("Frame time: %.3f ms", m_frameTime * 1000.0f);
        ImGui::Text("FPS: %.1f", 1.0f / m_frameTime);

        if (ImGui::Button("Increment Counter"))
        {
            m_counter++;
        }
        ImGui::SameLine();
        ImGui::Text("Counter: %d", m_counter);

        ImGui::Separator();
        ImGui::Text("Window Size: %.0f x %.0f", getSize().x, getSize().y);
        ImGui::Text("Window Position: %.0f, %.0f", getPosition().x, getPosition().y);
    }
}
