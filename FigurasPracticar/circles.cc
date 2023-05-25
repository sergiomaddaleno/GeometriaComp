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


const int kNumberPoints = 10;
const float kCircunference = 6.283185f;

float circle_coords[kNumberPoints * 2] = { 0.0f };
float transformed_coords[kNumberPoints * 2] = { 0.0f };

void InitShapeCoords(float *circle) {
	float portion = kCircunference / kNumberPoints;
	for (int i = 0; i < kNumberPoints; ++i) {
		circle[i * 2] = cos(portion * i);
		circle[i * 2 + 1] = sin(portion * i);
	}
}

void TransformAndDraw(const float *shape_coords, float scale, float angle, float posX, float posY) {

	esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(scale, scale), m);
	m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	for (int i=0; i<kNumberPoints; ++i) {
		esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_coords[i * 2] = result.x;
		transformed_coords[i * 2 + 1] = result.y;
	}

	esat::DrawSetStrokeColor(255, 255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0, 0);
	esat::DrawSolidPath(transformed_coords, kNumberPoints, true);
}

int esat::main(int argc, char **argv) {

  InitShapeCoords(circle_coords);
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    TransformAndDraw(circle_coords, 100.0f, esat::Time()*0.004, 150.0f, 200.0f);
    TransformAndDraw(circle_coords, 175.0f, -esat::Time()*0.001, 600.0f, 300.0f);
    TransformAndDraw(circle_coords, 45.0f, esat::Time()*0.003, 310.0f, 400.0f);
    TransformAndDraw(circle_coords, 60.0f, -esat::Time()*0.001, 310.0f, 270.0f);

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}