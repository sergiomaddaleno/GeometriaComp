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
const unsigned int kWindowWidth = 800;
const unsigned int kWindowHeight = 600;

const float kCircunference = 2*PI;
const int kNumberPoints = 10;
esat::Vec3 star_coords[kNumberPoints] = { 0.0f };
float transformed_coords[kNumberPoints * 2] = { 0.0f };
float shape_coords[kNumberPoints * 2] = { 0.0f };

float kRadius=50.0f;

void InitStar() {

	for (int i=0; i < kNumberPoints >> 1; i++) {
        if (i%2 == 0) {
		    star_coords[i] = { (float) cos(6.28f / kNumberPoints >> 1) * i, 
                               (float) sin(6.28f / kNumberPoints >> 1) * i, 
                               1.0f};

            star_coords[i + kNumberPoints >> 1] = {
                               (float) cos(6.28f / kNumberPoints >> 1) * i, 
                               (float) sin(6.28f / kNumberPoints >> 1) * i, 
                               -1.0f};            
        }else{
            star_coords[i] = { (float) cos(6.28f / kNumberPoints >> 1) * i * 0.6f, 
                               (float) sin(6.28f / kNumberPoints >> 1) * i * 0.6f, 
                               1.0f};

            star_coords[i + kNumberPoints >> 1] = {
                               (float) cos(6.28f / kNumberPoints >> 1) * i * 0.6f, 
                               (float) sin(6.28f / kNumberPoints >> 1) * i * 0.6f, 
                               -1.0f};  
        }
    }
}

/*
esat::Mat4 UpdateStar() {

  esat::Mat4 m = esat::Mat4Identity();

  m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time() * 0.001), m);
  m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, 4.0f), m);
  m = esat::Mat4Multiply(esat::Mat4Projection(), m);
  m = esat::Mat4Multiply(esat::Mat4Scale(50.0f, 50.0f, 1.0f), m);
  m = esat::Mat4Multiply(esat::Mat4Translate(400.0f, 300.0f, 0.0f), m);

  return m;
}

void DrawStar(esat::Mat4 m) {

  esat::Vec3 tr_points[kNumberPoints];
  for (int i = 0; i < kNPoints; ++i){
    tr_points[i] = esat::Mat4TransformVec3(m, star_coords[i]);
  }

  for (int i = 0; i < (kNPoints >> 1); ++i) {
    esat::DrawSetStrokeColor(255, 255, 255, 255);
    
  }

}*/

void DrawStar(const float *shape_coords, float posX, float posY){

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

    for (int i=0; i<kNumberPoints; ++i) {
        esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
        esat::Vec3 result = esat::Mat3TransformVec3(m, p);
        transformed_coords[i * 2] = result.x;
        transformed_coords[i * 2 + 1] = result.y;
    }

    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0, 0);
    esat::DrawSolidPath(transformed_coords, kNumberPoints);
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

  InitStar(star_coords);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);

    DrawStar(star_coords, 400.0f, 300.0f);  
    //DrawStar(star_coords, 410.0f, 300.0f);  
    

    //esat::Mat4 starBase = UpdateStar();
    //DrawStar(starBase);

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}
