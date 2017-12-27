#include "Application.h"
#include "ConfigManager.h"

int main() {
    ConfigManager::instance().load_file("Config/config.yaml");
    Application app;
    app.run_loop();

    return 0;
}

