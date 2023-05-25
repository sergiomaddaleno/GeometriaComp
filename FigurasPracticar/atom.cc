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

const float kCircunference = 2*PI;
const int kNumberPoints = 100;
float count=0;

float circle_coords[kNumberPoints * 2] = { 0.0f };
float transformed_coords[kNumberPoints * 2] = { 0.0f };
float transformed_Sat_coords[kNumberPoints * 2] = { 0.0f };

float offsetY=0, offsetX=0, radius=73;

void InitShapeCoords(float *circle) {
	float portion = kCircunference / kNumberPoints;

	for (int i = 0; i < kNumberPoints; ++i) {
		circle[i * 2] = cos(portion * i);
		circle[i * 2 + 1] = sin(portion * i);
	}
}

void DrawCenterShape(const float *shape_coords, float posX, float posY){
        
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(15.0f, 15.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

    
    for (int i=0; i<kNumberPoints; ++i) {
        esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
        esat::Vec3 result = esat::Mat3TransformVec3(m, p);
        transformed_coords[i * 2] = result.x;
        transformed_coords[i * 2 + 1] = result.y;
    }
    
    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0);
    esat::DrawSolidPath(transformed_coords, kNumberPoints);
    
}

void DrawSateliteShape(const float *shape_coords, int speed){

    count=count+0.2;
    if(count>=kNumberPoints){count=0;}  
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(15.0f, 15.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(transformed_coords[(int) count * 2], transformed_coords[(int) count * 2 + 1]),m);
    
    for (int i=0; i<kNumberPoints; ++i) {
        esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
        esat::Vec3 result = esat::Mat3TransformVec3(m, p);
        transformed_coords[i * 2] = result.x;
        transformed_coords[i * 2 + 1] = result.y;
    }
    esat::DrawPath(transformed_coords, kNumberPoints);
    
}

void DrawOrbitShape(const float *shape_coords, float posX, float posY){

    esat::Vec3 p;
    esat::Vec3 result;   

   for(int j=0; j<3; j++){
        
        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Scale(100.0f, 30.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001+j), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);
        
        for (int i=0; i<kNumberPoints; ++i) {
            p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
            result = esat::Mat3TransformVec3(m, p);
            transformed_coords[i * 2] = result.x;
            transformed_coords[i * 2 + 1] = result.y;
        }
         
        esat::DrawPath(transformed_coords, kNumberPoints);
        DrawSateliteShape(circle_coords, j);
        
    }    
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

  InitShapeCoords(circle_coords);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawCenterShape(circle_coords, mPosX, mPosY);
    DrawOrbitShape(circle_coords, mPosX, mPosY);

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}