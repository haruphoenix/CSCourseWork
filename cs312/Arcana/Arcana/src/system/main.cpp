#include "ArcApp.h"

int main(int argc, char** argv)
{

  if (ArcApp::getInstance().initialize() == false) return 1;
  ArcApp::getInstance().start();

  return 0;
}
