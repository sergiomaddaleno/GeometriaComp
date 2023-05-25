#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>
#include <conio.h>

//#include "..\smf\smfLibrary.h"

#define PI 3.14159265

double current_time,last_time;
unsigned char fps=60;

const int kNPoints=5;
esat::Vec3 g_circle[kNPoints];

void InitCircle(){

    float radians_between_vertices = 6.28f / (float) kNPoints; //2*pi = 6.28

    for (int i=0; i<kNPoints; ++i){

       g_circle[i] = { (float) cos(radians_between_vertices * i ),
                       (float) sin(radians_between_vertices * i ),
                        1.0f };
    }
}

void DrawCircle(esat::Mat3 m){
  
  esat::Vec2 tr_points[kNPoints];

  for (int i=0; i<kNPoints; i++){
    esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_circle[i]);
    tr_points[i] = {tmp.x, tmp.y};
  }

  esat::DrawSetStrokeColor(255, 255, 255, 255);
  esat::DrawSetFillColor(0, 0, 0, 0);
  esat::DrawSolidPath(&tr_points[0].x, kNPoints);

}

esat::Mat3 UpdateBase(){
  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(100.0f, 100.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(0.0f), m);
  m = esat::Mat3Multiply(esat::Mat3Translate(400.0f, 300.0f), m);

  return m;
}

esat::Mat3 UpdateDerived(esat::Mat3 base){

  esat::Mat3 m = esat::Mat3Identity();
  m = esat::Mat3Multiply(esat::Mat3Scale(0.50f, 0.5), m);
  //m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415f), m);
  //m = esat::Mat3Multiply(esat::Mat3Translate(cos(6.28f / (float)KNPoints * 0.0f), 
  //                                           sin(6.28f / (float)KNPoints * 0.0f)), m);
  m = esat::Mat3Multiply(base, m);
  return m;
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);
  
  InitCircle();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);

    esat::Mat3 base = UpdateBase();
    DrawCircle(base);
    esat::Mat3 derived = UpdateDerived(base);
    DrawCircle(derived);

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}