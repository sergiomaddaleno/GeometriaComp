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

const int kNumPoints = 7;
const int kNumFigures = 12;
float kCircunference = 2*PI;
float transformed_coords[kNumPoints * 2] = {0.0f};

float points[14] = {
0.0f, 2.0f,
- 5.0f, - 8.0f,
- 8.0f, - 8.0f,
0.0f, 8.0f,
8.0f, - 8.0f,
5.0f, - 8.0f,
0.0f, 2.0f
};

void DrawTrtiangle(){
	float mposX = esat::MousePositionX();
	float mposY = esat::MousePositionY();

    for(int j=0; j<kNumFigures; j++){

        float portion = kCircunference / kNumFigures;

	    esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, 20.0f),m);
	    m = esat::Mat3Multiply(esat::Mat3Scale(5.0f, 9.0f),m);
	    m = esat::Mat3Multiply(esat::Mat3Rotate(portion * -j),m);
	    m = esat::Mat3Multiply(esat::Mat3Translate(mposX, mposY),m);

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

void DrawInTrtiangle(){
	float mposX = esat::MousePositionX();
	float mposY = esat::MousePositionY();

    for(int j=0; j<6; j++){

        float portion = kCircunference / 6;

	    esat::Mat3 m = esat::Mat3Identity();
        m = esat::Mat3Multiply(esat::Mat3Translate(0.0f, -24.0f),m);
	    m = esat::Mat3Multiply(esat::Mat3Scale(3.0f, 3.0f),m);
	    m = esat::Mat3Multiply(esat::Mat3Rotate(portion * j),m);
	    m = esat::Mat3Multiply(esat::Mat3Translate(mposX, mposY),m);

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
   
    DrawTrtiangle();
    DrawInTrtiangle();

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}