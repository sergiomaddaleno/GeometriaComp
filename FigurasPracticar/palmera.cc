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
float mPosX;
float mPosY;

float points[20] = {
0.0f, 0.0f, 0.45f, 0.0f,
0.8f, 0.35f, 0.9f, 0.35f,
1.0f, 0.25f, 1.0f, 0.35f,
0.9f, 0.45f, 0.8f, 0.45f,
0.45f, 0.1f, 0.0f, 0.1f
};

const int kNumberPoints = 30;
const int kNumberPointsHex = 6;
float circle_coords[kNumberPoints * 2] = { 0.0f };
float hex_coords[kNumberPointsHex * 2] = { 0.0f };
float transformed_coords[20] = { 0.0f };
float transformed_circle_coords[kNumberPoints] = { 0.0f };
float transformed_hex_coords[kNumberPointsHex] = { 0.0f };
const float kCircunference = 2*PI;

float offsetX=0, offsetY=0, radius=35;

void InitCircle(float *circle) {
	float portion = kCircunference / kNumberPoints;
	for (int i = 0; i < kNumberPoints; ++i) {
		circle[i * 2] = cos(portion * i);
		circle[i * 2 + 1] = sin(portion * i);
	}
}

void InitHex(float *hex) {
	float portion = kCircunference / kNumberPointsHex;
	for (int i = 0; i < kNumberPointsHex; ++i) {
		hex[i * 2] = cos(portion * i);
		hex[i * 2 + 1] = sin(portion * i);
	}
}

void DrawHornPart1(float scale, float angle, float posX, float posY) {

  for (int j = 0; j < 7; j++) {

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Translate(0.82f, 0.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Scale(60.0f, 60.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / 7)*-j), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY), m);

    for (int i = 0; i <= 10; ++i) {
      esat::Vec3 p = { points[i * 2], points[i * 2 + 1], 1.0f };
      esat::Vec3 result = esat::Mat3TransformVec3(m, p);
      transformed_coords[i * 2] = result.x;
      transformed_coords[i * 2 + 1] = result.y;
    }

    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0);
    esat::DrawSolidPath(transformed_coords, 10);

  }
}

void DrawHornPart2(float scale, float angle, float posX, float posY) {

  for (int j = 0; j < 7; j++) {

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Translate(0.82f, 0.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Scale(-60.0f, 60.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / 7)*j+3.1), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY), m);

    for (int i = 0; i <= 10; ++i) {
      esat::Vec3 p = { points[i * 2], points[i * 2 + 1], 1.0f };
      esat::Vec3 result = esat::Mat3TransformVec3(m, p);
      transformed_coords[i * 2] = result.x;
      transformed_coords[i * 2 + 1] = result.y;
    }

    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0, 0, 0);
    esat::DrawSolidPath(transformed_coords, 10);

  }
}

void DrawCircle(const float *shape_coords, float scale, float angle, float posX, float posY) {

	esat::Mat3 m = esat::Mat3Identity();
	m = esat::Mat3Multiply(esat::Mat3Scale(scale, scale), m);
	m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
	m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	for (int i=0; i<kNumberPoints; ++i) {
		esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
		esat::Vec3 result = esat::Mat3TransformVec3(m, p);
		transformed_circle_coords[i * 2] = result.x;
		transformed_circle_coords[i * 2 + 1] = result.y;
	}

	esat::DrawSetStrokeColor(255, 255, 255);
	esat::DrawSetFillColor(0, 0, 0);
	esat::DrawSolidPath(transformed_circle_coords, kNumberPoints);
}

void DrawHexagon(const float *shape_coords, float scale, float angle, float posX, float posY) {

  for (int j = 0; j < 7; j++) {

	  esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Translate(20.0f, 0.0f),m);
	  m = esat::Mat3Multiply(esat::Mat3Scale(scale, scale), m);
	  m = esat::Mat3Multiply(esat::Mat3Rotate((kCircunference / 7)*j), m);
	  m = esat::Mat3Multiply(esat::Mat3Translate(posX, posY),m);

	  for (int i=0; i<kNumberPointsHex; ++i) {
	  	esat::Vec3 p = { shape_coords[i * 2], shape_coords[i * 2 + 1], 1.0f };
	  	esat::Vec3 result = esat::Mat3TransformVec3(m, p);
	  	transformed_hex_coords[i * 2] = result.x;
	  	transformed_hex_coords[i * 2 + 1] = result.y;
	  }

	  esat::DrawSetStrokeColor(255, 255, 255);
	  esat::DrawSetFillColor(0, 0, 0);
	  esat::DrawPath(transformed_hex_coords, kNumberPointsHex);
  }
}

int esat::main(int argc, char **argv) {
 
  esat::WindowInit(800,600);
  WindowSetMouseVisibility(true);

  InitCircle(circle_coords);
  InitHex(hex_coords);
  
  while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    mPosX = esat::MousePositionX();
    mPosY = esat::MousePositionY();

  	last_time = esat::Time();
    esat::DrawBegin();
    esat::DrawClear(0,0,0);
   
    DrawCircle(circle_coords, 50.0f, 0.0f, mPosX, mPosY);
    DrawHornPart1(50.0f, 0.0f, mPosX, mPosY); 
    DrawHornPart2(50.0f, 0.0f, mPosX, mPosY); 
    DrawHexagon(hex_coords, 5.0f, 0.0f, mPosX, mPosY);

    esat::DrawEnd();

   do{
    current_time = esat::Time();
    }while((current_time-last_time)<=1000.0/fps);
    
   esat::WindowFrame();
  }

  esat::WindowDestroy();

  return 0;
}