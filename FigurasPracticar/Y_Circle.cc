#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>
#include <esat/window.h>

#define PI 3.14159265

double current_time,last_time;
unsigned char fps=60;
float mPosX;
float mPosY;

const int kNpoints = 9;
const int kNpointsCircle = 8;
const int kNumFigures = 8;
const float kCircunference= PI*2;

float circle_coords[kNpointsCircle * 2] = {0.0f};
float transformed_coords[kNpoints * 2] = {0.0f};
float transformed_coords_circle[kNpointsCircle * 2] = {0.0f};

float figure[] = {
1.0f, 0.0f,
1.0f, 3.0f,
3.0f, 7.0f,
1.0f, 7.0f,
0.0f, 5.0f,
-1.0f, 7.0f,
-3.0f, 7.0f,
-1.0f, 3.0f,
-1.0f, 0.0f };

void DrawInFigures(){

  for(int j=0; j<kNumFigures; j++){

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(10.0f, 10.0f ),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumFigures)* -j),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

    for(int i=0; i<kNpoints; i++){
      esat::Vec3 p = {figure[i * 2], figure[i * 2 + 1], 1.0f};
      esat::Vec3 result = Mat3TransformVec3(m,p);
      transformed_coords[i * 2] = result.x;
      transformed_coords[i * 2 + 1] = result.y;
    }

    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSolidPath(transformed_coords, kNpoints);
  }
}

void DrawOutFigures(){

  for(int j=0; j<kNumFigures; j++){

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, 12.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Scale(10.0f, 10.0f ),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumFigures)* -j),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

    for(int i=0; i<kNpoints; i++){
      esat::Vec3 p = {figure[i * 2], figure[i * 2 + 1], 1.0f};
      esat::Vec3 result = Mat3TransformVec3(m,p);
      transformed_coords[i * 2] = result.x;
      transformed_coords[i * 2 + 1] = result.y;
    }

    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSolidPath(transformed_coords, kNpoints);
  }
}

void InitCircle(){

  float portion = kCircunference / kNpointsCircle;
  for(int i=0; i<kNpointsCircle; i++){
      circle_coords[i * 2] = cos(portion * i);
      circle_coords[i * 2 + 1] = sin(portion * i);
  }
}

void DrawCircle(){

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(120.0f, 120.0f ),m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(0.0f),m);
    m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

    for(int i=0; i<kNpointsCircle; i++){
      esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f};
      esat::Vec3 result = Mat3TransformVec3(m,p);
      transformed_coords_circle[i * 2] = result.x;
      transformed_coords_circle[i * 2 + 1] = result.y;
    }

    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSolidPath(transformed_coords_circle, kNpointsCircle);
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

  InitCircle();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    mPosX = esat::MousePositionX();
    mPosY = esat::MousePositionY();

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawInFigures();
    DrawCircle();
    DrawOutFigures();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}