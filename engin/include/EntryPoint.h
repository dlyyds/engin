#pragma once

#include "Application.h"
#ifdef _WIN64

extern GE::Application *GE::CreateApplication();

int main(int argc, char **argv) {
  auto app = GE::CreateApplication();
  app->Run();
  delete app;
}

#endif