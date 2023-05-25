#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "esat/window.h"
#include "esat/draw.h"
#include "esat/input.h"
#include "esat/sprite.h"
#include "esat/time.h"

//#include "..\smf\smfLibrary.h"

#define PI 3.14159265

double current_time,last_time;
unsigned char fps=60;

const int kNPoints=5;
esat::Vec3 g_circle[kNPoints];
esat::Vec2 tr_points[kNPoints];

esat::Vec2 mouseToCenter;
esat::Vec2 mouseToVertex;

float centerX = 400.0f;
float centerY = 300.0f;

int dotProduct=0;

void InitCircle(){

    float radians_between_vertices = 6.28f / (float) kNPoints; //2*pi = 6.28

    for (int i=0; i<kNPoints; ++i){

       g_circle[i] = { (float) cos(radians_between_vertices * i ),
                       (float) sin(radians_between_vertices * i ),
                        1.0f };
    }
}

void DrawCircle(esat::Mat3 m){

  for (int i=0; i<kNPoints; i++){
    esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_circle[i]);
    tr_points[i] = {tmp.x, tmp.y};
  }

  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_points[0].x, kNPoints);

  //for(int i=0; i<kNPoints; i++){
  //  printf("%f %f\n", tr_points[i].x, tr_points[i].y);
  //}
  //printf("\n");
}

esat::Mat3 UpdateBase(){
  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(80.0f, 80.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(6.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(centerX, centerY), m);

  return m;
}

void Collision(){
  float mPosx = esat::MousePositionX();
  float mPosY = esat::MousePositionY();
  
  mouseToCenter.x = mPosx - centerX;
  mouseToCenter.y = mPosY - centerY;

  for(int i=0; i<kNPoints; i++){
    mouseToVertex.x = tr_points[i].x - mPosx;
    mouseToVertex.y = tr_points[i].y - mPosY;

    dotProduct = (mouseToVertex.x * mouseToCenter.x) + (mouseToVertex.y * mouseToCenter.y);

    if(esat::MouseButtonDown(0)){
      printf("%d\n", dotProduct);
    }
  }
  
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  esat::WindowSetMouseVisibility(true);
  
  InitCircle();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);

    esat::Mat3 base = UpdateBase();
    DrawCircle(base);
    Collision();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}