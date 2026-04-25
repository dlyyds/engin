#pragma once

#include "Application.h"
#include "Log.h"

#ifdef _WIN64

extern GE::Application *GE::CreateApplication();

int main(int argc, char **argv) {

    GE::Log::Init();
    // GE::Log::GetCoreLogger()->warn("Initialized log");
    // GE::Log::GetClientLogger()->info("Hello");

    auto app = GE::CreateApplication();
    app->Run();
    delete app;
}

#endif