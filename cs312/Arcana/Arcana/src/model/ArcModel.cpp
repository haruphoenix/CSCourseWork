#include "ArcModel.h"
#include "ArcApp.h"
#include "ArcTerrain.h"
#include <list>
#include "ArcMath.h"
#include "ArcVertexData.h"
#include <iostream>
#include <fstream>

ArcModel::ArcModel()
{
  
  
}

/*
void ArcModel::loadScene(const char* filename)
{
  std::ifstream fin;
  list<char*> files;
  fin.open(filename);
  if (fin.fail()) return;
  char* objectFile;
  while (fin >> objectFile)
  {
    
  }
  fin.close();
}
*/

void ArcModel::loadObjects()
{
  //std::cout << "Loading Objects\n";
    ArcVertexData oceanData0;
    ArcVertexData oceanData1;
    ArcVertexData oceanData2;
    ArcVertexData oceanData3;

    oceanData0.loadData("src/model/objects/seaLevel.od");
    oceanData1.loadData("src/model/objects/seaLevel.od");
    oceanData2.loadData("src/model/objects/seaLevel.od");
    oceanData3.loadData("src/model/objects/seaLevel.od");

    oceanData0.setPosition(-128, 0, -128);
    oceanData1.setPosition(-128, 0, 128);
    oceanData2.setPosition(128, 0, -128);
    oceanData3.setPosition(128, 0, 128);
    //oceanData0.setRotation(45, 0, 0);
    //oceanData1.setRotation(0, 0, -45);
    //oceanData2.setRotation(0, 0, 45);
    //oceanData3.setRotation(-45, 0, 0);
  
  
    
    //ArcVertexData terrainData;// = terrain.getVertexData();
    //terrainData.loadData("src/model/objects/terrain0.od");
    //terrainData.setPosition(0, -10, 0);
    

    registerData(oceanData0);
    //registerData(terrainData);
    registerData(oceanData1);
    registerData(oceanData2);
    registerData(oceanData3);

    //ArcTerrain terrain1(8, 7);
    //ArcTerrain terrain2(8, 7);
    //ArcTerrain terrain3(8, 7);
    //terrain1.generate();
    //terrain2.generate();
    //terrain3.generate();
    //ArcTerrain terrain0(8, 7);
    //terrain0.generate();
    ArcVertexData terrainData0;// = terrain0.getVertexData();
    terrainData0.loadData("src/model/objects/terrain10.od");
    terrainData0.setPosition(0, 2, 0);
    registerData(terrainData0);
    //ArcVertexData terrainData1 = terrain1.getVertexData();
    //ArcVertexData terrainData2 = terrain2.getVertexData();
    //ArcVertexData terrainData3 = terrain3.getVertexData();
    //terrainData0.setPosition(-128, 0, -128);
    //terrainData1.setPosition(-128, 0, 128);
    //terrainData2.setPosition(128, 0, -128);
    //terrainData3.setPosition(128, 0, 128);
    //registerData(terrainData1);
    //registerData(terrainData2);
    //registerData(terrainData3);

    //terrainData0.exportData("src/model/objects/terrain10.od");
  //registerData(terrainData);
}

void ArcModel::initialize()
{
  ArcApp::getInstance().getEngine().
    getCamera().setPosition(0, 20, 0);
}

void ArcModel::registerData(ArcVertexData data)
{
  data.formArrays();
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
