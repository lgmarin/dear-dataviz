#include <iostream>
#include <memory>

#include "application/Application.h"

int main(int argc, char* argv[]) {
    auto app = std::make_unique<Application>();

    if (app->init() != 0) {
        return 1;
    }

    app->run();

    return 0;
}
