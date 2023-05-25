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

float points[14] = {0.0f, 4.0f,
                    -4.0f, - 8.0f,
                    -7.0f, - 8.0f,
                    0.0f, 10.0f,
                    7.0f, - 8.0f,
                    4.0f, - 8.0f,
                    0.0f, 4.0f};

float transformed_coords[14 * 2] = { 0.0f };
const float kCircunference = 2*PI;
const float kNumberOuterShapes = 12;
const float kNumberInnerShapes = 6;
float offsetY=0, offsetX=0, radius=140, radius2=70;

void DrawOutShapes(){

    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<12; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, 30.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumberOuterShapes)*-j), m);
      m = esat::Mat3Multiply(esat::Mat3Scale(5.0f, 5.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

      //offsetX = radius * (sin(j * kCircunference/kNumberOuterShapes));
      //offsetY = radius * (cos(j * kCircunference/kNumberOuterShapes));
      //m = esat::Mat3Multiply(esat::Mat3Translate(offsetX, offsetY), m);
      
      for (int i=0; i<=7; ++i) {
          esat::Vec3 p = { points[i * 2], points[i * 2 + 1], 1.0f };
          esat::Vec3 result = esat::Mat3TransformVec3(m, p);
          transformed_coords[i * 2] = result.x;
          transformed_coords[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255, 255, 255, 255);
      esat::DrawSetFillColor(0, 0, 0, 0);
      esat::DrawSolidPath(transformed_coords, 7, true);


    }
}

void DrawInsideShapes() {
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for (int j = 0; j < 6; j++) {

      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, -30.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Scale(2.0f, 2.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumberInnerShapes)*-j), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);

      //offsetX = radius2 * (sin(j * kCircunference / kNumberInnerShapes));
      //offsetY = radius2 * (cos(j * kCircunference / kNumberInnerShapes));
      //m = esat::Mat3Multiply(esat::Mat3Translate(offsetX, offsetY), m);
      
      for (int i = 0; i <= 7; ++i) {
          esat::Vec3 p = { points[i * 2], points[i * 2 + 1], 1.0f };
          esat::Vec3 result = esat::Mat3TransformVec3(m, p);
          transformed_coords[i * 2] = result.x;
          transformed_coords[i * 2 + 1] = result.y;
      }
    
      esat::DrawSetStrokeColor(255, 255, 255, 255);
      esat::DrawSetFillColor(0, 0, 0, 0);
      esat::DrawSolidPath(transformed_coords, 7, true);

    }
}






int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawOutShapes();
    DrawInsideShapes();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}