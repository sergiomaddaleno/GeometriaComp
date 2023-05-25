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

const int kNpoints = 30;
float kCircunference = 2*PI;
float circle_coords[2 * kNpoints] = {0.0f};
float transformed_coords[2 * kNpoints] = {0.0f};


void InitCircle(){
    float portion = kCircunference / kNpoints;
    for(int i=0; i<kNpoints; i++){
        circle_coords[i * 2] = cos(portion * i);
        circle_coords[i * 2 + 1] = sin(portion * i);
    }
}

void DrawCircle(float *circle_coords, float scaleX, float scaleY, float transX, float transY){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    for(int j=0; j<2; j++){
        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Scale(scaleX - j*10, scaleY - j*10),m);
        m = esat::Mat3Multiply(esat::Mat3Translate(transX, transY),m);
        m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

        for(int i=0; i<kNpoints; i++){
            esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f};
            esat::Vec3 result = esat::Mat3TransformVec3(m,p);
            transformed_coords[i * 2] = result.x;
            transformed_coords[i * 2 + 1] = result.y;
        }

        esat::DrawSetStrokeColor(255,255,255);
        esat::DrawSetFillColor(0,0,0,0);
        esat::DrawSolidPath(transformed_coords, kNpoints);
        }
}



int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

  InitCircle();
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawCircle(circle_coords, 110.0f, 90.0f, 0.0f, 0.0f);
    DrawCircle(circle_coords, 50.0f, 90.0f, 0.0f, 0.0f);
    DrawCircle(circle_coords, 70.0f, 50.0f, 0.0f, -40.0f);

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}