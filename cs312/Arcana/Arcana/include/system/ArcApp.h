#include "ArcTimer.h"
#include "ArcWindow.h"
#include "ArcEngine.h"
#include "ArcController.h"
#include "ArcModel.h"

#ifndef ARC_APP_H
#define ARC_APP_H

class ArcApp
{
public:

  static ArcApp& getInstance();
  static bool initialize();
  static void start();
  static void destroy();
  static ArcWindow& getWindow();
  static ArcEngine& getEngine();
  static ArcModel& getModel();

  ~ArcApp();

private:

  ArcApp();
  ArcApp(ArcApp const&);
  void operator=(ArcApp const&);

  static ArcWindow mWindow;
  static ArcEngine mEngine;
  static ArcTimer      mTimer;
  static ArcController mController;
  static ArcModel      mModel;
};

#endif
