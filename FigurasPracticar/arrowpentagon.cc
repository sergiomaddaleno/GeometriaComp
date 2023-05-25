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

float points[] = {
0.0f, 0.4f,
0.65f, 0.4f,
0.65f, 0.25f,
1.0f, 0.5f,
0.65f, 0.75f,
0.65f, 0.6f,
0.0f, 0.6f,
0.0f, 0.4f };

const int kNumberPoints=5; 
const int kNPointsArrow=8; 
const float kCircunference=PI*2;
float circle_coords[kNumberPoints*2]={0.0f};
float transformed_coords[kNumberPoints*2]={0.0f};
float transformed_arrow[kNumberPoints*2]={0.0f};

void InitCircle() {
	float portion = kCircunference / kNumberPoints;

	for (int i = 0; i < kNumberPoints; ++i) {
		circle_coords[i * 2] = cos(portion * i);
		circle_coords[i * 2 + 1] = sin(portion * i);
	}
}

void DrawCircle(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(50.0f, 50.0f), m);
	m = esat::Mat3Multiply(esat::Mat3Rotate(0.4f), m);
  m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

    for(int i=0; i<kNumberPoints; i++){
        esat::Vec3 p = {circle_coords[i * 2], circle_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_coords[i * 2] = result.x;
		transformed_coords[i * 2 + 1] = result.y;
    }

    esat::DrawSetStrokeColor(255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0);
	esat::DrawSolidPath(transformed_coords, kNumberPoints);
}

void DrawArrow(){
    float mPosX = esat::MousePositionX();
    float mPosY = esat::MousePositionY();

    float portion = kCircunference / 5;

    for(int j=0; j<kNumberPoints; j++){
        esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, -0.5f),m);
	      m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001), m);
        m = esat::Mat3Multiply(esat::Mat3Translate(0.9f, 0.5f),m);
	      m = esat::Mat3Multiply(esat::Mat3Scale(50.0f, 50.0f), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j), m);
        m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time()*0.001), m);
	      m = esat::Mat3Multiply(esat::Mat3Translate(mPosX, mPosY),m);

        for(int i=0; i<kNPointsArrow; i++){
          esat::Vec3 p = { points[i * 2], points[i * 2 + 1], 1.0f };
	    	  esat::Vec3 result = esat::Mat3TransformVec3(m, p);
	    	  transformed_arrow[i * 2] = result.x;
	    	  transformed_arrow[i * 2 + 1] = result.y;
        }

        esat::DrawSetStrokeColor(255, 255, 255);
	    esat::DrawSetFillColor(0, 0, 0);
	    esat::DrawSolidPath(transformed_arrow, kNPointsArrow);
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
   
    DrawCircle();
    DrawArrow();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}