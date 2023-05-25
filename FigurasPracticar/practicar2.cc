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

const int kNumPoints = 5;
const int kNumFigures = 4;
float kCircunference = 2*PI;
float transformed_coords[2 * kNumPoints] = {0.0f};

float points[10] = {
0.0f, 0.0f,
0.0f, 0.75f,
0.125f, 1.0f,
0.25f, 0.75f,
0.25f, 0.0f,
};

void DrawShapes1(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCircunference / kNumFigures;
    for(int j=0; j<kNumFigures; j++){

        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Translate(-0.1f, 1.0f),m);
        m = esat::Mat3Multiply(esat::Mat3Scale(90.0f, 90.0f),m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j),m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001),m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

        for(int i=0; i<kNumPoints; i++){
            esat::Vec3 p = {points[i * 2], points[i * 2 + 1], 1.0f};
            esat::Vec3 result = esat::Mat3TransformVec3(m,p);
            transformed_coords[i * 2] = result.x;
            transformed_coords[i * 2 + 1] = result.y;
        }
        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSetFillColor(0,0,0,0);
        esat::DrawSolidPath(transformed_coords, kNumPoints);
    }
}

void DrawShapes2(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCircunference / 4;
    for(int j=0; j<4; j++){

        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, -2.2f),m);
        m = esat::Mat3Multiply(esat::Mat3Scale(90.0f, 90.0f),m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(0.8f),m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j),m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001),m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

        for(int i=0; i<kNumPoints; i++){
            esat::Vec3 p = {points[i * 2], points[i * 2 + 1], 1.0f};
            esat::Vec3 result = esat::Mat3TransformVec3(m,p);
            transformed_coords[i * 2] = result.x;
            transformed_coords[i * 2 + 1] = result.y;
        }
        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSetFillColor(0,0,0,0);
        esat::DrawSolidPath(transformed_coords, kNumPoints);
    }
}






int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawShapes1();
    DrawShapes2();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}