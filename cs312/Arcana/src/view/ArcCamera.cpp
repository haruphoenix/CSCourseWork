#include "ArcCamera.h"
#include <math.h>
#include <iostream> // debugging

ArcCamera::ArcCamera()
{
  initCamera();
  mMidX = 400;
  mMidY = 300;
 
}

ArcMatrix ArcCamera::getMatrix(void)
{
  mView = IDENTITY_MATRIX;
  TranslateMatrix(&mView, -mPosition.x, -mPosition.y, -mPosition.z);
  RotateAboutY(&mView, DegreesToRadians(mRotation.y));
  RotateAboutX(&mView, DegreesToRadians(mRotation.x));
  RotateAboutZ(&mView, DegreesToRadians(mRotation.z));
  return mView;
}

ArcCamera::ArcCamera(int width, int height)
{
  initCamera();

  mMidX = width  / 2;
  mMidY = height / 2;
}

ArcCamera::~ArcCamera()
{
}


void ArcCamera::setPosition(float x, float y, float z)
{
  mPosition.x = x;
  mPosition.y = y;
  mPosition.z = z;
}

void ArcCamera::setRotation(float x, float y, float z)
{
  mRotation.x = x;
  mRotation.y = y;
  mRotation.z = z;
}

void ArcCamera::initCamera()
{
  zero(mPosition);
  zero(mRotation);
  zero(mSpeed);

  // How fast camera moves (Higher = faster)
  mMovementSpeedFactor = 1.0;//100.0;
  
  mPitchSensitivity = 0.2; // up down
  mYawSensitivity   = 0.2; // left right

  // Not holding any keys
  Forward  = false;
  Backward = false;
  Left     = false;
  Right    = false;
}

void ArcCamera::setScreen(int width, int height)
{
  mMidX = width / 2;
  mMidY = height / 2;
}

void ArcCamera::changeDirection(int mouseX, int mouseY)
{
  float horizMovement = (mouseX - mMidX + 1) * mYawSensitivity;
  float vertMovement  = (mouseY - mMidY) * mPitchSensitivity;

  mRotation.y += horizMovement;
  mRotation.x -= vertMovement;

  // Limit looking up and down
  if (mRotation.x < -90) mRotation.x  = -90;
  if (mRotation.x >  90) mRotation.x  =  90;
  // Revolve around
  if (mRotation.y <   0) mRotation.y += 360;
  if (mRotation.y > 360) mRotation.y -= 360;

}

void ArcCamera::move()
{
  move(2);
}

void ArcCamera::move(float time)
{
  // Breaks up movement into components x, y, & z
  ArcVector movement;
  zero(movement);

  float sinXRot = (float)sin(DegreesToRadians(mRotation.x));
  float cosXRot = (float)cos(DegreesToRadians(mRotation.x));
  float sinYRot = (float)sin(DegreesToRadians(mRotation.y));
  float cosYRot = (float)cos(DegreesToRadians(mRotation.y));

  // Stops movement when looking up or down
  float pitchLimitFactor = cosXRot;

  if (Forward)
  {
    movement.x += (sinYRot * pitchLimitFactor);
    movement.y -= (-sinXRot);
    movement.z += (-cosYRot * pitchLimitFactor);
  }

  if (Backward)
  {
    movement.x += (-sinYRot * pitchLimitFactor);
    movement.y -= sinXRot;
    movement.z += (cosYRot * pitchLimitFactor);
  }

  if (Left)
  {
    movement.x += -cosYRot;
    movement.z += -sinYRot;
  }

  if (Right)
  {
    movement.x += cosYRot;
    movement.z += sinYRot;
  }

  normalize(movement);

  // Calculate to keep movement same speed no matter frame rate
  float framerateIndependentFactor = mMovementSpeedFactor * time;

  // Apply to movement vector
  movement *= framerateIndependentFactor;

  mPosition += movement;

}

