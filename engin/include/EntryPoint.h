#pragma once

#include <GE.h>
#ifdef _WIN64

extern GE::Application *GE::CreateApplication();

int main(int argc, char **argv) {
  GE::Log::Init();

  auto app = GE::CreateApplication();
  app->Run();
  delete app;
}

#endif