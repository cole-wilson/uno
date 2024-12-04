#include "GraphicsMain.h"
#include "TestCases.h"

int main() {
    // Test Cases:
    // TestCases tests;
    // tests.runAll();

    // run the main graphics thread
    GraphicsMain graphics_main;
    graphics_main.run();

    return 0;
}