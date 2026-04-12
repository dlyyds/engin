
#include "EntryPoint.h"
#include "GE.h"
#include <iostream>

class Sandbox : public GE::Application {
public:
  Sandbox() {}
  ~Sandbox() {}
};

GE::Application *GE::CreateApplication() { return new Sandbox(); }
