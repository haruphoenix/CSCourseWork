#include "ArcModel.h"
#include "ArcApp.h"
#include "ArcTerrain.h"
#include <list>
#include "ArcMath.h"
#include "ArcVertexData.h"
#include <iostream>

ArcModel::ArcModel()
{
  
  
}

void ArcModel::loadObjects()
{
  std::cout << "Loading Objects\n";
  ArcVertexData oceanData;
  oceanData.loadData("src/model/objects/seaLevel.od");
  //ArcTerrain terrain(8, 7);
  //terrain.generate();
  ArcVertexData terrainData;// = terrain.getVertexData();
  //terrainData.exportData("src/model/objects/terrain1.od");
  terrainData.loadData("src/model/objects/terrain1.od");
  registerData(terrainData);
  registerData(oceanData);
}

void ArcModel::initialize()
{
  ArcApp::getInstance().getEngine().
    getCamera().setPosition(0, 20, 0);
}

void ArcModel::registerData(ArcVertexData data)
{
  mData.push_back(data);
}


std::list<ArcVertexData> ArcModel::getData()
{
  return mData;
}

void ArcModel::stopLeft()
{
  ArcApp::getInstance().getEngine().getCamera().Left = false;
}

void ArcModel::stopRight()
{
  ArcApp::getInstance().getEngine().getCamera().Right = false;
}

void ArcModel::stopBackward()
{
  ArcApp::getInstance().getEngine().getCamera().Backward = false;
}

void ArcModel::stopForward()
{
  ArcApp::getInstance().getEngine().getCamera().Forward = false;
}

void ArcModel::moveForward()
{
  ArcApp::getInstance().getEngine().getCamera().Forward = true;
}

void ArcModel::moveBackward()
{
  ArcApp::getInstance().getEngine().getCamera().Backward = true;
}

void ArcModel::moveRight()
{
  ArcApp::getInstance().getEngine().getCamera().Right = true;
}

void ArcModel::moveLeft()
{
  ArcApp::getInstance().getEngine().getCamera().Left = true;
}
