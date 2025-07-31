#pragma once

#include "Window.h"
#include <vector>
#include <memory>

namespace UI {
    class MainWindow final : public Window {
    private:
        float m_frameTime = 0.0f;
        int m_counter = 0;

    public:
        MainWindow();

    protected:
        void onUpdate(float deltaTime) noexcept override;
        void renderContent() override;
    };
}