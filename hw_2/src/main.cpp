#include "../include/console_app.h"

#include<memory>

int main() {
    std::unique_ptr<ConsoleApp> consoleApp = std::make_unique<ConsoleApp>();
    consoleApp->run();

    return 0;
}