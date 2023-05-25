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


float points[10] = {
                    0.0f, 0.0f,
                    0.0f, 0.75f,
                    0.125f, 1.0f,
                    0.25f, 0.75f,
                    0.25f, 0.0f,
};

float transformed_coords[10] = { 0.0f };
const float kCircunference = 2*PI;
const float kNumberOuterShapes = 4;
float offsetY=0.5, offsetX=13;

void DrawOutShapes(){

    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<4; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Translate(-0.125f, - 1.0f - offsetY), m); //Para poner la x en el medio. La y la bajo hasta la punta de abajo
      m = esat::Mat3Multiply(esat::Mat3Scale(100.0f, 100.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumberOuterShapes)*j + esat::Time() * 0.001), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);
      
      for (int i=0; i<=5; ++i) {
          esat::Vec3 p = { points[i * 2], points[i * 2 + 1], 1.0f };
          esat::Vec3 result = esat::Mat3TransformVec3(m, p);
          transformed_coords[i * 2] = result.x;
          transformed_coords[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255, 255, 255);
      esat::DrawSetFillColor(0, 0, 0);
      esat::DrawSolidPath(transformed_coords, 5);
    }
}

void DrawInShapes(){

    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<4; j++){
      esat::Mat3 m = esat::Mat3Identity();
      m = esat::Mat3Multiply(esat::Mat3Translate(-0.1, 0.5), m);
      m = esat::Mat3Multiply(esat::Mat3Scale(100.0f, 100.0f), m);
      m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / kNumberOuterShapes)*j + 
                            ((kCircunference / kNumberOuterShapes)*0.5f) + esat::Time() * 0.001), m);
      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY), m);
      
      for (int i=0; i<=5; ++i) {
          esat::Vec3 p = { points[i * 2], points[i * 2 + 1], 1.0f };
          esat::Vec3 result = esat::Mat3TransformVec3(m, p);
          transformed_coords[i * 2] = result.x;
          transformed_coords[i * 2 + 1] = result.y;
      }

      esat::DrawSetStrokeColor(255, 255, 255);
      esat::DrawSetFillColor(0, 0, 0);
      esat::DrawSolidPath(transformed_coords, 5);
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
    DrawInShapes();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}