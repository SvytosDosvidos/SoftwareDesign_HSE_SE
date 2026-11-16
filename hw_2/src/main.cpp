#include "bootstrap/application_container.h"

int main() {
    ApplicationContainer container;
    auto consoleApp = container.console();
    consoleApp->run();

    return 0;
}
