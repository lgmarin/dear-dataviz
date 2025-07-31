// filepath: src/ui/test_Window.cpp
#include <catch2/catch_test_macros.hpp>
#include "Window.h"

namespace UI::Test {

// Mock implementation of Window for testing
class TestWindow : public Window {
public:
    explicit TestWindow(const std::string& title) : Window(title) {}

    // Expose protected members for testing
    using Window::m_firstFrame;
    using Window::m_size;
    using Window::m_position;
    
    // Track calls to virtual methods
    int updateCalls = 0;
    int renderContentCalls = 0;
    int showCalls = 0;
    int hideCalls = 0;
    int resizeCalls = 0;
    int moveCalls = 0;
    ImVec2 lastResizeSize{0, 0};
    ImVec2 lastMovePos{0, 0};

protected:
    void onUpdate(float deltaTime) override { updateCalls++; }
    void renderContent() override { renderContentCalls++; }
    void onShow() override { showCalls++; }
    void onHide() override { hideCalls++; }
    void onResize(const ImVec2& newSize) override { 
        resizeCalls++; 
        lastResizeSize = newSize;
    }
    void onMove(const ImVec2& newPosition) override { 
        moveCalls++; 
        lastMovePos = newPosition;
    }
};

TEST_CASE("Window Construction and Basic Properties", "[window]") {
    TestWindow window("Test Window");
    
    SECTION("Initial state") {
        REQUIRE(window.getTitle() == "Test Window");
        REQUIRE(window.isVisible() == true);
        REQUIRE(window.getSize().x == 400);
        REQUIRE(window.getSize().y == 300);
        REQUIRE(window.getPosition().x == 100);
        REQUIRE(window.getPosition().y == 100);
    }
    
    SECTION("Title modification") {
        window.setTitle("New Title");
        REQUIRE(window.getTitle() == "New Title");
    }
}

TEST_CASE("Window Visibility Changes", "[window]") {
    TestWindow window("Test Window");
    
    SECTION("Hide window") {
        window.setVisible(false);
        REQUIRE_FALSE(window.isVisible());
        REQUIRE(window.hideCalls == 1);
    }
    
    SECTION("Show window") {
        window.setVisible(false);
        window.setVisible(true);
        REQUIRE(window.isVisible());
        REQUIRE(window.showCalls == 1);
    }
    
    SECTION("No redundant callbacks") {
        window.setVisible(true); // Already visible
        REQUIRE(window.showCalls == 0);
    }
}

TEST_CASE("Window Size and Position", "[window]") {
    TestWindow window("Test Window");
    
    SECTION("Set size") {
        ImVec2 newSize{500, 400};
        window.setSize(newSize);
        REQUIRE(window.getSize().x == newSize.x);
        REQUIRE(window.getSize().y == newSize.y);
    }
    
    SECTION("Set position") {
        ImVec2 newPos{200, 200};
        window.setPosition(newPos);
        REQUIRE(window.getPosition().x == newPos.x);
        REQUIRE(window.getPosition().y == newPos.y);
    }
}

TEST_CASE("Window Update Lifecycle", "[window]") {
    TestWindow window("Test Window");
    
    SECTION("Update when visible") {
        window.update(1.0f);
        REQUIRE(window.updateCalls == 1);
    }
    
    SECTION("Update when hidden") {
        window.setVisible(false);
        window.update(1.0f);
        REQUIRE(window.updateCalls == 0);
    }
}

} // namespace UI::Test